QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addshuiyin.cpp \
    main.cpp \
    mainwindow.cpp \
    qushuiyin.cpp

HEADERS += \
    addshuiyin.h \
    mainwindow.h \
    qushuiyin.h

FORMS += \
    addshuiyin.ui \
    mainwindow.ui \
    qushuiyin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    watermark/README.md \
    watermark/__pycache__/reedsolomon.cpython-37.pyc \
    watermark/__pycache__/wm_kmeans.cpython-36.pyc \
    watermark/__pycache__/wm_kmeans.cpython-37.pyc \
    watermark/data/covtype_10000.csv \
    watermark/data/data_wm_1000_em_wm.csv \
    watermark/demo_1.py \
    watermark/reedsolomon.py \
    watermark/wm_emb.py \
    watermark/wm_ext.py \
    watermark/wm_judge.py \
    watermark/wm_kmeans.py
