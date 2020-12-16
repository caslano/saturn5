/*!
@file
Defines `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_HPP
#define BOOST_HANA_LESS_HPP

#include <boost/hana/fwd/less.hpp>

#include <boost/hana/and.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less_equal.hpp>
#include <boost/hana/lexicographical_compare.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Less = BOOST_HANA_DISPATCH_IF(decltype(less_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value &&
            !is_default<less_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less(x, y) requires 'y' to be Orderable");

        static_assert(!is_default<less_impl<T, U>>::value,
        "hana::less(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Orderable");
    #endif

        return Less::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value &&
        !detail::LessThanComparable<T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for LessThanComparable data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<detail::LessThanComparable<T, U>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) < static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants wrapping an Orderable
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct less_impl<C, C, when<
        hana::Constant<C>::value &&
        Orderable<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr auto apply(X const&, Y const&) {
            constexpr auto is_less = hana::less(hana::value<X>(), hana::value<Y>());
            constexpr bool truth_value = hana::if_(is_less, true, false);
            return hana::bool_c<truth_value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Products
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<hana::Product<T>::value && hana::Product<U>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const& x, Y const& y) {
            return hana::or_(
                hana::less(hana::first(x), hana::first(y)),
                hana::and_(
                    hana::less_equal(hana::first(x), hana::first(y)),
                    hana::less(hana::second(x), hana::second(y))
                )
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Sequences
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct less_impl<T, U, when<
        hana::Sequence<T>::value && hana::Sequence<U>::value
    >> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys)
        { return hana::lexicographical_compare(xs, ys); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_HPP

/* less.hpp
w/3cpGgUnx52o3E+FXOtH5J+UrL/iBvt4GdW1WiMl9u8ae2DXgIeN9sgsgfHjFt7f/WokTli+rzOsL3S/Im6zqCpY/rE2X4low2LaMdjRteRufZ+6ixgKuyX8jltSozzBYzaIYbNeugAl7tzO/CWM6Ftb2WRXKqEy6LWoUJnkgApX6d6/GRhWNf/NuqPKJFR+XKlSU3fv9y2gz2yY0fWC3NNfh7KTT8DnwZj90CzsKHMOXosnovZDkfgfeE42WWMIh9eW49wVmp+ZcQw7TMFMLlM5bePkq1S0TxQ62BGC6EYuxffaPw+tq37XgY404YiZpH8vBrlo/ay6X94A4Npz483oczYu7G6wA+f+Ogeoj133zKyLppryNNQrpVap7E1tvE2CF5MAg7QMc95vBL2zIKQUsa/CLYsjiUBj3kDnOYe2zwPeILhw2kMCVH3vahr+GsYV+6G8k+M8W/jN7E7y7ShRWP9VLS7MRhqfr8P+EccLDReH0LZqB/enAMfB8zoOZ+5tn+2hmm7YkZsqc+DD7VAz/s5JKSidnx+jM5qj+uX2rLB1ytj7hex2HjqVZFofA31R30Kpl6/ArxuCJCvkegyU6q9nkNetK3UYGTrJDQYjhDrufbdHXjV1ivfbOus2fr7D5i9yMfpJzuNE2CUHP4cMCMKmvjzu7H8MXn8Z8C0/RkkBvWeifGq3Z+vmf05pvaaN0A5mfny9xeBl1jPhHKq+Ud+Uhgakn9/v9FO/hFTV1xlz5hxQ2v5ufOuPePHou3Xv+6etnxyGWB+Jegjf74Zd1LFEsfuMe1p69cb72mfK5r7+McBaWuz3PJt5hX3x998FJ/qWn1OBbrYsui14vUYo3IeLkrRQ5LtW3MeqdYQX165t9N6tYa9EkT1b8vrqw6TTFwfd8X73Y0FdbUQ1dT5GWQAPSG+3HFPey/E/Wh3hgghTxb+THaWcUd4CXTrb0jPjG90l4eea1DwF68iyuT9Xg1/BehOyrhNupVxFvSp7KnX0WX8wjH6cUdZbu1GuXn3t6aDP+odN4TYuz1cXd1cyXDL+XgTY23C+Jun13C5R7yPeGwRVJbWAavwRQwW9yFWgrWtwTBYEyCLCuZSC6boniEQvAFFMB9mMO46+FNf79X3vDpXasqP40lIFw/Yzfdy3Kdcc84OGVy7f5uD3nq3fhTbrToabjfDNzcG7uYEByAFp9636Kmy3U0Z3QZvyi4x/FvdulDdy/6xzE2CwGY8R95hbxX87k3i+2PWNg9OLGwPT07j1v9pfN5+OuE895gmZvgA3vzGrZ0oxz0D+RpjKf6qxF+++KsQf83pvzLx14L467j4K9Yg8rrehC49Kv6aF38F4q9p/KXiqJt4sCuNjwcrEFtrZ4A7BLin3Fr0H6q5yuwHCWsiDhfmYCZAj/sLcGv5cvWHRhJeIledI13nBtv4+SLkTb2KvCuPKdivvw/x/aXyO55OAmOWCf6laM+r2ffTpP+2yfZU897GnD0eF+AsYiM96euB+NWw1611vBu19jD4IOc7+jy2x6r+UOoHsbOr4V916x3OCw/WbfnzHgE/2pobouwcykQosd4v0HzfC3k62BHvpGxugyVaR3xafsezoctYZBdOrfeWmjL4fFAmb3FD2BYkd25N+mH1GigblTWUU9z7LzvgKT2jpMPGm/kzPMLvXeYuRj7CDbJFfbGN4KrTV+J3blM/zu0yday51d5j6OFTNI6qAaXC/whe70CZlEXpI/B/iQDXFf5VDufgTgLC8/0sj4nA0vba+gpI6NtsCv/FJ/D245pp5HspciIQ/iX9/rKBv7CQ4MKNwjit8dPT1ttbdH95ZW0L9/Rwl4zQNPx66Ms4vTQ=
*/