#ifndef BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED
#define BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/quick_allocator.hpp
//
//  Copyright (c) 2003 David Abrahams
//  Copyright (c) 2003 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/smart_ptr/detail/quick_allocator.hpp>

#endif  // #ifndef BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED

/* quick_allocator.hpp
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
*/