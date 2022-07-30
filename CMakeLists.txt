cmake_minimum_required(VERSION 3.23)

#========================================================================#
#==============================# Metadata #==============================#
#========================================================================#

file(READ "${CMAKE_CURRENT_LIST_DIR}/package.json" PACKAGE_JSON)
string(JSON PACKAGE_DESCRIPTION GET ${PACKAGE_JSON} "description")
string(JSON PACKAGE_HOMEPAGE GET ${PACKAGE_JSON} "homepage")
string(JSON PACKAGE_VERSION GET ${PACKAGE_JSON} "version")

project("Starlight"
	DESCRIPTION ${PACKAGE_DESCRIPTION}
	HOMEPAGE_URL ${PACKAGE_HOMEPAGE}
	VERSION ${PACKAGE_VERSION}
)

#===========================#
#=====# Configuration #=====#
#===========================#

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(CMAKE_FOLDER "Source")
add_subdirectory(Source/Runtime)
add_subdirectory(Source/Program)

#=======================================================================#
#==============================# Install #==============================#
#=======================================================================#

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT CMAKE_INSTALL_EXPORTDIR)
	set(CMAKE_INSTALL_EXPORTDIR "" CACHE STRING "Project export files (DATAROOTDIR/cmake/PROJECT_NAME)")
	set(CMAKE_INSTALL_EXPORTDIR "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
	mark_as_advanced(CMAKE_INSTALL_EXPORTDIR)
endif (NOT CMAKE_INSTALL_EXPORTDIR)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/CMake/PackageConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion
)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
	COMPONENT Development
)

install(EXPORT
	"${PROJECT_NAME}Targets"
	DESTINATION ${CMAKE_INSTALL_EXPORTDIR}
	NAMESPACE ${PROJECT_NAME}::
	COMPONENT Development
)

export(EXPORT
	"${PROJECT_NAME}Targets"
	NAMESPACE ${PROJECT_NAME}::
)

#=====================#
#=====# License #=====#
#=====================#

if (NOT CMAKE_INSTALL_LICENSEDIR)
	set(CMAKE_INSTALL_LICENSEDIR "" CACHE STRING "Project license files (DATAROOTDIR/licenses/PROJECT_NAME)")
	set(CMAKE_INSTALL_LICENSEDIR "${CMAKE_INSTALL_DATAROOTDIR}/licenses/${PROJECT_NAME}")
	mark_as_advanced(CMAKE_INSTALL_LICENSEDIR)
endif (NOT CMAKE_INSTALL_LICENSEDIR)

install(FILES
	"${PROJECT_SOURCE_DIR}/LICENSE.txt"
	DESTINATION ${CMAKE_INSTALL_LICENSEDIR}
)
