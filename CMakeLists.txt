cmake_minimum_required(VERSION 3.27.1)
project(Shooting VERSION 0.1.0 LANGUAGES CXX)

# Aggiunta dei file .cpp delle librerie
set(SOURCES
    include/bullet/bullet.cpp
    include/character/character.cpp
    include/enemy/enemy.cpp
    include/lifeBar/lifeBar.cpp
    include/object/object.cpp
    include/sottoprogrammi/sottoprogrammi.cpp
    include/text/text.cpp
)

# Aggiunta dei file header delle librerie
set(HEADERS
    include/bullet/bullet.hpp
    include/character/character.hpp
    include/enemy/enemy.hpp
    include/lifeBar/lifeBar.hpp
    include/object/object.hpp
    include/constants/constants.hpp
    include/sottoprogrammi/sottoprogrammi.hpp
    include/text/text.hpp
)

# Trova la libreria SDL2
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/include/sdl/lib/cmake/SDL2)
find_package(SDL2 REQUIRED)

# Trova la libreria SDL2_ttf
find_package(SDL2_ttf REQUIRED PATHS ${CMAKE_SOURCE_DIR}/include/sdl/lib/cmake/SDL2_ttf)

# Trova la libreria SDL2_mixer
find_package(SDL2_mixer REQUIRED PATHS ${CMAKE_SOURCE_DIR}/include/sdl/lib/cmake/SDL2_mixer)

# Trova la libreria SDL2_image
find_package(SDL2_image REQUIRED PATHS ${CMAKE_SOURCE_DIR}/include/sdl/lib/cmake/SDL2_image)

# Aggiunge l'eseguibile
add_executable(Shooting main.cpp ${SOURCES} ${HEADERS})

# Collega l'eseguibile alle librerie trovate
target_link_libraries(Shooting PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image)

# Copia i file DLL dalla directory ./include/sdl/bin nella directory dell'eseguibile durante la fase di build
add_custom_target(CopyDLLs ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/include/sdl/bin"
        $<TARGET_FILE_DIR:Shooting>
    COMMENT "Copying DLLs to the build directory"
)

# Collega la copia dei DLL come dipendenza dell'eseguibile
add_dependencies(Shooting CopyDLLs)

# Aggiungi le directory degli header
include_directories(
    "${PROJECT_SOURCE_DIR}/include/bullet"
    "${PROJECT_SOURCE_DIR}/include/enemy"
    "${PROJECT_SOURCE_DIR}/include/character"
    "${PROJECT_SOURCE_DIR}/include/lifeBar"
    "${PROJECT_SOURCE_DIR}/include/object"
    "${PROJECT_SOURCE_DIR}/include/constants"
    "${PROJECT_SOURCE_DIR}/include/sottoprogrammi"
    "${PROJECT_SOURCE_DIR}/include/text"
)

# Configura il file MakeDocumentation.in
configure_file(MakeDocumentation ${CMAKE_CURRENT_BINARY_DIR}/MakeDocumentation @ONLY)

# Aggiungi un target personalizzato per generare la documentazione con Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(DoxygenDocumentation
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/MakeDocumentation
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
    add_dependencies(Shooting DoxygenDocumentation)
endif()