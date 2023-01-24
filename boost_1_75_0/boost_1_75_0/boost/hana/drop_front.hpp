/*!
@file
Defines `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_HPP
#define BOOST_HANA_DROP_FRONT_HPP

#include <boost/hana/fwd/drop_front.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFront = BOOST_HANA_DISPATCH_IF(drop_front_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return DropFront::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_t<1>{});
    }
    //! @endcond

    template <typename It, bool condition>
    struct drop_front_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&&, N const&) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_HPP

/* drop_front.hpp
3AGZXXTHM2LHLTcoNOcl+hikia5drs5wp8z2oPURgr9orsQzeFHhQZVlvSjZh9Xg5g2NAt+rvIbn6t7mwmdsgpi/Wv0augGLt7rQC5eFP78R2O3rSXjQ19yEg3gbLUGPe1UyaUVCmM9TWCLfXK9kTsCcrbM9K7ddvSVianVvkJ5Vf9JFjZ9BhVvdRhs9XOefz432Texd1yJpdgtQT28ffVG2hhtd2Ys7Jlsyui+MXpqoO6I27sDYdZoRBi8MX55hwDA7s5KnarAgaBDMw16vnzcx163AFzB055eurGarilnBty/P0F3RXDGF0VvQjIPo8ylb6VrRW0lbx+ga8G/Xe6V6v22YWYQ/QIKkJbHVV6Tf7zzJScq8CCDyeeVD5YPhQ7a0A6X/LfXyGIseG0TkYzUq2lP1sEVsPXwsjLTa3VQUJBcISSXWeP01niArWJFHiIwwcwS0SvOtSnFtcWpRlpm+qRUKYA/TXKU+uaHrkJlbJ/07zP5KyV5V5snmbIRu9yZve8nAfJQ/aX1XrHRWMDvZ5Ya+qajEZQD70WCtVsU/5jNudlgYqbvAKQJ5HDxHxJVYthTw3qgKi3f12Jvkxv4sZNc+bTM7WDQuJ4Kzzp9PEkoqtuQvCqXl3xqBvaLKuXEGuh5gSoJ0cWjElujEd264Drekb9tvp7/UJlIKuYoGVSS3l34+as5O/7K/6LCsVnpOJKhNW/75gt+i
*/