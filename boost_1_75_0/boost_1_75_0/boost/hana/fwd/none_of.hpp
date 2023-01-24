/*!
@file
Forward declares `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_OF_HPP
#define BOOST_HANA_FWD_NONE_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether none of the keys of the structure satisfy the
    //! `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a true-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_of_impl : none_of_impl<S, when<true>> { };

    struct none_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr none_of_t none_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_OF_HPP

/* none_of.hpp
CbONqdTUdiVBahAQE+pm1oFheRv/GmfqYoE0Chq2WdHZ8P7lZ3XgsZmsDHsa4ZoGKI16akTHUfo8bjJT9VZwMYkd+bJDOLX8HfKnZfrQjISxnBN2kFsitYxRv65uO1H6JC9CNU1yba4uLDJ9rZYmU6mkbt0giD38vhc9aOdfQX6mPdnnjMsQ4irqz1vTvNvLvsbbl5aHBJgG33qPbHAe9rCzZWl9sYIntNNJp6dtLl+krxKBuW/5Lxp+uAVdILA8AeXGzlL2aCV8tIkzX+GUSlztJYm3T/DZGnKY8tE1JdEzHPWin9dlJyBpTFQwE+4Lg4rHwOBqQ0cPcMq13hhCrxfCt4APL0AxMfBNd8w0DoAPet2Lpm9GATfNV/45kH8BPRrJHVaGYzGlI8E56eEK1BAt5AzhlunETiKx3DO4keqXnJFROfDjYxc5TOcb451W/hE8CL5NS+SHNHoE328J2L5XGQk4FxGWOStszCETy7azmAigjQrwAaHBLfN7sV6tY+A+Nxu/vX7B/8jMgXP8nkqGE170LLzUc1yhPoSQ7LaiLbRZadj60OeCzqnaPQUqSyb1NqnAoliHXrhdM+B6owhLjICM2iPlK8snIZiCe6rdHkYXsVV1V9jlHnlXLPwH+ZGxf2z2wV2PH2FzjrSc94Q5+JbpumdqRTpr9ERfafdCIOQSt/TGXCAZ6sScuxqGA/NigvsAJz0STR67
*/