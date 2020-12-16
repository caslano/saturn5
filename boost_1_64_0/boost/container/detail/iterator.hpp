//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ITERATOR_HPP
#define BOOST_CONTAINER_DETAIL_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/iterator.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/container/detail/mpl.hpp>

namespace boost {
namespace container {

using ::boost::intrusive::iterator_traits;
using ::boost::intrusive::iterator_distance;
using ::boost::intrusive::iterator_advance;
using ::boost::intrusive::iterator;
using ::boost::intrusive::iterator_enable_if_tag;
using ::boost::intrusive::iterator_disable_if_tag;
using ::boost::intrusive::iterator_arrow_result;

template <class Container>
class back_emplacer
{
   private:
   Container& container;

   public:
   typedef std::output_iterator_tag iterator_category;
   typedef void                     value_type;
   typedef void                     difference_type;
   typedef void                     pointer;
   typedef void                     reference;

   back_emplacer(Container& x)
      : container(x)
   {}

   template<class U>
   back_emplacer& operator=(BOOST_FWD_REF(U) value)
   {
      container.emplace_back(boost::forward<U>(value));
      return *this;
   }
   back_emplacer& operator*()    { return *this; }
   back_emplacer& operator++()   { return *this; }
   back_emplacer& operator++(int){ return *this; }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template<class InputIterator>
using it_based_non_const_first_type_t = typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_const_first_type_t = const typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_second_type_t = typename iterator_traits<InputIterator>::value_type::second_type;

template<class InputIterator>
using it_based_value_type_t = typename iterator_traits<InputIterator>::value_type;

#endif

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ITERATORS_HPP

/* iterator.hpp
hUzOrI1H06kwk2A/JHUxwHLJ7JnFdG7mBzMLcSuGN5gPc0q2rCHO4981U5I5sbgHM+q3hKnJSrM4rXFZcVwQmTvPs1nZtOJ3KGT4TI2zVR0pUbpoA9OSuTIbsiVxGyyBTM7MuVLSeJierAqzdVuvpsBMZDJmQwe/fwu7y2ovsPvrxuqKjN5nkoV/e1fuZjVe2vHEtLz4njLj389yeFB9lbu5D4ClkFVnlrN/9zhYHpkrs009b+cXX0+c//cYoqDzg7/X4yswNVkNZtfa3ltRfB4jw3snT7IJf0T+F5ZI5s9skHJ9bVgGmZJZ7eveP8FyyXyYOXw23oHJLlANzK5dznoHU5G5Mbs1e0RtWAiZO7NRbXeOh4WTYVsqsPMHUq/DIoT5akacCIZpybyZ9XwxeB5MR8ZrWFs/twbMSKZg9ujoqvmwDDJfZsnzZt+H5ZJ5Mpv2qEab4v79/m8fvKy00prTPXvBNGRezPJvpTrBIskcmZ06MXYdTEtWhtmer3blYDoyX2Zja/c8DjOSeTDr0r7DHVgGWUVmM8v9MRmWJ4x5+UlvI0x+kfZbZu+Wqz/BQsjkzOrOzkuGhZPx+m5sHJYKiyRD3wtsin/bgbAoMl+e56Q7K2EJZD7M2gx8+jvMQGbPTNr6NASWTGbL5tOMWN4fdkzIZfvCZkOKbIyUQYZ92ttqkCRrt68KTLpE52JmTjtfXIHJybyZ9T7Z+TIsiMyd2a7oscdhYWQyZp2WJ/WGRQhxzda2d4VpBXu5ubQalkBWhlncsClKmIHMh5ldqIM7LIPMi9nt4V98YLlCfe7qL/VhssuWuUyusHYzTEXmx2zjkjIXYGFkKmYXx+j7w7RkPM/Zf7pUgunIPJnlPDCehRkFu/3m579hJjJe32EppxcsT7B7Xw2bYPIrln3fMPVIBZiKzInZILOuHCyIDOecAqt0K/lYkfWXQshwza6khx+xHdK9i2y4pGVWxuoH6dav61OKj2dkPb49C/Klc9XpwwdewlSm0lJHZm+yV8+DxZN1Y9Y7+q+/YHlkEcxqtajTDhZ5tfiavdDG3wlYBdOSuTCzHfFcjWeH8SzOj2qvWXG+O0xH5sRsV6mffoLphThn7XVvmJHMm9ld57JRMJMQl1WrwxhYNpk9M/dto1rA8mCI2//PM5h0jc4dzCacml0JpiQrw+zCnD4TYSGCHZ/27DAsgsyNWaZXg2EwLZkrs67L3iyGJZCVZfZYWh4PMwr2fOuXnbBMwWI2Pv8LJl23zDM127Y8TCVY4oXgVTANGe9DwoB/+sEiyVyYBQ73vQPTkrkzezJr8BdYAhnP0xhzwR9mFOzIdb0LLJPMl1njG4lqmJlMyezdx+1HYMoblr2t8/jTZVgQmQez9xsnGGBhQlzVmXf+hEWSleO9PaGaBksQrHW5nr4wIxmvwW3grq4wExlfs5qTA9bAcsnkfM3WpSXApJuW5tJm62SYksyN2fzArGGwIDIPnuedLh9gYULcuDo/7odFCvPd27l2MiyWjNfn6DbjLSyRjNcX8VOCBmYUzH6s93xYhpDL2tBjpWDZZLxH/0lZMhlmFuqzVWtuweR/WOaZ0L7tW1gQGR8zv2+v/bAwMj6m77zP72CRZOWZvb83tQksgYzXMK3qw+cwPZkrs2Ppb2SwFMEuV3p4GGYSxqxd6c0EWC6ZC7Ps9ms7wMxkzsx0zzt2gcluWfZhzB/1fWAqwQ7Jt9jCQsj4ek5c2UcBixDi7kX1VsK0ZHw9p3yZcQ+WQMbz7KJacQKWKIyZ/GTiYphRGPNyqmkULIOMr8ua1vJpsEwyOY8b87YBLE+YL+SXAU1gskzL7aXzr5c8YSoy3qO8ddNiYSE=
*/