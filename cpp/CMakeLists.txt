find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_definitions(
	--std=c++11
#	-Wall
#	-Wextra
	-g
)


link_directories(
	${SDL2_LIBRARY_DIR}
	${SDL2_TTF_LIBRARY_DIR}
)

include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
)


file(GLOB SOURCES ./*.cpp)

add_executable(
	algaudio
	${SOURCES}
)

target_link_libraries(
	algaudio
	${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
)

add_custom_command(
	TARGET algaudio POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/algaudio${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_BINARY_DIR}/"
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/sc" "${CMAKE_BINARY_DIR}/sc"
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/fonts" "${CMAKE_BINARY_DIR}/fonts"
)

install(
	TARGETS algaudio
	RUNTIME DESTINATION bin
)
