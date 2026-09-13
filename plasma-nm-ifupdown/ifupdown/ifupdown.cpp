/*
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "ifupdown.h"
#include "ifupdownwidget.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(IfupdownUiPlugin, "plasmanetworkmanagement_ifupdownui.json")

IfupdownUiPlugin::IfupdownUiPlugin(QObject *parent, const QVariantList &)
    : VpnUiPlugin(parent)
{
}

IfupdownUiPlugin::~IfupdownUiPlugin() = default;

SettingWidget *IfupdownUiPlugin::widget(const NetworkManager::VpnSetting::Ptr &setting, QWidget *parent)
{
    return new IfupdownWidget(setting, parent);
}

SettingWidget *IfupdownUiPlugin::askUser(const NetworkManager::VpnSetting::Ptr &setting, const QStringList &hints, QWidget *parent)
{
    Q_UNUSED(hints);
    // No secrets; reuse the same widget (or return an empty one).
    return new IfupdownWidget(setting, parent);
}

QString IfupdownUiPlugin::suggestedFileName(const NetworkManager::ConnectionSettings::Ptr &connection) const
{
    Q_UNUSED(connection);
    return {};
}

#include "ifupdown.moc"
