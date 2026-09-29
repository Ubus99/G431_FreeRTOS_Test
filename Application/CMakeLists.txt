target_sources(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/common/scpi-def.c
        ${CMAKE_CURRENT_LIST_DIR}/common/scpi-def.h
        ${CMAKE_CURRENT_LIST_DIR}/tasks/COM_Task.c
        ${CMAKE_CURRENT_LIST_DIR}/tasks/COM_Task.h
        ${CMAKE_CURRENT_LIST_DIR}/tasks/scpi_Task.c
        ${CMAKE_CURRENT_LIST_DIR}/tasks/scpi_Task.h
        ${CMAKE_CURRENT_LIST_DIR}/osDefinitions.h
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/common
        ${CMAKE_CURRENT_LIST_DIR}/tasks
)