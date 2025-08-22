#ifndef _START_ANIMATION_H
#define _START_ANIMATION_H

#include "Texture.h"

/* ================================================================ */

typedef enum { X, Y } AnimationAxis;

typedef struct animation {

    Texture* texture;

    /* A time interval at which an animation should be updated */
    double speed;
    double last_time_updated;

    /* The number of frames an animation has */
    unsigned int num_frames;
    int current_frame;

    /* ================================================================ */
    /* ======== A sprite atlas is usually an image containing ========= */
    /* =========== sets of sprites for a particular action. =========== */
    /* ============= In this context, the X and Y offsets ============= */
    /* ===== define the number of pixels from the top-left corner ===== */
    /* ======== of the sprite atlas to the top-left corner of ========= */
    /* =============== the first frame of the animation =============== */
    /* ================================================================ */

    int x_offset;
    int y_offset;

    /* Sprite width */
    int s_width;
    /* Sprite height */
    int s_height;

    /* 
        The orientation of the sprite animation changes,
        with `X` representing horizontal alignment
        and `Y` representing vertical alignment
    */
    AnimationAxis axis;

    SDL_Rect frame;
} Animation;

/* ================================================================ */

/**
 * Create a new animation from the given texture.
 * 
 * @param t Texture/image (usually a sprite sheet) containig desired frames of the animation
 * @param x_offset Horizontal offset. In case the image is the sprite atlas
 * @param y_offset Vertical offset
 * @param num_frames Number of frames of the animation
 * @param width Width of a single frame (sprite)
 * @param height Height og a single frame (sprite)
 * @param axis The order of frames alignment (`X` for horizontal, `Y` for vertical)
 * 
 * @return Returns the `Animation` that was created or NULL on failure.
 */
Animation* Animation_new(Texture* t, int x_offset, int y_offset, int num_frames, int width, int height, AnimationAxis axis);

/**
 * Destroy the animation. The function doesn't destroy the texture associated with it, call `Texture_destroy` instead.
 * 
 * @param animation animation to destroy (`&animation`)
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Animation_destroy(Animation** animation);

/**
 * Update the current animation frame based on the time passed.
 * 
 * @param animation animation to update
 * @param delta_time time passed since the last frame (for example)
 * 
 * @return None.
 */
void Animation_update(Animation* animation, double delta_time);

/**
 * Set the speed of the animation.
 * 
 * @param animation
 * @param speed new speed of the animation
 * 
 * @return None.
 */
void Animation_setSpeed(Animation* animation, double speed);

/* ================================================================ */

#endif /* _START_ANIMATION_H */

