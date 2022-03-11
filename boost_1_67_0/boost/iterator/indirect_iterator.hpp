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
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
*/