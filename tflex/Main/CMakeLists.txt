include_directories(${tflex_gui_app_SOURCE_DIR}/Lib/inc)
link_directories(${tflex_gui_app_SOURCE_DIR}/Lib/src)

add_executable(tflex_gui_app main.cpp)

target_link_libraries(tflex_gui_app Lib)
