/*!
@file
Defines `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIND_IF_HPP
#define BOOST_HANA_FIND_IF_HPP

#include <boost/hana/fwd/find_if.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/index_if.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto find_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using FindIf = BOOST_HANA_DISPATCH_IF(find_if_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::find_if(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return FindIf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct find_if_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    namespace detail {
        template <typename Xs>
        struct partial_at {
            Xs const& xs;

            template <typename I>
            constexpr decltype(auto) operator()(I i) const {
                return hana::at(xs, i);
            }
        };
    }

    template <typename Tag>
    struct find_if_impl<Tag, when<Iterable<Tag>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            using Result = decltype(hana::index_if(
                static_cast<Xs&&>(xs), static_cast<Pred&&>(pred)));

            return hana::transform(Result{},
                detail::partial_at<std::decay_t<Xs>>{static_cast<Xs&&>(xs)});
        }
    };

    template <typename T, std::size_t N>
    struct find_if_impl<T[N]> {
        template <typename Xs>
        static constexpr auto find_if_helper(Xs&&, hana::false_)
        { return hana::nothing; }

        template <typename Xs>
        static constexpr auto find_if_helper(Xs&& xs, hana::true_)
        { return hana::just(static_cast<Xs&&>(xs)[0]); }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return find_if_helper(static_cast<Xs&&>(xs),
                hana::bool_c<decltype(
                    static_cast<Pred&&>(pred)(static_cast<Xs&&>(xs)[0])
                )::value>
            );
        }
    };

    namespace struct_detail {
        template <typename X>
        struct get_member {
            X x;
            template <typename Member>
            constexpr decltype(auto) operator()(Member&& member) && {
                return hana::second(static_cast<Member&&>(member))(
                    static_cast<X&&>(x)
                );
            }
        };
    }

    template <typename S>
    struct find_if_impl<S, when<hana::Struct<S>::value>> {
        template <typename X, typename Pred>
        static constexpr decltype(auto) apply(X&& x, Pred&& pred) {
            return hana::transform(
                hana::find_if(hana::accessors<S>(),
                    hana::compose(static_cast<Pred&&>(pred), hana::first)
                ),
                struct_detail::get_member<X>{static_cast<X&&>(x)}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIND_IF_HPP

/* find_if.hpp
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
*/