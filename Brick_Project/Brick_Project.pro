#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T10:53:43
#
#-------------------------------------------------

QT       += core gui opengl multimedia 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Brick_Project
TEMPLATE = app


SOURCES += main.cpp \
    CView.cpp \
    CControl.cpp \
    CModel.cpp \
    CObject.cpp \
    CVector3.cpp \
    CGLarea.cpp \
    CBrique.cpp \
    CShpere.cpp \
    CPalet.cpp \
    CMurH.cpp \
    CMurV.cpp \
    CWebcam.cpp

HEADERS  += \
    CView.h \
    CControl.h \
    CModel.h \
    CObject.h \
    CVector3.h \
    CGLarea.h \
    CBrique.h \
    CSphere.h \
    CPalet.h \
    CMurH.h \
    CMurV.h \
    CWebcam.h

OTHER_FILES +=

INCLUDEPATH +=$$(OPENCV_DIR)\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core248 \
    -lopencv_highgui248 \
    -lopencv_imgproc248 \
    -lopencv_features2d248 \
    -lopencv_calib3d248 \
    -lopencv_objdetect248