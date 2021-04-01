#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace fusion
{
    template <typename Dummy = void>
    struct vector0;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector1 to vector10
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (1, 10)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector10_fwd.hpp
/6SZXQcdd0HxbBTNll/w4zdBXo1zBgJoppecUCGa28drRXzN1GktpMlZ/7w4ibjD4QJjWqH3zBS/sGpU7diYz5XOfWBM8g0ILj/BF4/sUCbODqEdlmqV2n+oQnVUY8iGviUyLqd3J0ZhodjY9aX3QdEtP22TiHI5LcTeVL8ACpnzDyqogkrq8RyKE9P8uGudHXquUHAiaIIlk15pSgJe2oiW2a9ITrYwQIgwA+SNW9KPo7mVBYq+/yC4ex7TruGdqggsbhVhtZkZzyYlk72EDO2gDbnFcqdX3UXUXqNoA1ESR5WRFtLD4yqTroUYt8c+pxxmTQmJ5v9e+GUi1P2zOvk68bCyU9GGfkZC8RqkIUwi5l0Yk3jdWQOxropQZpd9Wqs6XzpAAApXsVvZp78GYKUgb2zZGrcQ53ENsWkSRMUxZ5Sq8veWQOuci7J8orValfQNSGnlMoFedgzBuySHYMlBkkIPdsElHLuMthI8rctu8421E0RJwXsq9tnBTiIQLjSd/CMRsfKT2CrIMM4wFuJ4bdE0Z9XE22HkCl3FT+CF1k7x3y7J4Evl4A==
*/