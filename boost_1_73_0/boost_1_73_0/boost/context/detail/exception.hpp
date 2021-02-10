
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCEPTION_H
#define BOOST_CONTEXT_DETAIL_EXCEPTION_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/fcontext.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

struct forced_unwind {
    fcontext_t  fctx{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool        caught{ false };
#endif

    forced_unwind() = default;

    forced_unwind( fcontext_t fctx_) :
        fctx( fctx_) {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCEPTION_H

/* exception.hpp
TMmhEBWHQTi9HE3+6sJ1KbKytbOWDehSNlUOJVtxUDzjYuXMLJkyIAu0gPZzoQ3abIyQtY/uORiuFro1Q0GwSktgKyYqlqI7ZqA0Zql/7/WyRlWYSS+Xme5lm1L4pVnsZHWJ0SzYGuTSgJHQaN4Fku/CQuaioCuWCA+XTVoJXXbvwkKHdd6TCjSvqtYcqgquXQocorZaXZKEJUYvDF20rDV5uy7l4oEglrU1VDSqRndYFpTLJRa+C02dc2XlbSE2Xtoq25J/p2V3secga4wKOkEEo6gDKdNCd+HzKD4Lz2P4HMxmwSS+hPAUgslla+/jaHKC2BDoVQG/WSquMQoFYrGsBM8fOP+pk+758RkMzmfjcBonwTiOLgbJIJ6N4Qg6b+CUp4js/tsOdCqRUuvhV/+X134fD+gu4UyvE80NNRm/iCeNJqMzmASfht5Tdq8OsJW1UbJCkJkDvcog5QhXIZVVjC4n4TQaRZ5fF94LUWdVk3M4Jm8Oe+V7z3uR80LU3AbeGp8Ng5NwMr48HY2HsNc/Pj7cf0rsrH9v2kns6Gmxwx2x10+LHe2Ivdn3bNaZxKB3K7RHT+BliZCtELlPVKcLlaznkAqzYPrL/jvPL4StyskwGsxG03gUTrypXDYVwyEhiFr5q2LUqlwV
*/