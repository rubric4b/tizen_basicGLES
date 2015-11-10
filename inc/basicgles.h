#ifndef __basicgles_H__
#define __basicgles_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <Elementary_GL_Helpers.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "basicgles"

#if !defined(PACKAGE)
#define PACKAGE "org.example.basicgles"
#endif

ELEMENTARY_GLVIEW_GLOBAL_DECLARE();

typedef struct appdata {
	const char *name;

	// All graphical objects here are pointers to the value of the type Evas_Object
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *naviframe;

	Evas_Object *fps_label;
	Ecore_Animator *ani;

	int glview_w, glview_h;

	/* GL related data here... */
	unsigned int program;
	unsigned int vtx_shader;
	unsigned int fgmt_shader;
	unsigned int texture;

	float xangle;
	float yangle;

	// Locations for vertex attribute
	unsigned int idx_a_position;
	unsigned int idx_a_color;
	unsigned int idx_a_tex;

	// Locations for shdaer uniforms
	int idx_mvp;
	int idx_tex;

	float mvp[16];

	Eina_Bool mouse_down : 1;
	Eina_Bool initialized :1;
} appdata_s;

// in gl.c
Evas_Object*
		add_glview(Evas_Object* parent, appdata_s *ad);

// in gl_tex.c
unsigned int read_texture(Evas_Object *parent, const char *filename);

#endif /* __basicgles_H__ */
