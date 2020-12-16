/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#define BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <string>, as it's quite big
#if defined(_MSC_VER) && defined(BOOST_DINKUMWARE_STDLIB)
   #include <iosfwd>   //Dinkum libraries for MSVC define std::char_traits there
#elif defined(BOOST_GNU_STDLIB)
   #include <bits/char_traits.h>
#else
   #include <string>  //Fallback
#endif

#endif //BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP

/* minimal_char_traits_header.hpp
05ub5SpgyXWKjxOFtkQ20wqWRobjS4EtnfYwBGYi82CmmjRnLyyXzIvZ0NFJm2CyurSvMJuWs79ykY2TNGRh3/JsS8/gveNuucBMwf/W167gszj//TW8yKIleT1bSfstrj19B3xD05gOMFP94v2h0M70aJgCyxbM39yzHyyPTM5s/cOFnWCyBnTMYvZw18kMmIrMjdmjcy3aw0IEW+y44zMsnMyB2ZxxpmhYJJk9M8X0a0NhWrJAZv+4ys/DDMKY3cb+WgmWIox56HOlHFg6Ga69C2zaY/u9sAwyJYtb2evRbfQojwzH1g7UI2nRQQVMG1K8jxVa5entp8ESyeyZ5S0ceBtmIPNkFvF0ZiIsg0zBbFOv1FmwbGHMTsNuLIblkQUw631CfRjm37B4fyi07eY2R2EBZKWZBdx9dQcWTGbLbNzQC+GwUMGiKxwtAwsnwzO5jrTNR800PoBF/lB8fCm0P8bk1oXFkjkz+ym3VhYsgcyb2fm8en4wA5kTs5jyUwJhKWQ+zA5t/82AvmeTIc9w6vvOPd1iYHmNivf3Qmtr06oCTB5K/WM2fXeQFhZE5sGszH6HJ7AwMiWzx6XKVIBFkXkzMzcwv4IlkAUyexlQQQ9LI0MNnchGZudPg5l+LN6nC21RHZcjsFwyZ2aHPtfpDjOTOTHLmdHljyKLkuSN6V3Bt+NSZ/pMW63OfffB4psU115ov59sfRyWSKZgdmunfivMSObK7Hi/8DewDDI5M/OSA/6wbLJAZhXKp3vis2lKzb/bZxermtKAFLd2MJVg0VYuG2BqMuxHBWZqOH0yLJLMjVm677jHsFgyD2b1yrnULrL6ko4M17td6TMu28/YVYHpyRyYvdl6zA5mFOL8y/00HJYmxGmnfQmDmcgUzHKWDnoJyyVzYrb8Xd8XMDOZK7P6L5QrYPKmlvMFPlHMgqnI3JmZHszbBgshc2a2//W1l7AwMp6L6rcZGlgEmYzZAHl5BSxKiNs4+2sELJYMx/nC9UwObAKLF+Kkz9fCYToyvtb2dg5KmJ7Mg5lbv3X9YClkLsyeB3Z+AcsgCykwqcjGOke1gcmb4ZqhyIyHv1bCdU84Gc453ejzrRkpp9vCTCyOjJ6fWc/GNbu8ua0UXqoorjttg4EP+n+EbWlRfJwvtDdDc+bDdgs2btweX1gKGfpQYCPbPjwJSyezYXGaV/91hmWQ2TKrYhvcCWYiU7IxzzcZWweWR+bJ7KenbQbC5D/R/s6sXsOAEbi3CCdL+bZmPegdEX3PfBksqGVx3wvtytmur2EaMldmuZ3jzbAIMndmYwduewbTktVkZv1yylF8Ts5AhmNIBF0Phq345AS7S4a1LrCmvjd+geWQWTEr+2jySFiuYCdOff4Ce0Zmw2x5qVOdYHlktsye/qfOTzCzMOaCgR9Hw/LJrJlJb/5yhkmtLGsYuCXHqsjGSzIyHCN70udUGznEbYWpyPyYLe7ewRMWJpjnmabVYFoyFbP6DYeegSWSOTKb5ZXcFmYgc2JWc9C+RFiKEDd347gkWIZgI4KrRMIyyZyZTYpuIsFyyTyZ/fy57nqYLIyOycxa56wrBVOReTBrU969ESyEjK9n8H+O9IKFk/kwGyr3awnTkrkyK1+jzGhYApk9s7s/3ugNSxTi3qasV8CMZO7MznWp+Scsg4yvdb8RaQpYJpmM97aC/iosV6hdPjlEC5NaW9be2ntnH5iSzIvZzY012sFCyHgudte3j4WFkfE+bLKu/AYWKcw3PmDzXlgsGe/tjN0XysASyXgNPZ3LjYYZhTGnX1HYwDKEOFUvwydYNhlf618+LNgHMws1vCiXXxcmb2O5TWiH3/kMCyLjcS0=
*/