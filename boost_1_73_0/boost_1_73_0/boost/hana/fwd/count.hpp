/*!
@file
Forward declares `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COUNT_HPP
#define BOOST_HANA_FWD_COUNT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in the structure that compare equal to
    //! a given value.
    //! @ingroup group-Foldable
    //!
    //! Given a Foldable structure `xs` and a value `value`, `count` returns
    //! an unsigned integral, or a Constant thereof, representing the number
    //! of elements of `xs` that compare equal to `value`. For this method to
    //! be well-defined, all the elements of the structure must be Comparable
    //! with the given value.
    //!
    //!
    //! @param xs
    //! The structure whose elements are counted.
    //!
    //! @param value
    //! A value compared with each element in the structure. Elements
    //! that compare equal to this value are counted, others are not.
    //!
    //!
    //! Example
    //! -------
    //! @include example/count.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto count = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct count_impl : count_impl<T, when<true>> { };

    struct count_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr count_t count{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COUNT_HPP

/* count.hpp
GINXcbzg4gpdjzMP2czNMVlcRt0oohjGsdJNyB5Tvj0q5pvXQI3C7u2exUShBvfwtyaxvVF90yMO7gKsy/TL7srPZn0BCNTzQPMBW/6V2mdBpnqOqSinUAmxDK/n5a1BB4cUVPu+NgZzZcDYvjWBROXmeoG1BViFjHU3uH5UXiTAsv+Uxh+t9Uzz+ys+p3yr+4eoSxT9nkMQBx+HjfJZvpQyd8rsfVW9t0+if32HbYmTYrawcfM4DYlYF+ZYdQmSpg17U1ZPilhKR4+NyJAzGZ0EsufpIoyNeMzaSGog9bJofAeyJuIUTCInJklSnNlTj+k2ehY5tSD/5/voYfPvAdcqcwGbjiAWk35yZW2yxuuSYM3m9pEpycs9+rBLALa4r/ajzSsAWF5jHU4iHiCMvhPtkjtmbhgV5QEaOBUwAUXhBCgeGWDytZ6Z1cDtx7exYMuarMv8aWrZzd5g9b2BDcqSV+3FTu317fhy8LHvjLsfOnjN+uwUPvo1rn0/iqaCf0MGC0KV9ISSovTjHFK9rtLsizjwBCTDu9hghk3yGzqTnZBCkYVGIjPz1x5TuLtbbDTVydn2k6TRVE/uFESwwoUqIbQNp1Vz3fy9rt9fdZz+YOyc33Z7Y6fbL8NOmhqrh+F1PyMB302bdiMO
*/