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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_COUNT_IF_HPP

/* count_if.hpp
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
*/