/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    and.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_AND_H
#define BOOST_HOF_GUARD_AND_H

#include <type_traits>
#include <boost/hof/detail/using.hpp>
#include <boost/hof/detail/intrinsics.hpp>

namespace boost { namespace hof { namespace detail {

constexpr bool and_c()
{
    return true;
}

template<class... Ts>
constexpr bool and_c(bool b, Ts... bs)
{
    return b && and_c(bs...);
}

#ifdef _MSC_VER

template<class... Ts>
struct and_;

template<class T, class... Ts>
struct and_<T, Ts...>
: std::integral_constant<bool, (T::value && and_<Ts...>::value)>
{};

template<>
struct and_<>
: std::true_type
{};

#define BOOST_HOF_AND_UNPACK(Bs) (boost::hof::detail::and_c(Bs...))
#else
template<bool...> struct bool_seq {};
template<class... Ts>
BOOST_HOF_USING(and_, std::is_same<bool_seq<Ts::value...>, bool_seq<(Ts::value, true)...>>);

#define BOOST_HOF_AND_UNPACK(Bs) BOOST_HOF_IS_BASE_OF(boost::hof::detail::bool_seq<Bs...>, boost::hof::detail::bool_seq<(Bs || true)...>)

#endif

}}} // namespace boost::hof

#endif

/* and.hpp
tWlc0F4pmGam+/a18X18mgeCGBn7fnKCvs64hPd7Nibof26Kf3/r0/j39IT8TybE7xbx77+Mj18xbloc/4C3IotzgK/0GOKEBmyKRc2J4XQzheQjhDxmYx4TkHJlz+BRsKA1Klmc8bUUGbVn4xzsWTdUe2IaixfMAJHj9NcMet8EJV7gJ/Nmw4W5jEkY0w9LLZ8YFJxV1CL9Irv+ypJexScbeo/DrcUVht7hWlvD6ng+LvYd2aB9Gsh3y+AV1Pz2apAMIhYKzD3Ccu1lH6u79Ti0M6uyRvz6U3PxTcbio6R04Exoqhsle1jHPSyHzG4kaPDrgga/LmhRDLuDjKjm8UgxJaz7O1HBxH/REe1RPqhL6X+9fUR6Cs/abHlXaTpi/gR4vna7gucq3oR3Sq0+ppzm6Z/Er8eOH8e+K/uHEIgUi0Fokeumd12ZVv4DXjc/xKi2bjbWDTXfcFCfDT+7woGyYwwykTww2PgPfmQgq0xDwTrTZxXoY9ho9jILu0gFk1x/w5APyCjuFdWnnWjIBzyTqE8bGKyv4/TtXE2gGoxxh9Y6IWh7C3A8yADWWSPn1Yj3/q5Iiv2pE7QLyJpJoMw/QhR/bKJX58WsMep03UWx4/HuK0RZHMvwLQNrRyXyyURXcaKVSHR0N3VXA2dnHxkduJQCLuVE+PP9tg/TS/Q5BTwKeTSzYHD7Rfljagd2ZamBOgtRUL5o4tHDuFLy4Ou1NEbHJnE1f/Rh/Ppb8kH8+4Gv4t/tH8W/+16Kf9/xZPz6dTL828bDKQUgxXWvMXUCflMy977Ze8OpJNfnqEZ8Nn094gcs2JN9xHbTPcXMF8ZL8yCkVrHq/jwU9bHUBEp2ekQHVBi9RePS1b8Ru9FVvpMAO6XrT1+P+AzppBWx0wmxRqCdKR/dBcB3Y08Lb3DIdzzxIW9xKAV8K0ZtwP+30B5ugV22AC1D4WgBt1J9xeXcAHdCAzLFbZ/GNyDfbMCRgWLi+A98K3b8929R4194xPH/8NVvG//CmPH/K1JH473MwmCnFeKjFSajIZg0Fdic34vj7Jr3DaA0fxodHmA+9ADEhCwqUCZppi3tEYkEEfZbQcQqOPILdvJF8sVUDJ90JOisi/iASkmikE/ccj8Yc5WiB8omPgrSwNDn/TBAo3CgSSDofRcUR47fjq2x4/fkZn7LpsUVHbVJfzrCqKn1j/w8MDTSHjF3s0QYwvhKXz5BgHm2uIBVuM+hJCCo5AyPuUBF6CGqAi14gM05p0+ls8TwHOLwRZuy1y6jvwPFipac6PFrRXc8RSM+kjYPcFO7kZ4WS37M9S8aRw5V71Rf6OHhunvMPcE7ziMWpRr9zcDudJjkWC7EZ0r4Pe2Q/WhS/lQyxHjZNI+5ZTrZqSSkAtGwoG4gN1UKcdwhm7rpBUMkfivEAWkYpVygXfx0BRWVo689HiaA0f7nUqLtvzBVtf+UhPZv+b0xX3tSEztitn9UEkcdpQ1MT9arMti5SWk6GXWT1/8UkjCPbNdusKrpuY36/FPZ57efV9Nz9PK6yfJgAzGmuNnxxS2VxTUetTi2P4fCeujjUO5wtJF1i+AhJoNpEE1HSE+8G8e6YekrhvR2h4dlNB0xPjyM/iD3T1hKeniYG39I7WQ2kbXpSOU9qMo7Zvscx24fuMqMeV6Oo1Qn3EjUkbnbD/8mdS9gDLb+LKDlohtEJ/wk69f6C5Jb7Hpva4QTPmkkzIIp861Ta79VnUaeD0sBQ6Wlt/T8Peqc0iuprRPCtLk2efgOwqfR73HDMeQS59ZrD6r9CWbpTXK63l2P0+IhFc55JqC5ILBLwE7IDLBpvTKjzsJAY5PG4h9bOX2NKJeq9dIfe+A=
*/