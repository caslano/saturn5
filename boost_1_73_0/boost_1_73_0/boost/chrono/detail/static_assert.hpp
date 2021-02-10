//  static_assert.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP
#define BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

#include <boost/chrono/config.hpp>

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(BOOST_CHRONO_USES_STATIC_ASSERT)
#include <boost/static_assert.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) BOOST_STATIC_ASSERT(CND)
#elif defined(BOOST_CHRONO_USES_MPL_ASSERT)
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    BOOST_MPL_ASSERT_MSG(boost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
//~ #elif defined(BOOST_CHRONO_USES_ARRAY_ASSERT)
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static char BOOST_JOIN(boost_chrono_test_,__LINE__)[(CND)?1:-1]
//~ #define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)
#endif

#endif // BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

/* static_assert.hpp
EEQ6DRp19tA/0QMVO34TqPSIF4/pr4CIz8Ym4Z8u9g2+PxoLXgj9scl0vsAjpF73y0Q23IxAaFwBsGZ+77tstaHxdwjf8abd+juIUtU0aTYYUH80m+BKeX/5IH7qgWiIYG85qcvuGmr2HpghJuke73n9vL8wD2CbraaXiz1smP8DUEsDBAoAAAAIAC1nSlJ4sCGTbgQAAH4JAAAuAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfZWFzeV9kdXBoYW5kbGUuM1VUBQABtkgkYK1VUW/iRhB+968YuS/h5MDlrg9NG51KCG2scoAw6SkSElrba7zNsut61yFI+fH9dm2Ocol0eTiiYHs9M9/MN/MN/VVI737YJ+i7cPTdz9r/r/HB9eA0r/U/PLOvO6zXz9T+wXGF6xugBnT0el736E1ez3TmvdYd1pW7X6/fALdySbqvgXNerd0tTlrPzn+kq30tNqWls1GPLi4vf6Fz+vD+w/uIbpgSXFJiuUp5vYnoKvcnv5fs6alv+KeIuCUm+ycBl6UwZHRhd6zmhHspMq4Mz4kZyrnJapHiQSiyJadCSE6j2fw+nv4Z0a4UWdnF2euGTKkbmVPJHjnVPOPisQ1TsdqSLhAB8XNhLGI2VmjVBzwny+ut
*/