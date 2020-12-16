// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
GOwl5r7QBa+AteFwWAfmw3BYBCPgHBgFF8B6cBWMgesknvWwAXwaxsO3YBP4PmwMD4j5CGwKP4OJ8CuYJOXeHEaSt1Qp/5YwCbaCLWFr2B62gb1hGuwL28Ms2AGOg+mwEHaEU2FXuAH2gI/CXvAdmAEPwQHwezgYxhh6hp1gFrwKjoRlcDScA6+Bi+E4eDMcC5eLeTWMg2vELPfzcjYTebW4n+ees8LgFlgXPgHri7kJ3AqbwaehZ725l4RXFlB1vfkA7doFj8Im8FPYFH4G0+DnMB3+Q8alL+BV8AQcAb+E+fArWAa/htfBk3Ax/AaugqfgGvgt3AhPwyfgGfgUPAt3w+/hCfgz/Ao6A+jfjbk5rAVDYASsDTvBKNgZ1oVdYDTsCmNgP5gIL4epcChsAUfAlnAkbAVHw9ZwPOwGZ8IecI2Y74K94TPwMvgXOADuhQPhfjgIHoCD4WE4G34JN8Nv4WPwDHwcGvXmj7ANHArbwWGwC7wK9oJZsD+8Gg6Ao+AgOBoOgWPh1XAcHAuzYR7MgcUwH06CBXAqLILXwmI4D06Ei+Ek+Hs4FS6DpXAFLIO3w3L4AJwBH4cz4VNwFnwazobPw+vhdlgBX4cL4G64EL4Pb4AH4E3wEPw9PAKXw8/gavgdfBD+BGvDICd9GawN74YN4AbYFK6HqTAJdoDxcAhsBEfAxnAs3AKvg0/AhfBJuAT+Cd4Mn4F3wKfgXfA5uB4+D1+AO+BRuBMeh2/DL+Ee+A38M/wWvgZJi+0vMAW+CfvC3XAA3Asz4XswC/5gjNPwUzgCfgazxd0EcVci5qnKLO3Zc/YIbCvrFjFGe/Y8OyOcWvApWBduhfXh07A5fAa2hc/DIfAFOAxuk/nAi7AU7oPlcAecDXfCCvhnmRe8BpfD1+E6+BbcAN+GD8F3IOsPyj4S7pX543uwJSR86e/kfArY2KK/qyPjajgMhJEyrkbAemJuBKNkHDTqRIWE1zpEnsPxO176uwh5vtYQdoWN4XB4Go6GqTAPtoCTYUs4D7aDN8EOcBNMh5thR/g6/Ai+JeG8Cy+FJ2F/eFrM34l5kNF/wFVwEPwIDoHG/DQTVsCRcA8cA+uR9mw4Ak6A6+AUeBCWQuq8rRwWwjlwopiniLlMzNeJeTGcC2+C78A18CO4Hp6G98HF8Cu4GnZC8XfAmXAt3A7vhoEU1CZYFxrm+mJuLOZEMbeBD8N28BHYGz4Kx8CP4Hh4GhbCx+F8+AxcCp+F6+Fz8E/wBfgS3AZ3wBfhTrgdHoSvwDNwBwwJpr5CF3wNRsJ3YBP4EUyGp2EL+DZMl+uXyfUr5PqV8K8wB34Ir4MH4I1ifws8BtfDv8NN8DO4GR6HT0t4L0h4L8OD8B14CO6X6x/L9SPwC/glPAG/FvMp+CU8D7+CgSGMszAMfg1rizkKnoLx8FuYCE/DFBgPU8Us67+yp5Q5l8X673XS/mbCunA2jIdzYGN4PfSEc7KacIrl/mcibAgnwXgxNxbzKbjBLnsqZa+lEU47fq+GKh12yhPOhTHwepgA58FEOB+mwgrYFi6AaXAh/B1cBPvBxXAgvAEOE/9j4c1wAlwGS+EtcAFcDpfAW+HNcAVcBVfC2+FtcCNcBV8W/3+Ba+AJuBa67NRrGAXvhPFiToR3wdZiXgCfhTfA5+Ct8Hm4Er4A18KX4PdwO/wJvgKD6S9ehaFwB6wLX4PT4OtwDtwFP4RvwKPwL7CLk/EK9oCGub+YM+E7cBR8F+bAvXr9VPZ2wXpW66dS3uNhCMyDaj0VRsJCGAXzYbSYPfWoQsJNtKhHUyTcqVJvSmETMTcVczwejjFZje5DP4vMRDYj+5GIvrQBbkoykCI=
*/