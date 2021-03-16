//  boost lockfree: allocator rebind helper
//
//  Copyright (C) 2017 Minmin Gong
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED
#define BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED

#include <memory>

namespace boost    {
namespace lockfree {
namespace detail   {

template <class allocator_type, class value_type>
struct allocator_rebind_helper
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type> type;
#else
    typedef typename allocator_type::template rebind<value_type>::other type;
#endif
};

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED */

/* allocator_rebind_helper.hpp
w+s5zeBYvSaSV5HgTXmg8SXDa4zL4Fi9Jlm81uy8/GbDq95lcKxek5m55pP+y+4xvDa6DI7Vawozn9cH4ftWGV43uQyO1auIvMYLnpbsXW54/bfL4Fi9ppKXvK5rH9l4u+E1Ns/gWL0OJ68pglcfurfU8JqfZ3CsXtPIa4LgPX8rdmbSqyPP4Fi9jmDm2rh25+gFhtfVeQbH6nUkM5/X/etCrxheO/IMjtXrKPKSo9U37rzqJMNrZ57BsXpNJ68=
*/