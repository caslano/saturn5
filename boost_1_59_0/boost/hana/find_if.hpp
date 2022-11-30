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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FIND_IF_HPP

/* find_if.hpp
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
*/