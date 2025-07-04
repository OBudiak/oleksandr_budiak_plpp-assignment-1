cmake_minimum_required(VERSION 3.15)
project(text_editor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_subdirectory(
        "${CMAKE_SOURCE_DIR}/../CezarCrypting"
        "${CMAKE_BINARY_DIR}/CezarCrypting-build"
)

add_executable(text_editor
        main.cpp
        src/editing_text.cpp
        src/functionality.cpp
)

target_include_directories(text_editor PRIVATE
        "${CMAKE_SOURCE_DIR}/../CezarCrypting/include"
)

target_link_libraries(text_editor PRIVATE MyDll)

add_custom_command(TARGET text_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/CezarCrypting-build/mylib.dll"
        $<TARGET_FILE_DIR:text_editor>
)
