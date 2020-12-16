/*!
@file
Forward declares `boost::hana::suffix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SUFFIX_HPP
#define BOOST_HANA_FWD_SUFFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value after each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` (called the suffix),
    //! `suffix` returns a new monadic structure such that
    //! @code
    //!     suffix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(x), lift<M>(z));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the suffix after
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `suffix` will return
    //! @code
    //!     [x1, z, x2, z, ..., xn, z]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{suffix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param sfx
    //! A value (the suffix) to insert after each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/suffix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto suffix = [](auto&& xs, auto&& sfx) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct suffix_impl : suffix_impl<M, when<true>> { };

    struct suffix_t {
        template <typename Xs, typename Sfx>
        constexpr auto operator()(Xs&& xs, Sfx&& sfx) const;
    };

    constexpr suffix_t suffix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SUFFIX_HPP

/* suffix.hpp
bISK/CYXjnf86eKHB7hw4WvZkzk5Ew77MNaY4TdMVNCV/6BY9rSspjQ2STG178G/UI7QvnsSkwaJzLc8I5vMinawoFkW89FqUOSlEQcmxJlmZaAiLfz93isx2dfybf7qcETMRL6GZYp1+/qVhsm0T9oyhey/u6x83kq5EZG5O/lCkn6tDN25VnhOUSxXGuqAG9uwSaEsnXwOvU5/dCCb4M3vy07mJvZqE/KZN8eSCsoNZscN0xWkikacFHd4xMUfOjxiN7zSn1gebyIqHUOUMYrZgTrx0LtKI7JRhF4lQbaTT9ro4ET1+UZx7fNS5w2IPyUh6qrlSV38Kgc1Vfw5SkvGf8AI9r2+HNmX88TjadxW8pT0rNBvk8LYQo8qiG+1pYtzP+DUgqKBk8XFo/BL1I3eZI0gqzyC/ZTGw6HHhz1NP2+lsRHFIQELs6FIK4eIvfUeCpW+Qx8Xw0LPJ+qql56UpS5PFfXntYlOf0Joa1KNNivbFmW6bYutT1LNIzBX/mtJNTaJD7Wqhc8CqrBwbZAq12wqgm1ZYABcvjtpANy4kRkrNPVpU6eovh96RiWJVTKCau/ez9Ueek/5s8ztPD5AnY2JCn0qdLJxU/wTGT2Hkz87RdpGeSh0OPzTzxwZn77r8HgpOx/B9hXssK/AVhYcB1tZGGzfYRsaz7DvUM1nDtIIhUjZLtvKQop9ukmK99A6cEYnWzmQTWzdZjRo5AxgyG+dCmTjQLgNsM1QJsXBxbeYeSxjzBIZlBjQWQ59a/zhOciEvQhJpl6Am5GtNA+QLynTaZ5n+HskGTqZl23r/2hmM5T9DymBlC4xGqkp4xSdh27Pb2NuPFSPU6rz6JzXvdivb2BGh2aZVN9OD1+Nvt23l/s2GjjAM5JNfFGuHke748H5owsQDfu7mMxE6EPay9hiPrK9jIfNR7aXcYvCDy7fjTsS5bs1qXzXonwZB5Xv66kfunybXpLlO3i/b0+V+k6kLnQK3zDjueHHa/pxC1gqZP4mpsV4z4pjuLr42XTZQjFLZ55oiO0j11Yri03S2tTXwLvRRV794lq1eJRnSBftOAppMWR5X6i+0wnclb1KyflUhXKFpjNqskQ9RMWlQ8q368RELF2sTPwtudlm3RMW1Px+O9fk1E9gj62/f5EiD98qgrhFYL/hPCkdX16V5mCRhH2+XSrwWaUtBXk7UmzrYr7VKzWbJmsp+PfCgLgKc60yEDKBu8SvRT/zwrZgQLRjNyMjfJ72V9zW8940JnunuGoNM1uGTIUte/NXktKqW2lXpDAx2WLje0xMlqzfJ5mYNQHRuylBzAomZphOjAPEpBjE3ELEMP69XkkMA72rBxFDfHp3Shy/gX5TulNuS9VvXsFPyjAZe8mixq+nOZaiLhfjj77vMyz/5lb9e2XiuvzrAFeWiy8+QM9uTx1tfh1atUs7n978dtBV+L6TcjeQG1ve4+DNXvxYOIVN51tE6Lp9AE0POeB63IN/7H56jyqL3oEiARKUL84NzZXKWfVq/Ntbl8CH1HSGQYGLzVXxTVwI9owbOj9iOyjIvTaccmEor5Owea+r4XMpfGkkhAoZMdpAVAGBhEOl7G82/M9mf1uokv37/qb8P8f+jlAN+2/826BBqHURq/bxR9nhf8b9vpLO/iPd7zt1bf9Hu9/3VOfA+3z5awAffB58CvJwDyX5qkU48Q2fGXoJIYMiLutk8NJ4CH0di5aarK5jgbrOIei5aSA9wfAozihsFZ9LTejLnBR2S+9iqMOli7/vZiIOoTXCbIwDE/MXqSsTZ0IlonPTqiGyNGX4Est6bnSKxRCTTz2cwEbZK0PJC5+V2xnqaEHxYLecSJygLp0=
*/