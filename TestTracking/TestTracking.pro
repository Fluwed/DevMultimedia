#-------------------------------------------------
#
# Project created by QtCreator 2012-10-24T15:02:48
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = TestTracking
TEMPLATE = app


SOURCES += main.cpp\
        webcamwindow.cpp

HEADERS  += webcamwindow.h

INCLUDEPATH +=$$(OPENCV_DIR)\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core248 \
    -lopencv_highgui248 \
    -lopencv_imgproc248 \
    -lopencv_features2d248 \
    -lopencv_calib3d248 \
    -lopencv_objdetect248

