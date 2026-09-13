/*
 * Minimal plasma-nm VpnUiPlugin for org.freedesktop.NetworkManager.ifupdown
 *
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#ifndef PLASMA_NM_IFUPDOWN_H
#define PLASMA_NM_IFUPDOWN_H

#include "vpnuiplugin.h"

#include <QVariant>

class Q_DECL_EXPORT IfupdownUiPlugin : public VpnUiPlugin
{
    Q_OBJECT
public:
    explicit IfupdownUiPlugin(QObject *parent = nullptr, const QVariantList &args = QVariantList());
    ~IfupdownUiPlugin() override;

    SettingWidget *widget(const NetworkManager::VpnSetting::Ptr &setting, QWidget *parent) override;
    SettingWidget *askUser(const NetworkManager::VpnSetting::Ptr &setting, const QStringList &hints, QWidget *parent) override;

    QString suggestedFileName(const NetworkManager::ConnectionSettings::Ptr &connection) const override;
};

#endif
