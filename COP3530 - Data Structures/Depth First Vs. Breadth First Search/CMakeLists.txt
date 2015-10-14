cmake_minimum_required(VERSION 3.1)
project(Assignment_7)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES main.c)
add_executable(Assignment_7 ${SOURCE_FILES} graph.h depthFirstSearch.c stackPush.c stackPop.c stackPeek.c queueInsert.c queueGetFront.c breadthFirstSearch.c queuePeekFront.c topoSort.c createAdjList.c)