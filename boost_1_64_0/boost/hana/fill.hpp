/*!
@file
Defines `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <boost/hana/fwd/fill.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILL_HPP

/* fill.hpp
X77TfH0qXuom995I8FzwZHI7uJVOD/1FB88Jju2/oJsL9Q350+wKvLHRuBr89tG2aHDdM8y7/k2Z/l/pLNfn85KnB5/PX6fPKL9afiW/x9MfNxrPh/zbWD7yRXrpMH76gP5BjwR+JHg9eYi6fkE9XmNex5m/w9VvIn6gB2JPqFt4ucW81hXyMTfA08X8x910/XK82VG8M+HyW/Lrarw1Dt82S+B/+cfP3Q+flLXA7yfre9bDvdrgGN3kNzK+9/z30V0z8AScHDHX8Qt48w2e7quO/FbLtFfpxW6ue40+5zH0/y+RIG/1y0tbmmf+ItYIz8+CJ08bBz7OrIAv9NPsXHzwpP4n37BMfyqzKXi96Cl6qp/+3U2x4Gj9od82/g3epcmrmrV4IcF4LhDPT/hW/mrGsfoW8rfs3uD9krf8/Rjfw2+3fE3/7ld5/RF9n4kX5GUZXCj5m77Rt17ZCi/l0hXjg7/zD4vwFRG/wQKv6NyqG9QZHCx8ma5fJf93y1v1OOMwOudL+GM9on4E/FFPRaM9z1H6XQXyoLU4joHHxtctnKfu+P294FjQXz2fDleq5RtdnnYZ/rxBPnzm+iF/dqCDrqdP9ug/1Ylv6E/x4roz8It6Se7tN5HO4l/xfel94nhiLDjC5aSeeCBZ/yjEiz58ZR29hqei/EQjPTiPn6hRZ3m59PtOeqUUHjTHD6nqDY+XP68+5GPlBHm8KRo83zzzM0T9JYV9czi91brJfPP+iPk+Un31xvenyp8L6LPd6uJEfrWX56NHp7zv9Q7iutH5K43r60iQX8ZTMgZ/Wc9ZuQmfH2kd8xZ6ONM6CF4YMUpd1ODxIfSAvG/qIS/uk8/4MTOPz1ynH6ROMw4yrqfpkRz4fDXdwLfnpXqOJ+RHK+tV+mAr8Xyx9aHcGj6/QP7R7+tGwLPn6PA18DDsn3VQ1xXqfq73z1X39Pvkv/C3fkGtvxdN1GdpqW4m8ed8SNEK/lYdLbyZP15C//2NfzLlw2hxbmnd4hH8t4welF+L3pFv/GP+bD4hkX9y/3T6NbPIehO9lGVdZNU3dOxMOgZPxx7nf0fi8eFR/WO65Df9jFfps9b8Az2QH6GLh8kfPn2a19MuU8d0SEq4PpIp7+jYWdn4rS089FuZRbvo0PZw9fbgWN8teD8VH+Y9xgfeKx7VUfylL07XNh4BNx6jT56WB9PC3+62DmH+6k/GV8n+/kMdnRocF/Y1r7+I10bPq19W+m5En0B//Xz6cRac+hAu49Hp4XpBH77oHviSq2/J12XfjweeMS/qpLxXQnB8ha6YiA+sM3ebRF8YX0U7fnma/Kmlj05Shyeq68edt0+cNsMBfZD83vL1VfWYrj7o/MIp/OQlnle91izk6+yLSLmNHqNLuiRFg+Pr8oJuTi/3+Z/FWf1MG2jcoX5Tj1nJ+iAHh3qEX9sDr/ii4iL9io3iezi9/aZxHuP6xlnTGU7zoel4MvdW+R+lEydap3gXHpivLtfSU9bBUy/HG+Pcdy/8uYNuxF/RCq/DlVm1+he3wqk0uHYl/uRbOvHJRa3pJX3N+gf0sVa6TgM81N/LkFcFD+kztaL7dtLjlXjTsfF3+mYVnjsKzx7PX8PztLbWL6da326jrvF70no67Hf9qdXw4mR8MUX+fqBf2YgHzEvNTHH+Ai8313+AJ7lzrBvKp1Ve76LO5hxnvu1faNmEjx5SD7XieL+6WAp/k/Bbn+BYdzycPRT+qN+V3fHHBD6otfsm0q/n00WZ6mURnH63GZ7hx+6iyxaJxwK+dYfrfUw3H8JXjTHPpfo/o8T9TD7a32l76bXu5o3/z4MXTX35yh/EdZd48R9ZtXzileZvguc=
*/