add_library( rtwg3D
Camera.cpp
Shadows.cpp
WaterRender.cpp
landscapeRender.cpp

)



SET(SHADER_PATH "${PROJECT_SOURCE_DIR}/Shader/")
ADD_DEFINITIONS(-DSHADER_PATH="${SHADER_PATH}")
