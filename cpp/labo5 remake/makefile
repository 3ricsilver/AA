.SILENT:
CLASSES=./classes
OBJET= $(CLASSES)/MyQT.o $(CLASSES)/Image.o $(CLASSES)/ImageNG.o $(CLASSES)/Dimension.o $(CLASSES)/Couleur.o $(CLASSES)/ImageRGB.o $(CLASSES)/ImageB.o $(CLASSES)/Exception.o  $(CLASSES)/RGBException.o $(CLASSES)/XYException.o $(CLASSES)/ArrayList.o $(CLASSES)/Iterateur.o $(CLASSES)/Traitements.o
APPLIC=Test9
COMP=g++ 
COMPTEST=g++ -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so
COMPQT=g++ -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

all:	print $(APPLIC)

print:		
			echo "////////////////////////////////////////////////////////////////////"

Test9:	Test9.cpp $(OBJET)
		$(COMPTEST) Test9.cpp -o Test9 $(OBJET)  -I $(CLASSES)
		echo "creation du test9"
$(CLASSES)/Traitements.o:	$(CLASSES)/Traitements.h $(CLASSES)/Traitements.cpp
							$(COMP)-c $(CLASSES)/Traitements.cpp -o $(CLASSES)/Traitements.o 
							echo "Creation de Traitements.o"

$(CLASSES)/ArrayList.o:	$(CLASSES)/ArrayList.h $(CLASSES)/ArrayList.cpp
						$(COMP) -c $(CLASSES)/ArrayList.cpp -o $(CLASSES)/ArrayList.o 
						echo "Creation de ArrayList.o"

$(CLASSES)/Iterateur.o:	$(CLASSES)/Iterateur.h $(CLASSES)/Iterateur.cpp
						$(COMP) -c $(CLASSES)/Iterateur.cpp -o $(CLASSES)/Iterateur.o 
						echo "Creation de Iterateur.o"

$(CLASSES)/Exception.o:	$(CLASSES)/Exception.h $(CLASSES)/Exception.cpp
						$(COMP) -c $(CLASSES)/Exception.cpp -o $(CLASSES)/Exception.o
						echo "Creation d Exception.o"

$(CLASSES)/RGBException.o:	$(CLASSES)/RGBException.h $(CLASSES)/RGBException.cpp
							$(COMP) -c $(CLASSES)/RGBException.cpp -o $(CLASSES)/RGBException.o
							echo "Creation de RGBException.o"

$(CLASSES)/XYException.o:	$(CLASSES)/XYException.h $(CLASSES)/XYException.cpp
							$(COMP) -c $(CLASSES)/XYException.cpp -o $(CLASSES)/XYException.o
							echo "Creation de XYException.o"

$(CLASSES)/ImageB.o:	$(CLASSES)/ImageB.h $(CLASSES)/ImageB.cpp $(CLASSES)/Dimension.h $(CLASSES)/MyQT.h 
						$(COMP) -c $(CLASSES)/ImageB.cpp -o $(CLASSES)/ImageB.o
						echo "Creation du ImageB.o"


$(CLASSES)/Couleur.o:	$(CLASSES)/Couleur.h $(CLASSES)/Couleur.cpp $(CLASSES)/RGBException.h
						$(COMP) -c $(CLASSES)/Couleur.cpp -o $(CLASSES)/Couleur.o
						echo "Creation du Couleur.o"

$(CLASSES)/ImageRGB.o:	$(CLASSES)/ImageRGB.h $(CLASSES)/ImageRGB.cpp $(CLASSES)/Dimension.h $(CLASSES)/MyQT.h
						$(COMP) -c $(CLASSES)/ImageRGB.cpp -o $(CLASSES)/ImageRGB.o
						echo "Creation du ImageRGB.o"

$(CLASSES)/MyQT.o:	$(CLASSES)/MyQT.cpp $(CLASSES)/MyQT.h $(CLASSES)/ImageNG.h $(CLASSES)/Image.h $(CLASSES)/ImageRGB.h
					$(COMPQT) -c $(CLASSES)/MyQT.cpp -o $(CLASSES)/MyQT.o
					echo "Creation du MyQT.o"

$(CLASSES)/ImageNG.o:	$(CLASSES)/ImageNG.cpp $(CLASSES)/ImageNG.h $(CLASSES)/Dimension.h $(CLASSES)/MyQT.h $(CLASSES)/RGBException.h
						$(COMP) -c $(CLASSES)/ImageNG.cpp -o $(CLASSES)/ImageNG.o
						echo "Creation du ImageNG.o"

$(CLASSES)/Dimension.o:	$(CLASSES)/Dimension.cpp $(CLASSES)/Dimension.h $(CLASSES)/XYException.h
						$(COMP) -c $(CLASSES)/Dimension.cpp -o $(CLASSES)/Dimension.o
						echo "Creation du Dimension.o"

$(CLASSES)/Image.o:		$(CLASSES)/Image.cpp $(CLASSES)/Image.h  $(CLASSES)/Dimension.h $(CLASSES)/MyQT.h
						$(COMP) -c $(CLASSES)/Image.cpp -o $(CLASSES)/Image.o 
						echo "Creation du Image.o"

clean:
		rm -f $(CLASSES)/*.o
		echo "Suppression des == .o =="

clobber:	clean
			rm -f $(APPLIC)
			echo "Suppression de  == $(APPLIC) =="