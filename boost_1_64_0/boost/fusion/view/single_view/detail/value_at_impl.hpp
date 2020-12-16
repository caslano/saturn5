/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
+kWYu0sCNAcy+S4/WgitR4y0teWzLKFe90iAXGzMAS+aWKlnn2IuLM+Od9LvoRp6J8ATkLbx87J/0dr2SYAmLG7S0QEvqS/9EiA2Vlq6/ouuCfN5aN3RdM9t0OzM+PYSRksk0903DlbHudBU83kM4vxoSWS6e1gD04ao83Sj1WBWJf3NQVQ72kNmC07PGE7zDcXzpkna46YjrtN8I+Q279Rt8w4Dc6LNZGaK7zlLWMQgDkaqzYLWMr20p43vX6G48QkQY5ZWdN3u/wrzTaCeoUXv0yE0GzO+38LEBIjESnv2uNhiqn2aekwP2naWS8nYKkk030yD+Wapx3SiqeI8BnEBg7gwmoXl6ZhSZ6Yw75cJUNgkrXQNUzpaP18CtANpx95WvCvMPRePE8xabh92nOZDU8W55iXAFmYdodYl6vV8vPZmxq+9PWjDmPFrb8sCPFf9j6/7AIvqygIAfAFFQJBRkGIdmFFRwKCgohEdO1jHjopx7FgZO8Y29m4matREo1iiWMPaYs/Y3dhIbGgsGEuwRRJ7i3tWOOcd7vfNdb/srP577r3nnHvfezMQZDm0G/3dQbS0b0JFA0/Nql1/8QXVerV2vTZJ12u7wrIVFrXGudnAzjAz+KzXka2F+wMzfn9wKEysc24mhdnAGrlqlppx9zD1dgPbZ/LnKGAhZNIzkcJEunatM8nPpmDO4qxgztaSoYjLVsTpNzqPM4M5i7OD4TWrgfwZBFgis6zfM2+i6TaFipUumvX0D3lIa9lC84FJn0+AlSeTPp8AiyOT9idYNDPed/1WyJ1Myh2M1iLnDvYwP4eGYGnPvL5FExmhYrzQbFjK+HVUF7AQMmm/gFVmxufT/SeU/j3MRmD0cwjALGDhzPheSlPE5SrioraHitbMvLvOXkRjgn3B7GZK+YlUzx3O4+xg65itabx+IOWw03lcJhifzzpr7xbq0S64/7loVuxQw1Ra527nY+p+Kmjno4yD0Wxgo5gde37zC8pvT6h4w+wP67QSlMPeULGMxzWt60lx+0LFd8ziUzofQMsGW83sh1ZPbqNl7A8VZmbXnycNpzEPwH5h1qN+zGVaC1gis95Tdv5I9VTE6Q4WnG/nleYdqC5gbZnx5+RcsFRmn686uZH6fihUfO2iWRvz2SFkjlBhcNNs/3K3EJrvWKhIEZoZf9DXpHUeh3PEjJ8jE5izfW0Do9zlrz8o4sSJULGE96jk8WcUB/aQWd01qdFUl5Oh4jrLfVSN5W559pOb+ZdQcTE/rrHrT25XG0ZeQLOcDhWuhTQ7N7KRJ5o1U7vugmnXXTCbwuwKS1NYhsIcCssEq8yMruVgul/hWs6MruVgJjBncTZFXIYiLlcRp//NeZwFzFmcXRGXqYgTF0KFzkWzG1Hhf9F8F7UzBsbOGIwJFseM7nFg+kvOzaowh8J0l52bBSyaGd1TwdIUlq0w/RXnZlFYGli/Qprt8Hv8HY15I1T8yeL+G1dxF5rpZqi4xOLGjnL7Ac18N1Rkumg27GLFcJrvPtSFWXD45XVoUTnadQmMXZcgB7Bwzdj1BcYEq8yMrktg2YoxdQ+cj2kGczamHSyQGb1/B8sAczZftmI+/UPnZgFztpY0MGdrcYA5W0uuYr6oR87ns4LhNauJfP1UmB1sMLNAn793UO6PncdFKcwENsVFs/u/7w+nuL9CxTeumhWfYPajHP4OFRZma2e/CSJ7Hir82Zi/DOk4Hi3zBdUFTLomv4RrFpl0TQZzFmdTxGUo4nIVcfpXoaIOy2FC4O3jNOZrxZhgTsd8k3du0cw5tmU05lswFsevdeKdczMrLE1huWDnmKUWTliDJj7AtY4Zv9aZFGZTmEM=
*/