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
# if BOOST_WORKAROUND(BOOST_BORLANDC, < 0x5A0 )
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