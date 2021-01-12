
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
fFjXMED/3jOYyWF+1PW/W93hdwXHPr014td/Q/1fW9czYZnHn57y9vGU/hP2V2nkWvv0wQEvlq3r6bSu56uyludbBuXK34tkXc/W5u/4kCJUmBs1kLTDeW7Tw2QYCkfCSnAiVOtreiTpFzisr/kK8dTxEQyDX8B4+CWsBr+C7eAR2AtegH3hRdgPHoW3wuNwIjwB75N4D0i8B8WeL/YZmKl/j2WulHoFy7kbH77r2A4YBhvB
*/