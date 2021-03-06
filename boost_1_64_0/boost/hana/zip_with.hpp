/*!
@file
Defines `boost::hana::zip_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_WITH_HPP
#define BOOST_HANA_ZIP_WITH_HPP

#include <boost/hana/fwd/zip_with.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto zip_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S>
    struct zip_with_impl<S, when<Sequence<S>::value>> {
        template <std::size_t N, typename F, typename ...Xs>
        static constexpr decltype(auto) transverse(F&& f, Xs&& ...xs) {
            return static_cast<F&&>(f)(hana::at_c<N>(static_cast<Xs&&>(xs))...);
        }

        template <std::size_t ...N, typename F, typename ...Xs>
        static constexpr auto
        zip_helper(std::index_sequence<N...>, F&& f, Xs&& ...xs) {
            return hana::make<S>(transverse<N>(f, xs...)...);
        }

        template <typename F, typename X, typename ...Xs>
        static constexpr auto
        apply(F&& f, X&& x, Xs&& ...xs) {
            constexpr std::size_t N = decltype(hana::length(x))::value;
            return zip_helper(std::make_index_sequence<N>{},
                              static_cast<F&&>(f),
                              static_cast<X&&>(x), static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_WITH_HPP

/* zip_with.hpp
/itijg817YksBP7VwXYJyGQy5bcBpRmDN2voe3ys7+VVGfLtLFtGZzPIZyYo68lxzIP/0x1a3+E0ChOaqLPD6MdK6A9aw8z3u6spNUg3zJni0PIQnjpTL6otcZrF/pbwWACHHvDBfQCD6IyEBRZzzEUYl75Z2FwZG+OmsE9hzVKFDSZZcGezH0K0Hb3cSzfoVyccWK4CteTfK9gl2HjIsHknhvd2vnggUrJ1DbzL5VlCKqcqp/gKumcpfvTXprk9A7QotVgAMedvx2QyIZUPYRHFFUO/ha0Ccrt5S7uxy/FsQZuX3/dHqrZp+NB0ARnBRs3mnDmtyrQ/GjxpmdqTJVfaQOEd7uLT0GzWSleCt3tKvbjyz49etYmlhljqOXbJI6g4vAW0T+vjb0UdSUi9MgqqGxhqrIfrxSzSQoIlivZo7V/PSfbPkuYTDMU6Q5IEWL9+wD5hx+Cx4TPFyUCxPHW2KPh90LGIFmU4p/QVWywutsXK38n6lS+VVNsUS7M73T7NDLmpZQMeNnjwr/XDAKOURqSfuhtPLfJRFd0Gk04nH1Hey7VO/vvkjA==
*/