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
srmHtYO4JyNdjZkDEJIwzSNVKnS0+r12pyj3mH6PMwJPRgvBEbbXKJlq+j6wBHqifql1Vt3jskgSoFv3/pFu/vrb10flo+NhOHU9KRU6RkYGk5jRMAktiQFQl4b4xkhcQPRvusDGLd8vkp16Hn1XwThY03ce4tdw6MZDlFRCC1ZQqSlcoIlajMBoZtdCgBVIaelGwqvRuH+p09VU4GFKiPhQK6FDdWxJycl6hhrobtwa00GsUkAcpxTq+I3Owp7V07goF66RfVM1Yhs6hqvlCVp2rKgCOtWbWtO+fDrxbhGyXS2sdJ4nKSu2DubfcW3GJRchHcbz/siJeicpbVjfrZTHvNL9sz4gjqsoohNkero57z5xWdo34haCiydOS06ovf5g2P/Aya1ckNPzC4zBEJSqjyt2GifhMtjn/fY3J1yLC4i1MopoDwO1UwL/w59ggykRvJodgqYyOjv6OLUWWtXHWmhNgluq4pyETljpQWKSyWK0uCWVo6oTUHpWrmGnFx9gKdFL50K5BJLUE7M3ihN2uzMExsMnwNlFep03l2yhsw46kdsVa/C8WK9FyZFoDgZ+z7kYp5ZIwuQaMoSku7BvXiig/3fKa2kz18EiXK+mnmK9CLiSDZkn1XpT+JfFqbYKqcaGcMGCoaP6
*/