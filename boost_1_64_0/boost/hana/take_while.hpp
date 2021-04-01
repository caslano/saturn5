/*!
@file
Defines `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_WHILE_HPP
#define BOOST_HANA_TAKE_WHILE_HPP

#include <boost/hana/fwd/take_while.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto take_while_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeWhile = BOOST_HANA_DISPATCH_IF(take_while_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_while(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return TakeWhile::apply(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_while_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            return hana::take_front(static_cast<Xs&&>(xs), FirstUnsatisfied{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_WHILE_HPP

/* take_while.hpp
off4clR/avYfXrFfmy12xtEgpvpvx7voP1pxkbpBNgyQLEsSDUFyIoFEwYkz9k45M68LrceY7Hp3Mqoot8jxs3XJvVfQrNwKIgiFjuVwRB/N6k/AHyE/e+pYFDoq3tee+Ro9f6LLwd+ND3UQhG6hy0UjxTVVCfQ7GjwlJ0oY/QD0NSEvQ4zHMOZJ+9/zCswxqehaL256DJyFdcj1A0+CHKa+xsFflgOd9zK+r86ey8MH1vzPvZc0g7FXJPwev0F2KkNTYtJLgQNncjHl5EYEcK6TQw54lTA+5xeAwIuMYmGME4FeDkN+IhwXGDGc/bQKNzlVMz/kKi3f6ruD448N9Z5WE10DQhCsi9gfwiV+mw0aSSlJu8mQLcDI/P+HKIlWSimB21B4BS46ZsHj70XnECPrteEiZj3xMk0IUqqBJBNP17VwGBUQhglWfBgcQnEvmrywpuZQKGGz1zSawIuRwC4en6h8z0s9uzE+Ty65F8ag604QbShnYkAO6JAqoA8QTugEkqikyyEQMIjl16AwcvghJeWbxSX3yjrMJTjeechlT0BSALB/r45Chg==
*/