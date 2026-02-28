cmake_minimum_required(VERSION 3.16)

project(QQ_Project LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt6 库
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# 定义源文件列表
set(SOURCES
    main.cpp

    login/login.cpp
    login/login.h

    register/register.h
    register/register.cpp
    register/avatar_popup.h

    base_widget/mainWindow.h
    base_widget/mainWindow.cpp
    

    left_widget/leftBar.h
    left_widget/leftBar.cpp

    mid_widget/contactsPage.h
    mid_widget/contactsPage.cpp
    mid_widget/friendCell.h
    mid_widget/friendCell.cpp
    mid_widget/friendWidget.h
    mid_widget/friendWidget.cpp
    mid_widget/friendList.h
    mid_widget/friendList.cpp
    mid_widget/groupList.h
    mid_widget/groupList.cpp
    mid_widget/messageListPage.h
    mid_widget/messageList.cpp
    mid_widget/addFriendWidget.h
    mid_widget/addFriendWidget.cpp

    # right_widget/

    socket/clientSocket.h
    socket/clientSocket.cpp

    util/avatar.h
    util/msg_cell.h
    util/msg_cell.cpp
    util/title.h
    util/util.h
    util/util.cpp


    # 资源文件
    QQ.qrc
)

# 生成可执行程序
qt_add_executable(QQ ${SOURCES})

# 链接 Qt 模块
target_link_libraries(QQ PRIVATE Qt6::Widgets Qt6::Network)

if(WIN32)
    set_target_properties(QQ PROPERTIES WIN32_EXECUTABLE TRUE)
endif()