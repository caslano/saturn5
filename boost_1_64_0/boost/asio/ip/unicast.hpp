//
// ip/unicast.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_UNICAST_HPP
#define BOOST_ASIO_IP_UNICAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/ip/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace unicast {

/// Socket option for time-to-live associated with outgoing unicast packets.
/**
 * Implements the IPPROTO_IP/IP_UNICAST_TTL socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::unicast::hops option(4);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::unicast::hops option;
 * socket.get_option(option);
 * int ttl = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined hops;
#else
typedef boost::asio::ip::detail::socket_option::unicast_hops<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_TTL),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_UNICAST_HOPS)> hops;
#endif

} // namespace unicast
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_UNICAST_HPP

/* unicast.hpp
akm4EhPP/XLutRqupEa4rU0JZ9pbduNRhMsw6XZRikOkbANto2wW/8z98fcid5c1mLOslDhxN3nkfmn09IKfE45KuHizLotb5BsbnamnaDtPYx7TNmRz50neq3ztw18/tC3TjuzyN20LqltpoG1RTrhJOckeNB9L+tEfS9J91bSt5YWZv28neF1skI7T8JFDR9kKWFI+DTNDdJuQP3H9K+ILq3+VmRiatuW9qevQtDmXFdBns9A0Es6sK9Ak/LoCyJz4ugKcM2RdgSah6woY/Tdvg9D8NSWOQ2Hyp8plkcqfMLXqluF/4rplDTPrplu20x1J1+r4dcLC63h9ezpM4XW2IutmLT/Fdj9/xi2/TVo/7q1LPpt89MrWE5/m3iE6W9Urvnr9hS9KNl5br/SDA5Ne2x1JZyuSzlMkXbFIumiRdLC+e92+8DpekXTvjl+3L7yu2PHrhIXX7Yuowyc6ZHotyHtPXxdptHifcfzmvcX8/hiTaem7sL4jH8F4MO01HoJW2ewI6/n3gFC5fRqO5zmxp2EOa7jHkGsKn4Ct4JOwHXwdnqbrEPTUdQeG6zoEI+GzsALugfNVfincC2+Cz8H18Hm4Eb6g6wq8CPfCffAQ/C38G/wd/Ay+BL+GL0M70a/A+vAPMBnuh02hHb4TfA32gQcg5SXpkPIy7yk8F2u+T8G01+8MuZrPH8JucBTsAfNgbzganqnzwIfCsXA8xMj6CReoPt6P4Fp4IVwHi+FWWAK3w1L4CsyH78AC+AEsg5/AQugiTdOhB5ZrfufCFDgPpsEKzW8lPBUugKfDhfBMuBgOgBfBs+HFMBdeAkfqOgzl8DK4CFbZ6YdL4Up4eaDceEaPXG5Xarkt13JbqeV2lZbbNVpuq7TcrtVyu07L7QYtt5u03G7Wcluv5XaXlts9Wm63aLndquW2Wcvtdi23O7Tcfqbl9nMtty1ablu13O7VcvuFlts2Lbf7tdwe0HLbruX2Ky231VpuO7XcHtJye1jL7REtt83muZBrRq872QPdsWdRE9hV9T67w/awB+wMe8K+sBc8C/aF58MBcDI8C14Ec+AlcDhcAQdqOQ6Bt6v/ner/c3V/UN0fst2NHqM+R+kzQd8aeoxfOuSq6yh36BhyWz1WrfqQhf29Rm8ycXOwbuTOZR70I4N1I/OC9SJVHzK8LuRhwkfShfRe6TE6kJMxEfQeVecxWN8xWK/RqdMYqs84kfOs7ObUYwzVXzyKCdZbDKezGKqvuB/zpW2yArqJ5ZxPdRNVHzGgh7gOv10Yny7isfUQ34eqexiid5jYAzOY9BNfRo9wuobHp2f4JfE49QvRLTR6ha2We6z3YS4Mp1eYv9xzTN3CSHqFywjr0y08tl6hX6dw+ybyBUP1COuuQ7gatoJ9MX59wXWYmnqCR+EBm5jtpNWpF7gHexZsmmP0AdEFDNIDNDqAy7jOVmO/De7CHMbEDfBaXTE5mGLMqgFRncDoET2iR/SIHtHjP+H4nsb/C0vm2cP/Jzf/3z/+nxUY/ydeM/wv4/93drYC85wjjP9X/TO55vh/cUFFsR1ZnXQA/OMcB8z+Axz6DeTDZN7vfPFPqWCAY/qcXj1wdow94Br47qmyrcR/vsRCEPVvDNeIfwtNV+3fOuPM93XOUSOtvXUsmMdUShw5+DPKotqX1oJCHQWmDCQtm/qEGZPRtPp1AQ6IvZn7bpdTP4EYdDxmhAmT4M62HneliBurwX9hu13s6mZ9bvV3tYukq6BhU3S9fL7biL2le7OLtQr0fHzFEP8J+P/RpMfr8C8X//H4y3lJx1yXU1dhplnHv5v493Rtxk3XhNcwpa5TrS9JazppM+etkG/fOqY=
*/