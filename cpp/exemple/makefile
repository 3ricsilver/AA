COMP=g++	 #-D DEBUG



Test5:	Test5.cpp objets/ImageNG.o objets/Dimension.o objets/MyQT.o objets/Couleur.o objets/ImageRGB.o objets/Image.o objets/ImageB.o
		$(COMP) -I classes Test5.cpp objets/ImageNG.o objets/Dimension.o objets/MyQT.o objets/Couleur.o objets/ImageRGB.o objets/Image.o objets/ImageB.o  -o Test5 -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so


objets/MyQT.o:	classes/MyQT.cpp classes/MyQT.h classes/ImageNG.h classes/ImageRGB.h
		g++  -c classes/MyQT.cpp -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++
	 	mv MyQT.o objets/MyQT.o


objets/Image.o:	classes/Image.cpp classes/Image.h
		$(COMP) classes/Image.cpp -c
		mv Image.o objets/Image.o

objets/ImageNG.o:	classes/ImageNG.cpp classes/ImageNG.h classes/MyQT.h 
		$(COMP) classes/ImageNG.cpp -c
		mv ImageNG.o objets/ImageNG.o
		#$(COMP) classes/ImageNG.cpp -c -o objets/ImageNG.o

objets/Dimension.o :	classes/Dimension.cpp	classes/Dimension.h
			$(COMP)	classes/Dimension.cpp	-c
			mv  Dimension.o objets/Dimension.o 

objets/Couleur.o: classes/Couleur.cpp	classes/Couleur.h
			$(COMP) classes/Couleur.cpp -c
			mv Couleur.o objets/Couleur.o

objets/ImageRGB.o:	classes/ImageRGB.cpp classes/ImageRGB.h	classes/MyQT.h 
			$(COMP) classes/ImageRGB.cpp -c
			mv ImageRGB.o objets/ImageRGB.o

objets/ImageB.o:	classes/ImageB.cpp	classes/ImageB.h classes/MyQT.h 
			$(COMP) classes/ImageB.cpp -c
			mv ImageB.o objets/ImageB.o

clean:
	rm objets/*.o core -f

clobber:	clean 
	rm Test5 -f 
