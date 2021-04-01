
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types> 
    struct member_object_pointer
      : detail::synthesize_mop< typename detail::to_sequence<Types>::type >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,member_object_pointer,(Types))
    };
  } 
} 

#endif



/* member_object_pointer.hpp
J9JvisUNA+BEdfUnR+ahYL2zuyYu8u+kh0g2dF2Ju/M0ldoo/bltP4aRLu1kaEuVfodiu9S4ApQnYXTt3gSxAgX3Qb63d5oyTj2/2BgIoOZ4u3w80veYIn7k5QyeUx1Dlfi89nCqo/PNOwlK9kWMs3MC5NMrPrPf1PKLtbo3bZCu10JX5ICBVDYILtie2B3sb9dUUlgQc7Xzn2gcrL9uOw5mk74JMukyxGBLXBIxdOgZ/rWOKKcyoX8bty88l/chKkGi3CKdrB+pO85qaPkohVsMiy3PZo91n0Czu7MHjGbGZXuD4PLgcpxcaTx9B8uplh4UfYDHgTqEgbEyLAF7mUOaaRK3ahb6gpl6nb6u7XFWgOFEyeU16fj3XtZ420MahJmf/Wxq1mSi8rRb30EI7U2IiTysCzLJf8lbavjKCJxoWH3+U2wYEVuRP/aV93u9mROtY1yUwA6/D6ujA34C8zxli6fgWMyQzu/yGkM9pRqVPleeqGLqA3QmW9FscDxY2je44JvUTq23sBgSRTEG59hAAXcVEu1IM7ekPySrGF10WvOF7Fj8b9ZdHA==
*/