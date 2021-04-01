/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0939)
#define FUSION_REPLACE_IF_08182005_0939

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F, typename T>
        struct replace_if
        {
            typedef transform_view<Sequence, detail::replacer_if<F, T> > type;
        };
    }

    template <typename Sequence, typename F, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace_if<Sequence const, F, T>::type
        >::type
    replace_if(Sequence const& seq, F pred, T const& new_value)
    {
        typedef typename result_of::replace_if<Sequence const, F, T>::type result;
        detail::replacer_if<F, T> f(pred, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace_if.hpp
bTMhPlmgnp3AQD+QnAoG6ATgJcOylbxyLGIsQK8gSW2Cg4WOwOOM1A/5zTCUTyUDfQm2hhwZzXv4dWJ42ya4cQ7Tj8MjLSGfR3ml629Z2SbTYVcanIl5/kzKCIelv4vvKn/UTOOhvmYD10Tifkn0Ps79dOb5OFNwXUyG+SbgX7Y5WD0BtdJrQ5UkJxzNHtkxnMYbp2EjvhzN8pMKiuBEMP8lqd+knUArs9hZQze+orY4ggIFyN6skENqmN+AXcjmqIz0nJybnNVt7huqZahnZCIpX4nSvs5FqBqyOHGSBTHMJ2ceVKam11dTTRRzQNOAR76UvqKkk9y4khmWzqR8q4E0b69uNPFvmg3LWSpgh1MtrP540AvZlH7DqhYH9ypH243h0CymvGxS5wHgakJTuklsF5dW48hsUiiMtBLplXFf+xBq+80UqrhB02A7KSR6jZSfDY9o+rxQXD+anjflsNQ6S4SjMSRgB9oqvYyuoMx6VhKLzKkoOCCKUJBo87Icx1ZYCOHoMF4ufuXdxdUXZty9Wb2F1dJB0CexRS3T5iu4VzBDGdQsIaP9qA==
*/