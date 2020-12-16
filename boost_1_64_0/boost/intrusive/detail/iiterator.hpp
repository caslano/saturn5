/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/iterator.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>

namespace boost {
namespace intrusive {

template<class ValueTraits>
struct value_traits_pointers
{
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      (boost::intrusive::detail::
      , ValueTraits, value_traits_ptr
      , typename boost::intrusive::pointer_traits<typename ValueTraits::node_traits::node_ptr>::template
         rebind_pointer<ValueTraits>::type)   value_traits_ptr;

   typedef typename boost::intrusive::pointer_traits<value_traits_ptr>::template
      rebind_pointer<ValueTraits const>::type const_value_traits_ptr;
};

template<class ValueTraits, bool IsConst, class Category>
struct iiterator
{
   typedef ValueTraits                                         value_traits;
   typedef typename value_traits::node_traits                  node_traits;
   typedef typename node_traits::node                          node;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef ::boost::intrusive::pointer_traits<node_ptr>        nodepointer_traits_t;
   typedef typename nodepointer_traits_t::template
      rebind_pointer<void>::type                               void_pointer;
   typedef typename ValueTraits::value_type                    value_type;
   typedef typename ValueTraits::pointer                       nonconst_pointer;
   typedef typename ValueTraits::const_pointer                 yesconst_pointer;
   typedef typename ::boost::intrusive::pointer_traits
      <nonconst_pointer>::reference                            nonconst_reference;
   typedef typename ::boost::intrusive::pointer_traits
      <yesconst_pointer>::reference                            yesconst_reference;
   typedef typename nodepointer_traits_t::difference_type      difference_type;
   typedef typename detail::if_c
      <IsConst, yesconst_pointer, nonconst_pointer>::type      pointer;
   typedef typename detail::if_c
      <IsConst, yesconst_reference, nonconst_reference>::type  reference;
   typedef iterator
         < Category
         , value_type
         , difference_type
         , pointer
         , reference
         > iterator_type;
   typedef typename value_traits_pointers
      <ValueTraits>::value_traits_ptr                          value_traits_ptr;
   typedef typename value_traits_pointers
      <ValueTraits>::const_value_traits_ptr                    const_value_traits_ptr;
   static const bool stateful_value_traits =
      detail::is_stateful_value_traits<value_traits>::value;
};

template<class NodePtr, class StoredPointer, bool StatefulValueTraits = true>
struct iiterator_members
{

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &data)
      :  nodeptr_(n_ptr), ptr_(data)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return ptr_;  }

   NodePtr nodeptr_;
   StoredPointer ptr_;
};

template<class NodePtr, class StoredPointer>
struct iiterator_members<NodePtr, StoredPointer, false>
{
   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &)
      : nodeptr_(n_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return StoredPointer();  }

   NodePtr nodeptr_;
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

/* iiterator.hpp
8dwrfB87s4ix6GJiObXll1apnFzwbuHr5lY4Pa16qnKIU18d7R/Tp+dbwvMm88x3+mdNfiBxAUm3alBbuqNV917FRu9d65fddu0ovbZHr91ipDtSr73Btbb3W9aZGmudB80On2k7AH1MdcLvo4Np+EOiSXS0wEnW1yVeX/ua+mr2T+w7g9Hmqm9S71WeLKM9iJc69zP0/yiN9+p7i8F/pKO+l9K+7JM+KPqZsEsrMw9yobnQrfA45b6+4sfRVCXf3HWVxjeLFNKqk6T1deC03PAac03v60Cu8Exzpjiuf+7qfci9B1oLtWR37O+pba1tJ+VR3ww9CzpHbYKaaCl0u3cvttWtqaEm8f13bXn4/juI+288ZL3/ymPH8IpLK23jvcGbAW+O+oJY7iGTT5+p9dbx3eT7KxE8P6zjOnzmuM6PdRRVZd4A6Z9P+4LwBM3vM2jfxuecqLXdtIexP2uO+q144Wz/Oc0Z1joWUw/Cc6O/w3Xz2yNVR4uh1eRXOEf7kZuJIbVuiSoZl33dcw3di6x1P1TSjbT2JzJNPxZ0EUpCF/O1Hbw884w8zXqszQ0nmKUJZ+p8wuy2ejTX78P8FOlt8wn+GotKuZ5v00nSxozXkpaHVP0S3+9vrvBMpd27+ed93yP6se/P8A6+lZFrb6vtZlvtw9zL9g7aakc7bbU9ibb61afQVrMPUt8PN1zO4eAK0pdUGG21D/MKJRUd71ExQXgKre1F+sTzDIaMxcKXa3/vrUg47+CnX6fpLWMk6e3zELEytqkM63txRfLzEiUVHb+nx74Xm2nMdybRLOO96QzhO9jd6+CB6/MabaoJIvOIk4W/r/u+EzJkR9rP11up7xTh7ef+y3EN2dpWJr++T5YKf4H7Lpp4OHqeoXpuUgu0Nooscy7WM7FTen1YEfED7tw3wH/THMzmfv66FvmV6RxMa6VxX+7DHAzp270vc8CtlQnHMdIn/93ZWtmxPsfcc6Tp3Hdna2XnvjtbKzu+X3qBPxC+cxmLUw/YWPxpfXuaejVzQLiQFVrYOZH5iypDr/Zl/qKqY72aUJVQr0ifvF6VVHVer0qqOqdXJVWd06uSqk7OZ1Qlp4enCd+sA/pO8GnpoX0OJPq7a/RA/lEfLhc6EZrijXu+fs5tqKqyrJvS59wzwjfGPvb5fXRWrwu5D16FnuNiVvd0f15pVK+wHSfS1mW98WPLS+493tbW5h5jbwyMfmb1hKrhzZ4bqdu8qqbiMn3w+K+m0T70hm7kSrpMNMO11Re5ya0L0HIbPvPR5V5VGG3H6qblLo4uN4u4eRolLrd9HfB+ljEyF7FnkPrWqt7UQV8iriS6jGEFTvJ9v0TLZq6/yFc9O1WuXeIM5N9Sq61V06u+3UYbzvS+QTx9yxzh69tutRv2VZ7F8Dzp8QSmpWYGs1NTs4Jpoo96fS3Xf+5dzzrXl/G2yoj+/t63NZU9or6/q6P04MHB/l5a/EiverDd1sZJ6O8OLx1XMxPo7/aOdeMMq27EPPMuPETLq4l6abl3R5ebAckvdXSZjWfYHi2z1b7VcXnHJVPevYfE329f9caJeWZ524wtye7FkD2vc+VLNI6tVcfcXCiiD/fAW2iWr0x9box5lYi+/kKeW9PFP+eKL3iFjfHPMb7vDhWZ6R3qgDkWLD3UWFeluN4bC6LKV7U40ngZfts12NqNdLHvJtWVi63zdD6vX9eZvTt+RveIau+GmDkw8orRj/5D4vXjEtKWmvXTbwN5iic5Fpd2Uj8SjcWbh/jl8vcpuZfyzTbLp3qRrO7O7mTZEulu/dA43aXtiI8qmw5h+urS3hjWJOl6JhzD6jtZ7kTP4GHD7OVeZSs3r2I=
*/