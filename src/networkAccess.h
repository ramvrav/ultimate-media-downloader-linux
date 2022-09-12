
#ifndef NETWORK_ACCESS_H
#define NETWORK_ACCESS_H

#include "context.hpp"

#include "engines.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QFile>
#include <QStringList>

#include "context.hpp"
#include "settings.h"
#include "engines.h"

class basicdownloader ;

class networkAccess
{
public:
	networkAccess( const Context& ) ;
	void download( const engines::Iterator& ) ;
	static bool hasNetworkSupport()
	{
		#if QT_VERSION >= QT_VERSION_CHECK( 5,6,0 )
			return true ;
		#else
			return false ;
		#endif
	}

	template< typename Function >
	void getResource( const QString& url,Function function )
	{
		auto networkReply = m_accessManager.get( this->networkRequest( url ) ) ;

		QObject::connect( networkReply,&QNetworkReply::finished,[ networkReply,function = std::move( function ) ](){

			function( networkReply->readAll() ) ;
		} ) ;
	}
private:
	QNetworkRequest networkRequest( const QString& url ) ;

	struct metadata
	{
		qint64 size ;
		QString url ;
		QString sha256 ;
	};
	void download( const networkAccess::metadata&,const engines::Iterator&,const QString& path ) ;
	void post( const engines::engine&,const QString& ) ;
	const Context& m_ctx ;
	QNetworkAccessManager m_accessManager ;
	QFile m_file ;
	basicdownloader& m_basicdownloader ;
	tabManager& m_tabManager ;
};

#endif

