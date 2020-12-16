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
zmqleLxQPGoAcPIMcVRRBKrhHJhZV6S7KCTiClhxKYE+/25Q6a8x0m+hXApFt0lxMYgJ+f7O+nPUmfqGXAkzeG4jMmHb3SsefNooREk+ZRudHAeUYdw1B5XoEX+TCvvEI9LCXUUwJuiquyQspyrM4nFPwOQpas+KXy/87sP3Bvx24FeMb0tsOW1t/U96EgxXok13tPpvXNYXiglYEPMlMgkYe1be3B2JLlDIDHz7a2JTi3nwNT6fwHptSV0UTXqPnCY+8Mu3dVLj1zSp+WHUlfXmhzOnGvPDTPP8YNj/uof5S0j1t89uLZePzEGm+grEYKBQgK554Aq1lkpRu8VD9fUULW8KxHWzDWlSL175pOH+0wJxLrhM3Ztk1IUBR4H47vbYgjxc4rYEM0F7M3gtnG7sumVONK3MH1Irc4oeepcYNA3SLbdF7pDQsswWW5ZJsXnZPSw7e9HmhDR6i7avPMVVupc+HEN/oYxoQCAz8eRXWOoN5IVHD96spjgR5DD16AJxoV1HPzgUeNwyEEOKSnA6SlAgNv+Rp8I0pMI4k9UmXoRnwF4gJt+i5pBErMoQrlcsJa9dypWppMx2UON/z5Jab3/QBEyqWOLaaEKl8xtFhIxuBEpkz5Srjb3j49bT6Xr7u/H2iutmGe1/lJLAkMzkHeTAjRzgpQBaOQsCkwOxpu4uelSjBUponY02cGbQ1mwa4mG5fTZEnNrwFL1dM9YFXZ5IUnkOtVt5XrrH2FyoSVLrcu4SmDJ9Wts1rzkpjUfGZ3r/+Ri9UUrOtiahi8IipVcUt1ZtnE29lrzKbMqrJ8lMS+woyS1nk7AFCNI6o9dtqBLxjhTAaVUwU8U1RkHH3KZzC8pz3GjU57+mcXX7D3/U14sxSfusG2UTnl3UcD4N77mueABmUtsqnkl3Pp/sVLVpFh/rC0ZeOqaqymaPNNP8cvXt+gJRq5JzD9ff9zUfcx/YqpaDu2re4qHczSuEquuQXW1HU5AG5KAnySLP/RD1GyjpSNQsoMpesaT+XPrFUrneO/OOmFBarRPN0yokFuLCR5Vm7lxauj1yFbeciucVd92oZvNOFL33PGZvuhMDbVWxMqPKhfXtIyuTnT/gdyPqcB/eKXhfhN9c/J7A76/ws1j1FV6izZ5o/+c8sbVe0n/U0q7QH6ZN6f20FhIYnULcHbvuv2fVUHlFwtA0eolO02jZTUcUj/VrKhnuoZjDjUbsq9KeulJNsM9cHptgD83d6vdTKf7bB8FSMXFH1NbXoPv4741D1if2Y44ja6UXXC7fxTzTSlOALVLnlPLv0fXl3wFjfq6oNz8PY/nPHYZ+HeLnY8rxELvswYdLLJ9ONahd5yoQi8PELiRhADhWFaVrtY5VI05CTa371H7Uh3CfrBynsKN8kC1xA9Hyfq0dvydVJG/50O7YWD2oC9dAyOnSLrbz6YZ/xYOG/5Mkfbywe+LmcuzPhb+1TXUpebY1KyHkDK+zhdfb4D9td/jg/uCwBdZzE0KnhA8eCOYsyLGem2sNdQ4fPBjssyAn4dzchNDR4YO4SnhBTuK5uYnBbugExr0oNK4w4PKhdnc+CziHVfL5hKEpMBM91I4SVA212YgetK4a6tZTcEqVrL2eLOBgpqK4nEfweKbPBB1Rdv+Bo7Sg9X79g2bjfdJvg3wKaJzLK7aXUqONvBUeHTUR/goXh8z3naK9uU7YcRp//vB07c35eSeX53Uf5VlX7fTOH36SGCPNsIAsnaolYSINSD2LbssVNWtv7YVaYApNL5RTVkCqmL7QWMoe1kJVfyCUJT3mTNIrv8C77quE3AWXJC7wWxfMSND3g+e7Fny44O0FuxfsDX9lDe2ef0k=
*/