/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_20060128_1423)
#define FUSION_EQUAL_TO_IMPL_20060128_1423

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        template<typename It1, typename It2>
        struct zip_iterators_equal
        {
            typedef mpl::zip_view<mpl::vector2<typename It1::iterators, typename It2::iterators> > zipped;
            typedef mpl::transform_view<zipped, mpl::unpack_args<result_of::equal_to<mpl::_,mpl::_> > > transformed;

            typedef typename mpl::find_if<transformed, mpl::equal_to<mpl::_, mpl::false_> >::type found;

            typedef typename is_same<typename mpl::end<transformed>::type, found>::type type;
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_iterators_equal<It1, It2>::type
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
6RsDWcjmp9+cSv2NBVIGkpNyahFJ73dxHBcbXjHvcYQDvAGpuHf6WF0eSk8UwriMHbZRKSuKXaZSuZcCXS8cvoDKXze86GSpQ3knhTCB4JCQAqBKZQltRy7gfjaGcOfznXWkOaj0mbTDaD4/rEKCzMi0s00Ah48nBH5OgUcVREQiBX6BZbMUoMrCtAEZF8tonX63Igkcmutp4ErJKoyOQsBQoeT1yLvv4JqQ9AJuoMa/dn0JvRikoDotikx+Brt6rJjWpClFBRMVt9zduaAc5iqMR1i7BeVz7jUYSsv6VgJVl1wfSXGHHbTSW9nNwmlvgwBRvXZzf8lDKTvKR00jqLcwWo2hZM/FR00+GWLIwGS/uoUb8d9u6tmt7WS0hBd39dyj3OorVp9i1vZ8SnwORpgW/bROQMZdC8OrElf1Bz10YQb+An3AT3wl4wAV681nM0JMSOWamhSjEguR9IBxfXYqhEE8D52bVCJxa59GjnVWbrK1+TOdYVJ/fTLVcKx2sDjWlfL2VfWxs1LoKyFFf+ldtxWXwI+G0YBTZro02FHiEoy+yTGmUc79/g==
*/