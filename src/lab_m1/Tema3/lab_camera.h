#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include "iostream"



namespace implemented
{
    class Camerahomework3
    {
     public:
         Camerahomework3()
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

         Camerahomework3(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~Camerahomework3()
        { }

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);

            if (once)
            {
                distanceToTarget = glm::abs(glm::length(center - position));
                once = false;
            }
        }

        void printvect()
        {
            std::cout << position.x << " " << position.y << " " << position.z << " " << std::endl;
            std::cout << up.x << " " << up.y << " " << up.z << " " << std::endl;
            std::cout << forward.x << " " << forward.y << " " << forward.z << " " << std::endl;
        }

        void MoveForward(float distance)
        {
            // Translates the camera using the `dir` vector computed from
            // `forward`. Movement will always keep the camera at the same
            // height. For example, if you rotate your head up/down, and then
            // walk forward, then you will still keep the same relative
            // distance (height) to the ground!
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void MoveonDirection(glm::vec3 dir, float distance)
        {
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            // TODO(student): Translate the camera using the `forward` vector.
            // What's the difference between `TranslateForward()` and
            // `MoveForward()`?
            position += glm::normalize(forward) * distance;
            //printvect();

        }

        void TranslateUpward(float distance)
        {
            // TODO(student): Translate the camera using the `up` vector.

            position += glm::normalize(up) * distance;
            //printvect();

        }

        void TranslateRight(float distance)
        {
            // TODO(student): See instructions below. Read the entire thing!
            // You need to translate the camera using the `right` vector.
            // Usually, however, translation using camera's `right` vector
            // is not very useful, because if the camera is rotated around the
            // `forward` vector, then the translation on the `right` direction
            // will have an undesired effect, more precisely, the camera will
            // get closer or farther from the ground. The solution is to
            // actually use the projected `right` vector (projected onto the
            // ground plane), which makes more sense because we will keep the
            // same distance from the ground plane.

            glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
            position += dir * distance;
            //printvect();

        }

        void RotateFirstPerson_OX(float angle)
        {
            // TODO(student): Compute the new `forward` and `up` vectors.
            // Don't forget to normalize the vectors! Use `glm::rotate()`.

            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, right);
            right = rotation * glm::vec4(right, 1);
            forward = rotation * glm::vec4(forward, 0);
            up = glm::cross(right, forward); // cross - vector perpendicular cu planul format de cei 2 vectori

        }

        void RotateFirstPerson_OY(float angle)
        {
            // TODO(student): Compute the new `forward`, `up` and `right`
            // vectors. Use `glm::rotate()`. Don't forget to normalize the
            // vectors!

            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));

            forward = rotation * glm::vec4(forward, 1);
            up = rotation * glm::vec4(up,0);
            right = glm::cross(forward, up); // cross - vector perpendicular cu planul format de cei 2 vectori

        }

        void RotateFirstPerson_OZ(float angle)
        {
            // TODO(student): Compute the new `right` and `up`. This time,
            // `forward` stays the same. Use `glm::rotate()`. Don't forget
            // to normalize the vectors!

            glm::mat4 rotation = glm::rotate(glm::mat4(1), angle, forward);

            forward = rotation * glm::vec4(forward, 1);
            up = rotation * glm::vec4(up, 0);
            right = glm::cross(forward, up); // cross - vector perpendicular cu planul format de cei 2 vectori

        }

        void RotateThirdPerson_OX(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OX axis. Use `distanceToTarget` as translation distance.

            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);

        }

        void RotateThirdPerson_OY(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OY axis.

            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);

        }

        void RotateThirdPerson_OZ(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OZ axis.

            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward(-distanceToTarget);

        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        bool once = true;
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implemented
