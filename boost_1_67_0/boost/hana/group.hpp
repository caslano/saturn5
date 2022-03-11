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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GROUP_HPP

/* group.hpp
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
*/