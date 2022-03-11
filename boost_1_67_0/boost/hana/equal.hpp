/*!
@file
Defines `boost::hana::equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EQUAL_HPP
#define BOOST_HANA_EQUAL_HPP

#include <boost/hana/fwd/equal.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/all_of.hpp>
#include <boost/hana/and.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/first.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/value.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Equal = equal_impl<T, U>;
        return Equal::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr auto apply(X const&, Y const&) {
            // Delay the static_assert by ensuring T_ is dependent.
            using T_ = typename hana::tag_of<X>::type;
            static_assert(!hana::is_convertible<T_, U>::value &&
                          !hana::is_convertible<U, T_>::value,
            "No default implementation of hana::equal is provided for related "
            "types that can't be safely embedded into a common type, because "
            "those are most likely programming errors. If this is really what "
            "you want, you can manually convert both objects to a common "
            "Comparable type before performing the comparison. If you think "
            "you have made your types Comparable but you see this, perhaps you "
            "forgot to define some of the necessary methods for an automatic "
            "model of Comparable to kick in. A possible culprit is defining "
            "'operator==' but not 'operator!='.");

            return hana::false_c;
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value &&
        !detail::EqualityComparable<T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr auto apply(X&& x, Y&& y) {
            return hana::equal(hana::to<C>(static_cast<X&&>(x)),
                               hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for EqualityComparable data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct equal_impl<T, U, when<detail::EqualityComparable<T, U>::value>> {
        template <typename X, typename Y>
        static constexpr auto apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) == static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants wrapping a Comparable
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct equal_impl<C, C, when<
        hana::Constant<C>::value &&
        Comparable<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr auto apply(X const&, Y const&) {
            constexpr auto eq = hana::equal(hana::value<X>(), hana::value<Y>());
            constexpr bool truth_value = hana::if_(eq, true, false);
            return hana::bool_<truth_value>{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable for Products
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U>
    struct equal_impl<T, U, when<hana::Product<T>::value && hana::Product<U>::value>> {
        template <typename X, typename Y>
        static constexpr auto apply(X const& x, Y const& y) {
            return hana::and_(
                hana::equal(hana::first(x), hana::first(y)),
                hana::equal(hana::second(x), hana::second(y))
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable for Sequences
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Xs, typename Ys, std::size_t Length>
        struct compare_finite_sequences {
            Xs const& xs;
            Ys const& ys;

            template <std::size_t i>
            constexpr auto apply(hana::false_, hana::true_) const {
                return compare_finite_sequences::apply<i+1>(
                    hana::bool_<i+1 == Length>{},
                    hana::if_(hana::equal(hana::at_c<i>(xs), hana::at_c<i>(ys)),
                              hana::true_c, hana::false_c)
                );
            }

            template <std::size_t i>
            constexpr auto apply(hana::false_, hana::false_) const
            { return hana::false_c; }

            template <std::size_t i, typename Result>
            constexpr auto apply(hana::true_, Result r) const
            { return r; }

            template <std::size_t i>
            constexpr bool apply(hana::false_, bool b) const {
                return b && compare_finite_sequences::apply<i+1>(
                    hana::bool_<i+1 == Length>{},
                    hana::if_(hana::equal(hana::at_c<i>(xs), hana::at_c<i>(ys)),
                              hana::true_c, hana::false_c)
                );
            }
        };
    }

    template <typename T, typename U>
    struct equal_impl<T, U, when<Sequence<T>::value && hana::Sequence<U>::value>> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys) {
            constexpr std::size_t xs_size = decltype(hana::length(xs))::value;
            constexpr std::size_t ys_size = decltype(hana::length(ys))::value;
            detail::compare_finite_sequences<Xs, Ys, xs_size> comp{xs, ys};
            return comp.template apply<0>(hana::bool_<xs_size == 0>{},
                                          hana::bool_<xs_size == ys_size>{});
        }
    };

    namespace detail {
        template <typename X, typename Y>
        struct compare_struct_members {
            X const& x;
            Y const& y;

            template <typename Member>
            constexpr auto operator()(Member&& member) const {
                auto accessor = hana::second(static_cast<Member&&>(member));
                return hana::equal(accessor(x), accessor(y));
            }
        };
    }

    template <typename S>
    struct equal_impl<S, S, when<hana::Struct<S>::value>> {
        template <typename X, typename Y>
        static constexpr auto apply(X const& x, Y const& y) {
            return hana::all_of(hana::accessors<S>(),
                detail::compare_struct_members<X, Y>{x, y});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EQUAL_HPP

/* equal.hpp
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
*/