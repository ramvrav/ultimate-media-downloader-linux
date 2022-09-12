#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "ITrackingService.h"
#include "about.h"
#include "accountmanager.h"
#include "basicdownloader.h"
#include "batchdownloader.h"
#include "configure.h"
#include "context.hpp"
#include "library.h"
#include "playlistdownloader.h"
#include "posthogtrackingservice.h"
#include "xpsearch.h"
#include "ytsearch.h"

class tabManager {
public:
  tabManager(settings &s, translator &t, engines &e, Logger &l,
             Ui::MainWindow &ui, QWidget &w, MainWindow &mw,
             utility::versionInfo &u, QString debug);
  void init_done(Ui::MainWindow &ui, settings &settings);
  void setDefaultEngines();
  tabManager &gotEvent(const QByteArray &e);
  tabManager &enableAll();
  tabManager &disableAll();
  tabManager &resetMenu();
  tabManager &reTranslateUi();
  basicdownloader &basicDownloader() { return m_basicdownloader; }
  batchdownloader &batchDownloader() { return m_batchdownloader; }
  playlistdownloader &playlistDownloader() { return m_playlistdownloader; }
  configure &Configure() { return m_configure; }
  accountManager &AccountManager() { return m_accountManager; }
  YtSearch &YoutubeSearch() { return m_ytSearch; }
  XpSearch &XpSearch2() { return m_xpSearch; }
  ITrackingService *trackingService() const;

  bool uiEnabled() { return m_uiEnabled; }

  void toggleXpSearch(bool enable);

private:
  int m_currentTab;
  bool m_uiEnabled = true;
  Context m_ctx;
  accountManager m_accountManager;
  about m_about;
  configure m_configure;
  basicdownloader m_basicdownloader;
  batchdownloader m_batchdownloader;
  playlistdownloader m_playlistdownloader;
  YtSearch m_ytSearch;
  XpSearch m_xpSearch;
  library m_library;
  ITrackingService *m_trackingService = nullptr;
  QMetaObject::Connection m_initConnection;
  void enableXpSearchSilently();
};

#endif
