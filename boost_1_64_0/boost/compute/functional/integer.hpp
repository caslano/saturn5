//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP
#define BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs_diff, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(add_sat, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(hadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(rhadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(max, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(min, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

/* integer.hpp
9jT14uhJflsgxxqT0hzKN+9G5x8/jEsFzZhb+/QhXFdoHpfMpaUenaG2+b4Q9NbZaynOshcp3iumMiZ4VDgR7y6Zn74LV0vnR7IpfJk4nUqUxk5oOdj/uMW1HOxFv9d3U7PPGHxKNAz9Qb+co2Z4unHkHLFLZdJcNFAjcBrpfNV43o7y5AbCPu5XkumEWCjL2Jcx+WkBYV7tE0N4rlnB2xqaHtWAeEFW8j3m0Rzllm3d+ap8ZehR75/IMf41/4jnB6lqY33wRcULNHKW7JP14xZf0ENfSnKLNcp7YS7nuejrKd6ALG7WQ/VzoU+wbOku0UUlYsGv4NyGQys3yOF5NLbRoVjAXWewoU+HcZzfBJf3vJrHrvm83tmhOllOR1ZNzhnnq8Vc8qHG2ukCwKt609DprXmWLxrS2mEuOkX6FLUuKHDyEpM2w8E3uMylyXTCxT5i36EfaDwEKMPvf6Zx52HD+OZvNO5enREx3C6DsuHtMLTn7/BbNyZ9K6BBC46TtitkhFw0kf725ZE+VhkYO1dkbMnXC3YQpwf9hPnxSvgd39OgHVfp+9v4/UUkh8tMHOwhaU64qTS3TsOBmmlO7kFs/UFxk2MLOvFCqnxq1MAO+5JKDwKqYs8J/US92g7f65/Fd+VX1+Lv/iGt6q2xHG1yYS5XEbZtXMRVLhfVU3BkX/OYkukgwjfbyflFFB5kgmOu1xQe9B3HtP2jKgO3NReF63xRlZbficrmMP7qAqd05B7n7FU0JhQB9+WfUBbWOV6IkM6XJWctX+2gO3k8X9znxacjBfTsVS8GjO4LzkzT3xnv9IWzuavj9+HC1jTmu/mzE5Y4zbBxQxI8NmeYtz2UR6NNtN8m9jOOhi2j6pJFJmOvvB0c6BfonncAg27AGHs/MN5uoXQxRkQZc8o4eqVc+kcsGC4l2BA2zI7Fec+V9bDlFC4NjMN3orwVVC7QMsL5PuAlS5zjV7fIcp30Bp48W07zdMzXNEfpgtm7VJzJk+PH78lDgdfUrZbGKQOeG+1vKWHlsyPwu9x19KRIn/NvJTiUB+qQSMPGS23sMieOfMlttvv+ITzKDzIyLC3KU7b/1oeZR2cnrdb4RDjTOA09+vGY48vE8QMT6cj6zybS8GU5jXvp76s4U5P3oCLTMa2TwSoW+vT45ITPktdes4fzKXuWn/xwrhpL24LrS6zX5xFu1iURrmOONo7XCJ8q13Pe6TtbRyy6OwEjCc+m4YuN785RV/ojb7WA0QUtmngIQ12mA0Ymx2oH92exTjsJvFQ7G2QMVA949ihv6IK7BY4P6UkJ0ecV2EKcP73Lssrr8Tvz96IzWOz5onMsQODFAjUwTVZnEBcav60eDeA1vPgeykvXMbvrnWwaenqCObZO2H+bDBzc0+R16T0C5g5SfYVXIOv3qvDjIyp0N+O1ZeAIra3mgTmPY4bINpD2osdUSG8xL857nLEc/dQNWC+Z72zH4+FlWsr3YqE9Vh12YzmXPdB/C+G/iQ87AxinBZ/sZ1XYOJ1En6D3Jdh2KdT3trXtmwONe9ue18wG50jIYqwajveyR/s23l3iymOgst/R/glc+vDnHmcvAvN+gcbDz3n8Brw9OTrWalfXG7yCx/jdT3FcMuAcJDmkZkRb5Oe8qOeU8/QRKBvYYe+pBXx6WhWF02glOEqvG5yLwWXdPh7KcY+b3+iIf4rZ3UmDTbd/e8khXURGKTV/ObKIybJZG1W88gooXYHntUL2YV8e9wouZLLO31fpRhxtT5CQLHG6eQJfZ/uBzng97sNUULnYB8xgtsw7XwC+SnFN/YMEXObaRzzuEehV/E7HVdr5hP+umontleangJtmZE7ti8w=
*/