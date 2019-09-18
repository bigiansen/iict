SET(IICT_SOURCES
    src/image.cpp
    src/main.cpp
    src/task_queue.cpp
)

add_executable(iict ${IICT_SOURCES})
target_link_libraries(iict stb strutils)