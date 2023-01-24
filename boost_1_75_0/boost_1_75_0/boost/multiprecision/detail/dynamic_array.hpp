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
33V7foCqck5+pjnYWmRtLMXeBqWBWhVirNNmh8bq2owIqzPW71fVz69HsM0KvIGD1EFKNLV5VXM2ar6zhGctDIHUpTRWE2j7PU3T/6qmYDpYWYjqJteo6bSqOdBMsTQGzdvvq28jFLR/SWiIOunf/qRB+tIuE+lfx6RvzyDS/2swkf4lV+ikv/qAQfoXPmmQ/jXPh5H+oKcbJH1AzyoTeqhp7NPNofiBUr0chnUovjDQaG7Jy2Y1iZ/HnjoPflYb+Jn5VHPw86hmawQ/OxY3gp+FxWH42fG4gZ+8j034yWf83DKI8DMng/CzMEHHj/0rAz8LHjfw89RzYfh57snG8LO6Pn7mP9kc/Dx7ztYEfvYsahQ/gZlN4ufUE+fBzxoDP1880Rz8nDzbGH4SFjWCn59nhOEn4TEDP+UfmfBzL+PnAw/hx5FO+Pn5Mh0/t+w38PPdowZ+zj0Thh/bE43hZ019/Bx6vDn4sZ5tCj+JCxvFT5WvSfzc9Ph58POygZ+rH28OfkafaQw/Slkj+BnsC8OPstLAT+x2E36eYvzEpRF+ygYSfgbH6/j54HMDP56VBn7GrwrDz6THGsPPy/Xxk/ZYc/Az8XRT+Fle2ih+vEVN4mfjo+fBz1oDP4882hz8bDjVGH6q/Y3g54W7w/BTvcLAz/xKE342Mn5Kr2H+8RB+XrhEx0/cZwZ+nllh4GfTU2H4qVjZGH7W1sfP
*/