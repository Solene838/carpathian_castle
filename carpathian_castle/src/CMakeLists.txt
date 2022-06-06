
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}    "Player.h" "Player.cpp"  "Object.h" "Object.cpp" "Assets.h" "Assets.cpp" "Textbox.h" "Enigma.h" "Enigma.cpp")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics)
