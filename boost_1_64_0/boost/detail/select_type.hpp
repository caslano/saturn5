// (C) Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for most recent version including documentation.

// Revision History
// 09 Feb 01  Applied John Maddock's Borland patch Moving <true>
//            specialization to unspecialized template (David Abrahams)
// 06 Feb 01  Created (David Abrahams)

#ifndef SELECT_TYPE_DWA20010206_HPP
# define SELECT_TYPE_DWA20010206_HPP

namespace boost { namespace detail {

  // Template class if_true -- select among 2 types based on a bool constant expression
  // Usage:
  //   typename if_true<(bool_const_expression)>::template then<true_type, false_type>::type

  // HP aCC cannot deal with missing names for template value parameters
  template <bool b> struct if_true
  {
      template <class T, class F>
      struct then { typedef T type; };
  };

  template <>
  struct if_true<false>
  {
      template <class T, class F>
      struct then { typedef F type; };
  };
}}
#endif // SELECT_TYPE_DWA20010206_HPP

/* select_type.hpp
R/DIo5Azj95WUfllM9X5i8ghxW20atCymhHyBY+mN6hjKhvD17lFpGRKliJTksS65L/3ggvN8lWV3s3p58J/4883Wg/ko93SHelKlJAAE6oWG+a581lildrcnwDGy/P0fWEZkSxSlhpPnEdh5ZMJG9beOEoWn4K2TLiiSlQ9xstVjEVYXe2YZxSqAh8hWMWK2D5JRtyhMlHq+wNBsIZGxxzq40BjHqdI01GIDCOVE4ZIW8gIU/8mqf5Nlu2PfKbqUDH3RUVxUnkMqpyNXBD9cIXkZZ+Db2xbkEdsv8wjUPis+z+9Rvd/OsKZfK2GE2nd9LMftEO+VsjJo6mBteFUvubjtGoA42FAidj+dB4euAfz/n1rg34Wf2MhRg3hqBlalN94hqIyOeoiLSrTWItRkltwuhaVZyxeqHELjsUoqsrMhe093Mc8n504XRAk/biQuno4n4UxZsppNvaL/XkNXVGvSIYFag1tntAuQypbfZ9VV5v1N5X9olrO5GlU8pEQK1zvCmthmdtYL0R5FUavrupunjwXzGzU2UauUGv5KVKJCIMvcwvVeE7VZ2bUMss1P7V5FERjzqM2/lrlvKGLS565R2EW6KOOL4bpSWyneanNqSKotdwj5nCAIUo5i9fOsK6RewCd6PVDy8QaGhbsf5jl0oM4A9zOuiypdPWRxll8Zhzhnw3ZZrvAHOVmDr4BGCSK5txTx0OslEbfQORN8xefujKRI50pNOLyQXJRx8nWaMnyjMh8kUwpB2KybJksyGTMyPz6Zzn1FXVSpfjJ+YjLcxx8rggOGT+GYEb2pYojUp2mjfx/miaPvW8YbWxcgYqJ0ekZO/0jnF5ZhlFacBXpJ6dDuznf9+XJ14H8g/Pj1qwrgA/L7XvjpL0Da8JCUR4uipPMc9GQSmOryC8LiCA6QbkjiUDA17qwLwY9F9oST/9oyVVWI3vruqCU/r8l9bICs7263lAw8u38+ld4uL25QWoPzD7Jqtu9Tp9JxcaxN+gaq6nNxKKvQkbjFOwnuQyxaBPJC1LIUa3ZOkf4XhoncSEVn7Lc/Pp9jEsh4CLiPMYanPC6px6uDHuDULWO+gD4M+fh2SBn1WU34qx6j4MP/ErOqoIb2TXAYVDosXbdzilqEy1RBud9xXqaufFSsZaVGFPcvJ5ieLYKLzbO5/AMWkjndaXFez4qRL4GIHw9WVda58q6EidCrsJpvMxj4HqXXIfTeGnGwDtVyfl4GpfG7sWjlEpFGbNTS3BBZsiRgvLNgaAMhh9CQcpEpMzDI4kyyOWF4IpLNE8HTG8rjeii73Nxh8lbnJhfljVjyGSx+wsZS0hoa0/Q72UrO4PbdUABHkyiULUTsAbzbOhWeUDPqPY4O8vYyZNqfmBW/ZUEAEuwb8+hU9VQKgrnPx+wiqoqilrL+spXd/l31G0mwo9JCVMwXZ5QtswLo/qvY4mpVeMW9uiYbZbGXNr9OPm4MydqKaREE2UiZpaADkVoRChQniGVPHxSycNDUEQUuu9EF05cxCwuYiYVMdtcxO1cxKcuSxEhKCKTtQbLOfkplLzMnDzMyZ/C98zx1otzbsfgh5EPiLnyJdns0lJKQfOMrHKxml0V9TfJMejBhWLOJ8zIvohBwiGGMAbzQqpRkbcKvyGPkYqjGdmfoziZdZzyOnCr7+H72e5Xb1whhdQvTFZC6pA45BXxovSutPShAcoO6WiAUuwLGFsr3Uqp28VKydhceXVVcdswL0tgaVvT8sBSd0ywHGdgmc7AAs7A/M7AfM7APE7A4oOAkNHWAjZAhnQMYIp167EBqfEboL6jUliVlh1TcFCx0XM4TiTq6H3u6DAQThNKEE9dbzhIRog=
*/