#ifndef BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <istream> // wistream
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

class binary_wiarchive :
    public binary_iarchive_impl<
        binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
    >
{
public:
    binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(is, flags)
    {}
    binary_wiarchive(std::wstreambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(bsb, flags)
    {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_wiarchive)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

/* binary_wiarchive.hpp
NqToZ6QF8w2PhXcpQG9Ujb+JE/UvDGZh2g9fc60h0b0DCEL8ZLBZ0Ro8CQPPbnhT8GwV9sVAvczt0O+ecAdLc81wg6PJfmAbjav6QUEzEL22xzMYy1zjJj0gxEPHvU4iukj82pbMaTAfJ8AR6rPmU6GLkKVX289n65n9DKlfh/kuGuYUCRv8uBL0XYD2arfCkPyyxrzPzso+QwOf7XE6VMWL11iksCyon6+225k31HarNBvgKPUS/sNe28Al1UZ7AcWplFOVgmx72RsyFRQaA+PNEHuoRgdkvwV4vx3eJ/1+5Vhwvw1TVT2ONP/lst+avRO81CY5zEASdwDE3HN1FH7ZdETtuUI99Q1SDh87Cbk+1VIyimTgvYA3XRfadKbVE/UHdfgvYkMH8M/4gXk0ZwVDf+1rqaX2POrPWLJJpVXcMZtWocNtd4ezx6oGhmjaSyS+GZhxiEilB9/wb2kBqvg/CBNN+5/ZNvrPlvz7F9jYP1nyk4tt7J8s+a+8bmP/ZMlvt9FG/3tHMH9HUfn8bZb8J9+3sX+y5De0aX+GJX/OBpvxW/Lvz7MZvyU/uchm/Jb8Y+/ZjN+S/9BrNuPfHsw/Pd9m/Jb8PMgWLoBf5zvpb1IOUco5XkxR0hd4Jej7XpBff0SYbqA4/9/lXP/FZLh7oyH1YkBvkUR8E6EUvTXID3oArOinYVAEFHVIID4pS6b7TRliOxGlDeYLbXZKnn/DVssdcOlzIBzQr/yHFV1UX9Bkiw1EZ8wCj7VQ37dU3irPvCCqW6t2iCwANCXV/NU6O9pDLhLFe0NZgxWY1+vxq4JI5zVe3BeDAyJjJ2XOde885ZOHkqDXtyqa4j25DgQJyJ4MvIl6kM7AWWkAfK6QDCL9QWq3kbxokjuwnERhfMe9KnTiU+eE+3MDhOag6CJ5zfi2UOamwrNA/N+co8yiH/8tRPblQxnU5/h324yHUDc7XsN2w13xzCuyp6BQI17Phk9j3QGRl07CVIqe6P79sgIaR9qtQIQC6dhUoGeqHqzfWTWNVdGGr5fL4D5IRGGhEu/Iaoad8u3nTFwgf4DK7wscQeS/qmlURexytiuKfEXsinyY56Can+ksKpWwv+c3USSw2E+uLP2+EEO/y5z/rYp2DMsucmbVzD4V5kOAI0+83vJZZVjLGpUZhanxDnyCKXbt1VpRur2dqj17+/X70bQYcbpJxaUqFo8XIV1bQlN3J441mQKNq4WJfnAnJppJkHRFCeqgGLMfqCjZN5rZV6rs1ZxdU7KvMLOvUtlvIZv876sV3oisNJU1vQK1W1dKRpolu6rskUSpZnd2+JKpc+PbUx/Gt6KmxjfljeGrR6XHU+nCHUbpjQlhXLo9Sv+mXsJ+Br9QSp56drP5ToRFy2QFAv217wwUw9EjG66Wh+WnSWfvb5aH5Y2LgRxedRqygBYvymFLcPLj79RVbM8q8oBJkK8wBvwUWEVJT+HYKl7vimkmZ6AbiJqbMkBILg+KcvDCRCcyiXqT944E0s+ANMD6Xozn4grmc3F1fi4+APiKBL8fImD/3UDMeJ7l3qSxPWw4h1cIY/CSaN9BgNcl8HkEnkr8T6G0v6Ytt18ZADUJYAYB1APAJwrgTQHI8OT2jgd2h8Gw+PF63GTIE14QRHuc/Y8U/pSEluaXJ/txuYNeL6Q7aDLuoPX6kEWmnG/hbEPOt3h2GaZ8+uxycr6Pdb6s+i0TnN7xKX6BvedfpsJyAfTiLRuN97Z3lqj3gglPFod4/zPgK4014HfvC/X+Z9Z/Z4GCrx+q/m0bzPdOA358qPpfM+ATZhnwBU+EgPeZ9Zv9qWdff6pCmz2khDgYhX8HFfNwch5fdYRQ4Ck=
*/