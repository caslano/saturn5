/*!
@file
Forward declares `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_RANGE_HPP
#define BOOST_HANA_FWD_INSERT_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Insert several values at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and any `Foldable` containing elements to
    //! insert, `insert_range` inserts the elements in the `Foldable` at the
    //! given index of the sequence.
    //!
    //! @param xs
    //! The sequence in which values should be inserted.
    //!
    //! @param n
    //! The index at which elements should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param elements
    //! A `Foldable` containing elements to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert_range = [](auto&& xs, auto&& n, auto&& elements) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct insert_range_impl : insert_range_impl<S, when<true>> { };

    struct insert_range_t {
        template <typename Xs, typename N, typename Elements>
        constexpr auto operator()(Xs&& xs, N&& n, Elements&& elements) const;
    };

    constexpr insert_range_t insert_range{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_RANGE_HPP

/* insert_range.hpp
SkOVodpQY6gz1BsEY4hRYQw3RhgHGJVGozHaGG9MNCYbpxvTjTnGBcZ843LjGuM64wbjJuMWY5Gx2FhhrDRWGauNNcY6Y71RMIWYFKZwU4RpgElpMpqiTfGmRFOyabop3ZRjWmDKNy03rTGtM20wbTJtMRWZik0VpkpTlanaVGOqM9WbBHOIWWEON1MQDhcmXNFc1wRp22jX2zbaNtu22nbZyuHNjsCTkR+7AB8ms4cyDxYJ76W1W+2x9gR7kn2yPdWeaXfZF9kTHA0UbG9gpo9F5cYVpWklSVQmiatJqjJdmanMUbqUC5SLlPnKeqWgClEpVOGqCNUAlVJlVEWr4lWJqmTVdFVrHgzjbBFY2B8Bix4Am1bCqo2w62hYdjxsOxHWnQz7ng4LT4eN58DKF8DO82Hpy2Hra2Dt62DvG2Dxm2DzW2D1RbD7Ym2+udC83LzKvMZstcXaEmxJtsm2VHh8l22RrdC2yrbW9j8vq0L7Kvta+3r7Rvtm+1b7Lnu5/YD9iP24/ZT9tP2CvcEuc4Q6why9HZGOKIfWYXXEOhIcSY7JjlRHpsPlWOQodKxyrHWsd2x0EPP02fm1TNcV8CaJ0GHyJoXwI+ugveRHDsCDVENvLzDNDYfORsF3RMN7kNamQ18XwW+sYZ5jq+FZ64vWDdbN1iJrqfVra5X1lLXOKrF1tN1h62e7z2axxdnG2OrsNscox5OOHY56
*/