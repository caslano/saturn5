/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_KEYED_VALUES_26112006_1330)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_KEYED_VALUES_26112006_1330

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

#define FUSION_VOID(z, n, _) void_

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_keyed_values.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_keyed_values" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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
    template<typename Key, typename Value, typename Rest>
    struct keyed_element;

    struct nil_keyed_element;

    template<typename N, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque_keyed_values_impl;

    template<typename N>
    struct deque_keyed_values_impl<N, BOOST_PP_ENUM(FUSION_MAX_DEQUE_SIZE, FUSION_VOID, _)>
    {
        typedef nil_keyed_element type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct()
        {
            return type();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_()
        {
            return type();
        }
    };

    template<typename N, BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_keyed_values_impl
    {
        typedef mpl::int_<mpl::plus<N, mpl::int_<1> >::value> next_index;

        typedef typename deque_keyed_values_impl<
            next_index,
            BOOST_PP_ENUM_SHIFTED_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>::type tail;
        typedef keyed_element<N, T0, tail> type;

#include <boost/fusion/container/deque/detail/cpp03/deque_keyed_values_call.hpp>

    };

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque_keyed_values
        : deque_keyed_values_impl<mpl::int_<0>, BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>
    {};

}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef FUSION_VOID

#endif

/* deque_keyed_values.hpp
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
*/