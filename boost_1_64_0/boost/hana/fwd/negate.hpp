/*!
@file
Forward declares `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NEGATE_HPP
#define BOOST_HANA_FWD_NEGATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the inverse of an element of a group.
    //! @ingroup group-Group
    //!
    //!
    //! Example
    //! -------
    //! @include example/negate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto negate = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename G, typename = void>
    struct negate_impl : negate_impl<G, when<true>> { };

    struct negate_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr negate_t negate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NEGATE_HPP

/* negate.hpp
tWttQjjfvJ0pc3a35FF+CedxPbN2acbTmzV+s5B4tFGzmHhX9RvYIf/Mb58mRrVQzwMIDY48Q9SQkuQuX/IRJYDAnZwWLJi4ljeqzvov7brcfyAYl51a9bX9t1z7BdsUbHqPdDktIW/k6Go4ZlDjcAEGxDbk4kWvPlRKcUnLKHbYszj/9qCakA9m3hKeZJy6OKze+Y5kTQrLD0FNNsMmX2oMNy9YTb6EIaTs+usDWLjpVE1vUD/fYM6UfSlJ1f6/KGpqZGiDtuWzw993Q9d26/MBlUj1sbypyhT1kNDbSwhZ4wVFhEqjEdAPlkeP1BEyEiTirpmPRs+sK4nghtUq/cItK4CHG04j14Kwa+9Lau+sKVwMxg2VDetbznW9Xg8JdbkVxJXIjUMYsDWL5onXaKzxlHRZx10QwxbyI2LCCIiuj+8o/GhMbLrGBfR2ZxmH93QbstqTf2cNXnds4FihBeimgzi7Wb+jn/aLbZNBhYropu2QjZ2N2VUw5rQzBZWPvtGEe5ILqQAx2YVveIyDWnpx5m2vq4T4vY/wBzIyuaTvpDefnc9gRH+7Eg==
*/