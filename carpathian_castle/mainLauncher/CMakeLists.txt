
add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics tmxlite)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources ${CMAKE_SOURCE_DIR}/resources/images ${CMAKE_SOURCE_DIR}/resources/images/tilemap ${CMAKE_SOURCE_DIR}/resources/Sprite
                   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(mainLauncher copy-resources)
