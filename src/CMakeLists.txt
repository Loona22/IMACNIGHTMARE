file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

set(OUTPUT "Projet")
add_executable(${OUTPUT} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
