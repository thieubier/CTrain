cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Définir le répertoire de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Inclure SFML en tant que dépendance via FetchContent
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Ajouter les fichiers sources
add_executable(TrainSimulation
        src/main.cpp
        src/rail/Rail.cpp
        src/rail/Switch.cpp
        src/train/Train.cpp
        src/scenes/Cloud.cpp
        src/scenes/Cursor.cpp
        src/scenes/Legend.cpp
        src/settings/Globals.cpp
        src/scenes/Crate.cpp
)

target_link_libraries(TrainSimulation PRIVATE sfml-graphics)

target_compile_features(TrainSimulation PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET TrainSimulation
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
            $<TARGET_FILE_DIR:TrainSimulation>
            VERBATIM
    )
endif()
