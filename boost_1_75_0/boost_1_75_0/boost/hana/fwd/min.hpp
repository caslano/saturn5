/*!
@file
Forward declares `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MIN_HPP
#define BOOST_HANA_FWD_MIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the smallest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo
    //! We can't specify the signature right now, because the tag of the
    //! returned object depends on whether `x < y` or not. If we wanted to be
    //! mathematically correct, we should probably ask that `if_(cond, x, y)`
    //! returns a common data type of `x` and `y`, and then the behavior
    //! of `min` would follow naturally. However, I'm unsure whether this
    //! is desirable because that's a big requirement.
    //!
    //!
    //! Example
    //! -------
    //! @include example/min.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto min = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct min_impl : min_impl<T, U, when<true>> { };

    struct min_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr min_t min{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MIN_HPP

/* min.hpp
WhxZP6Ukd2P1qsNTWSazqJ4LR8H/DndGxnMBrKG1BydzIbXqfv6NVKf4Vr7XqudHXZcVZ/QPEgkOPeEWJe7nPH7+OLXli7ArM/AfuGDbZVnIrcxdFd26oAZsZNRztfW8wXwHStU9vQskgIvt6isGE7Xl7wokYioEKz+ijF4wQxkfVYvSR92Z41SCRbB4Hl9t6FKgqm6W1yLj/2DqqVkfZ0BAVIITKOyvcyaEmHrGO8d2W35kY5Y7dV9OHmQ2dSuNenoJrpJRqQkCZYlG8uiF2Ri7Oy4vWDa2ZViIPXyZtIO2M4nqnBj4+7W/lOBW5uV1oT5ZKMzBLvjKs+yjoqSxNpjr51HSfu9Ab+6+JQUwWMknq5mziROnGJaApm9/fJQiFCNUSqxXz2/PgeaP0O/Q2PWv9BJNYYC/8F9+a+jL/kKb4et3BQMKnYCFph8ERcFmskQ92lk7Yg8TAHfR17GHlnzQc9+5vBl5yNnj0nS3J5Ot3bh9PPgEdFoAEFecdt049vU3KraUHy61bpxdZn45Mh3gPubrHLosFT+miEvA33FEtoi/ErKOm41+RqnUfzcCTOXRbPkurH2W8npp5EvCan2SlcI+GMS4uMxyiu+zTMOytUGZA8DiWAph39ksRXbtXZhgWvS5uoXwvVUTfN7d/YjRSpKM2t4gkKYwhHHbCtiVUdq3uOi1zAsH0Ye+2MFkYZZ1e4tVneKDo/ov
*/