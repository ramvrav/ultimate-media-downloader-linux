#ifndef SETTINGS_H
#define SETTINGS_H

#include <QByteArray>
#include <QComboBox>
#include <QPixmap>
#include <QSettings>
#include <QString>
#include <QStringList>

#include <memory>
#include <vector>

#include <QStandardPaths>

class Logger;
class QApplication;

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPalette>

class settings {
public:
  enum class tabName { basic, batch, playlist };

  settings();

  QSettings &bk();

  int tabNumber();
  size_t maxConcurrentDownloads();

  QString downloadFolder();
  QString libraryDownloadFolder();
  QString downloadFolder(Logger &);
  QString localizationLanguagePath();
  QString localizationLanguage();
  QString commandOnSuccessfulDownload();
  QString commandWhenAllFinished();
  QString defaultEngine(settings::tabName, const QString &);
  QString cookieFilePath(const QString &engineName);
  QString windowsDimensions(const QString &windowName);
  QString engineDefaultDownloadOptions(const QString &engineName);
  QString playlistRangeHistoryLastUsed();
  QString configPaths();

  QStringList getOptionsHistory(settings::tabName);
  QStringList playlistRangeHistory();
  QStringList playlistUrlHistory();

  QString lastUsedOption(const QString &, settings::tabName);

  QStringList localizationLanguages();

  QPixmap defaultVideoThumbnailIcon(settings::tabName);

  bool autoDownload();
  bool showVersionInfoWhenStarting();
  bool concurrentDownloading();
  bool useSystemProvidedVersionIfAvailable();
  bool showThumbnails();
  bool saveHistory();
  bool playlistDownloaderSaveHistory();

  int stringTruncationSize();
  int historySize();

  double thumbnailWidth(settings::tabName);
  double thumbnailHeight(settings::tabName);

  void clearOptionsHistory(settings::tabName);
  void setEngineDefaultDownloadOptions(const QString &engineName,
                                       const QString &options);
  void addToplaylistRangeHistory(const QString &);
  void clearPlaylistRangeHistory();
  void clearPlaylistUrlHistory();
  void addOptionsHistory(const QString &, settings::tabName);
  void setTheme(QApplication &);
  void setMaxConcurrentDownloads(int);
  void setTabNumber(int);
  void setShowThumbnails(bool);
  void setPlaylistDownloaderSaveHistory(bool);
  void setShowVersionInfoWhenStarting(bool);
  void setDarkMode(const QString &);
  void setPlaylistRangeHistoryLastUsed(const QString &);
  void setHighDpiScalingFactor(const QString &);
  void setlibraryDownloadFolder(const QString &);
  void setCookieFilePath(const QString &engineName,
                         const QString &cookieFilePath);
  void setDefaultEngine(const QString &, settings::tabName);
  void setLastUsedOption(const QString &engineName, const QString &options,
                         settings::tabName);
  void setDownloadFolder(const QString &);
  void setLocalizationLanguage(const QString &language);
  void setWindowDimensions(const QString &window, const QString &dimenstion);
public slots:
  QVariant getValue(const QString &key, const QVariant &defaultValue) const;
  void setValue(const QString &key, const QVariant &value);

private slots:
  void initThemes();
private:
  std::unique_ptr<QSettings> m_settingsP;
  QSettings &m_settings;
  QPalette lightPalette, darkPalette;
  QStringList styleKeys;

  double thumbnail_width;
  double thumbnail_height;

};

#endif
