//
// impl/serial_port_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP
#define BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline serial_port_base::baud_rate::baud_rate(unsigned int rate)
  : value_(rate)
{
}

inline unsigned int serial_port_base::baud_rate::value() const
{
  return value_;
}

inline serial_port_base::flow_control::type
serial_port_base::flow_control::value() const
{
  return value_;
}

inline serial_port_base::parity::type serial_port_base::parity::value() const
{
  return value_;
}

inline serial_port_base::stop_bits::type
serial_port_base::stop_bits::value() const
{
  return value_;
}

inline unsigned int serial_port_base::character_size::value() const
{
  return value_;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP

/* serial_port_base.hpp
8HL4d9ED/Wk3cDj0V+nD+nAKrAenij5T9DmiZ8JW8CbYRh0fdoR/ghfDD/zN+v0Cfg9/hD+odglPwX/Cl2D9ejxvw4ZwCvG6w6mwL0yCA2Cmsg/mwEkwF04TPVn0GfAquADmwUUwH66ABbAULoL3waWwHJbAXXAZ/BIuh/Xrc07DgXAlHAdXwctFTxW9BN4Ey+At8A9wNXxU9LfgWvg9XAxPwdsCzX4kA0l8zOxHnpH+uRGcIf0iZaSvG/71zP6hPhwPQ6EKEwhzYWO4BDaBJeJfCpvCbaLbrycJj5vH6+XhesK1U99f5cN2+jphPjfT9+j4Ks0Sib9c+nEVfoXE51lU348+AcPhbhghelfRe8I9sLehx8b19fBpmKvKAC6DL8Bf4H440Wb6X6rH13S/rOMthQfErjH8zn3CtGuN2NVFPRdC/Rzra15fLoat4CgYIXoP0fuIHg/HwSGiD4PjfU07J0B9rYcz4GSYCm+GJXA6XAGT4RZ4GXwUzoRPwVnwOTgbvg7nwHfhPPgBzICfw0z4FZwPf4ZZ8B8wD6pM5sMgWABDYRFsDxfDLrAEDoZTlN2ij4MpMAWuhJlwFVwIb1J228x8/CB74uXuNstznbwvi1H3SVKeu23m/fQe2AU+C3uqeoQxoveD+2G86BfC1+AIeBCOVvUv1/c34GT4JrwUvgUz4GFYArmW6PcjR+Btoq8XfTt8H74FP4IfQ645+r3apzAIfgZbwVOwL/w77A+/gQPhd8ouWAVHwS/kvuA4TIG/wHXQ5kM9wnrwKKwPfSmfANgShsB2sD2MhB1gTxgOE2EEnA67wMtgVzgDRsKZsBuc7WPmOxv2QC+CUbAUfij3HypP5U+b9fOY1I96jvezv8/0xw7lB7vAx2FPcY8RXdXPk3A4fBaOhXvhRNEvh8/DWfAFOF/0bNHXwpfhnfAg3KbqD74N34E/wSOwBzYdVenCT+Af4dfwMdG7+1Deyh543F+Xk/ZPgt/AefA7eA38Ad4BT6rjwlPwHvizv1kuqUjQc2a5pBlmuTSESdI/+fqb/YA/bCF6W9GjYD3YS/Teog+D9eEE2EiOU46UynHqS3+j0t0qx/nAz+xHP4Yq/UrYHv4Eu8JP4BD4KRwm7uPgMTgJfgGvhFyrdXmfgEXifg08Dq8X99XwG1gKv4dfwx/hSXgS/iLpYzcNGFuel/cK2m6owondpZz/HeE62AWuhz3hHXAw3ABHwDvhRHi39If3wNlwM5wHt8D58F64DN7na9r7AFwFt8Gb4Q64Hv4BboA74Vb4R7hbtVf4DCyHz8PHpL98Dr6v2iM8ptoj/BYy1q3z+yRsaKOfgsHwKdgGPu3reC5KfMEsh9WG+3MRH26W6PqEHZSdMFrZAQfCR+FkZQ+cBp+CafBxOBvuglnwCXiV+BerfMJlois7DhnKaHnvIfXRkt/7xI69hOuq8gn1OgJwrMovnCj6ZNGnqXgwWfTLRU+FL8FsuB+uFfc7VH8J71b9JXxa9cfwRfgGfA2+BVV5vw1Veb8DP4Lvwb/CP8Mf4REYbKPdS75ykdQXzXy9KuUbAOfYx839zPLtAvVeGrAzHAhjYDc4EEbB2bAXXAhjoWo3feF9MA4+IfHs3zGk7uO4+h2C+3cMf/Axy/MhGAMfhgNFHyT6UNXu4BRYDqfpPtYsx8fhfJU2XCnuq+FuuA7ugX+EfCOi7SlCEl8y7Zkm9Ruoruf28TjChcG9sAN8FnZS7RsOUPUOF8EKuBi+Bm9UTQY+AF+En8GX4a/wFWW/TYezj5PgKN8xGu7jJFt95PsJ2En0LkqX/G+DV2hd7guQEkmvieQnSM4h9ce7KN1/XCz3BWNhApwBp8I=
*/