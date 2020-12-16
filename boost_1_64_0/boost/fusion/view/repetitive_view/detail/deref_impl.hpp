/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
np/YQOnQ0jCj82Q0KG6Fccy236zSSrF4tJWsvIIHF/+k74yUtEJ7vbR15/5wk5W2whuWDh/oTKf4ylqhIStv1wX7Vvq+BdptZmN29k+k8VLOSvuOZan2HQkaloj2jFm15Zvy0tit4D1dgIbZNcyhYU4Nc2lYmIa5NSxSw2I0LE7D4jUsQcMSNcyjYUkaBhU1+k/D7Brm0DCnhrk0LAytJ7M6+SOLUHwa6aCSRnwaZtcwB1pDZqF5hl2gMaGRLg5tBTPHwAm9aAxW1hiDGhaDBjpp/eJNBhovIRrjRcOSNAyqaLSnhtnR0rF6vgiJC6T4qmrEh+YUthz/Nrzb7hLFgNaGTP0beK5qVmjHbMGhf3WndtEwlxOv08wOO8unp7qg1ZSG93l3llObaaRzVLdCeWbZaxh/odjRKjIzdumWgeqJVoDZUNso2pNADXW7xHfocJ5iqKFul71LLzWh9aWGOvYdVYZtpLlZ07sl1FTHV6xEzxJUl1rqdnn74rdVNG9reU8XV0vdLpOKtZW/LVdL3S7zbJVKUj1rq9vlcZdAvP0R78ZG2yFsBZQqv9+se6OYq44V94bS6vYMGK1Y2C9WCAZpL/MWmU/v8kKrKtKthIi+1j7TPinmqG+FbSBtQsaeuxULaGCFkyZprcfc+KCYq6noI2G1X4xorLzvKQFtkbBVEB5R6WjD0fTu6F/VlnPJqa/0rqtmVtjFrF++2U0UczS3QgizLL8te0J5ohXXSUv/c/YWxQBfL7MEpJ3KMZTqmYjWk9noTeU30TugW1lhN7Nxee7cVMzV2grjmf3smuswldfGCr8xuxYVT/WMR+vGbMKniHsUX1sr2Jil/DaZaBe0d3ppgeme/KT3fHWwwkwW+/jXLX3J8KC5Mkj7MfV9X8qzkxVCmb0q0qMH1ROtPcuzV39PJcXcXawwn9Vl9+cgK6XrboWvLF33wRFPKb5e2Lcs3R5LjzL07u++VqjL7Mq+9hOob/tboaWOjYlXgUB5DhDjWlip7hXe0BgcaAUdsxz9u1FdAgZhlZktSn/+EvXtYCtcBGlLqpxaR2NiiBjzwqpHj9tIYwmtN7OHrbp8p3RDrZCXGb1PAC0GLYhZym+MiTw10iV/ALkos5T3cYq+HeY9z8hh3vOM/7/pxPff0VzCVkNEOH/HS9hw7D/Rnmvw++iVh18MVwxGijyF0Tt90Zxou5i1dq+V7xoYZYU8zFLe6SvKQzvCTBdQi97z5RpthX3M8s44eIDKG2OFeKO0dTdvzVPMHmWF7CyGrIeG5pHvOLPCZJA2+sWW+VTPaCvcZJbWsi8zlTfRClWY0buH0WLQgpnRu4fREtHyMuPvn4BJ6vbkfeREK8osZUyI78ZPkuWthYiIlPLEXg0tkdmt0LkZ6d3fk3H+Mav5oV5/+g7/FO8Wj9aN2XR3v5W0/5vq3eLRmjN7NsdAvxdpn+Y9hjC0Lcx0KzfEUT2nq9ONfh3XidpFwxLQ6jELu1ySzr3tM6z0bvPkBaJhbMN8tD9Cq6GTdnyX+wDd28RYoaQ0zCd6FN0vzbLCbJB2tJZTnlHPFmNC2NhzUz7IzzLi+OR5rt7fl+oy1wotQNrVx1nlZ5tirbCeWYUpO+nzijDPCsuYXao9tD7VE+00K69VeJ9XdA+90AozmM1ecKEj2WIreEBa7osb6b7OsURcO4Qt+WVVN4phmRXug7RTn5+eobosV7WL6vcbIQ7nA5n693adaEFk6t92jGS2PvVv9KPlIVO/Dz4JrSGzTgv8LNTvK0RbC1tdcdkzin2ldwtYhe3CrOarvgmU52oxV4T9eWvjEaonWi1mY9/koM/62dd4t0i0eJ00z9jZpel+dx2eWTE=
*/