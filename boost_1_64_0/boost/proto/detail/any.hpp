///////////////////////////////////////////////////////////////////////////////
/// \file any.hpp
/// Contains definition the detail::any type
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_ANY_HPP_EAN_18_07_2012
#define BOOST_PROTO_DETAIL_ANY_HPP_EAN_18_07_2012

#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        namespace anyns
        {
            ////////////////////////////////////////////////////////////////////////////////////////////
            struct any
            {
                template<typename T> any(T const &) {}
                any operator=(any);
                any operator[](any);
                #define M0(Z, N, DATA) any operator()(BOOST_PP_ENUM_PARAMS_Z(Z, N, any BOOST_PP_INTERCEPT));
                BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, M0, ~)
                #undef M0

                template<typename T>
                operator T &() const volatile;

                any operator+();
                any operator-();
                any operator*();
                any operator&();
                any operator~();
                any operator!();
                any operator++();
                any operator--();
                any operator++(int);
                any operator--(int);

                friend any operator<<(any, any);
                friend any operator>>(any, any);
                friend any operator*(any, any);
                friend any operator/(any, any);
                friend any operator%(any, any);
                friend any operator+(any, any);
                friend any operator-(any, any);
                friend any operator<(any, any);
                friend any operator>(any, any);
                friend any operator<=(any, any);
                friend any operator>=(any, any);
                friend any operator==(any, any);
                friend any operator!=(any, any);
                friend any operator||(any, any);
                friend any operator&&(any, any);
                friend any operator&(any, any);
                friend any operator|(any, any);
                friend any operator^(any, any);
                friend any operator,(any, any);
                friend any operator->*(any, any);

                friend any operator<<=(any, any);
                friend any operator>>=(any, any);
                friend any operator*=(any, any);
                friend any operator/=(any, any);
                friend any operator%=(any, any);
                friend any operator+=(any, any);
                friend any operator-=(any, any);
                friend any operator&=(any, any);
                friend any operator|=(any, any);
                friend any operator^=(any, any);
            };
        }

        using anyns::any;
    }
}}

#endif

/* any.hpp
oaX7Y/tIprW3/xrWqQAxb9Wgzj4O7vQ6ve6K85rTha5LUHFCP3d2zw7tnh/2oYH/dJaZqikMxM6gjc8ucC1W8P1HZWBU7ws4rxNp3RSqrGsRZhBcc7xfStTfVtQGcKs8i95LDphF3P7u01H7lWhbkyQqq8X+AfspV2cx266fcj4nm8bCtmxKMaLpyG3kfhm1PRNNqvI0KTL3rRwJGzH/vujzdH2Yn5utscrKNOnrWjaEv0n1XevDg/f/oitLWWf4jUJ9hslNsW3mZVF9TZckMB8s1bc7kf/x6KC+Km8bW8kkrm/3wPqKqL6yVTmm0aP6dibqWxrUV9Sgay0aG9e3M6zPv2GIu/Uy3eponsndls62eX8GOp/Ancf1XpDsbFsL5+nK+mh5du4kGLSshnhvjwpwkJicFzjR7jzV+/6Od9g+9tcWwR/Lzk0OJz3Yk4b0Fm5Oyy76U9YhdvBpfZrndTAu1fuipwafVrh1kduwJvgrHBz5zC3vnBlrnPib66sH8NmxSmrjsQAyJF9cPhXHfTP0hyW8Tz/F4w3bjM3yY/nFp4RxRtxZlFqgPoK/LZZ7AAxIAKfv9PungwzSz4VeCFmk/rwHaIe+oT39WcL50EBOYUhnKU7BpYP4xB2bIdnnswfyjAlQbqN+fqOnQawQFnlGEvw7HA5DfhQHH+Ak72x+eBATKbFVrWum0/OGqDCfJ6xRJ+xQXzDgh0Hjy0raafwWsoP50Zp/T8QvF1lZ6zS33r4SlIug1/V2mkR+LqM38ojeCBAeVGFlMbCrHPbO3yd9XqOITyPyssAw8EZoZwHuntPcCWTJV/Y47wsKXnFfKo1Rb0pv8+xkEt6X2M7qphG9Ep2spCpTxe/FQ+KT9J4JtLHvYtnoJJeu/Qe3+d6DNnc6t1XSZVTn2vr0Nhvaswd3ubbomkLb/L+Vp2F5gn2A0+m87zDFP17qbD0PMjGU+Rh5piuXNNqM+vKr9+Vy4cF2yZdTHORFV8zKrxnKgSyUX4uXL4Tya/NyG9p4Hafzgowioey6ruwYLzvU48FCcGVe9+V64uID0rkVH1u3A7vTjwIMQp3g2j42O377T5N8nOv+LKTbnxnjfPIAnJ3HB5zPTMXB7RZxnI3r5wGnP9R6q+CgC/v0FUDf2bdvaDfwkrv6M/cUt1tL6U3xA8MYwCC0JE17kJ6KP9b7Nc55SCUqqUtb6D6Gb59Tds6luRmhYQz3rWB3jUe0XB4uK1UlMleCZe+f2axItovqbEXVSN0mtqA6odljI3LyYmL5AHCco/fJG/J7SyuaSsuirLDePjvMMOYZx1epqNtClnXXCcso5nzoY4hp5Do8cpeg6H3wb3v+fRBMj/GBMJwdDwpnx6leIYA60I7g9kIU76QPUhvgh8DOGOCYUKBPcrN+AeHeDuuiP4NP9RPnAskBO4+dPAt9TfBW6mMJfDDe37U0VVXKdoqP8Lgf5Psz9B181SPicwuOrNY0dmpcUGzwBKMZt15/c5jmfDzlcX3/LsTzxERagO/Kru7LXIT1RWaT8ypYW7fseQ3tU0+8M/IPM1UC50EKd2N0D+hbldI+/s54nWkQ1bOmy4frLI4iG7/fP4jzmGtlmmoYIwGIvbUuy03xiKi+SrStgjWp+rtBu0gxYy+sjnOqu/Biw/heUf8y1VUyLzTWB49Rg9hrzxj0L8trBco+xevj0a54hcTj8gGPtjTKylIPx4h7Zo0Gbf4053GqTdu0zlUpVjdpHfN9i+NKtN+DfStrB2pOlyVqSqVBRxLVWSdp3hYW6lyZUuev3znMoQ47l8zLQaUymVYhj7n/roFPfWoTLWs5GCsWUQ0UII/aH0EJPslH+oC7cV4nTKk=
*/