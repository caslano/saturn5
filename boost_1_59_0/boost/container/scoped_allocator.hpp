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

   BOOST_CONTAINER_FORCEINLINE static type &get(MaybeScopedAlloc &a)
   {  return a;  }

   BOOST_CONTAINER_FORCEINLINE static const type &get(const MaybeScopedAlloc &a)
   {  return a;  }
};

template<class MaybeScopedAlloc>
struct outermost_allocator_imp<MaybeScopedAlloc, true>
{
   typedef typename MaybeScopedAlloc::outer_allocator_type outer_type;
   typedef typename outermost_allocator_type_impl<outer_type>::type type;

   BOOST_CONTAINER_FORCEINLINE static type &get(MaybeScopedAlloc &a)
   {  return outermost_allocator_imp<outer_type>::get(a.outer_allocator());  }

   BOOST_CONTAINER_FORCEINLINE static const type &get(const MaybeScopedAlloc &a)
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
BOOST_CONTAINER_FORCEINLINE typename outermost_allocator<Allocator>::type &
   get_outermost_allocator(Allocator &a)
{  return outermost_allocator<Allocator>::get(a);   }

template <typename Allocator>
BOOST_CONTAINER_FORCEINLINE const typename outermost_allocator<Allocator>::type &
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

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base()
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs &...args)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      , m_inner(args...)
      {}

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      , m_inner(::boost::move(other.inner_allocator()))
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<OuterA2, InnerAllocs...>& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base
         <OuterA2, InnerAllocs...> BOOST_RV_REF_END other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}

   public:
   struct internal_type_t{};

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base
      ( internal_type_t
      , BOOST_FWD_REF(OuterA2) outerAlloc
      , const inner_allocator_type &inner)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      , m_inner(inner)
   {}

   public:

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=
      (BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      m_inner = other.inner_allocator();
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));
      m_inner = ::boost::move(other.inner_allocator());
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE void swap(scoped_allocator_adaptor_base &r)
   {
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());
      boost::adl_move_swap(this->m_inner, r.inner_allocator());
   }

   BOOST_CONTAINER_FORCEINLINE friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)
   {  l.swap(r);  }

   BOOST_CONTAINER_FORCEINLINE inner_allocator_type&       inner_allocator() BOOST_NOEXCEPT_OR_NOTHROW
      { return m_inner; }

   BOOST_CONTAINER_FORCEINLINE inner_allocator_type const& inner_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_inner; }

   BOOST_CONTAINER_FORCEINLINE outer_allocator_type      & outer_allocator() BOOST_NOEXCEPT_OR_NOTHROW
      { return static_cast<outer_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE const outer_allocator_type &outer_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return static_cast<const outer_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_type select_on_container_copy_construction() const
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
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(){}\
   \
   template <class OuterA2>\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc, BOOST_MOVE_CREF##N)\
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))\
      , m_inner(BOOST_MOVE_ARG##N)\
      {}\
   \
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)\
      : outer_allocator_type(::boost::move(other.outer_allocator()))\
      , m_inner(::boost::move(other.inner_allocator()))\
      {}\
   \
   template <class OuterA2>\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base\
      (const scoped_allocator_adaptor_base<OuterA2, true, BOOST_MOVE_TARG##N>& other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   template <class OuterA2>\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base\
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base<OuterA2, true, BOOST_MOVE_TARG##N> BOOST_RV_REF_END other)\
      : outer_allocator_type(other.outer_allocator())\
      , m_inner(other.inner_allocator())\
      {}\
   \
   public:\
   struct internal_type_t{};\
   \
   template <class OuterA2>\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base\
      ( internal_type_t, BOOST_FWD_REF(OuterA2) outerAlloc, const inner_allocator_type &inner)\
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))\
      , m_inner(inner)\
   {}\
   \
   public:\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=\
      (BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)\
   {\
      outer_allocator_type::operator=(other.outer_allocator());\
      m_inner = other.inner_allocator();\
      return *this;\
   }\
   \
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)\
   {\
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));\
      m_inner = ::boost::move(other.inner_allocator());\
      return *this;\
   }\
   \
   BOOST_CONTAINER_FORCEINLINE void swap(scoped_allocator_adaptor_base &r)\
   {\
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());\
      boost::adl_move_swap(this->m_inner, r.inner_allocator());\
   }\
   \
   BOOST_CONTAINER_FORCEINLINE friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)\
   {  l.swap(r);  }\
   \
   BOOST_CONTAINER_FORCEINLINE inner_allocator_type&       inner_allocator()\
      { return m_inner; }\
   \
   BOOST_CONTAINER_FORCEINLINE inner_allocator_type const& inner_allocator() const\
      { return m_inner; }\
   \
   BOOST_CONTAINER_FORCEINLINE outer_allocator_type      & outer_allocator()\
      { return static_cast<outer_allocator_type&>(*this); }\
   \
   BOOST_CONTAINER_FORCEINLINE const outer_allocator_type &outer_allocator() const\
      { return static_cast<const outer_allocator_type&>(*this); }\
   \
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_type select_on_container_copy_construction() const\
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

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base()
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      {}

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      {}

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<OuterA2 BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE>& other)
      : outer_allocator_type(other.outer_allocator())
      {}

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base
      (BOOST_RV_REF_BEG scoped_allocator_adaptor_base<OuterA2 BOOST_CONTAINER_SCOPEDALLOC_DUMMYTRUE> BOOST_RV_REF_END other)
      : outer_allocator_type(other.outer_allocator())
      {}

   public:
   struct internal_type_t{};

   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base(internal_type_t, BOOST_FWD_REF(OuterA2) outerAlloc, const inner_allocator_type &)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      {}

   public:
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor_base &operator=(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(boost::move(other.outer_allocator()));
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE void swap(scoped_allocator_adaptor_base &r)
   {
      boost::adl_move_swap(this->outer_allocator(), r.outer_allocator());
   }

   BOOST_CONTAINER_FORCEINLINE friend void swap(scoped_allocator_adaptor_base &l, scoped_allocator_adaptor_base &r)
   {  l.swap(r);  }

   BOOST_CONTAINER_FORCEINLINE inner_allocator_type&       inner_allocator()
      { return static_cast<inner_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE inner_allocator_type const& inner_allocator() const
      { return static_cast<const inner_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE outer_allocator_type      & outer_allocator()
      { return static_cast<outer_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE const outer_allocator_type &outer_allocator() const
      { return static_cast<const outer_allocator_type&>(*this); }

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_type select_on_container_copy_construction() const
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
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor()
      {}

   BOOST_CONTAINER_FORCEINLINE ~scoped_allocator_adaptor()
      {}

   //! <b>Effects</b>: initializes each allocator within the adaptor with
   //! the corresponding allocator from other.
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(const scoped_allocator_adaptor& other)
      : base_type(other.base())
      {}

   //! <b>Effects</b>: move constructs each allocator within the adaptor with
   //! the corresponding allocator from other.
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(BOOST_RV_REF(scoped_allocator_adaptor) other)
      : base_type(::boost::move(other.base()))
      {}

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Requires</b>: OuterAlloc shall be constructible from OuterA2.
   //!
   //! <b>Effects</b>: initializes the OuterAlloc base class with boost::forward<OuterA2>(outerAlloc) and inner
   //! with innerAllocs...(hence recursively initializing each allocator within the adaptor with the
   //! corresponding allocator from the argument list).
   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs & ...innerAllocs)
      : base_type(::boost::forward<OuterA2>(outerAlloc), innerAllocs...)
      {}
   #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #define BOOST_CONTAINER_SCOPED_ALLOCATOR_ADAPTOR_RELATED_ALLOCATOR_CONSTRUCTOR_CODE(N)\
   template <class OuterA2>\
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(BOOST_FWD_REF(OuterA2) outerAlloc BOOST_MOVE_I##N BOOST_MOVE_CREF##N)\
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
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> &other)
      : base_type(other.base())
      {}

   //! <b>Requires</b>: OuterAlloc shall be constructible from OuterA2.
   //!
   //! <b>Effects</b>: initializes each allocator within the adaptor with the corresponding allocator
   //! rvalue from other.
   template <class OuterA2>
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(BOOST_RV_REF_BEG scoped_allocator_adaptor
      <OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER> BOOST_RV_REF_END other)
      : base_type(::boost::move(other.base()))
      {}

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor) other)
   {  return static_cast<scoped_allocator_adaptor&>(base_type::operator=(static_cast<const base_type &>(other))); }

   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor &operator=(BOOST_RV_REF(scoped_allocator_adaptor) other)
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
   BOOST_CONTAINER_FORCEINLINE size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return outer_traits_type::max_size(this->outer_allocator());   }

   //! <b>Effects</b>:
   //!   calls <code>OUTERMOST_ALLOC_TRAITS(*this):: destroy(OUTERMOST(*this), p)</code>.
   template <class T>
   BOOST_CONTAINER_FORCEINLINE void destroy(T* p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      allocator_traits<typename outermost_allocator<OuterAlloc>::type>
         ::destroy(get_outermost_allocator(this->outer_allocator()), p);
   }

   //! <b>Returns</b>:
   //! <code>allocator_traits<OuterAlloc>::allocate(outer_allocator(), n)</code>.
   BOOST_CONTAINER_FORCEINLINE pointer allocate(size_type n)
   {  return outer_traits_type::allocate(this->outer_allocator(), n);   }

   //! <b>Returns</b>:
   //! <code>allocator_traits<OuterAlloc>::allocate(outer_allocator(), n, hint)</code>.
   BOOST_CONTAINER_FORCEINLINE pointer allocate(size_type n, const_void_pointer hint)
   {  return outer_traits_type::allocate(this->outer_allocator(), n, hint);   }

   //! <b>Effects</b>:
   //! <code>allocator_traits<OuterAlloc>::deallocate(outer_allocator(), p, n)</code>.
   BOOST_CONTAINER_FORCEINLINE void deallocate(pointer p, size_type n)
   {  outer_traits_type::deallocate(this->outer_allocator(), p, n);  }

   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   //! <b>Returns</b>: A new scoped_allocator_adaptor object where each allocator
   //! Allocator in the adaptor is initialized from the result of calling
   //! <code>allocator_traits<Allocator>::select_on_container_copy_construction()</code> on
   //! the corresponding allocator in *this.
   scoped_allocator_adaptor select_on_container_copy_construction() const;
   #endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   BOOST_CONTAINER_FORCEINLINE base_type &base()             { return *this; }

   BOOST_CONTAINER_FORCEINLINE const base_type &base() const { return *this; }
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
   BOOST_CONTAINER_FORCEINLINE void construct(T* p, BOOST_FWD_REF(Args)...args)
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
   BOOST_CONTAINER_FORCEINLINE void construct(T* p BOOST_MOVE_I##N BOOST_MOVE_UREFQ##N)\
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
   BOOST_CONTAINER_FORCEINLINE scoped_allocator_adaptor(internal_type_t, BOOST_FWD_REF(OuterA2) outer, const inner_allocator_type& inner)
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
   BOOST_CONTAINER_FORCEINLINE static bool equal_outer(const IA &l, const IA &r)
   {  return allocator_traits<IA>::equal(l, r);  }

   //Otherwise compare it normally
   template<class IA1, class IA2>
   BOOST_CONTAINER_FORCEINLINE static bool equal_outer(const IA1 &l, const IA2 &r)
   {  return l == r;  }

   //Otherwise compare it normally
   template<class IA>
   BOOST_CONTAINER_FORCEINLINE static bool equal_inner(const IA &l, const IA &r)
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
   BOOST_CONTAINER_FORCEINLINE static bool equal_inner(const IA1 &, const IA2 &)
   {  return true;  }
};

/// @endcond

template <typename OuterA1, typename OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNERCLASS>
BOOST_CONTAINER_FORCEINLINE bool operator==(const scoped_allocator_adaptor<OuterA1, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& a
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
BOOST_CONTAINER_FORCEINLINE bool operator!=(const scoped_allocator_adaptor<OuterA1, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& a
                      ,const scoped_allocator_adaptor<OuterA2, BOOST_CONTAINER_SCOPEDALLOC_ALLINNER>& b)
{  return !(a == b);   }

}} // namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //  BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_HPP

/* scoped_allocator.hpp
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
*/