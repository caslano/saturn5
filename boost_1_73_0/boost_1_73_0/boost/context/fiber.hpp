
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/fiber_winfib.hpp>
#else
#include <boost/context/fiber_fcontext.hpp>
#endif

/* fiber.hpp
iLmtm5KlKoUUw28rlRH0NcN9hAvpOoRXFcs5hBCgDAgVpLWrKqsDtjDvwXNdaH13ZRBFkde2N/FqvAwmq/HYLszm0+V0MB0vgthcHLAy/G98NRsP7dxAr2ue0WYtBDDWe4HP1v1NVy+mgJI81elJ8Cd03YwU2dY1ors0j0X/sIH+tMK/SQrJ2L31S7v8pYrblcc13BRiSCYMe/qv4OH5B1rhZ5kxkCymg3dDZwN3i5DOQ/q3h2sN+cr9FRtX88EwmQ+vpu+Hl8FfQUfGfmYavTwal19MwftDzdKzac35U6y+tMw1l4FjiecnnhwFVc5YIlmFUdHH1hO7B+MQ3eM055Z1nfZ7q7TXHTJq7nXHjlhYPWChly9x/igF1rZ5tngMmx2ZaBTm98LMvzp0fucmqdlt38YS0oW3cepfdT7Rsv37XByKJyTv+DhtLu338nWccH+u0xebl280cDT1TfbMwC+4rfr4fTwax69G49HyOojz3P3v4Vl08WN0bjfMh8vVfELv4/FqGMytf+U8JNN3Rl9MC7q7nJXQtmmExN3W6Z7buJq8m0w/TJKpvVyYQ2hj15i9xXBI8XgxxT3w1fyR2KkHgQupd3jlSnl/PfTvg/8DUEsDBAoAAAAIAC1nSlIRs9RwpwQAAAAKAAA8
*/