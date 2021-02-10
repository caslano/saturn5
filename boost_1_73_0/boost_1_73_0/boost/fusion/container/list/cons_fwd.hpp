/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONS_FWD_HPP_INCLUDED)
#define BOOST_FUSION_CONS_FWD_HPP_INCLUDED

namespace boost { namespace fusion
{
    struct nil_;
    #ifndef nil
    typedef nil_ nil;
    #endif

    template <typename Car, typename Cdr = nil_>
    struct cons;
}}

#endif


/* cons_fwd.hpp
M4PlazGP/K/k1f0wuCWnFdh/dPfuF0dI0ySKZgCBZ8HWljiJFVfYq+V3mfmLxZdXuIPZG1bEjAa0a4W0DhWq75vawRfffmuMH+4u/KUHSAfVPy3feZytPwfBqI0ImuKi/+Zy0JINd1XYruyqjAJEfCUkD385q38nE/z6Sl1fXV7eXIyubt79ih+HI9d8rs/7/mZ4+xXnfX9j5wWFtjZxvcczqxEUnvi33264+xOAJh+tcYcBoBn3QN5E5UkJFuAuHLqLo3RdVsaudjjpcmww0TN8wKMdsUvJHCb5TgAFYGWTOAgLzBGApphrLFPAxWN2Dmxsjgl+ho8BIgTDY/4kecCChpzDDMsw15UbTbjExKaXBGZlxc8YYqraMgBW/AZe5/ALHOvg1nvTv2jm+rVGlkpy6BgwgfUjMEzK+zmtnItV0iLJcgIwKJCo/GSRiDASqmJZmD2sCQ+cDAuLrOiLt7hFjltrYvZctTakoN3+85belstfPomAW6erM/8XzNdeC2SxCt4Wkc3N56CGYDOdaqBcgKxpLBUwrA+npR/CpKTajRobSnoQQCM6tJLp6alhYcJgVDzkINGEePaQkkwzHI4wMtgbzgXlWi/I4BXYpUgSgmRruFPFYJsAudkQBwXP8t2hWGfLvx2A2h+3
*/