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

add_subdirectory("3DRender")


SET(SHADER_PATH "${PROJECT_SOURCE_DIR}/Shader/")
ADD_DEFINITIONS(-DSHADER_PATH="${SHADER_PATH}")

SET(RESOURCES_PATH "${PROJECT_SOURCE_DIR}/res/")
ADD_DEFINITIONS(-DRESOURCES_PATH="${RESOURCES_PATH}")

SET(OUTPUT_PATH "${PROJECT_SOURCE_DIR}/outputIMG/")
ADD_DEFINITIONS(-DOUTPUT_PATH="${OUTPUT_PATH}")


target_link_libraries(rtwg dl RTplatec rtwg3D ${OPENGL_LIBRARIES} GL3W  ${GLFW_LIBRARIES}  
                         ${IL_LIBRARIES}    ${ILU_LIBRARIES}   ${ILUT_LIBRARIES}
                    ${ANTTWEAKBAR_LIBRARY} ${LIBNOISE_LIBRARIES}  ${X11_LIBRARIES})