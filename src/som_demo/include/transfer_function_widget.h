#pragma once

#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_color.h>
#include <imgui_internal.h>

class TransferFunctionWidget
{
  enum { kGroupR = 0, kGroupG = 1, kGroupB = 2, kGroupA = 3};

  bool is_grabbing_;
  bool is_sel_lock;
  int active_group_;
  int active_point_;
  int max_point_count_;
  int handle_radius_;
  int handle_border_;
  int range_x_;
  int range_y_;
  int scale_;
  int grid_fineness_;
  ImVec2 canvas_margins_;
  ImVec2 canvas_origin_;
  std::string label_;

  std::array<int, 4> draw_ord_;
  std::array<std::vector<ImVec2>, 4> ctrl_groups_;

private:
  ImVec2 TfPos(ImVec2 pos) const;
  ImVec2 ScreenPos(ImVec2 pos) const;
  void TfRecordFile() const;
  void SetActiveGroup(int group_id);

public:
  TransferFunctionWidget(int range);
  bool Render();
  std::vector<float> TransferFunction() const;
};
