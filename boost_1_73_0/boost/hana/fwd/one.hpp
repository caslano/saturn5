/*!
@file
Forward declares `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ONE_HPP
#define BOOST_HANA_FWD_ONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the `Ring` multiplication.
    //! @ingroup group-Ring
    //!
    //! @tparam R
    //! The tag (must be a model of `Ring`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/one.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename R>
    constexpr auto one = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct one_impl : one_impl<R, when<true>> { };

    template <typename R>
    struct one_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename R>
    constexpr one_t<R> one{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ONE_HPP

/* one.hpp
wg+Y+Dcj3GDsVtYjvNqE1yG8YY24zLrttVG4z7r9rjujcKG1bs2dr4s6vo1r1t+24bboXRt80XvugoNAZ8OaNZ7IDdGN6+9es2HjHXfdufINt61FjBONDon5O/40uA12LQZnvXKH8uVwukEOp4dIOz2ECVuka4VRIxsKC/apIJfSUJke33Iydo89puYIVYy3QhVelc08sXc1cGRhSARpjlSG/LhsVLY20DyXZz4DmAx8sSJc
*/