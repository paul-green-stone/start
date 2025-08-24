#ifndef _START_HEADER_H
#define _START_HEADER_H

/* ================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

#include "Core.h"
#include "Window.h"
#include "Application.h"
#include "Clock.h"
#include "Input.h"
#include "Texture.h"
#include "Text.h"
#include "Manager.h"
#ifndef __EMSCRIPTEN__
#include "File/conf.h"
#endif
#include "File/Color.h"
#include "State/State.h"
#include "Math/Core.h"
#include "Math/Vector2D.h"
#include "Widget/Menu.h"
#include "Widget/Widgets.h"
#include "Widget/Widget.h"
#include "Error.h"
#include "Camera.h"
#include "Animation.h"

#include "Widget/Button/Button.h"
#include "Widget/TextInput/TextInput.h"
#include "Widget/SelectWidget/SelectWidget.h"

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_HEADER_H */
