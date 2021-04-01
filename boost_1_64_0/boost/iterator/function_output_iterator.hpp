// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Revision History:

// 27 Feb 2001   Jeremy Siek
//      Initial checkin.

#ifndef BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP
#define BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP

#include <iterator>

namespace boost {
namespace iterators {

  template <class UnaryFunction>
  class function_output_iterator {
    typedef function_output_iterator self;
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit function_output_iterator() {}

    explicit function_output_iterator(const UnaryFunction& f)
      : m_f(f) {}

    struct output_proxy {
      output_proxy(UnaryFunction& f) : m_f(f) { }
      template <class T> output_proxy& operator=(const T& value) {
        m_f(value);
        return *this;
      }
      UnaryFunction& m_f;
    };
    output_proxy operator*() { return output_proxy(m_f); }
    self& operator++() { return *this; }
    self& operator++(int) { return *this; }
  private:
    UnaryFunction m_f;
  };

  template <class UnaryFunction>
  inline function_output_iterator<UnaryFunction>
  make_function_output_iterator(const UnaryFunction& f = UnaryFunction()) {
    return function_output_iterator<UnaryFunction>(f);
  }

} // namespace iterators

using iterators::function_output_iterator;
using iterators::make_function_output_iterator;

} // namespace boost

#endif // BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP

/* function_output_iterator.hpp
hxOvsyHaf3Duodaz5mDFDFct1qVct8DRuQa9bJvCcl0JFMkl2MB/Rzs0G2JMq8qz43YJVrkeNduS4sqxzWoI4NbzTsZ+aji7QjK1FjpfoU0Utn7TecPC3f83FMMPuZtiOUtaOgv4AaqnzGriczEz5u0yel03mfCH5gBAWimvSaf2NWKS3468XIVKIoslkU8kQl3Ocs3MaNDveRbR4XIp9/y4kvP5QPlez4gP719Uu9c0ylZ7MD6l17K7eIQfOpXzjTFSc1MSj+Yk90yK2cmtEuJ5sLYpGGu8IuAvoU49YbMPc4mz7oVYqhv6vGbsVxhldNy44syrTrAhCo3nKU6b/VC0lKvHzLupRRXxnbNEZfdJYDxOtz7WJVZl3LKw/AjnRU+QxJta3k0oDRN/j0ipOYGBriKCX+9IunO25ywI0MNX3xr0/qOLx5oy6VWPQSB87o8HRtkxLhNzebvMK2vixmvxa9oDUCnhwoN684PIk7bCEdGROE4hP+1kdre3gwX08tts+cE6XWC+5wRzO3HoJnnV17EsjVUg6/5BVlCS3yp0h2BG76JnfBIGog==
*/