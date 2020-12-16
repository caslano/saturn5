
#ifndef BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,0> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
n3wD+upn8ijY+/xU/KczJvx34vFceNWV+FXwWiWb8EeId5I2IPd3w4vxPLej2BF4/iLyZFUT4IF5vh6ewMOVeLKzH3kgdX11E36zjXrOsTKu0/JJK0xqvNALuaew1+HkTQPU7xrSNX4WP2ijek5FsxZXqXHvztGrcfmDuL6TOJb8fPEz6EHsqW2xWY3/EvXZlUZ842Wp5vtJ9fzcz8l3TiYu3TpA3e8jLU8Jr/0S89/BPA/C/mOfj80nX1yj7lMAz2/7AuvpMeJK/LfcQOZnMv5PqLq+ZiF+B3nu0M/xg3fj107lzHf09rIU5tsVuSQuyqkg/3AnvM0o1hfr3/t3eLQXWH9PmlV7xrC+4MFt1jHu2IsyO/z1Ndj1Rcz3Qex4GH7FnYPIq2Kv4bsDC7Gno1h3fxJ3PwdPtx17aU8ct5B42gb+wJU83/PkHRzh0ZPRv22sn1KDkic9/k0UZ9YPwq7Cv5hXwrujl7qOUg8VBM89kH59qT6T3sPOj2f+rtJ4S/xc8h3ds3jOU/SbeV3nAE/kyvXf0L7VyG0/1Q49+jtnmwFeF7l/QI8exv+3N8IPktdBnhzauM6ePPAX+N08Lwk7lIy9rVmH3f1Oq6OiH4fVPJYRR3v0o+5nPfEwfEHoHHV94xHyHRGc1T8R+X6L+1+j/u6sI77yhX8/iVx+TR3ZQC2/OIDxIa+CnHqNwH+uwy4SD/vQzwI39PcpeDJ4tqxc7C3xQ+dudZ+4zdTfbETOw+kP/e4wo2/j8aNfQ79jB4OnEPcSL1QdVtenvIT9PYi/ezXxWSpyXkgehvXh8Q33e4jxa8RvteY+VbTzecaTeDgUvVpRDA/zM+MQRF0NvMUy5MFcAX/3N3nEOnjbBOz3+2q8/SYZldzYEDcR755cR9zyJ3wk6yKfvGDaDZZK3n/DXrmRXymE11yunmdDHOWD31BxB/o8iXZTR9bxKPptMnnXseRB3PFDJpD/XaP+7rZffVq1qudERyBvY1T7Ejar5+Z+oJ538lvsz22afUf/fMh8bSGe2k08Eoa/9CX1Rq+QB6iDV3wbuV5NnRI8f0CUQcnNAfLv8KA5zF/gq/B1PN95Kc+7nToZ+I3Q+4l/AlnnA5Hba6gfcIO3csHuheiUXDyOfiffbRdtUPPnST7DiB5+gvWxlHUDX2PlT7yVid+/g787wC/Cz7d4Yl+I05Ia4NW+xo/7HDsSiH/2DnxwNXalHb/Lhvm1xK/6E792Ofn2Gvidv+EXnqNe5yPsQAP+6xrkzZo89jh4hmfoZ9AA8jrU8ZXgf+vgIXLxw/YYlTwexV/Q6l6r1d/32+rRi8gVfl90GfHXV8j7duKMKvTLMfj1HZo+gwcuJE4ZY1D9XIi9rsUewOet+xG+2Bt+/jX6xbq1PcO4zMEfHcl9WllHMZbwANQPkfeq+Au+KVGr0yBveYDnU1fZiL+UNAp9/yb8MvGmDXrEowH/6kvNTuiJu8gLvsm8/Uqc+wv5w1bsFHzOMeKRUK2e6T7W++MWatyHsX52U39JHaHNEfyzwfCFxGceL6u/p3xJvZglvBn5gv025CMeIO5+lrjjGTXeSXORW/zgEnjh0N0m/HODkltH/GY9cuxOXuYq/MQ4nkPdthU8odsK/IQ49Bn1Tqs84J2IF/Ofhz+ejR8QAJ/4HfyTB3W9JfBvs7ADR6hHGaPuX8P81NRaqHHAzzca8VOyWI9VfA7CT62Dr7gVfjscfymK/Ikr/PJX+LM3Iy/rkMcA/KzxjEMTvEcAvBf6K/RF/I5a/KTP4PVvhtd1w65T3561mbijHB7qWvQY/l/VenhyL9pfhB5IZv6pt7ENRp80opdeRn4C0CcV8I/L8M99qIs=
*/