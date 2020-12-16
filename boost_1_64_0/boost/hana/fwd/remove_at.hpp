/*!
@file
Forward declares `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_AT_HPP
#define BOOST_HANA_FWD_REMOVE_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove the element at a given index from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_at` returns a new sequence identical to the original, except
    //! that the element at the given index is removed. Specifically,
    //! `remove_at([x0, ..., xn-1, xn, xn+1, ..., xm], n)` is a new
    //! sequence equivalent to `[x0, ..., xn-1, xn+1, ..., xm]`.
    //!
    //! @note
    //! The behavior is undefined if the index is out of the bounds of the
    //! sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which an element is to be removed.
    //!
    //! @param n
    //! An non-negative `IntegralConstant` representing the index of the
    //! element to be removed from the sequence. The behavior is undefined
    //! if that index is not in the bounds of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_at = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_at_impl : remove_at_impl<S, when<true>> { };

    struct remove_at_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr remove_at_t remove_at{};
#endif

    //! Equivalent to `remove_at`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto remove_at_c = [](auto&& xs) {
        return hana::remove_at(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct remove_at_c_t;

    template <std::size_t n>
    constexpr remove_at_c_t<n> remove_at_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_AT_HPP

/* remove_at.hpp
iFK3fVGfJLPOQh2G758WHihsqhQXYQqQypRyIjqzag+qPnqkbo1hCtS5D/nIPuWPTMqJwMAmcPN2/7mi+xfN8rA9eGRJoL+45d3mKB+gRrop5tsrHkzT784CbjftuyZjHI+n8gcvzK5LKvfsGdzZ9Ij8DKwrFzhowGcO1lEs+LF5xbWsqur16N8+G6SzicG1dtPaFPLkbKFbbOr7q03NUbiT2/d+c1S7SSEZWY6fi+ppq1SMF2d+jHYoYuW982bpud/O4arT/smhRx09qGOf4+yxL6bflcVCFK4C3C8vB7ku7hJ3+blvMSgpa8BVStvlWRtS18NA70bbpi2u6N8l6bNuwMEkpE8Refu0e+ntoL6CDHt97PeuG2vyz4CYKyW8OhrpyWJSyIdj8qrwmmhysw4bnIwB1GbbVBGdpoKBT2llzztRQXXJ9USsFOS7D69Kc/hdUIQ1HDA3kmsZRtyvdH16pzinI7RKzGIn1AxaU3QOXsTdDwV6DybMvRRgdRKP9pHCQKjCJg+Ic2NHcjo+IvpEpaAFGbKm7fIAMQvpaqaynK8GdmGn0hzvqR2KIXS+xdDAUdjVS2lBBIZpR1RKInMmpNWaY3kPJrM8q53aOyf/lP0337nuaPcxGGCloWrJOxTpHDoEcSwExzykn8q6QVqePdC40ebVK1xPbRW4PRrAgu4Cckllvd7yc4U4MEBZpPibbld03tzQs+2etvwz8Lt9K8LLSS1XhPqkxBXhT0k8NU/VbcqeW/O+hHkO8MsI2KoYsPkMLCsRGNNLbbBK5ctkdXuoubiy2AletoFFbLhuuEpIjG/NWHFLP5SRFxdZAAwSN/bjMceurmaRfdQii/9K9MPsUAXbQ6ac6BK+dSsdU+1ZM+IXWRKPvyXWDQJW66EF2kVGxcpAJTqLzE5yu8qeGDpi6um9y8oV7vjWrzCjZpfFd+58iqmM9YfHrJQryAIy7NOLCakKqdPkCfj6aIU9VH8G1PvMf/K+x8/AWvFI/Jwqy7eoqZ9Ehw58jSXXMJgpju3BqnacDcyAvfndWwhhhOygqCnhmYsio7QHuHEOqTYo3QLTp8WRflqtXJ66861JUFbo1n0ZpZFCEhgf3fQOUOhNNXXdvgDtf9KJ/9uJcKW2Sm5vrjtC60D+1+QNsjaT298jXp/MzqZacgm1cyXdFV+goqAExZIoX0YXTm3oL/HUiajOlZTSDcbB2i9V/bGJWoYGvAty6pFVTxIPHqaqZ+tDHiIPyjthZksek3orgQIHjkWVbdS1lxLECu0hA+JChrixI3VJNbHROOohXaCIaI7ivcilbeSOem1DN7teZqoo5jJL6SzFcKDzMfZ2X5MMv/HqxuZE/9XZLey/9U0M920RnpacGP7Zx4nwklvAf6d/YvpHsxLD0aQW91/6JIbXt0g/POG7uv+UKf3r6g4lMNk78e5K7qIsOfA1QTcQS0UKcrct1+X1MofXy2HiOBhYEcJgi9rXmqO+AnZHYRKBV2l8MhpSKN3JMqyEeN4P7MUZgrC8HztfoAiXmI9+10qtfL5wRXZb5wu8vzj/RUJtZm/soFxd845syEgLl5rPnxTt+AL4sMDBebZNbRxNJ0bK+5PKk7v21x9A3fw7J9C6HuitO3iR8yVjt4jX1oDxfmC/FEFmdVNT8Nmaicd+kYtWe7ykorQXX9H52vf6sAEErRSFILwA4XspVSSFE1NScpjbkEKhKP26f440Ug2f1DTDE49Ij95J2Gcf/J7M8nN8QAURCh75lq3qewiGAkduPmFKIhe930bQGfzgRE3gSNiZJCK0KP01POXIdI8LUGomfq4A+WeFJh6BP9Ypn5cG956omXjkBaHNREWnz68=
*/