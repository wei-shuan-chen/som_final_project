#include "transfer_function_widget.h"

TransferFunctionWidget::TransferFunctionWidget(int range)
  : is_grabbing_(false)
  , is_sel_lock(false)
  , active_group_(kGroupR)
  , active_point_(0)
  , max_point_count_(10)
  , handle_radius_(8)
  , handle_border_(2)
  , range_x_(range)
  , range_y_(256)
  , scale_(2)
  , grid_fineness_(4)
  , canvas_margins_(2 * handle_radius_, 2 * handle_radius_)
  , label_("Transfer Function")
  , draw_ord_{0, 1, 2, 3}
  , ctrl_groups_{}
{
  ctrl_groups_[kGroupG].emplace_back(80.0f, 256.0f);
  ctrl_groups_[kGroupG].emplace_back(85.0f, 256.0f);
  ctrl_groups_[kGroupG].emplace_back(85.0f, 0.0f);
  ctrl_groups_[kGroupG].emplace_back(210.0f, 0.0f);
  ctrl_groups_[kGroupG].emplace_back(210.0f, 256.0f);
  ctrl_groups_[kGroupG].emplace_back(240.0f, 256.0f);
  ctrl_groups_[kGroupB].emplace_back(210.0f, 256.0f);
  ctrl_groups_[kGroupB].emplace_back(240.0f, 256.0f);
  ctrl_groups_[kGroupA].emplace_back(80.0f, 10.0f);
  ctrl_groups_[kGroupA].emplace_back(85.0f, 10.0f);
  ctrl_groups_[kGroupA].emplace_back(86.0f, 0.0f);
  ctrl_groups_[kGroupA].emplace_back(200.0f, 0.0f);
  ctrl_groups_[kGroupA].emplace_back(210.0f, 10.0f);
  ctrl_groups_[kGroupA].emplace_back(240.0f, 10.0f);
}

bool
TransferFunctionWidget::Render()
{
  using namespace ImGui;
  using namespace imgui::color;

  ImDrawList* draw_list = GetWindowDrawList();
  ImGuiWindow* window = GetCurrentWindow();

  // if (Button("Output tf_record.txt")) {
  //   TfRecordFile();
  // }

  BeginGroup();
  Text("Selection Lock");
  if (Button("Red")) {
    is_sel_lock = true;
    SetActiveGroup(kGroupR);
  }
  SameLine();
  if (Button("Green")) {
    is_sel_lock = true;
    SetActiveGroup(kGroupG);
  }
  SameLine();
  if (Button("Blue")) {
    is_sel_lock = true;
    SetActiveGroup(kGroupB);
  }
  SameLine();
  if (Button("Opacity")) {
      is_sel_lock = true;
      SetActiveGroup(kGroupA);
  }
  SameLine();
  if (Button("Release")) {
    is_sel_lock = false;
  }
  EndGroup();
  Dummy(ImVec2(0, 3));

  // prepare canvas
  ImVec2 canvas(range_x_ * scale_, range_y_ * scale_);
  canvas_origin_ = window->DC.CursorPos + canvas_margins_;
  ImRect bb(canvas_origin_, canvas_origin_ + canvas); // bounding-box
  ImRect hoverable(bb.Min - canvas_margins_, bb.Max + canvas_margins_);

  ItemSize(hoverable);
  ItemAdd(hoverable, 0);
  ImGuiID const id = window->GetID(label_.c_str());
  ItemHoverable(hoverable, id);
  RenderFrame(canvas_origin_, bb.Max, GetColorU32(ImGuiCol_FrameBg, 1), true, GetStyle().FrameRounding);

  // background grid
  for (int i = 0; i <= canvas.x; i += (canvas.x / (2 << 4))) {
    draw_list->AddLine(ImVec2(canvas_origin_.x + i, canvas_origin_.y),
                       ImVec2(canvas_origin_.x + i, bb.Max.y),
                       GetColorU32(ImGuiCol_TextDisabled));
  }
  for (int i = 0; i <= canvas.y; i += (canvas.y / (2 << grid_fineness_))) {
    draw_list->AddLine(ImVec2(canvas_origin_.x, canvas_origin_.y + i),
                       ImVec2(bb.Max.x, canvas_origin_.y + i),
                       GetColorU32(ImGuiCol_TextDisabled));
  }

  bool const on_clicked_left = IsMouseClicked(ImGuiMouseButton_Left);
  bool const on_clicked_right = IsMouseClicked(ImGuiMouseButton_Right);
  bool const on_clicked = on_clicked_left || on_clicked_right;
  bool const on_released_left = IsMouseReleased(ImGuiMouseButton_Left);
  bool const on_released_right = IsMouseReleased(ImGuiMouseButton_Right);
  bool const on_released = on_released_left || on_released_right;
  bool const on_dragging_left = IsMouseDragging(ImGuiMouseButton_Left);
  bool const on_dragging_right = IsMouseDragging(ImGuiMouseButton_Right);
  bool const on_dragging = on_dragging_left || on_dragging_right;
  bool const is_canvas_hovered = IsItemHovered();

  bool changed = false;

  if (on_clicked && is_canvas_hovered) {
    using namespace std;

    ImVec2 const mouse = TfPos(GetIO().MousePos);

    float min = INT_MAX;
    int group_id = 0;
    for (int color = 0; color < 4; ++color) {
      for (int point = 0; point < ctrl_groups_[color].size(); ++point) {
        ImVec2 const& d = mouse - ctrl_groups_[color][point];
        float const dist = d.x * d.x + d.y * d.y;
        if (min > dist) {
          min = dist;
          group_id = color;
          active_point_ = point;
        }
      }
    }

    // Avoid SetActiveGroup(0) after left-clicking on empty canvas
    bool const valid_sel = (min < 2 * handle_radius_ * handle_radius_);
    if (valid_sel && !is_sel_lock && on_clicked_left)
      SetActiveGroup(group_id);
    if (group_id == active_group_)
      is_grabbing_ = valid_sel;
  }

  std::vector<ImVec2>& GP = ctrl_groups_[active_group_];

  if (is_grabbing_ && is_canvas_hovered) {
    ImVec2 const mouse = TfPos(GetIO().MousePos);

    if (on_clicked_right && !GP.empty()) {
      if (GP.size() <= 2) {
        GP.clear();
      } else {
        GP.erase(GP.begin() + active_point_);
        std::sort(GP.begin(), GP.end(), [](auto const& a, auto const& b) { return a.x < b.x; });
      }
      changed = true;
    } else if (on_dragging_left) {
      ImVec2 next_pos = {std::round(mouse.x), mouse.y};
      float max_x = range_x_;
      float min_x = 0.0f;

      if (active_point_ > 0)
        min_x = GP[active_point_ - 1].x;
      if (active_point_ < GP.size() - 1)
        max_x = GP[active_point_ + 1].x;

      if (next_pos.x < min_x)
        next_pos.x = min_x;
      if (next_pos.y < 0.0f)
        next_pos.y = 0.0f;
      if (next_pos.x > max_x)
        next_pos.x = max_x;
      if (next_pos.y > range_y_)
        next_pos.y = range_y_;

      GP[active_point_] = next_pos;
      std::sort(GP.begin(), GP.end(), [](auto const& a, auto const& b) { return a.x < b.x; });

      changed = true;
    }
    SetTooltip("(%.2f, %.2f)", GP[active_point_].x, GP[active_point_].y);
  } else if (is_canvas_hovered) {
    ImVec2 const mouse = TfPos(GetIO().MousePos);
    if (on_clicked_right && GP.size() < max_point_count_) {
      ImVec2 new_pos = {std::round(mouse.x), mouse.y};
      if (new_pos.x > 0.0f && new_pos.x < range_x_ && new_pos.y > 0.0f && new_pos.y < range_y_) {
        GP.emplace_back(new_pos.x, new_pos.y);
        std::sort(GP.begin(), GP.end(), [](auto const& a, auto const& b) { return a.x < b.x; });
      }

      changed = true;
    }
  }

  if (on_released) {
    active_point_ = 0;
    is_grabbing_ = false;
  }

  // Draw lines first
  for (int i = 0; i < ctrl_groups_.size(); ++i) {

    int const id = draw_ord_[i];
    auto const& group = ctrl_groups_[id];
    if (group.empty())
      continue;

    ImColor line_color;

    if (is_sel_lock) {
      line_color = (id == active_group_) ? kWhite : SetAlpha(kWhite, 0.6f);
    } else {
      line_color = kWhite;
    }
    for (int p = 0; p < group.size() - 1; ++p) {
      draw_list->AddLine(ScreenPos(group[p]), ScreenPos(group[p + 1]), line_color, 1.2f);
    }
  }

  // Draw handles
  for (int i = 0; i < 4; ++i) {

    int const id = draw_ord_[i];

    ImColor handle_color;
    ImColor line_color;
    float radius = handle_radius_;

    if (id == active_group_) {
      handle_color = SetAlpha(kPrimary[id], 0.6f);
      line_color = kWhite;
      radius = handle_radius_ * 1.2f;
    } else {
      if (is_sel_lock) {
        line_color = SetAlpha(kWhite, 0.5f);
        handle_color = SetAlpha(kPrimary[id], 0.5f);
      } else {
        line_color = kWhite;
        handle_color = kPrimary[id];
      }
    }
    for (auto const& p : ctrl_groups_[id]) {
      ImVec2 const pos = ScreenPos(p);
      draw_list->AddCircleFilled(pos, radius, line_color);
      draw_list->AddCircleFilled(pos, radius - handle_border_, handle_color);
    }
  }

  return changed;
}

std::vector<float>
TransferFunctionWidget::TransferFunction() const
{
  std::vector<float> function(range_x_ * 4, 0.0f);

  auto const& gp_red = ctrl_groups_[kGroupR];
  auto const& gp_green = ctrl_groups_[kGroupG];
  auto const& gp_blue = ctrl_groups_[kGroupB];
  auto const& gp_gray = ctrl_groups_[kGroupA];

  float const norm_ratio = 1.0f / 256.0f;

  for (int r = 1; r < gp_red.size(); ++r) {
    ImVec2 const b = gp_red[r];
    ImVec2 const a = gp_red[r - 1];

    int const interval = (b.x - a.x);
    float const slope = (b.y - a.y) / interval;

    for (int i = 0; i < interval; ++i) {
      int const x = (i + static_cast<int>(a.x)) * 4 + 0;
      function[x] = (i * slope + a.y) * norm_ratio;
    }
  }

  for (int g = 1; g < gp_green.size(); ++g) {
    ImVec2 const b = gp_green[g];
    ImVec2 const a = gp_green[g - 1];

    int const interval = (b.x - a.x);
    float const slope = (b.y - a.y) / interval;

    for (int i = 0; i < interval; ++i) {
      int const x = (i + static_cast<int>(a.x)) * 4 + 1;
      function[x] = (i * slope + a.y) * norm_ratio;
    }
  }

  for (int b_ = 1; b_ < gp_blue.size(); ++b_) {
    ImVec2 const b = gp_blue[b_];
    ImVec2 const a = gp_blue[b_ - 1];

    int const interval = (b.x - a.x);
    float const slope = (b.y - a.y) / interval;

    for (int i = 0; i < interval; ++i) {
      int const x = (i + static_cast<int>(a.x)) * 4 + 2;
      function[x] = (i * slope + a.y) * norm_ratio;
    }
  }
  for (int A = 1; A < gp_gray.size(); ++A) {
      ImVec2 const b = gp_gray[A];
      ImVec2 const a = gp_gray[A - 1];

      int const interval = (b.x - a.x);
      float const slope = (b.y - a.y) / interval;

      for (int i = 0; i < interval; ++i) {
          int const x = (i + static_cast<int>(a.x)) * 4 + 3;
          function[x] = (i * slope + a.y) * norm_ratio;
      }
  }
  // for(int c = 0; c < 256; c++){
  //     for(int j = 0; j < 4; j++){
  //       printf("%f ", function[c*4+j]);
  //     }
  //     printf("\n");
  // }
  return function;
}

inline void
TransferFunctionWidget::SetActiveGroup(int group_id)
{
  if (group_id < kGroupR || group_id > kGroupA) {
    std::invalid_argument("Valid groups are kGroupR, kGroupG, and kGroupB.");
  }

  std::vector<int> group_set{kGroupR, kGroupG, kGroupB, kGroupA };
  group_set.erase(group_set.begin() + group_id);

  active_group_ = group_id;

  // Let the group be the last one to render.
  draw_ord_.back() = group_id;

  // Don't care
  for(int i=0;i<ctrl_groups_.size() - 1;i++)
    draw_ord_[i] = group_set[i];
}

/*
 * Return the corresponding position in Transfer-function coordinate
 *
 * @param pos  Position in Screen coordinate
 */
inline ImVec2
TransferFunctionWidget::TfPos(ImVec2 pos) const
{
  float const height = range_y_ * scale_;
  float const px = (pos.x - canvas_origin_.x) / scale_;
  float const py = -((pos.y - canvas_origin_.y - height) / scale_);
  return ImVec2(px, py);
}

/*
 * Return the corresponding position in Screen coordinate
 *
 * @param pos  Position in Transfer-function coordinate
 */
inline ImVec2
TransferFunctionWidget::ScreenPos(ImVec2 pos) const
{
  float const height = range_y_ * scale_;
  return (ImVec2(pos.x * scale_, (height - pos.y * scale_)) + canvas_origin_);
}

void
TransferFunctionWidget::TfRecordFile() const
{
  auto const function = TransferFunction();
  std::ofstream file;
  file.open("tf_record.txt");
  for (int i = 0; i < range_x_; ++i) {
    file << std::setprecision(2);
    file << std::setw(6) << function[4 * i] << "\t";
    file << std::setw(6) << function[4 * i + 1] << "\t";
    file << std::setw(6) << function[4 * i + 2] << "\t";
    file << std::setw(6) << function[4 * i + 3] << "\n";
  }
  file.close();
}
