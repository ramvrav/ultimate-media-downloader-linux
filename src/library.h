#ifndef LIBRARY_H
#define LIBRARY_H

#include "context.hpp"
#include <QDir>
#include <QString>
#include <QStringList>

#include "settings.h"
#include "tableWidget.h"
#include "utility.h"

class tabManager;

#include <QObject>

class library : public QObject {
  Q_OBJECT
public:
  library(const Context &);
  void init_done();
  void enableAll();
  void disableAll();
  void resetMenu();
  void retranslateUi();
  void tabEntered();
  void tabExited();
  enum class ICON { FILE, FOLDER, VIDEO, AUDIO, IMAGE, UNKNOWN };
private slots:
  static library::ICON getIconTypeFromFileName(const QString &filename);

private:
  void enableAll(bool);
  void disableAll(bool);
  void internalEnableAll();
  void internalDisableAll();
  void showContents(const QString &, bool disableUi = true);
  void moveUp();
  void addItem(const QString &text, library::ICON);
  const Context &m_ctx;
  bool m_enableGlobalUiChanges;
  settings &m_settings;
  Ui::MainWindow &m_ui;
  tableMiniWidget<ICON> m_table;
  QString m_downloadFolder;
  QString m_currentPath;
  const QDir::Filters m_dirFilter =
      QDir::Filter::Files | QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot;
  QPixmap m_folderIcon;
  QPixmap m_videoIcon;
  QPixmap m_audioIcon;
  QPixmap m_unknownIcon;
  QPixmap m_imageIcon;
};

#endif
