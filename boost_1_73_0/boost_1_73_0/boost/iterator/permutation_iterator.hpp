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
61zXcfiuJWra5XjUPO0Qkc+dkTYaN1sXguSHo/39fQ0MOp0+EwLLtehIuxYLpFiwc86QH7pO/CjS3MWCe1I/4pXUjyP2EomV9zZmK1PutOubyNBCP0ZJQLnnMvYXZuxYpus+Is9hvfaQ8qyf2XtS+7Vn5Wh7/CGWDECIeyL/JJejpGOF5IkNrkbdW2wBZATJiOiJqdMeCB6s72OJHSbWj0zXmjsk4zIsWB/pUlO/oElaz4xksYxiEGX830vTJXL9dufk+owyOfFQZbRF4jEh2T7R2icgJCEVqV2c0LGzcL6alIIfs9rVR+8XomLzyXI2w3IxNwMJ/m/a4vaJXpX4usZwiI9Br3Z1SM8nf5cWH3KXw7007uJfKcwsDyJoZ2uhtH/qu1AQaZeUToXGVPxKD/UXAXK1kLRDK2ndnPoucmfQRIwcXt10hhcjYTzJG11Rl/AZEDCQSt60bhI/3qtEywlU+aXaqO5VMkBdb6jMbLQMAj+Midf34DUueRz6Kx7eRTlSrRZoLFaWhdw10ZSYm1mWEn3QGZIpobSgIuScI7clE7eQ7EM1MGfmYc9QXN043vtDhihiho9JDeHDrzHhMnN1dwx0ckd442q1qs/uvBVlvQ2bQ04/IJNvBOEs9n03agC+hgJzf//Hw/f1
*/