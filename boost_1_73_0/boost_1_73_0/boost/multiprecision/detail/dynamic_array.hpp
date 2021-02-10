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
ia1V8ym6GtPPQkdLb0gJqVh5Hc+blqXrNzmtVuQXmq1nRAL1KJ3fdP+QJ1kKtlnN4mCWj93gLPvCggJ3QFtBCDvMMj3z5SnZBOX3IPpObbhde3X6CST8xM81DSTAC/djuZiO08bPTRaPVB6LE0EyAlWx4C1GirLBmHa4/HDvKzINpz83HHiifStEGFF0NKS4QicFlkBilH/Y+P3zycfVAfzfqZx8XHPlj1yarDC6UWLInZ5jJ/zghg/t1IMRNdOmzSBbcjplm4JtaXeFCMMzJwD30xlPQ5r0LkFjeSirM5NkXpLrcq/9k8Ddmg+Jajm2xGdpi07/JVYNiRzwLRYbWivaNkmWelxOLYTL4rSQsScJcJjcsTik492IqqX7s5pJOagEG6Y9VAnLFiSD83G8wpM6pUs8cQG6TATjY0xqao5TX3lCUgRVsehgdRWr2QpX3iazZGbt9i9VmdyEA3lozD32+VVtRc+ZX+90es2d/3g3FkBbbY//bdA+ciPMluyfL4C9iiKYiT2mLXWT/JGwyJa3dOZ2TrJR0oC5fNCQosPMmoWDAg4reFoM88W8IejJRbHiagPolIpAp9NronKknWVTJ94M8zx1pyy1lUPX5lP2bo8dtdv7/wLpLqZNIf0Iu1Vi5eH3V93O7gYe
*/