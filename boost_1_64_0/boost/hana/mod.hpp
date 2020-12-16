/*!
@file
Defines `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MOD_HPP
#define BOOST_HANA_MOD_HPP

#include <boost/hana/fwd/mod.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) mod_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Mod = BOOST_HANA_DISPATCH_IF(decltype(mod_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<mod_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::mod(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::mod(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<mod_impl<T, U>>::value,
        "hana::mod(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Mod::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct mod_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct mod_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::mod(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct mod_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) % static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_mod {
            static constexpr auto value = hana::mod(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct mod_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_mod<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MOD_HPP

/* mod.hpp
XWLKZOOTK4Frg8JhfV8o85wmbqTqR7Fy/GEnTSAX/a/552GLJ7ZsD1bsXvpYd43mVRTVYewJU58C1e5MmeeT6sCyOYQt5m6+nvhY94yEAJMU0k+58DR3VEypYHbAr+G4TuFc88o0jUSraDL2J3Se9sYEW16clWnVjsmJyx6TjzpjouQ3DwdCk8wdE9OSuUMyYT5mDk5sSKEXRSGohv+BT0KHTwI7Js97ovO2n8RJ4TepUIBkMxPZM+Vx7pg0OtJB1A7Jyf86JEuUY9zB04hGyjJO/GDOmLB298eD1g+NS/I4l1cq7LhVGqRc3p03MoxXTpDveK+vmWxKmSZN29nF/9pZ29fXPc7dOzH3QROF89cEa+elOkvxrpz2eSKKUs+rvcDI1qyXNEyjzO5bvXEqigJCj+ej7n/iICoFskU7ToPHu+OE60GShVnSjtPSfx2nFbtfPd5dJ2EVFmWdzl8nMrg0Vyx160RwnGEsoiKWQRLm7v3j0j1Vdwk6f3r9DMskb7K6bvt56rL7+apePyuVKa0K5CX6eWmOQONIzuA4GxFkQZRmSWXkjBlOCIkPUM/J05nEMsoLqSsaMcCozqFJm8tTEZ1dj+/Z2YZhVpehFZJa/brGgynaNL6eiIKysd2hozhjT3DHOo1SPwi8uB3r0/91rO3aO+bgqUXVxDIJyrQ31mfsWKOdB+NLbzMk4wvg5bZnQdTEZSCMwpESN56x8A2HX5RplSV+WQpgdsTtM3ZPfhSHP1F6scxrX3c+IVmRzkcOGxbqjl5GVdKG/XzYchuKbfKwZcin9sJ8fGFhYdJK22efCmRbdk95K8dVYdjjqEjqXEyfOkZV9z/TkONkA8frnkzqMPeDtBZmjly/rI8CltuK1F5UebqD0Wkbx77v2/x5Z8xjCYExynM9KJHDCL372Dd5vSWZ51HZRO1qg53jSbpnkN27QycKQgj6jWj54fhxxRHnZ/yRfuvQUDE3myb0BWNMXYPk3786NPw4r2UV+Q4R/Oz6mj3nLdzPMyjyoMzyAHV6fp5XDHsx66um9PKwFBr38kTv7WYOzb5iftMlxyf6c7eHLgz7fis4qpuiakfeyEFHzj9b5h/L2Bfsekw4LnUsF0WUhU2qb+W684tHeuczCoXlhy2e2pr/8/Etlpt13GtjgFnLZRS1bTx5OW0k2eRFvTZikIvG95Go4f9rY2XXR29eMj9UmZ/b8+3kwv88L9/t9bnIwhJbd9P2efFy+nzhMVZnMezFMYrrqkm9WrDu4vazYYcgta64GfV1Ef1mP7O4+E907/zgxgSqk9j2+2DMdxX8hp7aObF9XXZw+KJMEi9P2p4uXU5PIa/YXKLNE3uxJ6Gdqf1qpqvbl9PT4x0FyvXg4A8gN2ZNmnvycv2slc3wouhyKL+O46tFlsSNX5Se7ny4ZrY8tgEyNRzF43qn06YI+ucqx74QibANla1xsHiYmzrAHokiKoslBgaXV9HpVr/am1e/KXHg+6lpWOPuyewf1kDLf792cDWiLLKiCJPKtI+LRKat5p9lt9WUL4LpYK5Yd/2YiiCOoUUWsIow2g/U9TuVl2/lUV6vwlWikJ4sjbjnds5hNi4z3nPdHaM0U2GZcDLo2qwT8yWOQ6sHFw6eFEzgNbjXZELrFYxWYY4Ci2JfOPUz4UcBdt2UVzeuO259yz8Xe/WrIFSJwz0jGFzmfxol+V+8huNciqoICsWwMefyicVJP87BWzX8cKh8YMTJra0F/j+dz83wOodbXFjeWpwP9wEXbuPk8rIDZ/nnUwbu4t6eMKXHL/UvwB9m632V1dv6L/9T9W5h+/knZS8Hq62pCrQ92LoJcjp4dwS+v6vvh0f7gFE=
*/