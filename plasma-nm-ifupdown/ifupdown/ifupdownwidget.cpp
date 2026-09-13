/*
 * SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
 */

#include "ifupdownwidget.h"

#include <NetworkManagerQt/Setting>

#include <QFormLayout>
#include <QLabel>
#include <QDBusMetaType>

static const char SERVICE_TYPE[] = "org.freedesktop.NetworkManager.ifupdown";

IfupdownWidget::IfupdownWidget(const NetworkManager::VpnSetting::Ptr &setting, QWidget *parent, Qt::WindowFlags f)
    : SettingWidget(setting, parent, f)
    , m_setting(setting)
{
    qDBusRegisterMetaType<NMStringMap>();

    auto *layout = new QFormLayout(this);
    m_iface = new QLineEdit(this);
    m_iface->setPlaceholderText(QStringLiteral("wg0"));
    m_gateway = new QLineEdit(this);
    m_gateway->setPlaceholderText(QStringLiteral("203.0.113.10 or 2001:db8::1"));

    layout->addRow(QStringLiteral("Interface (iface)"), m_iface);
    layout->addRow(QStringLiteral("External gateway"), m_gateway);
    layout->addRow(new QLabel(
        QStringLiteral("NM host-routes this address outside the tunnel so "
                       "peer traffic is not looped into the VPN."),
        this));

    watchChangedSetting();
    connect(m_iface, &QLineEdit::textChanged, this, &IfupdownWidget::slotWidgetChanged);
    connect(m_gateway, &QLineEdit::textChanged, this, &IfupdownWidget::slotWidgetChanged);

    if (setting && !setting->isNull()) {
        loadConfig(setting);
    }
}

void IfupdownWidget::loadConfig(const NetworkManager::Setting::Ptr &setting)
{
    Q_UNUSED(setting);
    const NMStringMap data = m_setting->data();
    m_iface->setText(data.value(QStringLiteral("iface")));
    if (m_iface->text().isEmpty()) {
        m_iface->setText(data.value(QStringLiteral("interface")));
    }
    if (m_iface->text().isEmpty()) {
        m_iface->setText(data.value(QStringLiteral("ifname")));
    }
    m_gateway->setText(data.value(QStringLiteral("gateway")));
    if (m_gateway->text().isEmpty()) {
        m_gateway->setText(data.value(QStringLiteral("vpn-gateway")));
    }
    if (m_gateway->text().isEmpty()) {
        m_gateway->setText(data.value(QStringLiteral("remote")));
    }
}

void IfupdownWidget::loadSecrets(const NetworkManager::Setting::Ptr &setting)
{
    Q_UNUSED(setting);
}

QVariantMap IfupdownWidget::setting() const
{
    NetworkManager::VpnSetting s;
    s.setServiceType(QLatin1String(SERVICE_TYPE));
    NMStringMap data;
    data.insert(QStringLiteral("iface"), m_iface->text().trimmed());
    data.insert(QStringLiteral("gateway"), m_gateway->text().trimmed());
    s.setData(data);
    return s.toMap();
}

bool IfupdownWidget::isValid() const
{
    return !m_iface->text().trimmed().isEmpty() && !m_gateway->text().trimmed().isEmpty();
}

#include "moc_ifupdownwidget.cpp"
