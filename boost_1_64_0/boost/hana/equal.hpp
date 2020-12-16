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
AgpAOdgM6kETaAGHwHHQBXrBILgCRifLzREEwkAEWAwyQDFoBHtBGzgKOkEP6AfDwHcKxgBigAkUASdoAM2gFbSDDtAN+sAQuAbGgOE+IQJAMIgCRmABmaAcbAb1oAV0gUEwCsSH0G0QBMJABEgGGaAYVIM6sBe0gaOgE/SDYXAb+Aag7yAUWEERcIJa0ACaQStoBx2gGwyBa2AMGALRdxAMooAFZIJysBnUgxZwCBwHveAKGAXifvQfBIEwEAEWg2SQAfJANagDjWAvaANHQT8YBreB7wMYAwgFJmAFRcAJakEDaAatoB10gyEwBgKmou8gClhAASgHm0E9aAIt4DjoAlfAKPCfhn6DMBABFoNkkAHyQDVoBHvBUdAJ+sEwGAG3wdQPCzEPxAATsIJsUAScoAG0gnbQAbpBHxgC18AYMHxEiAAQBYzAAjJBASgHm0ETOAS6QC8YBFfAKBBBQviDIBAGIsBikAwyQB4oBtWgEewFR0EP6AfDYATcBr7ThYgBVuAEDaAZtIJ20AG6QR8YAtfAGDA8KEQACAbhIBMUgHKwGdSDJtACDoHjoAv0gkFwBYwC8VEh/EEYiACLQTLIAHmgGFSDRrAXHAWdoAf0g2EwAm4D32AhpoJQMA/EABOwgmxQBJygFjSAVtAOukEfGALXwBgwhAgRAIJBFDACC8gEBWAzqAdN4BA4DrpALxgEV4B4SAh/EATCQARYDDJAMagGdaARtIGjoBP0gH4wDEbAbeD7MMYG5oEYYAJWkA2KgBM0gGbQCtpBB+gDQ+AaGAOGUCECQDAIB1HACDJBASgH9aAJtIAuMAhGgZghRBCIAItBBigG1aAONIK9oA0cBZ2gHwyDEXAb+D6CcYAYYAJWkA2KQC1oAM2gFbSDDtAN+sAQuAbGgOFR9B9EASPIBAWgHGwG9aAJtIBD4DjoBYPgChgFIkwIfxAEwsBikAwyQB6oA42gDRwFPaAfjIDbwHcmxgLmgRhgAlaQDYqAE9SCBtAK2kEH6AND4BoYA4ZZQgSAYBAOooARZIICUA42g3rQBFrAIXAcdIFeMAhGgZgthD8IAmEgA+SBOtAI9oKjoBP0gH4wDEbAbeAbjjGBUDAPxAATsIJsUAScoBY0gGbQAbpBHxgC14BhjhABIBxEAQvIBAWgHNSDJtACDoHjoAv0gitgFIi5QviDIBAGIkAyyAB5oBhUgzrQBjpBDxgGI+A28P0YxgNCwTwQA0zACrJBEXCCWtAAmkEr6AND4BoYA4Z5QgSAYJAJCkA5aAIt4DjoAoPgChgFYj76D4LAYpAMMkAeKAbVoA40gjbQCXpAPxgGI+A2mLoAfQcxwAqKgHMB+rsAfQXtoAMMgWvA8Bj6CsJBFLCATLAZ1IMmcAgcB12gFwyCK2D0MRls+IMgEAYWgwyQB4pBNagDjaANHAWdoAf0g2FwG/hGou8gFMQAE7CCbOAEtaAZdIBu0AeGwDUwBgwLhQgAwSAcRAEjyAQFoBxsBvWgCRwHXaAXDIIrYBT4f1yIIBAGIsBikAzyQDGoBnWgEewFbeAo6AQ9YBiMgKlRQoQCE7CCbFAEnKAWNIBm0AraQQfoBn1gCFwDhmghAkAwCAdRwAgsoBxsBvWgCbSAQ+A46AWDYBSIx4UIAmEgAiSDYlAN9oI2cBR0gh7QD4bBCLgNfJ/AWEAomAdigAlYQTYoAk5QCxpAM2gFfeAaGAOGGPQfRAEjsIBMUADKQT1oAofAcdAFesEguAJGgVgkRBAIAxFgMcgAeaAONII2cBR0gh4wDG4D3yeFCAUxwASyQRFwgmbQCtpBNxgCYyDY/bfNQBQwAgvIBAWgHGwG9aAJtIBD4Dg=
*/