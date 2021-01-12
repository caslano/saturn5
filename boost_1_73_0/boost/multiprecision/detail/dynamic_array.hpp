///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP
#define BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

#include <vector>
#include <boost/multiprecision/detail/rebind.hpp>

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, const boost::uint32_t elem_number, class my_allocator>
struct dynamic_array : public std::vector<value_type, typename rebind<value_type, my_allocator>::type>
{
   dynamic_array() : std::vector<value_type, typename rebind<value_type, my_allocator>::type>(static_cast<typename std::vector<value_type, typename rebind<value_type, my_allocator>::type>::size_type>(elem_number), static_cast<value_type>(0))
   {
   }

   value_type*       data() { return &(*(this->begin())); }
   const value_type* data() const { return &(*(this->begin())); }
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

/* dynamic_array.hpp
6+uZtw5X+x2klVnODU98/fpWOavHIqwbU2i+W+9mHkqQK17r9IMRjB5zxjC2WdtY/C/axuJ/0TYW/4e2sfhftI3FRNuQ9j7q2zuXjbHT8/JYlrXMXuXnk0UxlalfEJ0fD8uMA3GbwGCYmCsma7qj69PxN7i1ijY1amMpDm6aXRUvmDRg+pgqp2dosVMM43ujC68R2bYX02OQqDr+rubcGMh7UTS3xtLEza95z5THo82HI+Zu
*/