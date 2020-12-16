// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>

namespace boost { namespace asio {

class io_context;
}}

namespace boost { namespace process { namespace detail {

struct async_tag {};

template<>
struct initializer_builder<async_tag>;

template<> struct initializer_tag<::boost::asio::io_context> { typedef async_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* async.hpp
nAcnwflwGlwAZ8JFcBVcDNfDB2EBfAhuhkvgJ/BR+AV8DB6GT8BTcCn8ES6DLif3cBgJV8BouBJWhYPg5XAVvBKuho1gFmwPh8BOMAf2gbkwBebBNLgO3glfgJPhWjgDboBLlT3bM/AluB5uglvgZvgJ3AKPwq3Q5WIswzC4HcbCHTABvglrwLdgXfg2vBG+A++Ae2AG3Kvszj6EE+BBuAF+BnfAL+AueAJ+BE/Cz+ApeAqehmfhIViX+e4wbAq/gi3gP2FL+DXsCL+F3eARmAS/g2nwGBwDv4cT4Bl4L/wJLoRn4UPwZ7ha2atthQ64HTrhXuiCX0A3/CcMhcdgGPwJRkAX13kkLAWjYVlYAl4MY+ClMBb+DcbDm2FZ2AWWg6mwPBwIK8JMWBlOgFXhdFgDLoKXQUPZdZWADWApeCWsDhvC2rARbAmvgz3g9XA0bArnwhvhU7AVXA1vgfmwLdwD28OjsCOMYH67DV4MO8O2sCvsAbvDTNgDToQ94VzYCz4Be8N18A74OkyEH8I+8As4AH4PB0IjjPkCloIZsCIcAmvCbHglzIVNYB5sDYfB7nAE7AdHwSFwLBwL74WT4XQ4Dd4HH4J14Up4OVwNZ8INcBZ8Cc6Gm+E8+CpcCN+Ci+Dn8AH4JVwMXcreqwR8BMbBx2BluAxeCpfDxnAFbAafgh3gSngrfBbeAVfBZLgGpsJ1MB2+AIfDDfBe+CKcBzfChXATfAy+DJ+CW+BauBW+BF+B2+A2+BZ8Fe6F2+Gn8DV4Er4Oz8I3YHgE1z+Mg2/CivAfsCZ8C0Z5fnmtWPcql3EZoTOhDHHDYQHyBXAtYQfhM8JPhHrEl8HwtPbqoC3MH2oL8wfbwVhtYG5q6/hL2MHwg+V3sYXZ3dYRtIf5g+1hfk9bmP3aHob41UH7l7/i5ibc8cfp///tb/9XUHrt9bzXc/GeOmOovBDJobpav71X4nzKaLTcojevfdH5tgLIAm0FkJ1nK4DM3lYAeaCtgJa7A/XxSu5R5VhlIf4yLLJQ0xZAy8JMuwItixBZx9tvpEj/sSP9MjJb6xql1ykksUUereVksMhLKPltzdrRkuZaXlLkzTu075IorfbLSwWsL6jqCLWtA2nDkNnbGhTEGdoX/FSkIdtR7zOF4skYuE/ZGth/41/rsCIOyLt1I86ip0sRmdvO7oByL9zugLR26/lpPXPofm/8+57A9/gVVN2+lHosoiwP9RuMj1mMUU294z8nZX/q+coZZpwkpPOwPZYHsmmeEKNImwOlK7tVjjvDY7dmXhn2Zkj8rZ6XHU5+P1/v8q+bdcPnMubF/5lzU0ivP1fyDHVE8wRko7cXXWSqpBnlsdP75xM/RuKTPXZ6/ZrqOA9Jn+ynJ6obbeiZboQJhpP3E5WMN6FfX15IL5+V1zc9LVnbJ4yX4yR67PTy0la45iBp8JKJVW2/V/YNZwKeL347hPpSzrOewmvYpWUwIrQNwA2S5jGPjW5f69n2fip6ST3+Tsm+R+u1W0sZ880y1Jyl9J/y3jdP0gzyWOwAtH4s/zOJk1FUiRmjBrmuov96K3/9JXb2BUpHfJeU29Njo//Xeuq6kmbNef2g1vYRnaqNHYC2YWgn+edYxgUnjOx++5vKEr/FU9VVwejninbG+nXdck5CnO15evbr6gdL2hyPvuYC1hooLfFveoZ7PEZR+vwV9udD2+VcImW84AnUqa8nrqrEbQroC+qg+mInaeID43yu4tomqJmU8TBlWPqDZCqNvM8fImkypZ355bRuXutdd0nfpDtUX6nxe9bhHb9F6OLFrsVOv34KeZocb5gc71gpcz0p8ok+2UbvrueTjnLNJjObOI3rqYE=
*/