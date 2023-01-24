
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED
#define BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename T> struct function_arity
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , typename components<T>::function_arity, boost::blank
        >::type
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,function_arity,(T)) 
    };
  }
}

#endif


/* function_arity.hpp
RDlMJ4KmAzpqhXqEeZEzvZIl7ol142sP45OetppoWBHasCJoWNffRPngZDGuCP24Igzj4r95N6LcPvtMME/zfYan+ZaOZJQeMs+ZjTfQzeDAyKSXt/k31fyQpauzZkiERs7JSMuHQ660aKHaRSuN20JM6skNI8tM3i4nLUSsvU5dSStfyUfjNZJsWMyzvWgxQ7xaM2d53dy1mokb/LEjVX9spF14rNqXL9dRtJq84mkJuabCu/SkLIfbdJQQ8QWzQCBN0zlpuqeHjiSFcUoD85ArEmnkcI3TmO6/lRm8leEBW5nEW4kJbp24LefErc5A3Exs19NxiJFWNAwr7CSIgFBCaOyTtZQfCrqz6URJwLNpT8l/dTa9W+J9NqXmGc6mkhKvsylcsRWUCBVJrmDwvCTeuciKAkt8PBPvVgGMhsytyBH3XMzvP/lz9bvgrXNTH/TRCeMvzy6iZzN/HubPPxYhl7yfHnX02EaP7+mxjh4r6fE1PT6lx/u8mUWLyIn+1nfp9zz+O/lddKrfIl/BC7q/j9/F0iOff55Lrd1DjzsXqTYwGp9OaY9C25/tJvj0eET3A8Cn5zohEMoxYNXzwerNjfLnjlnixhP49fqpxK/XcyzrHYL8+oPtkV//pT3y67ceidWsRQZPJ34dfii2WbM4v45l946LRprvbRXz4ZN6qxjGr28VVjHpKV8Sv/59R0ilWH443f0x4gM0
*/