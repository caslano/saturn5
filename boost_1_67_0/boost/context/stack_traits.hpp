
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_TRAITS_H
#define BOOST_CONTEXT_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct BOOST_CONTEXT_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t page_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t default_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t minimum_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t maximum_size() BOOST_NOEXCEPT_OR_NOTHROW;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_TRAITS_H

/* stack_traits.hpp
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
*/