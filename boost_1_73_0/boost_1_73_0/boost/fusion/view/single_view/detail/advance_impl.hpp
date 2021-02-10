/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
LZT28LYMD9IReF3pnIynAtKjIJ87veIXbRAUodQVIZteLceTnwkelM5VJHmyLbyybVVAyXuCo5z0/ZqjkS7Algxn8kL7wIRt0NYMWJsQyNU+ckR5WXkLeS91JVcsJANUCI3/mqZ56yp2nxY292n+cvyBCvXrSZZsopZPsE1AsGg9JYiZCWpb6DLOXBDebNpVpb1Ktm5YyhSpdfBUVZGLcZr82jZhvilPEtPQsGMd4uSt8VHqQdn6v0SuY2QpW2dYiOvASYXlMido+Q/luuTu5C8Sm5p2BX63NVu/BaxhM/g0nGM8/4SV9NonuBkvRtPrBW6Gs9lwslhi+gPDyTKSXY4n59x6zWIO9Ng48izuoOum0lRsND9upL3enjZ51RaE09i9dQvVWe/11ni9LsRk+nvIlwYO34itI8BRT5uAjElETi4IZX3IFeV/93NuQ0CupEO/lrwpGhm4uib2fxuKACNrOvjGFsjwTwJp/72rC3yAf1BLAwQKAAAACAAtZ0pS+9V9qesmAAC7gwAAGAAJAGN1cmwtbWFzdGVyL2xpYi9ob3N0aXAuY1VUBQABtkgkYO09a1fb2LXf+RUHdyVYxDYknaEtDLQMOBPuEOACmTQrk6sK6RhrIku+kgyhTe5vv/txnrJsyKO9q2td
*/