
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> 
    struct member_function_pointer
      : detail::synthesize_mfp< typename detail::to_sequence<Types>::type, Tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,member_function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* member_function_pointer.hpp
mh4ixAEpcGAAqXFYmJwOVUZHnIH6/siMs2AZ545JlBWkiyRPZkmcOdlZnto6ZLPUboV/BpdpHFpyD1S1afv1AZEZZ3qCpGP1xAgP4C+k6r94bgT3/MbFA1fVusPBTe8IDhPqY06nhoougn0V4Ykd4k5x3tJp2RK52SB/PhFUjvyytiQ2+sOQcF5jH2yHeB47U7aU8L7bb/3t+DWzmQreBVEcnERxlK9s5VzX0KXEmuNbjlTV8KI89l/86B9ajUWYLxdzeBfEy9BZUI3jX9n4wiK52LfNUDjbI33XCakNe4dDy/nFPHk/LxLb5EYBueHhcHZGkGVeJGfFZXiZLFYjHr4TjDtItL6uWclMSzWUdKA6UtKBH24WhhDEWYKD8mTxOOOL6F2Qh5+GpDt5eYCFfHQmWObnRb5Kw2y/7fwDUEsDBAoAAAAIAC1nSlI/67HXPAYAAIkNAAAvAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TU0xDRVJULjNVVAUAAbZIJGCtVm1P20gQ/u5fMfJ9gco4BdoCPQ5dLg0lR16s2CmNFCna2Gu8h7NreddAdL3/fjNrB5IUCT40iNjZ3Xl75pmZ9WcuvPtlH8cndfDqZ27/5/jB51ooKNU/
*/