#include "../include/Animation.h"
#include "../include/Error.h"

/* ================================================================ */

Animation* Animation_new(Texture* t, int x_offset, int y_offset, int num_frames, int width, int height, AnimationAxis axis) {

    Animation* a = NULL;
    /* ======== */

    if ((a = calloc(1, sizeof(Animation))) == NULL) {
        return NULL;
    }

    a->texture = t;
    a->num_frames = num_frames;
    a->s_width = width;
    a->s_height = height;
    a->x_offset = x_offset;
    a->y_offset = y_offset;
    a->axis = axis;

    a->frame = (SDL_Rect) {a->x_offset, a->y_offset, a->s_width, a->s_width};

    /* ======== */
    return a;
}

/* ================================================================ */

int Animation_destroy(Animation** animation) {

    if ((animation == NULL) || (*animation == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    free(*animation);
    *animation = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

void Animation_update(Animation* animation, double delta_time) {

    animation->last_time_updated += delta_time;

    if (animation->last_time_updated >= animation->speed) {

        animation->current_frame = (animation->current_frame + 1) % animation->num_frames;

        animation->frame.x = (animation->axis == X) ? animation->current_frame * animation->s_width + animation->x_offset : animation->x_offset;
        animation->frame.y = (animation->axis == Y) ? animation->current_frame * animation->s_height + animation->y_offset : animation->y_offset;
        
        animation->last_time_updated = 0;
    }
}

/* ================================================================ */

void Animation_setSpeed(Animation* animation, double speed) {
    animation->speed = speed;
}

/* ================================================================ */
