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
3JRuDgAInVQYD4jbBk+E2jjTHeGW/ncYuVeaj0K3WuCLrpF28ffL/tSls3rSDiOoXdWmWGRLiu91T/n5Liqh+kIIAsOH42JbogUe7haOHdEc5rP3rreWA953bdtk/ETQO10NODtk8A3htp18CgOoBoIU1KNsVsgusc3yvMns1cT2TnhRnNTpRgAJpfu79nTfJzbNPPlVPe7pqftgDn5dtlT1O2t/v8Lrxsam/fyLtXV2CD2f7VWnpYWgLcSEOwYZCZtliBcVqxaHQFw0PKPGpw1J2UNhuWfwPmsDpVApX7TX2iI404Vx1nm/+UYv1rrXSPTc4zfOGctXpuSeMiSmuZex2BiwPqLOc87exBL4l1/+dqUZ47Z8BMbN59EHt3bQtg+BZ0o5hnE/42BX4E55CG3ocpf+fREfGZXt1In4ORZnHu4XjZGgYZhkl9B6xiYYlbXVH8teqCmRk87CG/uOk+rZ2Ovcd1ZWUM3VdhlR0EMrj1D6voGfUu15FhTwc9FVqjGHnfMJQqLSL/X+ASM3Ii9o7jJR/rejD5MjQXJKLTt8iFzUOLBhUy1+PA==
*/