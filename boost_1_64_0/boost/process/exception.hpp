// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXCEPTION_HPP_
#define BOOST_PROCESS_EXCEPTION_HPP_

#include <system_error>

namespace boost
{
namespace process
{
///The exception usually thrown by boost.process.
/** It merely inherits [std::system_error](http://en.cppreference.com/w/cpp/error/system_error)
 * but can then be distinguished in the catch-block from other system errors.
 *
 */
struct process_error : std::system_error
{
    using std::system_error::system_error;
};

}
}



#endif /* BOOST_PROCESS_EXCEPTION_HPP_ */

/* exception.hpp
7xr3uKSMpOyh9vT+eh/UY8yyriVdF6NHWeMSbceTHmkuV5JneW35B0ragJyU1EF6waz5D9LLJbuiLT1ZL5ceY5Y12FouPcoaN8S2XHWnG+oujyMnIzM9Oz0teYi1zCkyLik1I83Kf53efzON4tIGc4Rb41Jt49KShifbx6V51n84e+5IaV/NYyb9D+NSk9Ns2/R693JkjUobaE6T6Z5XRmqKMce0QbmDM5OG2OaX5d5nkkbmZqRkJKdy5GaZdZhtjKNBTBpE5Q+26nafr9RTbu7glMwsW/u/X6dnpKemDBxlpb/vSc/JzODwNef9gU7XLStVYbUPB2qN4/jPqL3ffajHJ2Ubx4FVRx/Vnm5oelZ2rXL/UXt88vCklFR7/R+sPT4lQ1llH9LjaG7TM5NzB9IypQxMSjXHf+wZn5WVk5zJTpY8cFiWrexP9HjODO6RtrIP1x3H/pRqG/9prbrVk9vGH9Hj2S/IkJKtM5rz/syzbGlDUwYwOinNGne09jj2hgxz3DE9buSV3a6iOc1MGZhtzvNzc57Z7FnJg1j4WnV5XI/PyUpmA6ZmJ2VZy3ui9vpkcJBk29fnCz1eVpS2ODeLdtg2/ks9PjszJyubWcuuaBt/Uo/PyknJTh6Qy4tCctPTUq11PvWH8dZyf1Vn3FU9rHK/9ix3UmZ2SlKqbo+s8af1+LR0NqBuaLJs48+Y4/Wqye7LuVOP/6b2/peUkz00NzV5RHKqLc+3Og97SPoNVF36yFHSamfZjo/vdJ7c1CTqxUo/5TTSR5rHbphnnXU6rYuZ92udJr0xWxmndbqsnG17n7Gnu9trxun10uPMXpmtvG+tecsocx10et112NJI2rQ/tD+vuNOpWzmfm+mvmulyejWX6TUrXZ+3rXFbbePqnutf1+PokmTZ098wp6HjMNw6hraZ6bQXw+gA2uaz3T1Onw0yMulGmuPedI9j+w9JGjgqM5mTjjluR61xRp/bmu4t9zh2+MzkrBwWxLb/7TSXxZrSvg5v6/H6UDfT/6rTOQyTUlltT3nv6PSBqSnJadl6rK28XZ7xOayfra/xN51uNM6DZKQ1zbueaVIyhiZnWum7dfqgoRx9ScPNsvbodOkkDshMH2Yr6+96nGwQ23Lt1enWvhUY6orhnhEfYnvJc+lLCoqq5VlP8qy1PL7c5DTeoThR8sqzsIZKWkGu52XS0To9VadXF1fcZLzmgGJUrC4nQ8bxcoOyfB4SZbyXoDR/fFGpitXTnun7h/FF5Xr5jGdqZcv0xjO1CnJ5Kqe5LCP1PKdMLSmqsS1LoaRX508rKjQemVVeYYzTy9JtEONqvYfdGjdWpqv1Pi4Z52/UkYyr+74Fv9BGjNNvpqiZLsvsJ3VNTaekp9EspKcMlP4W6f5mXqMcKUa/Jz41dKzx/WP9vNAT8n/2FyKceIeIZdq8Hx3GV7p4j2nBZFZtKu+P78Moef5ec8Y7eL82b1I0nznW5JyR349h/Rw/md6r3ue2U3ad5+tT0w08i1/ntZ4XyHztz1v8RsZ3Nec7Q4ZH6mE+ozhnTi/1Lo8xq1Tmcr8t+X1l3jwLTZ4JGiY1Ms18j+djkme+8UUuedZfaWPO6SzLjdSjsz+PWw5w1fus/whcLdPepm5RTnm+X6ye3sXMxzF9oE9QoyCK8PIP9GHxdJ4wvhrV0DvPrHelGNuhqd4O+rlr+pn+5vNkZZ0qJU2vN884kzpiPN9rleE5dYbv18Nt9fBjdcavrjP8gQxb7+z4vs6wzzlrmD1C73vyrkn5l0w4tDdH8b+fZN8rrDCeQM5RPrWmsOKmcsoy3/FAuu2Z8d6SP1El8P/69jfKq+d9DNY+0IjxjNXDPEU=
*/