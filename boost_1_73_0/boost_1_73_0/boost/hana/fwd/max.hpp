/*!
@file
Forward declares `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAX_HPP
#define BOOST_HANA_FWD_MAX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the greatest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo Can't specify the signature here either. See `min` for details.
    //!
    //! Example
    //! -------
    //! @include example/max.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto max = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct max_impl : max_impl<T, U, when<true>> { };

    struct max_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr max_t max{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAX_HPP

/* max.hpp
IexsQfEbYMNnITHM+J80lHp0ELxA+YNSD/jcZaQNbyIvwQHsFnmBZiESVFa+qPcg2GXoQXFTf9pK8iFQr9iDYkrS5LN5xh5jCU3zADpnZ6fwAbrH3U4LeiRlNAFP0nRMs8cWfImKnl9j8vx8JOgvLaASSHJUqfJjJkDwifxOMgr4nrCQpoJGQAREVIQZG+MHS0HGFCYsoWAOhve2c9WC7zELY6VkznMQMc+TCGLyRCGjIWVPpY4ZySTwCYqj8ogJiQpzyXh6hLYpSJpNhdKhzJNEcCBPhCVkjIaIhFjKmfjcbod5liD7dsRD0Q4X0z+K5fR1JvdIYkrmwGcSJIdc0BYoZAumPGIT9USHYOcsHydMxK03Nmgqjdo8A0GTROlCOUZFSZuCV7mnpWAwQ8ZMqofgqVCmvsd8ugREPyotkzxL0RD6AUERRze3IMf9lBXgYuYLE5VPCwdvDM0b3wh4imRgz/DA9vZgTAQTLfhq+9eDkQ9fDdc1HP8eBpdgOPdK2Y3t9DD0DI1lQJ9nGRVoPAM2nSWMRpXN/6+1G419loZJHlHYU9ELBJX57CjeUwMTKDNH1Bx5VnDl3dg+bqaXpV7H89b6rpyR3y+7Hxpqn9QHvw76l57XXxPyzGvDcaz+QZ0SMoqIJAWfdrWp
*/