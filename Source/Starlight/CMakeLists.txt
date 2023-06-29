#======================================================================#
#==============================# Target #==============================#
#======================================================================#

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${TARGET_NAME} STATIC)
add_library(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

#=======================#
#=====# Libraries #=====#
#=======================#

find_package(SDL2 REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

#=====================#
#=====# Sources #=====#
#=====================#

file(GLOB_RECURSE TARGET_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE_FILES})
target_sources(${TARGET_NAME} PUBLIC FILE_SET HEADERS FILES ${TARGET_HEADER_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_HEADER_FILES})

#=====================#
#=====# Install #=====#
#=====================#

install(
	TARGETS ${TARGET_NAME}
	EXPORT LibraryTargets
	COMPONENT Library
	FILE_SET HEADERS
)
