/*!
@file
Defines `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/fwd/lexicographical_compare.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys) const {
        return hana::lexicographical_compare(xs, ys, hana::less);
    }

    template <typename Xs, typename Ys, typename Pred>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys, Pred const& pred) const {
        using It1 = typename hana::tag_of<Xs>::type;
        using It2 = typename hana::tag_of<Ys>::type;
        using LexicographicalCompare = BOOST_HANA_DISPATCH_IF(
            lexicographical_compare_impl<It1>,
            hana::Iterable<It1>::value &&
            hana::Iterable<It2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It1>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'xs' to be Iterable");

        static_assert(hana::Iterable<It2>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'ys' to be Iterable");
    #endif

        return LexicographicalCompare::apply(xs, ys, pred);
    }
    //! @endcond

    template <typename It, bool condition>
    struct lexicographical_compare_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::false_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return apply(hana::drop_front(xs), hana::drop_front(ys), pred); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, bool is_greater)
        { return is_greater ? false : apply(hana::drop_front(xs), hana::drop_front(ys), pred); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::true_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, bool is_less)
        { return is_less ? true : helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const&, Ys const& ys, Pred const&, hana::true_)
        { return hana::not_(hana::is_empty(ys)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper1(xs, ys, pred, hana::if_(pred(hana::front(xs), hana::front(ys)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto apply(Xs const& xs, Ys const& ys, Pred const& pred) {
            return helper(xs, ys, pred, hana::bool_c<
                decltype(hana::is_empty(xs))::value ||
                decltype(hana::is_empty(ys))::value
            >);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
54pe4x7F5QhPRcRhEth5afW7WxBToe5XpRcMjVA41FtOwGMpHu/neEqrwC3sCltglbJCvoBHjZ5SbbZQh40LFkU3y+rb8DHmCgyKRXQevyUmfyte74iPQ5oQ1ITqrulQH++g9afRR1fkTESaJeykamjMiMWTIw9jnO5JeeZ9fIbZRyRQq9LYzhvCeMaaGHxSr6m8DoYjdHGwWXm5on1yG1VI/zVUaQFgtN9r8irG0oyELwUpb6PfM4r2pw3aJRicJnmAPS/GVqwXIHhyeWpien+jC/k4WWqcLgIPly03TzyRCFTIJ6qtDReoemvPfcnge4535aClkkAmZGtInq79ufQayRqW6yMCr9X0/S7rhv5P4qxIhW5c20SeGlBf3CTSzGcyzevALC4DmBZVkOxEm3DNHBHIjrD8nCbtuApggZaKNDYlrdxRfQ4P1VZmyNEGTf4f6YoirrNMuo4N71AGw0h40+UjxsvDkT5fYdCuLCfOYy+AkKysDQS1lozDvwLrE9TX14bA09C+sG7Imge3JFJJ+nUOthU4RCHwRHyoaP+O1wHJENll4BuGvtysSVNlZRadRLKKbSiy9ttruzeMdRAaN4HN7Vrw/WDRXR8uDsw1ZR+Hx/YgF3tkOwQ8aMoKkqCiM6X11Ya5Jnhw7lVRSfOpPhihOrbqo7XRWnMhVJWbV5aAZqNLnlAYomjC2iIU8AAMbvi7atKGMKfYE1RWrUPgQsURTHsundkw53KUp1GBrZPSI1u93hA9tbHSi4SfR4Bik3NY0X4px4M9l+uJZG4lGec4q8XZCXW8q/OwGf32LD/MEzctU8j04tbyKm2/1NsvUxJF7eWoN0X8PZwvbLTfswrtJPRg/G7j3R1n4cDENN7VXz/bzkF3waiXIh+m68SYFNYc6oGoMzOFqjNH5FySCGD6r2i7br3ZE3H5gjrOYqcMQkbe3HPs5vCeg/kciyR97hi6RFE4lHuPweCj5Iix/4xM2olvuw7etdS0j0yYuuTEptnnAHYsgoMKRht1xveZrx1nNo0xhxqJqgS6pL8IbbC4zrYczdrxDKPf0J8+DL0Mm+Da0qcla4Debi6vYtgxr5dAH/MAdgPT3R82acewo7PECbH7xWI5rEmTiC6rOl8w6wh+F2nqoQ4ts41puazlY7OVj9Epc7dIbbJ/WqpPnkdIaxioYA83a92unmnDJ0kE53URW3JUFzC1z2C1Ba6BOVb7eqZuKDCxcqSUrevRLml7QHtoicZwjiif63NaeU9YzpN1BfONb47CHKiz5UCPUq6eHfKn7F+gmY5FBA+oaviXjoM/BXjgrfO4DM/wPATP+MF4+AP1kGq4V+7YDiwig46m//rx9OunwrXLoaP59AviQfsKGk7gNO3fjYehM9Qmh8ybfz4WrnnYnsFesTOsekx/qOi/+zJ4eZ6m3ZT/gF1/1P38AHDwnCMqQcPCyb6Gsb46HoaP1+d3eLd/IPrH2tJX77rr9DhN7iVrn/H++UCU6Xfl79iUYWCb3BJZ8845YTylzg4+fFiUyVVzrTvQuSMWVJv7uSiXq8pCjYF7Z5o2X3gFnSMAO7mJt9Te8fyw9bZmhdkcYd2c7S73Tm3iIYMVzEv4ffnDpqiv9oFvQn2+XlRlEkQFXPmHsb4FeGFy/wD/NB72tPT5lkE7RW7aCJZUapCWrSYnBGvBmn7Hl+M4HHpOFOZRysg3dKdUny8MzfO7zEdKzhSdh3hexlFqqz5fGprnSUh/7rslzkIuU1u1d/e2wS+4pZGwFS66HhTgFjfFME8KpTtRh6+xQeogdbPvNm93u4ub8HuSAp05Qu2gZ9rwwTXe3Fvd4joca7bnBBVOYEyfU+Nf1L4=
*/