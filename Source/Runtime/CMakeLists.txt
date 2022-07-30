get_filename_component(TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_library(${TARGET_NAME})
add_library(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

#=====================#
#=====# Sources #=====#
#=====================#

file(GLOB_RECURSE TARGET_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.hpp")

target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE_FILES})
target_sources(${TARGET_NAME} PUBLIC FILE_SET HEADERS FILES ${TARGET_HEADER_FILES})

# File grouping in IDEs
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TARGET_HEADER_FILES})

#========================#
#=====# Properties #=====#
#========================#

target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

# Language standard & features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

# Export all symbols on Windows (default on Unix)
set_target_properties(${TARGET_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# Rename the output to PROJECT_NAME
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

#==========================#
#=====# Dependencies #=====#
#==========================#

find_package(SDL2 REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE "SDL2::SDL2")

find_package(fmt REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC "fmt::fmt")

#=====================#
#=====# Install #=====#
#=====================#

include(GNUInstallDirs)

install(TARGETS
	${TARGET_NAME}
	EXPORT "${PROJECT_NAME}Targets"
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT Runtime
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Runtime
		NAMELINK_COMPONENT Development
	ARCHIVE
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT Development
	FILE_SET HEADERS
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		COMPONENT Development
	INCLUDES
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
