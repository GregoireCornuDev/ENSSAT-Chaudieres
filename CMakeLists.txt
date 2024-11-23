cmake_minimum_required(VERSION 3.10)
project(MyApplication C)

# Rechercher SDL2
find_package(SDL2 REQUIRED)

# Rechercher SDL2_image
find_package(SDL2_image REQUIRED)

# Ajouter tous les fichiers source
set(SOURCES
        src/main.c
        src/control_panel/control_panel_gui.c
        src/water_tank/thread_water_level.c
        src/water_tank/water_valve.c
        src/control_panel/control_panel_gui.h
        src/control_panel/control_panel_gui.c
        src/control_panel/control_panel_config.h
        src/control_panel/control_panel_config.c
)

# Créer l'exécutable
add_executable(MyApplication ${SOURCES})

# Inclure les répertoires d'en-têtes pour SDL2 et SDL2_image
target_include_directories(MyApplication PRIVATE
        ${SDL2_INCLUDE_DIRS}            # Inclure SDL2
        ${SDL2_IMAGE_INCLUDE_DIRS}      # Inclure SDL2_image
        ${CMAKE_CURRENT_SOURCE_DIR}/src/control_panel  # Inclure control_panel
        ${CMAKE_CURRENT_SOURCE_DIR}/src/water_tank    # Inclure water_tank
)

# Lier les bibliothèques nécessaires à l'exécutable
target_link_libraries(MyApplication PRIVATE
        SDL2::SDL2                    # Lier SDL2
        SDL2_image::SDL2_image        # Lier SDL2_image
)
