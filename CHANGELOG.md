# Changelog

This changelog records notable changes to the project, including new features, bug fixes, and updates. It follows Semantic Versioning.

Entries are organized by version and date, with changes grouped under categories such as Added, Changed, Fixed, Deprecated, and Removed.

## [2.0.1] - 2025-06-08

### Added
- Added documentation for the missing function

## [2.0.0] - 2025-06-05

### Added
- Introduced a `Class` struct to support object-oriented programming patterns in C (widgets only)
- Added a `Widget` struct as the foundational base for all widgets
- Introduced `Button` widget struct as the first concrete widget type
- Added ability to specify a source rectangle (`SDL_Rect`) when creating buttons to control which part of the texture is rendered via `Menu_draw`

### Fixed
- Refactored `Menu` struct to hide internal data behind an opaque pointer
- Added `NULL` pointer validation for the `color` parameter in `Text_set_color`

## [1.1.1] - 2025-06-02

### Added
- Added functions to customize the menu widget color and the highlight color for the focused menu item
- Added function to set the position of a widget
- Added `CUSTOM` alignment option for menus to allow free positioning of widgets
- Added function to set the menu's alignment that also recalculates and updates the positions of widgets within the menu
- Added  `on_hover` callback method to widget interface to handle hover events
- Added `get_position` function to the widget interface for retrieving the current position of widgets
- Added function to retrieve the current mouse cursor state/position
- Implemented hover behavior for menu and buttons to provide visual feedback on mouse-over (default)
- Add `PinR` macro to check if a point `(x, y)` lies inside a rectangle with origin at top-left and y-axis increasing downwards

### Fixed
- Fixed an issue where an error was incorrectly set when objects were present (non-null), instead of only when they were null
- `Menu_set_position` now recalculates widget positions correctly when the alignment is not set to `CUSTOM`
- `Menu_set_padding` now correctly recalculates the menu height
- orrected hash function to return 1 on collision instead of 0, ensuring accurate collision detection

## [1.1.0] - 2025-05-

### Added
- A header file that contains escape sequences for color output
- A simple error handling mechanism
- Default `SDL_image` module initialization
- Simple error handling mechanism

### Fixed
- A bug with unrecognized characters in the name of the filepath in `take_screenshot` function

## [1.0.0] - 2025-05-09

### Added
- Functionality for testing the existence of a file or directory
- A `Start` function for initializing the framework and underlying systems it relies on
- `App_init` reads configuration from a file now

## [0.11.0] - 2025-05-01 Resource Manager Update

### Added
- A simple resource manager based on a hash table for in-game resource storage

## [0.10.0] - 2025-05-01 State Update

### Added
- A `State` object descriptor
- The application can **set** and **retrieve** its current state
- A `<Start.h>` header file that contains most of the framework systems

### Fixed
- Callback functions now require a list of variadic arguments

## [0.9.0] - 2025-04-30

### Added
- A `Button` widget can support a callback function

## [0.8.0] - 2025-04-29

### Added
- A basic `Menu` object with initial functionality such as rendering and updating
- A basic widget system represented by a `Widget` object
- A **Button** `Widget` that is a label a user can interact with (*in development*)
- A `Window` object can return the underlying `SDL_Window` object now

## [0.7.0] - 2025-04-25

### Added
- Add application struct (`App`) to encapsulate SDL window, renderer, and timing state
- An example on using app

## [0.6.0] - 2025-04-23

### Added
- A basic mechanism for handling input

## [0.5.0] - 2025-04-21

### Added
- A `Vector2` addition and subtraction

## [0.4.0] - 2025-04-21

### Added
- A `Vector2` object with initial functionality: 
  - *multiplication by a scalar*
  - *division by a scalar*
  - *vector negation*
  - *vector normalization*
  - *finding the vector's magnitude*

## [0.3.0] - 2025-04-14

### Added
- A `Text` object with initial functionality

### Changed
- A `Texture` object is exposed now

## [0.2.0] - 2025-04-13

### Added
- A `Texture` object with initial functionality

### Fixed
- Makefiles in examples are configured to support compilation on MacOS, a Unix-based system

## [0.1.0] - 2025-04-10

### Added
- A `Window` object with initial functionality
- A `Clock` object with intial functionality
- Examples for using both `Window` and `Clock` objects
