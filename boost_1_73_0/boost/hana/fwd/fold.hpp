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
mMT4gbMfYBRGW3KlYQa3sGB5QrjSdarNaHFHjRGzyvWVndLYEj943ZIOv3Hp1c7YzwQKI+lfKuHEqXu2hbpnVdESDSyKFmngJZhD8oTKWSh+pvji1iReUjgLS63Au7ud5hIrdhUVh5+9gsxSHDQ8tswPcxQzMO+0riAHm5FkOjl1Y0AnlGuLzCCkstltPpl0NHwHWXI3x1IH2mVtEFo47JVDm9grOkamGZlwbOP9zmHAcYZ5
*/