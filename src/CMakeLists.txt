add_executable( rtwg
main.cpp

)

target_link_libraries(rtwg RTplatec GL3W ${OPENGL_LIBRARIES}   ${GLFW_STATIC_LIBRARIES}  ${ANTTWEAKBAR_LIBRARY} ${LIBNOISE_LIBRARIES}  ${X11_LIBRARIES})