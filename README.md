CELLOTRONICUM
=============

Celem projektu jest zaprojektowanie i skonstruowanie rozbudowanego i elastycznego instrumentu wirtualnego, rozumianego jako narzędzie do kompozycji i improwizacji w czasie rzeczywistym w dialogu z instrumentem solowym.


# Building and running

## On Linux

To build, you will need CMake 3.0 or newer, SDL2 and SDL2-ttf development headers. Run:

	mkdir build
	cd build
	cmake ..
	make
	
To launch, you will also need sclang (SuperCollider). Execute [from `build` directory]:

	./algaudio

## On Windows

### Using MSYS2

From MSYS2 shell, use `pacman` to install following packages (for mingw subsystem, also choose an architecture you are compiling for):

	mingw/gcc
	mingw/make
	mingw/SDL2
	mingw/SDL2_ttf
	mingw/cmake
	make
	automake
	pkg-config

Note that even if you have CMake or gcc installed on your host system, you will still need to install them in your MSYS environment.

You can also switch gcc for clang or any other compiler you want to use.

In project directory, run:

	mkdir build
	cd build
	cmake -G "MSYS Makefiles" ..
	make

When ready, run `./algaudio.exe` to launch the application.

### Using other build environment (VisualStudio, Cygwin, others)

The easiest way to build the project using any other build environment and/or compiler is to use the CMake-gui application, which generates build files for common IDEs from source.

Then use your environment of choice to compile the application.

## On other systems

While it was not currently tested, compiling the application on other systems should be also possible, because no platform-specific CMake modules are used. Please refer to CMake documentation for your platform to learn how to generate build files using CMake.

# Deploying

The application needs following directories to be available in the working directory:

	sc
	fonts

However, if you build the application on Windows using MSYS2, you will also want to ship all shared libraries with it, because they are unlikely to be available on the targeted system.

Below is the list of all non-standard shared libraries that you will need to provide in such case with the main application binary. You can find them all in your ./mingwXX/bin directory of your MSYS2 environment.

	libbz2-1.dll
	libfreetype-6.dll
	libgcc_s_seh-1.dll
	libglib-2.0-0.dll
	libharfbuzz-0.dll
	libiconv-2.dll
	libintl-8.dll
	libpng16-16.dll
	libstdc++-6.dll
	libwinpthread-1.dll
	SDL2_ttf.dll
	SDL2.dll
	zlib1.dll
