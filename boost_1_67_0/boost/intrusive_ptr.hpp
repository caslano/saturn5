#ifndef BOOST_INTRUSIVE_PTR_HPP_INCLUDED
#define BOOST_INTRUSIVE_PTR_HPP_INCLUDED

//
//  intrusive_ptr.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

#include <boost/smart_ptr/intrusive_ptr.hpp>

#endif  // #ifndef BOOST_INTRUSIVE_PTR_HPP_INCLUDED

/* intrusive_ptr.hpp
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
*/