// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_template_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef ::boost::parameter::template_keyword<K,T> type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = ::boost::parameter::template_keyword<K,T>;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_template_keyword_arg.hpp
l3GdncR+VsC9h0vM+Jskft3JD7uJO5mRfZydatq97qX1jC9bpEx3B6YHanrHMHOG4EbxXxdYGEixfPRXmP61WPK7Sq77Nsoqeao+G/bPMA8cksmt+Ole0fC5gOY5YZvklUE9JOp10K4cN2xoTRI5LCX+r+J2dSBCl4q2pZlSjglGp88Jyx17F+z1pfztG7l6Q7Re5ZzQ/emmse+VdmAfbzf3TzdaLuz3raFt8w8pz0x7OP0GaWmf4fYT91MJKzB6rrfuFfc9XxT/sm6vwJXEv0r7lvxy9i2p3n7D3I/0He5coLYTs7fc7TcizhrVNq/u1L3Z/+zZay71ninubnvAXWRPneDu1U3mPbfUyDTiuWCN1CPyo1PqBq+HbXDrfV/kfuWccUVTtPuJPhfXjO0TJU6JOds2S+wNzHnK996vemN0bH5T7NV8+yryN/d460ZuXxVOO03iJpv2WiThL/Xri0grek7cyNR9xpQwE2yf/ik6vt7/ol/ElGeahGlkxv6lYm/ODE9Q5FOIfGaI2wjbfWYeP87ZWa9qmMy1fCPhvrE8upJMX7xErvs00698KmGfoE6nmGeelhLmYnqx3l49SSaNHPE/mvDY3fDIvUTKOoyyBsXtcytd61rLqufSuufLbpb8q6Jj6VjzfLVN3GrYXn0yGs3Ia6iTvspmKHF+lDg/0guoDhVvfll6jrA+O7jyK87JHqsV4TmfebyktZrelz2QETJZKzKZThtMjdaF5SnbxRI/Qco2hPwuE3uhXSZOXq6R6eFO+uQXreslwF/niF9TmbNbgNB6Ngzr5biiS1IAnSPVQnN2ibh3x4TmeK7oY/RyaLxCjYdfDcetN/Z8N3wNM7+n4UsbhnWvTNuZFBen09Sh+esi/LZhQvPX0/4VS+/KYfe7emHmEf49zY8090XoKNE80xqF5yOvmJQUDMXbQZwU3LWcs8Jx9Lxhnvsw+p1peQX7XXOWs6ffpb/QftfV6RHdlzbGfarRIxHd1sy3qoh933mYBEwupjN5DFsRrdNhDEqDwho6rOjnLNM+R0m8c3nCjvPr+zRd993ajtoPbOYKJFwH3z6PNKL7PPPe4dfHaXiPrim9DFUW4r13r5Sw1SXtfelGVxLjjlu20YQhNY9OtZHjxuW6/cZl4t8dGTQPfU9xvik3Yf+X03aqDEzi8VPcM3EbgJlRy3UPt5/6Gu/FJuH58faOZqE4/vTOz5l+da7k2UruwyHE2YS5wY0X5M9QO8d9IybUXk+V/KLzHJqpeQYaUqakYJMkO95z/5jnwrGS5xnUSdT8r8pppvjXlDK9Sp5DMimTN10tUwvcB2FCZeq73/n8FL89/lHPI/W9c4xR7SvqnjHtxjt3tqOpnounc+Y9MW2RS6nnnsgdl+V8XB/Py3X0O4tfuydu9PvJpPHe58cvxb8TLcb2bfMa3/tubp6JAysdv1q0t4D5tv2gz5xMXKTsyvF8J2WMeKZKU90IwzE2Jltl035lhGwmjDXSscolH+JHv79FyKeL+A9ldPOXj8b3nbu4RPyS1U4qjp2r0j5azhJ/6JDIa7yR15EqryGtJD57E0M8BzYm7CqPvJj5iZiPqq/9yHMS5hj7EUryJi2xvh3wkx1paX9oZFcwVlYleOYvqj6AOzs6x5ECWnFNv7FT3DNCOj7DaVHabGuzyUPdo9deZGkeEjfJE7fY2mDihtwr9g5MeFOXzUL6FU1dJkt5q5p3v/piv4iRoqa5hlri9hNX0NB3/ren+NfX8kTNW2k+GyRMA6QeMO3m3+IW0k3cWFpKrlx/Y5Xla1LuDKmlVfz1Gqa2bausJX7UnNVwJ77Rx9pQ/J+xMunHLyDnKaQjZTZxA0Y=
*/