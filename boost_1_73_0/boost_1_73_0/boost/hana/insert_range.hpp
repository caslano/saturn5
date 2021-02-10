/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename hana::tag_of<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            hana::Sequence<Xs>::value &&
            hana::Foldable<Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take_front(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_RANGE_HPP

/* insert_range.hpp
KtIKW4WuoryYUNhVhKBul3PG7MWypOL/QbKedQbeIonIzwvj8zmnB4xf+0YgNWC6b2CXie+onDu2UikAi0IaPYWofKR8IcpHPqHcKr//rni79gSrQgIoqyqkEb6t+9bp5M2Ktd3k3hqQaWmmwi1cPaM8KrkrONEW4zOLXhrh6F5tY6Slp7EAWMCf1iMfQKi6dZQ/iGLBne6H5kUHdLCef9H82B6YeV5FQRoKX5St8MCGZaixiHB32B94nf2eR7GH+lBW7Egs7Ks4+vsy7IjHpFxjIXgjBeumOG66t+7vWNMkzrbefy0ztjNRXKuqgIYn2fJwMCPA4gG5n3ETQBqVhzJrOxXqRqFxva4RTO5AFEUiuV4AS1FiGXEIbC7KkxPVxak0K9JatNlD24xH0lJbmk6cX+IZ3vxSHvfLX9Lp0fhSHTm/lDKLahVTX/Io/ajgn+6s7/PEURRY+PtVVB0WsZhKInLUR1Gmqxo55L/xdpZcBzMy2WBL4dXxH9ACa08dSDOqubcLH1T5zaFqLLs1j1HF6rmSNEZ9Y7Q0oHy9IVT4bV261ea3eHDdzYJpyMnN4XkeZlSNwLjOkmAps74ssKtTs6J2gcbkq2F74I/eoepATNsfdHqDzugjbvGXzQudp9WGRy6h4T3l2zf1
*/