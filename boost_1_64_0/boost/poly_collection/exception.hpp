/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_EXCEPTION_HPP
#define BOOST_POLY_COLLECTION_EXCEPTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <stdexcept>
#include <typeinfo>

namespace boost{

namespace poly_collection{

struct unregistered_type:std::logic_error
{
  unregistered_type(const std::type_info& info):
    std::logic_error{"type not registered"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_copy_constructible:std::logic_error
{
  not_copy_constructible(const std::type_info& info):
    std::logic_error{"type is not copy constructible"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_equality_comparable:std::logic_error
{
  not_equality_comparable(const std::type_info& info):
    std::logic_error{"type does not support equality comparison"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* exception.hpp
PVe0PUn58ZM+TYyL0YwuDMKJvma23MvB1o8YCvXTqA+Ei3S2kTfeGaQNf/9dQO2xVYxZuAbhHPoT9yC9mlHg8xb+r5Qa33g/SZ+DHo4bhg8x5FBzPOFDP1wYxRjMJ/A5+tHD/zngYhvl/9Apc486/vY/wvsURolP8jg+53X1+LNIC3FCib936eJ9nDTy7CI9CXtsBteGdSX1lvLRhj4MwwM3aRthO4b2WuK56tCz5cL481z+v+M2OJrpc9k2ce3QPuKF3Cr61Uv4DLZxlJUg2xau1404r8dguJS8RAt6MAQ3QkiigGr+rtLKOU1su2CFF3EUUc+YvB0DcCOIBJrJl24Mkyd+JNBKHvTBgQASGBig3NK+eTi2ljrXiX5k0H0Kx5FeNrbl8efgbOubuR/6EUIGRvKjEXaEkIHpw4QBfXCjgFbyafx5dLefNGAbJk96+MwGL6LIo66FY9EPF8LIovp0wgcbPBjFGEzMaS1oRz9ciC7iuPFn0mzNZxI+dMIGL6IoNhLnBaQ/muezHwNwIEya26lTPpR4bSasBupQI9tODMCNDOrex71hRQ1lrxd2BFBEQy3hghNBJBCg3EaRRc9L1EHfod/RhGGijbWgDY5VlNVdhAHFVbS/HFdLu9BKmepB/W0chz6M8D7GdpRtA2HtwRivzdSJRnTDg0HSv2P3od/gOLieHxFkMcq1MzBwnQDnJ1HL8S363mIIbgSRoV1K/YR7DBAu1K6kHYQLMeRgvYhwYRR1g4e+w+hDGCk0X0I4MQw/cvBcyvFIjreJ6CGcrrM4BxkY2kgftKEfdngxigzq99N+LuY4jPIMKYkeJ89UaGvHyPfIy8zV88ylL6TOcmwaDW9QxxEsTDOE/sZnr9Hm/JXXf6HthhXN/F9fdtj4G8EiemEs0868zjFsA2zTCJa5Ftsh9PI6xnEJrtnEawcsvG9FM/8HX+AgfQD3zc7iPX/baEYvQojwmXEfx6Md3j/Qf7zIM4tXCTv6/kzbjAx/K5ji7zcdbFv5e1oT2yACvO4b/4xzymztvO9FgGMTbO1se1FELe8zyyljpHs9f/MZW07ZYJtCkLQY4t72ReNjfs7l/57vZFuHDH/f12Alz3g9jGbYiOsITPzNdDeGEUQKhukcj3YESYMR4jnA68GjuOZhXG86aXD0Yfy9D8eyv43XY7x28bmXY6yHkTa8Th7FubweYn+DkX2kYRiDcCBSxf2Qh3Ea12YMkvARj/Hni2hdQVlGjrJRfwPt/XryDrU/pC+DG1nKTN019Evfol+yc+1rOIYy5PomfQ8KiBwgvdjfASs8aBgmX9ZwLIxD5Dt64UQYjsvJu69RtlBGxxX0rYP0P1zbjZpBjkcRdReQ9xhE9YWcB3cL5yKL6tPZDzsiKKLhI/ST8CEN8xlcG0NIwNzKsy64EIdxEfsxjCjqz+R8BJBDw1mEB24kYGoj/WBFCAU0LCZs8CKN6o8SLzgRh+ljvIcLSVS3M0aAGwmYlxAmOBBFGW0f5z3icI//cRmaPkHZRxRFNHWQn0jCfDbXxAjSqPsk4YYXWVg+xXM8BJFHYyfxhBdZWJbyHn7k0Php0h1p1H2G+CGAAhq72Icg8mg6h/RFGCW0fpY8QRzVnyNc8CCD+m7CBR/GYDmXa8OPHLo+T7ohgeovkC5wIA5zD+kIN9KoP484IYAcGr9IviCMEtq+xLUQh6mXa8GFKApoXMb58CIOUx95ehphaSJNYfwz/ftC2j70w40Icqg5mbDCgQiKaDiF68GLOMpoaCaecMznM/TPod89kXjAhiDSqH/feFtI//kHnhOy9SML85v00eiHC6MYQ7WBdMYAPIihgLoqro0heBFH/1o=
*/