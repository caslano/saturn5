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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PARTITION_HPP

/* partition.hpp
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
*/