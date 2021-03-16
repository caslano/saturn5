//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#if(defined(__GNUC__) && __GNUC__ < 5)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>
namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into  boost::filesystem::path such all char strings are interpreted as utf-8 strings
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif

/* filesystem.hpp
Hoi1UYxMV4oJz4oczMXOKxLfykSzzUgTQrRvb4ktPx/zttE7Xs7EJzJUqL/Pn+FBX3oRy5lWjqrx1Jn69HIpqW+LJHrF1Mx0JBFLnO3iaEnfcnWNRamZsURztOVsMYicF2fOK5LzMZOmuvwd/2rqXOc0c6cpnIqmU81nYk5KemYhcnZ8pOLpXJHtwxsInn7MxGNizF2UW0mfHKcPQQ3Gj45TaxA9XpZkw4ePOrDrnZ1P/I/9yQ31eSNWz3mlMfc=
*/