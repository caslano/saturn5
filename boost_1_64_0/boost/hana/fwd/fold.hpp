/*!
@file
Forward declares `boost::hana::fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_HPP
#define BOOST_HANA_FWD_FOLD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/fold_left.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `fold_left`; provided for convenience.
    //! @ingroup group-Foldable
    //!
    //! `fold` is equivalent to `fold_left`. However, it is not tag-dispatched
    //! on its own because it is just an alias to `fold_left`. Also note that
    //! `fold` can be called with or without an initial state, just like
    //! `fold_left`:
    //!
    //! @code
    //!     fold(xs, state, f) == fold_left(xs, state, f)
    //!     fold(xs, f) == fold_left(xs, f)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold.cpp
    constexpr auto fold = fold_left;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_HPP

/* fold.hpp
aH17eSMyFmiS2lbnSypc+UYH8hdfRWgZIkTCW/q/Khm5FNDMnjykvD6NTMjLD5XsIqwr5eyeV80Ba99RhFOhuebRdeXZ5iCMXW4eXZh3cjLE4xH4FM5iVyN3igiH44HoMjc/tHecZfDezHlDscXBqiDA2RTbjp2cd/cj8EJYGVbRsGCKOfstxIV+ZaDsDOFsHTyqdk8DS71JPuR7MHgzx7o4G7IgasWcmO0oUBJd4DLwEJ0Bo1mm/d0A0d4LjlW74TqTbIDV1K2DuFpUosVo6WL4RYnDePyocOvMSSd9ARw2GayEkR5GhU2fStr4ylbnd1RmONgjqz0CKFqoLYWUlg6siFnpbWlxHdnHleCNZrtxINvhM8TDt2bmLA8fKNaDZz1d+o1FQaPTEbfbRC8PC+P04zDxhDwba8RjJzplaTGSZxYIsALQC0HDEke4UvVvywmZl1nBru1X/SUQtlH1uL+Kkwd91kCuM7v0tnDABOnWCk8+FbFTlOsY0ZrWSVgNytkw0xlVs6fBVdE29QdvxetNFF18CnfiK17EgQBqNSMzrXaM2+ibdhAi/g==
*/