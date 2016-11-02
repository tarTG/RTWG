/* 
 * File:   camaraHandler.h
 * Author: tg
 *
 * Created on 19. Februar 2015, 08:24
 */

#ifndef CAMARAHANDLER_H
#define	CAMARAHANDLER_H
 #define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


class camaraHandler 
{
public:
    camaraHandler() = default;
    
    void SetCamera_look_at(glm::vec3 camera_look_at);
    
    void SetCamera_position(glm::vec3 camera_position);
    
    void SetMove_camera(bool move_camera);
    
    void SetField_of_view(double field_of_view);
    
    void SetAspect(double aspect);
    
    void Update(uint64_t time);
    
    void SetPitch(double degrees);
    
    void SetRoll(double degrees);
    
    void SetYaw(double degrees);
    
    void MoveX(double distance);
    
    void MoveY(double distance);
    
    void MoveZ(double distance);
    
    void MoveHead(double x, double y);
    
    void setViewport(int x, int y, int width,  int height);

    void setClipping(double near_clip, double far_clip);
    
    glm::mat4 getProjection();
    
    glm::mat4 getView();
    
    glm::vec2 getViewPort();
    
    void loadViewPort();
    
private:
    
    uint32_t viewport_x, viewport_y;
    uint32_t window_width, window_heigth;
    
    double aspect, field_of_view, near_clip,far_clip;
    
    float scale, roll, pitch, yaw;
    float max_pitch = 25, max_roll = 25, max_yaw= 25;
    
    bool move_camera;
    
    glm::vec3 camera_position, camera_position_delta;
    glm::vec3 camera_look_at;
    glm::vec3 camera_direction;
    
    glm::vec3 camera_up {0,-1,0};
    glm::quat rot_quat;
    glm::vec3 last_position;
    
    glm::mat4 projection;
};

#endif	/* CAMARAHANDLER_H */

