#ifndef __basicgles_H__
#define __basicgles_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "basicgles"

#if !defined(PACKAGE)
#define PACKAGE "org.example.basicgles"
#endif

typedef struct appdata
{
	const char* name;

	// All graphical objects here are pointers to the value of the type Evas_Object
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *naviframe;

} appdata_s;


#endif /* __basicgles_H__ */
