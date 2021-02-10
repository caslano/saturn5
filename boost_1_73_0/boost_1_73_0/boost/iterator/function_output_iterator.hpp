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
+szsyzzz0m33mDZJc9TkVGQqlcKg/ZmLTB6vTyhv3QiFt7+IQ3SrIV7+gIMeE3lwlP4kiSdFFM3QIm0MVlFkXyEE1RBeoDzBE5o62+vzkjQP/a2m8V/lErzUqW9FRnktonK6akZ7vbrvO+xX9+PeUGUrY4oW8NK50v4DUEsDBAoAAAAIAC1nSlKnaaCsJwUAAF8OAAAcAAkAY3VybC1tYXN0ZXIvc3JjL01ha2VmaWxlLmluY1VUBQABtkgkYK2X/W/TOBjHf99f8QhOYkWlhXF3OhB3uqkcRwW3ob0IJk2KnMStzRI7sp12lfbH39dO0tld0X6hCJJ8bD9vfr6Jefr85/0OntKjvyz8zfDD1S/4YvR3Xrj9k7Psjro/WHSN6yMupnS/4i4b0aMr7ugwrMh6H+/8fZY94ubaB+b/mfqF15m/BTl4inUz3WyMXApHh7MRvXrz5g96QUcvj16O6T1Tkld07rjKuVmO6V0ZyN+C3d5OLP9rTNwRqybB0IWQlqxeuDUznHBfyYIry0tilkpuCyNzPEhFTnBayIrT7PTL1fzk3zGthSwEbGx0S1botipJsBUnwwsuV52JhhlHeoHVsF1K62CvdVKrCVxzctzUFia8c1ZZTWzFZMVyuGGOhHONfTudFq2pEPm0
*/