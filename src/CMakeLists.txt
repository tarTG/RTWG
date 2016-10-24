add_executable( rtwg
main.cpp
ShaderLoader.cpp
inputHandler.cpp
simpleRender.cpp
RendToTex.cpp
TextureLoader.cpp
)

target_link_libraries(rtwg RTplatec GL3W ${OPENGL_LIBRARIES}   ${GLFW_STATIC_LIBRARIES}  
                         ${IL_LIBRARIES}    ${ILU_LIBRARIES}   ${ILUT_LIBRARIES}
                    ${ANTTWEAKBAR_LIBRARY} ${LIBNOISE_LIBRARIES}  ${X11_LIBRARIES})