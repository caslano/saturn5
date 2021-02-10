#ifndef BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/scoped_enum.hpp>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__

# error The Boost.Endian library does not support platforms with PDP endianness.

#elif defined(__LITTLE_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BIG_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#else

# error The Boost.Endian library could not determine the endianness of this platform.

#endif

namespace boost
{
namespace endian
{

BOOST_SCOPED_ENUM_START(order)
{
    big,
    little,
    native = BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

}; BOOST_SCOPED_ENUM_END

} // namespace endian
} // namespace boost

#undef BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

#endif  // BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

/* order.hpp
LVERV4n0SCqOi/743VGUnaQNkoc6iGVJvO/uvrv7yP5lD579tA/rExw8+kn9f4ofvHZGM6P/FZn7sUGafoP2Dw0v8foEVwPYW31LD+FJVt/gwFulwdcb+p2mT3B3SUHS14CML1P6iU9ay2A/1OutkVelg4PhIbx4/foPeA6/Hf12FMEJV1JUsHBCrYS5iuBN7p/8XfKbm74VbyMQDnjVvwO4LKUFqwu34UYA/q5kJpQVOXALubCZkSu8kQpcKaCQlYDhdHYxmryLYFPKrAw4W92ALXVT5VDyawFGZEJetzBrbhzoAhEQP5fWIWbjpFZ9dC/ACVPbAENB8Mpq4NdcVnyF7riD0rm1/XMwyBpTYSaDXGd2kHVU9EtX38vqAqOp+Rb02oHT0FgRAa2PoNa5LOiKFOHDdbOqpC2jfVjoUOUDbcCKqgpwaCqFbVMQsAhsRbQS1hi9dHSxWlnytil1fWch0hqAisYodIe04LpcI/ERNCoXxq/3RHReAsue8kdKto89B60wKujFCxgterDiVtoIzkfL99OzJZzH83k8WV7A9BTiyUXA+zCanGBvSPRqQNysjbAYhQFZrysp8jvOf+qks/7yPQzP5uPpbJnO5tN382SxOD2bDJej6QReQu/FK/inUdjfL37vQa+S
*/