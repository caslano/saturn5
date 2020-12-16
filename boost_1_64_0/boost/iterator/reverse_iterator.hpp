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
OgnT2F4/FpV83fyqRSXfA51+db3bfQa6Y9OvXCPfux7XlnqQrayfaxDnMW/eIdOGjc5MG5/Jz9NeuZNnvzrLMfY7+Vr8N/TUc3Lc4LxjfOy73Sv53r0gDct6zXr51W2yRlW3wQ3FHK9lb7yYz9V97p8kzmqec53PbWWAewb3s/OMdcOfi3sdmKVu0r9xvpzYlXzfStMv+49jc42138mS/g14wlnSR1ove74N4jdg7y9X/HwMCezhzMezmvV6w+3yLiR2CbQ7X/x3kTgSafe62N2BN4FyqN2xfu/IN4hbWXe4k+nVD7R/W+xH+e0z11bsOkvcsczTBLEr5zZBD/tyOf8PaafbNZK+SGNfOsQrdu297+O0u1jieAZ5OEzsE2l/s9j3c2s4z+p4o3F1EPu63nhpV13iTfI+A+36id3tEmcC7bZI2NFoe5L99sYbJfYXMk5X7h/jzRv9fi11U+wqM6xpV5Y6c6ZzAn1sb9jyHp8ePWnYcY8gc92oPFuWpLcqzS7jDWe/3Qyv5Skzywj/qLjH6vpxvsRXVr87N2Y6OcZgiQ/zToy+4rPinoZ3imo6zs5il2r06SfqsY1scTuCFGTiPPAOWs4rSDpWYKRksm6/lovfHRiZbQLdM0Xr24G3Ge/7Og+a6DrpS7PSh8klaFuUboqHbjL3QVL6Jl7rG+pEY9wgj3Yxp9CTS7g++Tso6KbgV+Aq1bdfXKwnsyeMLbDpSVPHPSn+P3TZp2f4BlqP0C60rmRZrVlSLDsJKj1i3qB14z6JYy7Gquva+/2LrbpKx/+0uFfRctBX4o8z9ZZff6eauDfx01c9l4q+Yl/W+3tH4q3p9na2OxXdSD9d9rLEEU+d4P3dJHZLIGPh+n7STxf7vvp+UvZiV8NPr80Xu3Z+eu09SUNbJ8HQUx+K3ZNueez/JOFp78ozRPrpr/4S5xiUWhk//dXEmyboxt06rSJnEndDP/110HjWONq1Ebtr3brOY346bJDYF6A0EvzG23qLfbTWQ8ru0GKe8UE9pL6BdBF/aW6AHtL1taO4f47SfUqPhXYXu2vcULpniLhX1PLxvpjDi78NSTpitO5BWkW3h9I914p7LvK0sdYNn0kcdU3do/0vEv8YRVJtC9MQLXYX4R35NswsG6d1T3OxP44yuhA9hVv1N6bvJf5Nrk/ftmP+l/RbRkl0jalDHoKb+t0ZBv/gYnA77FLv0DoEoyNUIdxL71H/+q91b/07ZbzWrYV69JkzXI8T3y1xZXk6OY+7NT2V8F5XXpdRfwnTVrcPncXvAD3muFDcI91sZ7Iug5bLlF1H/R0iWcxrsUPb6/Y9de/gu6zWf9217rtI3FpK/kdqv8+aeskMTz3TX+69XOWbpK8MRr5n8J3E+3tUwjzgxjlTMfvgkJ8Oek7cplIn0L/Ek+Wneyrcpeyy/cbuMiRsd7/9n/8udhX95vsdFbuJ0AZpTpKhjzLFvpqnDPKvl7PKNfVSstwv3e+8oGzxn4t8vVTsE2kfJemNRa/vEn3fSFxjxP9OvNnkO6bOOlf83+yns46L3XroXcZN+8sljpXQmg34nJx/KfZN4bdYZz0lcbzhLsbTJBl6a534HepEQdprOY38dNc5EibTCYdLkvH+tUfCqD23zkMuhOsxWJWmv4nbFNq58n4lcoEa4/N30rCDHEp9LtYTfbUemi1+2jkBbpKH34hb2UA3yZvWku460g9LCa0L9B6Mj5r1nnt9RGod0V2ZJY3rxV//X3Ve8ZBYF/bzR5wzoHri2Ku6HV3W4cSwLgP/N84rPuab+8s5z6m4quF6lZm+KMy7jncFWAG8B5S9kMF4cCVYF1wFXqhkE+wN3g/2BR8AB4A=
*/