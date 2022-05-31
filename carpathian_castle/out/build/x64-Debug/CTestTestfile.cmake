# CMake generated Testfile for 
# Source directory: C:/Users/elois/Documents/carpathian_castle/carpathian_castle
# Build directory: C:/Users/elois/Documents/carpathian_castle/carpathian_castle/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(that-test-I-made "C:/Users/elois/Documents/carpathian_castle/carpathian_castle/out/build/x64-Debug/unitTests.exe")
set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/elois/Documents/carpathian_castle/carpathian_castle/CMakeLists.txt;125;add_test;C:/Users/elois/Documents/carpathian_castle/carpathian_castle/CMakeLists.txt;0;")
subdirs("_deps/pugixml-build")
subdirs("_deps/sfml-build")
subdirs("tmxlite-build/tmxlite")
subdirs("mainLauncher")
subdirs("src")
subdirs("googletest-build")
