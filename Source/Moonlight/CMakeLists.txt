#======================================================================#
#==============================# Target #==============================#
#======================================================================#

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${TARGET_NAME})
add_executable(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

#=======================#
#=====# Libraries #=====#
#=======================#

target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})

#=====================#
#=====# Sources #=====#
#=====================#

file(GLOB_RECURSE TARGET_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE_FILES})
target_sources(${TARGET_NAME} PRIVATE ${TARGET_HEADER_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_HEADER_FILES})

#=====================#
#=====# Install #=====#
#=====================#

install(
	TARGETS ${TARGET_NAME}
	EXPORT ProgramTargets
	COMPONENT Program
)
