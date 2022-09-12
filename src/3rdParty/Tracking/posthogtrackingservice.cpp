#include "posthogtrackingservice.h"

PostHogTrackingService::PostHogTrackingService(
    QNetworkAccessManager *networkManager, const QString &host,
    const QString &apiKey, const QString &distinctId)
    : m_networkManager(networkManager), m_host(host), m_apiKey(apiKey),
      m_distinctId(distinctId) {

  if (m_networkManager == nullptr) {
    m_networkManager = new QNetworkAccessManager();
    m_networkManager->setObjectName("ph_internal_nm");
  }
}

void PostHogTrackingService::trackEvent(const QString &eventName,
                                        const QJsonObject &properties) {
  QJsonObject json;
  json["api_key"] = m_apiKey;
  json["distinct_id"] = m_distinctId;
  json["event"] = eventName;
  json["properties"] = properties;

  QNetworkRequest request(QUrl(m_host + "/capture"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  m_networkManager->post(request, QJsonDocument(json).toJson());
}
