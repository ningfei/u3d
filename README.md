This is a fork of ningfei/u3d which is a fork of the v1.4.5 U3D library. It has been updated to support x86 and x64 Windows (VS2008, VS2010, VS2015), Linux and OS X.

See here for an conda package: https://github.com/conda-forge/u3d-feedstock

# Build scripts

Below are the build scripts used to compile and install the U3D library.

Set `U3D_SHARED=OFF` to use the packaged `libpng`, `jpeg` and `zlib` libraries, or on to use system installed.

## Windows

Confirmed to work for x86 and x64; VS2008, VS2010 and VS2015. Set `%LIBRARY_PREFIX%` to the target installation directory.

```batch
set BUILD_CONFIG=Release

mkdir build
cd build

cmake .. -G "NMake Makefiles" ^
    -Wno-dev ^
    -DCMAKE_BUILD_TYPE=%BUILD_CONFIG% ^
    -DCMAKE_INSTALL_PREFIX="%LIBRARY_PREFIX%" ^
    -DU3D_SHARED:BOOL=ON
if errorlevel 1 exit 1

nmake install
if errorlevel 1 exit 1
```

## Unix

Confirmed to work for x86 and x64 Linux and x64 OS X. Set `$PREFIX` to the target installation directory.

```bash
#!/usr/bin/env bash
BUILD_CONFIG=Release

mkdir build
cd build

cmake .. -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=$BUILD_CONFIG \
    -DCMAKE_INSTALL_PREFIX=$PREFIX \
    -DU3D_SHARED:BOOL=ON

make install
```

# Original Readme

U3D is a format for 3D models that can be embedded into PDF and viewed in Adobe Acrobat/Reader 
(but not other PDF viewers).
There is a C++ library to produce U3D files and a converter from IDTF, a verbose text format.

You need libpng (http://www.libpng.org/), jpeg library (http://www.ijg.org/) and zlib (http://www.zlib.net/)
installed to compile U3D lib using autotools.

The cmake build uses bundled versions of the above tools.

This is just a port of Intel U3D library to the GNU Build System and cmake,
with rendering part thrown out.

There is not much to read in this readme since I guess there is not too many potential readers.

You may contact me, Michail Vidiassov, by Internet e-mail master@iaas.msu.ru.
That will make me describe my changes in more detail or apply some minor fixes you desire.
But the proper place to discuss things is the U3D software forum at sourceforge.
You can also find the Intel source there, only the main part is preserved in this distribution.

I have made the following changes - all quality factors are set to maximum quality by default,
thus supressing compression.
To IDTF I have added one more parameter - TEXTURE_LAYER_REPEAT: "UV", "U", "V" or "NONE",
with "UV" being default. The name says what it does.

I have also dissected IDTFConverter and made a library from the converter part
(discarding IDTF file parser), it can be used to eliminate intermediate IDTF files that
may be really lengthy and slow to create and than parse with IDTFConverter.

"History of the U3D File Format" at http://www.okino.com/conv/imp_u3d.htm is a good read on what U3D is and where it comes from.
