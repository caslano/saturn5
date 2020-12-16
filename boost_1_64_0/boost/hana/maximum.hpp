/*!
@file
Defines `boost::hana::maximum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAXIMUM_HPP
#define BOOST_HANA_MAXIMUM_HPP

#include <boost/hana/fwd/maximum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/fold_left.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // maximum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct max_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<Y&&>(y),
                                         static_cast<X&&>(x));
            }
        };
    }

    template <typename T, bool condition>
    struct maximum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred&& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::max_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // maximum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct maximum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::maximum(static_cast<Xs&&>(xs), hana::less); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAXIMUM_HPP

/* maximum.hpp
Z8VOiEiEEqf686ton7yhtry9vghNjP7KV1YQVaEC3tjbFtNTRjxOGrgZgjFQ53TTREXz1QaPECKCzUkWRWlNE3VU9DhWY9L7TduZLfABjucgVvhSXMm04BIx6X3YoIcLzAjC8iucmdmAxJDgDFtQwii3qQMN6+N3OJ5D2MFkMmwevm8ISuvO5sVl82wtxSX5ygnxOF0NjTEf7SuupqEVYndnxLvtWeF0g9LJHLwqZeF2bXfYbdHdt2LutSIbXUU4iuXV0OirtrHaXG7H2fXfx+XIw/qIt2FySyhpBdtV9roFujyGywkQJuAhzA7ANdHmPSBty/E6E1mIBafAKzunKAxkoPdoHM6FDRkgZxXEC7GXwH2KRq6Q1wq3u7TXW6r7ioKTkNOr6T0axzVdVQko4vRQNFA4CXUbFe3zBm3PwqjbqOIL2ZHzQFiOomZDdYBWgeiWoG/w86XP5O9LwYSEoYOdmdg660gwRffVgDXs5jTCA4u4WIkArv8qMknQVedIvxJ+iYUFaNUeFh7s+091ZaQu2XYAWVdnFGfkOabMBlJiidpa2e5rX9R5lDVnpPIdygEqL6u6L+blWMRQNlBlr5fnkfMnYA85cMeC3UPtS/rTz0TZ3Kz2xSq5hH9EwfyNYOi8j+y5U0UHMPrMaaoDmOblXpixS+KOpWrDq/UdObRgpXsGn5ZU2XkHZXJtGS3r31+UbfXgeKbSpuyKvaIMyz2rdxNV1hdtxhyvF54zKib0vYYMCkdP5YYFe53OxR/8E/8gU5e9KcHrFnAThaWLiWahHu2t8cMrdkDTvIH0DY7nSIidOgLBKguTCXW7iC86a8Y+XjTnd4z3WCIYjtZRjCSvAFBX1blktjXEO/R2GNvWVu8xkFksfUOtFVzVv11dc20ISj+qCuyt6xtEFCorDpMh72p5GbOv3gUr04jnCqo8LfLUqkUQTRb7i2bTR64xzadZtT/vmrF6SYQITqeI/zvfFRrInFdqT7z3geZ9fjzWEmZ5nljNsxR0OYnuTeEnu1uF//APFmtR8Tb62KBCS0dZFch378CpegsIASHtD/loS4dgpZh2xjsUr+Z4p7G0YgVD5HSFCdbaiTW+kSu6ph8iqsT+3MOqPABp4zLYwZqqXBtwF12idPh7aN8wcMWIIcvwGAUEKKZ3QvUonm46OgUdgQ9dbDFPEp7OSdPGyYoKUUSwN9ytLnHnMpw5NfZrob6iwdqXY9AJEZuT2n5qu6PthZ4zWgt9hzm+pMbzZPudvxzeCwS8nSqwuQdd0hTEtdHm8ZWdF1tNXPyZky37JMIlU8TrshuKeNBAPeR2EniOCLvqwMwRMjvwr41eY2O9iePzMN+KEnfEIuA7omYprdMqZq3+VLtrm3XvdxyPj1ByvMHow3Nj+WcWl4esRWRBkQWu2rcfw3FE4bJO8TZBWeIiLp5lgnO926UrgVjDBvgBnMoywkwjrEDV4Dpn4EL8OKK/sXh76B8WHPiK4dxEG2gtB/KtU9sbUIsDIAMjJS6HcK0+y9RNYQxHJZxDOzrVMc/ab+G995Rpl4RZ4SQ2IsuhiFG31pOQMvRTLZbS2ERDMesavX6B4xGmcZwWuK1r8UqkvlaU3fbxh3O/VlFFWYnrMJYGVWvMecMfXgaYvR64LxwfwrcworN/Z/QpsbzAxSqT5WP6pGSKOiSO6phvatXUQZWPpQqqZX4EDWZf2wq2mvdEo1Uzht6P4ZiFE9HycJC6JC0uuRmC8oGh2ZwH6LsfRn3YwmEUpmHkWV7NXG67Ei9ste70eV20PS0hu3mFQOreqMlLUisNkJGVv5lbL+U4obnyIsHkikLqj/Zbb9YkCvNdw0m0r3lf+cOrrbs=
*/