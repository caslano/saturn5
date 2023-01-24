/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/vector.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_initial_size.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_initial_size" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

namespace boost { namespace fusion { namespace detail
{
    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_initial_size
    {
        typedef mpl::vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)> args;
        typedef typename mpl::find<args, void_>::type first_void;
        typedef typename mpl::distance<typename mpl::begin<args>::type, first_void>::type type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_initial_size.hpp
u8F5kbVOPZlDuuEDEcvYnhVWgWLsLCXTbgb6MOtqj37y5sthcrlBCuWk3b2AfMywBqbeWu91D/O6TFhjz7HRfCUWO3RwgA3KANvmnmFirV9LILVfIpByD+uTn2KylG6RNKBaL4n1HObA4y3rEH+rdYNalaxqbuy+rcOHs2ein16wWMEOu3NFwH2dXSG6AYQIOJHOoDMWqP6PIqyuHo6BWbcadGSc2wp1eywTt6pHOrB9TQfDskVsa2P9L7PS7DWzYBGdFL1fZAmUZxZEcfo/ZAeeyiIECFbsbio2dhHiz2mjhC0rxR7L7XqlQbec94BtvqEmHncDxZmgbwnjt9LZAthIEtg7/13DRhJJal5WXHhMrI/L507pcVKV8G1T47n9G7ctVHY5ZXET5DvPpxY9UN4fliG1umiSurIgWvIMdtu+sJVf8gJGxNZuuKxsyXeem+BoIbtvF8XZ8S0r1fmsn0mys0KP3UePrOYTQPbxHxQXxbI5VnkilGr1DlY/d4YSgY8Xr/X+R+GWGGKigt+NjibpIcL92BodTBaiyc5tSZO36naFc0C5A09XsHVZ/Zt2uiJidhgx+RLE5O87KX1OtEt2A+zDXeeeAwYPnPcdokjas/IzFFmjR9aof/BIVY9U1fPz0OvWxENs/9fI7CgQANoa6Ug5JzmnG4R4PWBYoOgqfC/mnESL/qCoBsmwHzwpAL1XIU0Lkqu8i4p5
*/