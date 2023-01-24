/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_LIST_FORWARD_CTOR_07172005_0113)
#define FUSION_LIST_FORWARD_CTOR_07172005_0113

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define FUSION_LIST_CTOR_MAKE_CONS(z, n, type) tie_cons(BOOST_PP_CAT(_, n)
#define FUSION_LIST_CL_PAREN(z, n, type) )

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/list/detail/cpp03/list_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_LIST_CTOR_MAKE_CONS
#undef FUSION_LIST_CL_PAREN

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    list(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : inherited_type(list_to_cons::call(BOOST_PP_ENUM_PARAMS(N, arg)))
    {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* list_forward_ctor.hpp
Oa7zXDuu8tIu2G9dW9dv3XjTrwF+6xNFrvzWsToMnud0ZDS40478Xm/nfA3CJ8slnh686edkDQL2v1tiHrBfg7hU2xBMvbLd2RrEqpb1rvGnZLpbX3yt1q/+9edIZXXg/3D9ua2b9edID7L+/HVHd+vPbVUu1hvfrmmIdWn5Y/3rjVILjA19C+dYuPmK6/mPGmdYgOMTLF072WPh7I2GYGHcNmdYWNrcDgsOK1GJr7AYi7xn81+jbLXpHrnmx8OsHpdImCVBmNXOB4dZ39cGQZj11E0cZq0YE0RfW/i6moRZkk3351U/EmZJlqIjJMxKAqAlQa90qFfsQIAsMG03EBeQfQH/1doEL9X8qMICL7e0wwLHyw7RdNnhcTigz8VLNzo+s//+dT94/+s7HN8cgfomooBUeVk8A+IOxfU1+5xvRqbUU0h8eOCgL+omiQqM2DaadQdlvK5i8bzvGpyGo8mbA1YIdTMGxTKZU/Hh4zjkmuxJXpIP5CtA2Zfwk6GYFrpq9FQH6F0tXuszyiXGiGLNJnUfzaaWqoifs9XQKdSfi6jPL+IDCKADXhBR8xM9C5G0qMIlG2QzdvzNs8DGa+YGwltQ1M6XKisRv4LeJSt61x70DgtDs2AjvMP/IlTtj6t+7hoWoo+O8UWGY7fJOsM0u3WGchDgBTu+ooIbWUEmEL9rWCAdPMgKYHL2BGx/oGP/ae+Lm/tM28jm
*/