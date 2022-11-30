//
// ip/multicast.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_MULTICAST_HPP
#define BOOST_ASIO_IP_MULTICAST_HPP

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
namespace multicast {

/// Socket option to join a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_ADD_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to join a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::join_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined join_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_ADD_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_JOIN_GROUP)> join_group;
#endif

/// Socket option to leave a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_DROP_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to leave a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::leave_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined leave_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_DROP_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_LEAVE_GROUP)> leave_group;
#endif

/// Socket option for local interface to use for outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_IF socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address_v4 local_interface =
 *   boost::asio::ip::address_v4::from_string("1.2.3.4");
 * boost::asio::ip::multicast::outbound_interface option(local_interface);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined outbound_interface;
#else
typedef boost::asio::ip::detail::socket_option::network_interface<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_IF),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_IF)> outbound_interface;
#endif

/// Socket option for time-to-live associated with outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_TTL socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option(4);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option;
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
typedef boost::asio::ip::detail::socket_option::multicast_hops<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_TTL),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_HOPS)> hops;
#endif

/// Socket option determining whether outgoing multicast packets will be
/// received on the same socket if it is a member of the multicast group.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_LOOP socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option(true);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option;
 * socket.get_option(option);
 * bool is_set = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined enable_loopback;
#else
typedef boost::asio::ip::detail::socket_option::multicast_enable_loopback<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_LOOP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_LOOP)> enable_loopback;
#endif

} // namespace multicast
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_MULTICAST_HPP

/* multicast.hpp
iiLx25izagVZ1vrnTxqmzV2CWey/QEwWLRVoi1y59M4P4BljL7FgI8TKJdiqTzDdcvb+ykMHWTrz6wPAF6kW7It6qZW/A51onyzf6gcZ3Has1j16CBEcJoHX3R4iOgfEzybffvDpMw/Xfb/ZEYeqsvZ750Dgkj0qUWoZvfpL6l6J6KFgDTWrt8I7tHaq5t46d9sDBw6LjZE07+cB7trub9CjMuW2GXSlVCHYUtifJ2Cig0D5PiXxWvaqq/vEAc6sMGWoh8mKZNpLPWkEI6hfDKqGRz3ycWwyr8z/A2hfgP1Fk++fhqrqVHqRJg7/wycLNUAa88Ekh0Y/FuRQUHGajr9eFHC3kvrrfbj40i9Hb6ReXQWT1faQoEnledKsmSeR/zRtI0TdKbCNwat+0e55Qk4/2DMPAbagA7lBWeIV6y4VfpvgGhjn4VTexy+S2uuNZD2daLXkry6iW6Ln0yHZENlC9Z9GvC1A8OLhCi0ZfM94gUPZepqOl2tP2FSU3wPY2GYn6j326Tk0umYX6SkKORI7wIqCTYW5UqQzc7eKTsWLvChGWtJYZoHkmNceocRVhwylXM/fpo9yNOczfEiaGncOPqcS4DlqMgAFjA/X5j89ApQHWwJ8oY6Nxc2C52g2wYnar8kPs4oQzlix8PLolgA8uloBl39aoy7eAQaQCh9X1hLDfHJl9efqX/y4e6a6Tj7Rut3ofJVF7VUaEjmm/DhQvgIXOoKNW01O1m49secF1AuiL54viP/obemnXpGCK9Kgm/ZlWD7ESx9iw5a8iTeGvAP3LWXDiH2JixmtkTYk7QAIhvM2gDFe1izFsWXxl3PvQKwsJzDArpmtzWBYx+4WXnTDXJbB2mPcouoo79I2ZF3YFB9FuiD0h+cEXueT8vUucYM0hOcsZxDIfgGMm8YZxJQL6/e6a/TxuF+DdNLF6GISiu7fBBeAawDQgIN19Tl9Nx5l+q0EM5lyxoECsvpZbvagTU7FrAaTJU2csykek7JgZ5dhU4LeFPCOG9/JkS9AQGMkk5KC9qlK7KLCMSL9ciI7hOwxTWzzjp+xihGOozSYwY6Jw77iaPLwwttqpeIta8rmfNv5SpRCEBYbB7lW37EDvEP4wJT6ryszxZy6dSfJH1ogNOAZPv0wEgSC1vw02KV8NV5dHjOlWglhwuATHY7O9wo164TDlm/ZP7/VlvbzsNAHfa311sJ1LHHnUT43YsumBC9c0K5mcRPTrKeKoNb7hs9htZmqtuQMvWhaWBXuLZ0XngNbCKzxhzWv4OMTL0z7pX76LHcHkCrvrGfHYnglPqRu/suslQH7jC++7TNRc8pqJw/MXGtZzowp87AUdExzlVVn4ohuIjZz/t0UORM1zOBDazXFgmCAyxYCqrqkQ09hS6SpU2hSY+6l0n4OVXySI6/rNpThMuxO6otMMAfjUdfnfD6qhWMRTiy8XKbTETE1yvU+VY8U8oHES9TpUtQJ9soN6drN9FqmG+uak+XU+5yGBNnykcRAzIlYVA/Mt3i46gez3I6efN3d9j93uHn1a7lXYq1EJx52F60AAECL2rQiDPBNTTicaN7Pr/rVZwQuvLWU8OCicEwz9+vbaZ+XF4CDo2n6fVuO3sHlDM2akFtWQonjTp1lFF+UbAMeXQMcQYxYbZD8jTgG03CYxwTYR0HiryMBMHA/yD04BFj9cF7viP/Y1vof1q9WMSQD6MQOnKQrhR5iC5n0UJPP25cn0HLKur19/O4Woppw5t1m82/GDFBeza4r3NGcNOa51jWJtxtMXQtxsBMzFRKKo3aIWes+WfYv6LedwSAVYokpIElqTqLOwVtpjLyUsLfu7ab/TY7DjYty1E9oV2Kq6aKtRQueJqfXImbC4AhlpKU79A6yV5VRM2MxZVu9bsVI7ue8RvM7pcN7bWuxjSH7pZqm0LL0GODFO4btnia6EUzDdafPoGNoOg0UTL8NJLV9t7BRgapOMXLABiw/+ARurzJ88b1cBaUkY0cp4wQBZTswC514bxd8nAC5DkSrnr7/c9VbjCZU0ErfWGp20D0edJ2bKUdxMwqAaNbguXpPTIQr7UQbycsZI8KRdWwE64CxtJPiK5K4QVmbWh/lktw7Qpvu+S0ITPptqS+Pr6To1KOMMrmfAjLiq5arwEyZ71b/8p3/GL/Sv3yli69KDOBTDVh+9a/Ms7rjHmsjVekZi6hpm9rWSuVsYwZFH3ZJUKp+Y/ppRBlBPFWveTjYFxFXU9c0KbjqLMMn8a+Ih0U/aSJCui1OHTbEKbOlcXVgKEkLpqC5wp+gmUanuyHtk0ScJwNuMLN2WSEYbAysPT7HiDtdiV08FBGDc1VBhHTH5inJoqA/KJE4Ldm19JDhold7JbWbygWv1u3rmoH7pGpZguROxNti9jqcPd3B/0Q2C2OBfzVOJkBedWcQCsX9zjFAvpEYCDgILVHf2rk0GADDTJVrlSDCycbGMZWIZNKIhWWdrhiwMs2Ga/1eHlNY81BcuDt3CQKuyFDUEmaKyEr0AWaKgJzozwyAJLncs4R23+/gCttLqMhGGsHRjAJu/vfpyQiEtUnx7HLgz+4BCLy84ODjxOjMyFr/fbqqKtdwlrb5tag2AWOKb71EIyeErorZvaurD5R0Qs3rVrxQAxdJSY/Y3BGWJOiqhMUB2ZDU6NNMuDj0beCmlDYR2/B4+PkI32pl6rNcVWdYamKfzNBcVnO0oYpeWGdE7+2l6xyOx/5im3+4MfLiNjcsqGX+7hrOtresSbjc+aZhfk4mV3f3eWDhEpvrb1gK7VRNKlo13xyqd5jDHU5CTDVIig3ooEZRvYFgETZTtcM21gEaeyHRTFLZJxe2orEjsitc1/jxUrIQue61u9thTnwfUOSpenGW9WF9RCSic+ThK6EACGkz3q8ZgP7IaF1yntshp0vZdn4ItwDkQhmAZKkBmNHbNLYsMYZn7U4VJiWBtrt/2dW+3VVnVteU82w9U16p/kxvhbGes3eqjQfXXszN54HL6+AMpafYfTumlhZSM1E1wRhM3XTgEhasWLxaYrlTRRdu8AyKNU7ESF0rkIVJ7BNOGSKpOx2KOgfricE0QY8YzBwPb9BFcKwYPgDReTkgL6j4rT507TmX1dHMbq1fYWdmZ5VvBQg+q+HDEgLcgLyAzGfW3u4fqB/WE5FSEl/bA0gYggAOzMvLHR4QADs8PjzY/09qTlpWTk723YqRWksISsjXHhUs2HFU9UXVdVR1JTgwUjp4odOTLHUuHYnCpuTXS4XA05PN0xQBm5gZGJuWd7FOZWJd85z7DNP/8mOsEmYA9ksXFX5u92NK4NfLD1VGGxYCU0AAlJraSwhhrRYApY2lmejLRHqvO54LnZuaHzqJAZg7CICfGDk8Ny8mAp+EBAYJBSACApoh8r9HBMcADJBg0LOMc5Gzd0yQf2vnoBqYoOciICIgmGtrGBjr6h4sAZJ0K2D9r1BgoQIqLgiEwITiyBQm+hbGdtLjoyA3G3ZiKAA7BADi+t8HkED9zzADFagAQECgAIAhUD924ALdCOAC/TyABLrnwAR7/IAECBmACOKcABBHlAAgkmgAQC3YAPdk2AAJP6AACYRgb2XvjU2rLS1urawMwcDwYQmAsdHS6qrB0rLiwWj/xqDEWjvZeODAP74RJs6xMNcQmX4ceXwxQ/Jre2o7UuZvwZPv4R/tjvUh+eIFJJB9uF1OTn18sT/oW756oR9vu+42N6DVOav45aCQqQmpk8jakaS8gKW8uIVS9bBS2P5jn/8OI3LsbN1D6nuWHOifnRxQhd+SWtn1et/au71u+NrZsQvLSUjBpTA0tLXTh0ZhBA9Ljw/ITekduFXa5zHL77ftIHzNXDw1B811bn7e+rdvhbTUY6DI9bv/cLkF0ukYzr6MMWCkho5nKZU3QetOPE6pTat63LmoQl0zhr3oUjm6ZB9JamnL/PA8Vc8lY6FbB26qZXaFFEUjMHOzkH4gr5gp7CZpdl0eZJn88BQMPQopR/fo5w3b0tsZFGssqW2Frvfo9V3DyqWwj3N97KbtknNUo18WQJi05WJsI+vXEcpwOmBTah5by3hIldw+A4gasn630J4Ga4fJx3rRpGBHEacJf3Vxus8RwiTmY3WtKsiWja1CY1BnIqFbliiiprHTxqMNsYo+NlWbdNuZRIVUOfJYyFvvYf6eCS4ztZm5Lsu+I2DlG2aRqyR/FrQnl/Vfmezecsd8xM2Q1TpGcuaDhRZyE52Ffzzj2dbJ9/BbiS+3V00YzHDmdTJdhlSkzjgpe4n+wRKkhGlCUFf+dVRAuHHeWeTBhzBRI17MMyFn8ntSVUhL7lMP7yr3aUPYWNHmiZFcDTmEYtnbl1+k+squmdzauq7yPB6P3l53ORFE9YBZZ08NsPuJu3suOjCvCLCXCwFHZoAk2OyLgAO0PQ7EVybET2a4FdDulC8L639N4Le0toJy4y84rHOfvzW8rbubn8/d3y0c8vP7Rd/MPyVY+f4RPTnZATX5KSEtKcdOLI0BxKtbk6rzmmpzABTGe+aFZvkEVHdtFMhIyh+soz9oAcHB0U80AirIPva5EagUpvqGxtbwsTe7RncWJxag/jSERHRAuoC5amD1npngEEC6g/39gwJ9wSEhPs8XpFtWLMGrd3d1u4W9gkJDQ2T9Y0OjI6QkJcTkJKWEAyMl+iXFBeCMjIyI8U1OTYz284xMjDxqQPcXy1Wrd3UNCAj1GOH2ERg/YW1lrgCTUv4gABCggjD+/wL8hQLcL0DyfxeW+W3oB0xZjvyagXJrEPwsRN7NLnH2WFFA2lEpUADoCXpw79Swrxav+ENm+47I/nschSJDFSVb+Q3PSodUkel/5lr/JmbmtbMmQDN1JUvtU3vin5XO9zMm+4+fefF2eJhgGsAQrAEaoqE+KAsV5QDdEAxyHpqBuYERmrmpoT4wIkIDYVqaqNoaqDow2lpIfxBosQwiPRtDAzMYYx0k45eUkfGbfBhEHUxAoDQwAhJQWpoZAMK8z0+Eg4AM4fBXxHsIAgj+Qe9xxk7kZ/cR1l3zB3eXojHs8KHP9dBv4VijgpfEQbOFbH/ZQ7i27DX5R2R/7NUOv6EPYhgStEBnzd38idgHn81PU7JuzpLKNIu8PkwtlkcPOjPOR2dF5lP0rbxiks6/zEUZCxu7ULdnTpSq5FUqXS6ctwDoAR46qBBbvOWrCKhAzlSzN+j2MTspkR52l8Lw1RgDNVwzQgpiakUtCmNxWaxwcAqDXS3vtLrC58gLed4Rp/Mp4DYXjmlJqFuSKqckz9F4579VO9ngktFPNmpOXVUE3BQ6MrKaZlNVfsV0UDG99ex2qtsiVAvgnNLnnxe4ND073MNJL6GeydTs29H8I7rff2izLrFYBrEbzNuXcYeXsUKqJMhrQVBWlAOfCR2N7uhldvPlXTnSVTCnR0OBJLCp4skdT0DR9R6FFIORbkAYe6D37hLXTUhsCcwXzcL2zBg63NZrTCzgMjKgu0ed+XrPOzfsUlnai3Vx05wa4EzEVHKxgxXRDxw9BywDecrpcjk/wQDX2enuBdD8vz4t4hqniYsiHvSCOkAspgKwgqYGUqiK+oKBbukn655rbm4BTsJTsZSSm0pubqL51Wu3+wWPJsf/5jXL3O2MjWNl6Pr6Ik9TmsiYyc2kdHXNe/mBV/GC9R3knNXSqkM1Jn/I8zyGtPDz7gsa1VqkDN3rSxJj/suGo1J5jUTcTllC5/epWifkeErnh1b3U+v4vXH1vb7777+PI77WlaZut7vvyXvASB7j88dfu/CEgJx7dkNjkO8YjIwfftFoFoDA36Dhs2e/XOj1dMzfNocCgqp6iLfa6JQcFfn4CMH43DzddJV/8vIQJNM047Jzg/AnQgaivgjhCTLBeCREg4NURNP0NCQUFATTw9JzBNPTw7Nvu0Mh8nvhwZWgj/m8b2QxZ3qOhMzQn78yr7oEQqIvfgdCClrU4Jeny3tpJSAU71aFEMqNyy3NTb5kIrxpetjvJSTuJe+P2xt1KT99ZnJkZKl+Q7loDbuB6Gd6n2Vt+DVnyzHlEWOLWyw3Ru2W3Tx11VEq4XLR/O3E+URtjPhy3lEuoq4fzWrouA7RgSKOM1hu+ssHq0YjWBxXLnGViJgcjvyp2FnPWDOSoliAz9F10mB4uvC/5dC+QJRtv9CW9U8EWCxO8E4UmrtS/HH75XIo61CfOBtcNjO7MDLdr6rdG+QVupWvzOoTYz31mJu0thTWjtmH5WkVvemPTj5uI/nrCq5f+m41GdtB3/VhA0b2T5UvxFH7QmNPZhyhjJUL2nwYW19H6WtUSjJPcw0rofSG+LEzIEpFqzOw1Q+oGQKP+C8cd3qZPoaHDKxyOvrf9iIXOl8vVZee5h4phrrLpYyn8jBTy86GmWFGlppzSVJvbfepKWGzFGbFzeIOh9kri7bFxgL6FMSyEp0+x4qCxCEdjrkwCUAtgjVmHcC9eXUmrXD3ZklCqpVrE24VfAbrK0Zk5jhbbp84W4id5uEtUvyz2l2LfFdTkrFLu8T/zNWaE2tzY5X4p9EoFOP3pxSv6Z85GO48I6q0j8/dWvvkUvrToa4ruXW4nTL5SR3ceKUMr3tEZdu5apUDbU54dNm6Qq/x3DF+805ZEe3bA2WI8vscln9JFr9bE9X9Ifw03HKb9hZ/20pGAxMQhu+0UiMQht/o1RUEVmf3OuQEWEkxMd/hl75ayTpPFiT1F5oWgdNWWpr9XjYqgny5+UNoBxysDS1AUFbB8wjJXuiaDQUwdaCB78J/ZCvnyCF45Sck1xeOOM8gBWn68tjnWr53EF9+ZZ7+evSp7XOlb5GZmFteQXN1Nhph+Ony/h1YDR8IwU/jBfCjz3HFD1rpV6jxCECSAgAKAAh02n8OJgJWN4Sw4Gc4UZ6eoMDAoJ8PyfiOFmo4ir+TkKBAV6AovxB54K4P8PzjS6h0LoqbBEC6VExLN5vdJOvdtR1JWFA2VM6fIW7aDzZjZmgaJ0rlq2SsNGV6aNQtOdFSxDJTuRx09zodtTH8KhtdsirJW51GaC66oS5jmLChT6V0BGIf2M14ilS5qNbjmYBD26RBnFZT/7vxnsmHxwXZuMsZTVFqpPZG3ZACDp+5jf2U9PCpxKrfJtyWzG/IsJYsIVl2pXr6KODlI0f/yn8fkBVvlujvMKwxav/Pd1uSqJDIxtGloSfFJ8JcZBfnM2vyWO7jSrEl1Qi1iNaI9Y33aPSSaajVlhF6BwCAxAIy2ePQrSBiuBfrmmdx7gBf3xSXDxyVYTS9dUK6N7pWtHzL61l04Gy72MyScIU9Aot14SzNzoGNJUyll4w8222IEv0lQfThmU4Jt3OFgbbZp0SNQgGR/BuE2LHIkl3jzuUwIDv7K69W7+ed6Thu+rePJTojff2XKPp3ToQOBOAiLs2Hvn8fEvbZO0Y8EsYf5FRPAPAHpYOi3Bym8x+B7zv7MJsf3HbW52mfwN2LRgHZi1kmWSm8ZgRglkLgXSRLyxtC4bVrU80EZJG1fGLXEqUaCBUjo8K1smVud1m8iEzuRLArSkDGvHbtA6zksfSrPx6ezdkUu0VdQ3gEvMfJ6PnOEbuuFei0H8PbjX8FLD+XphLrHjmi490i
*/