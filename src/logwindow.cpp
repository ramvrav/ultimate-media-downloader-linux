#include "logwindow.h"
#include "ui_logwindow.h"

#include "logger.h"
#include "settings.h"
#include "utility.h"

logWindow::logWindow(QWidget *parent, settings &s, Logger &logger)
    : QWidget(parent), m_ui(new Ui::logWindow), m_settings(s) {
  m_ui->setupUi(this);

  m_ui->plainTextEdit->setReadOnly(true);

  connect(m_ui->pbClose, &QPushButton::clicked, [this]() { this->Hide(); });

  connect(m_ui->pbClear, &QPushButton::clicked,
          [&logger]() { logger.clear(); });
}

logWindow::~logWindow() { delete m_ui; }

void logWindow::setText(const QByteArray &e) {
  m_ui->plainTextEdit->setPlainText(e);
  m_ui->plainTextEdit->moveCursor(QTextCursor::End);
}

void logWindow::update(const QByteArray &e) {
  if (this->isVisible()) {

    this->setText(e);
  }
}

void logWindow::Hide() {
  const auto &r = this->window()->geometry();

  auto x = QString::number(r.x());
  auto y = QString::number(r.y());
  auto w = QString::number(r.width());
  auto h = QString::number(r.height());

  m_settings.setWindowDimensions("LogWindow", x + "-" + y + "-" + w + "-" + h);

  this->hide();
  this->clear();
}

void logWindow::Show() {
  auto w = m_settings.windowsDimensions("LogWindow");

  if (!w.isEmpty()) {

    auto m = util::split(w, '-', true);

    if (m.size() == 4) {

      QRect r;

      r.setX(m.at(0).toInt());
      r.setY(m.at(1).toInt());
      r.setWidth(m.at(2).toInt());
      r.setHeight(m.at(3).toInt());

      this->window()->setGeometry(r);
    }
  }

  this->show();
}

void logWindow::clear() { m_ui->plainTextEdit->clear(); }

void logWindow::closeEvent(QCloseEvent *e) {
  e->ignore();
  this->Hide();
}
