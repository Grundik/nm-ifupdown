add_definitions(-DTRANSLATION_DOMAIN=\"plasmanetworkmanagement_ifupdownui\")

add_library(plasmanetworkmanagement_ifupdownui MODULE)
target_sources(plasmanetworkmanagement_ifupdownui PRIVATE
    ifupdown.cpp
    ifupdown.h
    ifupdownwidget.cpp
    ifupdownwidget.h
)

target_link_libraries(plasmanetworkmanagement_ifupdownui
    plasmanm_internal
    plasmanm_editor
    KF6::CoreAddons
    KF6::I18n
    KF6::WidgetsAddons
    Qt6::Widgets
)

install(TARGETS plasmanetworkmanagement_ifupdownui
        DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/network/vpn)
