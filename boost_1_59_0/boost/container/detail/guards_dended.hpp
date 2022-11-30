//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Benedek Thaler 2015-2016
// (C) Copyright Ion Gaztanaga 2019-2020. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://erenon.hu/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_GUARDS_HPP
#define BOOST_CONTAINER_DETAIL_GUARDS_HPP

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/move/core.hpp> // BOOST_MOVABLE_BUT_NOT_COPYABLE

// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

#include <boost/container/allocator_traits.hpp>

namespace boost {
namespace container {
namespace detail {

class null_construction_guard
{
public:

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   template <typename... Args>
   null_construction_guard(Args&&...) {}

   #else

   #define NULL_CONSTRUCTION_GUARD_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE null_construction_guard(BOOST_MOVE_UREFANON##N)\
   {}\
   //
   BOOST_MOVE_ITERATE_0TO9(NULL_CONSTRUCTION_GUARD_CODE)
   #undef NULL_CONSTRUCTION_GUARD_CODE
   #endif

   void release() {}
   void extend() {}
};

template <typename Allocator>
class construction_guard
{
  typedef typename boost::container::allocator_traits<Allocator>::pointer pointer;
  typedef typename boost::container::allocator_traits<Allocator>::size_type size_type;

  BOOST_MOVABLE_BUT_NOT_COPYABLE(construction_guard)

public:
   construction_guard()
      : _alloc_ptr()
      , _elem_count()
      , _allocator()
   {}

  construction_guard(pointer alloc_ptr, Allocator& allocator)
      :_alloc_ptr(alloc_ptr)
      , _elem_count(0)
      , _allocator(&allocator)
  {}

  construction_guard(BOOST_RV_REF(construction_guard) rhs)
      :_alloc_ptr(rhs._alloc_ptr)
      , _elem_count(rhs._elem_count)
      , _allocator(rhs._allocator)
  {
    rhs._elem_count = 0;
  }

  ~construction_guard()
  {
    while (_elem_count) {
      --_elem_count;
      boost::container::allocator_traits<Allocator>::destroy(*_allocator, _alloc_ptr++);
    }
  }

  void release()
  {
    _elem_count = 0;
  }

  void extend()
  {
    ++_elem_count;
  }

private:
  pointer _alloc_ptr;
  size_type _elem_count;
  Allocator* _allocator;
};


/**
 * Has two ranges
 *
 * On success, destroys the first range (src),
 * on failure, destroys the second range (dst).
 *
 * Can be used when copying/moving a range
 */
template <class Allocator>
class nand_construction_guard
{
   typedef typename boost::container::allocator_traits<Allocator>::pointer pointer;
   typedef typename boost::container::allocator_traits<Allocator>::size_type size_type;

   construction_guard<Allocator> _src;
   construction_guard<Allocator> _dst;
   bool _dst_released;

   public:
   nand_construction_guard()
      : _src()
      , _dst()
      , _dst_released(false)
   {}

   nand_construction_guard( pointer src, Allocator& src_alloc
                          , pointer dst, Allocator& dst_alloc)
    :_src(src, src_alloc),
     _dst(dst, dst_alloc),
     _dst_released(false)
   {}

   void extend()
   {
      _src.extend();
      _dst.extend();
   }

   void release() // on success
   {
      _dst.release();
      _dst_released = true;
   }

   ~nand_construction_guard()
   {
      if (! _dst_released) { _src.release(); }
   }
};


template <typename Allocator>
class allocation_guard
{
  typedef typename boost::container::allocator_traits<Allocator>::pointer pointer;
  typedef typename boost::container::allocator_traits<Allocator>::size_type size_type;

  BOOST_MOVABLE_BUT_NOT_COPYABLE(allocation_guard)

public:
  allocation_guard(pointer alloc_ptr, size_type alloc_size, Allocator& allocator)
    :_alloc_ptr(alloc_ptr),
     _alloc_size(alloc_size),
     _allocator(allocator)
  {}

  ~allocation_guard()
  {
    if (_alloc_ptr)
    {
      boost::container::allocator_traits<Allocator>::deallocate(_allocator, _alloc_ptr, _alloc_size);
    }
  }

  void release()
  {
    _alloc_ptr = 0;
  }

private:
  pointer _alloc_ptr;
  size_type _alloc_size;
  Allocator& _allocator;
};

}}} // namespace boost::container::detail

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_DETAIL_GUARDS_HPP

/* guards_dended.hpp
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
*/