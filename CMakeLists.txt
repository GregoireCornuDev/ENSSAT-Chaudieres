cmake_minimum_required(VERSION 3.10)
project(MyApplication C)

# Rechercher SDL2
find_package(SDL2 REQUIRED)

# Rechercher SDL2_image
find_package(SDL2_image REQUIRED)

# Ajouter tous les fichiers source
set(SOURCES
        src/main.c
        src/threads_manager.c
        src/water_tank/water_tank_manager.c
        src/water_tank/water_tank_simulation.c
        src/fuel_tank/fuel_tank_manager.c
        src/fuel_tank/fuel_tank_simulation.c
        src/control_panel/control_panel_gui.c
        src/control_panel/control_panel_config.c
        src/control_panel/control_panel_gauge.c
        src/central_manager/central_manager.c
        src/pipes_manager.c
        src/central_manager/values_average.c
        src/control_panel/control_panel_manager.c
        src/tests/tests_pipes.c
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
