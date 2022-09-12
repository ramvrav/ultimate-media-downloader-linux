

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QWidget>
#include <QTranslator>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include <vector>

#include "settings.h"

class translator
{
public:
	translator( settings&,QApplication& ) ;
	void setLanguage( const QString& e ) ;
	void setDefaultLanguage() ;
	~translator() ;
	const QString& UIName( const QString& name ) ;
	const QString& name( const QString& UIName ) ;
	const QString& untranslated( const QString& string ) ;
	QString translate( const QString& internalName ) ;
	const char * UINameUnTranslated( const QString& name ) ;
	struct entry{
		entry( const QString&,const char *,const QString& ) ;
		QString UINameTranslated ;
		const char * UINameUnTranslated ;
		QString internalName ;
	} ;
	QAction * addAction( QMenu * m,translator::entry,bool permanentEntry = false ) ;
	QMenu * addMenu( QMenu * m,translator::entry,bool permanentEntry = false ) ;
private:
	void addString( const QString& translatedString,
			const char * untranslatedString,
			const QString& internalName ) ;
	void clear( void ) ;
	QApplication& m_qapp ;
	QTranslator * m_translator = nullptr ;
	std::vector< entry > m_languages ;
	std::vector< std::pair< QAction *,entry > > m_actions ;
	std::vector< std::pair< QMenu *,entry > > m_menus ;

	settings& m_settings ;
private:
};

#endif

