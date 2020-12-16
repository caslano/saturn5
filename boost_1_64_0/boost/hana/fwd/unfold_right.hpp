/*!
@file
Forward declares `boost::hana::unfold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNFOLD_RIGHT_HPP
#define BOOST_HANA_FWD_UNFOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Dual operation to `fold_right` for sequences.
    //! @ingroup group-Sequence
    //!
    //! While `fold_right` reduces a structure to a summary value from the
    //! right, `unfold_right` builds a sequence from a seed value and a
    //! function, starting from the right.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S`, an initial value `state` of tag `I`, an
    //! arbitrary Product `P` and a function \f$ f : I \to P(T, I) \f$,
    //! `unfold_right<S>` has the following signature:
    //! \f[
    //!     \mathtt{unfold\_right}_S : I \times (I \to P(T, I)) \to S(T)
    //! \f]
    //!
    //! @tparam S
    //! The tag of the sequence to build up.
    //!
    //! @param state
    //! An initial value to build the sequence from.
    //!
    //! @param f
    //! A function called as `f(state)`, where `state` is an initial value,
    //! and returning
    //! 1. `nothing` if it is done producing the sequence.
    //! 2. otherwise, `just(make<P>(x, state))`, where `state` is the new
    //!    initial value used in the next call to `f`, `x` is an element to
    //!    be prepended to the resulting sequence, and `P` is an arbitrary
    //!    `Product`.
    //!
    //!
    //! Fun fact
    //! ---------
    //! In some cases, `unfold_right` can undo a `fold_right` operation:
    //! @code
    //!     unfold_right<S>(fold_right(xs, state, f), g) == xs
    //! @endcode
    //!
    //! if the following holds
    //! @code
    //!     g(f(x, y)) == just(make_pair(x, y))
    //!     g(state) == nothing
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/unfold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto unfold_right = [](auto&& state, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unfold_right_impl : unfold_right_impl<S, when<true>> { };

    template <typename S>
    struct unfold_right_t;

    template <typename S>
    constexpr unfold_right_t<S> unfold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
OmpEkt0yO5pxUT1Tyo3M6o02iOUTUSKWyw6KBf2v/jV1bfvO96pJVtJ/OyuTvlRJeyFBfMhuOpynwYk+m8KMI2yHhMl4SNF2ZT6kHOGRDPshJfAv4w/bD6lOGxCZJu1feHmR/CNGAsTL4E6izF60SkZtSd56Zt7k4AbhYL6kUd5xs3Ichpr+K0dyzA1prgDFPbrPiJ2Om4CNmEeUmtNoFDqFD67WLK2/0I6H7yAjdj+8wlEiwRK8oG9IvJv7cnPifWtRM23lQ0GFOyL1FAkiUIZx83AH/LpkfIZh+TZQHSEOGTJLITxYLBmiMdpziEuGzGbk5xCPDJmjpgD6SYbE1ERAT8mQC9R0AHcoQxaoSSF5oWGSOePZwYF5MpDFU7IXWXWf85YgZIsMeUiGjGarKxyySoaUkuQWodtk6BMytByz/zS2ssKh9TK0CiFChqyTIZPYmgqHrGe9fJYvruBZiKidMup5imqE/zPyNwyj0ZIogb3KK9I0EcYVYV+m4WcpIjsV/HaCH04FP4eUJuFUsHNIeZKdCm67hLs+Dbed4WanjuG1y5EmPRF4Z8HrkN7R8GrwOqW3FN7Z8LqktxzeOXY5uvbpaBHqQVAMQV4KkpolJAi5AEE+mSkI7wK7HFzrSu4z6xPoH448zTjSRHxAJp+ijlMxzjJkOu8pJBPJEsoVJlesJR/isQ2K1U+nUmrXwCw2+HEO4gExL0yL11/hwI1G4JccuBaB1C3g3o2uE4YM067Gm7358AbVGEsB8GlqiEl6RNCTcQjoTpCcVw24lA9PB35p+iQW/M5W444BsPN04/FY7hiWNGZc83LHWFKXSBrzbR+JlhdwmTzbNrG8h2S/+GOJDwl+8ccyH4Bq6NOcxlIl/LHchwTW+GPJD6nf4I/azfOGllIML3qF0QT8VlWaXMxchx6S3X+EMZ1i0Et4ggfPEFnoKxXNuIqSPYQxxucJ9DU+GDP6rMTkxMece9ewT825X0ufkL4V7FNz7Rb2oevNi9Cul9vskGbCBulLCJEdiPiPNgNmOe72NkTlLgrJJiorOVCiXgxIvwCYPh2oDW2OtkTGLklj1jyVfZM1VWVPJKVPbr/kUgK0NfdsySdkHwOt2diSvFEnPl6bsceSOCZvmotXEAM8moQlXwdbm2iy0jrgTn66B+Hg3QzqH06PXs9HmYUwib0NfuOa+Y9Xs7M0aGyXERSTNa8jH1ipSeL9d5nNuJwv4xcbbEbodGIzJv1/T/Y/82s65gemvc60voB7hrS3WUAiw3wwKRRqGbUXdjdJDUUrnnmIB1bHiQhEPWJhtTI0yMe/RETD9ETiLn6dtcuR5rOk79nkw6hv4stnC2Gx4QiKdVLsOoSOHO+J59Ya5cCsT6hGXBQFLCKZTxAJcUm+aficH4JlGq0vcuDFCjr0xKMZ/ERrfxSr7wyHcGSZJ449xny1sQo5wjUiwCFOChlBIRHRPR2SRyFsqnTP0WagW4JcQGJTktnDfmlInBA0C95BHKK1RljHmVneQhDtWvScED4+fTERE34YwEPRT5rR/O5QdvRvKXpeOU5uXRPMWpIyT7EYky+fR61ajUyL6eRVrDwHTYYuIGrXXVct3XBBF5KXbtqx9KXYF5t2xLtM5KSk+7l0s3vZs/AgXpY2F1lZaRFPGDmW0YJDRsrJZPpVDPlO/B84vAUGm1+u4Hrz8ZeH0VsnvdNp7akJUWuItqBv8JklFjt4C0OAE6ZQNCcqEXSPy2jnwzLGR1WggvPaVnAGvHQcgkOiTTvcS+md1gTIo5Xb4k6OhZ9GhYrmUUFPUk5UM8cJMMJiJSxMy7dfg8CnQlhaj3tQ7lcz1CNPI5t9USssqIrKMSo=
*/