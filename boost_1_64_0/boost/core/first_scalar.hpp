/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_FIRST_SCALAR_HPP
#define BOOST_CORE_FIRST_SCALAR_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace detail {

template<class T>
struct make_scalar {
    typedef T type;
};

template<class T, std::size_t N>
struct make_scalar<T[N]> {
    typedef typename make_scalar<T>::type type;
};

} /* detail */

template<class T>
BOOST_CONSTEXPR inline T*
first_scalar(T* p) BOOST_NOEXCEPT
{
    return p;
}

template<class T, std::size_t N>
BOOST_CONSTEXPR inline typename detail::make_scalar<T>::type*
first_scalar(T (*p)[N]) BOOST_NOEXCEPT
{
    return boost::first_scalar(&(*p)[0]);
}

} /* boost */

#endif

/* first_scalar.hpp
VC2rdn/TuIDadvzbhRXd8+eZ+tFR/l3jv8O+195Xv2n0EVmD/glYBWvQGQT7L2AnLADnBRZ22ApNt57oDl+h+R1GdHcD7KOge6iia7ef6i+dxnr9fER07O4FGbp7yIhm1RaZ4ymNa61ZTo+Hmjae3W8Fze/p6r5JxOMZ2x42tPhygmLUXlwbk749AG3vAU32qL5RDOwBPLc3qaT3+Sg3fpADzzlnzA9WOIwUXk/HGBVxk1qo5IV93uOsFD77REDG/0QHDgGi5zbA10LPU0BzXbtj0MD/cnjqMpg/66O+VlFjML51+2YVIfTP0kzkk9K6NWTLGmjAVMMRStUXCNyvZcfpOzw7dm7AKZ2N63XmTfwagI8NjgcSzTsoFm9stE9gfEiYyZn4H3dXHh93UcVTERCPSmkptcU2hJIemJps0tCiommSltg2jU1LW42sye4mXXLssr9Nm6h4YhXvW0TFC8X7Fg9EPPHA+75vRfEEb/F685v3m/nOzPtld4t/+fkQkr7vmzczb95cb2bejzF/vpy3adqpieL70cYHhBidq5Au4+YyPiDCS1Qn4nHuZBg/DZRHXW4gR4lzf+oJgKusyUNRmffu4z2xxdy7IY3G0aPr+gaQbmNp33rhyprfSKcy4VjyFCrDOHGvIL7r2e6uYFoL0J7FtHWK1pAtUu2Dcg6K5XxOYi98AON/w/V5hNN8pVngPZOJTeKln+B2VyEe8N71S1EO3yk3MUcA4xWB6esvd+VrffLamtffpv2vFnj9Nfqr436lChhRXCqeYOmeEO+vDN9rU/j8mKrXeHmSGPvNI6iXWQzA2HeJSet+d+5aQ5+wvQjyfIOD6xW/iT/hYuU48JZ3d/3Nemw50sGi9YBQVkymbIMr9B1AHl+M/+mtLfH3OtQnfKw/y+jKjC5qvjZlWnVGqEuVNdrAO1FXakHUkL2XctXA3gvi/Hcd5ZPnMWbXwPA+LMP7YfzxsQ8RRvpYACshZvT1YYuZcfVGHqeKUXzKFa+SV/v8OAaCzXxU64nguBeZMnzc0O2auhXzQ3lOzrasN3H9sayfdtYLeSd+7WdMnta6k3LebDEaNeCbdUCnVjb5fIHoif7wzSSWnywa6jAT9wmz17Jjf4dhYv/BV3hOv0Ttq+tdFyu7oqJT75kP11aPFuf1b1A+VIShPbsGeg9l+8ndbE9Pk/HsOzKP6qzmvL0eXn292L5T+O4CvKbnwTj4vVR+mlphPPm+zEftbcfoH4o8uim4TnXxJnXqTu6UpfJmozhkXBZGXqjbT1PScd0amO/LlZlgXDkmjis/B/vVy1Fr87fEGJMhza+IbtYxjJq350GfHU3i6ETManT6G+Lljl/M6ycbUZUSRbzqwLHgt9CXAn5ed/ye+8tFqu81NA5Hwjj8HFFftznjg3sm/EfUJRcS59w/u/V11sV/05gxUhNbvEX75nhCU8Zg8vsXpzGGyPdyW0McDZXZ7Dz4H+ZDY8O11KKzHTx463Ii4P6dpJMIg/IH6+67QVp/DXcKYxPeuntlgOOaPcRgXDVj3t0Nnr7mvgfwRKXZSg7WOvcEDNb0Ju29AOc9iLSfwLLJcwLWW8C53vZMlvON/DkHyrbE8nC96jyvTfqKWlCG3yQR+8tSyosSzLF7mapj7fd0ZRsAJKHYzD03wtXaRfFgX1mRpKNpHW1pJdPZg+fk9brTGOs/uI92+gN7Bt2+eyaUk8xbrdHnSDrJdstCyozFVMfs/m81YUI/M22yBusJnQFt/aw4f1j3xkft4Ffg/DG5cGfR+TbnOUm+Ufq7nnVeG6DPbz1joDPi0u5sExch5IkSHjUm34/wF6vo02oN2NCYfGR8PrCxG0Qb20Q=
*/