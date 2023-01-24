// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_COPY_ARRAY_HPP
#define BOOST_MULTI_ARRAY_COPY_ARRAY_HPP

//
// copy_array.hpp - generic code for copying the contents of one
// Basic_MultiArray to another.  We assume that they are of the same
// shape
//
#include "boost/type.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {
namespace multi_array {

template <typename Element>
class copy_dispatch {
public:
  template <typename SourceIterator, typename DestIterator>
  static void copy_array (SourceIterator first, SourceIterator last,
                   DestIterator result) {
    while (first != last) {
      copy_array(*first++,*result++);
    }
  }
private:
  // Array2 has to be passed by VALUE here because subarray
  // pseudo-references are temporaries created by iterator::operator*()
  template <typename Array1, typename Array2>
  static void copy_array (const Array1& source, Array2 dest) {
    copy_array(source.begin(),source.end(),dest.begin());
  }

  static void copy_array (const Element& source, Element& dest) {
    dest = source;
  }

};


template <typename Array1, typename Array2>
void copy_array (Array1& source, Array2& dest) {
  BOOST_ASSERT(std::equal(source.shape(),source.shape()+source.num_dimensions(),
                          dest.shape()));
  // Dispatch to the proper function
  typedef typename Array1::element element_type;
  copy_dispatch<element_type>::
    copy_array(source.begin(),source.end(),dest.begin());
}


} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* copy_array.hpp
QKxpXTWctBm3Ql3sUOPoaU4z5tVzEj11mdjhSza28DCRasgOVMztNo0W23jivIv+ZcXqg/FWwbaTJ1hDsChWH7uEtj9xtLujdNJNxpE9yGZDixjZfS/xyBTzyOzNHFlcvZHN72WM7OSl+sh2jLfqPRer/4w3xjWmjT6uNcLcnqhWwFPkGQma6XxamQkVCzrwwLyouf92E8etbeZguN0G+G9nGWKPM4RIZpyQIqSihsQIvvwpl/7yFIshRvRKAp+NFrFxod7RHwK6KSYYFxst34CWKAqAMlI56O3Cm0wioQOe6DnD6Lb1JqfOLl8AitYfhq+ovonv/Tza9OiXo+s8CtpA5WinZIiXjbEG2y27xNq0pFksJM2uBXUkjWesIWqkVkb+85YkSn5vycKmU2sQNt+Lk6/E7z78VT8WZx/Ar7q5ZagekWFGWHAkuhXJH98pQ/5IrdDCDWuek6AdgUQOZSk+1IPnk4LQfFLgSZkHyhQWuc5wbf4AqHbMLk6iglBR23STjAQSm3DlgVlgWpyOpCXD3XAxdavLX0rFbbmgBZd+u1b0UU5JXvee4vb5lNqihONccS8JxaCVHsLtIpwq0uSgXhhjOH4RrwhyZNxNKU0UiSuYLk5fgPphucyJbjE1n8gkR3rbgK68Hx1pFRdad+MLklUK1f3YE8oOIup+HGq4AoYxqp9i8ctCT8abHxLtsXWNE3PUZllZhYUp
*/