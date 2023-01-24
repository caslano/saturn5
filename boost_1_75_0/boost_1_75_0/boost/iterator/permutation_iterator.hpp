// (C) Copyright Toon Knapen    2001.
// (C) Copyright David Abrahams 2003.
// (C) Copyright Roland Richter 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PERMUTATION_ITERATOR_HPP
#define BOOST_PERMUTATION_ITERATOR_HPP

#include <iterator>

#include <boost/iterator/iterator_adaptor.hpp>


namespace boost {
namespace iterators {

template< class ElementIterator
        , class IndexIterator>
class permutation_iterator
  : public iterator_adaptor<
             permutation_iterator<ElementIterator, IndexIterator>
           , IndexIterator, typename std::iterator_traits<ElementIterator>::value_type
           , use_default, typename std::iterator_traits<ElementIterator>::reference>
{
  typedef iterator_adaptor<
            permutation_iterator<ElementIterator, IndexIterator>
          , IndexIterator, typename std::iterator_traits<ElementIterator>::value_type
          , use_default, typename std::iterator_traits<ElementIterator>::reference> super_t;

  friend class iterator_core_access;

public:
  permutation_iterator() : m_elt_iter() {}

  explicit permutation_iterator(ElementIterator x, IndexIterator y)
      : super_t(y), m_elt_iter(x) {}

  template<class OtherElementIterator, class OtherIndexIterator>
  permutation_iterator(
      permutation_iterator<OtherElementIterator, OtherIndexIterator> const& r
      , typename enable_if_convertible<OtherElementIterator, ElementIterator>::type* = 0
      , typename enable_if_convertible<OtherIndexIterator, IndexIterator>::type* = 0
      )
    : super_t(r.base()), m_elt_iter(r.m_elt_iter)
  {}

private:
    typename super_t::reference dereference() const
        { return *(m_elt_iter + *this->base()); }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template <class,class> friend class permutation_iterator;
#else
 public:
#endif
    ElementIterator m_elt_iter;
};


template <class ElementIterator, class IndexIterator>
inline permutation_iterator<ElementIterator, IndexIterator>
make_permutation_iterator( ElementIterator e, IndexIterator i )
{
    return permutation_iterator<ElementIterator, IndexIterator>( e, i );
}

} // namespace iterators

using iterators::permutation_iterator;
using iterators::make_permutation_iterator;

} // namespace boost

#endif

/* permutation_iterator.hpp
HzGoQWWheM2RfiK6kE+Eim0exUuP3xwndLL5aPPxZBzlxU9gY8ILgHIbuTZ6B+KwTWCwb1ge81RJCaDZN8m9p+Nzp4E3X1hk1t0IxeLuKO3btonPw1TVUZpZPNz6RWZH2R7elPzHWtUJGpKmFpsfc8go4VoDcWJRNKyscpuK0oNhGqsJYYtW2SoNwTflRk6EdLZgKt8DVBdmNsTvxwSzK2Ze2hW/RQpuPIwwlwFPEpbr9BldWCexabNi6EQ5lJqocIZ1UNc8hF7CwJNYfeul123NbB1cVShY3yQcoCfSNC8l/A2xt4euX1AyP4ylvm7J7m8N5It3OZ1WeQWKupnCTxvVcgqXzZawCwizRSf0PcRxYkq1HjF1i52MF5yvzTVmcFBB2tn8KZfNFmMQ1ok2T1qqD11Ez0Ud/+dXv5AKurhbFfJiGOLkbgPGpdeu0f24XGsXSFga9wU1IgYeAbSfn0D0n8QrX5lgwoebuFUFvSinitbn00H2smPkoY4QEH2lVgBcnwyJt2jxSbSSE7QoGIAHaba1vlY80n1OU9CrIpGA5xL8FgNZ7bScyx5j82zei8J/HOx5htjsMEBTAtq+fjgY0DyvT5dYsFyz+mC3ooEzYW3x44RukeUzYrNzgILR3brQajDImXcE0EthD/8ejeHAqu0V2aMdH2ym7ZOALt8z3z8iwGdgTn3kVzzoR4D7IVxsIVPar/MDwqu0
*/