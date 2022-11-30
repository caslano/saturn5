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
#ifndef BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP
#define BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/container_fwd.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>  //is_empty
#include <boost/container/detail/placement_new.hpp>
#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP
#include <boost/container/detail/std_fwd.hpp>
#endif
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
// move
#include <boost/move/utility_core.hpp>
// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
// other boost
#include <boost/static_assert.hpp>

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
#endif

#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME allocate
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 2
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 2
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME destroy
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 1
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 1
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME construct
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 1
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 9
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic pop
#endif

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

template<class T, class VoidAllocator, class Options>
class small_vector_allocator;

namespace allocator_traits_detail {

BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_max_size, max_size)
BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_select_on_container_copy_construction, select_on_container_copy_construction)

}  //namespace allocator_traits_detail {

namespace dtl {

//workaround needed for C++03 compilers with no construct()
//supporting rvalue references
template<class Allocator>
struct is_std_allocator
{  static const bool value = false; };

template<class T>
struct is_std_allocator< std::allocator<T> >
{  static const bool value = true; };

template<class T, class Options>
struct is_std_allocator< small_vector_allocator<T, std::allocator<T>, Options > >
{  static const bool value = true; };

template<class Allocator>
struct is_not_std_allocator
{  static const bool value = !is_std_allocator<Allocator>::value; };

BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(pointer)
BOOST_INTRUSIVE_INSTANTIATE_EVAL_DEFAULT_TYPE_TMPLT(const_pointer)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(reference)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(const_reference)
BOOST_INTRUSIVE_INSTANTIATE_EVAL_DEFAULT_TYPE_TMPLT(void_pointer)
BOOST_INTRUSIVE_INSTANTIATE_EVAL_DEFAULT_TYPE_TMPLT(const_void_pointer)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(size_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(propagate_on_container_copy_assignment)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(propagate_on_container_move_assignment)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(propagate_on_container_swap)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(is_always_equal)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(difference_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(is_partially_propagable)

}  //namespace dtl {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! The class template allocator_traits supplies a uniform interface to all allocator types.
//! This class is a C++03-compatible implementation of std::allocator_traits
template <typename Allocator>
struct allocator_traits
{
   //allocator_type
   typedef Allocator allocator_type;
   //value_type
   typedef typename allocator_type::value_type value_type;

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      //! Allocator::pointer if such a type exists; otherwise, value_type*
      //!
      typedef unspecified pointer;
      //! Allocator::const_pointer if such a type exists ; otherwise, pointer_traits<pointer>::rebind<const
      //!
      typedef see_documentation const_pointer;
      //! Non-standard extension
      //! Allocator::reference if such a type exists; otherwise, value_type&
      typedef see_documentation reference;
      //! Non-standard extension
      //! Allocator::const_reference if such a type exists ; otherwise, const value_type&
      typedef see_documentation const_reference;
      //! Allocator::void_pointer if such a type exists ; otherwise, pointer_traits<pointer>::rebind<void>.
      //!
      typedef see_documentation void_pointer;
      //! Allocator::const_void_pointer if such a type exists ; otherwise, pointer_traits<pointer>::rebind<const
      //!
      typedef see_documentation const_void_pointer;
      //! Allocator::difference_type if such a type exists ; otherwise, pointer_traits<pointer>::difference_type.
      //!
      typedef see_documentation difference_type;
      //! Allocator::size_type if such a type exists ; otherwise, make_unsigned<difference_type>::type
      //!
      typedef see_documentation size_type;
      //! Allocator::propagate_on_container_copy_assignment if such a type exists, otherwise a type
      //! with an internal constant static boolean member <code>value</code> == false.
      typedef see_documentation propagate_on_container_copy_assignment;
      //! Allocator::propagate_on_container_move_assignment if such a type exists, otherwise a type
      //! with an internal constant static boolean member <code>value</code> == false.
      typedef see_documentation propagate_on_container_move_assignment;
      //! Allocator::propagate_on_container_swap if such a type exists, otherwise a type
      //! with an internal constant static boolean member <code>value</code> == false.
      typedef see_documentation propagate_on_container_swap;
      //! Allocator::is_always_equal if such a type exists, otherwise a type
      //! with an internal constant static boolean member <code>value</code> == is_empty<Allocator>::value
      typedef see_documentation is_always_equal;
      //! Allocator::is_partially_propagable if such a type exists, otherwise a type
      //! with an internal constant static boolean member <code>value</code> == false
      //! <b>Note</b>: Non-standard extension used to implement `small_vector_allocator`.
      typedef see_documentation is_partially_propagable;
      //! Defines an allocator: Allocator::rebind<T>::other if such a type exists; otherwise, Allocator<T, Args>
      //! if Allocator is a class template instantiation of the form Allocator<U, Args>, where Args is zero or
      //! more type arguments ; otherwise, the instantiation of rebind_alloc is ill-formed.
      //!
      //! In C++03 compilers <code>rebind_alloc</code> is a struct derived from an allocator
      //! deduced by previously detailed rules.
      template <class T> using rebind_alloc = see_documentation;

      //! In C++03 compilers <code>rebind_traits</code> is a struct derived from
      //! <code>allocator_traits<OtherAlloc></code>, where <code>OtherAlloc</code> is
      //! the allocator deduced by rules explained in <code>rebind_alloc</code>.
      template <class T> using rebind_traits = allocator_traits<rebind_alloc<T> >;

      //! Non-standard extension: Portable allocator rebind for C++03 and C++11 compilers.
      //! <code>type</code> is an allocator related to Allocator deduced deduced by rules explained in <code>rebind_alloc</code>.
      template <class T>
      struct portable_rebind_alloc
      {  typedef see_documentation type;  };
   #else
      //pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         pointer, value_type*)
            pointer;
      //const_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::dtl::, Allocator,
         const_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<const value_type>)
               const_pointer;
      //reference
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         reference, typename dtl::unvoid_ref<value_type>::type)
            reference;
      //const_reference
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         const_reference, typename dtl::unvoid_ref<const value_type>::type)
               const_reference;
      //void_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::dtl::, Allocator,
         void_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<void>)
               void_pointer;
      //const_void_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::dtl::, Allocator,
         const_void_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<const void>)
               const_void_pointer;
      //difference_type
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         difference_type, std::ptrdiff_t)
            difference_type;
      //size_type
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         size_type, std::size_t)
            size_type;
      //propagate_on_container_copy_assignment
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         propagate_on_container_copy_assignment, dtl::false_type)
            propagate_on_container_copy_assignment;
      //propagate_on_container_move_assignment
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         propagate_on_container_move_assignment, dtl::false_type)
            propagate_on_container_move_assignment;
      //propagate_on_container_swap
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         propagate_on_container_swap, dtl::false_type)
            propagate_on_container_swap;
      //is_always_equal
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         is_always_equal, dtl::is_empty<Allocator>)
            is_always_equal;
      //is_partially_propagable
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::dtl::, Allocator,
         is_partially_propagable, dtl::false_type)
            is_partially_propagable;

      //rebind_alloc & rebind_traits
      #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         //C++11
         template <typename T> using rebind_alloc  = typename boost::intrusive::pointer_rebind<Allocator, T>::type;
         template <typename T> using rebind_traits = allocator_traits< rebind_alloc<T> >;
      #else    // #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         //Some workaround for C++03 or C++11 compilers with no template aliases
         template <typename T>
         struct rebind_alloc : boost::intrusive::pointer_rebind<Allocator,T>::type
         {
            typedef typename boost::intrusive::pointer_rebind<Allocator,T>::type Base;
            #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
               template <typename... Args>
               rebind_alloc(BOOST_FWD_REF(Args)... args) : Base(boost::forward<Args>(args)...) {}
            #else    // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
               #define BOOST_CONTAINER_ALLOCATOR_TRAITS_REBIND_ALLOC(N) \
               BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N\
               explicit rebind_alloc(BOOST_MOVE_UREF##N) : Base(BOOST_MOVE_FWD##N){}\
               //
               BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_ALLOCATOR_TRAITS_REBIND_ALLOC)
               #undef BOOST_CONTAINER_ALLOCATOR_TRAITS_REBIND_ALLOC
            #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
         };

         template <typename T>
         struct rebind_traits
            : allocator_traits<typename boost::intrusive::pointer_rebind<Allocator, T>::type>
         {};
      #endif   // #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

      //portable_rebind_alloc
      template <class T>
      struct portable_rebind_alloc
      {  typedef typename boost::intrusive::pointer_rebind<Allocator, T>::type type;  };
   #endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

   //! <b>Returns</b>: <code>a.allocate(n)</code>
   //!
   BOOST_CONTAINER_FORCEINLINE static pointer allocate(Allocator &a, size_type n)
   {  return a.allocate(n);  }

   //! <b>Returns</b>: <code>a.deallocate(p, n)</code>
   //!
   //! <b>Throws</b>: Nothing
   BOOST_CONTAINER_FORCEINLINE static void deallocate(Allocator &a, pointer p, size_type n)
   {  a.deallocate(p, n);  }

   //! <b>Effects</b>: calls <code>a.allocate(n, p)</code> if that call is well-formed;
   //! otherwise, invokes <code>a.allocate(n)</code>
   BOOST_CONTAINER_FORCEINLINE static pointer allocate(Allocator &a, size_type n, const_void_pointer p)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_allocate
            <Allocator, const size_type, const const_void_pointer>::value;
      dtl::bool_<value> flag;
      return allocator_traits::priv_allocate(flag, a, n, p);
   }

   //! <b>Effects</b>: calls <code>a.destroy(p)</code> if that call is well-formed;
   //! otherwise, invokes <code>p->~T()</code>.
   template<class T>
   BOOST_CONTAINER_FORCEINLINE static void destroy(Allocator &a, T*p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef T* destroy_pointer;
      const bool value = boost::container::dtl::
         has_member_function_callable_with_destroy
            <Allocator, const destroy_pointer>::value;
      dtl::bool_<value> flag;
      allocator_traits::priv_destroy(flag, a, p);
   }

   //! <b>Returns</b>: <code>a.max_size()</code> if that expression is well-formed; otherwise,
   //! <code>numeric_limits<size_type>::max()</code>.
   BOOST_CONTAINER_FORCEINLINE static size_type max_size(const Allocator &a) BOOST_NOEXCEPT_OR_NOTHROW
   {
      const bool value = allocator_traits_detail::has_max_size<Allocator, size_type (Allocator::*)() const>::value;
      dtl::bool_<value> flag;
      return allocator_traits::priv_max_size(flag, a);
   }

   //! <b>Returns</b>: <code>a.select_on_container_copy_construction()</code> if that expression is well-formed;
   //! otherwise, a.
   BOOST_CONTAINER_FORCEINLINE static BOOST_CONTAINER_DOC1ST(Allocator,
      typename dtl::if_c
         < allocator_traits_detail::has_select_on_container_copy_construction<Allocator BOOST_MOVE_I Allocator (Allocator::*)() const>::value
         BOOST_MOVE_I Allocator BOOST_MOVE_I const Allocator & >::type)
   select_on_container_copy_construction(const Allocator &a)
   {
      const bool value = allocator_traits_detail::has_select_on_container_copy_construction
         <Allocator, Allocator (Allocator::*)() const>::value;
      dtl::bool_<value> flag;
      return allocator_traits::priv_select_on_container_copy_construction(flag, a);
   }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      //! <b>Effects</b>: calls <code>a.construct(p, std::forward<Args>(args)...)</code> if that call is well-formed;
      //! otherwise, invokes <code>`placement new` (static_cast<void*>(p)) T(std::forward<Args>(args)...)</code>
      template <class T, class ...Args>
      BOOST_CONTAINER_FORCEINLINE static void construct(Allocator & a, T* p, BOOST_FWD_REF(Args)... args)
      {
         static const bool value = ::boost::move_detail::and_
            < dtl::is_not_std_allocator<Allocator>
            , boost::container::dtl::has_member_function_callable_with_construct
                  < Allocator, T*, Args... >
            >::value;
         dtl::bool_<value> flag;
         allocator_traits::priv_construct(flag, a, p, ::boost::forward<Args>(args)...);
      }
   #endif

   //! <b>Returns</b>: <code>a.storage_is_unpropagable(p)</code> if is_partially_propagable::value is true; otherwise,
   //! <code>false</code>.
   BOOST_CONTAINER_FORCEINLINE static bool storage_is_unpropagable(const Allocator &a, pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      dtl::bool_<is_partially_propagable::value> flag;
      return allocator_traits::priv_storage_is_unpropagable(flag, a, p);
   }

   //! <b>Returns</b>: <code>true</code> if <code>is_always_equal::value == true</code>, otherwise,
   //! <code>a == b</code>.
   BOOST_CONTAINER_FORCEINLINE static bool equal(const Allocator &a, const Allocator &b) BOOST_NOEXCEPT_OR_NOTHROW
   {
      dtl::bool_<is_always_equal::value> flag;
      return allocator_traits::priv_equal(flag, a, b);
   }

   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   private:
   BOOST_CONTAINER_FORCEINLINE static pointer priv_allocate(dtl::true_type, Allocator &a, size_type n, const_void_pointer p)
   {  return a.allocate(n, p);  }

   BOOST_CONTAINER_FORCEINLINE static pointer priv_allocate(dtl::false_type, Allocator &a, size_type n, const_void_pointer)
   {  return a.allocate(n);  }

   template<class T>
   BOOST_CONTAINER_FORCEINLINE static void priv_destroy(dtl::true_type, Allocator &a, T* p) BOOST_NOEXCEPT_OR_NOTHROW
   {  a.destroy(p);  }

   template<class T>
   BOOST_CONTAINER_FORCEINLINE static void priv_destroy(dtl::false_type, Allocator &, T* p) BOOST_NOEXCEPT_OR_NOTHROW
   {  p->~T(); (void)p;  }

   BOOST_CONTAINER_FORCEINLINE static size_type priv_max_size(dtl::true_type, const Allocator &a) BOOST_NOEXCEPT_OR_NOTHROW
   {  return a.max_size();  }

   BOOST_CONTAINER_FORCEINLINE static size_type priv_max_size(dtl::false_type, const Allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return size_type(-1)/sizeof(value_type);  }

   BOOST_CONTAINER_FORCEINLINE static Allocator priv_select_on_container_copy_construction(dtl::true_type, const Allocator &a)
   {  return a.select_on_container_copy_construction();  }

   BOOST_CONTAINER_FORCEINLINE static const Allocator &priv_select_on_container_copy_construction(dtl::false_type, const Allocator &a) BOOST_NOEXCEPT_OR_NOTHROW
   {  return a;  }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
      template<class T, class ...Args>
      BOOST_CONTAINER_FORCEINLINE static void priv_construct(dtl::true_type, Allocator &a, T *p, BOOST_FWD_REF(Args) ...args)
      {  a.construct( p, ::boost::forward<Args>(args)...);  }

      template<class T, class ...Args>
      BOOST_CONTAINER_FORCEINLINE static void priv_construct(dtl::false_type, Allocator &, T *p, BOOST_FWD_REF(Args) ...args)
      {  ::new((void*)p, boost_container_new_t()) T(::boost::forward<Args>(args)...); }
   #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
      public:

      #define BOOST_CONTAINER_ALLOCATOR_TRAITS_CONSTRUCT_IMPL(N) \
      template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
      BOOST_CONTAINER_FORCEINLINE static void construct(Allocator &a, T *p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
      {\
         static const bool value = ::boost::move_detail::and_ \
            < dtl::is_not_std_allocator<Allocator> \
            , boost::container::dtl::has_member_function_callable_with_construct \
                  < Allocator, T* BOOST_MOVE_I##N BOOST_MOVE_FWD_T##N > \
            >::value; \
         dtl::bool_<value> flag;\
         (priv_construct)(flag, a, p BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      }\
      //
      BOOST_MOVE_ITERATE_0TO8(BOOST_CONTAINER_ALLOCATOR_TRAITS_CONSTRUCT_IMPL)
      #undef BOOST_CONTAINER_ALLOCATOR_TRAITS_CONSTRUCT_IMPL

      private:
      /////////////////////////////////
      // priv_construct
      /////////////////////////////////
      #define BOOST_CONTAINER_ALLOCATOR_TRAITS_PRIV_CONSTRUCT_IMPL(N) \
      template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
      BOOST_CONTAINER_FORCEINLINE static void priv_construct(dtl::true_type, Allocator &a, T *p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
      {  a.construct( p BOOST_MOVE_I##N BOOST_MOVE_FWD##N );  }\
      \
      template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >\
      BOOST_CONTAINER_FORCEINLINE static void priv_construct(dtl::false_type, Allocator &, T *p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
      {  ::new((void*)p, boost_container_new_t()) T(BOOST_MOVE_FWD##N); }\
      //
      BOOST_MOVE_ITERATE_0TO8(BOOST_CONTAINER_ALLOCATOR_TRAITS_PRIV_CONSTRUCT_IMPL)
      #undef BOOST_CONTAINER_ALLOCATOR_TRAITS_PRIV_CONSTRUCT_IMPL

   #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class T>
   BOOST_CONTAINER_FORCEINLINE static void priv_construct(dtl::false_type, Allocator &, T *p, const ::boost::container::default_init_t&)
   {  ::new((void*)p, boost_container_new_t()) T; }

   BOOST_CONTAINER_FORCEINLINE static bool priv_storage_is_unpropagable(dtl::true_type, const Allocator &a, pointer p)
   {  return a.storage_is_unpropagable(p);  }

   BOOST_CONTAINER_FORCEINLINE static bool priv_storage_is_unpropagable(dtl::false_type, const Allocator &, pointer)
   {  return false;  }

   BOOST_CONTAINER_FORCEINLINE static bool priv_equal(dtl::true_type,  const Allocator &, const Allocator &)
   {  return true;  }

   BOOST_CONTAINER_FORCEINLINE static bool priv_equal(dtl::false_type, const Allocator &a, const Allocator &b)
   {  return a == b;  }

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
};

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

template<class T, class AllocatorOrVoid>
struct real_allocator
{
   typedef AllocatorOrVoid type;
};

template<class T>
struct real_allocator<T, void>
{
   typedef new_allocator<T> type;
};

#endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif // ! defined(BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP)

/* allocator_traits.hpp
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
*/