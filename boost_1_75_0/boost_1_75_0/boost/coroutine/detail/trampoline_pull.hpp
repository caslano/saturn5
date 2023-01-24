
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline_pull( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

/* trampoline_pull.hpp
YrTrfoQe/EF5f+utvTtudmy67A0REG+a5i4o5h9XHUXrKtRdcFp7rR+X+GhR+UbPmcmhv0zyva81vdYlQ+jG2700EdWLxAHixRM1Z7Hto+9vsgp8ZZMge/AnkjB94ronaSZFUE3kiBTD7u/O8Dop1l1rOmkQle1CzqxlLZN/CjIIScU5RVGb7yc9WAqZw2fCPuA/0vd9GyclYT5In/PIP0SfzIEsVb/EiZNWKfMa0HIeLuDg8dYfYsn54jy6gGK7HDExJRE+tFIrs44NS5xSynxQkXyeuDqXmDyMMrVpdF8lWJWz72rWXau2Nzmyxtf70aVdwitA4DvqME9QxwpjgM2wjkKqpWPybq0ZYYxVShV9hO45HlodyRYunYgA7nzgO8tT/bbrGwAM1Y4SQUl58T0Pb5v2uQKXfOjwn8YfiPrFwIspFW3bPWy8xao4o1twbxcUirhtvUGqUapeyiyUAmLwjMo/Q0mtK1714CaghreJfLtnr03SUU9Os3hQCCIIlBN1AHIiB5Whrqabpkn7rh6XKlBSC6l9KCHNZ1QizgDkVqKtEIW8aExC0dNiNze8RNJqefmWrq+kokA7tm+XLOueRaN4MiZRzLQ4QRDuHSmddeQzin/B/IIoXv+cBVU01ancZIPkHNuGpFe5P9LHRP+Q2vTm7hR2M7dGat89e6KpJkNsNjV5UPSePkLX/xR43E9kOD/R/xM4x38K
*/