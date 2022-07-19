cmake_minimum_required(VERSION 3.6)

# Set the project name
project (Event)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
	main.cpp
	event.hpp
	events_holder.cpp
	events_holder.hpp
)

add_executable(Event ${SOURCES})