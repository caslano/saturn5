// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_REVERSE_ITERATOR_23022003THW_HPP
#define BOOST_REVERSE_ITERATOR_23022003THW_HPP

#include <boost/iterator/iterator_adaptor.hpp>

namespace boost {
namespace iterators {

  //
  //
  //
  template <class Iterator>
  class reverse_iterator
      : public iterator_adaptor< reverse_iterator<Iterator>, Iterator >
  {
      typedef iterator_adaptor< reverse_iterator<Iterator>, Iterator > super_t;

      friend class iterator_core_access;

   public:
      reverse_iterator() {}

      explicit reverse_iterator(Iterator x)
          : super_t(x) {}

      template<class OtherIterator>
      reverse_iterator(
          reverse_iterator<OtherIterator> const& r
          , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0
          )
          : super_t(r.base())
      {}

   private:
      typename super_t::reference dereference() const
      {
          Iterator it = this->base_reference();
          --it;
          return *it;
      }

      void increment() { --this->base_reference(); }
      void decrement() { ++this->base_reference(); }

      void advance(typename super_t::difference_type n)
      {
          this->base_reference() -= n;
      }

      template <class OtherIterator>
      typename super_t::difference_type
      distance_to(reverse_iterator<OtherIterator> const& y) const
      {
          return this->base_reference() - y.base();
      }
  };

  template <class BidirectionalIterator>
  inline reverse_iterator<BidirectionalIterator> make_reverse_iterator(BidirectionalIterator x)
  {
      return reverse_iterator<BidirectionalIterator>(x);
  }

} // namespace iterators

using iterators::reverse_iterator;
using iterators::make_reverse_iterator;

} // namespace boost

#endif // BOOST_REVERSE_ITERATOR_23022003THW_HPP

/* reverse_iterator.hpp
QnRNSpRbtNzqZMDD+tMGU58BHMyxKqeOR6RFS3FrImFOb5cg9gqhuBc33zYeY3nLp2Z77e9Ud37nGJwkRNEIG7zE1TEnqM7v2MJSpWBb0KyrRtg4BWovvlVfsrRHPuMQhZMIvdF+3YegjjAM6BuOjiSKVsFxqNQO+0qKfjNh93pcnl34XjD6Y4J9AhpoXkJQSZnPC6nhS0skq58veI7lFubkubWG7QABigjIyLvzx892enJOZySIVErKHWhW6qxsJubFlMSOBSVTgpEmzwKup/G1+YyB86fIrMU8Bc3yetcesJvGLYUPvZ7LEw0iahPPmQztOBCu8dVf3uRgnG3i6ayAhhpjPLOkKA5vkKNw/n5nn7fLI79VSsfRwp4BDDsGn3EM0CnSrcvxuiCM7uGBIPXu5ZJlHQgsUmfLnE85+eA4JHk54KN+/lTG8a/RPb+C/kVcf+HEnrRJXxuM4RlLpY8jjYGa8F3p6n+klvjAqFOpc49EvO+8804oBp1n+z61vvEAv81IKwHDWz7yI3O4wNNKnobk97lHb3WLOAHxZt/7rxbrHDv3gS93+H6NBP3qh+oLp+6ocC3gQwVQHkO4bHuBGVL3zC1+J+z8vV55klCEoDsuRHbkejf2oiTrI3Ktj5RZsgpgL9OUIXNOYV9EAYU/FX/9sHeTePrCjaul2g31Z9jcZKo6+IAb7ImnHDlDaZ3Unr0TLHKc0aN2
*/