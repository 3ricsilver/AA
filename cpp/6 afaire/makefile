All: Test5



Test5:	Test5.cpp Dimension.o Image.o ImageNG.o MyQT.o Couleur.o ImageRGB.o ImageB.o
				g++ Test5.cpp -o SusTest5 MyQT.o Image.o ImageNG.o Dimension.o Couleur.o ImageRGB.o ImageB.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

Dimension.o:	Dimension.cpp Dimension.h
				g++ Dimension.cpp -c

Image.o:		Image.cpp Image.h
				g++ Image.cpp -c

ImageNG.o:		ImageNG.cpp ImageNG.h
				g++ ImageNG.cpp -c

MyQT.o:			MyQT.cpp MyQT.h
				g++ -c MyQT.cpp -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++


Couleur.o:		Couleur.cpp Couleur.h
				g++ Couleur.cpp -c

ImageRGB.o:		ImageRGB.cpp ImageRGB.h
				g++ ImageRGB.cpp -c

ImageB.o:		ImageB.cpp ImageB.h
				g++ ImageB.cpp -c
