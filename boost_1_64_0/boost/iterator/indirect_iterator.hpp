// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_INDIRECT_ITERATOR_23022003THW_HPP
#define BOOST_INDIRECT_ITERATOR_23022003THW_HPP

#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/pointee.hpp>
#include <boost/indirect_reference.hpp>

#include <boost/detail/indirect_traits.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/has_xxx.hpp>

#include <iterator>

#ifdef BOOST_MPL_CFG_NO_HAS_XXX
# include <boost/shared_ptr.hpp>
# include <boost/scoped_ptr.hpp>
# include <boost/mpl/bool.hpp>
# include <memory>
#endif

#include <boost/iterator/detail/config_def.hpp> // must be last #include

namespace boost {
namespace iterators {

  template <class Iter, class Value, class Category, class Reference, class Difference>
  class indirect_iterator;

  namespace detail
  {
    template <class Iter, class Value, class Category, class Reference, class Difference>
    struct indirect_base
    {
        typedef typename std::iterator_traits<Iter>::value_type dereferenceable;

        typedef iterator_adaptor<
            indirect_iterator<Iter, Value, Category, Reference, Difference>
          , Iter
          , typename ia_dflt_help<
                Value, pointee<dereferenceable>
            >::type
          , Category
          , typename ia_dflt_help<
                Reference
              , mpl::eval_if<
                    is_same<Value,use_default>
                  , indirect_reference<dereferenceable>
                  , add_reference<Value>
                >
            >::type
          , Difference
        > type;
    };

    template <>
    struct indirect_base<int, int, int, int, int> {};
  } // namespace detail


  template <
      class Iterator
    , class Value = use_default
    , class Category = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public detail::indirect_base<
        Iterator, Value, Category, Reference, Difference
      >::type
  {
      typedef typename detail::indirect_base<
          Iterator, Value, Category, Reference, Difference
      >::type super_t;

      friend class iterator_core_access;

   public:
      indirect_iterator() {}

      indirect_iterator(Iterator iter)
        : super_t(iter) {}

      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0
      )
        : super_t(y.base())
      {}

  private:
      typename super_t::reference dereference() const
      {
# if BOOST_WORKAROUND(__BORLANDC__, < 0x5A0 )
          return const_cast<super_t::reference>(**this->base());
# else
          return **this->base();
# endif
      }
  };

  template <class Iter>
  inline
  indirect_iterator<Iter> make_indirect_iterator(Iter x)
  {
    return indirect_iterator<Iter>(x);
  }

  template <class Traits, class Iter>
  inline
  indirect_iterator<Iter,Traits> make_indirect_iterator(Iter x, Traits* = 0)
  {
    return indirect_iterator<Iter, Traits>(x);
  }

} // namespace iterators

using iterators::indirect_iterator;
using iterators::make_indirect_iterator;

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_INDIRECT_ITERATOR_23022003THW_HPP

/* indirect_iterator.hpp
cFWx7/JvZowiIYb7Rxkd3k2g7T9c5cKGc+K47t9dhPBtGmhutU6SCRri5IE8MEe/ZDTJhphaUw1W2xWp+MHwGloHJ9cMnRVtIvXpTEnoCKPW2wURyBpyeTPWuUPFMhPb6zIUxS7x2DaksIfn7oEi0iyy5q07uT5r0EQPNU5WLDY8l4uPZZG2omfz0lCjmJpAmetyTKElfKNAy26t/MRuXGBmK7k9T9MaAdZwd0hVT4O/KG6dCWy5+43sCdpPElrVnquIM/iWmi9ByhwDdw7xu5/FglqTTWjulBh9YkzFu7u3uHSJV+g7HnA5CQ7NyiT35CJJCvHA2pxTSJRnHtdnE/SQzhrUdnfihPM9dg56lS4+80MmQITz7u3PmXAHLyo9R8n0I/ToB2hLjJ55hhfPBaJUa11fWrHm+gikfh1fhgr75WxPL+5GRyXPhu89oUUI96t5Esv+H/UJrxvlvagzSirTLNX8axQampwckEs+2hiip9iTSg+D4/THuFEqzsm7TVW8pJoXJvt8kZKtlDIQ+DamtgIcCdiSdtFvq9PUKkecbPZWRIBjQAvAqg==
*/