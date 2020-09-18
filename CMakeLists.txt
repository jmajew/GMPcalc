cmake_minimum_required(VERSION 3.17)

project(GMPCalc) # Your project name

set(CMAKE_CXX_STANDARD 11) # This is equal to QMAKE_CXX_FLAGS += -std=c++0x

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# This will find the Qt5 files. You will need a QT5_DIR env variable
find_package(Qt5Widgets REQUIRED) # Equivalent of QT += widgets

set( SOURCES 
	main.cpp 
	display.cpp 
	calculator.cpp
	calculator_form.cpp
	multidisplay.cpp
	mini-gmp.c
	#mini-mpq.c
) 
	
set( HEADERS 
	display.h 
	calculator.h
	calculator_form.h
	multidisplay.h
	mini-gmp.h
	#mini-mpq.h  
)

set(UI 
	calculator_form.ui
)
	
set ( RESOURCES
)
	

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Widgets REQUIRED )

SET( QT5_INCLUDES
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Xml_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${QT5_INCLUDES}
	${QT_QTDESIGNER_INCLUDE_DIR}
	${Qt5Widgets_INCLUDES}
)

IF ( WIN32 )
	add_executable(qcalc WIN32 ${SOURCES} ${HEADERS} ${UI})
	target_link_libraries(qcalc Qt5::Widgets)
ELSE ( WIN32 )
	add_executable(qcalc ${SOURCES} ${HEADERS} ${UI})
	target_link_libraries(qcalc Qt5::Widgets)
ENDIF ( WIN32 )

