/*!
@file
Defines `boost::hana::partition`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PARTITION_HPP
#define BOOST_HANA_PARTITION_HPP

#include <boost/hana/fwd/partition.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto partition_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Partition = BOOST_HANA_DISPATCH_IF(partition_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::partition(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return Partition::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <bool ...B>
        struct partition_indices {
            static constexpr detail::array<bool, sizeof...(B)> results{{B...}};
            static constexpr std::size_t left_size =
                detail::count(results.begin(), results.end(), true);
            static constexpr std::size_t right_size = sizeof...(B) - left_size;

            static constexpr auto compute_left() {
                detail::array<std::size_t, left_size> indices{};
                std::size_t* left = &indices[0];
                for (std::size_t i = 0; i < sizeof...(B); ++i)
                    if (results[i])
                        *left++ = i;
                return indices;
            }

            static constexpr auto compute_right() {
                detail::array<std::size_t, right_size> indices{};
                std::size_t* right = &indices[0];
                for (std::size_t i = 0; i < sizeof...(B); ++i)
                    if (!results[i])
                        *right++ = i;
                return indices;
            }

            static constexpr auto left_indices = compute_left();
            static constexpr auto right_indices = compute_right();

            template <typename S, typename Xs, std::size_t ...l, std::size_t ...r>
            static constexpr auto apply(Xs&& xs, std::index_sequence<l...>,
                                                 std::index_sequence<r...>)
            {
                return hana::make<hana::pair_tag>(
                    hana::make<S>(hana::at_c<left_indices[l]>(static_cast<Xs&&>(xs))...),
                    hana::make<S>(hana::at_c<right_indices[r]>(static_cast<Xs&&>(xs))...)
                );
            }
        };

        template <typename Pred>
        struct deduce_partition_indices {
            template <typename ...Xs>
            auto operator()(Xs&& ...xs) const -> detail::partition_indices<
                static_cast<bool>(detail::decay<
                    decltype(std::declval<Pred>()(static_cast<Xs&&>(xs)))
                >::type::value)...
            > { return {}; }
        };
    }

    template <typename S, bool condition>
    struct partition_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using Indices = decltype(hana::unpack(
                static_cast<Xs&&>(xs), detail::deduce_partition_indices<Pred&&>{}
            ));
            return Indices::template apply<S>(
                static_cast<Xs&&>(xs),
                std::make_index_sequence<Indices::left_size>{},
                std::make_index_sequence<Indices::right_size>{}
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_PARTITION_HPP

/* partition.hpp
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
*/