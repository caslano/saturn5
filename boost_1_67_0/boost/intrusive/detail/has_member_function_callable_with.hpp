//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_CALLABLE_WITH_HPP
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_CALLABLE_WITH_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

//In case no decltype and no variadics, mark that we don't support 0 arg calls due to
//compiler ICE in GCC 3.4/4.0/4.1 and, wrong SFINAE for GCC 4.2/4.3/MSVC10/MSVC11
#if defined(BOOST_NO_CXX11_DECLTYPE) && defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  if defined(BOOST_GCC) && (BOOST_GCC < 40400)
#     define BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED
#  elif defined(BOOST_INTEL) && (BOOST_INTEL < 1200)
#     define BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED
#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1800)
#     define BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED
#  endif
#endif   //#if defined(BOOST_NO_CXX11_DECLTYPE) && defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <cstddef>
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/fwd_macros.hpp>

namespace boost_intrusive_hmfcw {

typedef char yes_type;
struct no_type{ char dummy[2]; };

struct dont_care
{
   dont_care(...);
};

#if defined(BOOST_NO_CXX11_DECLTYPE)

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class T>
struct make_dontcare
{
   typedef dont_care type;
};

#endif

struct private_type
{
   static private_type p;
   private_type const &operator,(int) const;
};

template<typename T>
no_type is_private_type(T const &);
yes_type is_private_type(private_type const &);

#endif   //#if defined(BOOST_NO_CXX11_DECLTYPE)

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_DECLTYPE)

template<typename T> struct remove_cv                    {  typedef T type;   };
template<typename T> struct remove_cv<const T>           {  typedef T type;   };
template<typename T> struct remove_cv<const volatile T>  {  typedef T type;   };
template<typename T> struct remove_cv<volatile T>        {  typedef T type;   };

#endif

}  //namespace boost_intrusive_hmfcw {

#endif  //BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_CALLABLE_WITH_HPP

#ifndef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
   #error "You MUST define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME before including this header!"
#endif

#ifndef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN
   #error "You MUST define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN before including this header!"
#endif

#ifndef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX
   #error "You MUST define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX before including this header!"
#endif

#if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX < BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN
   #error "BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX value MUST be greater or equal than BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN!"
#endif

#if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX == 0
   #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF
#else
   #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF ,
#endif

#ifndef  BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG
   #error "BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG not defined!"
#endif

#ifndef  BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END
   #error "BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END not defined!"
#endif

BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_DECLTYPE)
   //With decltype and variadic templaes, things are pretty easy
   template<typename Fun, class ...Args>
   struct BOOST_MOVE_CAT(has_member_function_callable_with_,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
   {
      template<class U>
      static decltype(boost::move_detail::declval<U>().
         BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(::boost::move_detail::declval<Args>()...)
            , boost_intrusive_hmfcw::yes_type()) Test(U* f);
      template<class U>
      static boost_intrusive_hmfcw::no_type Test(...);
      static const bool value = sizeof(Test<Fun>((Fun*)0)) == sizeof(boost_intrusive_hmfcw::yes_type);
   };

#else //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_DECLTYPE)

   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////
   //
   //    has_member_function_callable_with_impl_XXX
   //    declaration, special case and 0 arg specializaton
   //
   /////////////////////////////////////////////////////////

   template <typename Type>
   class BOOST_MOVE_CAT(has_member_function_named_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
   {
      struct BaseMixin
      {
         void BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME()
         {} //Some compilers require the definition or linker errors happen
      };

      struct Base
         : public boost_intrusive_hmfcw::remove_cv<Type>::type, public BaseMixin
      {  //Declare the unneeded default constructor as some old compilers wrongly require it with is_convertible
         Base(){}
      };
      template <typename T, T t> class Helper{};

      template <typename U>
      static boost_intrusive_hmfcw::no_type  deduce
         (U*, Helper<void (BaseMixin::*)(), &U::BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME>* = 0);
      static boost_intrusive_hmfcw::yes_type deduce(...);

      public:
      static const bool value = sizeof(boost_intrusive_hmfcw::yes_type) == sizeof(deduce((Base*)0));
   };

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////
      //
      //    has_member_function_callable_with_impl_XXX for 1 to N arguments
      //
      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////

      //defined(BOOST_NO_CXX11_DECLTYPE) must be true
      template<class Fun>
      struct FunWrapTmpl : Fun
      {
         using Fun::BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME;
         FunWrapTmpl();
         template<class ...DontCares>
         boost_intrusive_hmfcw::private_type BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(DontCares...) const;
      };

      template<typename Fun, bool HasFunc, class ...Args>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME);

      //No BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME member specialization
      template<typename Fun, class ...Args>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
         <Fun, false, Args...>
      {
         static const bool value = false;
      };

      template<typename Fun, class ...Args>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun, true, Args...>
      {
         static bool const value = (sizeof(boost_intrusive_hmfcw::no_type) == sizeof(boost_intrusive_hmfcw::is_private_type
                                             ( (::boost::move_detail::declval
                                                   < FunWrapTmpl<Fun> >().
                                                   BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(::boost::move_detail::declval<Args>()...), 0) )
                                          )
                                    );
      };

      template<typename Fun, class ...Args>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
         : public BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
            <Fun
            , BOOST_MOVE_CAT(has_member_function_named_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun>::value
            , Args...>
      {};
   #else //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////
      //
      //    has_member_function_callable_with_impl_XXX specializations
      //
      /////////////////////////////////////////////////////////

      template<typename Fun, bool HasFunc BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF BOOST_MOVE_CAT(BOOST_MOVE_CLASSDFLT,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME);

      //No BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME member specialization
      template<typename Fun BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF BOOST_MOVE_CAT(BOOST_MOVE_CLASS,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
         <Fun, false BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF BOOST_MOVE_CAT(BOOST_MOVE_TARG,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)>
      {
         static const bool value = false;
      };

      #if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN == 0
         //0 arg specialization when BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME is present
         #if !defined(BOOST_NO_CXX11_DECLTYPE)

            template<typename Fun>
            struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun, true>
            {
               template<class U>
               static decltype(boost::move_detail::declval<U>().BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME()
                  , boost_intrusive_hmfcw::yes_type()) Test(U* f);

               template<class U>
               static boost_intrusive_hmfcw::no_type Test(...);
               static const bool value = sizeof(Test<Fun>((Fun*)0)) == sizeof(boost_intrusive_hmfcw::yes_type);
            };

         #else //defined(BOOST_NO_CXX11_DECLTYPE)

            #if !defined(BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)

               template<class F, std::size_t N = sizeof(boost::move_detail::declval<F>().BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(), 0)>
               struct BOOST_MOVE_CAT(zeroarg_checker_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
               {  boost_intrusive_hmfcw::yes_type dummy[N ? 1 : 2];   };

               template<typename Fun>
               struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun, true>
               {
                  template<class U> static BOOST_MOVE_CAT(zeroarg_checker_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<U>
                     Test(BOOST_MOVE_CAT(zeroarg_checker_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<U>*);
                  template<class U> static boost_intrusive_hmfcw::no_type Test(...);
                  static const bool value = sizeof(Test< Fun >(0)) == sizeof(boost_intrusive_hmfcw::yes_type);
               };

            #else //defined(BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)

               template<typename Fun>
               struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun, true>
               {  //Some compilers gives ICE when instantiating the 0 arg version so it is not supported.
                  static const bool value = true;
               };

            #endif//!defined(BOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)
         #endif   //!defined(BOOST_NO_CXX11_DECLTYPE)
      #endif   //#if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN == 0

      #if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX > 0
         //1 to N arg specialization when BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME is present
         //Declare some unneeded default constructor as some old compilers wrongly require it with is_convertible
         #if defined(BOOST_NO_CXX11_DECLTYPE)
            #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATION(N)\
            \
            template<class Fun>\
            struct BOOST_MOVE_CAT(FunWrap##N, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)\
               : Fun\
            {\
               using Fun::BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME;\
               BOOST_MOVE_CAT(FunWrap##N, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)();\
               boost_intrusive_hmfcw::private_type BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME\
                  (BOOST_MOVE_REPEAT##N(boost_intrusive_hmfcw::dont_care)) const;\
            };\
            \
            template<typename Fun, BOOST_MOVE_CLASS##N>\
            struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun, true, BOOST_MOVE_TARG##N>\
            {\
               static bool const value = (sizeof(boost_intrusive_hmfcw::no_type) == sizeof(boost_intrusive_hmfcw::is_private_type\
                                                   ( (::boost::move_detail::declval\
                                                         < BOOST_MOVE_CAT(FunWrap##N, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun> >().\
                                                      BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(BOOST_MOVE_DECLVAL##N), 0) )\
                                                )\
                                          );\
            };\
            //
         #else
            #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATION(N)\
            template<typename Fun, BOOST_MOVE_CLASS##N>\
            struct BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)\
               <Fun, true, BOOST_MOVE_TARG##N>\
            {\
               template<class U>\
               static decltype(boost::move_detail::declval<U>().\
                  BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME(BOOST_MOVE_DECLVAL##N)\
                     , boost_intrusive_hmfcw::yes_type()) Test(U* f);\
               template<class U>\
               static boost_intrusive_hmfcw::no_type Test(...);\
               static const bool value = sizeof(Test<Fun>((Fun*)0)) == sizeof(boost_intrusive_hmfcw::yes_type);\
            };\
            //
         #endif
         ////////////////////////////////////
         // Build and invoke BOOST_MOVE_ITERATE_NTOM macrofunction, note that N has to be at least 1
         ////////////////////////////////////
         #if BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN == 0
            #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATE_MIN 1
         #else
            #define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATE_MIN BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN
         #endif
         BOOST_MOVE_CAT
            (BOOST_MOVE_CAT(BOOST_MOVE_CAT(BOOST_MOVE_ITERATE_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATE_MIN), TO)
            ,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)
               (BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATION)
         #undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATION
         #undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_ITERATE_MIN
         ////////////////////////////////////
         // End of BOOST_MOVE_ITERATE_NTOM
         ////////////////////////////////////
      #endif   //BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX > 0

      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////
      //
      //       has_member_function_callable_with_FUNC
      //
      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////

      //Otherwise use the preprocessor
      template<typename Fun BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF BOOST_MOVE_CAT(BOOST_MOVE_CLASSDFLT,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)>
      struct BOOST_MOVE_CAT(has_member_function_callable_with_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
         : public BOOST_MOVE_CAT(has_member_function_callable_with_impl_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
            <Fun
            , BOOST_MOVE_CAT(has_member_function_named_, BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun>::value
            BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF BOOST_MOVE_CAT(BOOST_MOVE_TARG,BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX)>
      {};
   #endif   //defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#endif

BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

//Undef local macros
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_COMMA_IF

//Undef user defined macros
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG
#undef BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

/* has_member_function_callable_with.hpp
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
*/