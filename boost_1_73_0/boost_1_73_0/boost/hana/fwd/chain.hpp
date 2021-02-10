/*!
@file
Forward declares `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CHAIN_HPP
#define BOOST_HANA_FWD_CHAIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Feed a monadic value into a monadic computation.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value and a monadic function, `chain` feeds the
    //! monadic value into the function, thus performing some Monad-specific
    //! effects, and returns the result. An implementation of `chain` must
    //! satisfy
    //! @code
    //!     chain(xs, f) == flatten(transform(xs, f))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! For a monad `M`, given a monadic value of type `M(A)` and a monadic
    //! function @f$ f : A \to M(B) @f$, `chain` has the signature
    //! @f$
    //!     \mathtt{chain} : M(A) \times (A \to M(B)) \to M(B)
    //! @f$.
    //!
    //! @param xs
    //! A monadic value to be fed to the function `f`.
    //!
    //! @param f
    //! A function taking a normal value in the `xs` structure, and returning
    //! a monadic value. This function is called as  `f(x)`, where `x` is an
    //! element of the structure `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/chain.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto chain = [](auto&& xs, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct chain_impl : chain_impl<M, when<true>> { };

    struct chain_t {
        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr chain_t chain{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CHAIN_HPP

/* chain.hpp
kLQECr6di/Gv2UJelUMldCUQ1+PxcOQMbwa/fjIQr4sQ1HVRzfecEk1KIhGu0LBLsCBin71yLrrD687N6LY77ow04jdFRKAiZ61XxOURGJKMuTJoiQIvtKqlT/5zBNESTIokhtxYxFI1yITZQCKkIixQYo3OQX0/XELYUOgxwUyTgI/qwJHGAwM2oe4dCzyJIUkb1swPJ1RPCiZWq7c02Qn8dK0sjmUBjmn4Bh7EgeSzQEc1lS7tDa5zwtUUgqXXhEgAQWESQjDTWJL/zhylv8JpHjQxU6LBag0ecFWv3Yfcq+NU+AuMuj6jQRylDzLEWuMe9hHCYb3mzqkgjUk8nTLRzM+okQy8O2funeOugHzbjUgDH2TEch6DG4XLjFirh1G5Jg1kgFnKQOCP5lFJUtLbFbp3HGLYSs8zCUMfJkI+J4LdAN3BOiAsqsOQE3QkSNC1AVmbIKeEgyWA2YAaBURhCLhgUxAtfZOctJLQY9wQIk6tYWiq152agNl0NERMFeWyWVX4LJipeX7dLhPKkYqqWDqC/TtmUuVVnJMnCWoTX+/frFKyqt1JZana1hLtlMwfhMGfFmF/KfaB0lvZ8MKApTrv2rQ76iXeTpY0UDrXCkY9zFtLAaEHs6CuK6wg4EbEiwVGEGqmnoMd
*/