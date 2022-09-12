

#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QCloseEvent>

class settings ;
class Logger ;

namespace Ui {
class logWindow;
}

class logWindow : public QWidget
{
	Q_OBJECT
public:
	logWindow( QWidget * parent,settings&,Logger& ) ;
	~logWindow() override ;
	void setText( const QByteArray& ) ;
	template< typename LoggerData >
	void update( const LoggerData& e )
	{
		this->update( e.toString() ) ;
	}
	void update( const QByteArray& e ) ;
	void Hide() ;
	void Show() ;
	void clear() ;
private:
	void closeEvent( QCloseEvent * ) override ;
	Ui::logWindow * m_ui ;
	settings& m_settings ;
};

#endif // LOGWINDOW_H
