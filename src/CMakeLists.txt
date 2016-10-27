add_executable( rtwg
main.cpp
ShaderLoader.cpp
inputHandler.cpp
simpleRender.cpp
RendToTex.cpp
TextureLoader.cpp
display2D.cpp
simulation.cpp
)
SET(SHADER_PATH "${PROJECT_SOURCE_DIR}/Shader/")
ADD_DEFINITIONS(-DSHADER_PATH="${SHADER_PATH}")

target_link_libraries(rtwg RTplatec  ${OPENGL_LIBRARIES} GL3W  ${GLFW_STATIC_LIBRARIES}  
                         ${IL_LIBRARIES}    ${ILU_LIBRARIES}   ${ILUT_LIBRARIES}
                    ${ANTTWEAKBAR_LIBRARY} ${LIBNOISE_LIBRARIES}  ${X11_LIBRARIES})