#############################################################################
# Makefile for building: Ship_Happens
# Generated by qmake (2.01a) (Qt 4.8.6) on: Wed Jun 18 17:16:35 2014
# Project:  Ship_Happens.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Ship_Happens.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_TESTLIB_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtTest -I/usr/include/qt4 -I. -IPlayer -IPlayer/Ships -IGui -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtTest -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = game.cpp \
		main.cpp \
		Gui/setwindow.cpp \
		Gui/startwindow.cpp \
		Player/board.cpp \
		Player/player.cpp \
		Player/square.cpp \
		Player/Ships/air_carrier.cpp \
		Player/Ships/battleship.cpp \
		Player/Ships/destroyer.cpp \
		Player/Ships/ship.cpp \
		Player/Ships/submarine.cpp \
		Gui/listwindow.cpp \
		Gui/playwindow.cpp \
		Gui/enddialog.cpp moc_setwindow.cpp \
		moc_startwindow.cpp \
		moc_listwindow.cpp \
		moc_playwindow.cpp \
		moc_enddialog.cpp
OBJECTS       = game.o \
		main.o \
		setwindow.o \
		startwindow.o \
		board.o \
		player.o \
		square.o \
		air_carrier.o \
		battleship.o \
		destroyer.o \
		ship.o \
		submarine.o \
		listwindow.o \
		playwindow.o \
		enddialog.o \
		moc_setwindow.o \
		moc_startwindow.o \
		moc_listwindow.o \
		moc_playwindow.o \
		moc_enddialog.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Ship_Happens.pro
QMAKE_TARGET  = Ship_Happens
DESTDIR       = 
TARGET        = Ship_Happens

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_setwindow.h ui_startwindow.h ui_listwindow.h ui_playwindow.h ui_enddialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Ship_Happens.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtTest.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Ship_Happens.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtTest.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Ship_Happens.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Ship_Happens1.0.0 || $(MKDIR) .tmp/Ship_Happens1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Ship_Happens1.0.0/ && $(COPY_FILE) --parents game.h my_headers.h Gui/setwindow.h Gui/startwindow.h Player/board.h Player/player.h Player/square.h Player/Ships/air_carrier.h Player/Ships/battleship.h Player/Ships/destroyer.h Player/Ships/ship.h Player/Ships/submarine.h Gui/listwindow.h Gui/playwindow.h Gui/enddialog.h .tmp/Ship_Happens1.0.0/ && $(COPY_FILE) --parents game.cpp main.cpp Gui/setwindow.cpp Gui/startwindow.cpp Player/board.cpp Player/player.cpp Player/square.cpp Player/Ships/air_carrier.cpp Player/Ships/battleship.cpp Player/Ships/destroyer.cpp Player/Ships/ship.cpp Player/Ships/submarine.cpp Gui/listwindow.cpp Gui/playwindow.cpp Gui/enddialog.cpp .tmp/Ship_Happens1.0.0/ && $(COPY_FILE) --parents Gui/setwindow.ui Gui/startwindow.ui Gui/listwindow.ui Gui/playwindow.ui Gui/enddialog.ui .tmp/Ship_Happens1.0.0/ && (cd `dirname .tmp/Ship_Happens1.0.0` && $(TAR) Ship_Happens1.0.0.tar Ship_Happens1.0.0 && $(COMPRESS) Ship_Happens1.0.0.tar) && $(MOVE) `dirname .tmp/Ship_Happens1.0.0`/Ship_Happens1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Ship_Happens1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_setwindow.cpp moc_startwindow.cpp moc_listwindow.cpp moc_playwindow.cpp moc_enddialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_setwindow.cpp moc_startwindow.cpp moc_listwindow.cpp moc_playwindow.cpp moc_enddialog.cpp
moc_setwindow.cpp: game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/setwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) Gui/setwindow.h -o moc_setwindow.cpp

moc_startwindow.cpp: Gui/setwindow.h \
		game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/listwindow.h \
		Gui/playwindow.h \
		Gui/enddialog.h \
		Gui/startwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) Gui/startwindow.h -o moc_startwindow.cpp

moc_listwindow.cpp: Gui/listwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) Gui/listwindow.h -o moc_listwindow.cpp

moc_playwindow.cpp: game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/enddialog.h \
		Gui/playwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) Gui/playwindow.h -o moc_playwindow.cpp

moc_enddialog.cpp: Gui/enddialog.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) Gui/enddialog.h -o moc_enddialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_setwindow.h ui_startwindow.h ui_listwindow.h ui_playwindow.h ui_enddialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_setwindow.h ui_startwindow.h ui_listwindow.h ui_playwindow.h ui_enddialog.h
ui_setwindow.h: Gui/setwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic Gui/setwindow.ui -o ui_setwindow.h

ui_startwindow.h: Gui/startwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic Gui/startwindow.ui -o ui_startwindow.h

ui_listwindow.h: Gui/listwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic Gui/listwindow.ui -o ui_listwindow.h

ui_playwindow.h: Gui/playwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic Gui/playwindow.ui -o ui_playwindow.h

ui_enddialog.h: Gui/enddialog.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic Gui/enddialog.ui -o ui_enddialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

game.o: game.cpp game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o game.o game.cpp

main.o: main.cpp my_headers.h \
		game.h \
		Player/player.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/setwindow.h \
		Gui/startwindow.h \
		Gui/listwindow.h \
		Gui/playwindow.h \
		Gui/enddialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

setwindow.o: Gui/setwindow.cpp Gui/setwindow.h \
		game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		ui_setwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o setwindow.o Gui/setwindow.cpp

startwindow.o: Gui/startwindow.cpp Gui/startwindow.h \
		Gui/setwindow.h \
		game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/listwindow.h \
		Gui/playwindow.h \
		Gui/enddialog.h \
		ui_startwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o startwindow.o Gui/startwindow.cpp

board.o: Player/board.cpp my_headers.h \
		Player/board.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o board.o Player/board.cpp

player.o: Player/player.cpp my_headers.h \
		Player/player.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o player.o Player/player.cpp

square.o: Player/square.cpp Player/square.h \
		my_headers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o square.o Player/square.cpp

air_carrier.o: Player/Ships/air_carrier.cpp Player/Ships/air_carrier.h \
		my_headers.h \
		Player/Ships/ship.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o air_carrier.o Player/Ships/air_carrier.cpp

battleship.o: Player/Ships/battleship.cpp Player/Ships/battleship.h \
		my_headers.h \
		Player/Ships/ship.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o battleship.o Player/Ships/battleship.cpp

destroyer.o: Player/Ships/destroyer.cpp Player/Ships/destroyer.h \
		my_headers.h \
		Player/Ships/ship.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o destroyer.o Player/Ships/destroyer.cpp

ship.o: Player/Ships/ship.cpp Player/Ships/ship.h \
		my_headers.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ship.o Player/Ships/ship.cpp

submarine.o: Player/Ships/submarine.cpp Player/Ships/submarine.h \
		my_headers.h \
		Player/Ships/ship.h \
		Player/square.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o submarine.o Player/Ships/submarine.cpp

listwindow.o: Gui/listwindow.cpp Gui/listwindow.h \
		ui_listwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o listwindow.o Gui/listwindow.cpp

playwindow.o: Gui/playwindow.cpp Gui/playwindow.h \
		game.h \
		Player/player.h \
		my_headers.h \
		Player/board.h \
		Player/square.h \
		Player/Ships/submarine.h \
		Player/Ships/ship.h \
		Player/Ships/destroyer.h \
		Player/Ships/battleship.h \
		Player/Ships/air_carrier.h \
		Gui/enddialog.h \
		ui_playwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playwindow.o Gui/playwindow.cpp

enddialog.o: Gui/enddialog.cpp Gui/enddialog.h \
		ui_enddialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o enddialog.o Gui/enddialog.cpp

moc_setwindow.o: moc_setwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_setwindow.o moc_setwindow.cpp

moc_startwindow.o: moc_startwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_startwindow.o moc_startwindow.cpp

moc_listwindow.o: moc_listwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_listwindow.o moc_listwindow.cpp

moc_playwindow.o: moc_playwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playwindow.o moc_playwindow.cpp

moc_enddialog.o: moc_enddialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_enddialog.o moc_enddialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

