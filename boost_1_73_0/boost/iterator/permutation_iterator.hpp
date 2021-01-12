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
BlSVTG3DnMabUiOQMG9NApPWE0O0G8cFasJiR+Xe4u9EQ63pq8v2tJZ2aIHOoeG1z2Fg+tWHvAPThefIwFSvdoAuQ5LaxwhLdoBu1+PPPc+554F3POfaJ65GOGHNXTRjCQ7YZst1LjMI6XDA6w9N24fsEfuQlsGGINYAOD5cg+91L8NfybFZthvHdPTU0m5dfD/XTsMo4O8FRewFDSiiWRIPoRnMmfpYthuM8P6evfgsPfnn
*/