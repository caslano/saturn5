//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Pablo Halpern 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_HPP
#define BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/allocator_traits.hpp>
#include <boost/container/scoped_allocator_fwd.hpp>
#include <boost/container/detail/dispatch_uses_allocator.hpp>

#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/pair.hpp>
#include <boost/container/detail/type_traits.hpp>

#include <boost/move/adl_move_swap.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/utility_core.hpp>

#include <boost/core/no_exceptions_support.hpp>

namespace boost { namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace dtl {

template <typename Allocator>
struct is_scoped_allocator_imp
{
   typedef char yes_type;
   struct no_type{ char dummy[2]; };

   template <typename T>
   static yes_type test(typename T::outer_allocator_type*);

   template <typename T>
   static int test(...);

   static const bool value = (sizeof(yes_type) == sizeof(test<Allocator>(0)));
};

template<class MaybeScopedAlloc, bool = is_scoped_allocator_imp<MaybeScopedAlloc>::value >
struct outermost_allocator_type_impl
{
   typedef typename MaybeScopedAlloc::outer_allocator_type outer_type;
   typedef typename outermost_allocator_type_impl<outer_type>::type type;
};

template<class MaybeScopedAlloc>
struct outermost_allocator_type_impl<MaybeScopedAlloc, false>
{
   typedef MaybeScopedAlloc type;
};

template<class MaybeScopedAlloc, bool = is_scoped_allocator_imp<MaybeScopedAlloc>::value >
struct outermost_allocator_imp
{
   typedef MaybeScopedAlloc type;

   static type &get(MaybeScopedAlloc &a)
   {  return a;  }

   static const type &get(const MaybeScopedAlloc &a)
   {  return a;  }
};

template<class MaybeScopedAlloc>
struct outermost_allocator_imp<MaybeScopedAlloc, true>
{
   typedef typename MaybeScopedAlloc::outer_allocator_type outer_type;
   typedef typename outermost_allocator_type_impl<outer_type>::type type;

   static type &get(MaybeScopedAlloc &a)
   {  return outermost_allocator_imp<outer_type>::get(a.outer_allocator());  }

   static const type &get(const MaybeScopedAlloc &a)
   {  return outermost_allocator_imp<outer_type>::get(a.outer_allocator());  }
};

}  //namespace dtl {

template <typename Allocator>
struct is_scoped_allocator
   : dtl::is_scoped_allocator_imp<Allocator>
{};

template <typename Allocator>
struct outermost_allocator
   : dtl::outermost_allocator_imp<Allocator>
{};

template <typename Allocator>
typename outermost_allocator<Allocator>::type &
   get_outermost_allocator(Allocator &a)
{  return outermost_allocator<Allocator>::get(a);   }

template <typename Allocator>
const typename outermost_allocator<Allocator>::type &
   get_outermost_allocator(const Allocator &a)
{  return outermost_allocator<Allocator>::get(a);   }

namespace dtl {

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template <typename OuterAlloc, class ...InnerAllocs>
class scoped_allocator_adaptor_base
   : public OuterAlloc
{
   typedef allocator_traits<OuterAlloc> outer_traits_type;
   BOOST_COPYABLE_AND_MOVABLE(scoped_allocator_adaptor_base)

   public:
   template <class OuterA2>
   struct rebind_base
   {
      typedef scoped_allocator_adaptor_base<OuterA2, InnerAllocs...> other;
   };

   typedef OuterAlloc outer_allocator_type;
   typedef scoped_allocator_adaptor<InnerAllocs...>   inner_allocator_type;
   typedef allocator_traits<inner_allocator_type>     inner_traits_type;
   typedef scoped_allocator_adaptor
      <OuterAlloc, InnerAllocs...>                    scoped_allocator_type;
   typedef dtl::bool_<
      outer_traits_type::propagate_on_container_copy_assignment::value ||
      inner_allocator_type::propagate_on_container_copy_assignment::value
      > propagate_on_container_copy_assignment;
   typedef dtl::bool_<
      outer_traits_type::propagate_on_container_move_assignment::value ||
      inner_allocator_type::propagate_on_container_move_assignment::value
      > propagate_on_container_move_assignment;
   typedef dtl::bool_<
      outer_traits_type::propagate_on_container_swap::value ||
      inner_allocator_type::propagate_on_container_swap::value
      > propagate_on_container_swap;
   typedef dtl::bool_<
      outer_traits_type::is_always_equal::value &&
      inner_allocator_type::is_always_equal::value
      > is_always_equal;

   scoped_allocator_adaptor_base()
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs &...args)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      , m_inner(args...)
      {}

   scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      , m_inner(::boost::move(other.inner_allocator()))
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<OuterA2, InnerAllocs...>& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base
         <OuterA2, InnerAllocs...> BOOST_RV_REF_END other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   public:
   struct internal_type_t{};

   template <class OuterA2>
   scoped_allocator_adaptor_base
      ( internal_type_t
      , BOOST_FWD_REF(OuterA2) outerAlloc
      , const inner_allocator_type &inner)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      , m_inner(inner)
   {}

   public:

   scoped_allocator_adaptor_base &operator=
      (BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      m_inner = other.inner_allocator();
      return *this;
   }

   scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));
      m_inner = ::boost::move(other.inner_allocator());
      return *this;
   }

   void swap(scoped_allocator_adaptor_base &r)
   {
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());
      boost::adl_move_swap(this->m_inner, r.inner_allocator());
   }

   friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)
   {  l.swap(r);  }

   inner_allocator_type&       inner_allocator() BOOST_NOEXCEPT_OR_NOTHROW
      { return m_inner; }

   inner_allocator_type const& inner_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_inner; }

   outer_allocator_type      & outer_allocator() BOOST_NOEXCEPT_OR_NOTHROW
      { return static_cast<outer_allocator_type&>(*this); }

   const outer_allocator_type &outer_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return static_cast<const outer_allocator_type&>(*this); }

   scoped_allocator_type select_on_container_copy_construction() const
   {
      return scoped_allocator_type
         (internal_type_t()
         ,outer_traits_type::select_on_container_copy_construction(this->outer_allocator())
         ,inner_traits_type::select_on_container_copy_construction(this->inner_allocator())
         );
   }

   private:
   inner_allocator_type m_inner;
};

#else //#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

//Let's add a dummy first template parameter to allow creating
//specializations up to maximum InnerAlloc count
template <typename OuterAlloc, bool Dummy, BOOST_MOVE_CLASSDFLT9>
class scoped_allocator_adaptor_base;

//Specializations for the adaptor with InnerAlloc allocators

#define BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_BASE_CODE(N)\
template <typename OuterAlloc BOOST_MOVE_I##N BOOST_MOVE_CLASS##N>\
class scoped_allocator_adaptor_base<OuterAlloc, true, BOOST_MOVE_TARG##N>\
   : public OuterAlloc\
{\
   typedef allocator_traits<OuterAlloc> outer_traits_type;\
   BOOST_COPYABLE_AND_MOVABLE(scoped_allocator_adaptor_base)\
   \
   public:\
   template <class OuterA2>\
   struct rebind_base\
   {\
      typedef scoped_allocator_adaptor_base<OuterA2, true, BOOST_MOVE_TARG##N> other;\
   };\
   \
   typedef OuterAlloc outer_allocator_type;\
   typedef scoped_allocator_adaptor<BOOST_MOVE_TARG##N> inner_allocator_type;\
   typedef scoped_allocator_adaptor<OuterAlloc, BOOST_MOVE_TARG##N> scoped_allocator_type;\
   typedef allocator_traits<inner_allocator_type> inner_traits_type;\
   typedef dtl::bool_<\
      outer_traits_type::propagate_on_container_copy_assignment::value ||\
      inner_allocator_type::propagate_on_container_copy_assignment::value\
      > propagate_on_container_copy_assignment;\
   typedef dtl::bool_<\
      outer_traits_type::propagate_on_container_move_assignment::value ||\
      inner_allocator_type::propagate_on_container_move_assignment::value\
      > propagate_on_container_move_assignment;\
   typedef dtl::bool_<\
      outer_traits_type::propagate_on_container_swap::value ||\
      inner_allocator_type::propagate_on_container_swap::value\
      > propagate_on_container_swap;\
   \
   typedef dtl::bool_<\
      outer_traits_type::is_always_equal::value &&\
      inner_allocator_type::is_always_equal::value\
      > is_always_equal;\
   \
   scoped_allocator_adaptor_base(){}\
   \
   template <class OuterA2>\
   scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc, BOOST_MOVE_CREF##N)\
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))\
      , m_inner(BOOST_MOVE_ARG##N)\
      {}\
   \
   scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)\
      : outer_allocator_type(::boost::move(other.outer_allocator()))\
      , m_inner(::boost::move(other.inner_allocator()))\
      {}\
   \
   template <class OuterA2>\
   scoped_allocator_adaptor_base\
      (const scoped_allocator_adaptor_base<OuterA2, true, BOOST_MOVE_TARG##N>& other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   template <class OuterA2>\
   scoped_allocator_adaptor_base\
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base<OuterA2, true, BOOST_MOVE_TARG##N> BOOST_RV_REF_END other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   public:\
   struct internal_type_t{};\
   \
   template <class OuterA2>\
   scoped_allocator_adaptor_base\
      ( internal_type_t, BOOST_FWD_REF(OuterA2) outerAlloc, const inner_allocator_type &inner)\
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))\
      , m_inner(inner)\
   {}\
   \
   public:\
   scoped_allocator_adaptor_base &operator=\
      (BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)\
   {\
      outer_allocator_type::operator=(other.outer_allocator());\
      m_inner = other.inner_allocator();\
      return *this;\
   }\
   \
   scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)\
   {\
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));\
      m_inner = ::boost::move(other.inner_allocator());\
      return *this;\
   }\
   \
   void swap(scoped_allocator_adaptor_base &r)\
   {\
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());\
      boost::adl_move_swap(this->m_inner, r.inner_allocator());\
   }\
   \
   friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)\
   {  l.swap(r);  }\
   \
   inner_allocator_type&       inner_allocator()\
      { return m_inner; }\
   \
   inner_allocator_type const& inner_allocator() const\
      { return m_inner; }\
   \
   outer_allocator_type      & outer_allocator()\
      { return static_cast<outer_allocator_type&>(*this); }\
   \
   const outer_allocator_type &outer_allocator() const\
      { return static_cast<const outer_allocator_type&>(*this); }\
   \
   scoped_allocator_type select_on_container_copy_construction() const\
   {\
      return scoped_allocator_type\
         (internal_type_t()\
         ,outer_traits_type::select_on_container_copy_construction(this->outer_allocator())\
         ,inner_traits_type::select_on_container_copy_construction(this->inner_allocator())\
         );\
   }\
   private:\
   inner_allocator_type m_inner;\
};\
//!
BOOST_MOVE_ITERATE_1TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_BASE_CODE)
#undef BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_BASE_CODE

#endif   //#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   #define BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE      ,true
   #define BOOST_CONTAINER_SCOPEDALLOC_ALLINNER       BOOST_MOVE_TARG9
   #define BOOST_CONTAINER_SCOPEDALLOC_ALLINNERCLASS  BOOST_MOVE_CLASS9
#else
   #define BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE
   #define BOOST_CONTAINER_SCOPEDALLOC_ALLINNER       InnerAllocs...
   #define BOOST_CONTAINER_SCOPEDALLOC_ALLINNERCLASS  typename... InnerAllocs
#endif

//Specialization for adaptor without any InnerAlloc
template <typename OuterAlloc>
class scoped_allocator_adaptor_base< OuterAlloc BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE>
   : public OuterAlloc
{
   BOOST_COPYABLE_AND_MOVABLE(scoped_allocator_adaptor_base)
   public:

   template <class U>
   struct rebind_base
   {
      typedef scoped_allocator_adaptor_base
         <typename allocator_traits<OuterAlloc>::template portable_rebind_alloc<U>::type
         BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE > other;
   };

   typedef OuterAlloc                           outer_allocator_type;
   typedef allocator_traits<OuterAlloc>         outer_traits_type;
   typedef scoped_allocator_adaptor<OuterAlloc> inner_allocator_type;
   typedef inner_allocator_type                 scoped_allocator_type;
   typedef allocator_traits<inner_allocator_type>   inner_traits_type;
   typedef typename outer_traits_type::
      propagate_on_container_copy_assignment    propagate_on_container_copy_assignment;
   typedef typename outer_traits_type::
      propagate_on_container_move_assignment    propagate_on_container_move_assignment;
   typedef typename outer_traits_type::
      propagate_on_container_swap               propagate_on_container_swap;
   typedef typename outer_traits_type::
      is_always_equal                           is_always_equal;

   scoped_allocator_adaptor_base()
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      {}

   scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      {}

   scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<OuterA2 BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE>& other)
      : outer_allocator_type(other.outer_allocator())
      {}

   template <class OuterA2>
   scoped_allocator_adaptor_base
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base<OuterA2 BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE> BOOST_RV_REF_END other)
      : outer_allocator_type(other.outer_allocator())
      {}

   public:
   struct internal_type_t{};

   template <class OuterA2>
   scoped_allocator_adaptor_base(internal_type_t, BOOST_FWD_REF(OuterA2) outerAlloc, const inner_allocator_type &)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      {}

   public:
   scoped_allocator_adaptor_base &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      return *this;
   }

   scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));
      return *this;
   }

   void swap(scoped_allocator_adaptor_base &r)
   {
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());
   }

   friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)
   {  l.swap(r);  }

   inner_allocator_type&       inner_allocator()
      { return static_cast<inner_allocator_type&>(*this); }

   inner_allocator_type const& inner_allocator() const
      { return static_cast<const inner_allocator_type&>(*this); }

   outer_allocator_type      & outer_allocator()
      { return static_cast<outer_allocator_type&>(*this); }

   const outer_allocator_type &outer_allocator() const
      { return static_cast<const outer_allocator_type&>(*this); }

   scoped_allocator_type select_on_container_copy_construction() const
   {
      return scoped_allocator_type
         (internal_type_t()
         ,outer_traits_type::select_on_container_copy_construction(this->outer_allocator())
         //Don't use inner_traits_type::select_on_container_copy_construction(this->inner_allocator())
         //as inner_allocator() is equal to *this and that would trigger an infinite loop
         , this->inner_allocator()
         );
   }
};

}  //namespace dtl {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//Scoped allocator
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

#if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

//! This class is a C++03-compatible implementation of std::scoped_allocator_adaptor.
//! The class template scoped_allocator_adaptor is an allocator template that specifies
//! the memory resource (the outer allocator) to be used by a container (as any other
//! allocator does) and also specifies an inner allocator resource to be passed to
//! the constructor of every element within the container.
//!
//! This adaptor is
//! instantiated with one outer and zero or more inner allocator types. If
//! instantiated with only one allocator type, the inner allocator becomes the
//! scoped_allocator_adaptor itself, thus using the same allocator resource for the
//! container and every element within the container and, if the elements themselves
//! are containers, each of their elements recursively. If instantiated with more than
//! one allocator, the first allocator is the outer allocator for use by the container,
//! the second allocator is passed to the constructors of the container's elements,
//! and, if the elements themselves are containers, the third allocator is passed to
//! the elements' elements, and so on. If containers are nested to a depth greater
//! than the number of allocators, the last allocator is used repeatedly, as in the
//! single-allocator case, for any remaining recursions.
//!
//! [<b>Note</b>: The
//! scoped_allocator_adaptor is derived from the outer allocator type so it can be
//! substituted for the outer allocator type in most expressions. -end note]
//!
//! In the construct member functions, <code>OUTERMOST(x)</code> is x if x does not have
//! an <code>outer_allocator()</code> member function and
//! <code>OUTERMOST(x.outer_allocator())</code> otherwise; <code>OUTERMOST_ALLOC_TRAITS(x)</code> is
//! <code>allocator_traits<decltype(OUTERMOST(x))></code>.
//!
//! [<b>Note</b>: <code>OUTERMOST(x)</code> and
//! <code>OUTERMOST_ALLOC_TRAITS(x)</code> are recursive operations. It is incumbent upon
//! the definition of <code>outer_allocator()</code> to ensure that the recursion terminates.
//! It will terminate for all instantiations of scoped_allocator_adaptor. -end note]
template <typename OuterAlloc, typename ...InnerAllocs>
class scoped_allocator_adaptor

#else // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

template <typename OuterAlloc, typename ...InnerAllocs>
class scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>

#endif   // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

#else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template <typename OuterAlloc, BOOST_MOVE_CLASS9>
class scoped_allocator_adaptor
#endif

   : public dtl::scoped_allocator_adaptor_base
         <OuterAlloc BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>
{
   BOOST_COPYABLE_AND_MOVABLE(scoped_allocator_adaptor)

   public:
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef dtl::scoped_allocator_adaptor_base
      <OuterAlloc BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> base_type;
   typedef typename base_type::internal_type_t              internal_type_t;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef OuterAlloc                                       outer_allocator_type;
   //! Type: For exposition only
   //!
   typedef allocator_traits<OuterAlloc>                     outer_traits_type;
   //! Type: <code>scoped_allocator_adaptor<OuterAlloc></code> if <code>sizeof...(InnerAllocs)</code> is zero; otherwise,
   //! <code>scoped_allocator_adaptor<InnerAllocs...></code>.
   typedef typename base_type::inner_allocator_type         inner_allocator_type;
   typedef allocator_traits<inner_allocator_type>           inner_traits_type;
   typedef typename outer_traits_type::value_type           value_type;
   typedef typename outer_traits_type::size_type            size_type;
   typedef typename outer_traits_type::difference_type      difference_type;
   typedef typename outer_traits_type::pointer              pointer;
   typedef typename outer_traits_type::const_pointer        const_pointer;
   typedef typename outer_traits_type::void_pointer         void_pointer;
   typedef typename outer_traits_type::const_void_pointer   const_void_pointer;
   //! Type: A type with a constant boolean <code>value</code> == true if
   //!`allocator_traits<Allocator>:: propagate_on_container_copy_assignment::value` is
   //! true for any <code>Allocator</code> in the set of <code>OuterAlloc</code> and <code>InnerAllocs...</code>, false otherwise.
   typedef typename base_type::
      propagate_on_container_copy_assignment                propagate_on_container_copy_assignment;
   //! Type: A type with a constant boolean <code>value</code> == true if
   //!`allocator_traits<Allocator>:: propagate_on_container_move_assignment::value` is
   //! true for any <code>Allocator</code> in the set of <code>OuterAlloc</code> and <code>InnerAllocs...</code>, false otherwise.
   typedef typename base_type::
      propagate_on_container_move_assignment                propagate_on_container_move_assignment;

   //! Type: A type with a constant boolean <code>value</code> == true if
   //! `allocator_traits<Allocator>:: propagate_on_container_swap::value` is
   //! true for any <code>Allocator</code> in the set of <code>OuterAlloc</code> and <code>InnerAllocs...</code>, false otherwise.
   typedef typename base_type::
      propagate_on_container_swap                           propagate_on_container_swap;

   //! Type: A type with a constant boolean <code>value</code> == true if
   //!`allocator_traits<Allocator>:: is_always_equal::value` is
   //! true for all <code>Allocator</code> in the set of <code>OuterAlloc</code> and <code>InnerAllocs...</code>, false otherwise.
   typedef typename base_type::
      is_always_equal                           is_always_equal;

   //! Type: Rebinds scoped allocator to
   //!    <code>typedef scoped_allocator_adaptor
   //!      < typename outer_traits_type::template portable_rebind_alloc<U>::type
   //!      , InnerAllocs... ></code>
   template <class U>
   struct rebind
   {
      typedef scoped_allocator_adaptor
         < typename outer_traits_type::template portable_rebind_alloc<U>::type
         , BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> other;
   };

   //! <b>Effects</b>: value-initializes the OuterAlloc base class
   //! and the inner allocator object.
   scoped_allocator_adaptor()
      {}

   ~scoped_allocator_adaptor()
      {}

   //! <b>Effects</b>: initializes each allocator within the adaptor with
   //! the corresponding allocator from other.
   scoped_allocator_adaptor(const scoped_allocator_adaptor& other)
      : base_type(other.base())
      {}

   //! <b>Effects</b>: move constructs each allocator within the adaptor with
   //! the corresponding allocator from other.
   scoped_allocator_adaptor(BOOST_RV_REF(scoped_allocator_adaptor) other)
      : base_type(::boost::move(other.base()))
      {}

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Requires</b>: OuterAlloc shall be constructible from OuterA2.
   //!
   //! <b>Effects</b>: initializes the OuterAlloc base class with boost::forward<OuterA2>(outerAlloc) and inner
   //! with innerAllocs...(hence recursively initializing each allocator within the adaptor with the
   //! corresponding allocator from the argument list).
   template <class OuterA2>
   scoped_allocator_adaptor(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs & ...innerAllocs)
      : base_type(::boost::forward<OuterA2>(outerAlloc), innerAllocs...)
      {}
   #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #define BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_RELATED_ALLOCATOR_CONSTRUCTOR_CODE(N)\
   template <class OuterA2>\
   scoped_allocator_adaptor(BOOST_FWD_REF(OuterA2) outerAlloc BOOST_MOVE_I##N BOOST_MOVE_CREF##N)\
      : base_type(::boost::forward<OuterA2>(outerAlloc) BOOST_MOVE_I##N BOOST_MOVE_ARG##N)\
      {}\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_RELATED_ALLOCATOR_CONSTRUCTOR_CODE)
   #undef BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_RELATED_ALLOCATOR_CONSTRUCTOR_CODE

   #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Requires</b>: OuterAlloc shall be constructible from OuterA2.
   //!
   //! <b>Effects</b>: initializes each allocator within the adaptor with the corresponding allocator from other.
   template <class OuterA2>
   scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> &other)
      : base_type(other.base())
      {}

   //! <b>Requires</b>: OuterAlloc shall be constructible from OuterA2.
   //!
   //! <b>Effects</b>: initializes each allocator within the adaptor with the corresponding allocator
   //! rvalue from other.
   template <class OuterA2>
   scoped_allocator_adaptor(BOOST_RV_REF_BEG scoped_allocator_adaptor
      <OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> BOOST_RV_REF_END other)
      : base_type(::boost::move(other.base()))
      {}

   scoped_allocator_adaptor &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor) other)
   {  return static_cast<scoped_allocator_adaptor&>(base_type::operator=(static_cast<const base_type &>(other))); }

   scoped_allocator_adaptor &operator=(BOOST_RV_REF(scoped_allocator_adaptor) other)
   {  return static_cast<scoped_allocator_adaptor&>(base_type::operator=(boost::move(other.base()))); }

   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   //! <b>Effects</b>: swaps *this with r.
   //!
   void swap(scoped_allocator_adaptor &r);

   //! <b>Effects</b>: swaps *this with r.
   //!
   friend void swap(scoped_allocator_adaptor &l, scoped_allocator_adaptor &r);

   //! <b>Returns</b>:
   //!   <code>static_cast<OuterAlloc&>(*this)</code>.
   outer_allocator_type      & outer_allocator() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Returns</b>:
   //!   <code>static_cast<const OuterAlloc&>(*this)</code>.
   const outer_allocator_type &outer_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Returns</b>:
   //!   *this if <code>sizeof...(InnerAllocs)</code> is zero; otherwise, inner.
   inner_allocator_type&       inner_allocator() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Returns</b>:
   //!   *this if <code>sizeof...(InnerAllocs)</code> is zero; otherwise, inner.
   inner_allocator_type const& inner_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   #endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

   //! <b>Returns</b>:
   //!   <code>allocator_traits<OuterAlloc>:: max_size(outer_allocator())</code>.
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return outer_traits_type::max_size(this->outer_allocator());   }

   //! <b>Effects</b>:
   //!   calls <code>OUTERMOST_ALLOC_TRAITS(*this):: destroy(OUTERMOST(*this), p)</code>.
   template <class T>
   void destroy(T* p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      allocator_traits<typename outermost_allocator<OuterAlloc>::type>
         ::destroy(get_outermost_allocator(this->outer_allocator()), p);
   }

   //! <b>Returns</b>:
   //! <code>allocator_traits<OuterAlloc>::allocate(outer_allocator(), n)</code>.
   pointer allocate(size_type n)
   {  return outer_traits_type::allocate(this->outer_allocator(), n);   }

   //! <b>Returns</b>:
   //! <code>allocator_traits<OuterAlloc>::allocate(outer_allocator(), n, hint)</code>.
   pointer allocate(size_type n, const_void_pointer hint)
   {  return outer_traits_type::allocate(this->outer_allocator(), n, hint);   }

   //! <b>Effects</b>:
   //! <code>allocator_traits<OuterAlloc>::deallocate(outer_allocator(), p, n)</code>.
   void deallocate(pointer p, size_type n)
   {  outer_traits_type::deallocate(this->outer_allocator(), p, n);  }

   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   //! <b>Returns</b>: A new scoped_allocator_adaptor object where each allocator
   //! Allocator in the adaptor is initialized from the result of calling
   //! <code>allocator_traits<Allocator>::select_on_container_copy_construction()</code> on
   //! the corresponding allocator in *this.
   scoped_allocator_adaptor select_on_container_copy_construction() const;
   #endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   base_type &base()             { return *this; }

   const base_type &base() const { return *this; }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>:
   //! 1) If <code>uses_allocator<T, inner_allocator_type>::value</code> is false calls
   //!    <code>OUTERMOST_ALLOC_TRAITS(*this)::
   //!       construct(OUTERMOST(*this), p, std::forward<Args>(args)...)</code>.
   //!
   //! 2) Otherwise, if <code>uses_allocator<T, inner_allocator_type>::value</code> is true and
   //!    <code>is_constructible<T, allocator_arg_t, inner_allocator_type, Args...>:: value</code> is true, calls
   //!    <code>OUTERMOST_ALLOC_TRAITS(*this):: construct(OUTERMOST(*this), p, allocator_arg,
   //!    inner_allocator(), std::forward<Args>(args)...)</code>.
   //!
   //! [<b>Note</b>: In compilers without advanced decltype SFINAE support, <code>is_constructible</code> can't
   //! be implemented so that condition will be replaced by
   //! constructible_with_allocator_prefix<T>::value. -end note]
   //!
   //! 3) Otherwise, if uses_allocator<T, inner_allocator_type>::value is true and
   //!    <code>is_constructible<T, Args..., inner_allocator_type>:: value</code> is true, calls
   //!    <code>OUTERMOST_ALLOC_TRAITS(*this):: construct(OUTERMOST(*this), p,
   //!    std::forward<Args>(args)..., inner_allocator())</code>.
   //!
   //! [<b>Note</b>: In compilers without advanced decltype SFINAE support, <code>is_constructible</code> can't be
   //! implemented so that condition will be replaced by
   //! <code>constructible_with_allocator_suffix<T>:: value</code>. -end note]
   //!
   //! 4) Otherwise, the program is ill-formed.
   //!
   //! [<b>Note</b>: An error will result if <code>uses_allocator</code> evaluates
   //! to true but the specific constructor does not take an allocator. This definition prevents a silent
   //! failure to pass an inner allocator to a contained element. -end note]
   template < typename T, class ...Args>
   void construct(T* p, BOOST_FWD_REF(Args)...args)
   {
      dtl::dispatch_uses_allocator
         ( (get_outermost_allocator)(this->outer_allocator())
         , this->inner_allocator(), p, ::boost::forward<Args>(args)...);
   }

   #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //Disable this overload if the first argument is pair as some compilers have
   //overload selection problems when the first parameter is a pair.
   #define BOOST_CONTAINER_SCOPED_ALLOCATOR_CONSTRUCT_CODE(N) \
   template < typename T BOOST_MOVE_I##N BOOST_MOVE_CLASSQ##N >\
   void construct(T* p BOOST_MOVE_I##N BOOST_MOVE_UREFQ##N)\
   {\
      dtl::dispatch_uses_allocator\
         ( (get_outermost_allocator)(this->outer_allocator())\
         , this->inner_allocator(), p BOOST_MOVE_I##N BOOST_MOVE_FWDQ##N);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SCOPED_ALLOCATOR_CONSTRUCT_CODE)
   #undef BOOST_CONTAINER_SCOPED_ALLOCATOR_CONSTRUCT_CODE

   #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //Internal function
   template <class OuterA2>
   scoped_allocator_adaptor(internal_type_t, BOOST_FWD_REF(OuterA2) outer, const inner_allocator_type& inner)
      : base_type(internal_type_t(), ::boost::forward<OuterA2>(outer), inner)
   {}

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

/// @cond

template<bool ZeroInner>
struct scoped_allocator_operator_equal
{
   //Optimize equal outer allocator types with 
   //allocator_traits::equal which uses is_always_equal
   template<class IA>
   static bool equal_outer(const IA &l, const IA &r)
   {  return allocator_traits<IA>::equal(l, r);  }

   //Otherwise compare it normally
   template<class IA1, class IA2>
   static bool equal_outer(const IA1 &l, const IA2 &r)
   {  return l == r;  }

   //Otherwise compare it normally
   template<class IA>
   static bool equal_inner(const IA &l, const IA &r)
   {  return allocator_traits<IA>::equal(l, r);  }
};

template<>
struct scoped_allocator_operator_equal<true>
   : scoped_allocator_operator_equal<false>
{
   //when inner allocator count is zero,
   //inner_allocator_type is the same as outer_allocator_type
   //so both types can be different in operator==
   template<class IA1, class IA2>
   static bool equal_inner(const IA1 &, const IA2 &)
   {  return true;  }
};

/// @endcond

template <typename OuterA1, typename OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNERCLASS>
inline bool operator==(const scoped_allocator_adaptor<OuterA1, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& a
                      ,const scoped_allocator_adaptor<OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& b)
{
   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   const bool has_zero_inner = sizeof...(InnerAllocs) == 0u;
   #else
   const bool has_zero_inner = boost::container::dtl::is_same<P0, void>::value;
   #endif
   typedef scoped_allocator_operator_equal<has_zero_inner> equal_t;
   return equal_t::equal_outer(a.outer_allocator(), b.outer_allocator()) &&
          equal_t::equal_inner(a.inner_allocator(), b.inner_allocator());
}

template <typename OuterA1, typename OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNERCLASS>
inline bool operator!=(const scoped_allocator_adaptor<OuterA1, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& a
                      ,const scoped_allocator_adaptor<OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& b)
{  return !(a == b);   }

}} // namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //  BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_HPP

/* scoped_allocator.hpp
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
*/