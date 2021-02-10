/* Copyright 2017-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/has_equal_to.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
using is_equality_comparable=std::integral_constant<
  bool,
  has_equal_to<T,T,bool>::value
>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_equality_comparable.hpp
8kk5rZqZrh/fb/I3D1t1nl4ov+cN1d/Lv3zvUo1nqzxbqutttrrLNm8u1ZcL/eT/Hmbv3n1eZP97qbKtmi0/F1A3D3mhivX99rfZJlPl/TKfZ6siW6hZoRZZMd/kd+U/8pXaPmTqPl9mKn393U8vX319qX57yOcPFZD3650qHta75UI9zH7N1CabZ/mvgPE422zV+r6cXgJf5MW2BLjb5uvV5yXuTG2zzduiglGhny2LtZr9OsuXs7sS0WyrHrbbx+J/rq7mu82ypP5qsZ4XV/N6+Z8/bN/uV/JTScTb2Xu1ftyq7VrtiuxSVSMv1dv1Ir+v/i4ZUj583N0t8+Lh0lBTolotrtYbVWTLZQWrnJdnBcjO1LWw57Iaph5LivNt9VexXhUVqt8e1m+tgSUfKyj3u82qRFTyoRy0WJdsvlS71SLb6MF65TUK4almcKtoDL0LtV6VxKgXybV6ef1C3c2KvLhUP768+cfrH27Uj8n33yevbn5Sr6cqefVTBeybl6/GpejzEtlGZe8eN1lRIt+o/O3jMs8WgvPj/bk6+yRfzZe7RaZeVMKbP2TzXz5/eHFGz98NevGsWHn6cbGdbfO5Sn/4/tv5uvx0t8q3t0W23T2e/7rOFxdn/z5TpWJtS57qQZPb1998cfbn
*/