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
MSJoxxrZAVVxdxAYLXL1JVB6GZ8AoB4X5U3rtq3nrim9zFq6ogM4saznIACiONhODj9a8YuBDsl6oQVTwlHWcQCwRjV9FurjRmVokiARw38NlH2WZdunkaXlgutYpOKsuH6dauurAbug37wVNXp2/BsGSu1d4VLIGASjDvBEoooKKphEU+JzOnqYukzoa/bD3SBztN7BZX2A/zbZYM0LEhJVeP7dT+NI+FHz416x9f14R1HibgtJ5WzSk17vLfiKrf2tRebSIiFAPTQ9fichLLJ+OILq21FuwxG8h7lS65/l0URS7StwqRbBymYvzgKVTlonSWFw63z+Z+9+VJMNAGtbYU2IIsZSusvvR+l7588pEpcfSoQQIDNRIsp/WF7/dHCdWQIb+pDSgBbBh1w+AU0KDOS27Ph0dit7SI1PmpbWxVL/VHowqOByveeMVvOtYrJLcu9N7mEX43EFbZ6OsMo5CucL2eVUO6Sd0P1pb7j11Pn0KBPMDMfhwlhQDXod0ZHHpCkFMLFudo13n93dmJ/SQRHzgl/mTX0U8akyh1MwLZdNv977ENEtEg==
*/