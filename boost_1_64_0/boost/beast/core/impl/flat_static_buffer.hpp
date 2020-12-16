//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_FLAT_STATIC_BUFFER_HPP

namespace boost {
namespace beast {

template<std::size_t N>
flat_static_buffer<N>::
flat_static_buffer(
    flat_static_buffer const& other)
    : flat_static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
flat_static_buffer<N>::
operator=(flat_static_buffer const& other) ->
    flat_static_buffer<N>&
{
    if(this == &other)
        return *this;
    this->consume(this->size());
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
    return *this;
}

} // beast
} // boost

#endif
/* flat_static_buffer.hpp
fwWMI5TBL2VRISLqHXOu5O0otCWKtg928TGy3njasdXTjrPWFtm1I176aIhPO2Idkdo3AdsxXGjj2Q4vbSftE2lHonaR8PaOJMv7SfZ04wWDe1flWbyrSizeVS6Lfd0Ki31djXFfxz33+ius32lZ3a33eTXr1PN6bnkQ+zzJb7/PY7r9Po/pan175RTu83J6kOel82aAHbnPqzP2QZD7PKHht2kW4nsk/gV4D1HaWQjW/UM65IrnnuApif9LS8ZcH4Vg02+k66HFcw17QuKRjkH4/3wEX35zPNeWv0m+T9ALcaB+QDPs+xQ/dtlVwlcw78+4RrSTtF8irtLQKu/aNVrSZ2A1bq942sVyLQN300vtH8afoj3d/nVq/kv8l1epuI/ve+s9Xux6w1wIYo+H/KY93qj1gfd4oDHt8YZL3H6PN0TSuccjfVN7vPT1xj0e83OPN0/335X83d/jVfe03uPVGscnyD1e7frAezzmsdnjMd1+j4f0wHu82vXfrz1eC/2wm34JE4GLucerN45BkHs8N80QNecjNojNRrs9HvOnqj3YUYnn2e3xmD9d7fE0Kf9Cuz0e8w9Ue8h/S3ym3x4vnt+xCzfq6YewshdrG6HJEs9n8zOhK3S+7+iKHeKZpvGu53i3xxDWeOLozQOOKcbvZ3U2+IC0OUatvV9tdO+L23Of+YGkd3Ss06LUnvBncs3p2ROyna8hxx7Sea69Ite89V6m6r1J0qNwT9JO5v8YV4bLvbJPuPZ7+dNDpe7OTv/9JW2+SXoFVjrE0Y7bJf6wQ/eSeTV2d/diDevkaKX1dfSDjZSOst+swXNflcp93pkVtvvNbCkrnXFP2acF3OO5JF8a4x66lrLmxbP+3mmsP3Jty5gRrf3aEM8597nQbtYmYMxytWTcFa6jzFrpv714y7fBqj5IW4499q1apG3b4vkebqPTIXcc1pFMrTvPo73ldcXVNUi9UWsn7aU8E/ej7jA+yHfsqdiL3rfB/C7O2WiOv+sTj92k4iYZkyxuDjPpI2U8wg0609itE1ZaiTPpJVWl+WVlK3M9PYsTahm3lrGUWxqs1iLSdTanZ3BuqfRESxt8JSo903JuzkB6nKSPsJ+LfL6HS764ps7BJxvPwVtKn8u98BxcXZP2i61Ls21Eped20GlnE8zOl2joNt+sbZSFbgvO2qZZ6Pp4P1QbcTY202x95t4heoZvbHzmj41PTUiY8WLqOf94r3rUd88WXHPZfDtGXzD4yXnecYfwqbCmu/9OQTjAv4chz8v8eznCfv79Mf3b1muUH6VMq56ms4efZvl5TvrzAw4ALgCeDSwBTgaWAqcBFwHnAMuB9wNdwD8CFwNfBy4BvgWsBL4LrAI2ApcC9XYsBzodaAOwLXA1sCewGtgPuAY4Avgj4Chgjd4O4FrgJOB84CLGlR9OyjyWIxz38Us5DvnaACcAOwEnAnsBzwWmAjOBg4CTgKOBk3nfFwDHAqcCzwVOAy4ATgeWAmeyfj1PLesfzPojgUMNNt7a08ZbZ9p46wNMBw5g3ON3qJ7l9GY5Rr9DfamX2g/YFXg6sAfjtNVG+UGc85PeaKttDvshB9gNONdJ/5rAdcBLgJsY/znjnv6tZ7kbLPq3E+8vnveXwHZ1AQ6iLbyhwG7029idfht70CZhCv1/9qIfyt7AtQYbei6PHBvwUdYfDSxk/afzvvpz/g4AVgIHAvW2n8H7TAdeBRwM3AwcBvwxcAjn8VDgg7xOPWHKd+FeWK9RT3gk8uk4Bnga8ExgLPBsoPATgAmMszzKUuHeLMp7i+P7Nm0Ivs/+fAfYjfFk+if1lLe7ifJeZXl/Z3lvsLzXWN4bLO8fhvk=
*/