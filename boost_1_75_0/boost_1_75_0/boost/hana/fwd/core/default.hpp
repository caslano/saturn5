/*!
@file
Forward declares `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_DEFAULT_HPP
#define BOOST_HANA_FWD_CORE_DEFAULT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Mark a tag-dispatched method implementation as a default implementation.
    //!
    //! When defining a new concept with tag-dispatched methods, it is
    //! sometimes possible to provide a default implementation for some
    //! method(s). Making `default_` a base class of such a default
    //! implementation makes it possible to detect whether the method
    //! was dispatched to the default implementation afterwards.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
    struct default_ { };

    //! @ingroup group-core
    //! Returns whether a tag-dispatched method implementation is a default
    //! implementation.
    //!
    //! Given a tag-dispatched method implementation `method_impl<T...>`,
    //! `is_default<method_impl<T...>>` returns whether `method_impl<T...>`
    //! is a default implementation. Note that if there is no default
    //! implementation for the method, then `is_default` should not be
    //! used unless a static assertion saying that "the method is not
    //! implemented" is acceptable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Method>
    struct is_default { see documentation };
#else
    template <typename T, typename = void>
    struct is_default;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_DEFAULT_HPP

/* default.hpp
2a6nGQUHzw6fEG2FAangkhZhQTOHC76bENu13C8y/VPiX/h2MI/THG3IcAb+vrPhAtjxuBFvkcaNXCX1Mnuv1VORt29ZvrZQ1gkOpVlo5cVpVyoTdkGV8SbEdCQYCHfFqRuUC0oiyjVVOFPDZ6fVuIoo1OKo2gnuMXlurfN5TZ4xO8q7ZmqAhMTjmoyvGaddH/MeGPZKPwKJJLD80xXz0y1fTyrNW1zh7sxx34Gf9ng+PGHznHvV28HodzIVjEmXzNQKFctQIVtKfPM6NIHTax3g8TvDowOfZJbjIni2Jql1pfYW9Zb2Bpsj2gPZkQ87mxtC3S+FBuo2r7aj+81RVi6WBj6ryr/cA2uH+eiptq6O3AvV76XqEfh0sk2aVPR3Mdc7CYProjPCzCOpKsttDWlfSW5iCJ2cbbZZ70YN0fVKQNwc7bpfqZAuZ45N4mc7AZz93jk9hie9xJB+QdTk6/nnOSsx6euM56iNt6mvz7rCcVV47LE1lQz2CUSm6hwxGXJTJUcLsbZWbTDNDiMfmvpo1QruTlOiwj7JhPnoMJMwH/ZOkNd8GLLb6F/zJ/bLG7imF2XGVcCwjbr06zU6/irZugUlgfkEsusECOOmmgAN+ka4mPFyZPAORFU4Nnv/BO/0UB5i8YIGJQCDHeZ90xdPH7HWQyUbzHS2xvPd1UiYtqsjwwHOeQpM22g+NXx/Rf2azEj9iabYxmiQ
*/