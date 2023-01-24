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
J7sU573aM//srvd+3WzU41Ti2u1M11/vHc34YZV6yKt3RixaU/veuz7/eqvrEOPL5Y91br3z89XHTp4p/Lzv0boZ516av/TzV1btH9qxReHNeoEzV/3uULUZcLdh3Ffr5ulGqb7Zv+i68XSnQbZrG55dPX9Muyd6veasNXHogm8HhxT9YX7lm/A6zXbeebGu6mbmrYamHR0jZ/+xd+mCOvb3Jt2v8UxI1Hqj8/GQrjNGvKX6qc0RFj7x86+yN14fP/OM6qvFB/fsynhelfHxqCMntv41ssf0jX4tYxL8ntib2HIt29XmSkVCyXLX3iePhrz/7Z12BU+98nz/f51pWXLIVri7+PVNX5Uk+ZVe86G+Zvm3J8aaLJOvvfrN2Sf/WG7JLhrWe/bu66Mevzjy4sDDI+/Htms6acSqUc5vOqXlFjXXffL195m1/75qfOJ6rz5lNVY9t6nHb1EN2rQ9HzX6zMJfH1nzRktNHr4v9fcmb+3mv3fo+h9+vXwuafkL9vOB1177MTm33utN3zn10Ue/1V/Y375ge/z3BxY9nvmypn+D3z5coG7Sr/jol5FHt11sN6jpiC/fm5X51a9Fs/d98+aY1G5+YcnfRPJ9MaovbqcGxoy7HLnh3dDeH75pefOgxjwxeMPvRduGHtlzLPfSnVXv5j65d92Hw/eY6ixd+jLbFjcmbNbWIbf7nk1NvH5+wq62rf8InBYz
*/