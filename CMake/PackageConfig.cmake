@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

find_dependency(SDL2)
find_dependency(fmt)

include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake")

check_required_components(@PROJECT_NAME@)
