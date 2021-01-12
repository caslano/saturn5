//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_SYSTEM_HPP
#define BOOST_CHRONO_DETAIL_SYSTEM_HPP

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING

#include <boost/system/error_code.hpp>

namespace boost {
namespace chrono {
    inline bool is_throws(system::error_code  & ec) { return (&ec==&boost::throws()); }
}
}

#endif
#endif

/* system.hpp
pai0cntrWpO/SawpHVbseCLHCv0knmnW3BPbjV/swzpL2JpRx9NH88DT768mBhPraTbET/g5j2Xan+lzHrq+JuI+S97H/Lt91m/vn65I+e39E3HKdc31fuLa2s8n3S9BXdL+KLKeaf/z3NHo+e87Xzj6CtWnfuk+fxL9/HNfI6aZtsdNkcuyqA9fSf9UXDjE3mc3bFDkLvCK7rOyOuuP+Qy4xqFtcIb4Hz5+7BWl7xE4R9z/
*/