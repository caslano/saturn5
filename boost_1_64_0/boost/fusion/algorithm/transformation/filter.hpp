/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_02122005_1839)
#define FUSION_FILTER_02122005_1839

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct filter
        {
            typedef filter_view<Sequence, is_same<mpl::_, T> > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter<Sequence const, T>::type
    filter(Sequence const& seq)
    {
        return filter_view<const Sequence, is_same<mpl::_, T> >(seq);
    }
}}

#endif


/* filter.hpp
Xb44astXWYdGMpeRkBqvQX9BT+xmN/2RaekKDHOzm472EVUnZHm+8vaUOLthGZ72Hc7vobEXRo5MWjoE3noT9DlQDiqQJBq4Mtj2lf9c5cgTsMM/LAFqQ+KrGiRgE/+38ZOmCJEsYUBB2J0PIC0eRZr7KWTpSiU8VbhZQvg6oGZp8wf4GVkTEKyfHX4A97tGTWJQpvfeojvoS/yNH6JK/Tuc8TRNynMnLUo6YH+QMkFnXdeYBaFwe6h/8Am2tBGKkTrfXdCqAwroq5mnLU6U0nlFxk0Dn+60QRgLFRUVPlLau4VTQJsqXLxb981Arjq/3oiha8gTNo+Q48rGaVFdFkGFd8i0w5e4Ckq8GoZwiV4ivC5Nqa5o0vzwjX3gXqVwG5L1Qj3USUCUpouZGBjcKJb+s5+FSC3afpOi6hClxsLrW7p/Fh9Rj2xbD49OKokTytAuhNjflOLB8bkyY/7WlhI+qMAqa40YBB3k3lzti4e8D5CwyJ1a77sAIEP97HGreOp/tm2aeoL9soVfF+cGuUNe2b7otdG6l5/UcyWALElNzhz5r1wgck8lYw==
*/