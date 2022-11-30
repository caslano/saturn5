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
a7bfAEJZ/Gjcho5klnYF6xMEkkPr6TYgQ/NEx/5b9vxfCRorxeHSHXbwmIj0Judgf8HHi0A9s7Z+/nag7ZFK6JO/qMlDXsuMt4bf2iyIQmzVkFzZUZIN6YpM9VGmjtVSAfF+O8wAQCV5aZINJzdUzvYhOLiEIWgynxYOgA7AAz9BhcClo3DdnofUopQuU1Lr0/WsHsSi6aS73IEt/cf5xw7ONTQzTGf//o8s7A6IPrabdAR2CsbwXgrPc3Jt587D2PomKFzugaUQxfaM1KD1zL8LjXkpqN5nedB6tqHVn1YiOM5exp8foWWnbhy2E/76KUm1JY4FXFcQXqUvXYf8nhzg2CyDMf8/0gSaIuUFMZ3aVWAo+YB7saCR/XYvWyaBtoyd2/iZu9m7UynDYpP6ZB5JDvzw4ou0H6nf9RHTtGAwUQ3itBW1YgWZTvAwRR57MQR89G4re3CuAz2U9r1cmQtg0YA8+pYTMfCJe2HtrpABTcKdF10qExKzUH3c0H2R7+dKchK5b+kz1r1xbGS09L3TbttqATRpFH4vboPgODlwji9WMFEVm583F7rYGC1SSsoqeMJ1d7BTzcgOFKLuONTm5cyb9cTGCbQcEK/TopZmd5m9PyCBmDGtHxDUqWYt+yGdlAIirE8nfM3lDx7NLM9cb7mTzsuKEs60rrm+HscpPysziBj//ugcu9uq7mxqu1mKCfoxvyYjZlyqdjWf0Dx7PUv1L31OZchkaYTYulh3801+zXEeKDqPov4jzQklnY7VvAcXHNsq7uJJR2fr0htuJTwJyYub894b7viGWBER97RKaY9mHsDxzJgyU3jAjl6VykkaXGvzU05u645zlsvcN8Vcc4nnL7ysf/Lg421pJx2dek0DU9smDuYWKJ+1CTXl/aTOvz/9u5nRCBAmSN86rgUVM0CES985TgRY10fA2Dk6peV3lSkPnEWnNvmpZmKWfAFUH8V6uKawVLmgndtrW0/hds5P763Ax/QsTaFuXsutqpGzdjw1io+unssT+A2Z41kTIbyQREplLFazDFcksfV07L0kzVUmzpaGKBGhcPNCVzg8AMHYUlvKn+nfoK9RoasKfjlr46f5vv9mNWASFo0gfXYutOzv1ZLbjcuPZ4KQxaEEWoVP4gldgHWAa50vdsT4p4nkrNvNsOWL6GCdUYnrXjgA1BsYTvrbqLAjSm47XfW5gkZ5HqCv65Er+EmIZHTAfqCiT5d9zKWEYHvjnF6vSXf3FHr5Ps4Hsw4lquF2xkReMTBn0kKzlfUTMlvClBnPC19Zsxn3YOzO0JHDfnvkzzqZCycgnhBvgescpxM53xuZXUxaQEaCe5vUOC9Hxh984aXUDv/jocvIBbdX4CpJU5GHP6SnEpnzJHahlcZ1fTHEi/HOBuRmU3O+JevVU319YXQXuB7upLEIFBEgzYcecUKnNNUWxAyp2V6ISwPane05l+ABQ5nrCdV1BZ2giPlFf42qQAOBXV2h0OUwf+zKm8AHoJoiGIiUw72neIbqVypmHHLgkvZN7d2Y6N5jjArRTbQICzH+rALQAvMzje8UoK+3ksOItw7ZvunAJzommKWnDwtR/UCaGbVZzUnsNMWxlN5sst543HCa8xFyZGcDCTdaqw8nod0SYqHUVGaOo+Q7HuqeonRR0CEpAxpecCqoeXgR+aGuE0nRRViXbXFiw3RrFMLUAJlRpCgsZyOmUU5X1G9CeFQuN5/AyZdaaUCZ9+9UUx3gmt5grCow0VRXwpU4R6CWTDh/wgnyBchxCnIxBEO3H4/iqkblmoHabR9DnJboUntVeNQT0MWrwqRbGScahJbjiELcspdUxTJDrtqLXiEtasWGwrvrfWN82+c8CygxLZ5xUxpq+Svf5HYxvnbxgBLafjLaR1/Lit0Fl/wLmkrYxbOWKlvCvRIh7hSRmNEWB6i+FHWAkAGF3KEppxEWmgJ3k0flMOEb811M8F4YhNbdWU9kHrsxe4Q7GKEd1bwzlOepiOjl61b9NNSHiGa4XGEQcaOqcR6MSJEIEJQkCm8PZgHRq6j3B7dorwXQU48okBJ73/0dv5TK1GFhKIE+uPipeTS6wH6cnmnOi4kyV+3oHGOv2qk5z056GXmHhoTP3regFfRGMP+jePE8LkwWoy4OAGjKd9xEtQybF/EcUMyRK1r76hJQD4kaS+dCcq1WabGbeSoVTY27J9PHkL8bL0rq4gmMVWiYhpNDbalP/BJ2g9ddl0QfSrJNlEF/RB8643hbheX+KvLzAuYStstSck35ulasMrQfqZZIuoa2NJqnTI3X/hNpw7jf+sQsmYU6mHe7UkcIThLiATU3JgLdJ+S2MNOkCZJG0MA4G/tT6/hIE2JKEqc9e5Sa4cfGYVM3/71PDRaW4isE/m+9Kpvvpl215B3bGKOL6p79D0GVAkpmqWutbtaZSINFkZ8RbkZCbPgcIEDksMytdYB5OCihnGQXNGKtikWcwcy4ROvjf6eKFvyvh7Haz4xND6langdveanNB4OTtFKfcc0a6Lis7ZENeBIKTiGKYAW37fRz8kA0W7B8BhgCPa7tqLHpFzTXInRfaHvVvupydVGsBIbV1zgCawtU+Z5Fc02x3ZvI/b1NkOC50EsVhABcURK9caaYCTq40azFZJqhej/E4lG4BMSg28B01bBWDhYNzd9gtggmeXNvYcEIJTJn5wiSnbdCix7s+jqtrUJvzYljlY3eUTwmIQul5cSEclMIbxN7Dw+1CYRPpY3KY10Ps/VoGrLP63BtlDHs4ageLzNBp3PBkrGmRL+m4o/qH7GbKAyA7jhxJSKXh3F0Z+SXuiYfp3zKVYfBw5eWVoU+O+6e3anErns2xdpNJzJhkXcQPCjpbE0aAw5AK2ndx+M28+MU5gEV+ruW49MMOuhS8IfqmZHD5LN59RFWnlz6JaoXY7cf/qxNZhWhoypZbzZQuUp4c/8IJ9XGx4xhBecaG6tungaxINL03QW88aCMoa9cUBQvlOznBtKlPG6GfdQkIDTWHnqWXrgUUzS4FnE0bmtde0/Kv0oEFWuZI0XkXt/UumKc8JBsc7eR+KbT/dlngrIqyXmYFyChQcJaHSCewoNlsShwC3ox556DBLMdSyFIqDztq2ioSgFDh8L6tEF31woHyqT2i4gRQJTPOUIRAXV2XyI4mfyXkYHNnAi5sMcSHfB9Rjhb6fgnGR8QZMxnsp6LSpO6s4BfgCifCwYPQNoGegVKNK/h9URuPtnhqKHLs+awD83hCOgWM1Uil7NLSFp2pUiHdM1BwzmPzgmx7S1/GV4EKKUFNFBpvUDWf7I42jIzRxskJIAdBnr9Mwt86YhV6AbsoHG3W0LDXwf9ysbIZ5cCd35s8jpRpDFBBrlWDSvikFD8b6kiXQOCLmAjlqwQRHzu3aDUnzzHR+slruaMr5UuPj0ZLwg6o6K4AUIrGb6QdEpFagUfQMcznxlEhrYaMkhTWBFp9Rg5/pDbD7aH95mDym+CejH5Z5rWJ9dipwW5TMaKG1txwCxF/iNxfT0f3X90vLHKBTXMOma3tZIjDwu4+qGdfsUpboRHN4tkPWkB//duHITnYAmcotHzfjTYM/8xx0+yjrZy2YsdFlt4jwM8LuBeyT5OMV/GQKjUr9RdV5IK/Jo1VjLIWiCOiUGAEIrx92dD8I86uhS1vMBd/+1O8SijGaBzLIjdaKfZX/mWgfgnNmdT3SmJ4cwAmafzd8HljWmKH3hw/gQGqDvTlCfM6iC/QczMlf22o50W6qX58jqCGSA1suCqFrQbME905eesYkr9Tc1Ndg3E3dLR+zf0W2F+sTJqvb4BdtYQzU59Pu/YnXoa0qrrMyRnYmwQdOOu+Ax61k8QQ87jxWxdzibyEgRqjjlRNI1ObGLSlBiUOMBk/Qadem2LgsckqeMq1CvA98SEdcO3YNoVElzHqS8jC0cVhLEQFixx1v787FpPySUzTevKckKP3jmYfxOzRO0SStTTHJQEwmbcb2uP5bEX1I5tmc1w5fojo3RlbwNAPfi4iCbLhcWPYBndH6qQeLT/YPKT2tcmWLyODJYkVGK3BCUNGcIf62yIYNyDs429R826KrV4xUrvTZPfMyaiJFEnAAAs/9O6dypY2ts8NVOCwSKIVhXSaOMb8hFiee1+4mCPFWvtlEwLBWuAlCNa2C+dsqh4KeQjBMYmTiV8B0JF6mBYKwApYcA3CFfOy2m3IZnxJz/YTNR+vvJ2RGl4sxXpV9YpRendhuExPvSiFLSSj3XB9fVe07rvF3RNlfYf2j7HbakyBNcfzKFIsIyxV/mUmDWno2qchxOu1UjRxl/m7qxSkiXkxeDtvaheAHUSFOiW6P0ShJakb5/J/X78F+xHYfTTfkKso868NDOKEfTRn+gmFT/dcRw/1UOox1wyvBiUMO1YD4WfWIgv2JFRmPG3YyEigGPiBQUFDS6h/9IYvAORlvblzrou4PNjYJ+39Q6XrNgfphpHEtp2EjtBCH8IhvijUfCpttWh6Wc2FFctN7/y8+k/FYIZ1QHPmIRThEPWQnFxCtNnHLrHurteAUrBeVusNCs6ZkwHxUz6QCMgHVvlCkTQ/uNS5d2jtqtQdc8csDKUeKxLvSPO/uTMjDt8FKSOh8GqldYKiU7QiFEpG9nscHy3drt/be9Z+z5srKq6vFZxkjuqkDVu+LffeXoQKBk9t6mty7gCArZGk1F8/xrkQrYHfkO3thwxKiwhj/zkBy/+GMC5JO8Om6BG1i2mMv96HNNAnuVyDEaF50MSUF7GNqAL4PWPjSPYqbBquHvWQHZpuK8J8uqPe12qaT/IdypbupT8outbworYCF7ZrQruCitQwlSzYyKV11ROIr2G4sO7Dq3VG6DXZWGnTpneP3scE0W24czTYOsFfvgeeOP4sIDzEaEpfXqT1ikph2Ng41l/9ITNuVzngkMEwwR7bOSUlIh6u9IHNbFZzX1n+O+w3mRT38yxa2tfXloQqpcGiuFhlVV8G8GIIMUwJ1rP5Y9HRZOZ2YhxNpnsuUNiKkFuI5j6VZHGyErxAnR2FP6ZT+aj3KFH5XXvYoJw+DyuZNoQlemJhOGsEi1Lg0DK3QqxklQfPS7qzllsLvnA3Fl0hoWf258/pYaS1r3L/FYyVoAb1dCXbXkERKubGu49zs0hRFX9aQBgIucp2Jv/zMtHkIXhu2r4pM3y4VVb9FiTA1j38v3dx2l4yyBnxKttJqQcexCQfNHqtiDBEbxhXF+eERQEaYYkor5Tg/8sxhIuCZSlQuUeHWqS4/IDdIhuRIyKkjbJuOOTLlC9xNBzvO/Yiaym/tEQRUYPhdXfrx1M4t5q8D2moFNMjauCzlc/lRYgM+lKHvtXO0bgbw6dkTMb8eR3wmd0wRPwzoFgsbSjVgSdh5dQ8UebF3r6MipXLDWBJdhnMj+7BmKngJE4nIFVzt6A9UPYN7LpJkjxAAMGsUy1RidFcDetXi+p9P0PbPA6PgbS6J0mtm5fGqJaPeO2q+GLAIVTYwVMpTEBsVo4mcJPcGOmJ8xgaDP0MhLSxI+o36FqDCnL0na0hhY+jduY/r81KjFMlH3ZawiXzQnlczuzp0nEsHvRhkCBDFS4ePLIi5EkVm0ZOguyOjRp2QVSg3mCRnqE1bP1B2HwMixS2f4s2P2FOK4W9Xo2khQEGgqVSwM0oUZzW4ueEDYPdJ1ifUoi1K7GR1j+uMauRlJ9s2Qjjhzb8yCRdh7Y0E1MmNTln4H3Oxt99ydVuelyrXoCwdZ7w9hZdWq4wjA7H3TDo0dO+tzWCt8tIXDj0cpZ3b99YD+ADiHD5rsUzf4zsxscHmtXe+XEehrXUlT3uSkjT1jJ4rlvLhJ51YA3yeBiJ88Fi2ZLwEP7EtnrGCDA8jWAeVKuV1dBNBCh+FnNrxI+en6b+ff+6caCnzdePdctknkr0a/ty03fUdHvpjPbtbWFQVV8ntxqdB136QXpR9OzeY18PaU2xrymsG+KHLwwSuA+9W9Ww/iqldz1sk0cdB5y6RqCsUKXsc/PO0zuxj+ePJkwHcn+tDHK+Gb/zJak0Dj/HktcC86fwhSL3pYIzEH7xsPTp0xGPygOkTV8N0kVCz0LqA0mLBcy+34Dv+L5Qv6bKLj641UpTNenRB51+FbJtsnVuunqEFUP9fCeTSI38Uly82PTt+YdCXqcQuYLQZzquMZrh52LbXGWrnRVLP2wBcJ2OAZ68phumulTRCKW54uH80P3u9/jq9C37nyTxHNaKYruJrUpjeie6gemaVrvhvFrZZcyJQPwK7zQzt3rPgUqH+2xD0fMK3jrPZc9Xm5SJ0D6RJ/QuKjlXIPbdzG9Of+w2f03GXqq9crR36Mn3SfkGEbrTCjrQ8/UHFVZXsMIqlhDO8yl/epTb85vBEdzHVxbKDR5nwm+vQCPsAAGecxEj621gI+DZsyV6xQjdxQP3NUPH6dsd+06Z6zZJ0e85VY9+GxwKruwIf+S68rAlkcpWUd3LLGA77QOOLHQztROq8SC7bNXjYJ1RzCFrE7VLLo0FjPAlPrHAfqD3C5e2ptJgTKs560N/JhSCBr1SYjfeedka0z2wD8ei5m8xqZq96O5o7TcuK/7+IO9V6/dKhlD8kcvTpfwLV6MFzpqb3GbF6SFqSl6KhB8GMl8WiCes6e+nPxVFX7HREAt+ptUM20uNANBY9MPM3dzTDpAjUPypNXwT1CAoEfvlQYetz7rMBY3IEnE3ntPaYFV9oBbgI9GzteuB+Via850VCOHYSGsyyPW1wvuC7o1Kbw+DYmjLAh9JjQd7aVgZht+dN6svwyP6846ZHKB9qH0I73Oe64QYy1B/DKw9bwtVivXKOCU1yRXSTIxoBTym91K3G1Mc0z/tkJKjR2GHF5dmkmZWw5lEujQvkodX3OHf247TqgTv49Ubsl3k+dQql24KSpAYbKZG+Y/s4ekcElszr93E11rYDaJZ8zgNqZjdYZlbR41EPmqFbsGWAehe+epWJDvX30tCK4ZUHvWzaaj/RlYpZsMiDF3U1Jy+lX+RwcHtEunq4dFdEXdzn0uMowEyT8UKEsMvFI0HN3aXeVkr+WceHewtE5WNn+TY7FCVP0oNbJ85CearYTpGE8Zc33kq6rZbNukqhRFWORVjEi8KVsj3LkceyuM3WLY3cgbylDPLG89CKysnR/p/IPWqZRLMsaKNtcSJpwh3KDx21cyPVMp6EUbvP/wpjHeM8nJZzwZ87UaU4RaNO8TcKJ8aMr0P53KD1VDkqvufDuELG78PtwS4+XAyP58M/vG/EiNXnpUEh4XZYQOBY+KTr+0kXe5UbIBdLj8SFjtCKSRVRSTIoGylHsMhaG3rrw6EEgIKrVqR6L6yryRCrBCrLGfF2BGrN3Et8qXld6d8gz4zcuMCMlVsdpFUXY5V71W3vVEx3v7d0JCh11Zpl3Rv96Id3CbRCYiS95dpGVZEyXIpUL6IhVz7xIOLh7YlO5pdNqT1y2sQHtyZ+npt0ybGs/N/P3d3odUpg8LRvaDlDcj1VAi+WvMqDkx1ZMMmmuI5EsQbPg4/JmbxwVvMfrmD3uFcTZqK/oEWSBczmjuznfDyDw5JrqJZIE+dlt2Xmci6uZUBuWY6WhJH9EQSp+b
*/