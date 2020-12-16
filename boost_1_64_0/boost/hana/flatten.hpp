/*!
@file
Defines `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FLATTEN_HPP
#define BOOST_HANA_FLATTEN_HPP

#include <boost/hana/fwd/flatten.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/unpack_flatten.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto flatten_t::operator()(Xs&& xs) const {
        using M = typename hana::tag_of<Xs>::type;
        using Flatten = BOOST_HANA_DISPATCH_IF(flatten_impl<M>,
            hana::Monad<M>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::flatten(xs) requires 'xs' to be a Monad");
#endif

        return Flatten::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct flatten_impl<M, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::chain(static_cast<Xs&&>(xs), hana::id); }
    };

    template <typename S>
    struct flatten_impl<S, when<Sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return detail::unpack_flatten(static_cast<Xs&&>(xs), hana::make<S>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FLATTEN_HPP

/* flatten.hpp
vFK94KVivq+aHs2nZxY2U28n0RNT+MO0RH5Cn5WvTrMOtc46Vb/X1F8r+sq+y8yb7D86y+d/EudGuPCZeVvvufbBmRf0FXvaZ3cTXrIemTVN/+oJ604v46MYnMBnnexbyC7lY4yjcIh+nvpurMPb1guLnqaTEtTFoe57DH1+gTjp3xfoU5dcmEDP2QfXN6Ze6Yn34HmyfeNHuS9fm3spvqWbKs+ivyfot5yrT9MGv+K1LPuUpu2QL+Pw0T//gv2VeHkxfOYfYt3V845EfTQ8bP9f0a3yva28PSRc9zfuX43rd/U+zvpC1Dw2Mx8ZcIZ/2X4LXdoL3mSYryPU83vO3wwXJ9LdY4yPb005C9/zN5mn0+Xr1XuVcYbfOyWvpr/j9XDfcZ6+dx++3r6dOZ6z9KooPQvPnjbf5mdLtuu0drycf+zhvA36FV35ozb0Whc+b0SUz3I8HI43p/db4N1F9G0ivbqc71QfOQe7z42J+k1wejMcG0evNJr3lv6+H158YVzwes5t8rKjPF5kf1wePXULXngjUZ+TLx9FT/Wn9+6AC+/KVzqu+EX4fLj98i+r+/fVZ2/6PREvVsKVU+XjxeqADiy7Xv3wQXNfoHc7yMNwXOoleS1/GrEP4Fp8Zv96zq1wn79vf6frwOusL+VzgzyZAecz6dRivLiKj+ILJ0+mJ86I+N47+xnkUc9m6u+/7ptnXs6DdyfQZe6X934CnWR+YvTBofzRH/DvYsfb1ZG4L2rr7xfpxxX6fG+rl9/peD6rth9+6sCH34QHR6vf3VH1Y9zwr+VO/bMteA9PLgv3a1hv7/kvz/U9X9jP+PtE9O3xzST+ks5sVPfrjuSrB5kv+rrgYn3gK/HlT/i2h7y63jzKp3ljI8H5D1l/gLddeuuLR4xzG97tbBzP6Zfda17u5rf50Bm7zW8bcdhinKfzkfod2Seop/D3g8rd9xp+p5Fu2uj8UdZF3+XrqvmOztax4up8sbriY6tcJ70nnzvA86eYj3Pxd1ZwXFkdrg/zdY+Ydzicf5w4Wvev3q5vNM764BR1MpvPsp8hs7/7Hmmc9tXMLdd/6k7nviyPkuXr5fzcCnV/qH0znYJjQYiPdeZ/rLrZZz7uoaMebea+9qVs5Kt+pVPCfelH0zWet9z9Zk3Af+oz68MQr52/UD+quT4cf9qyDh/SfWniPy8brl0NX+mFVXn8bYXnOxUP0HMpL9GfcL/tFjzg9al/0zP38bfn8TvGPfc5/PqHeBxh3q7jB0bDhcflaSaccZ0a/b+ik+TtVjp/L/2k7svp29ob1LP6n5wsvvpfNSPlwQz+OPx/z5+YV/66ITE4Rpvz19fjqTX6oWPsnyr396sR69nWMeBZzl947Rfr5cvkxyHWyT9w3dZ8Pt6poT+Wnxkck/msOWXiGOpJejmLz+l3djM4ri7e4FvvxhP0wBb9saS3PN9WenWMeTmNLtOny7zZuD50v3l05V3ywT7dwu3yJUv/0N8ll+LrQ4Lj8iH03mvqc5N8z5V/4ly+Gu73EqcH4WeN+jwD/8bM97f8xlzzbh7WlVunXMI/n0pfd+CDKpxHb5ecjL+HWxdYFuos9dfa+N+jC8K8sr9mxHL1+aXn6ysOFfTTbfZhfeM5Jos3PZZ/s7h+Cvdm89svqZeu+mqtxW+nfJqvj7KUrzjbPvF6uH45n3US/qXXW+KXLYeIl/sULTDeavoYf7S/mr54y3pe+P/pnpSna/W1TsWzE+0X4AticCB9N1x7gW+l/zL28Idj+YYL6YKH8SKeq0rAE8OCY9FbeG6M/kG6daWX8WoC//Co86+wXkP/FM8Xjwv1Pb5Rl3RAsddXTnaefdDRbfpc+nc=
*/