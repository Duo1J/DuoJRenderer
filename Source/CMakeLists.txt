file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

set(IMGUI_ROOT_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/imgui)
set(IMGUI_SOURCE_FILES
    ${IMGUI_ROOT_DIR}/imgui.cpp
    ${IMGUI_ROOT_DIR}/imgui_draw.cpp
    ${IMGUI_ROOT_DIR}/imgui_tables.cpp
    ${IMGUI_ROOT_DIR}/imgui_widgets.cpp
    ${IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(${TARGET}
    # src
    ${SOURCE_FILES} 
    # imgui
    ${IMGUI_SOURCE_FILES}
    # stb_image
    ${CMAKE_SOURCE_DIR}/ThirdParty/stb_image/stb_image.cpp
)

target_include_directories(${TARGET} PRIVATE
    # src
    ${CMAKE_CURRENT_SOURCE_DIR}
    # glad
    ${CMAKE_SOURCE_DIR}/ThirdParty/glad/include
    # glfw
    ${CMAKE_SOURCE_DIR}/ThirdParty/glfw-3.4/include
    # glm
    ${CMAKE_SOURCE_DIR}/ThirdParty/glm
    # imgui
    ${IMGUI_ROOT_DIR}
    # stb_image
    ${CMAKE_SOURCE_DIR}/ThirdParty/stb_image
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