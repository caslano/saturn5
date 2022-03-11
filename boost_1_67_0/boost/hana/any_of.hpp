/*!
@file
Defines `boost::hana::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ANY_OF_HPP
#define BOOST_HANA_ANY_OF_HPP

#include <boost/hana/fwd/any_of.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto any_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using AnyOf = BOOST_HANA_DISPATCH_IF(any_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::any_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return AnyOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct any_of_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct any_of_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <std::size_t k, std::size_t Len>
        struct any_of_helper {
            template <typename Xs, typename Pred>
            static constexpr auto apply(bool prev_cond, Xs&& xs, Pred&& pred) {
                return prev_cond ? hana::true_c
                    : any_of_impl::any_of_helper<k + 1, Len>::apply(
                        hana::if_(pred(hana::at_c<k>(xs)), hana::true_c, hana::false_c),
                        static_cast<Xs&&>(xs),
                        static_cast<Pred&&>(pred)
                    );
            }

            template <typename Xs, typename Pred>
            static constexpr auto apply(hana::true_, Xs&&, Pred&&)
            { return hana::true_c; }

            template <typename Xs, typename Pred>
            static constexpr auto apply(hana::false_, Xs&& xs, Pred&& pred) {
                auto cond = hana::if_(pred(hana::at_c<k>(xs)), hana::true_c,
                                                               hana::false_c);
                return any_of_impl::any_of_helper<k + 1, Len>::apply(cond,
                                        static_cast<Xs&&>(xs),
                                        static_cast<Pred&&>(pred));
            }
        };

        template <std::size_t Len>
        struct any_of_helper<Len, Len> {
            template <typename Cond, typename Xs, typename Pred>
            static constexpr auto apply(Cond cond, Xs&&, Pred&&)
            { return cond; }
        };

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return any_of_impl::any_of_helper<0, len>::apply(hana::false_c,
                                            static_cast<Xs&&>(xs),
                                            static_cast<Pred&&>(pred));
        }
        //! @endcond
    };

    template <typename It>
    struct any_of_impl<It, when<
        hana::Iterable<It>::value &&
        !Sequence<It>::value
    >> {
        template <typename Xs, typename Pred>
        static constexpr auto lazy_any_of_helper(hana::false_, bool prev_cond, Xs&& xs, Pred&& pred) {
            decltype(auto) tail = hana::drop_front(static_cast<Xs&&>(xs));
            constexpr bool done = decltype(hana::is_empty(tail))::value;
            return prev_cond ? hana::true_c
                : lazy_any_of_helper(hana::bool_<done>{},
                    hana::if_(pred(hana::front(xs)), hana::true_{}, hana::false_{}),
                    static_cast<decltype(tail)&&>(tail),
                    static_cast<Pred&&>(pred)
                );
        }

        template <typename Xs, typename Pred>
        static constexpr auto lazy_any_of_helper(hana::false_, hana::true_, Xs&&, Pred&&)
        { return hana::true_c; }

        template <typename Xs, typename Pred>
        static constexpr auto lazy_any_of_helper(hana::false_, hana::false_, Xs&& xs, Pred&& pred) {
            constexpr bool done = decltype(hana::is_empty(hana::drop_front(xs)))::value;
            return lazy_any_of_helper(hana::bool_c<done>,
                hana::if_(pred(hana::front(xs)), hana::true_c, hana::false_c),
                hana::drop_front(static_cast<Xs&&>(xs)),
                static_cast<Pred&&>(pred)
            );
        }

        template <typename Cond, typename Xs, typename Pred>
        static constexpr auto lazy_any_of_helper(hana::true_, Cond cond, Xs&&, Pred&&)
        { return cond; }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            constexpr bool done = decltype(hana::is_empty(xs))::value;
            return lazy_any_of_helper(hana::bool_c<done>, hana::false_c,
                                      static_cast<Xs&&>(xs),
                                      static_cast<Pred&&>(pred));
        }
    };

    template <typename T, std::size_t N>
    struct any_of_impl<T[N]> {
        template <typename Xs, typename Pred>
        static constexpr bool any_of_helper(bool cond, Xs&& xs, Pred&& pred) {
            if (cond) return true;
            for (std::size_t i = 1; i < N; ++i)
                if (pred(static_cast<Xs&&>(xs)[i]))
                    return true;
            return false;
        }

        // Since an array contains homogeneous data, if the predicate returns
        // a compile-time logical at any index, it must do so at every index
        // (because the type of the elements won't change)! In this case, we
        // then only need to evaluate the predicate on the first element.
        template <typename Xs, typename Pred>
        static constexpr auto
        any_of_helper(hana::true_, Xs&& /*xs*/, Pred&&)
        { return hana::true_c; }

        template <typename Xs, typename Pred>
        static constexpr auto
        any_of_helper(hana::false_, Xs&&, Pred&&)
        { return hana::false_c; }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            auto cond = hana::if_(pred(static_cast<Xs&&>(xs)[0]), hana::true_c,
                                                                  hana::false_c);
            return any_of_helper(cond, static_cast<Xs&&>(xs),
                                       static_cast<Pred&&>(pred));
        }
    };

    template <typename S>
    struct any_of_impl<S, when<hana::Struct<S>::value>> {
        template <typename X, typename Pred>
        static constexpr decltype(auto) apply(X const&, Pred&& pred) {
            return hana::any_of(hana::accessors<S>(),
                    hana::compose(static_cast<Pred&&>(pred), hana::first));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ANY_OF_HPP

/* any_of.hpp
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
*/