#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QStringList>

#include "engines.h"
#include "engineupdatecheck.h"
#include "logger.h"
#include "logwindow.h"
#include "rateapp.h"
#include "tabmanager.h"

#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QApplication &, settings &, translator &, const QStringList &);
  void retranslateUi();
  void setTitle(const QString &m);
  void resetTitle();
  void Show();
  void processEvent(const QByteArray &e);
  void quitApp();
  void log(const QByteArray &);
  ~MainWindow() override;
protected slots:
  bool eventFilter(QObject *o, QEvent *e) override;
  void closeEvent(QCloseEvent *) override;
private slots:
  void initRateWidget();
  void restoreMainWindow();
  void handleEngineUpdateAvailable();

private:
  QApplication &m_qApp;
  std::unique_ptr<Ui::MainWindow> m_ui;
  Logger m_logger;
  engines m_engines;
  utility::versionInfo m_cou;
  tabManager m_tabManager;
  settings &m_settings;
  QString m_defaultWindowTitle;

  EngineUpdateCheck *m_engineUpdateCheck = nullptr;
};

#endif // MAINWINDOW_H
