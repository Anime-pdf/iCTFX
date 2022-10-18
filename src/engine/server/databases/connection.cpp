#include "connection.h"

#include <engine/shared/protocol.h>

void IDbConnection::FormatCreateUsers(char *aBuf, unsigned int BufferSize)
{
	str_format(aBuf, BufferSize,
		"CREATE TABLE IF NOT EXISTS `stats` ("
			"`name` nvarchar(255) PRIMARY KEY not null,"
			"`kills` int not null default 0 check(`kills` >= 0),"
			"`deaths` int not null default 0 check(`deaths` >= 0),"
			"`touches` int not null default 0 check(`touches` >= 0),"
			"`captures` int not null default 0 check(`captures` >= 0),"
			"`fastest_capture` int not null default -1 check(`fastest_capture` >= -1),"
			"`suicides` int not null default 0 check(`suicides` >= 0),"
			"`shots` int not null default 0 check(`shots` >= 0),"
			"`wallshots` int not null default 0 check(`wallshots` >= 0),"
			"`wallshot_kills` int not null default 0 check(`wallshot_kills` >= 0)"
		");"
		);
}