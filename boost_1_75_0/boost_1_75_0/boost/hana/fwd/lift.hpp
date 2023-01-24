/*!
@file
Forward declares `boost::hana::lift`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LIFT_HPP
#define BOOST_HANA_FWD_LIFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Lift a value into an `Applicative` structure.
    //! @ingroup group-Applicative
    //!
    //! `lift<A>` takes a normal value and embeds it into a structure whose
    //! shape is represented by the `A` `Applicative`. Note that the value
    //! may be a function, in which case the created structure may be
    //! `ap`plied to another `Applicative` structure containing values.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an Applicative `A`, the signature is
    //! @f$ \mathtt{lift}_A : T \to A(T) @f$.
    //!
    //! @tparam A
    //! A tag representing the `Applicative` into which the value is lifted.
    //!
    //! @param x
    //! The value to lift into the applicative.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lift.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename A>
    constexpr auto lift = [](auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename A, typename = void>
    struct lift_impl : lift_impl<A, when<true>> { };

    template <typename A>
    struct lift_t {
        template <typename X>
        constexpr auto operator()(X&& x) const;
    };

    template <typename A>
    constexpr lift_t<A> lift{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LIFT_HPP

/* lift.hpp
Y69eqhpDZKg3Lu86NvahLDNXUbxPr5wVWG2OnWuG1UIHoSh+c6Mil0iWilpjvbygQI4H6O+spX5uF3MJt/ous/PBZ3kFjef7xPuVzFBRF3cKw+9CDoyuXzhMt9L8PoxecqEKDZkUrhu461DFyeEELv5jh7z4PYV2oiVprjJi/oj5cN4xP/S84pt6qG75c42WmKnwZGGyqMy9aRGQxdtJntG33UdLvsib6ejb1H2DUPmJa/sOdN9Dp8dremNSPzxB91rOR/hziavOHJMx0NAyoj3ZXT6hJ2dfAaIY7w6gZunTrIBQHXhRsTQllRNRoRripc0bVGlTTh5cUwzfdAmkEXmLR03vMXbiRheAoNjAudGARmlFEq37bnIFzarnTbb2mVu/9xGYqZ8SBw/rpb7jH15E52/Jj0jmJ8fiuliBNWPFdSia5Gi8bXJm481y+3v4CEEcFMuZx3LcayyMW0EpRCNS6J4aoSgqIG47U1uMMc24GK/RUBadIgzyVVziSSk8JY1QntbqtNIBJx2rLrWGUhBvv1ijFaqwZhqtThGdz3d7RTaK6OzIVY30Ph7NAmqdT3R8LJZ7y/FKXXRNM0lxlylVpXof+WU33J/q2K9Ev3+0tp7TEMJunNxdofSA1YkwmtgKsTyCttzY3XvxBzUm8eO6y8Gvy6V+SQzJoX2OkpYsPLXGLAfFPG4s0OJ6V5alYt9K5FZqoqoZwTzJ
*/