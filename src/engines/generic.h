

#include <QByteArray>

#include "../engines.h"

class generic : public engines::engine::functions
{
public:
	~generic() override ;
	generic( const engines& e,const engines::engine& s,QJsonObject& ) ;
private:
};
