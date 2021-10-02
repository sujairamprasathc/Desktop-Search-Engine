cmake_minimum_required(VERSION 3.1)

# Set the project name
project(Desktop-Search-Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add libraries used
link_libraries(stdc++fs)

# Text Crawler
add_executable(text-crawler Text-Crawler/main.cpp)

# Indexer
add_library(DocumentIDManager.o Indexer/DocumentIDManager.cpp)
add_library(FileConstants.o Indexer/FileConstants.cpp)
add_library(Indexer.o Indexer/Indexer.cpp)
target_link_libraries(Indexer.o DocumentIDManager.o)
add_library(hash.o Indexer/hash.cpp)
add_executable(indexer Indexer/main.cpp)
target_link_libraries(indexer DocumentIDManager.o Indexer.o
	FileConstants.o hash.o)

# Interface
add_executable(interface Interface/Interface.cpp)
target_include_directories(interface PRIVATE Indexer)
target_link_libraries(interface DocumentIDManager.o FileConstants.o)
