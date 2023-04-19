add_library(som STATIC)

target_sources(som PRIVATE "SOM.cpp")

target_include_directories(som PUBLIC "include")

target_link_libraries(som PRIVATE
    glm::glm
)