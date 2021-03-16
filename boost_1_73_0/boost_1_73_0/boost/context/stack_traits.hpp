
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
bk7+dyQdZ0nmEo3J1Zg5NoZ/wzjYs8Yu06BpLdOYTnkcR8wGycQSc6tkEoj5NTM3k3lIHnuJeUqTOSqP04l5TzKZxJyVzGhicE4Ht2xixkhmAjEFkskixhxcTyZmuWTGEvMTyUwi5m7J+Ih5TjIZxLwjGTcz6/SMZKwr/VZjEp2RzMUaM0VjLteYGo25VmN6JJNPzGZN5gGNeUljPtaYsMb4XJFMlcas1pi7NOZpjXlXY77VmDR6nExmlsYs1Zg=
*/