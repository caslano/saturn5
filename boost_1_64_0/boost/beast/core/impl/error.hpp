//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_ERROR_HPP
#define BOOST_BEAST_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // beast
} // boost

#endif

/* error.hpp
j7z8zFFrj8lY0mNw0o/jdWc6/vPsGN3PROw6O0Y5u0+NqQP5KtifjfNwbRavznDa3Iyhzc3htLUppa1NDW1tzqatzU20tWmhrc09wCnAh2njsQxYDFxNG491tPEwbSjLgdsApwN3BlYADwQeAfTzLMNGnmV4MdAPbAHWAp9h+ks8I7ENeDTwI+CxwM945uH3POtwHc9KjIfcpwK7A+cBNwKeDswBngnsBzwHOJBnH44Gngc8BHgBcCrwQuBRwIuADcCL1RlzHNtwzFPhWIvMpa1QP56BtxnPWuvPM93ygJmMqzVmlpfH8qxrL0NpE7IVzwIcRrpG9RuFeiedma+edNuwnguA44A7ACcCdwQeDNyJ9b4z8FTgrsAmYCHwduDuwHuBo4GPAccAXwbuAVwO3BPINSn2xSiDfFjXpLLIf09gBm2PEIxNgAhic7QNbY524P3iKNeWrn8iUZ3bNs/l7Dae2+Zcb1pv57VZz2rL3rXj57Wtr7PauuKctrW7dfystn/SOW1/9oy2jq5x/RPPZ1uK96QNwXgSa0kI456MrRPFrtgVu2JX7IpdsSt2xa7YFbv++usvWv/HElzn1//7Yv1/O3PO9TBzjkamrOvhAbihurTeXC6T9O2RXlxiTa8FWzXVyCA2Am/3M9SceJmHE/ecE9/FQNrGoKeNwIQJvqoarMewJPBSZwR9WT+KEh4zQxQ+1INz27ke3Zxox+ekNXOc2jnLo2Sut3TYZTdt6/1+fOuZO53XdtPl9+rmUHVznLq57a6bk+YcH+tA6gYr3PY5vps4p3Ur57BuAw7m/sKRwDuBuwAXA7HOCnth2KB+kKizg+aclH0u6gsEzjmpOSaLXbPMJU3k/NFaoHVeaJHM/3Dup1DmeBy2xzKHQ3tjIOdl1iBY7YY5x+KcW6F9sMyhqLmSYs38COc/ZO5DY+Mr8xYFH8TmJGJX7IpdsSt2xa7YFbtiV+z6r19/1fd/dWnnv//N7/eXLd/vy/j9fjQwEzgDeHFffGfX06bNfl48/djyrCWepaRsU+vtZ4uNlHixZ5jHYzkTlGca0dZxO8kzxTPUk0B7/2A5Wfh3SLqp29vB6ecwvvClhfwH5kdhhwoebecqjVVnhoIH2s/t2BD4Rt5qsMMfMJ0LVnNeoxIhB+UZM131Av+12jOoSFOozqE7QOIb0R5T7ZegjanKz3gwf7wlf0ntdGAWbUqD+Tc38C2LEDrX2F9fSz72t+STuOIjxdUuNB1YKOmZtMcP5u8NmyFvtP4c9w6vD+jGZhdstyUvUvcgI/NNVucIQx7W2y4z3ettBB1obo2wEcKWCHebZ0K61Zsck+FSb2yb1wpNDuuNZajz/wJtsiSKc9hczv6y8dwcZ7cP741wJ3hudeNZXKlbzjCJ4uwOq/10Hm3dr+WzrkR4wDTKmuX2rNqS6jJz35FTR8rHJ+nOhY3dcNW+q+TeRq77UvZRNJlGDu3RMyV+otEHnG6LsLMx0tgCZ7hcHwfe4tG/4qXo1ie5f/JWyVOTB8r/w3CYS1yKdzNrO3RtxxnAg/m8DIkH+dsOHObKuSzBMvbMiN7G3a0tq/0JbKMTZ7m30VWsg9PYRk9E6IHyWt3roBxGxdazHFXf+YHkr4ednoe6D5aRwTlWsbeWNnrdnzh/0ZRhLWUYNtjuP7k4iX6X2I7uRLjSPGNutpsMkMBxzqlTHvBO2macppOt2lLuHOmjaOvOtoRixIdgoL8k3YWwkE8y9kCYjDdoK7SfL6DntYlsP73QYrJSNkhK2KhbcvLAhJSU7knJU5KH4kigdDQxbR/4lpSdzT6Q/CCebnil7UTZD1K/trZjZNn6QMrFtrNitmo7Nt/O+dw=
*/