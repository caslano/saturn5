/*!
@file
Defines `boost::hana::group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GROUP_HPP
#define BOOST_HANA_GROUP_HPP

#include <boost/hana/fwd/group.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs>
    constexpr auto group_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Group = BOOST_HANA_DISPATCH_IF(group_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::group(xs) requires 'xs' to be a Sequence");
    #endif

        return Group::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr auto group_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Group = BOOST_HANA_DISPATCH_IF(group_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::group(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Group::apply(static_cast<Xs&&>(xs),
                            static_cast<Predicate&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Xs, std::size_t ...i>
        constexpr auto get_subsequence_(Xs&& xs, std::index_sequence<i...>) {
            using S = typename hana::tag_of<Xs>::type;
            return hana::make<S>(hana::at_c<i>(static_cast<Xs&&>(xs))...);
        }

        template <std::size_t offset, typename Indices>
        struct offset_by;

        template <std::size_t offset, std::size_t ...i>
        struct offset_by<offset, std::index_sequence<i...>> {
            using type = std::index_sequence<(offset + i)...>;
        };

        template <bool ...b>
        struct group_indices {
            static constexpr bool bs[sizeof...(b)] = {b...};
            static constexpr std::size_t n_groups =
                    detail::count(bs, bs + sizeof(bs), false) + 1;

            static constexpr auto compute_info() {
                detail::array<std::size_t, n_groups> sizes{}, offsets{};
                for (std::size_t g = 0, i = 0, offset = 0; g < n_groups; ++g) {
                    offsets[g] = offset;

                    sizes[g] = 1;
                    while (i < sizeof...(b) && bs[i++])
                        ++sizes[g];

                    offset += sizes[g];
                }
                return std::make_pair(offsets, sizes);
            }

            static constexpr auto info = compute_info();
            static constexpr auto group_offsets = info.first;
            static constexpr auto group_sizes = info.second;

            template <typename S, typename Xs, std::size_t ...i>
            static constexpr auto finish(Xs&& xs, std::index_sequence<i...>) {
                return hana::make<S>(
                    detail::get_subsequence_(
                        static_cast<Xs&&>(xs),
                        typename offset_by<
                            group_offsets[i],
                            std::make_index_sequence<group_sizes[i]>
                        >::type{}
                    )...
                );
            }
        };
    } // end namespace detail

    template <typename S, bool condition>
    struct group_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred, std::size_t ...i>
        static constexpr auto
        group_helper(Xs&& xs, Pred&& pred, std::index_sequence<0, i...>) {
            using info = detail::group_indices<static_cast<bool>(decltype(
                pred(hana::at_c<i - 1>(static_cast<Xs&&>(xs)),
                     hana::at_c<i>(static_cast<Xs&&>(xs)))
            )::value)...>;
            return info::template finish<S>(static_cast<Xs&&>(xs),
                std::make_index_sequence<info::n_groups>{}
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto
        group_helper(Xs&& xs, Pred&&, std::index_sequence<0>) {
            return hana::make<S>(static_cast<Xs&&>(xs));
        }

        template <typename Xs, typename Pred>
        static constexpr auto
        group_helper(Xs&&, Pred&&, std::index_sequence<>) {
            return hana::make<S>();
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return group_helper(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred),
                                std::make_index_sequence<len>{});
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return group_impl::apply(static_cast<Xs&&>(xs), hana::equal); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_GROUP_HPP

/* group.hpp
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
*/