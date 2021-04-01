//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_ERROR_HPP
#define BOOST_GIL_IO_ERROR_HPP

#include <ios>

namespace boost { namespace gil {

inline void io_error(const char* descr)
{
   throw std::ios_base::failure(descr);
}

inline void io_error_if(bool expr, const char* descr)
{
   if (expr)
      io_error(descr);
}

} // namespace gil
} // namespace boost

#endif

/* error.hpp
ao0ED8WkN+fz1cmh3QfQu/qHYHT00yZVPUYssGMGVEcDfuLGIwIyFKN2wRqv+VKqk1TVYBrCBx3rl1UzVsMco5NK1T6wM1Xxn/FUQAwPt2MFwxbbFRYk8A+C4ZHlV+PxE2UwL+zJQMWgrrlnpYt3oIB+QDtnY2qYjvkOYyi+42t0s8O6DtTVLew7ZLIYa6OcQELIasdOaNEo7c9q9jhRcpvK2wDJk2XiVBLm1psqCDpmPYSep3x3B3mNIxnxlrZE6LxNXIVcrxD33XIbvzKK6nfKZtdq8GKl/cdsQ6+MVzokhC9SSm2g1t0cTwmsy6ks3aNMsEqz6LiSaIjE0RR8Jr4RDLBKkc46vnZMVjH9CMiE69PhpSpRGKn5HOG0/LDZUcHeLo8OIH94F/LrC9mTc0CJ8rovlFBnuhR1V7MIYibrXENlfnAlf3pQseoCatV+84UmuDo/5EgPFh2cSEPlz9cdIMUdlMUZ9rUNqGwJmHGKxkkZR7jZ4T4m8JWcKvaiS49pe6Uj6KRJDK59yAYqTJzvfTaQNGIoxibHFkpI2FphGAm/xw2HYCH3Vw==
*/