//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#ifndef BOOST_LOCKFREE_PTR_COMPRESSION
#include <boost/lockfree/detail/tagged_ptr_dcas.hpp>
#else
#include <boost/lockfree/detail/tagged_ptr_ptrcompression.hpp>
#endif

#endif /* BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED */

/* tagged_ptr.hpp
SlKcNiVhThsAAMJlAAAgAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfZm9ybXBhcnNlLmNVVAUAAbZIJGDtPWtz20aS3/UrxsxFJCTqmc0mlmxXFJlKVLGllEjvbjbOsUBwKCICARwAWlY2/u/Xj3mC4EOOs7VVd9yKRQ5menr63T2D2YOdT/fZEjti7WdI/w3hA39pxI9F9quMqubew+Hvgv8Ho97C33WTHAg75PdhINYP+V10aMhQzfIMvw+H6yZ6i7jhPwc48u0Qv0ILDMOR51n+UMS300p0zgNx9PTp12JPHB8eH3bFyzCNZSL6lUxHsrjtimdjavlmGr5/v1/KF10hKxEm+wrUYBqXoswm1X1YSAHfkziSaSnHIizFWJZREY/gR5yKairFJE6kOL/+8afLq++64n4aR1ME8pDNRTnN5slYTMN3UhQykvE7hpGHRSWyCQwH4OO4rADgvIqzdB/mlqKSxaxEGDh9mJSZCN+FcRKOYKKwEtOqysuTg4NoXiSA/cE4i8qDSC9/f1rNzEp+AiRm4YPI8kpUmZiXsiuwZ1fMsnE8wb9AEGjM56MkLqddiw1MlY4PskKUMkkQFoyLZcloS9FX5OliN5EDxnGFf8osLXGq+2k28zoCHRHKZF6kMBHQATqNMyBz
*/