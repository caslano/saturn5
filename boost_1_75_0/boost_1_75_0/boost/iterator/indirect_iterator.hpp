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
5szGAUMm4XN7H/k2UOTe4iizVExwPfPIXb208kUiDlvz3/HPGsge0F6mNhuvfQOw0N94VIUmuJduVkKIyDAamRbDLpmPLhZoeh0DHB68wDcuvZ0Yx/E2uXyp5f2r2f1/U059q83XIvotWdrgHZjiUCwadrgat+3c+AdsUcNUvO7ecccevdT2hOJkX9q4EerCyymQh9q+YquTzsk/FeysdHMeJm0LTnpKfRffqWqADFK8vSsdDor0NvlH85P5wlHbj2g82IXxXDzud4fpLEy4X7rGUxcDuT8lRW/lG/3Tk79URt80UojoF/tHdH1zrqLlf2nu2y3RacrTYzOrUBAxbzkl8HCk2/smxtG3zPmRMupb0fEwQp7tsiR7cHBQtChMXuSNv597vvIsRWvEsumdfb1Ri28buCLulP129hpmKy8g6PCxp9uWMoYAcXc/hkyVj2GVLno5pqItHl+jfhG8Z5DbpDUPFDom61fFOZMuil5eJEW5BbX8rZ1VA2RpmhRtk4TSOYS1oBsHw1b45R0k5tT/I0JzqXS7PC6+tti7F8sXrF9kTa74ZTJQkrkhMER1OgljfowkeVSgNArusnz3QOjYhaMjpxS04y14JGQRrXz0pLvikUmYpS9xizgSB8dzzeNbFvPWFREgt8MdsjAFRNjo51nLoxxEKImZYpDcyenIJbMDhNRU/ar2IMMOkIDxbr1zQLs1n4dgI8b4
*/