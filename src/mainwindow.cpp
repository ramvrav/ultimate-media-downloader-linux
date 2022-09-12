#include "mainwindow.h"
#include "tabmanager.h"
#include "ui_mainwindow.h"
#include "utility.h"

#include "context.hpp"
#include "settings.h"
#include "translator.h"

#include <QScreen>

static std::unique_ptr<Ui::MainWindow> _init_ui(QMainWindow &mw) {
  auto m = std::make_unique<Ui::MainWindow>();
  m->setupUi(&mw);
  return m;
}

static QString _debug(const QStringList &e) {
  if (e.contains("--debug")) {

    return "--debug";

  } else if (e.contains("--qdebug")) {

    return "--qdebug";
  } else {
    return "";
  }
}

MainWindow::MainWindow(QApplication &app, settings &s, translator &t,
                       const QStringList &args)
    : m_qApp(app), m_ui(_init_ui(*this)),
      m_logger(*m_ui->plainTextEditLogger, this, s), m_engines(m_logger, s),
      m_cou(*m_ui), m_tabManager(s, t, m_engines, m_logger, *m_ui, *this, *this,
                                 m_cou, _debug(args)),
      m_settings(s), m_defaultWindowTitle(APPLICATION_NAME) {
  QIcon icon = QIcon::fromTheme(QApplication::applicationName(),
                                QIcon(":/icons/app/icon-64.png"));
  this->window()->setWindowIcon(icon);
  initRateWidget();
  m_ui.get()->ytSearchResultsListWidget->installEventFilter(this);
  m_ui.get()->orion->installEventFilter(this);
  restoreMainWindow();

  // init engine version check
  auto engine_path = engines::enginePaths(m_settings).binPath() + "/core";
  m_engineUpdateCheck = new EngineUpdateCheck(this, engine_path);
  connect(m_engineUpdateCheck, &EngineUpdateCheck::updateFound, this,
          &MainWindow::handleEngineUpdateAvailable);
  m_engineUpdateCheck->checkForUpdate();

  // init player service
  PlayerService *playerService =
      new PlayerService(this, engine_path, m_settings);
  playerService->clearSocketDir();
  playerService->deleteLater();
}

void MainWindow::handleEngineUpdateAvailable() {
  qWarning() << "ENGINE: handleEngineUpdate...";
  m_ui.get()->pbConfigureDownload->setEnabled(true);
  m_ui.get()->pbConfigureDownload->click();
}

void MainWindow::restoreMainWindow() {
  if (m_settings.getValue("MainWindowGeometry", QByteArray())
          .toByteArray()
          .isEmpty() == false) {
    restoreGeometry(
        m_settings.getValue("MainWindowGeometry", QByteArray()).toByteArray());
    //    //move to screen where mouse is and center
    //    QPoint pos = QCursor::pos();
    //    for (QScreen *screen : QGuiApplication::screens()) {
    //      QRect screenRect = screen->geometry();
    //      if (screenRect.contains(pos)) {
    //        this->move(screenRect.center() - this->rect().center());
    //      }
    //    }
  } else {
    // default size
    this->resize(870, 620);
  }
}

bool MainWindow::eventFilter(QObject *o, QEvent *e) {
  if (e->type() == QEvent::Resize &&
      o == m_ui.get()->ytSearchResultsListWidget) {
    m_tabManager.YoutubeSearch().resizeTrendingView();
  }

  if (o == m_ui.get()->orion &&
      (e->type() == QEvent::HoverEnter || e->type() == QEvent::HoverLeave)) {
    if (e->type() == QEvent::HoverLeave) {
      m_ui.get()->orion->setIcon(QIcon(":/icons/app/orion-64-grayscale.png"));
    } else if (e->type() == QEvent::HoverEnter) {
      m_ui.get()->orion->setIcon(QIcon(":/icons/app/orion-64.png"));
    }
  }

  return false;
}

void MainWindow::initRateWidget() {
  RateApp *rateApp =
      new RateApp(this, "snap://ultimate-media-downloader", 2, 5, 1000 * 30);
  rateApp->setWindowTitle(QApplication::applicationName() + " | " +
                          tr("Rate Application"));
  rateApp->setVisible(false);
  rateApp->setWindowFlags(Qt::Dialog);
  rateApp->setAttribute(Qt::WA_DeleteOnClose, true);
  QPoint centerPos = this->geometry().center() - rateApp->geometry().center();
  connect(rateApp, &RateApp::showRateDialog, rateApp, [=]() {
    if (this->windowState() != Qt::WindowMinimized && this->isVisible() &&
        isActiveWindow()) {
      rateApp->move(centerPos);
      rateApp->show();
    } else {
      rateApp->delayShowEvent();
    }
  });
}

void MainWindow::retranslateUi() { m_ui->retranslateUi(this); }

void MainWindow::setTitle(const QString &m) {
  if (m.isEmpty()) {

    this->resetTitle();
  } else {
    this->window()->setWindowTitle(m);
  }
}

void MainWindow::resetTitle() { this->setTitle(m_defaultWindowTitle); }

void MainWindow::Show() { this->show(); }

void MainWindow::processEvent(const QByteArray &e) { m_tabManager.gotEvent(e); }

void MainWindow::quitApp() { m_tabManager.basicDownloader().appQuit(); }

void MainWindow::log(const QByteArray &e) { m_logger.add(e, -1); }

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *e) {

  m_settings.setValue("MainWindowGeometry", saveGeometry());

  e->ignore();

  this->hide();

  m_tabManager.basicDownloader().appQuit();
}
