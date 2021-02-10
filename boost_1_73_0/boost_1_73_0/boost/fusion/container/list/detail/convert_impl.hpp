/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1215)
#define FUSION_CONVERT_IMPL_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_cons;

                typedef typename build_cons::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
6nU15rRVSP77VDJQR7qYHjHT9nCFGD24DOPyU5t3JTUvz1omDP38uaHdX49/abtlFe5FHHp3aSNW/Y/j79o7vp4cU8WRc8ymbBDZT2b2EM2AFOYPDdb+CRK4+WP4sSqSfGQFj8xdG1CwrGB8Z2A2yARU3UTLSwMPNmuK1/Gt86Kn5l6bL3pqHuAWX/A07F8O/2dw8XL9S0zSrT18078Y3968dN2Thumhlff2bkTVAV7/5oe7d4PROk7/zCSnSxJJ4r7jVPwMydpzZYLJyvNfNWKebbx5zyldalZltgz+i/1Y12/l0eQdebvYn0XKNMdh+DPQbX+f1JrlN0r/eYF++A3mWQZ2i7gqHrLErhPZ0H4HsXnYs/VB61q6erlfM8V5P2H63VehuB3tSUSXGeVdyMr/zhTotZ5VA2GWs2X/BB3H14YMdva/6+Xc3fr8IQWrg5f4Ohv0myZhHHAaz74mTPIxlfV1MJ8F6+bdxq2+AU52GV313IelPcMspoN/nFPYIWkcGdtkKjyE3wln4iKZRy1Lk/ZX5zm70q/Edqdfle1OH2c7933dDpZFdrRv4qZB/dO/kuPg9S8ubkC1Xg5Gv2zy52mdP083+PNLGNLeYfRP3RuK/mnb3pR+Cr+eVgwLH6H3V+fX09+gBGH+
*/