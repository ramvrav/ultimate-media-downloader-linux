#include "accountmanager.h"
#include "moreapps.h"
#include "utility.h"

void accountManager::enableAll() {}

void accountManager::disableAll() {}

void accountManager::resetMenu() {}

accountManager::accountManager(const Context &ctx) : m_ctx(ctx) {
  if (accountWidget == nullptr) {
    accountWidget = new account();
    QObject::connect(accountWidget, &account::showAccountWidget,
                     m_ctx.Ui().tabWidget, [=]() {
                       m_ctx.Ui().tabWidget->setCurrentWidget(
                           m_ctx.Ui().tabAccount);
                     });
  }

  m_ctx.Ui().accountFrame->layout()->addWidget(accountWidget);

  // add moreapps widget
  MoreApps *moreApps =
      new MoreApps(m_ctx.Ui().tabAccount, nullptr, "keshavnrj",
                   QUrl("https://raw.githubusercontent.com/keshavbhatt/appdata/"
                        "main/moreapps.txt"),
                   false, true, 3);
  moreApps->setFixedHeight(110);

  m_ctx.Ui().accountFrame->layout()->addWidget(moreApps);

  this->retranslateUi();
}

QString accountManager::getAccountId() {
  if (accountWidget != nullptr) {
    return accountWidget->getAccountId();
  } else {
    return "null";
  }
}

bool accountManager::isPro() {
  if (accountWidget != nullptr) {
    return accountWidget->isPro();
  } else {
    return false;
  }
}

bool accountManager::evaluationUsed() {
  if (accountWidget != nullptr) {
    return accountWidget
        ->getEvaluation_used(); // we just check evaluation_used since we set it
                                // to false if the account is found pro in
                                // network test
  } else {
    return false;
  }
}

void accountManager::showPurchaseMessage() {
  if (accountWidget != nullptr && accountWidget->getEvaluation_used()) {
    accountWidget->showPurchaseMessage();
  }
}

void accountManager::retranslateUi() {}

void accountManager::tabEntered() {

  if (accountWidget != nullptr) {
    // update the evaluation date time
    if (accountWidget->getEvaluation_used() == false)
      accountWidget->check_evaluation_used();

    // update palette
    QPalette palette = QApplication::palette();
    foreach (QFrame *f, accountWidget->findChildren<QFrame *>()) {
      if (f->frameShape() == QFrame::HLine ||
          f->frameShape() == QFrame::VLine) {
        QPalette customPalette = palette;

        customPalette.setColor(QPalette::Normal, QPalette::WindowText,
                               palette.alternateBase().color());

        f->setPalette(customPalette);
      }
    }
  }
}

void accountManager::tabExited() {}

void accountManager::init_done() {}
