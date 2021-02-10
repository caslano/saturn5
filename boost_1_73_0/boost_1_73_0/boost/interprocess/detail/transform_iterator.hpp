//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
// container/detail
#include <boost/container/detail/transform_iterator.hpp>

namespace boost {
namespace interprocess {

using boost::container::make_transform_iterator;
using boost::container::transform_iterator;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
YuF0i5wf9I4Q1CS7LlZborPWevCdNvLrGiFVaJ7ymriX5vfBekXKHI31YPdsagc5ZJUXcMGiDtpKU3+Atflt1XWe3cf5IolV/93lIpm8vb/KJnERMQxG0blS4O1Iu/UfUEsDBAoAAAAIAC1nSlKZ2EeVQhIAANRBAgAyAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzEwL2xpYi9saWJjdXJsLnRtcGxVVAUAAbZIJGDtXW1vo0gS/r6/wrLmNJMPY2cy2ezujeNVxk4mlvJ2cZLZk0aKiN1JuMVgAZ5J9vb++zUY/AoY2k13A4+0LwFD0/1U8VRXd1XR+v1lZNS+E9vRLfOw/qGxW68Rc2ANdfPpsD5xH9//Wv+9/VPryrb+QwZurUsetYnh3mj2E3Gdw/rniW4M67UbyzKcu7CVfa8V2q5JL3h23fE/m01n8ExGmtMY6QPbcqxHtzGwRs0h+U4Ma0zs5sh58Fpq7u3ufqy3f6rVWj2XjL7Y1mRcO9MeiHFYD7rQscxH/Wliay59luNfS6+O+rHWMwfGZEgO692zM9rzh8lT7X3N+/uHZTz2+2d/f9XNj3tBE7SRpbvbMTe1msuXhTdfGZr7aNmjtt9oqzk7nnawGdXDrTr/crDPu+u0
*/