/*!
@file
Defines a replacement for `std::decay`, which is sometimes too slow at
compile-time.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_DECAY_HPP
#define BOOST_HANA_DETAIL_DECAY_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::decay`, except faster.
    //!
    //! `std::decay` in libc++ is implemented in a suboptimal way. Since
    //! this is used literally everywhere by the `make<...>` functions, it
    //! is very important to keep this as efficient as possible.
    //!
    //! @note
    //! `std::decay` is still being used in some places in the library.
    //! Indeed, this is a peephole optimization and it would not be wise
    //! to clutter the code with our own implementation of `std::decay`,
    //! except when this actually makes a difference in compile-times.
    template <typename T, typename U = typename std::remove_reference<T>::type>
    struct decay {
        using type = typename std::remove_cv<U>::type;
    };

    template <typename T, typename U>
    struct decay<T, U[]> { using type = U*; };
    template <typename T, typename U, std::size_t N>
    struct decay<T, U[N]> { using type = U*; };

    template <typename T, typename R, typename ...A>
    struct decay<T, R(A...)> { using type = R(*)(A...); };
    template <typename T, typename R, typename ...A>
    struct decay<T, R(A..., ...)> { using type = R(*)(A..., ...); };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_DECAY_HPP

/* decay.hpp
URWBxAd45CDNsto+Xg3HyRatfKtBVhWe1OpRnU0KGNBJpgm0dJ6i0Asy5KSAG4ltjG5tRJ4W96HGB6bhn+2iRrYrRizmKIsAmmXURCZxMim8EN8t9I42iNsEY2mAXiYdrhQUnBK/JtRoAnT6gFsTx3/prYkU0aeI5jHXJDa4m5C/PBTHFmIGCYMYg+5syySxv+hyAs/km4nwM/Qm/Y83gl86lpAuPOaDZCSJ8EHwN4dDGHHNkHWRNnIF4/pfeQnh+NtdQtjkykFKp6ZT26kKT+DG8cofr2UYn4X0VNP1YOWpgDtk9rxVy+D9xFZJHuSO0gEbVCD1Ckc46NUU4VEp2himoHUQqrc1T5Xiro2IEJt2vPKWc/f+Id2mgk1s2jHJ8SLMmx/fV+9XhrI4EycTm3YsoloId6iNhszjZGw8tzHoxwsWrvCk3Oix0g3FzWKDFcdV/PvaW0k7c1Mtj1oFX6HSj4hJ1xyN7DFsKjf0VGN7mwQdrOBHCwP2PvFwE2KvemgSRA3GPeLXGH9rKM0Vcqilobp4DWe4nqDFDscibXVF4Y6EDdKFSmTRFeHyvtvbiTJMOAMoANCZDilVi/1dPT86ln3oqkVySswJNIWnp0ZmrifoFrhY1vIq5IFnoaOiPo0zdb4JBd5NsAyY
*/