/*!
@file
Forward declares `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_BACK_HPP
#define BOOST_HANA_FWD_TAKE_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_back(xs, n)`
    //! is a new sequence containing the last `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_back = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_back_impl : take_back_impl<S, when<true>> { };

    struct take_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_back_t take_back{};
#endif

    //! Equivalent to `take_back`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_back_c = [](auto&& xs) {
        return hana::take_back(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_back_c_t;

    template <std::size_t n>
    constexpr take_back_c_t<n> take_back_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_BACK_HPP

/* take_back.hpp
94RuDrZnk2gmjE2ihQCY6lUWjszdNy2FMK9a6SDiVdcG8i4hj9k6pHkAYF0VEjbSJcpDiZOOVghv0jCD0qY46FZCmmQwTaRHlHfDecKhN7SBYzwR0KP5Tt1XJN1pwxXAdlp4wchONXg419ERdlMdiLTdem6i47c1jueIvQlDcyr4vCxHtzGe5GgG9nCcdye/9Tp8dGGRXs2u0zv08IKksIHm1OhgeU5dMfoRBklBO9exi9Rzxi7SRsL2KINNxLFwNO4QTYnqpgI4kaR3CCmSqsNYUV0BscEoM8fPixo4VvNogwm0AG7Ugg5IjpwIGo849DrwU3AZe362sX3z5+CSUmvf4AzcbO5KyLQAbEecgxv9AvSkQ5dWvgWPsuhWvo2GjnmgBWRoyIIIe+jBs26s/LGH2JUfG1tIvcUFFyafwEcXBluDwosGAHB80cbZGWDAxB1WdIYYEKOjYoyaPyKCjAZE6OMQUj+GByJkalw3A34kQudrzociFATZ8wnb7ucTZM23xRMK8lK6ruzj7kcj2p17nsmQO3/m6PwZ8AEJ0+xDx32tqecM/Pqdvg5c3KnXgSttW/FeP+h14H5XrwMX9SsH5jDPWi5WLWu5Nm5bdGcsty7atc0j47pCfn0FE9QV+hseiIiu0N7ucIdz
*/