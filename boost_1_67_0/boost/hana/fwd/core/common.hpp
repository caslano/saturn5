/*!
@file
Forward declares `boost::hana::common` and `boost::hana::common_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_COMMON_HPP
#define BOOST_HANA_FWD_CORE_COMMON_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! %Metafunction returning the common data type between two data types.
    //!
    //! `common` is a natural extension of the `std::common_type` metafunction
    //! to data types. Given two data types `T` and `U`, we say that they share
    //! a common type `C` if both objects of data type `T` and objects of data
    //! type `U` may be converted (using `to`) to an object of data type `C`,
    //! and if that conversion is equality preserving. In other words, this
    //! means that for any objects `t1, t2` of data type `T` and `u1, u2` of
    //! data type `U`, the following law is satisfied:
    //! @code
    //!     to<C>(t1) == to<C>(t2)  if and only if  t1 == t2
    //!     to<C>(u1) == to<C>(u2)  if and only if  u1 == u2
    //! @endcode
    //!
    //! The role of `common` is to provide an alias to such a `C` if it exists.
    //! In other words, if `T` and `U` have a common data type `C`,
    //! `common<T, U>::%type` is an alias to `C`. Otherwise, `common<T, U>`
    //! has no nested `type` and can be used in dependent contexts to exploit
    //! SFINAE. By default, the exact steps followed by `common` to determine
    //! the common type `C` of `T` and `U` are
    //! 1. If `T` and `U` are the same, then `C` is `T`.
    //! 2. Otherwise, if `true ? std::declval<T>() : std::declval<U>()` is
    //!    well-formed, then `C` is the type of this expression after using
    //!    `std::decay` on it. This is exactly the type that would have been
    //!    returned by `std::common_type`, except that custom specializations
    //!    of `std::common_type` are not taken into account.
    //! 3. Otherwise, no common data type is detected and `common<T, U>` does
    //!    not have a nested `type` alias, unless it is specialized explicitly.
    //!
    //! As point 3 suggests, it is also possible (and sometimes necessary) to
    //! specialize `common` in the `boost::hana` namespace for pairs of custom
    //! data types when the default behavior of `common` is not sufficient.
    //! Note that `when`-based specialization is supported when specializing
    //! `common` in the `boost::hana` namespace.
    //!
    //! > #### Rationale for requiring the conversion to be equality-preserving
    //! > This decision is aligned with a proposed concept design for the
    //! > standard library ([N3351][1]). Also, if we did not require this,
    //! > then all data types would trivially share the common data type
    //! > `void`, since all objects can be converted to it.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/common/common.cpp
    //!
    //!
    //! [1]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3351.pdf
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, typename U, optional when-based enabler>
    struct common { see documentation };
#else
    template <typename T, typename U, typename = void>
    struct common;
#endif

    //! @ingroup group-core
    //! %Metafunction returning whether two data types share a common data type.
    //!
    //! Given two data types `T` and `U`, this metafunction simply returns
    //! whether `common<T, U>::%type` is well-formed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/common/has_common.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, typename U>
    struct has_common { whether common<T, U>::type is well-formed };
#else
    template <typename T, typename U, typename = void>
    struct has_common;
#endif

    //! @ingroup group-core
    //! Alias to `common<T, U>::%type`, provided for convenience.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/common/common_t.cpp
    template <typename T, typename U>
    using common_t = typename common<T, U>::type;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_COMMON_HPP

/* common.hpp
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
*/