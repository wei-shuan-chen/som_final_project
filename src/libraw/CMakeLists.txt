add_library(raw STATIC)

target_sources(raw PRIVATE "RAWmodel.cpp")

target_include_directories(raw PUBLIC "include")

target_link_libraries(raw PRIVATE
    glm::glm
)