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
h5x8/n1IPor9PdFegDkqLmfP6Smv1qchaZImf2g7TkYpQP8EKju6ikzPa43hXIaPv0zRJzEn0x633T1zWoGiBJMmAV/cyuqoW+Ezx0zHI/3+EWJoq1K/dLneaAfZJEAEzBjBlsJtzApcXr1FFvoLyyP4MkI8MKWS+mlfu8ec5sHT16k3Ry0qnf6m8g+Fg/MaerHBENIoQ/P3ob6e4Rea1zLIgClsqb6wMWlnxiw7B/n195616bi8GhgCp19GC2IUGj8LD5CVuJXZBLytpxRnild6+x+moqa61f1H84qW5pOgkfBd1QzWFb//JpMXTT64l+n9DVYzDf/7V1Ds3J/E2OxAmOiZZFZEVtwpuJCcbnxwv8lpWeOlRhN6USJZu5uOXtOPTIShD2iFoCZqHOYwSmOUso+8dHDn6xWzIPUPP5N4kTrB9MXfyvFOV22jW/lTnlTDDIYyjXzmE/0ohG9mRpejOGyBPCbTPAw/R6M+V2odOXlfqzvQGq0JzHmFaD4I+hWRfoKZX/CAcJ37lWbv3yzLIijf7c0TP999SfbI3UNX/eYM7UxaWMem+MSTbjeBUlys+Q5I0faiCNc4mJe52IuVdMvabBnQ2hpVvsfv6jGllAy7hifjtht0+CZwZge8KPF/MmzPUpoVTbBwp0pEaNtN4QhD6LTaDsqB84VkMjh5kivkwnIP0ja2ERWcO11DRiCtdYH0Hz2pr/Kw
*/