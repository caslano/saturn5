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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CORE_COMMON_HPP

/* common.hpp
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
*/