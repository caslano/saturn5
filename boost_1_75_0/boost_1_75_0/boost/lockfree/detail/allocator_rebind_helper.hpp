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
UqBJMs204mPJn2RnVQbk/r7o1OP6V2mEqknZp0aBX5mT+lFutQJKrU1FZPpKzVzCovTGJiY1+jmiTBORBHf1DJ+7soJX9RoATGswQ7Js1g5v0vXhewBUHDJ29/qGZzW84ioiiVFPYz6af/77QHQqy5RhRfae0WqoLZPRh3QMhvxlTP1F6x7pxatCHlRvPv+wiu6a6LPDCHdvlvSMMp5Tob/TYV8bOyvYwZKBoe+oa2zxBVtpWTmEQYeQK3F31F5LcdlI5zvIxCVBsTTxFO+wHKSw5mvmu9eGo9TO5qpgVOkcI8pTqEQFKwjI+A1sBOQB5Ab6QDENZ3LDBWeo1Q6/xDvH3i326piNDn4+NVYpTO1//FBMvGSq4vrGqZGh8x1+EssPwf7Ds8H7qV6Plr/o+x3HCynMfCkoFNL9ThtL8S7PJsPVwfKgoL/eQIJ/7lMBaoEcLSJrRzSrN2qeg0sehkAuflMftjuqa5+eO3zHDBqDwV+y/I9zMC4H6u40HHmPgEgDGiEr5DUYX3qEr/5i7U++4z+cgyBxRevcb+hOIjL+IgLPQveelgMy/ZRTx/N3WQcBmqAGz99kHY1igu+wkbGH/0rZWQXFAV1hOJAAwYu7B3cIrgnuwd1dF9fFCVCKBg3uDgvBHYK7uzuL+8IusNVpHzptp4/35c69/9v3zTnz47yaSYp2cG9hP9RRaJH/iZ88jp88gZ88iX+r
*/