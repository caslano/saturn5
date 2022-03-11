/*!
@file
Defines `boost::hana::count_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COUNT_IF_HPP
#define BOOST_HANA_COUNT_IF_HPP

#include <boost/hana/fwd/count_if.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto count_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using CountIf = BOOST_HANA_DISPATCH_IF(count_if_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::count_if(xs, pred) requires 'xs' to be Foldable");
    #endif

        return CountIf::apply(static_cast<Xs&&>(xs),
                              static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Pred>
        struct count_pred {
            Pred pred;
            template <typename ...Xs, typename = typename std::enable_if<
                detail::fast_and<
                    Constant<decltype((*pred)(std::declval<Xs&&>()))>::value...
                >::value
            >::type>
            constexpr auto operator()(Xs&& ...xs) const {
                constexpr bool results[] = {false, // <-- avoid empty array
                    static_cast<bool>(hana::value<decltype((*pred)(static_cast<Xs&&>(xs)))>())...
                };
                constexpr std::size_t total = detail::count(
                    results, results + sizeof(results), true
                );
                return hana::size_c<total>;
            }

            template <typename ...Xs, typename = void, typename = typename std::enable_if<
                !detail::fast_and<
                    Constant<decltype((*pred)(std::declval<Xs&&>()))>::value...
                >::value
            >::type>
            constexpr auto operator()(Xs&& ...xs) const {
                std::size_t total = 0;
                using Swallow = std::size_t[];
                (void)Swallow{0, ((*pred)(static_cast<Xs&&>(xs)) ? ++total : 0)...};
                return total;
            }
        };
    }

    template <typename T, bool condition>
    struct count_if_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred&& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::unpack(static_cast<Xs&&>(xs),
                detail::count_pred<decltype(&pred)>{&pred}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COUNT_IF_HPP

/* count_if.hpp
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
*/