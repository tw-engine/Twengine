cmake_minimum_required(VERSION 3.27)
project(TwengineDemo)

# Output dir for the library
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# All engine source files
file(GLOB_RECURSE SRC src/*.cpp)

# Creates the library from the sources
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/lib/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE Twengine glfw)

if(BUILD_SHADERS)
    set(SHADER_DIR ${CMAKE_SOURCE_DIR}/engine/shaders)

    file(GLOB_RECURSE SHADER_SOURCES
            "${SHADER_DIR}/*.vert"
            "${SHADER_DIR}/*.frag"
    )

    set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/shaders)

    file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

    foreach(SHADER_SOURCE ${SHADER_SOURCES})
        get_filename_component(SHADER_NAME ${SHADER_SOURCE} NAME)
        set(SHADER_OUTPUT ${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv)

        add_custom_command(
                OUTPUT ${SHADER_OUTPUT}
                COMMAND glslc ${SHADER_SOURCE} -o ${SHADER_OUTPUT}
                DEPENDS ${SHADER_SOURCE}
                COMMENT "Compiling ${SHADER_NAME}"
        )

        list(APPEND SHADER_OUTPUTS ${SHADER_OUTPUT})
    endforeach()

    add_custom_target(
            Shaders
            DEPENDS ${SHADER_OUTPUTS}
    )

    add_dependencies(${PROJECT_NAME} Shaders)
endif()

if(RUN_AFTER_BUILD)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${PROJECT_NAME}
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMENT "Running ${PROJECT_NAME} from ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
endif()
