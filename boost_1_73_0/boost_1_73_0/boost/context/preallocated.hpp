
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PREALLOCATED_H
#define BOOST_CONTEXT_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) noexcept :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PREALLOCATED_H

/* preallocated.hpp
Wolecv3pvPPmvPMDHvDdQkm7X1jluNL4A6gs9M6uadT90BcvKb87JZUyuizJwpmtdDoC2iOz9dFDC5fhej6foEq7NDEytl7r7HY0nswGM/EnnUZJESt6x26UyNz8LLzFyOD5U++O+A2dbICZBNB5wTPAdCNzOlFpdPzWW7zsz3rTwWQ+GI/ERKIyMhxBr6yLrUod2UxFALVO18Ae2gXCQDnu0JR/jtHR90CQmClnPbIik4IjXI20bhSpzJ32g9QFbZRkSFrWrT2efCZy9Z9CWedhL6r0cdK8LSiTOGIzVEDBDwVB0JU39Vw3UFsxBFyrSpsZPq1lkuzJFllmcnhp1YPKZQKUr1YqZ5+qMgHuVajsSKZS/ipQPJ+GoAExMoWAh5YKTi0LnbhTncLsHDSjwVAZcB5Jjx1KDZ994IjQokvjm0IuTeGCUp9roEUma5OjZ7bW85pgktNRkaA0VThsKq4DadfPEZ/ZcSE/q9ycJipduw1xCwejSgAydNRqHfOttPe0QjuiDC9Vygsxy8VlsFxhqRENLIkq4MqRZtaQhG4C2kkR/YNKwIvM4xFMBUyBD2TkUA4GSo0rwzFaz+mHAkBS7GQJGT5dYaFDV6bIGweZtWpfLuhuNdAxl93t71YTZmaMLZQxNenpodJt
*/