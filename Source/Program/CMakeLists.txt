get_filename_component(TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TARGET_NAME})
add_executable(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

#=====================#
#=====# Sources #=====#
#=====================#

file(GLOB_RECURSE TARGET_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.hpp")

target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE_FILES})
target_sources(${TARGET_NAME} PRIVATE ${TARGET_HEADER_FILES})

# File grouping in IDEs
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TARGET_HEADER_FILES})

#========================#
#=====# Properties #=====#
#========================#

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Language standard & features
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

# Rename the output to PROJECT_NAME
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

#==========================#
#=====# Dependencies #=====#
#==========================#

target_link_libraries(${TARGET_NAME} PRIVATE "${PROJECT_NAME}::Runtime")

#=====================#
#=====# Install #=====#
#=====================#

include(GNUInstallDirs)

install(TARGETS
	${TARGET_NAME}
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT Application
)
