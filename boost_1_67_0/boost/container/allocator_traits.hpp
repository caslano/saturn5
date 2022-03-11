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