cmake_minimum_required(VERSION 3.16)

project(Health_statistic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Health_statistic_uk_UA.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Health_statistic
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        bios.h bios.cpp
        exercise.h exercise.cpp
        workout.h workout.cpp
        foodlist.h foodlist.cpp
        foodstatistics.h foodstatistics.cpp
        nutritionstrategieas.h nutritionstrategieas.cpp
        foodform.h foodform.cpp foodform.ui
        foodchangeinfo.h foodchangeinfo.cpp foodchangeinfo.ui
        exercisefactory.h exercisefactory.cpp
        performance_evaluator.h performance_evaluator.cpp
        ideal_exercise_repository.h ideal_exercise_repository.cpp
        physical_test.h physical_test.cpp
        dream.h dream.cpp
        dream_user.h dream_user.cpp
        messegefromdevs.h messegefromdevs.cpp messegefromdevs.ui
        dreamform.h dreamform.cpp dreamform.ui

        mainwindow.h mainwindow.cpp mainwindow.ui
        workoutwindow.h workoutwindow.cpp workoutwindow.ui
        recourses.qrc



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Health_statistic APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Health_statistic SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Health_statistic
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Health_statistic PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Health_statistic)
endif()
set_target_properties(Health_statistic PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Health_statistic
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Health_statistic)
endif()
