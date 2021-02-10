/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PP_DEQUE_FORWARD_02092007_0749)
#define FUSION_PP_DEQUE_FORWARD_02092007_0749

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque" FUSION_MAX_DEQUE_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
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
    struct void_;

    template<
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_fwd.hpp
3owhtJ02SyGEooHxQ6LYCMB+9yB1UTJxI2cVYInrieYRxodVEreDM5zF4qoHKZieNn6YktYsOnbImnlqoYCbY7Mc8FU5VSsZRu8h7f1ovnr/FI8eoWswMiOjuh8/rBbkHU32ECKusWELwcP5YFhjPRq9WQWwlcqay4gfV0/xFPVIiqS8zLYfNNtWCKixYpudLYVtwRpiRuwyGf4Wr8Hz0iiUrSvfs1KLC4UdhUecIFjmzIDydo3ORdPlYi1iO6PTEebPghCpJfM/3kmWCkI104USCDRDPYUTXQ+fYq5nZgExDAgfIPgd+0iWgQoXK0QPEWOsiNYeG99NdThtzslZRVpHs7AREbcd2BoCN3CdEmOwBX5aisXyZeOG6XKsgTeZtEkC2aJc/dL0cbMxNdpQ1M+47Fvm2y0bwMlY1gcDba+ekgVbYc/wk5iRGyjQ29eNf4Q9QOat1EreD/Z30KG/yxX4u9voNy/NMcmqUNzm/Vc3Grc1S6OnD+CSW7G2mn97RbOVdpcP9XYfFzRbqcQG7dZp/1qNR0N1dTVpIYu3vcOjKJSkDrKzQYtkKAPuffjqfifNwaz3KCbTMHWVJdd/vq9yoHjkhoZuDbiX3KVIOBvUnO3Sosb5kufx8vFVJcNT3k+V/Kq+InXKIqTf
*/