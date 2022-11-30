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


namespace boost { namespace hana {
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
    struct equal_impl<S, S, when<
        hana::Struct<S>::value &&
        !detail::EqualityComparable<S, S>::value
    >> {
        template <typename X, typename Y>
        static constexpr auto apply(X const& x, Y const& y) {
            return hana::all_of(hana::accessors<S>(),
                detail::compare_struct_members<X, Y>{x, y});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EQUAL_HPP

/* equal.hpp
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
*/