//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_AS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_AS_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_as
{
    invoked_as(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref as function converts its argument to type \c T (similar to
/// reinterpret_cast<T>).
///
/// \see \ref convert "convert<T>"
template<class T>
struct as
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_as<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_as<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_AS_HPP

/* as.hpp
/+m2nObXdaf48fJnM1zqFOX3hXacbH6NL2W46Fh4ZlDHl7Mc+o/NoCrvhRwOb9jpOv5NHs7TyCa+WufF60T3bs7y1ns8ialuiXnZvqm/Xzn+/lmJ6z6QwVHzMRRJ5VP8psfhNcc8ede/3ZbT/LqGfSpa5vcDbiVPH+YbbTk2atP8un4cc7P1m/lJG042P/ydx2V/rrzm5+/leJ9ynI8RH94RYZKBchr3z3LSow5Un8ztHmdP1q6S38R4Vo7J79txsv0yf0eGm30m+Nd2nGx+/f/McF1AoXb175ijtifjnTk8w9FzwfgcksFRYnTZO8etK+ao/Wq8tTjLwX4lj/oDpK7R0Rc6rhUemOXoKRZmjfiCD0Y83oBtbZdKdzGtkbXW93q88dQwxb9/2Me4nw4Y8/ZN8KNPAc6TBp1LnXJ4gKHmqgcP8vKl8l47J2Uc/anPIS6L7Pgk5zt+fhCe2t6UxBq/zOVnnmE2fnUwnuYr850V2l4OkR6MbWnusAzu4iGdfxyew2GDA3LfH5wvd0TMy46rvUdlONQ95HStijhqP5rPsRFH7Uf15O4hJ7afrnvEeNY2Zu4VciLbQDg+nj8WzXo+U0cZ7fsZT5/tvjXeea9O8zYwh4R6a6o5PDIjkuIBuv+uZA4PVxs835vLcpyZ6fmEbTmlYTZeaUzbnkeXqO6a6w7KG03PmNdnYYUsn9kbDO9ZWEcO59JWnsopPNTnBP5LOR+KOPiG9Kgs75lKwIl9l+4V7Fjr6QQrCP55wnMRNgHonyU7c7yH7w9sW9dr/HpcGvrGmWe1fF/fOdvO5AcYtm23x5pPSXyRwXHCRQLoPSyhMVOBcqnMlZ4dc5sTVZlvMrXVcaaRyw3XZpLnxhyskbUQkdvzBBd9dffWFJMaU12N92K8uYLixzYxnkwPjjEv4JmPkTV85QR+YuGK4HrrlSN3EJjY8GzKYfbL/rFdpe5zN5yTd45sox2PStlHpLpf5WBcnnlUplnaknez+bzuYHwEhsJNes+xCwfht07M99ayO9pxEQjwuKzntuNhL/ZxalX2gbz+IFxpH4G/k3F7Pit1bFNgkdfTLp3zH+w+2unHsLMnLjVwUZ4xDkjz91aqLBYiTuD1kYWemZjhZca6eoYjOWlsdbLPiWci3lnPAQ87jfaEJgEe7OtMXB7zAUf3doqeFwOcES+/LibgyR7PCd2/Tp+YzeyzbIp4aC/bDHW8vNHDNO8J8SPft3i0tdXhxR96uN6v84edy1LcHsxPxVglYiHhgHf+3smOE/rejl/ZvJ1412i83v9wdw+iXSMF6xlvJ3q4wN55yr++q8OHy2uCxicSf97scyIBeLo3d2vMy+pxcfMynzMZ5yV99QeblwNXm1MEW7ksxDoVm39AhK1RrCjy3e3KO0V8ufRP84Wu8kCrh7x3WRYE53qpQid6a4QPctiEL78hGX/PcPhkru509Hi4Q/33Xk+yuL54oedBbHFYEiiutGu7w5tv4Vul939TpM/hzRclGGNonuEjMjvX4mJOuuc6ibFUt5GMPisqnBdziF0sS2L4C3wObwE6y/DXoYRjD7tnz38n2SELo++tZTlQ1EZLDt/vy0rnaS9o4WeVzt58Bu+ml07p1DN3Zl5tsW2ccrpjxzn++cq116SYfZ/mHHe98Bx7nQYzQTpH9OF5/nX3doa2w1wZ4rxZQTO8PrXlhcfVKl5zdWXhmJOvytwdyLKexXFGrFaWvfcvXRnEEsE7lva6voPMzd4+4v6rIjxtHg912cWBfcu84ur2PP8MgIXXCo94gp9k49xSb68GBuDj1MXDOgIsuXiPtoO5iGKtN4NLq9cVPbz/OsVbb/A23+8SnM/1Mc4=
*/