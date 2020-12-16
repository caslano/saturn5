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
DhLkfUi/g+2WdM1s9RJ56neHxNbc48adXKf/RHiibXXTTP9Xub6MC+pd/7DwxNj2fUyvddbU7XjgBDl/1KqBhPaADN8K+v6bLTx/tu7F/7fr5VWysGye9z3qV8K3ADrQn/cESitxH1oTEXszvsjFI+1d6p4wxj+mf4ldwt9d+9m7WsJbrXHIcwP3x0nQ+RZZbXBG6cs8VDYrBt/sxQdjC60vn/P9OpE8q2P4Hu4Y5mzUmO/svu/i5K0B7w3ud/GbPTwHyRNPnt0x+n19szPcO174knz0JwMd9dL9LjOs9wgT7ED/yrx/fceQWk5j3Tp30nd1z30fL/yjoGWtT7p/Qzzve6XvcV59175roMeI13os8U6+n8cZ+mn2Aakt+W2b73K3gh7ohvemHfXvudK8wmKsTA5q3Iq0J+zzn5Pzje3uK6S17fO1Lr8t52db03ClQP24rCFFX1KHcq4SX7ZnOCMjnOFNDJ064HlnJm9UC8848FwMA210j3xzWnj0apYVzDhw347648DGO73jQHf6ho3tfiv5NQ30PNHXrRa+09zPkiDWMv6QZ4l6v3DsNMaAhm+L1Fa03ebFEkHt0ZdnCH8lX1v5ngnZ7euldUqvz5wmvK1sdQz56HfHtikyv6HrPkPONbfTL6Q76TrBenJBubRcYigXXE+/b+XtNN6vDB8Ong0FBzDT/p71nqy/+dpu+oJq7b63emcGWuvJ8hu8fcBrPwfUwLq61wHi2n5rA3ENX780cd79lhrRru4TyKDWpn5oZv825v28J3AbIy/fsUUuiuHVj11yvo1t3Zk26LW8Rjuz7nzX5jXNtj0c57+Wt2uKKpDH14F3eIaZT7130scn9HHA9NTpfYH9OWg+3Zc1wJ/Dx/7+HFj33Hp13BvvX8dmqKPLr450DRNkHZFet2l0ygl9w4D3h/uGMeqp2xPX075hTN8VrgT/uialgALUVYKjJ4+YMCG4OicZde6QcsK5DZMX/doJ5zY0rx6H/kj5oGw+4032dSyDqR9bbGQWCd5Uf5nBx2txabD6kepTpyt+YJ3Mviq3jX9ZW6Osaf5lVS9JQZUzbdcP9/tjltPUw4RE/3K6UM4M/3JeYrpQCVa2GT5lrvwRsvXowXGbMn8P3iy/MtNVUZBlzTL6wqOB+0Lw/XBfRXZ94VEbX0X72/rX8VvwlfjXEUNTd/2OncRXUYlxn39zYl9F4P3hvoqO2fgq+iaAr6J17ez1r9K/nhj1ZOaX5xWWBat7lT51WH4KdK+ivf1zuMq/vHStFNy9XRXkc7hq1w/3q3Si57DZJxR08K9jc9Sx2r+OZT+kT6je1QC/Srt+uF+lj4Pwq+S532K5EXZr5hQPqkb6GnedjcGRdNdS9rukniXlpQHqWcOyG2OuoN+LVd5xzNvUv2MsZzITdQE1RdvUspwclEkp+Zakx7UOfh/V8yuSpp39e7BP2VfLfKI5H6G/Sesx0MeSpmXQdZR+j2Uyx3H7O7mZZa9UUAXoa/Bav9F+a6Q9MIQx7pdsPffaSPjKZN/M+fbf8ZCX7/12sZ5nairnCq1BKFUOuO30Eunt59IoW6ecz8Pcak/k01P7AV0k8e795493BF8nzxxAG/s5APJldfLMAfQIag6gE65jzgGMkXBjyTPYcX/cb4L7phtTbzyT7dO3XCxj1qEqL84Xmffd6i70n8C2ngj6O9JV+7Q1XdGa7a3nZx4S3lFWqn1bIy9bP7PaB+weOR+HcrXQc2S/kbjWSN9c2uoA5L+5s6etYuzbinzOLp62ah9UWz3l01YfSTjKnK+Br9jg52vuk/TNTzoO9Ws3tNO7Ki3n+8zn9PEu/s+EHmps9oHbL9F89/PgnPM=
*/