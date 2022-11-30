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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_ANY_OF_HPP

/* any_of.hpp
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
*/