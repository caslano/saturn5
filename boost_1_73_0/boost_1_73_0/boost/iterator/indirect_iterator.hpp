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
1IWdFkPqE+HqPosrRFCzDenGkdPUWj4mP29MtS7lwl9RCsCmzStpxfg+FDhS5VQbsryqYArLJLddyJzO+8qM/SxqEK10/mK1st7TWug6mYgSwsiiNQpuUALMKTUKPKZWldyEuSHpwUNfzVDaH2zJfawlaYVI6MnxOc3Pn1DOrLRj+jq/+Hh6eUFfj8/Ojk8uruj0Ax2fXMHWp/nJe+y3hCdD/LYx3MKzIVk3leRlcPjzfnA4mVpTTP9jNzwkJFUBeGmlWoZsc1bc2IpZ4Xujkoqj3spJ1TLfE1QIZliB+lAdmjvn1BiNbqgx7i2tkQlqU3Ns9w36sWIr3RqUAOa+Mlfo+pmldRhDR65RsNaisQxn5WZC8wWtOazwFTysmQrNAp9qybsGRZszarRxoQNrplS3ZQrrhhZHwFZiK2GnW1NyRoeNtq7bbp9mJXPfs7haJLGh45LV9AkNxuzorZfv+dnsFf0ZNv3VpAjXo/76elL0M476Gb/2I7/119/7GaeXZ7N/zjHpl8NgcNTfHI0OMD7EIJjvptYU6GonoCpUdIWg0aSq8FW3pFiN2P3s2+x5Nwmtp565Qb4hV46bhSwkq+j4y3xMaEhfFsNfQG9hvNAwi07jvg7YGVlS2aLRirC7k4PZ5dnnb9nsw/xz
*/