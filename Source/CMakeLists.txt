file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${TARGET} ${SOURCE_FILES})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/glad/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/glfw-3.4/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/glm
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui
)

target_link_libraries(${TARGET} PRIVATE
    glad
    glfw
)

if(WIN32)
    target_link_libraries(${TARGET} PRIVATE
        opengl32
    )
endif()