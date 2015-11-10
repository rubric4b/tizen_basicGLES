#include "basicgles.h"




static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

static void create_indicator(appdata_s *ad)
{
	elm_win_conformant_set(ad->win, EINA_TRUE);

	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);

	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);
}

static Evas_Object* add_win(const char *name)
{
	Evas_Object *win;

	elm_config_accel_preference_set("opengl");
	win = elm_win_util_standard_add(name, "OpenGL example: Cube");

	if (!win)
		return NULL;

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, rots, 4);
	}

	evas_object_show(win);

	return win;
}

static bool
create_base_gui(appdata_s *ad)
{
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	ad->win = add_win(ad->name);

	if (!ad->win)
		return false;

	create_indicator(ad);
	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	// Create the naviframe
	ad->naviframe = elm_naviframe_add(ad->conform);
	elm_object_content_set(ad->conform, ad->naviframe);

	// Show the naviframe
	evas_object_show(ad->naviframe);

	Evas_Object *table = elm_table_add(ad->naviframe);

	// Create the box
	Evas_Object *box = elm_box_add(table);

	// Set the box vertical
	elm_box_horizontal_set(box, EINA_FALSE);
	// The box expands when its contents need more space
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	// The box fills the available space
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);

	Evas_Object *glview = add_glview(box, ad);
	elm_box_pack_end(box, glview);

	// Show the box
	evas_object_show(box);

	Evas_Object *label_box = elm_box_add(table);
	elm_box_horizontal_set(label_box, EINA_FALSE);
	evas_object_size_hint_weight_set(label_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(label_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(label_box);

	ad->fps_label = elm_label_add(label_box);
	elm_object_text_set(ad->fps_label, "<align=left color=#FFFFFF>FPS</align>");
	evas_object_size_hint_weight_set(ad->fps_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->fps_label, 0.0, 0.0);
	evas_object_show(ad->fps_label);
	elm_box_pack_end(label_box, ad->fps_label);

	elm_table_pack(table, box, 0, 0, 1, 1);
	elm_table_pack(table, label_box, 0, 0, 1, 1);
	evas_object_show(table);

	// Add the box in the naviframe container
	elm_naviframe_item_push(ad->naviframe, "Basic GLES App", NULL, NULL, table, NULL);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

	return true;
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;

	return create_base_gui(ad);
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	ad.name = "basicGLES";

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
