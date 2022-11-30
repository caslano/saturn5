/* Copyright 2003-2022 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_AUTO_SPACE_HPP
#define BOOST_MULTI_INDEX_DETAIL_AUTO_SPACE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <memory>

namespace boost{

namespace multi_index{

namespace detail{

/* auto_space provides uninitialized space suitably to store
 * a given number of elements of a given type.
 */

/* NB: it is not clear whether using an allocator to handle
 * zero-sized arrays of elements is conformant or not. GCC 3.3.1
 * and prior fail here, other stdlibs handle the issue gracefully.
 * To be on the safe side, the case n==0 is given special treatment.
 * References:
 *   GCC Bugzilla, "standard allocator crashes when deallocating segment
 *    "of zero length", http://gcc.gnu.org/bugzilla/show_bug.cgi?id=14176
 *   C++ Standard Library Defect Report List (Revision 28), issue 199
 *     "What does allocate(0) return?",
 *     http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#199
 */

template<typename T,typename Allocator=std::allocator<T> >
struct auto_space:private noncopyable
{
  typedef typename rebind_alloc_for<
    Allocator,T>
  ::type                                   allocator;
  typedef allocator_traits<allocator>      alloc_traits;
  typedef typename alloc_traits::pointer   pointer;
  typedef typename alloc_traits::size_type size_type;

  explicit auto_space(const Allocator& al=Allocator(),size_type n=1):
  al_(al),n_(n),data_(n_?alloc_traits::allocate(al_,n_):pointer(0))
  {}

  ~auto_space(){if(n_)alloc_traits::deallocate(al_,data_,n_);}

  Allocator get_allocator()const{return al_;}

  pointer data()const{return data_;}

  void swap(auto_space& x)
  {
    swap(
      x,
      boost::integral_constant<
        bool,alloc_traits::propagate_on_container_swap::value>());
  }

  void swap(auto_space& x,boost::true_type /* swap_allocators */)
  {
    adl_swap(al_,x.al_);
    std::swap(n_,x.n_);
    std::swap(data_,x.data_);
  }
    
  void swap(auto_space& x,boost::false_type /* swap_allocators */)
  {
    std::swap(n_,x.n_);
    std::swap(data_,x.data_);
  }

private:
  allocator al_;
  size_type n_;
  pointer   data_;
};

template<typename T,typename Allocator>
void swap(auto_space<T,Allocator>& x,auto_space<T,Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* auto_space.hpp
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
*/