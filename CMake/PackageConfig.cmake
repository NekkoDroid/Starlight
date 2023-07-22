@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

find_dependency(SDL2)
find_dependency(EnTT)

include("${CMAKE_CURRENT_LIST_DIR}/LibraryTargets.cmake")

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/ProgramTargets.cmake")
	include("${CMAKE_CURRENT_LIST_DIR}/ProgramTargets.cmake")
endif ()

check_required_components(@PROJECT_NAME@)
