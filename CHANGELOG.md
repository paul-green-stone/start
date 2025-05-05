# Changelog

This changelog records notable changes to the project, including new features, bug fixes, and updates. It follows Semantic Versioning.

Entries are organized by version and date, with changes grouped under categories such as Added, Changed, Fixed, Deprecated, and Removed.

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
