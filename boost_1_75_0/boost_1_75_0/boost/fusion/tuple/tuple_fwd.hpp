/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_FORWARD_14122014_0051
#define FUSION_TUPLE_FORWARD_14122014_0051

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if  !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   undef BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   define BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple;
}}

#endif
#endif


/* tuple_fwd.hpp
P3m9oHlCu8lBe88DaIV/gJ/LxC34xRaElmQie/julZStfNeuQOtGPmkNefLq75ZSxcaIRcmNDG/fEkEeoCDwjs9M3USFm5sdPimTJQ+V1z095hZv/D3zMf6iQFlHJLYAKdF/NKo9ZF13lidQvRcBJjutLnU5oi6+fwEuPBHuDKKEOzfa5gBkiUNga+uK+KF5pZS26SYxHvie4UvvTbvC7Jevetw1mHJevo8eKZOsPNdMxJrzrpZdfH7evS+J+/5TTutd26WXbEKg/MlzdnyC36rIpFC6HNLM1tR2MrexSF2c174/p9pwISwXDX/gfkk0GpOQboVu114u3AvfTtk6ruCe3G/6h4EQQtrcsBy4lyktmi7LIqjSSv2sK/TppQyHsYP8yVvSxTRPqtOll1eF/wXcvudoZOJ0ZwYssNIdZjeHj/9eWnB+kpIxPwzkszE2kpKcLJDQ7i8mtieyLQ4LrZPea5uq1C/09yV2ckpgnQ9KYyN5BkRm624Rdbve436tYluebzYXtRa9TbrDOxbGWYIvSUgmO7faykuzObuDK8n1DqKlwLvZd98WpM5hL4r+MnILPs4734hXaG/7Oja31hgrb26aYHc73bTjmfsueViiRoS02t6C6K3M5RAuzufnU/WeB89Oyu69kCAqtwalvgi+lp63gwW2vOiLQa549yJWrU+KwGQOvkRghC9ctcMvIfY0jzxcGilkh4va
*/