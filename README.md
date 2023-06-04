# Chunk_Types

## Summary

This is a repository that aims to implement an expandable set of generic data models that may be used in a variety of ```c++``` applications. 
The intention is that these may be functional across multiple platforms including Windows, Linux and Embedded Systems 
(specifically the [ESP32](https://www.espressif.com/en/products/socs/esp32)). With this in mind,
the repository aims to be as light as possible in terms of using other libraries that may not be cross compatible.

## Code Description

Each data model is defined in the ```include``` folder, implemented in the base level directory and is tested within the ```tests``` directory.
Data models types are defined with some utility functions in in the [ChunkTypesUtility.h](https://github.com/Sense-Scape/Chunk_Types/blob/main/include/ChunkTypes.h) 
header. Tests are run using [DocTest](https://github.com/doctest/doctest) testing framework.

## Getting Started

One should first pull this repository and update the submodules as it does required the DocTest header to build. 
The Doctest library has been branched into this organisation. **Note** that this is intended to be used a library.

### Windows

- One should have [Visual Studio 2022 downloaded](https://visualstudio.microsoft.com/vs/)
- Ensure this repository is pulled
- Open the solution file denoted by the ```.sln```
- Run the build command
- One should get an executable test file as well as a `.lib` file

### ESP32

- Ensure one has [VSCode](https://code.visualstudio.com/download) downloaded
- Download ESP-IDF (V5.0)
- Once downloaded, open the ESP-IDF terminal and run the ```code``` command, VSCode should open, you may make adjustments as you please
- Navigate to the folder contain this code and run the ```idf.py build``` command
- This should build the code for the ESP32

### Linux

There is currently no support for linux but there is an intention to add it when required.
