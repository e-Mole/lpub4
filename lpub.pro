# #####################################################################
# Automatically generated by qmake (2.01a) Sun May 25 15:34:20 2008
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    rcc
INCLUDEPATH += .
MOC_DIR = ./moc
OBJECTS_DIR = ./objs
RCC_DIR = ./rcc
macx { 
    ICON = LPub.icns
    
    # QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
    CONFIG += x86 \
        ppc
}

# Input
HEADERS += backgrounddialog.h \
    backgrounditem.h \
    borderdialog.h \
    callout.h \
    calloutbackgrounditem.h \
    color.h \
    commands.h \
    commonmenus.h \
    csiitem.h \
    dependencies.h \
    dividerdialog.h \
    editwindow.h \
    globals.h \
    highlighter.h \
    ldrawfiles.h \
    LPub.h \
    lpub_preferences.h \
    meta.h \
    metagui.h \
    metaitem.h \
    metatypes.h \
    name.h \
    numberitem.h \
    pagebackgrounditem.h \
    pairdialog.h \
    partslist.h \
    paths.h \
    placement.h \
    placementdialog.h \
    pli.h \
    pliconstraindialog.h \
    pointer.h \
    pointeritem.h \
    preferencesdialog.h \
    range.h \
    range_element.h \
    ranges.h \
    ranges_element.h \
    ranges_item.h \
    render.h \
    reserve.h \
    resize.h \
    resolution.h \
    scaledialog.h \
    step.h \
    where.h \
    textitem.h
FORMS += preferences.ui
SOURCES += assemglobals.cpp \
    backgrounddialog.cpp \
    backgrounditem.cpp \
    borderdialog.cpp \
    callout.cpp \
    calloutbackgrounditem.cpp \
    calloutglobals.cpp \
    color.cpp \
    commands.cpp \
    commonmenus.cpp \
    csiitem.cpp \
    dependencies.cpp \
    dividerdialog.cpp \
    editwindow.cpp \
    formatpage.cpp \
    highlighter.cpp \
    ldrawfiles.cpp \
    LPub.cpp \
    lpub_preferences.cpp \
    main.cpp \
    meta.cpp \
    metagui.cpp \
    metaitem.cpp \
    multistepglobals.cpp \
    numberitem.cpp \
    openclose.cpp \
    pagebackgrounditem.cpp \
    pageglobals.cpp \
    pairdialog.cpp \
    partslist.cpp \
    paths.cpp \
    placement.cpp \
    placementdialog.cpp \
    pli.cpp \
    pliconstraindialog.cpp \
    pliglobals.cpp \
    pointeritem.cpp \
    preferencesdialog.cpp \
    printpdf.cpp \
    projectglobals.cpp \
    range.cpp \
    range_element.cpp \
    ranges.cpp \
    ranges_element.cpp \
    ranges_item.cpp \
    render.cpp \
    resize.cpp \
    resolution.cpp \
    rotate.cpp \
    scaledialog.cpp \
    step.cpp \
    traverse.cpp \
    undoredo.cpp \
    textitem.cpp
RESOURCES += LPub.qrc
