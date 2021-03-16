/*!
@file
Forward declares `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSECTION_HPP
#define BOOST_HANA_FWD_INTERSECTION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct intersection_impl : intersection_impl<S, when<true>> { };
    //! @endcond

    struct intersection_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr intersection_t intersection{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSECTION_HPP

/* intersection.hpp
FdV5igYYsZWhStvgJ8jUaSg/r2Jjf52umnmS8MESfDoUqsrLwUzTUeSr4ivQH2RpA9oIWNe1rn4N9RGy/PDqmlnvQRJfNZ50WK0PV/LHqw8CWFNHOJ7A49Vj4KoRcVcr8tOneHIoh66w5dOArnC5dxpdvQJXiXSFO9hi6MqLkC8/uGoRIS+AcIWtliZ0NS9CnvzgCoebG7MV+P8vHl69EyG/gHC1T3TrxZgrrFx4AgqPvuBJrolwFUt3Z8QY3bk=
*/