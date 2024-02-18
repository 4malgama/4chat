QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = "Amalgama Chat"

DESTDIR = D:/chat_client

include(crypto/aes.pri)

SOURCES += \
    account.cpp \
    auth_form/authform.cpp \
    command.cpp \
    command/byte_command.cpp \
    create_form/createform.cpp \
    crypto/stringcodec.cpp \
    main.cpp \
    client.cpp \
    network.cpp \
    network_packer/network_packer.cpp \
    profile/profile.cpp \
    ui/uicontrol.cpp \
    widgets/avatar_widget.cpp \
    widgets/message_widget.cpp

HEADERS += \
    account.h \
    auth_form/authform.h \
    classes.h \
    client.h \
    command.h \
    command/byte_command.h \
    create_form/createform.h \
    crypto/stringcodec.h \
    include/json.h \
    memory/types_variables.h \
    network.h \
    network_id.h \
    network_packer/network_packer.h \
    profile/profile.h \
    ui/uicontrol.h \
    widgets/avatar_widget.h \
    widgets/message_widget.h

FORMS += \
    auth_form/authform.ui \
    client.ui \
    create_form/createform.ui \
    profile/profile.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources.qrc
