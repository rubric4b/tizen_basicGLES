//
// Created by hobbang5 on 2015-11-09.
//

#ifndef BASICGLES_GL_UTILS_H
#define BASICGLES_GL_UTILS_H

#define UPDATE_INTERVAL 1000ll

void init_matrix(float* result);

void multiply_matrix(float* result, const float matrix0[16], const float matrix1[16]);

void rotate_xyz(float* result, const float anglex, const float angley, const float anglez);

void translate_xyz(float* result, const float translatex,
                   const float translatey, const float translatez);

void view_set_ortho(float* result, const float left, const float right,
                    const float bottom, const float top, const float near, const float far);

void view_set_perspective(float* result, const float fovy,
                          const float aspect, const float near, const float far);

long long get_ticks();

float get_fps();

#endif //BASICGLES_GL_UTILS_H
