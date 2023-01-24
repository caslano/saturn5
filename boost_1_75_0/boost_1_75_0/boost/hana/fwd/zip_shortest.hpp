/*!
@file
Forward declares `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip_shortest` produces a sequence
    //! whose `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip_shortest` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip` instead, since it can be more optimized. Also
    //! note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_impl : zip_shortest_impl<S, when<true>> { };

    struct zip_shortest_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_t zip_shortest{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
hk1RUZe+laUDBhgABuEB4qEVzFiDCKge9CCLoggEIY0Bu4Cnru6DC6D8Y801oY/BNp4WscByo9iJ4iAArFDuJmTHBYFAZ8ieo0WBG0Cq8M5zPBtBdRwaNFJmo3ciBulOC9rXCkLXd1QdMh67qsvcEBbN9gLPsi3wAZDhG2BLMhdMBWdBc0NAARVgADU9A/4AVDYDe6m2H5PBdPwQ1snWfQybPn3lWqEG6hNdINGWEXm2BeaIbB2yDBsFjaC6sWszMwAraipGqoeaaUYwgLDOnhcHDoym5qA7H/YBkIGNAzWwA9NnduywyAPtQlNzoK6hl12CyIK58oEjSEqkQ3XAvY5Irds+dInDApgIIgxJY0xqHrob5LVsD4wEqtjQUVHEQsQ+NrgGCLQdKDkHCiUihW9ZoQOLFcPuedAEUFHMdyIDuLMC+G++rtq2qcVa4BixC4nzbd82HMAeQud6amgZsDax6kYhs9FmEEDJq2oUugwGg97EGDVGYLmwTG5gQGNAM2vQkTAffgQu9MEmTmSqIKCHAgy+TOxqwH3kAEYPo4OBwf8xFjMIYIliA04L6BlYGpiHGRgj+VWRDUZA+GH6nu2Zfkic7MDEMqY78AN0l2yjCiQZPpSXpYFNGVwPaAtYeLgIsNrgBBMojsgIg8s9A/YFZPFjDxaMC4MJdKlkwqBSYrgs+A8SxwwV6IGxgjHwfRvIcU1mWZB/CA+Q
*/