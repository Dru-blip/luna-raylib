#include <luna/luna.h>
#include <raylib.h>
#include <stdio.h>
#include "value.h"

static inline Color color_from_value(struct lu_istate* state, struct lu_object* obj) {
    uint8_t r, g, b, a;
    r = lu_as_int(lu_obj_get(obj, lu_intern_string(state, "r")));
    g = lu_as_int(lu_obj_get(obj, lu_intern_string(state, "g")));
    b = lu_as_int(lu_obj_get(obj, lu_intern_string(state, "b")));
    a = lu_as_int(lu_obj_get(obj, lu_intern_string(state, "a")));

    return (Color){r, g, b, a};
}

static struct lu_value color_to_value(struct lu_istate* state, Color color) {
    struct lu_object* obj = lu_object_new(state);
    lu_obj_set(obj, lu_intern_string(state, "r"), lu_value_int(color.r));
    lu_obj_set(obj, lu_intern_string(state, "g"), lu_value_int(color.g));
    lu_obj_set(obj, lu_intern_string(state, "b"), lu_value_int(color.b));
    lu_obj_set(obj, lu_intern_string(state, "a"), lu_value_int(color.a));
    return lu_value_object(obj);
}

LU_NATIVE_FN(rl_init_window) {
    int64_t width, height;
    struct lu_string* title;
    LU_TRY_UNPACK_ARGS(vm, "iis", 3, args, &width, &height, &title);
    InitWindow(width,height,lu_string_get_cstring(title));
    LU_RETURN_NONE();
}

LU_NATIVE_FN(rl_close_window) {
    CloseWindow();
    LU_RETURN_NONE();
}

LU_NATIVE_FN(rl_window_should_close) {
    LU_RETURN_BOOL(WindowShouldClose());
}

LU_NATIVE_FN(rl_begin_drawing) {
    BeginDrawing();

    LU_RETURN_NONE();
}

LU_NATIVE_FN(rl_end_drawing) {
    EndDrawing();
    LU_RETURN_NONE();
}

LU_NATIVE_FN(rl_clear_background) {
    struct lu_object* obj;
    LU_TRY_UNPACK_OBJ(vm, args, 0, &obj);
    ClearBackground(color_from_value(vm->istate, obj));
    LU_RETURN_NONE();
}

LU_EXPORT void lu_module_init(struct lu_istate* state, struct lu_module* module) {
    lu_register_native_fn(state, module, "initWindow", rl_init_window, 3);
    lu_register_native_fn(state, module, "closeWindow", rl_close_window, 0);
    lu_register_native_fn(state, module, "windowShouldClose", rl_window_should_close, 0);

    lu_register_native_fn(state, module, "beginDrawing", rl_begin_drawing, 0);
    lu_register_native_fn(state, module, "endDrawing", rl_end_drawing, 0);
    lu_register_native_fn(state, module, "clearBackground", rl_clear_background, 1);

    lu_obj_set(module, lu_intern_string(state, "WHITE"), color_to_value(state, WHITE));
    lu_obj_set(module, lu_intern_string(state, "ORANGE"), color_to_value(state, ORANGE));
}
