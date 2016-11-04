add_library( rtwg3D
Camera.cpp
Shadows.cpp
WaterRender.cpp
landscapeRender.cpp
Light.cpp
display3D.cpp
plane.cpp
)



SET(SHADER_PATH "${PROJECT_SOURCE_DIR}/Shader/")
ADD_DEFINITIONS(-DSHADER_PATH="${SHADER_PATH}")
SET(RESOURCES_PATH "${PROJECT_SOURCE_DIR}/res/")
ADD_DEFINITIONS(-DRESOURCES_PATH="${RESOURCES_PATH}")