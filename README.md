# Particle Systems Demo

A small raylib sandbox used to experiment with real-time particle systems.

## What's in this project

| System       | Files                              | Enable                                   | Live-tune                                                     |
|--------------|-------------------------------------|-------------------------------------------|----------------------------------------------------------------|
| `Rain`       | `src/rain.hpp` / `src/rain.cpp`         | `R` toggles rain on/off                    | `Shift+R` toggles config mode, then hold `+`/`-` to change spawn density |
| `Fire`       | `src/fire.hpp` / `src/fire.cpp`         | `F` toggles fire on/off                    | `Shift+F` toggles config mode, then hold `+`/`-` to change spawn density |
| `Explosion`  | `src/explosion.hpp` / `src/explosion.cpp` | Left mouse click spawns an explosion at the cursor | `Shift+E` toggles config mode, then hold `+`/`-` to change particle count |

A few implementation notes, if you're poking around the code:

- **Rain** emits thin streak lines from `y = 0`, falling under gravity, in a soft steel-blue tone.
- **Fire** emits circular embers from the bottom of the screen that rise with a sine-wave wobble on the X axis
  and cycle through a white → yellow → red → gray color gradient as they age, fading out via alpha near the
  end of their life.
- **Explosion** spawns a burst of particles in random directions at high speed from the mouse click position,
  affected by gravity, bouncing (inverting their vertical velocity) off the bottom of the screen, and using
  the same white → yellow → red → gray fade as the embers.
- All three classes use `GetScreenWidth()`/`GetScreenHeight()` instead of cached dimensions, so they stay
  correct if you resize the window (`FLAG_WINDOW_RESIZABLE` is enabled in `main.cpp`).

## Prerequisites

You need three things, on any OS:

1. A **C++23-capable compiler** (GCC 13+, Clang 16+/AppleClang from a recent Xcode, or MSVC from Visual Studio 2026).
2. **CMake 3.15+**
3. **vcpkg**

### Installing CMake

- **Ubuntu**: `sudo apt install cmake`
- **macOS**: `brew install cmake` (Homebrew), or the official installer from [cmake.org/download](https://cmake.org/download/).
- **Windows**: the Visual Studio 2026 installer can provision CMake for you under the "Desktop development with C++" workload

### Installing vcpkg

vcpkg is just a git clone plus a bootstrap script:

**Linux / macOS**
```sh
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=~/vcpkg
echo 'export VCPKG_ROOT=~/vcpkg' >> ~/.bashrc   # or ~/.zshrc if that what you use
```

**Windows (PowerShell)**
```powershell
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
setx VCPKG_ROOT C:\vcpkg
```
(`setx` persists the variable for future shells; restart your terminal/IDE
after running it.)

`VCPKG_ROOT` is what `CMakePresets.json` reads
(`$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake`) to locate vcpkg's CMake
toolchain file, so it must be set before you configure the project.

## Building

From the repository root, with `VCPKG_ROOT` set:

```sh
cmake --preset default
cmake --build build --config Release
```

The first `configure` will compile `raylib`/`glfw3` from source via vcpkg,
which can take a few minutes. Subsequent configures reuse the cached
install.

### Running

- **Linux / macOS (single-config generator, the default)**:
  `./build/particle_system`
- **Windows (Visual Studio generator, the default if no Ninja is on PATH)**:
  `.\build\Release\particle_system.exe` (or `.\build\Debug\...` if you built
  without `--config Release`)
- **Windows/Linux/macOS with Ninja** (`cmake --preset default -G Ninja`):
  `./build/particle_system` / `.\build\particle_system.exe`

### Running natively from Visual Studio 2026 (`Ctrl+F5`)

Visual Studio 2026 can open this repo directly via its built-in CMake
integration (no `.sln` file needed) and run the game with `Ctrl+F5`
(Start Without Debugging). Beyond having CMake installed, a few one-time
setup steps are required:

1. **Install the right workload.** In the Visual Studio Installer, make sure
   the "Desktop development with C++" workload is checked, including the
   "C++ CMake tools for Windows" component.
2. **Set `VCPKG_ROOT` as a system environment variable**, not just in a
   terminal session:
   ```powershell
   git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
   C:\vcpkg\bootstrap-vcpkg.bat
   setx VCPKG_ROOT C:\vcpkg
   ```
   Then **close and reopen Visual Studio**, it only picks up environment
   variables that were set before it launched.
3. **Open the folder, not a solution.** Use `File > Open > Folder...` and
   point it at the repository root. Visual Studio detects `CMakeLists.txt`
   and `CMakePresets.json` automatically and configures the project.
4. **Select the `default` preset** from the configuration dropdown near the
   top toolbar (next to the Run button). It comes from `CMakePresets.json`.
5. **Set the startup item.** By default Visual Studio's CMake integration
   doesn't know which target `Ctrl+F5` should launch. Switch Solution
   Explorer to "CMake Targets View", right-click `particle_system.exe`, and
   choose **"Set as Startup Item"**. Without this, `Ctrl+F5` is greyed out or
   runs the wrong target.
6. **Be patient on first configure.** vcpkg compiles `raylib` and `glfw`
   from source the first time CMake configures, this can take a few
   minutes.

### Troubleshooting (Visual Studio)

#### Forcing a reconfigure

If you suspect the CMake configuration is stale or broken (e.g. you changed
`VCPKG_ROOT`, edited `CMakeLists.txt`/`CMakePresets.json`, or things just
seem out of sync), force a clean reconfigure instead of guessing:

- `Project` (or `CMake`) `> Delete Cache and Reconfigure` — wipes the CMake cache and reruns
  configure from scratch. This is the usual fix.
- Right-click `CMakeLists.txt` in Solution Explorer `> Configure particle_system` to just
  rerun configure without deleting the cache.
- As a last resort, close Visual Studio and delete the build output folder by hand
  (`build/` per this project's preset, or `out/build/<preset>/` if your Visual Studio version
  defaulted to its own location), then reopen the folder.
  Note this also wipes `vcpkg_installed/`, so the next configure will recompile `raylib`/`glfw`
  from source again (a few minutes).

Check the **Output** window with the dropdown set to `CMake` to confirm configure actually
succeeded (look for `CMake generation finished` with no red/error text) before moving on.

#### "Target missing executable" when running with `Ctrl+F5`

This shows up when configure finished cleanly (no errors in the `CMake` Output pane) but the
Startup Item still can't find an actual `.exe` on disk.

The cause is almost always that **configure succeeded, but the project was
never actually built**.

A clean "CMake generation finished" message only means the build files (Ninja/Makefiles)
were generated, not that `particle_system.exe` was compiled.

Fix:

1. Explicitly build the project first: `Build > Build All` (or `Ctrl+Shift+B`), **before** trying to run it.
2. Check the **Output** window with the dropdown set to `Build` (a different pane from the `CMake` one)
   for compile/link errors, these are what actually prevent the executable from being produced,
   even when configure looked fine.
3. Confirm `particle_system.exe` exists on disk afterwards, in `build\` (or `out\build\<preset>\` if
   that's where your Visual Studio put it).
4. If it still shows "missing executable" after a successful build, re-set the startup item
   (CMake Targets View → right-click `particle_system.exe` → "Set as Startup Item" again)
   the dropdown can cache a stale target list from before the build finished.

## What are CMake and vcpkg, and why do they matter here?

If you're new to C++, it might seem odd that building this project takes two
extra tools instead of just hitting "Run". Here's the short version of why
they exist.

C++ doesn't have one single, built-in way to turn source code into a
program, unlike some other languages, there's no one official compiler or
build command.

Different operating systems come with different compilers, and projects need
a consistent way to tell any of them "here's what to build."

**CMake** is that layer: you describe your project once (in `CMakeLists.txt`),
and CMake figures out the right instructions for whatever
compiler and build tool is available on your machine.

On Visua Studio it generates a project under the hood on Windows, or Makefiles
on Ubuntu, for example. You never have to write separate build scripts per OS.

The second problem is external libraries. This project uses `raylib`, but C++
has no built-in way to download and install libraries like, say, `npm` does
for JavaScript or `pip` does for Python.

Normally you'd have to manually find, download, and compile `raylib` yourself,
on every machine, for every OS.

**vcpkg** is a package manager for C++: you just list what you need in `vcpkg.json`,
and it downloads and builds the library for you, automatically, the first time
you configure the project.

So long story short:
- CMake handles *"how do I build this on this machine"*
- vcpkg handles *"how do I get the libraries this needs"*

And because both tools abstract away the OS-specific details, the exact same
three files (`CMakeLists.txt`, `CMakePresets.json`, `vcpkg.json`) work unmodified
on Ubuntu, Windows, or macOS.
