

#include "generic.h"

generic::generic( const engines& e,const engines::engine& s,QJsonObject& ) :
	engines::engine::functions( e.Settings(),s )
{
}

generic::~generic()
{
}

