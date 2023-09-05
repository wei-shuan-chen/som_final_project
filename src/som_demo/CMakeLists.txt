
add_executable(som-demo) # create cmake target



set_target_properties(som-demo
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_sources(som-demo PRIVATE
    "main.cpp"
    "world.cpp"
    "matrixStack.cpp"
    "Drawmodel.cpp"
    "Gui.cpp"
    "stb_image.cpp"
    "textureMap.cpp"
    "logger.c"
    "carve.cpp"
    "transfer_function_widget.cc"
    "Math.cpp"
)


target_include_directories(som-demo PRIVATE
    "include/"
)


target_link_libraries(som-demo PRIVATE
    som
    raw
    glad
    imgui
    glm::glm
    glfw
    OpenGL::GL
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(som-demo PRIVATE OpenMP::OpenMP_CXX)
endif()

add_custom_command(TARGET som-demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/shader"
        "$<TARGET_FILE_DIR:som-demo>/shader"
    VERBATIM
)
add_custom_command(TARGET som-demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/texture"
        "$<TARGET_FILE_DIR:som-demo>/texture"
    VERBATIM
)

add_custom_command(TARGET som-demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/stl"
        "$<TARGET_FILE_DIR:som-demo>/stl"
    VERBATIM
)

add_custom_command(TARGET som-demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_SOURCE_DIR}/raw"
        "$<TARGET_FILE_DIR:som-demo>/raw"
    VERBATIM
)