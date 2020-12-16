// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_sort.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_SORT_EN_14_12_2004
#define BOOST_PHOENIX_HAS_SORT_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_sort
        : is_std_list<T>
    {
    };
}

#endif

/* has_sort.hpp
8ZxyHJDfuqFI5zjQTs47OmFt7Izh2AVjsCv2wxgcgz1wAvbEh7AXzse+uAb74R7sj+/jIPwSY/FnHI5X8D75XB+DbfF+HI6JaMAkzMZknIWT8QmcgssxDV/DqbgdM3AnGpFy83kqv6Mj66Tc5uPnXin3A3L8y8W6OBsb4kPYHR/GvvgIjsZ5mIHzMQcXYD4+ikvxCXwNn8QN+Bx+jsvxMq5AT+L4M4bgSqyNqzESX8Qu+BIOxJdxDK7BeHwFKRffU+U3dvntnXJxLGZ9sl/3l3Y6EANxEIbiMAzDEdgY78FWGIcd8F7shCOxL47CETgGE3EspuI4nIf342M4AV/EBNyJE3E3GvALnITFmILXMBVNwafhHTgVQzEDW+I0bI+Z2A2zsT/OxqH4EBowDx/ARzAP5+KjOA8X42O4HhfhJnwcD+AT+C0+i6dxCf6Mf8Kr+ByW4DK8jivwDup4JTbE57E5rsIofBm74RociK/gEHwVk6o61wdU+nve1r6eB0nF0tfT1M9zcDn6ev439PPM6+VcX0/p50mf2tvX11PVz7PcfTwLSMu0fTxd7t9p37czYu5/V//O0n7OmNTrv6ufZ0GvW9fXszYplhOvmaQ1pMOkK6Sm/Pg5mpRH2kAqJnnzQ2gb0gTSPNIG0hHSFVJDfhyNJWWTVpIOki6RakfQJ5SUQsonbSDtj6joP1nxqnhVvCpeFa+KV8Wr4lXxsnn9m/v/T01MTzYNAHBz/f+DuNtvrOk+/u6mn8xM6zX1EsuqVJf5OcTd0HY+D37OSee3utJxAwq48CPPreKZL/p9RC+st+nXx3Ojk1MnVXL+Pla9/nrSj03dx4Pf3LTP5l8XwPeKDUr+ppuPSysuIynHqT4J5ntIpb9BZf3+DzHK+l0vm9yj67hscg8oWWieQbiAvCdssDwTsNewoX3jR/YYfG+feDoMuvLMw3kh2mceRlTRPoNwIe/L08uPu5tzXHhWpuSnec62+hmI/aXjTRP5bbgBLmK51ZI/2zApQ6lu5+5zfWEjy97g+XbqtuZrtz3U/Q+S0xImWZY7w7zFIbxvqrWf2xNMJ5pWJO85qdxzb9cPZLr1Pv0zqvvsLffMPmRaz9Qkm7qpKn35r5N8SFdJJWyo2L9K3Vjad+njIZ2/z74F6yAryds23hKZnkwy3Xs72LR9iCMfFv/V9l5m07EkWyqNuG1iPyj937+Q7XoUH+H9+QX2saemp8pzyiNvsF2Hb9ZuVymLsl2nkQcHS9Zn7ldr2q5kVtqCTA+Uzpa+Mnplv6Auu2zvqYGm7cLDiVOzsrNs64h8pH+wso3NdeZBfRVS/gME++Am6eOh1Jk5HnVbK7bmQxbMk3Z0mnmEzKplvaxzC2kZ02vfsO37oWq/0keZ5SV2U9ktZT5h29aUZxZ+KuvLDrJ9Ruk4GQ8gRdpgEulJlg8zjxFjKUppbyRn+iBZ+tyq45U6lX1L23dF/Uw+/fuzHd8PrX//tOP7tvXv87519wHr33/s+L5t/fvIXb+fW//+YMf3PevfH+/o/uNb9ww//fvgHd+Prn//tKP7wl2/f93RfeRJAab5vnc+6l20MmDOky/tb/TMxrtfcv2ZkUO9TfMLvr+v/vIJ66rN9zroFvTLa2867idgvn9BzrUwmLTQ7v6Fd+UZAu9hDdyH5uXkHAlr6yw3U5abhbXwAZTlOPdxnF+RLLdb8tujftaeLOdHOmw3Jnk91fvy5H01ynjfaDc5L5DzhYWkpvx7sJwPLuJ9Pvg4BuITGIrPYBN8FnviEuyHz+FIXIrjcBnOwOW4CFfgU7gSl+Lz+Dy+gC/hKnwdV+Mb+CIW4ku4G1/Gj3ENfoqv4Jf4Kv6Aa/E=
*/