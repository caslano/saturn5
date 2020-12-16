///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_CPP_COMPLEX_HPP
#define BOOST_MP_CPP_COMPLEX_HPP

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/complex_adaptor.hpp>

namespace boost {
namespace multiprecision {

#ifndef BOOST_NO_CXX11_TEMPLATE_ALIASES

template <unsigned Digits, backends::digit_base_type DigitBase = backends::digit_base_10, class Allocator = void, class Exponent = int, Exponent MinExponent = 0, Exponent MaxExponent = 0>
using cpp_complex_backend = complex_adaptor<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinExponent, MaxExponent> >;

template <unsigned Digits, backends::digit_base_type DigitBase = digit_base_10, class Allocator = void, class Exponent = int, Exponent MinExponent = 0, Exponent MaxExponent = 0, expression_template_option ExpressionTemplates = et_off>
using cpp_complex = number<complex_adaptor<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinExponent, MaxExponent> >, ExpressionTemplates>;

typedef cpp_complex<50>  cpp_complex_50;
typedef cpp_complex<100> cpp_complex_100;

typedef cpp_complex<24, backends::digit_base_2, void, boost::int16_t, -126, 127>        cpp_complex_single;
typedef cpp_complex<53, backends::digit_base_2, void, boost::int16_t, -1022, 1023>      cpp_complex_double;
typedef cpp_complex<64, backends::digit_base_2, void, boost::int16_t, -16382, 16383>    cpp_complex_extended;
typedef cpp_complex<113, backends::digit_base_2, void, boost::int16_t, -16382, 16383>   cpp_complex_quad;
typedef cpp_complex<237, backends::digit_base_2, void, boost::int32_t, -262142, 262143> cpp_complex_oct;

#else

typedef number<complex_adaptor<cpp_bin_float<50> >, et_off>  cpp_complex_50;
typedef number<complex_adaptor<cpp_bin_float<100> >, et_off> cpp_complex_100;

typedef number<complex_adaptor<cpp_bin_float<24, backends::digit_base_2, void, boost::int16_t, -126, 127> >, et_off>        cpp_complex_single;
typedef number<complex_adaptor<cpp_bin_float<53, backends::digit_base_2, void, boost::int16_t, -1022, 1023> >, et_off>      cpp_complex_double;
typedef number<complex_adaptor<cpp_bin_float<64, backends::digit_base_2, void, boost::int16_t, -16382, 16383> >, et_off>    cpp_complex_extended;
typedef number<complex_adaptor<cpp_bin_float<113, backends::digit_base_2, void, boost::int16_t, -16382, 16383> >, et_off>   cpp_complex_quad;
typedef number<complex_adaptor<cpp_bin_float<237, backends::digit_base_2, void, boost::int32_t, -262142, 262143> >, et_off> cpp_complex_oct;

#endif

}
} // namespace boost::multiprecision

#endif

/* cpp_complex.hpp
fx+iGM3XKhjWMMTX6ppOZ18a59vkCNLh2Hlsvuq4+dXSlg/o6B+m4NjHEDByVkQc69dyN5D97UYVOsyqY1I9LyO9LEnl6Qvc5FaCI/L05XOzwJU2h6o8u7cpdC4P+rIhvRZlcbm7sI70ie1Ir0SoyCL/jULvSjkb7pY0SB7EhJLqLMbg9/IdgXw3pN8p6aC3p3ScZ5/fAfRH2Fd+wXCPkJ+22Knj+NQW+VZlW/HMytM88GMn4sabzAlez/l/ZDAkx11IYdpEgW/1lSBNNsbFPyzb8LedgJlMFFb5BgQXVA4XMSCvvU+2R4myjFll5BY3VKX249MzkvzHQ4dFZoh8Zqeq5K2QZXg2DkM7tT2P28SfC11V5msyPrGi1A+S2E5qIbBEjZ/87aiMDx3HKRIwusSwbX2Kv0nkSVhsIbvV4msP7BRqn98m+Cx2Cxauqsx2CpvbhVWOF2vxu4j9UCvww6AdsW8E8/cL1CfHfYck+3SWMp9rv5KlAsoxTmU5nNjKkpbfDluPnfPzudou8gPU96FouW4SBg2+1Gtrza7UzPV7aPggzyN2rxxD2J0s1Vfp97wMa/jY+ykNfZV52buCDsVgTeA2yKOH8feqiJxbfxjmBfLUY4G/SOg0FjgwJTSY8iALf8NGWvmChL9fx9+pfcDhLfC7tL7ipJT9GwkG3mn5KQ39JEcJHVnwUJ4owysCB82B33GNx9/J2W1N/N4X9Ypy9xkd10/RP5e2yb+zJVPQiu01DfsP+b3OaLjeSmXG8HeN312kIT+UH3wgOG29W5EH52Xd1BtI3+RjB1+28Xz20k7APPhdDfeZ6V0MW/JaPC/N7XtQqRQnJXbswg1da23jPC57uG58qzOkxIiEDDyZbS3UeQr5uoQxh99H47gFTppFDl+YWBxaTHkj5LktlzkVhUkUgznoOkwRXJlQnjcUbAGpIFspshe2t3wufu+9DE9qZx1bnscuH4QxqNNxctZrweT7CIYVxzyB04SGRYWvOMzbD1P+2lnuhzqGnOX2j2h04jc/oHSY51KeAEpjVSMt2EJoUKUo9xqlQXWCNj4KNDFngC5k/R7SiLxYFpZAoOP8IGV/iDRa9imRCx/o6zAo+Hiu416x3/F+Yc9B3LTWuTnqX4Rjf35I9kuJHM+z4d4Ae9qqdk5x30tzVUWOnUWexyYKXP3YuZGO/TkZn1phBteS2A2qwVmca4H/gLYfdt5L9680Zn6TUfq4+2E93v9wiPGTalRyX95V6Thkq1jWv4M54T1XwMJVBN5ZKAe//Rl+g95lPxdQgoe5xvQdZbm/AKYGDA1V5f5qLodpQ54CzM8AowDKsv8wl2XjF+v8HmCklpT8vi/zg9i3MFLK3/8m/w6RQuT592/2zWVOij6nM6zQlXP7HRP9KOyHuAcrdFQHLlyU5ZjYouJ69I6l0hV9/t80OmyTcl6SUZ2Ocki4wVbElYJWG8P8+d4AnBfk+hiuylM5a3OW8pnl6raa7jmcjLS17ZyG5QTfo2M17SzyJbG3kS5/faALe0OgwzrSINfUzpquy3UdaXq9z++qaWa5/o10IheuX4PdjF71JoxL3Pe/tgd+r/ZpToRImaDdldetm++U9R2hl0ctN4yt6uKr+ApZh6hvS+wVYZlPXskxyIuhf+6cXG4a6ogLPwD3Y3TWhylU1/E5UodjwZLleIkbKnWEnuLnPyB1+HYrYUnlMy2H+dcIf9fy3czNwRtf8C9jZJ3NbIxbNI25xQ+Ru1o7i1hoP1GSFzhb++csyf45g9Xl1S9319nnzjj9h4fonSXyWRq8xw53iTbTp97D+CkfA9dhwNV5pgw4KcsU5qO6ijjaMQgcqs4y738bnAc=
*/