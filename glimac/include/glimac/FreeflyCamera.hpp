#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {

    class FreeflyCamera {
        private:
            glm::vec3 m_Position; 
            float m_fPhi;
            float m_fTheta;
            glm::vec3 m_FrontVector;
            glm::vec3 m_LeftVector;
            glm::vec3 m_UpVector;

            inline void computeDirectionVectors(){
                m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta)*cos(m_fPhi));
                m_LeftVector = glm::vec3(sin(m_fPhi+ (glm::pi<float>() * 0.5)), 0, cos(m_fPhi+ (glm::pi<float>() * 0.5)));
                m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
            }

        public:
            FreeflyCamera(){
                m_Position = glm::vec3(0., 5., 30.);
                m_fPhi = glm::pi<float>();
                m_fTheta = 0.0;
                computeDirectionVectors();
            }

            inline void moveLeft(float t){
                m_Position += m_LeftVector*t;
            }

            inline void moveFront(float t){
                m_Position += m_FrontVector*t;
            }

            inline void rotateLeft(float degree){
                degree = glm::radians(degree);
                m_fPhi = m_fPhi + degree;
                computeDirectionVectors();
            }

            inline void rotateUp(float degree){
                degree = glm::radians(degree);
                m_fTheta = m_fTheta + degree;
                computeDirectionVectors();
            }

            inline glm::mat4 getViewMatrix() const {
                glm::vec3 point = m_FrontVector + m_Position;
                glm::mat4 ViewMatrix = glm::lookAt(m_Position, point, m_UpVector);

                return ViewMatrix;
            }

    };

}
