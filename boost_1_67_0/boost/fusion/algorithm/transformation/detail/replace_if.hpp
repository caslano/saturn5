/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0946)
#define FUSION_REPLACE_IF_08182005_0946

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_if_helper;

    template <>
    struct replacer_if_helper<false>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_if_helper<true>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }
    };

    template <typename F, typename T>
    struct replacer_if
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

        template<typename Params>
        struct result;

        template <typename F1, typename T1, typename U>
        struct result<replacer_if<F1, T1>(U)>
        {
            typedef typename remove_reference<U>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

        F f;
        T new_value;
    };
}}}

#endif


/* replace_if.hpp
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
*/