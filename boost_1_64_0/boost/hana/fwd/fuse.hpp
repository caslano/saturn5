/*!
@file
Forward declares `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FUSE_HPP
#define BOOST_HANA_FWD_FUSE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Transform a function taking multiple arguments into a function that
    //! can be called with a compile-time `Foldable`.
    //! @ingroup group-Foldable
    //!
    //!
    //! This function is provided for convenience as a different way of
    //! calling `unpack`. Specifically, `fuse(f)` is a function such that
    //! @code
    //!     fuse(f)(foldable) == unpack(foldable, f)
    //!                       == f(x...)
    //! @endcode
    //! where `x...` are the elements in the foldable. This function is
    //! useful when one wants to create a function that accepts a foldable
    //! which is not known yet.
    //!
    //! @note
    //! This function is not tag-dispatched; customize `unpack` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fuse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fuse = [](auto&& f) {
        return [perfect-capture](auto&& xs) -> decltype(auto) {
            return unpack(forwarded(xs), forwarded(f));
        };
    };
#else
    struct fuse_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr fuse_t fuse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FUSE_HPP

/* fuse.hpp
ipe5Zhu3Tx87FVE170MkHKvm+MsqvsiY8vsJ+EWrfBymleIYAGcP6qfay4x+GuY+ivxKzW46cwwGG1PLmcqS+MHYtDHRa+iUF53YuMAU+A9B4Ge+LGkdsMb5/ChC0wp++vrkp5EiPNMfui4xjFFrrZqQSQztOxb6oHZBYyM+bCo0lgpe/KLdXon2koS847rk8ZRZtHZ+IG6sL+YnAnZONAjI3iCbKDvzqbn/MAsFBZog6nkPjUXqt6HO7mhsRq1M8CW+DWJFNAbjnNdEDljJVnCyEwVJyRZRgOczrwDJswD+xfrv8niluECb8uYQFpR8+bMDlBbi9joxLsyrgtYorl3z9bEfwpYgXgLcWrjGvKrz1sXeCWAXud66ODf2W0d6vEUYrmpxE8x6LYoeBlkEuQwKLXni+rKtd40Rp4xQ/0LEUPox00d0Q8tyr+MN19MOdHcpskkRSd18pbgDaWiais8/zxEf7mG5OXP535bniJfExBv80Ox6ZpFoUvTPvJzZKSTUGV+D/VjmbFuz/R7eDKThVny+S4E81UrwPKLgr6T1DleW570kOq667HTruV5nNTJZQHVThwU2b3i54cBEpZSV9aFSXiCXDpjFSkgrfLXxO5Sw/v4PolLKqFI+ofS+IlZGFfLJQl4ODPP2C2e5QpBc2apcD48LVvsa5gdemeNBV/EAzu2U65G8lQdwUZzEm8VMXr/pJI3Xse0OBK359fFmN6bu+p8a2aPWNRPPKMYD29Ys9qoOCs/zTnACYme6tZnG/QY8sO5XKxzFN93v3dApOs2IQhlzyI/ZO0e7UH4CC/dZ62EgKFN/kxwYFaMW5FsqkmvjIcreCQ7trqKUoM9oea1+H15AEvRs0MJPh4plVHAWWPYjNc7ww5PhH8Lf3/FXhVqZi796/DXiL4K/f+H+63B+CGf8JuzOx0GfP+WNy/8PHO4rUn//F9dQ5rG+W18DLZZxA9dGJz+/Lf15dvxcwPj5TlKf6AdVhooU46LjKDiNvw858s+BeORrpsaEdtFvdgHNvm7ewWdCLjaMAmJtxunxkbR/1Ssb55taewXU8S3jTSzrZABGWMJ4Nioa879JpyN7CVfOwhAseAHH/c0uslfNJrdzi6KVak1u4RQ3Kw3UZ8QW9IxVs5mzrhmFDvtbrG9CMSn+ln75O3t93sr1WWvU59xM9SmeYju9jHV/bWrNnnSm1uzjTsbE4ddsCn3GKOl6fGiMH6VQGdAb82ll2rK90avjk98VkvvUcFf2iPGwBTpZsyCFVsnMZcm/cZlsN7f+51cn9k+5hhcwu9vBZlFj35QPcsKw/lJnYkO1D8uX8cHNqw1XozZXgbdxIgLFb/vHQLyxyXjpEGelylXv0KKkZ9GmvM0KL6vCmwBYRrXhVlOKvTj5tXTDi7X/QlvICTyy8G9LZ/b0NXAZsq2t9Xqp+XFKtrVF8PvD+HM4pLELJ0eO8bIzZbw8jP0ONq3fliq/1lcf5NdJ+9xipxVsdYz7ozvFQM/BefpnC1IM9L99emBYBnrTX1GXgY5w2jcft2QlYmxBisdi8tMDdj0WucYzj9r4/iPW3h/rf+9dH0ML75zOLbwRJ+55WFJGhgL5zQ+mxRXa3EI2kc9VMQeRcorfSuxudNAJoEfFV3VjRWWhNgb/0Nix01ikj88cylyTIj9fRmnfxN+P8Tcbf3fi7+f4czjHjhkz9vIdLmXniz7S5n85t/EY2v/5+LD9n+FIOzqE/tM3ZLX3vve5gaHsvfR6Z3o8wop7/NESmNlj/cvvuppiyMpYLFbiNFRYAtryLiSJlv2H7e47R35kjpdg+3qT9/l4Fv/gJpq0is/TmjaTOkJts5Z0zQqR2nY=
*/