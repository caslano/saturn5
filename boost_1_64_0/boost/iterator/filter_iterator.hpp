// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_FILTER_ITERATOR_23022003THW_HPP
#define BOOST_FILTER_ITERATOR_23022003THW_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/type_traits/is_class.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace iterators {

  template <class Predicate, class Iterator>
  class filter_iterator;

  namespace detail
  {
    template <class Predicate, class Iterator>
    struct filter_iterator_base
    {
        typedef iterator_adaptor<
            filter_iterator<Predicate, Iterator>
          , Iterator
          , use_default
          , typename mpl::if_<
                is_convertible<
                    typename iterator_traversal<Iterator>::type
                  , random_access_traversal_tag
                >
              , bidirectional_traversal_tag
              , use_default
            >::type
        > type;
    };
  }

  template <class Predicate, class Iterator>
  class filter_iterator
    : public detail::filter_iterator_base<Predicate, Iterator>::type
  {
      typedef typename detail::filter_iterator_base<
          Predicate, Iterator
      >::type super_t;

      friend class iterator_core_access;

   public:
      filter_iterator() { }

      filter_iterator(Predicate f, Iterator x, Iterator end_ = Iterator())
          : super_t(x), m_predicate(f), m_end(end_)
      {
          satisfy_predicate();
      }

      filter_iterator(Iterator x, Iterator end_ = Iterator())
        : super_t(x), m_predicate(), m_end(end_)
      {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
          // Don't allow use of this constructor if Predicate is a
          // function pointer type, since it will be 0.
          BOOST_STATIC_ASSERT(is_class<Predicate>::value);
#endif
          satisfy_predicate();
      }

      template<class OtherIterator>
      filter_iterator(
          filter_iterator<Predicate, OtherIterator> const& t
          , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0
          )
          : super_t(t.base()), m_predicate(t.predicate()), m_end(t.end()) {}

      Predicate predicate() const { return m_predicate; }

      Iterator end() const { return m_end; }

   private:
      void increment()
      {
          ++(this->base_reference());
          satisfy_predicate();
      }

      void decrement()
      {
        while(!this->m_predicate(*--(this->base_reference()))){};
      }

      void satisfy_predicate()
      {
          while (this->base() != this->m_end && !this->m_predicate(*this->base()))
              ++(this->base_reference());
      }

      // Probably should be the initial base class so it can be
      // optimized away via EBO if it is an empty class.
      Predicate m_predicate;
      Iterator m_end;
  };

  template <class Predicate, class Iterator>
  inline filter_iterator<Predicate,Iterator>
  make_filter_iterator(Predicate f, Iterator x, Iterator end = Iterator())
  {
      return filter_iterator<Predicate,Iterator>(f,x,end);
  }

  template <class Predicate, class Iterator>
  inline filter_iterator<Predicate,Iterator>
  make_filter_iterator(
      typename iterators::enable_if<
          is_class<Predicate>
        , Iterator
      >::type x
    , Iterator end = Iterator())
  {
      return filter_iterator<Predicate,Iterator>(x,end);
  }

} // namespace iterators

using iterators::filter_iterator;
using iterators::make_filter_iterator;

} // namespace boost

#endif // BOOST_FILTER_ITERATOR_23022003THW_HPP

/* filter_iterator.hpp
rJ0TLuGZn6l4gnh2U4a30e/LXX9iPLe2t/rqWQeAdLbvGQQBQHiP9AjNHmlr+4bEc6AOu/XnQJ0An55w/W3b6pdWVVVXsd+3M71R//Nhpre2bfJzoCg/9SVPMVqWW/oOIloux43F1s+BUvkoAB9iP/uUmkb1ibK2zdTLehK0DRJZ2fFrFmVt0PD/m4Kh8S/y6pml5/U7oPVKeG1t72zZ4bPGazi/Q/D9ZnmcQo1Mzw9RJho7ke83D2qv8y/Xy/gk6LolMuJrJpPvEON525Z2o++kgt89zmibiFYjo0DL248NGQ8xecCH4HePszTUpzn7r3S2Xs5joPVL5MQbd0dry02Wfc8v2PMxY3tyOj6/tCGrzJ6PCfasJDnz5+jlfA50vRI5O1t86E/e1c6iZ1iUFeUI4xMma5vh+bgaedvi7FPKAAWoT3um8UmSuZpKqgIcRf4AydwunIdbm2NyHi7nl+83lckFupjvyUFnw9ZqYoGibN3ZsKfmamSgs2FdZ0gG2cmwFs80dp2xfjZsmJb2VEKv/rm0J2SU4iwpdaaOVay93+yc9RrZK+aaHy7gWipoA53x7Q3rQB190/gB3a0P5alrY+BvPgIabmdrN0vF/p/xGaHZBJp2lcY1U3jHDabp5jSXGtIc4DQ5hjTHQNOh0qRnCL4fey1p55mYe0P0540vCD+4ndr6beT7fYLO4Pyog/u+18hPkEe739or9xNOK65dcDleZ8/G8Dlh2Z95/FxxrsDntH8genaPvzYy+pSYY7pcsX2RXJq91yxNbGfuhZr+kdpZ958j+hr62eHdf7bezohW+HZq97dW/2TvSuCjKs742ySQQJawQBJCuAKEQ4gakFuOcElAjgiIXJrEJEgkF0mA4BlEAQU0VLR4VKNFxQON1ioqKt6oqBGoBaU2LdhSBaUWLFXU/ufb/85Odt/CRrHnvvy+/HfmfTNv5pvvzXsz75tvTnhPaf04wvoOZUZDqB9V7vqWBds3Vh0Krm+sOnTq+8YjZ/vUgW1Wxzr8mL6xrgFtRl4ZAxyDXDeezTnmvvisPeDU94tHgCVhgX3f2vtCDuQbuOE+kgP5En5UfF21cxbceXrzL35x/Mpek5LWPnTTv88Xsr1v44b7lt4v9bp/6J8/+2LWqtkRWXfdMTdy/qRT5yPZ3rd0IF/UDffVdap8hH2l3keotFUtQMCxXBM8D2liEC40fl9g/M40fhcbv4uM37hnJM9eoLn8fQYoz/h9EX/3AV3I3/1Ac4zf5/P3NaAZ/P0gKJu/z8b1svRv9/ezKpUOdfkSaDm4Hptrv6u4bukI6/4Y9wd9kvu4/ho4EfgUMAP4ITAL+DT9Lj/D/VifA94N3AJ8EfgC8FXgi8A64EvAPwFfBobhuq8BI4CvA53AN4GtgG+o6wO3ARMY3x74NjCV6foD3wUOBu4ADne4yzUJuAs4F/gBsAT4W+Bq4G7gnYpP78vJtb9c+1zlsy/nOXC5pnAssAMwHajS1er1oqgz07UGvcp0k8Cnzk0FNgdOA8YClwDjlN4A1TVmAFWbzwQOAs4CjgLOBo5VbQ48V+kBUMn/ImAG088ALgDmAEuBc4EVwPm8TjmwDHg5sBx4L3AhUOnJIuCT5H+W/Ho/U66z7MB6mfthQvc0X21gPuic5oOwA/OdYfgVTyXfHvKZfsUfRvnCgTXAM5UeAtOU/gHTFR9wnGoL4HSlf8Ai4FvAxcC3gVeS7yrgVuD1qr2ANzB8k9JP4Fqln8B1PH8n8HXgBuAbwIeZ75PM91nmq/TgceBO4BPA3YxX9YtycI0Q1yZVUR7HWb8rwNcRuAw4EngtMAu4HLgAuAK4Eng9UKW9ge25CngfcDU=
*/