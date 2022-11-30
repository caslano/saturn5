//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file
//! This header implements macros to define movable classes and
//! move-aware functions

#ifndef BOOST_MOVE_CORE_HPP
#define BOOST_MOVE_CORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>

// @cond

//boost_move_no_copy_constructor_or_assign typedef
//used to detect noncopyable types for other Boost libraries.
#if defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
   #define BOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE) \
      private:\
      TYPE(TYPE &);\
      TYPE& operator=(TYPE &);\
      public:\
      typedef int boost_move_no_copy_constructor_or_assign; \
      private:\
   //
#else
   #define BOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE) \
      public:\
      TYPE(TYPE const &) = delete;\
      TYPE& operator=(TYPE const &) = delete;\
      public:\
      typedef int boost_move_no_copy_constructor_or_assign; \
      private:\
   //
#endif   //BOOST_NO_CXX11_DELETED_FUNCTIONS

// @endcond

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #include <boost/move/detail/type_traits.hpp>

   #define BOOST_MOVE_TO_RV_CAST(RV_TYPE, ARG) reinterpret_cast<RV_TYPE>(ARG)
   #define BOOST_MOVE_TO_LV_CAST(LV_TYPE, ARG) static_cast<LV_TYPE>(ARG)

   //Move emulation rv breaks standard aliasing rules so add workarounds for some compilers
   #if defined(BOOST_GCC) && (BOOST_GCC >= 40400) && (BOOST_GCC < 40500)
   #define BOOST_RV_ATTRIBUTE_MAY_ALIAS BOOST_MAY_ALIAS
   #else
   #define BOOST_RV_ATTRIBUTE_MAY_ALIAS 
   #endif

   namespace boost {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                            struct rv
   //
   //////////////////////////////////////////////////////////////////////////////
   template <class T>
   class BOOST_RV_ATTRIBUTE_MAY_ALIAS rv
      : public ::boost::move_detail::if_c
         < ::boost::move_detail::is_class<T>::value
         , T
         , ::boost::move_detail::nat
         >::type
   {
      rv();
      ~rv() throw();
      rv(rv const&);
      void operator=(rv const&);
   };


   //////////////////////////////////////////////////////////////////////////////
   //
   //                            is_rv
   //
   //////////////////////////////////////////////////////////////////////////////

   namespace move_detail {

   template <class T>
   struct is_rv
        //Derive from integral constant because some Boost code assummes it has
        //a "type" internal typedef
      : integral_constant<bool, ::boost::move_detail::is_rv_impl<T>::value >
   {};

   template <class T>
   struct is_not_rv
   {
      static const bool value = !is_rv<T>::value;
   };

   }  //namespace move_detail {

   //////////////////////////////////////////////////////////////////////////////
   //
   //                               has_move_emulation_enabled
   //
   //////////////////////////////////////////////////////////////////////////////
   template<class T>
   struct has_move_emulation_enabled
      : ::boost::move_detail::has_move_emulation_enabled_impl<T>
   {};

   template<class T>
   struct has_move_emulation_disabled
   {
      static const bool value = !::boost::move_detail::has_move_emulation_enabled_impl<T>::value;
   };

   }  //namespace boost {

   #define BOOST_RV_REF(TYPE)\
      ::boost::rv< TYPE >& \
   //

   #define BOOST_RV_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      ::boost::rv< TYPE<ARG1, ARG2> >& \
   //

   #define BOOST_RV_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      ::boost::rv< TYPE<ARG1, ARG2, ARG3> >& \
   //

   #define BOOST_RV_REF_BEG\
      ::boost::rv<   \
   //

   #define BOOST_RV_REF_END\
      >& \
   //

   #define BOOST_RV_REF_BEG_IF_CXX11 \
      \
   //

   #define BOOST_RV_REF_END_IF_CXX11 \
      \
   //

   #define BOOST_FWD_REF(TYPE)\
      const TYPE & \
   //

   #define BOOST_COPY_ASSIGN_REF(TYPE)\
      const ::boost::rv< TYPE >& \
   //

   #define BOOST_COPY_ASSIGN_REF_BEG \
      const ::boost::rv<  \
   //

   #define BOOST_COPY_ASSIGN_REF_END \
      >& \
   //

   #define BOOST_COPY_ASSIGN_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      const ::boost::rv< TYPE<ARG1, ARG2> >& \
   //

   #define BOOST_COPY_ASSIGN_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      const ::boost::rv< TYPE<ARG1, ARG2, ARG3> >& \
   //

   #define BOOST_CATCH_CONST_RLVALUE(TYPE)\
      const ::boost::rv< TYPE >& \
   //

   namespace boost {
   namespace move_detail {

   template <class Ret, class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      <  ::boost::move_detail::is_lvalue_reference<Ret>::value ||
        !::boost::has_move_emulation_enabled<T>::value
      , T&>::type
         move_return(T& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class Ret, class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < !::boost::move_detail::is_lvalue_reference<Ret>::value &&
         ::boost::has_move_emulation_enabled<T>::value
      , ::boost::rv<T>&>::type
         move_return(T& x) BOOST_NOEXCEPT
   {
      return *BOOST_MOVE_TO_RV_CAST(::boost::rv<T>*, ::boost::move_detail::addressof(x));
   }

   template <class Ret, class T>
   BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
      < !::boost::move_detail::is_lvalue_reference<Ret>::value &&
         ::boost::has_move_emulation_enabled<T>::value
      , ::boost::rv<T>&>::type
         move_return(::boost::rv<T>& x) BOOST_NOEXCEPT
   {
      return x;
   }

   template <class T>
   BOOST_MOVE_FORCEINLINE T& unrv(::boost::rv<T> &rv) BOOST_NOEXCEPT
   {  return BOOST_MOVE_TO_LV_CAST(T&, rv);   }

   }  //namespace move_detail {
   }  //namespace boost {

   #define BOOST_MOVE_RET(RET_TYPE, REF)\
      boost::move_detail::move_return< RET_TYPE >(REF)
   //

   #define BOOST_MOVE_BASE(BASE_TYPE, ARG) \
      ::boost::move((BASE_TYPE&)(ARG))
   //

   #define BOOST_MOVE_TO_LV(ARG) \
      ::boost::move_detail::unrv(ARG)
   //


   //////////////////////////////////////////////////////////////////////////////
   //
   //                         BOOST_MOVABLE_BUT_NOT_COPYABLE
   //
   //////////////////////////////////////////////////////////////////////////////
   #define BOOST_MOVABLE_BUT_NOT_COPYABLE(TYPE)\
      BOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE)\
      public:\
      BOOST_MOVE_FORCEINLINE operator ::boost::rv<TYPE>&() \
      {  return *BOOST_MOVE_TO_RV_CAST(::boost::rv<TYPE>*, this);  }\
      BOOST_MOVE_FORCEINLINE operator const ::boost::rv<TYPE>&() const \
      {  return *BOOST_MOVE_TO_RV_CAST(const ::boost::rv<TYPE>*, this);  }\
      private:\
   //

   //////////////////////////////////////////////////////////////////////////////
   //
   //                         BOOST_COPYABLE_AND_MOVABLE
   //
   //////////////////////////////////////////////////////////////////////////////

   #define BOOST_COPYABLE_AND_MOVABLE(TYPE)\
      public:\
      BOOST_MOVE_FORCEINLINE TYPE& operator=(TYPE &t)\
      {  this->operator=(const_cast<const TYPE&>(t)); return *this;}\
      public:\
      BOOST_MOVE_FORCEINLINE operator ::boost::rv<TYPE>&() \
      {  return *BOOST_MOVE_TO_RV_CAST(::boost::rv<TYPE>*, this);  }\
      BOOST_MOVE_FORCEINLINE operator const ::boost::rv<TYPE>&() const \
      {  return *BOOST_MOVE_TO_RV_CAST(const ::boost::rv<TYPE>*, this);  }\
      private:\
   //

   #define BOOST_COPYABLE_AND_MOVABLE_ALT(TYPE)\
      public:\
      BOOST_MOVE_FORCEINLINE operator ::boost::rv<TYPE>&() \
      {  return *BOOST_MOVE_TO_RV_CAST(::boost::rv<TYPE>*, this);  }\
      BOOST_MOVE_FORCEINLINE operator const ::boost::rv<TYPE>&() const \
      {  return *BOOST_MOVE_TO_RV_CAST(const ::boost::rv<TYPE>*, this);  }\
      private:\
   //

   namespace boost{
   namespace move_detail{

   template< class T>
   struct forward_type
   { typedef const T &type; };

   template< class T>
   struct forward_type< boost::rv<T> >
   { typedef T type; };

   }}

#else    //BOOST_NO_CXX11_RVALUE_REFERENCES

   //! This macro marks a type as movable but not copyable, disabling copy construction
   //! and assignment. The user will need to write a move constructor/assignment as explained
   //! in the documentation to fully write a movable but not copyable class.
   #define BOOST_MOVABLE_BUT_NOT_COPYABLE(TYPE)\
      BOOST_MOVE_IMPL_NO_COPY_CTOR_OR_ASSIGN(TYPE)\
      public:\
      typedef int boost_move_emulation_t;\
      private:\
   //

   //! This macro marks a type as copyable and movable.
   //! The user will need to write a move constructor/assignment and a copy assignment
   //! as explained in the documentation to fully write a copyable and movable class.
   #define BOOST_COPYABLE_AND_MOVABLE(TYPE)\
   //

   #if !defined(BOOST_MOVE_DOXYGEN_INVOKED)
   #define BOOST_COPYABLE_AND_MOVABLE_ALT(TYPE)\
   //
   #endif   //#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   namespace boost {

   //!This trait yields to a compile-time true boolean if T was marked as
   //!BOOST_MOVABLE_BUT_NOT_COPYABLE or BOOST_COPYABLE_AND_MOVABLE and
   //!rvalue references are not available on the platform. False otherwise.
   template<class T>
   struct has_move_emulation_enabled
   {
      static const bool value = false;
   };

   template<class T>
   struct has_move_emulation_disabled
   {
      static const bool value = true;
   };

   }  //namespace boost{

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for classes marked as
   //!BOOST_COPYABLE_AND_MOVABLE or BOOST_MOVABLE_BUT_NOT_COPYABLE
   #define BOOST_RV_REF(TYPE)\
      TYPE && \
   //

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for template classes marked as
   //!BOOST_COPYABLE_AND_MOVABLE or BOOST_MOVABLE_BUT_NOT_COPYABLE.
   //!As macros have problems with comma-separated template arguments,
   //!the template argument must be preceded with BOOST_RV_REF_BEG
   //!and ended with BOOST_RV_REF_END
   #define BOOST_RV_REF_BEG\
         \
   //

   //!This macro is used to achieve portable syntax in move
   //!constructors and assignments for template classes marked as
   //!BOOST_COPYABLE_AND_MOVABLE or BOOST_MOVABLE_BUT_NOT_COPYABLE.
   //!As macros have problems with comma-separated template arguments,
   //!the template argument must be preceded with BOOST_RV_REF_BEG
   //!and ended with BOOST_RV_REF_END
   #define BOOST_RV_REF_END\
      && \
   //

   //!This macro expands to BOOST_RV_REF_BEG if BOOST_NO_CXX11_RVALUE_REFERENCES
   //!is not defined, empty otherwise
   #define BOOST_RV_REF_BEG_IF_CXX11 \
      BOOST_RV_REF_BEG \
   //

   //!This macro expands to BOOST_RV_REF_END if BOOST_NO_CXX11_RVALUE_REFERENCES
   //!is not defined, empty otherwise
   #define BOOST_RV_REF_END_IF_CXX11 \
      BOOST_RV_REF_END \
   //

   //!This macro is used to achieve portable syntax in copy
   //!assignment for classes marked as BOOST_COPYABLE_AND_MOVABLE.
   #define BOOST_COPY_ASSIGN_REF(TYPE)\
      const TYPE & \
   //

   //! This macro is used to implement portable perfect forwarding
   //! as explained in the documentation.
   #define BOOST_FWD_REF(TYPE)\
      TYPE && \
   //

   #if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #define BOOST_RV_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      TYPE<ARG1, ARG2> && \
   //

   #define BOOST_RV_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      TYPE<ARG1, ARG2, ARG3> && \
   //

   #define BOOST_COPY_ASSIGN_REF_BEG \
      const \
   //

   #define BOOST_COPY_ASSIGN_REF_END \
      & \
   //

   #define BOOST_COPY_ASSIGN_REF_2_TEMPL_ARGS(TYPE, ARG1, ARG2)\
      const TYPE<ARG1, ARG2> & \
   //

   #define BOOST_COPY_ASSIGN_REF_3_TEMPL_ARGS(TYPE, ARG1, ARG2, ARG3)\
      const TYPE<ARG1, ARG2, ARG3>& \
   //

   #define BOOST_CATCH_CONST_RLVALUE(TYPE)\
      const TYPE & \
   //

   #endif   //#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

   #if !defined(BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(BOOST_MOVE_DOXYGEN_INVOKED)

      //!This macro is used to achieve portable move return semantics.
      //!The C++11 Standard allows implicit move returns when the object to be returned
      //!is designated by a lvalue and:
      //!   - The criteria for elision of a copy operation are met OR
      //!   - The criteria would be met save for the fact that the source object is a function parameter
      //!
      //!For C++11 conforming compilers this macros only yields to REF:
      //! <code>return BOOST_MOVE_RET(RET_TYPE, REF);</code> -> <code>return REF;</code>
      //!
      //!For compilers without rvalue references
      //!this macro does an explicit move if the move emulation is activated
      //!and the return type (RET_TYPE) is not a reference.
      //!
      //!For non-conforming compilers with rvalue references like Visual 2010 & 2012,
      //!an explicit move is performed if RET_TYPE is not a reference.
      //!
      //! <b>Caution</b>: When using this macro in non-conforming or C++03
      //!compilers, a move will be performed even if the C++11 standard does not allow it
      //!(e.g. returning a static variable). The user is responsible for using this macro
      //!only to return local objects that met C++11 criteria.
      #define BOOST_MOVE_RET(RET_TYPE, REF)\
         REF
      //

   #else //!defined(BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(BOOST_MOVE_DOXYGEN_INVOKED)

      #include <boost/move/detail/meta_utils.hpp>

      namespace boost {
      namespace move_detail {

      template <class Ret, class T>
      BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
         <  ::boost::move_detail::is_lvalue_reference<Ret>::value
         , T&>::type
            move_return(T& x) BOOST_NOEXCEPT
      {
         return x;
      }

      template <class Ret, class T>
      BOOST_MOVE_FORCEINLINE typename ::boost::move_detail::enable_if_c
         < !::boost::move_detail::is_lvalue_reference<Ret>::value
         , Ret && >::type
            move_return(T&& t) BOOST_NOEXCEPT
      {
         return static_cast< Ret&& >(t);
      }

      }  //namespace move_detail {
      }  //namespace boost {

      #define BOOST_MOVE_RET(RET_TYPE, REF)\
         boost::move_detail::move_return< RET_TYPE >(REF)
      //

   #endif   //!defined(BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG) || defined(BOOST_MOVE_DOXYGEN_INVOKED)

   //!This macro is used to achieve portable optimal move constructors.
   //!
   //!When implementing the move constructor, in C++03 compilers the moved-from argument must be
   //!cast to the base type before calling `::boost::move()` due to rvalue reference limitations.
   //!
   //!In C++11 compilers the cast from a rvalue reference of a derived type to a rvalue reference of
   //!a base type is implicit.
   #define BOOST_MOVE_BASE(BASE_TYPE, ARG) \
      ::boost::move((BASE_TYPE&)(ARG))
   //

   //!This macro is used to achieve portable optimal move constructors.
   //!
   //!In C++03 mode, when accessing a member of type through a rvalue (implemented as a `rv<T> &` type, where rv<T> derives
   //!from T) triggers a potential UB as the program never creates objects of type rv<T>. This macro casts back `rv<T>` to
   //!`T&` so that access to member types are done through the original type.
   //! 
   //!In C++11 compilers the cast from a rvalue reference of a derived type to a rvalue reference of
   //!a base type is implicit, so it's a no-op.
   #define BOOST_MOVE_TO_LV(ARG) ARG
   //

   namespace boost {
   namespace move_detail {

   template< class T> struct forward_type { typedef T type; };

   }}

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_CORE_HPP

/* core.hpp
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
*/