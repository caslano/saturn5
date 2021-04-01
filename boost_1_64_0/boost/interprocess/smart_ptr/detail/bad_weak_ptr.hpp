//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/detail/bad_weak_ptr.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif

namespace boost{
namespace interprocess{

class bad_weak_ptr
   :  public std::exception
{
   public:

   virtual char const * what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return "boost::interprocess::bad_weak_ptr"; }
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

/* bad_weak_ptr.hpp
TcbH/iIjaMyRKx58qSEbQEXABP9VXmodsTVqDY8KbnpNh7br4Mqi0wgcoGeDKBvolRPU/OSWKubr9fTCvuDXQeJYdGlYi2+422q3sTRFdJONtJFS0irfLSE++GFg/l0fPk+ByMWYH+6MADfPgHG6BWcrY2Hv6uWl6KVLjMzknVyHfw/HrRS7wEyFkKKt41Nd4clw+sS0BsGkM4J/SCdSPOqrLNFIKDIq1EGC/vjtOW7Xy3mxLLzamwmVCullZl2xfdRcRANULRmjPw/3Eq0b+X/wIh2RZzEeKFTj6Vpi8rzp0+qmM4hVfxVa14Z07Nc01dUSXG73Rm4BtyE5gSy5y59r89ll6T4/MPVcxY1g+NlUFE2b1IeGvFkkM+xJQQRMYX3iX2FnMnlQTwrZLStVLytUsCuKRWZZwxyfIBPQBOrujrXtiNZHehIj5gENRhrmOBZrzdFr5T6+qlpTMUa68OXIjEfpFttiTWNoqHuk9nR0tqnbkjMGh+6Ww+VBVzPhu5zHKcXITK/bxe4XP0yuAHtsiiYOzY2Rf8WlSc+99OdWXn2wxmjiPFGKaA==
*/