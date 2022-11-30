/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0841)
#define FUSION_REPLACE_08182005_0841

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_helper;

    template <>
    struct replacer_helper<false>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, T const&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_helper<true>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, T const& old_value, T const& new_value)
        {
            return (x == old_value) ? new_value : x;
        }
    };

    template <typename T>
    struct replacer
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer(T const& in_old_value, T const& in_new_value)
            : old_value(in_old_value), new_value(in_new_value) {}

        template<typename Sig>
        struct result;

        template <typename U1, typename U2>
        struct result<replacer<U1>(U2)>
        {
            typedef typename remove_reference<U2>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer(U)>::type
        operator()(U const& x) const
        {
            return replacer_helper<is_convertible<T, U>::value>::
                call(x, old_value, new_value);
        }

        T old_value;
        T new_value;
    };
}}}

#endif


/* replace.hpp
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
*/