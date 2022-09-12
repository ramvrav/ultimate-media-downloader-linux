

#include <QByteArray>
#include <QJsonArray>

#include "../engines.h"

class youtube_dl : public engines::engine::functions
{
public:
	~youtube_dl() override ;

	class youtube_dlFilter : public engines::engine::functions::filter
	{
	public:
		youtube_dlFilter( const QString&,const engines::engine& ) ;

		const QByteArray& operator()( const Logger::Data& e ) override ;

		~youtube_dlFilter() override ;
	private:
		const QByteArray& youtubedlOutput( const Logger::Data& ) ;
		const QByteArray& ytdlpOutput( const Logger::Data& ) ;
		bool m_likeYtdlp ;
		engines::engine::functions::preProcessing m_preProcessing ;
		engines::engine::functions::postProcessing m_postProcessing ;
		QByteArray m_tmp ;
		QByteArray m_fileName ;
	} ;

	std::vector< QStringList > mediaProperties( const QByteArray& ) override ;

	QStringList dumpJsonArguments() override ;

	bool breakShowListIfContains( const QStringList& ) override ;

	engines::engine::functions::DataFilter Filter( const QString& ) override ;

	void runCommandOnDownloadedFile( const QString&,const QString& ) override ;

	QString updateTextOnCompleteDownlod( const QString& uiText,
					     const QString& bkText,
					     const QString& downloadingOptions,
					     const engines::engine::functions::finishedState& ) override ;

	void updateDownLoadCmdOptions( const engines::engine::functions::updateOpts& ) override ;

	static QJsonObject init( const QString& name,
				 const QString& configFileName,
				 Logger& logger,
				 const engines::enginePaths& enginePath ) ;

	youtube_dl( const engines&,
		    const engines::engine&,
		    QJsonObject&,
		    Logger& logger,
		    const engines::enginePaths& ) ;
private:
	const engines::engine& m_engine ;
	QJsonArray m_objs ;
};
