#include <boost/thread/recursive_mutex.hpp>

boost::recursive_mutex m_sqlite_mutex;
typedef boost::recursive_mutex::scoped_lock Lock;