
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
zKCTI69UZURx8zFuntZ+kGnyMrlwaqnZt8/VbyPu7raD7GhQarf1zUOyCWOqqbunJG0fcLUDYVWtuybcZY/1zEMXmzWxheKmn2/b07Ud8txwOhH2w6CbRuTUV2FecIyOo01rmKPN9M5Z6nhi7gk+94kUs7ZO+r/Ypbr3Dvq1hCl9TO6fbl+VfZQakwcZ4xvEjoFjdXFYMy4mw2z4FXHPfTNmDHQeW/J9nluMLMWF4j6V/l+H
*/