# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
# define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
#
# if 0
#    define BOOST_PP_LIST_FOLD_RIGHT(op, state, list)
# endif
#
# define BOOST_PP_LIST_FOLD_RIGHT BOOST_PP_CAT(BOOST_PP_LIST_FOLD_RIGHT_, BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256))
#
# define BOOST_PP_LIST_FOLD_RIGHT_257(o, s, l) BOOST_PP_ERROR(0x0004)
#
# define BOOST_PP_LIST_FOLD_RIGHT_D(d, o, s, l) BOOST_PP_LIST_FOLD_RIGHT_ ## d(o, s, l)
# define BOOST_PP_LIST_FOLD_RIGHT_2ND BOOST_PP_LIST_FOLD_RIGHT
# define BOOST_PP_LIST_FOLD_RIGHT_2ND_D BOOST_PP_LIST_FOLD_RIGHT_D
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    include <boost/preprocessor/list/detail/edg/fold_right.hpp>
# else
#    include <boost/preprocessor/list/detail/fold_right.hpp>
# endif
#
# endif

/* fold_right.hpp
ffa3IPgZCMAj/6CG/HrJPczP8+vGw3lqDyCiCGCHcghVe4eco4Z+/jX08KmBey4rUkwYzsWRI4zzIYVnMOpcAqlCE0paWqO4rtF0L2spxEEA0S4eTQhL7452/ybPmxTRQrXoTNOd90Yh4NFjksTLo3gJVTou4ktsS9L9hmvFxHvl+dR4C1lWO1I6Lv5L2jKQ9SG95KGAdOeXbYz08ctE+xzOZ82hYLoIz+EpkJp/j3JSb//TU8SH7Qiov4xItu1nkoDJ+VHhYTPspavdp60JeehJG6MxpS7L/yg7H7i4yzqOH+y2nds5bu7mzg0VJyo6VAymzLHJBptMmd4Gd4fKlArXz4WKdadYpCygoIOiXLWKCnPaSipSSlRU5qayOZUpKTWqqajPecwwcTLF0ef7eX6/O0a9ehW8nvc9/5/n9/z/9/s9COt8Lm9N+iBclMd4gtPVTJgYM2abvvvUL2/gF/1L1OdwnBKftR5dYN03mYULUOTb1rVYxN66ZwD6+M5wyb7VNhHLn19t+/3e1bZuiE8hnNB7CuJBiEcgboNYCNGVzfNv8EJuceEd/hnVuHXS6EMHJte9YoYDLcr2YhxYCJEml1HLdFVmEk+OjeTx2LtYg0iHD8lSyM2L9nP5Qdr5udYd9/mqcZX+xG8rLLXg+74nJn2zzqa/75uKzmkWTsOIP9EvqYlsSj3RL1jLM9FNkOVQVgRZNmXr1KvaYmp0pXpeS93RTNWjpWnRNPUHSMMj0dNVu9bLiGLbVv0cCq+6Jt364mKyOpyrP6d7IzJP2daIIvgZuchz8ud8ezbpffKViTadTuriFdZHcF2RNOjGPnjNCzS3fzSu798OeSbfvX0nvXFEPtIzODePVeN5Hi19Je+/f7d0L77iubd2b4IxtIlfPk/BldZ7ZRibtAZziC0J5n3RGUkoMQOyCnowqe67Ukr33YagkIHhMVw2cWr4heYNCd9KWFXXEzoanrlk3wYfPretGm7j0xXhjgbI1LwvwisoGqEIqNtAIwG+b7lDvs8dHlFfHRvnnbip9YfxeLweNuMdNCzqvVKdSjLl9BvF0MP9oNAzwnE7+2jHE8HIQn/9svkDSSq7lBtJjkHo+2GQ5VW/up7eyS2xfqMMrs1UzIQX1k4xfXNFOMJFxpZISzOmr3VOMWribiaui7l5VscyGoo/VYr65Uf6mZxIpVIs8GSFZgV8amsl8wu3augGB0mLDVZb8AykzjtlNMP8/kvG9nhAP7iO2rCXgxtZi3zq1i9Sw/qGPO/7fWKTpOwH8MGn5iE6RSoEOZPjFpybNJ6y0ouXsP4QXoZRgPEFUan/tXuydxs7YRhJQZHd3JK6OM8mIhfil2fk2X4P8TjEdyFaIT6G6IM4CPEMxNsQ/4Cwvi9ehIVHZ/3B0HRcsHTdbn8ArZcr8wg+5CpF461r+eA1aM3WhQw87KYWmPjFqA9G4V75GmdCTfa60EXhdc7w7qTT/9fv7war4dFa8WirDgPXNu+44XpGAuF8aAVzE0wlEEfNsnXBC8IFCOR/DWGhFcLpsRB+ZYYw6YJOKW0uS6gsZAev4calMKdaukZyJFaH/3ANi1z8Ri6s6Tnq91YFkOVOW9DL674CG8K5TL8Hr5ECiTVBeJNqOCOxcnILvfFkHsH7eo/4DU/cpBgmaxFC7bEZ1W/ecD3vS3LVH7nL50PWMD5uM3OuEs+VJM56m6TORUYWvJHnSQ4oac/gi5EmWlvWTYRcuIH6mOg5vQF1uTa9YdP1uN/KLuefKid/Xz4FWmEczNR7b05IM7TUBWkWpL5wu2XqgFYOpH7IpeDolzsCUKU0Q+B0b7P0E4i2YYOBV75Ar755MhqqMcRABgQ=
*/