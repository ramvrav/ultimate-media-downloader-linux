

#include "tabmanager.h"
#include "downloadmanager.h"

void downloadManager::uiEnableAll( bool e )
{
	if( e ){

		m_ctx.TabManager().enableAll() ;
	}else{
		m_ctx.TabManager().disableAll() ;
	}
}
