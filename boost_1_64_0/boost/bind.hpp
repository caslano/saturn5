#ifndef BOOST_BIND_HPP_INCLUDED
#define BOOST_BIND_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  bind.hpp - binds function objects to arguments
//
//  Copyright (c) 2009, 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//
//  For backward compatibility, this header includes
//  <boost/bind/bind.hpp> and then imports the placeholders _1, _2,
//  _3, ... into the global namespace. Definitions in the global
//  namespace are not a good practice and this use is deprecated.
//  Please switch to including <boost/bind/bind.hpp> directly,
//  adding the using directive locally where appropriate.
//  Alternatively, the existing behavior may be preserved by defining
//  the macro BOOST_BIND_GLOBAL_PLACEHOLDERS.

#include <boost/bind/bind.hpp>
#include <boost/config/pragma_message.hpp>

#ifndef BOOST_BIND_NO_PLACEHOLDERS

#if !defined(BOOST_BIND_GLOBAL_PLACEHOLDERS)

BOOST_PRAGMA_MESSAGE(
  "The practice of declaring the Bind placeholders (_1, _2, ...) "
  "in the global namespace is deprecated. Please use "
  "<boost/bind/bind.hpp> + using namespace boost::placeholders, "
  "or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain the current behavior."
)

#endif

#if defined(BOOST_CLANG)
# pragma clang diagnostic push
# if  __has_warning("-Wheader-hygiene")
#  pragma clang diagnostic ignored "-Wheader-hygiene"
# endif
#endif

using namespace boost::placeholders;

#if defined(BOOST_CLANG)
# pragma clang diagnostic pop
#endif

#endif // #ifndef BOOST_BIND_NO_PLACEHOLDERS

#endif // #ifndef BOOST_BIND_HPP_INCLUDED

/* bind.hpp
dQf5O0Ng5abl3TMZusFN9T1dI4jHbYfk9g+wa5e6018bxz/7wxp90fvnY4rHD9X3GvrcNkpfWd1TjbB7so/CpF/91PjF6veldOtufyV7Qd8xWxQl69dO8elbYCvnVvz3D8xCxK/5cADUC4Xk521SxW8r3tOS1NFvkq+cvfQNBPKW0XDb10jxRlI75uk8vSD9Sku5QGlI7qZa6/cZFF9tBfh5zAC/M9D1G2ODfGJQsxJ0/bXLLr3Re5/C+n76pH6fprD0K7X7tJi94j2AC4qE7NOJlPVR/BQbW6Cj5arO7NjVeu/YQ/avBtZpqeJRh0jt1XZ2Voy5+mZL+HWRfTmCaq+ckGX+Lu2Pgnpvq0Or6kjtN10EBh3NvhO1XpIBb7Okv4wFu/Yq1Y63cdJ7M+njhaA7Ie/C3Rv6HixL/I6SctAmDpMJ0O617H2dayWeSt94B6KXzLRFivcUmSt9PEj7w5eyeaX1fa3eBhyuLf3gJ6moxkzyTKlMYfl0vtxTfH+H4vFqbYQs8AwPEOE/yX7U+ZJfiBnOAH9VmxUi+0Nczik1u6jOvxyKz6iNfvItHR3CwB4QSf/Fso+UqhZA2cg98h/c1nsub51/e8k+eCX/gXxVmSWk/52FX49xIJrcYVxOFdHvh0kz31gecE226XapBtNLKT6jMQiW8b1YnujK2kIPBuv7ZJ0Cv+kYPinr80h1UoPkLZszXt8PnqFscG/Nb4q+nzGz1PckYBvqSDtuKn/OIEfFy6zgZ0XZUFlFxUrrfB4JXcsYUgvE5WoF/R7Ar/d1+o7KXaqzt9S3anf0e1A7QaxIpWzzJH1/3pTUBHH2UZArVzCCZ+3V70vJdxP2k1Shp4Blt2njvPiNULAuo7MR/OQHOWOh9yrh+j5FL2U/XUN6kyTZqxXpfqfX+n7wsa3erwGqyvHx6DzE9+UmmHYdurltyLbWEi3poPGTA8JYvwxwZ5fsrV6KT7eXPtSIKbNStl4/vQc+AomHsu2+IYtBKV9tl0m95W+/B0iWyXN9oPaHbE47KbiWPopX+Ku/xdRfafWrKtqx3+QzX6B78Kq2wX19OzJtuH4/TO/H38oN3uywvg+QkH72gENjdP/2pe4DKRg+A/X9oL7h6PtS8csdIKqG6TwdpPO0r+ytw6SuDYf42DTF8xbYKR5Kt94p6vZSo9txoL5f1TeUWyRGsfqk2g6D38yh2h9/sGc+ZgLuj4Z4o0GxoqeM+CUJdPCI/Ls6X8o+sEa+m6Q+BVG37jMQLZqTyiUVxzQbbGB76nYuJn7qas/55vR3vd476oK81JXRsK2j9Vcd+YLTFL+0A0zZbKfvYUG06EmqsWQ+qRh4TW9SHo50f84iUstmGSt+Cd2HCnp//1zx5EuKR4Xq3m+ieECq9D9fhGyzD85D7XW//a7f45mk7yFO6/frLlO221f2h35SaLAQDRJo1/u+/LGZsmeu0/0V4vJddB3H631YJOBChV/v0fX+StphKaku1uMAEzVvrXS9l0iRf3Kq7JkJ0g/yQbf2G+wvp4DdXIWsf3Odz1P0/r6X1l8GQ5c1HVkuRmr9NQK7O1Xfk0jL+LqOJj/Mh7iXNalFd2VfNqVGnSPS156QfbpZ8V+NaYQCPAMDkaXve7CetRW/bEU/3By1/rTznh8lu2c9NYYpvjr9FayeXJcdZaX1V073m1gV+EFZxHLdv0Moy9JXJPeS5X+RVBXk3r6/SvEZaXPuKrsUQTZcX5hXGvFH9q4FvKnyDCdNSkNbOAG5VESpGrVYhbKgKytsPSWBE02kCggTL2xVhtNNhq3KRCikncTDUbfhZNNNNrdHtvk8c5vD0nlJWujFC9chKFOuakpBiihUhGY=
*/