/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_UP_HPP
#define BOOST_ALIGN_ALIGN_UP_HPP

#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_up(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T((value + (T(alignment) - 1)) & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
4RrYBzhkSYxMYmRNunnSmBmeXw2hlKhvLK+7uiu91mwwFQ+noLk3EmRoJADtu3dPYPAwNNV5GDIyzNqZLYwN+9q2Pk19lPayQVGgI1UwQAn3/BC8zkdVkWLrQqhKLRJ7iuOe0GlnlekGgX9gre62+YhEVgXSBlITV0TZNStEyr6hyL0ftCQifHZDYpbqSSNyJOhIOJKKaUzC5jloimX4rI/FDJd951GqkLYS/wqeovUc96GDRWX7M6BWgOtZhMVVjzuZEYeqsON6y90hBOKmUPZOaFtuVl68Ewf8E2CcQVtTiEp1A1AEZyh9eScUOnBXsFfegsdurMOsQLVcrxzghz+NTgCYCGJQCGZeOmup/+xl2R5L73+7hzI43K8Fy3/zOdxoNztXl00649m+LOJ1lZvhz08Wb3ND6Wd03IcUckS0Fx5UNeG6nbnvmEypQhb9WYmm5QgG+LH3SiuXFn1XeosfZIqrI+lkCw2qiXX9ChxmbYsaYlPit4+xUVwr795UoVocyEco3RnWnakHO52xyIynR55luAAq7+Zr7wkZIrY5YgHHKksNJSYy6WwTnc82584yLN1oq4bdNenlThnSEPhQvKwpnsf4YVvgckI5DP2RXFt6TD4PcpjKyfwAZfycfRBowTi1LpUB7F6TyHZa9bswDKbIKPLBkosWFVHR9PLC937W/mlESOt7PHGnffT5msnwC66Q43lMBk5J
*/