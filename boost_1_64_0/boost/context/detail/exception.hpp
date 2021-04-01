
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
PAmuLyzDThWGtGyQhlryELcqwfZ6ChtLuBi6HpXniOyVrl+XUrrEAasqRhv8rSTzgwI7zyOBGRY5GD4eKPrF5kicoD+Mh8/4tIAMSYJeBke4y3SVV7YxRkuH0bO35aJ5nELVac6SXZcLoChOYJY/avmhBrDUaQPN+hbzwiu18WcF5AAeGjwMu+hETWwPtah7/OtGRAzySoughKHA0wFPOazr5YZcshP1HVmMCTNyQXUlSS8g1dEZJ/P2fbB3h52aeHUHfDXFCCA9/VjMJXat0ND2OjWMz8anKoBx5SIE7WoSRzChaLKk6xLwzvhQjOocl/ufUhU38UENbjZxqXAypeugGE4+bF35VvbEQOp7ah3QDTtbZ+IUXWisSaFTlbojEJ11XNlombj2T98vUpX86wZf/86CfnLBEPa5eP1PdUNG+6kHRfX/ik8RY9QnltH+84wexXBe2jnDvUMCMMVLtH40a1vG8ccmZFNkrMh38u2CdmKd8GunAXRPcDXnB4jRliKoa7oRWDAKXPK7UIo7AxbjB1n8BjUlV40bQvMS1gqd1cCr6ybIgZy4zQ==
*/