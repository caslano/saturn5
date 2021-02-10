/*!
@file
Defines `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_IF_HPP
#define BOOST_HANA_ADJUST_IF_HPP

#include <boost/hana/fwd/adjust_if.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename F>
    constexpr auto adjust_if_t::operator()(Xs&& xs, Pred const& pred, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using AdjustIf = BOOST_HANA_DISPATCH_IF(adjust_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust_if(xs, pred, f) requires 'xs' to be a Functor");
    #endif

        return AdjustIf::apply(static_cast<Xs&&>(xs), pred, f);
    }
    //! @endcond

    namespace detail {
        template <typename Pred, typename F>
        struct apply_if {
            Pred const& pred;
            F const& f;

            template <typename X>
            constexpr decltype(auto) helper(bool cond, X&& x) const
            { return cond ? f(static_cast<X&&>(x)) : static_cast<X&&>(x); }

            template <typename X>
            constexpr decltype(auto) helper(hana::true_, X&& x) const
            { return f(static_cast<X&&>(x)); }

            template <typename X>
            constexpr decltype(auto) helper(hana::false_, X&& x) const
            { return static_cast<X&&>(x); }


            template <typename X>
            constexpr decltype(auto) operator()(X&& x) const {
                auto cond = hana::if_(pred(x), hana::true_c, hana::false_c);
                return this->helper(cond, static_cast<X&&>(x));
            }
        };
    }

    template <typename Fun, bool condition>
    struct adjust_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename F>
        static constexpr auto apply(Xs&& xs, Pred const& pred, F const& f) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   detail::apply_if<Pred, F>{pred, f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_IF_HPP

/* adjust_if.hpp
Y0QXrI1/co68EHxJKxTGkQNXb7y+rCIcDA7hvxcvnsMTOHp69DSDY2k1GphGtAv0lxm8Vs3K20peXfUCvskAI0jT20LNKh0guDKupUega6MLtAEVyAAKQ+H1gv5oC7FCKLVBGIw/zIfn7zJYV7qoGGTjEoTKJaOgkisEjwXqVYtRSx/BlRRO4EqHSIApamd7xI0Q0S8DYzC9NMGBXElt5IKIZIQqxjq8zPMieUPqc+WKkBc36fequPyZyZxELOUGXB0hOkgBM+CdGSyd0iXPZAgt1mlhdKiyWzVEZVXuPAQ0hrEoTmNoZSNMt/ZkvA1qUqwjT8HZwFTryi3vbCQfGaVM3hIR+UCblCObM0jUSr7Z3GR+Q7H1tDH4waO51avAWRIDe/0pDKd7sJBBhww+DWdn448z+NSfTPrnszmMT6F/Pmew98PzYzp6TWQe8Kr2GIjcg17WRqPacv67kXf2tS1MUgh7fHgiYEx1r9rr0FOBBY1rZPco99loCv/jBoy7bAtMl1RB3xIGTnSxaTbRcfq2YqbTUfuAOR2OThgJ7Up7Z5doI6yk103thBoLXfIhcrRLsU7xp7t5Z+W0ggHriiYIYidy4UjSAd85fHWjcmBcwIdlWse95FGqzW9wCwa5BzwhOzwb4FODdJMj
*/