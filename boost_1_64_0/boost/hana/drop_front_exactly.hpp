/*!
@file
Defines `boost::hana::drop_front_exactly`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_EXACTLY_HPP
#define BOOST_HANA_DROP_FRONT_EXACTLY_HPP

#include <boost/hana/fwd/drop_front_exactly.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_exactly_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFrontExactly = BOOST_HANA_DISPATCH_IF(drop_front_exactly_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front_exactly(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front_exactly(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_front_exactly(xs, n) requires 'n' to be non-negative");

        return DropFrontExactly::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_exactly_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    namespace detail {
        template <typename Xs, typename N>
        constexpr void check_dfe_overflow(Xs const& xs, N const&, hana::true_) {
            constexpr bool n_overflew_length = decltype(
                hana::is_empty(hana::drop_front(xs, hana::size_c<N::value - 1>))
            )::value;
            static_assert(!n_overflew_length,
            "hana::drop_front_exactly(xs, n) requires 'n' to be less than or "
            "equal to the number of elements in 'xs'");
        }

        template <typename Xs, typename N>
        constexpr void check_dfe_overflow(Xs const&, N const&, hana::false_) { }
    }

    template <typename It, bool condition>
    struct drop_front_exactly_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const& n) {
            auto result = hana::drop_front(static_cast<Xs&&>(xs), n);
            constexpr bool check_for_overflow =
                decltype(hana::is_empty(result))::value && N::value != 0;

            detail::check_dfe_overflow(xs, n, hana::bool_c<check_for_overflow>);

            return result; // NRVO applied
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_EXACTLY_HPP

/* drop_front_exactly.hpp
i373XMYlLG+L5Dk5m/aC56ON678vXdZ/pJJxB+3elgJeT6A9zKPfy31oe8SL/gz7q67zEP2lyey/L+0x+7+c67mK/RugvjteZX7q9Q3KY1X75OR6cJ3uPMb9wnPD/A7H+T7XgfXVbGIcRD/QxXgomv74xSYhz2mu302evyXc1zmMLyqYHlDjlExZ7x6O81Qx/VgX7SHPO1cn7XmZkONV/fLVPuPrdvVd+qsst5z6uoTzXUN/8cxa9pPjC1xHf4l6MPBx6hHP3Z20f35s/9gsjo/jLWE86Rhi+2xveyj1nXoZSztwitcraB8v8rw8sp/6uEqOK7BKno9TmK+E9nc6z9ubH/C8/bMst4r2eDv14MYl1lsh47PTedyP73J8iN/83d9VPVLjjGbazRqeH4gfvdz6ksfzgnruUyjTmezv9lTaf673HK7b+RKed5xvhedPLO1jTqVM5z/GeOpp6gPjgdc4zj1f5TnFuHPHn+iH0b5cjaB+8zyL5n7a4+T+Uu0wz+351Jf5Vnlf4QT1KZpxzBn66TZ1n+ZL+WWOf0cWx0E762KcrUTRj2c8dUbt93rOVxXjZMYVFe/SbrG/5xlHL7LzPsoGWf4A/fVAtOvrToekH+NXwHPNxLiwifu/mucpz/+zPrRj3AdZjJdm5Mv2T2xie9Tjkl08pxWDvL6CfgrlU6ivNbQ3dsYbZvqrJd603/SXI2kPb0Ux/mX5kGbaE54/yirGMbyPoGRy3hgPRXN8PuzHsXdprz7HfiYIuY/WUZ8cXrL+ZVz39dRj+sW3+nn/hPZyDvXulHquexmknP3KepZ+B+P4w6nU0yKZXuS4orOlXxK9WqY3PkP/LE+IT7jXHfGtwb2u3HdKhaz3pIPzynmc8gz9oULGv1zXnQ75fSft/sl0+ms58nrIRuZ/hvt+IeMM9f4X7VtklZQnLKfdZuoIo/1zSXnIHMZLqp6v4TrRriRQ/xax3HKm+2gvbqnraKcd71H9DsZPBfT/ijj/3D+pXF8H7d5WrsuUXdRfxnOxQzwPUT7K3b9w1ruC/jn92IFC+geMpyJTGc9k0G5nc1ycL0eRvH6Wdu0q/aMTXE+lj3EIv8/czXnOkutupx9Qwvhky7ssn6WMr3+ImX4W/b2EC4wXqZfnuE8d/Yyb9gg5/p95yXK8n3GA/m8s9dzF83EJ52kb7ccqxtU3qKeB9GNuLPCW9a2k//gu47r5PJ/WMT6gnXbweoWqZ7N5TrHcWe7P+XG0lx2MA7iuO+lHHqTfu+hNIeclm/Yk00fWN5H6XUS95jyVwF57uef5BcZpjD/O8Lw7Ke0Ozj/GUfQ7ppTKdTnPuNXFce+i3YqkXzvns4xXC+i3c3+lZtGelQlpb2ifItdw//N8G+inn/Ew7Xw44wGe64e5jqfyqR+Mdy5xPm6wPWWFzL/qTeZ/lf2g3kczrjhAOx3J/ZvK9TDTXvrRnm/luE58l3EYz919A9xvvP8cSD/n7ET6P07aW9otB+3pQZ7HsZXe4+UW+Xpzfwoxwd0O9c6sniMj3If0k197WvrvOxhnHOM4D/B8nm+R+/k047YbZbxv9g79IPpn0d+T9c500I7/nnqxgXrA/Wa2sp6Pc1z0+6asp53guRDN/WwrpR4e5n2yBuoH9cXOc/6kgXG5F/1Irp+d6xTC67dKOe4S9hPXpf9FPSmkni9n3EP/LqGT60/52UzGP3Vcf+rFxVTai1Q+v6iinobJ/Id53uQwrrxOu1rDOMRFf+NwFe8DeQuRKJD3adqxC9QLK/2OAsaxM+nvsH37ecYzvB7J9AT1KZLzr7C9EPpXS5qFrJ/Xl1APo/M4bvr1l6h/OwplPoeV60j9dqnPV/o=
*/