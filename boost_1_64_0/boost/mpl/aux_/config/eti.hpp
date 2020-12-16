
#ifndef BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if    !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_MSVC_60_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, == 1300)

#   define BOOST_MPL_CFG_MSVC_70_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
        || defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
        )

#   define BOOST_MPL_CFG_MSVC_ETI_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

/* eti.hpp
dk5bQpuu8vgn6gVdduEqAW27hJU/xov3tnfBZnEM43YXiEgUUKYpXXwfi/E88FyUL76PhTwOwhN2UZQFsAWYmGc4Wdf7FWzh0pWMY8rslA8HWcmGdt40cuARABTQIwi7X6KMTxNtZuF/Ynx0A4tJIHGhOZQlwExgVgw8jxoq4LHEMZUv4OF5mBmeBz/gOEvkCWcCyMXxhE4CSMjGisLg8bDxPIRGpyAymiCWx0AwvI+NpnBiBRROGIVHY4eLMsQ1LaIQJdHpB50DxWzh4ReXy+EJKEj0wO91hNkz2eGgneA5B4U4o1HCaEyWyEFI+IUHhcmnJDF4nI52TBHOrxRY5ZSQRAobpkCwxt7BRhFwOBQWjYcWITzMNBrvFQOdjER70F/7Atvyb31lspG2QxMwkQM/TgjSU/kAYLI4GotJp3R0eQo6cnUthyeFyMkVQYYNmBimM8PhCSPRXrhLgxHG84QxwGMOLxonR4OInlvh+LA5ETBsC1zYHFgMdrggQsxvLoPBwwwwHm65RcEWUgS5aFTolA9cfnWyimby+bBYnWzYDAZdWP/CEyYKTCC2fYJHqphGQZ6aiA4AMZ5wzo5msLGK53CRtQuMeBeNgksT1hU7lsXqOO9D08e3BFNhEIntAalg6AHyHlmoxAzFSfFyAQUboAl8pqjnQK/wEyXsiHRONPQnOgQGHHZ81HVh2tBnjPgsaBsGvQYAxLLpDJgBLAZugYfnd9Q95EWxOfFsUZvAYVQD4vb44M5Tu3OWCmsMd5KKhJWHc9wG9iyoYWArzNjAFgYswsBWNOJRNMdRvAM9PQGO1mn9/rvXpf6AfGgaIOfrArLPJEBmDwfkyRT4qQ8Idtg7f0VrR4pwbSpBmRB9yd7PTGUxQ34bB0IAhIAqDD4VDgf8jlBIlCcydUv6fkbia6Sxdx+nzelDroGX3bw+ZACpME30mZYu+ixB+dfn95Hou/HG8X3IhQl9yMapBDsJy8ntVB+4KRJdcBL5yLGWECeI3pwJIBHfuImejUfRw6jR9A6MvbgTHlPRGd32D45sEr7PG2bFgSLDUEls+DTUSDIbZHaW1CaOF4b3zRUbYSh6HVOdvo24LJZNlIrLIxJDeEwo6Z4fUTCweMch2ft7m1B83J1sKNp8AEk4CwhfzYpwFABCLsK1AfIy1w6e8D2xYjxfDitRNCHZiDAymcBbexsKhYLYoJ8+SDe1gXeQHNHmgULgz4B9GwBAQt9FojQRkBXheGQ1FpAP+AByJRyf7GiAnGMveg979RhAzjIH5FF+gFwF9crgvXw45FkD8nkNQJ5kB8j3+xPHsoNQ/gxer4wAubcuID/XBmTHCEA+BNMYZ0DUjdEEZJamiLcF5n0cXiowzf/oe9hFZ7yEisPi0ysQkJP7AbJ6KCzHJEDODP/Pxsd0ACAXo/b/tffUC89JJRwvuLiB+w9xbQsCZJrPfzauJF9A3ur7X49rp/f/B5taWJhYd6wHRJhCY4VzhOs3gJKCjPAS0paRGuRceNX0VCRfl4eXlCJ5pqwi2VdakWwsAy94n9ZDkZwFry3wAmJEke3gFSJ6OIzL77c0U06x23HpitKgfaG85Gn8McYJ1E5zsfYI/lh37yB7T3cnCvqCaQpcdNkqdMjRsKPnBQZw126j0Nk20MHT3REzFbcV7fdFpt3wlR0OV8DIBzWUHUbsNyIZVfg8ks8JE1BZHBpyT0+EKwQmsoAQRIAOLBrnfai+9gFuojEEXp5w3qHaOzkB5N7HXvjp7OUbMBkAgKz5hfaMMBryJLe9saEbmFHCHe044T2fEYqsEsd1+MWXqGwCHrG9O4l8poh0KLBkyK4R2/yAdiqH10sDDXKAkQY=
*/