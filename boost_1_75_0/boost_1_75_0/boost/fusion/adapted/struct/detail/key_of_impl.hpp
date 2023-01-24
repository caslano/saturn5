/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : extension::struct_assoc_key<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* key_of_impl.hpp
s/oBbCoNPi6m8gWJYl7f+9mVbYD1uci6zVYP67/jEUFmYgDIRpXfoQn73TtcCyksuEYQqKQgQSlpdsI8ib/WlDRnxTLMLIOy1iuVuLk4AoDwY9MTR+rdTz7RQvwffuqbNtrjvetS1Jlicv0Uf7uRKO5uVn/LsKNm/DJqmblWyxzmNn0f3SXS50LTiGlP5haM6YywmdkSRZP0F02yTS8+Sk2i4o6I8Wy62h4V526P5Rb3VzD3XZpRe8Rb7VGzgtuj4tztoVDccwNRPBDeeHssp/bYYrVHtZPenBdO7QFNIXgSbSKGao/VFlnQFvmjYIJ0Hxwf+ivhrrMAli39ZaeuefwmyXpq3T49wPbo6vr7tA1/Q9dwMBYT9gkCM1FO59WnYm9Qp+wLltPct9V+MQI5iOFWvE7hYInFwcu9iYMvwhpvxSXUijOtVnyDJXxiGLbizHTvZvEJsCyuQrn6SiNgUdFqN2GrpcOHzaBv2BUgWO+/pX5A9bk/YKn1Adt7MX7wOT5gKX1AlfUBu1kkt4TSBwDnad7MXSAFY4OlAKfJQyBlp/iYsfAxx/Mz0lIy92H3V8vuN87d/Urjt2XeCT2TTeZhNpnX0IB02DSbEQED0orgAekG7knwzDjXgHTYem07i+DL6BmRWY2QF37Hf6/rPAfINPhWDd0S04fMCr61g26JmUdmJd9aSbcqcSygW/PpViyOZHTrbbrVzly/
*/