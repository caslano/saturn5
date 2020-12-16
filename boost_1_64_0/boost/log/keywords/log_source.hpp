/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_source.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_source keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_source)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

/* log_source.hpp
q+3fZDgbtoZzYBq8CvaCV8McOBfmwxJNV6nWGyI2jZfCtbBcz7vLvPukjPS8LZEdet4M1Z/2MAl20PLrqOfrAgfAXnAgzIbjYDdNR3c4Vd0vhz3gDPgZeCW8EBaqexHsCcv1+HI9fgoe9fjfCcq7S0lnLvKCzg/fo/X4LdgV7odD4PfgBPgYnA2fUH0+AFfAJ+Eq+BS8DT4NvwKfgV+Hz8Fvw+fhD+BP4UtqG/Xn8GfwdfgSfBMehXYif+Gwkdoe2scvgL+BA+BvYR48DifAP8DZ8E9wBTwBr4dvwVvg23A7fBd+HZ6C++B78DH4Ifwh/Ct8EZ6Gr8J/wG5xXMtgP/gvOAh6PdQLTIBXwMawGCbCUtgUXgubwU2wObwFpsKdMA0+CNPhN2Fb+EPYHh6HHeDvYWd4Av7Y1l/qLYv9NrAr7Aq7qy3VWvNuhj5R9bC5tCtdp1Rt8ubCPnAQnAwHw6nwElgKR8GlcDTcDMfArXAc/CIcD78MJ8Cvwnz4BJwMX4BT4ItwqqZrnHk/QJ+HHAyxfb5F28c22AluV/27A2arDf483T8Fi/zPw/CwxtcEma7x3aVzEe6BBfAr8Fp4r/azu7Wf/TrcBu/T/vRLcL/ua7+jz2DUiXu/Y/wdV39t6vZHJgO2aXNC/GU6++0o/WU6/J32OPxpPnY0wNbt+R5XH2T7tnPSp8b+bWJmUlRj8N1t4J4/+7efNtu3ddi9jcrm7X+jvdvzaev2v8nObbQ2bhs6V6Ch9m2zM5M+Nhu3ucRdjGxBHkdeQ1K6JFn9kCuRVchO5CDyBtIiCzekICs2ryC2xbbYFttiW2z7NGzna/x/ZeXZj//vZKW0XJ3Le7rm9icENbBUWMlpy8sYhCHua3Bv0crpbn97qLadZf7A5CzLjCsp1vdDF2tZ9EF2p/KubZ18f8m7/PLCJeVYFtKYSEuVsW/XhBjWtrCl/u+W/u8eez2R39+7f5eI9D6+4e/RDzzi4fg/n+/9636Dkl798rPtP0yaN3Vn5O8k7t8rGv4dwP29+7l7j97Q7yfu35Eif4/yvedRnVBdWel8z6Nr9Nn8CLaC/4Qd4b9gL+jR91Jx8H4v8V3KmhEI7ybc3j1Eeu8g7xw6II75+5/o3P3zOW//TObsO+br1ztX3/+8fycSMj+/QXPz65mXX++cfPN8HuVzeeT592c+7z5kzv3HMt8+ZK79WT0763Oz6zPznTBkbn298+r38HvTpbFn2dgW22JbbIttsS22/W9u5+v5v2z52T//28/vU7MsM5b3mD6/T0M8yOXIfQP5t9TMHcwrW16yhNQWj8ESq07/l/GQg1vKnLXSikVEHGmM69LAmNGJMteJbJjx4vgV9zZmvHg/2U8Q//PFP1l3jIVPFPcJjF/xmPHp3+1CurPIA/K9LtHPY+dc/nnrxn6+nac0kycda6pldTqOf44xZ5ORHaSxYqlj3i1BS0vKqmVsbXGJVKEVPsfP3Raro6zWdZM5faWWzrVsBattd87ai9DDCXGp1cjdTqvGo/MepTymUzZXIDOy6n/X4jJHyYzDJV0cI10hZVNBAKGl1LI5HqFs0OYGlc3xCGWTpXr02lKd+0uZtEeykf6EnG4lupaRxmd0aGYW9YrMQqYja6J4J9XMSpG8jygjLtWppr7f2fmTBsp+vNkfIPv/WOrf7y/7p8x+vwaV+6V+OweNzLgPYy/30u6Uf1mEchfTARWLS64tnF+90gorz3Qtz2oJ395qQhmmIa76WtawefKR8nCosfg1Y+JuR9bnMo4nUh4WlyyuLPXlpLQ4LA9mrtluCd+dsXQJruknfqNThW3UhsHCwFzSw+Lewk1/CBtmP4GkOOahins=
*/