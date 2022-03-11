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

   }  //namespace move_detail {
   }  //namespace boost {

   #define BOOST_MOVE_RET(RET_TYPE, REF)\
      boost::move_detail::move_return< RET_TYPE >(REF)
   //

   #define BOOST_MOVE_BASE(BASE_TYPE, ARG) \
      ::boost::move((BASE_TYPE&)(ARG))
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

   namespace boost {
   namespace move_detail {

   template< class T> struct forward_type { typedef T type; };

   }}

#endif   //BOOST_NO_CXX11_RVALUE_REFERENCES

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_CORE_HPP

/* core.hpp
1z3BYlk2B9VnHxvGCy0kkopGQ4qvj27bVFF3u32g25m6BX27cCUd6cPNQnqFQqkr6Asl07UB3S+Ueg32CujXfiuJCiTWh46jitAZlJ8PBZWNl/eFtWEkcIsVSlIaFvQx02PZk0urfKWp9zgri+VspDkY7a17VOJLDkjWZ01Z85pR6L5xDUDDyB9AvqO2nstNzOp9R/nOQgwAs9VBfH1o8YtO/CklaiW+0/7vIkAyUDMatv45dnGIeoNeM3qmdos5FXNI/knH0BmpSifjZkSaqO8G6SrGf/yqaalLGONx11Rq73EgiE6xFuJFXF4nC8rr4aE+pbQjZDzd1Nq5oHpEjnTjEfOGNvchMS2DbD18u0VB9w59JGjtbVg8TMJbCJd+37zrHVPKJ9j2HYJ5D0afHEZ2g+9x+FYB7oMqRQNq5Dy9MjTmwdOfejv6759e9RmMwdIUj4J4FMSgZwknbZj8RS7Pek5ao1fTIBJY8daYpMtnS4VlWIGYiQAwOZ5YhUbWPkEMbt5ZsaNAvKltm3NX5xIucSnzkBYOqHZhSBu730xvUIZxbah+UTKkwci8ZC9GWV5NL+2jqemUeg96eDyDeR5NuELNioL7hym0be5msRjVjXtpKFZ8bgY09ghTcmr6hAoSVKjtqu7mSld4at0KWp7pLsAnqvbMGvimvOaznFAAtJ9GaL1+f95UloSsqP9Fys8WU4PjCEYWlxUaYRe7AdQtCL2A/ZZ2BKqoexaspBMC6iqKRVqo0KrGXQE1tV+ja6a8ClNepjXl2im9TSwHfTjzrS0YYThPARtB/ZZOhf1c7sy3fEQgt7S5M9AJdcXLMcWrkTuFtZ3qNr19QKm2XALt8zDIqdezpHqku9/2wAHFJ1hel2MO8Ry85HOQYtu+CdnnEM/iNabOXEdF8i4Kx6DnkjTMG73lFe4DN5TXJArrxU5H+9ug8/gq6cxBK0ZD6gIoAtQFjS9G3APLDsm+cV300An2LKbRR304WAP9UEC9OoHXEO3utyydfDiq+gFpMj2RfRhRq1A/+dhfqdsAwlp0lRK1AqrJ2dJmENUSHMyOasOK33DyUYQnH0e1kXxoTXr6cUS973HQQs9DgI/IkG6PotNP7DGerDRa86SmYiwpXj5/3FKMxy08PW7xPTTH0cpc/iW2rzD6G5k18tMt1ioaNWTTITau+QC5nKCg2jMu+3LoZTM/x/8ihwhwssS5zpf2rTD6s577PmH1qL6PXdOyCdfTt4uH8+tpccC4nk61bEp2XWdvF0ijK6ju/BVbN3uvs+H9s5bVqRZXssuJ2c3WkLopn+1k2Y5Ui/XLQmwiHqkepUdQ1JV7i+N5+qLXCS/K3usQO9EygAu5pVZuqdOhk9zSMIWe5JaNcsutDI4hDGvZAkgMV4WzNoCYfM6s+HJ/3/kLl6SoepSCO7kwDHqXuclBmfuOPZS6TH3sNzrKCyv1rqmsAMy8kJuEXOKvlRtrSbQO/erWr0enu/4GubGhNxpINQdIfZPsbSL+W+XGW0l0o9y8EeqImzA1rZukMsV7OzRDCfHfLusnD4PeTSZS3wb1I/7NcuNmEoVabpnLu7iVm1HflV8z6F/V3OtVO3rS8AiZImwHAPYcOYY2tBafc9BzGgbqRRx1CDkuHm+/DpYsMecZT7lJ2qz4hnStxQg2Q1RlY/+UfceVyNCkyr6L0V09joB66kHqzCi+gwzBRKp7VLIkbtAKoav5BCjFJJra3W4YQiLjFo8T58PygLqPTofCmv7ZPQ3vCC+Pr86TsnUfxNqU9i4kMUcqcpJ4TgaM7pVs3dQwICKEcTUMaP8ETCt3/gnYw3khedAhLxcvAwZilIGYE4oPwdR2/ZcyEL8iXzyJnUysUjZosk0r3NW5iCOFtm7Biqfx0yv0X7rPIOBp+UkkUMkIkMjJGnPixg1yBRUIDK4WaSutjI9nlYlzAeYHyva3/mT/ieREw7bv2/al3njlHk6rVJ6HLzLwC7m+Vo7WsZYcexJ3dfxNtdkrkv4t1mzFbn8TmiVly+BPc9YOWa7sJfBsylrh2QkFl4mLEr2kULS02910LLfglZCxGgud2UHaq6aqKySWItwuIWUBKs2A+svn8n60SpGGtKYXY8xNNsWkn6ul6OBLidaGwqwRDujvOeA9nAPFpe0ObAYPbQZfeSAcHPsLAxfxq40MdKKsZM9JKKsKM1cZZTmTu/PPTueuZh7uXIy79cjdG8Bd5RR30B1MWR4WPNCj6xtQWlIdai8f3yyjl50dzKsNoKcrmLga8txKC1lC26Til0AFdIm/CLX2CKIThB6jQo85g+GxAXT/AYpEacV3TL5YphViFLlZyljYy6dApSKoVdWj4ZBBWfYnJ663/fhKIGjbt6vtVVSYnir4glYHyNO0+23trKbtfonjYRjzN41dhjdhok2738Fd9t2HONBiOdo0hnFK6Bv1TVdoxzRtAXcpZNQ3jY3RA1Yk8yEl46JkGIXTlIKZUUD3Enp/h77+9Zld4xBdewugkXymCA3ix36KkIXHhJQ/wNKyXSgOFxMHzanP59yO3GVbWMEDhoKzt2Tq22ightbN2XU1sdOwaqynIzIMqv7NmXo2r7Q2ZFdkij5HUpeRwknuQANDgaBaxbgD/oHCIqkaFfUGaZGxcYps3a1oE13q9lHt9TkDQVyIqjm6OBfmarc+98g93I3wuQk+18KnDD7fhE85fL4Gn1b4cDxv4nneDB8Lb+X5At7wr5D/qn9F+QckYP4/V+22AwE7AIBDS819DXhU1bXoJDMJExiYUQeIGkuUoMHEWzTRBgctCDOJQsLMhJnQSgL3lrbTXPqVpzMaWxKgk8QcNydS+SkqorZqaUtb2qLEW5WBxCRILkSaqxNIINr0ejB5GoRigMC8tdY+Z+bMTwLee9/7HnxncvY++2ettf/WWnvvtcQHNTfBbPHdrp9qtPB3Jjy/gvc8eDbC8wN4auBJg3gbPCXw/g14TsFTAmHNpKRJyZMi/7Q6+EmJhDWp4/Rpk1LxdfwEA3yfCO+GyH6HgVRIJu5BgLbifoFrxBTRUJB3nF2ANbTu4BM30S2bqcotG+057TmuMTuhvTig59dr5uzNO4cXbHwjdQHIMKRkGIrJ8FfIMMTv44g+s9vh75tWZndKu46QAVp54TTJ9uGab1HJ6y1jyOv9Vy2v96O83vh8WF7XPvPfl9fX7sZlNSJyr6BpDyU5NsxO7h/QY/S6vyVdWRi3vsCF8RvihXEuMkYL4zCLXQPz6Ua79Naf0DSEAaWS69H9xAMof5o13uKwRNMMs3Kc2AlzYY4sn98RFTtZlkRVkjjagrSZmR7Y4HCh1qF11WZUPIQl8f6IJN6PKt8HZUm8XxaI+nnBTy2Z2Ine6AwNriHmWM3l8ShhfLAMrZ7hBpzDXuqUDg1ySXwCncPUM71DdG10Si1/JEPgLB1FsrCnIwNu3p6bJ8vgVtRO0OVelQyeSC2hhcUwXi2hjUjfw77bItJ3Bpe+J5P0bUTRrlTaMtIWOuWh1RGD9RCEIfXiNpS755LcXRAld5PATYJ2v9JdQfrOD9vWkvq3YU8lAQo6q/tp3lnJxhP2BWfYCJhK7qY6sO/WTixQ5G4yKsSK09FNBBe8MSIsd7/9O8XwkGxIDgTpgjhBukAWpL/5ey4C8+5H0XbpXhwEcveLdLooMbpAJUZf/F1YjL4eDzf1R4nRzXFidLpQbphdTmJ0P1dzzLwItH41Toy+ILiGhGqz5aRakjbIkrT50eyBceLKLKhnSC1S5xyApfop89R7zVykNjxygsvTMO76QWR/+0JbvDxdEJanq2LkABcs6NPpE98Ny9P9IE+H/uWw3P4C8tYReTr/vyhPz1XL0/O2yvK04f+5PD18y5Xsd6IwU5PNKnItF9fcDcDmPxUK7dQZa1/A45WKoA0iNh5pE6oHhfIhZA8VeeUxNIZ3P25pxrvbyjuufc/7LaFcr0X50GLL9s1c9w7dO/bqxfpXuH48gKpgsWQJsJA6J7TjP07RMkNl+q36qgTlzte+Z+l+5Ddj4B7Bf9Z0Ff5zRnNeQDs08bu+ecfJu5dQ3SGUd/qmVYZK/a35bYVcfl1ucrMjDdOklp9DJy8hKwu5rCJbsHZagtX5QMiBBiBksnemWNykyH2dbdYmL8l9LUJxu+hqCst9X/soFEI9g0Rll/c3lHeFPUZLN28CmgwbSd+Oh7fmPUcK92th3TExaxckfxRGYFerRgMgirZ8StTxz4dH2WqGVvlRm7WTML9fW92J6xpSH3NthVz+b14GaaBwLrDmlv2PmYxvlNlz9jup0F/BOMHk/rbMMgx/X6nEb+2sitsyn689ADLw86y6o9U2Kwn3kWXitRXyg6VHWsdppF+uOIz+zFEv4upySkVP8dNzbYkM6L/1mzTZ/LJiP9gu7//qYZJox/OY5jIx405+1AnneHEOzYIOOdmdkOw0m2fSDmH4WnZNaZn2AEgtOz4O8Y2I0jL2PsVsUGL+m+Opv/6rjKdb//4/PJ5c5/7nxhP51/Pp19XM0njHAWoHTyBXZbC7padx+9qWzWzZ6N4XT0Z822LLrXaVsRplY7GUDi+0f9ntnaxs7IqGLVd/eCGgnIpqjjsqHrXfim67+J2Q4ceK2ZS8g3UBby7wu1jzVOXYBNqC5vxuN/G7dJTC/BTVDYJmac5wmQN3Sh+nU2+yI7pH56GdeumXAbJylM7m6spEVx9uoIrF6KBLacNbfklqR5zANY5SHDhDyLYf6lOVpZxXtVgNxlo8yFDKyk3uMvEndnG1fUBL/p5208As2eMQF+8RtNLDm9po7InuTqe4uFNaCGFmGxIKh1jJWWHxWeYeFsqGmW1EKBx5alKDkbl1Qhm6NRcK0a606DYJiw2Q0yS9/FdkydKFQnT/IyzOYO5Mf2uVUJYp2nb7m6vwHAqAVfdj7uep+WE03G2KJTi316G3+ACBDYgASinicp2/VYZ/HAJbCvALtt3Sjmdk4Asz7WJJp9T4jKz0GyKl31lS+g2T0m8ElX5TSOenI52fnpUtEwtXQD6T4DZIfzuKViQ9gi2dtHsZpN1DBAB6gNtXv/xh5b6y1TDbqueeQ+PpW0/MTsj/WRVR2f95lcM/UMVp/fnPoml98mf/VVrffTSO1gAn0NoCkNU9PjqJ+XzzvyLrlyN+qik2AKuvmLc46E3DsyvS/E8Tar0TjN+048r4nfb/xfi9KnwToWw/FY8y959cfsoscacQsj1zNT+gH92eOSs3s2qD4BuUq2Ih4ADvx8rcpZKDfLEYFuOg8ekH/s58gzjffOk1Qzb4jjdu4RuQ0vKl73PyX7n7tTTN2BMsh2/3VcFXjT6W0E1ldQQ+GIje+9wg0jRfgtrbqtAdWrUJwJDhM0Xg++hyHHwmhK9tLAjl8Y63HaCkKaXitwxQ1Naooh5eHvHAENZfkC/T06xd8I3AXGk54C2EpaiUXGGj0bizF6DtanQs6G8xsTOWk96bZPuK1hF/wAALcZ66ilMMnSwMLxeW6h4OexOgUyecfv85XaWPMEfZ7oxi+YiKBmhPdlp4nVtj6yPLkminDc8Lv4RSbIWOHUpwFFB74E1y9tpuORJlbISV6HMmadu4BUo5F6OAmvmytBv9bwBkeFjnVwJIBiUGO7doKRW9gMek9DlfY+08+4D2r5jx2P6BadpjrBmNKDeLuv0CGV7mhpUdeUedUIRD2EJ2CF0jbAviAGu/8AJWLWkvKUllW5mpaLgO5zzcTdc7Hfa2OsxKrOZjZN+WEtt0kM7J8/DU2pPsELotPCQa3mMuvcPu5DlJxTLnEm2GAOdyKI5gUJAs52gPaNEI2VRI5ygFAryGuaY4Jee6aEsnRA9y6YimnBEE0dzOjmD4iODWQ0CAKTf11HlkvF8gu5DcyDAZCPVfTKqZykSyN9yKRGsVdW32MqngEhpZr5nJ6rCxta0wZ30MdWKpnTmHRd2HouGI3cEzShMgcZn05loCjAbJwC/SNDnl+qimkdv0iNGPRxRl2ovkGkp6s19FTCc7uf9vupyTlRrtcZn02uPwap7gtDsUPdWXF+m0VU6xPkxD2Xx2uOs5coYr8VC1HcoUt2A90NQgomqlGy6G7begdZdZIncDl3PGHS6/kCtlOXyndpNtUnJEx72iyCRz6Lh7FG2n1qoHYTlphOsypE9fRqOEErfRijYOpQ/+RsgRbrwTy71SRtRtcGqP29kw/ORcLAMwUhAM08Vwl3TpcZmnnHZHmVOyAoQiGaamewDBUrv0DGmD83mNcj+S7vs4asonCQHtGD63g0sIcfaD8Nz8NzXe2aVuuYst17FvWM54b1RcrhXiZNN6PjzZnIFZc5xdaqqmDlDxcF5AGCcU6mCFXx45P5uedYX9UVhKvqVjF3Nm8wb9XPthpCmVQ31DjxlFl8GZMwQT6t0XUZ3+6FSWxD5Ae7YfiLrOUjudtfvNBbTja1AoYPkojgKA9xoF71MTQipvSAq8C7NU8+O6KH9+bvWxOQM7DU2MWhPpzEe8iSfZHXKPYoq3Y2nqBWpClsrT4qmcw9IjCCeFFVA39kWBWsGFuc+3p2kUbliB709ZV1r/IlvyqJkr2IECkDeLNaL8M+rGPKUSa5bggjkO3TGB6Gkd0Unj1gJg+JrMXTH5a4pQDgURWgr8RN6fL+L78wsaKvIbykeEiszZFSbvZGBG5X5kAwZk00/k6UuoMAkVZqFCme+kuksJWinSf05H4etO2H/q9pBpm0H5ToIdLSYpqoHvfUFKOjdrlyZ8LnePIfwCOGmknTQBjuW/6tYZqv5QO7p/R5GcKeDluj1/JBVh2J/VE1FOf5iI6fxHQg3UVYTqkdEuHyQ+Za894Ltbdqwndz/dSepieN5VQfrOS0oHg/KlPDwEWwLLpiX42DTu+tI/WMU6hFcJZKkZvuNSs1CexaDlpCOncSHwpueF5MrYJO0R6cH/IM5poe9TPK2QDxNeWV1bKJEeIv+5sB4i5r7yjBh/maWjeBnvQ+O20vd3o31XmZQPVWFXCSA1hwRfi6IZHIV+bum9x/gRgRl4RECm/1NBdqShvAd3XtusXdQDv/MYErAH+C3jG+0Ot7NM+mc0y13cBwyXXfrHJfSjUZlkJ5vy/Q3WAcEaFK2DdixnUKqfHz6CPzsZj+CDUBWsQ6fikH9//oCJufqUZTpZXNS+kxXKtgD4YXt6nQqvHz61LC/p3oy7fOWqOHHJXUmCq4fHyEfw+5nDDIBwdc31A2iqYZ5JG+ThawbQkdMBQMfJXP143uDvnThhJwu+/lPI7rHyfpjTnao6tB9E1wDFa5u/QgW1UAGUDnjZsJRk9k1AnV2vvSxUA02D+z/R5VQHtSH6f5Lf7IcJMXlAS6fJ9MxhgvTaTsHVIXV7ke4txjcCdrejFG3x4+1k6ad44hpX7HRSeCezNObryTldG/A+wMr72ATtEahfGsTME9gcoz90yTvTHwr5UvG4ycB1/tBlfB1IGtBbqrtqtEJ1F10+SbJ2JlmD0Ox4QcE1iMfwm+aFLyjcTUbSg3nnLK3elXGNeIwVQsv2251lDmkT7euY1lWf0fi+y6q7LJfXWPD8MMCzM8k7Syzepei0dtGZluomwfeWaN0VnqOuPUTuFMr7xIX5A68xa2feUUtrzZS8g2yYaf1z9CGfTjDrH/Dvr1rs++whdD1c3K7sWL9J6kLyREqnnsikuPA6Gjdupd0KjSCSF9fXV1IUug+FuW+zRnid5p/XaRkitwK0Z+1b12CtbbM20Fko9C6wQT4LZd0uuF4SfK+wR3XMwg6r1GSsuDNqyUZGytL+mFncglA5c9rpyHX1GXnd5pyUW5zTVkb+tg5JX3yB01W+aj1c140OiwY0Xp1/YZaOuboeQOoKpbneVIjA8yXfybrMmq/ivFLbjKtZLwfzjisWoZCTKEVNChoKHgovV9Lbr+OZskyhIkuoyBYqchsqZkUtfWLJElwmW232UGhyfjtadViCC6mwYyNukO3YjO1Uvw2tdVD4JW4f1MEO00J74kLMShSHEMfn67eqz1+Npq+HkXUaUPK146SlIFbc4Qgj1hFBrH/P/wXEqjsRK8tFbzFri1Lai/YkmZ98Sj/33kO+8zkH7KQpv6mvLSS6upxEjxTpMPKZXOlt7bJLpY/Gu34MLzZtm+IWmzC96m9VrTdnx/LPrCczBcDVprwT3P6sxnLRl7KvHV4qr/XsgT8AYxQi0qqTbSFP9tpdmjfNL/5aQ5vuu4A6blHkji7Q3r1UiIIZeV9ycP8UW/838SO4tQEsSdV/ooatFLcOyDFFwYOHQ++g6n+2rwMxb7JL33qEMOeltlk7OATtDeVNwGxJn/wDCkj27OYASksLYf5qQxo/GEvf++DTbJ/0yARW3MX9QQ2kAb25HwORoAWGVkPbcujZsY0svaN5WB7rIBHqk/Ywz8zpe0JN38yk0elbrWc+pC+SleiLhNa8oKJvUxR2kuFEQvqWcadKXIcgfTKC9MVXmb73DMr07UL6pv9doW8T0TdYeFjdqy6tlml7lgQnVesibdlZFW2bpBEr0LZVrIrtv212N37uhc+loog+ESqvcYQm25HZ06OOe7WezTWwarRaBMsquqJxDYrWINAL71yja2884tiEDBki4hR8fUK1JM25iJui2+3SGYBjfctu4mwJD6200Sb3E4Bztm83oFO83SH9E0cH+84E5moStmBx0MrWJk4tmVAiOWRQWhnf0ai2SOoRJ01GjnchjvRT5l6r/q5AgzXUYL0sWtFF1mVHZZLsJ/nb9aFQr2sQvS5/1Ft+NjQ5CDj3lJ/lzpqNnjnQup4e+JFWQzP1Wgdj91+h8N5req2mXoe+12Xq/ow70U3yPtRbjoqxGRrN0Nq8o75x9+GL9x5IE/0hgz74JrOJmdBFRKvJ7lkD1TmkFShU7MdTOL3Bl/FbbxDttXrs8NUuPXAJO7FyP0/fq+mdC/UPQf3kZzrJWItHQNCxMRp055Ud9E2gyoy1HfjtPUgf/fkWDsuNbGIW1ncM1pHebntvUIbo8AidbulN7i0f5iq6GdAGa+sOhpHoPdbb3XMt99Cs6w12S+SPuRtyoGvlIWY9q1Q1jedIf5lq6hbhe9Dp2UW4fQ/q6bldLJ7QfdDRM3EWNCw01onz3X3YYDOhhXsmbiTH1gZe/EAyUEgpZwg=
*/