/*
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#ifndef PLASMA_NM_IFUPDOWN_WIDGET_H
#define PLASMA_NM_IFUPDOWN_WIDGET_H

#include "settingwidget.h"

#include <NetworkManagerQt/VpnSetting>

#include <QLineEdit>

class IfupdownWidget : public SettingWidget
{
    Q_OBJECT
public:
    explicit IfupdownWidget(const NetworkManager::VpnSetting::Ptr &setting, QWidget *parent = nullptr, Qt::WindowFlags f = {});
    ~IfupdownWidget() override = default;

    void loadConfig(const NetworkManager::Setting::Ptr &setting) override;
    void loadSecrets(const NetworkManager::Setting::Ptr &setting) override;
    QVariantMap setting() const override;
    bool isValid() const override;

private:
    NetworkManager::VpnSetting::Ptr m_setting;
    QLineEdit *m_iface = nullptr;
    QLineEdit *m_gateway = nullptr;
};

#endif
