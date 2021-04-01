/*!
@file
Forward declares `boost::hana::size`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SIZE_HPP
#define BOOST_HANA_FWD_SIZE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/length.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `length`; provided for consistency with the
    //! standard library.
    //! @ingroup group-Foldable
    //!
    //! This method is an alias to `length` provided for convenience and
    //! consistency with the standard library. As an alias, `size` is not
    //! tag-dispatched on its own and `length` should be customized instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/size.cpp
    constexpr auto size = hana::length;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SIZE_HPP

/* size.hpp
eoldv9D8ULLy3E/HQpQwZmHCiZiiMnos26wSlGf06df1HcGCo1zMCuMWZ9TWIBAuzd53To2ndlzsFj/WJT0yH2fLtt3ZfYLg3oxhvMsBoNpW4RaV/8KqosnsWI0rHcIUKPqxCQtREM9YJ7NQXyX+navs9WKD2JdE0bFEVQ/F4xmqvrCBTXFDAz0E1exI9injNPxfDqI8NQqbi+lJvFEdb2Tb5CRwh9QFIG4B5uQsEnpZxvSWY6Z6XMWm7sWjZHQFPiqKBA57iRdFBt+xH8ToVNyG5eYd7DYQtrIPtP1Clwh4IEiGJI6ZQZZE6+W/mFtKFrfadgdwm1aCxPoOtt0vF4SmBsgEH3VHNcMyTqLVPG/HcPxxpuquAE1R5k+QClTgSrfvr8vq0Om/Jm5rb4JoWlJaC+sxO4u2z+Afj2fDVucL1mcCyKlvGAS4BUKU3TThp77eI26mrMkCMHjYqCC6tQ8j/Yl9puPY2BKIF5ZfGfwlF1dKVDw2tuhu6VeLWeOl/TUGmA5wK49vYg5TnESew0eC6qWpUZS3EANwkHlBmypxC57ZrQEpH2Bfpg==
*/