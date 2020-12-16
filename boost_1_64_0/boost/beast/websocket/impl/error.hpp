//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::websocket::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::websocket::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace websocket {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // websocket
} // beast
} // boost

#endif

/* error.hpp
HkzC3yv+tSrI19H3JfXWzInNEb9sK556WROfo/DPwU7CzsQGyaxZMTueq7LXJZBXlO10U/6Do8o/JaL8I8uIBIo5H9skFBf2dsooZrWWkWMJuZaRhos3bdS+4i5k5UVNyYtxTaSczJx/R/GfyWqx3bXs7Diaueb1OeLfMDxvTb+jn/jl0bPwuebvj83/fP5yH6H8lbzspXm5dveK9f1O8vINOy/Thg08vAr1HPmIel5zjdxTRP5pXiEbWc8Dayqt5zQWEfWc8JH1PGdN5fU8Q/xrhcm71/O4NZXX85+rsRzc6nk3q0FZX1fn/O8nXW2UN1M2mySNi8sKZWq29F+0jxtdLirb1YrVcnlT3Gf5Tvf57Xc0bnlFm3UBr4nMSVpedhz7qj8z+2t1L6H2DehXF9vllWLkO1qx2md5Wdzn+lb4ghKmlZSxdM3MM/eCyJzvO8cX0DUCdjztHPvKDeG34p9iNef+4nRvYey5Uld8XWnlD/C1iVgfQHxmfUCSryzPtiZK36aI7qdcT4B1TB8y2zzzMyTeBr7XrM4V8qEpdaUG0ufp+9dQ68kHzvVkQEP5rT4NN0n5+6Q+xPjsd6OUo1xrEkq/XJNykmsJXAvKNfJe5dpxrZXEZedtQ+4zvH5pWMh9c437DpvXT/W7zaNX33z5zu6n2tn5aed5dPd564WB0PX14+8P1jvxp6tb3vBcy3bnD+3nNp9dffPxSYWh60WlP8y6PXP1VzViJh+ftHlAkfv6Ced1Eu7z687rJ9zXbTivz3BbN7Dz6xtkf5Ffx7I6bqctl7njTrq+fojORw6FreAI2A+mwOFwPBwNJ8DD4Tu6v+pduAS+B0+G7+t+qw/gWvghvFjnue+EE+EjcBJ8Ek6Gz+g+pOfgFPgenA5/hdmwto8ygDFwJuwKc+FgmA/HwNlwIiyAhbAIngDnwlL4JjwXHg2vgMfArXAx//zkwVLYFp4ED4Cnwf6wFCbDlXAMPBvmwlVwDlwNl8E18HR4AVwD18M74YXwbngRfA1ugJ/BS+FP8DLYgOfgatgDXgt7wethf3gDHAxvgunwVngsvBMug3fDk+E98Cp4P3wYboM/w4dhE+r1Y7ApfBwmwmfgAfAFeCR8GZ4AX4M3wTfhR/AknZdOt+w+rvRXpP7sBg/TBrVJKP9gc3gAbAEnwniYBhPgbLiP7odrCU+CreApsLX5He3PwfMdfqcXcvGwD+wOD4Bj4YFwHEyGmbAfnAsP0vrZHy5Xf/0d+jLu95Oo99NR76eT3k9nvZ8uej9Jej9d9X666f1019/ZaN590oeQ34mV+XeMrvPoCr+CveDX8CD4DZwMv4fz4A+a/h/hCvgzPBv+Bq+Efjolb8AA/ArWgPVCfUHYFu4GJ0I/nAHrwUtgQ3g33B1mhc3L33AJ8+3YyubndW5e5+Wrf05+Z+fj/9RcfNh8fCVz8VWehz8Mm/EPmodfHjkXHz0PXy1z8P1d5uFvu4Y5eGztTczBY4dv8ubbPeMZz3jGM57xzP/H7Ir5/4zCKWlzCqaHVgD86fn/PvGW0Vdbtq5A93kegp0d2otvz/8fMvbgtIy8tDmZBdnT51thOsqMGWFnaan8/jq/Z/vrfDEyjSxbpo3EkVe2jy97htFz2v59xb/THiF/1j1kzlf9pe3fw+wDmxRT9X2bZbq9sjTHcW2w0RObdBr9MWnjuqTN7OEkPVzT9HBGWWfVu2xOVB1z1L77kWH77mcSX35YfmpmhulhZSZT7jPWsmX7OeY1+mP17+Ca11lGJhkZOw7up0y1afIzP6LMVEaiidzfjVzk/u7o8tH9tUtErqcJmxQVln0Cf6jsyspJ8kiuDXYoz5SK5SnXU40=
*/