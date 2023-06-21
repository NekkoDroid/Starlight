cmake_minimum_required(VERSION 3.25)

#=======================================================================#
#==============================# Project #==============================#
#=======================================================================#

project(
	Starlight
	VERSION "0.1.0"
	DESCRIPTION "Cross-platform real-time 3D game engine"
	HOMEPAGE_URL "https://github.com/NekkoDroid/Starlight"
	LANGUAGES CXX
)

#=====================#
#=====# Targets #=====#
#=====================#

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER CMake)

set(CMAKE_FOLDER Source)
add_subdirectory(Source/Starlight)
add_subdirectory(Source/Moonlight)

#====================#
#=====# Export #=====#
#====================#

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT CMAKE_INSTALL_EXPORTDIR)
	set(CMAKE_INSTALL_EXPORTDIR "" CACHE STRING "Project export files (DATAROOTDIR/cmake/PROJECT_NAME)")
	set(CMAKE_INSTALL_EXPORTDIR "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
	mark_as_advanced(CMAKE_INSTALL_EXPORTDIR)
endif ()

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/CMake/PackageConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	COMPATIBILITY ExactVersion
)

install(
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
	COMPONENT Starlight
)

install(
	EXPORT LibraryTargets
	COMPONENT Library
	DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
	NAMESPACE ${PROJECT_NAME}::
)

install(
	EXPORT ProgramTargets
	COMPONENT Program
	DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
	NAMESPACE ${PROJECT_NAME}::
)

#=====================#
#=====# License #=====#
#=====================#

if (NOT CMAKE_INSTALL_LICENSEDIR)
	set(CMAKE_INSTALL_LICENSEDIR "" CACHE STRING "Project license files (DATAROOTDIR/licenses/PROJECT_NAME)")
	set(CMAKE_INSTALL_LICENSEDIR "${CMAKE_INSTALL_DATAROOTDIR}/licenses/${PROJECT_NAME}")
	mark_as_advanced(CMAKE_INSTALL_LICENSEDIR)
endif ()

install(
	FILES "${PROJECT_SOURCE_DIR}/LICENSE.txt"
	DESTINATION ${CMAKE_INSTALL_LICENSEDIR}
)
