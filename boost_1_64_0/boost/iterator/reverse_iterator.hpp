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
j/wsfJ6EuazgjdoRovHSZlf5Ajx5IXm5l4Y/tet9fB67Eaz+hiHAg6KReCl0Fr+s+bXqTnwfm4h+RLv5pPDwRZPh7z+ptcUdTkMlSspiBv0HfKSgnulV55m9pvnMs479l3sh0aku6SwNpQ50as4u81T8tQl9FSSAp42xEcY5R7QyfJbKy2SCwqrmpiFYGJt6AUqDTXiCSWUHJeR7q9c8FsUglOJx7hLw/TOXgTAnb0oZ/+nBQ1AfKZeQr55Je8g/rsrxyfVQsuOurIcAtEHnNdBOEYSUwWDXZ5Hv8uerhop8fxcUWdaHtdEQZueSMuOZjPkAnBzbgibVfEQlzpqG1dEfn+fW4citSSviVPGMOlTG41GQv/I9ef3bYjnVeHVfdQBm9+99TVxd81AYx5aTnaRXv9HXhhkrxnN25nr6nNHxhIgzQpgGJMoL6kW9t0v3wfwQFryq67x7WKN80SXskJv8cqh5xMKSC8JzXFPVXM9sr9M6TGzw1D8NjRBqAsXRiF8gMkqvs/1wnmOxgMNecjiZEZkWKb5qqXDykE9/RF1MC56bZ6tsSfNZmw==
*/