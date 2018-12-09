cmake_minimum_required(VERSION 2.8)
project(chess)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -Wextra -O3 -std=c++14")

find_package(Threads)
add_executable(chess 
	AI_basic.cpp  
	AI_tree.cpp  
	checkboard.cpp  
	empty.cpp   
	gameplay.cpp  	
	king.cpp    
	logger.cpp  
	pawn.cpp    
	queen.cpp
	AI.cpp        	
	bishop.cpp   
	chess.cpp       	
	figure.cpp  
	human.cpp     
	knight.cpp  
	move.cpp    
	player.cpp  
	rook.cpp
)
target_link_libraries(chess ${CMAKE_THREAD_LIBS_INIT})

