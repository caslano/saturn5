//
// detail/resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolve_op : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  resolve_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

/* resolve_op.hpp
AxkPdP+azDNXH4qb9KXWeSv0g3CTftBa20xPFTdpxClc2/xIwlr9kbjvijHuPOI97khaM+wzGyIfzS9363mO0f4A7eMq3P4XVFh6ILFvoP1s+r9U4d7L+DrtDfT/oML7XFLPhbpQb6M8dhPMj0CTU2WPg+rWzQJyeYz5Gek7W+36XLF/17730KNPWlLl1jUuEvtEIwFuHBsZb4q3ro/hbhSaKSLbNKqHyPIo21zQtGyj3ahbOEWZZkfVqck0kXvG7HPPVrlIPW2p0vX0YEQ95S+KPnP3pXrDo9qup5qIM3e9ZR0SrnY9kd4+czeguvkzd9nV9pm7zIXqDtBTO3MXzFR7H5rXtZpzj96ybiXp1nOPajdvT6928/Y51d77dBvOo47Ur+czS4HHUGZ73GUmU42CEtly5zhvrzUqvJOOYXpZZXK8hnbqCN4W/3aWLrJzra0Dn0U7977z/PbSmqoKSwZk/IMs/cZHYp/t5z4p/K6rMnk+16Lvb+1P+0Dsc/zR9c77LsQ/wU+5juEzjcj02nd24umakjK9z4PrxmtX6Dadbsx3y3HVLjku5t7zDisoA0qeeDeHHGO1ZY54KdcUX+Q5G+ppvPmU8lS2xH/M15R+QO5wWYT2m88+4uLm900o+v0mfeOrzeoGFH3wXNKvy20RfbZFf7BJ+kFwa2Pgd6Z9Fhrti7oRx36NU9AvpLFPG7fCPPd8DiSsSpx32vCVdAy899TSXW6yxj7heWtczpD+T/ia47K77afocZnxkR+jdBTCH0I7MvL+RvYf1wlPQb8T0T/sXhx5L6nuHw7VevQPpZVN9Q8Mk067z/DXCR879gx5t3uGo90MF1LhpFw9239EuFwrXBp1Ed79/7yIcPOscB1MnYRn+7fbOsOzrReyPa05D/3h+Zp/49s23Z5awo/mGPu32pbdg8QxNorvpnnwXa4H3+V78F1hFN+5x+MOS3QCOqn7OoD/REY3DYW8UufiHbm0w803JaJTI9+Qfoilh10h9rf9bSx+qSBvmLQTrD5/vdj3SZ9fbwhtATIv/sss+hnW/DfZ4iWkStRDdr97mdDu5/ggYanPQNxmGK4xmOt+FwvNq36bPxiO/LGH+S5IdfIh7yYRur9aYbMiwu4V2oj1RM75Lhe6F/yxxplt4t9O5nb1jvniRfB7c6XMl2nHiLuKc3TXvSL2mHdI6Ocgb6nN3jWi64H7elX/xPXNDvUqjj1GCP+1g+ksO6zXGLcCPcczygCPSD5u8XvsF2a/EnF3Bus9tErLJslih4PYz8LXekl7fWQxxr8Cjjdrmx//FP1+k35d8+t7ij5YaNJvaxF9tkX/cYvoS0z69YVfa7w01xPTe7d8DmCuHT4l9XME4+WN0MlUGz2hN1vtWyb9VWEzY2auY++t5kGuE7rGPPYVei7KvqxC0Uh7rhcaafPSZz1i9W1W+xb3PYrWdAcx+z1pYwWp7PdO4S4R3kXiuT/3d/XuO0Z6rXTfMfJ92i+nfdgqW7Z37hPLLdEF9hBMOrEIYTIa7P51JS/fjzEnJe0g2rETR+zxzjvjS1eWlnMfgkk/inab3uPufut8wgShudpYxn1eudZ3u1tj8x/E7nPEU1RzYTXPXrD/HSc03wcX+Tg2m/GcQbsdj/s+V3td40LxL8Ee4nhp56kYozYXs53Mimzn3vt93+iIuQcGoooWyo7mWF3T8NXnw8mue/GlTqjfj37DgOet6G6Xo1Ou67lUf3A7THviLnUPxsXCO1qzWltbX1pToC8n8NC5k4cYprORwvruK/YrjFQ5xeezdJw+6jhnWmFSrLsSeov9OyINrqW+eI+ktLLCyQPVQpeDcu9k6T8LxQ0vj8LVof8=
*/