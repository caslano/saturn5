
#ifndef BOOST_MPL_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2006
// Copyright David Abrahams 2002-2003
// Copyright Daniel Walker 2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#if BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x590) )
# include <boost/type_traits/is_class.hpp>
#endif

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX)

#   if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

// agurt, 11/sep/02: MSVC-specific version (< 7.1), based on a USENET 
// newsgroup's posting by John Madsen (comp.lang.c++.moderated, 
// 1999-11-12 19:17:06 GMT); the code is _not_ standard-conforming, but 
// it works way more reliably than the SFINAE-based implementation

// Modified dwa 8/Oct/02 to handle reference types.

#   include <boost/mpl/if.hpp>
#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl { namespace aux {

struct has_xxx_tag;

#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
template< typename U > struct msvc_incomplete_array
{
    typedef char (&type)[sizeof(U) + 1];
};
#endif

template< typename T >
struct msvc_is_incomplete
{
    // MSVC is capable of some kinds of SFINAE.  If U is an incomplete
    // type, it won't pick the second overload
    static char tester(...);

#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    template< typename U >
    static typename msvc_incomplete_array<U>::type tester(type_wrapper<U>);
#else
    template< typename U >
    static char (& tester(type_wrapper<U>) )[sizeof(U)+1];
#endif 
    
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(tester(type_wrapper<T>())) == 1
        );
};

template<>
struct msvc_is_incomplete<int>
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}}}

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, default_) \
template< typename T, typename name = ::boost::mpl::aux::has_xxx_tag > \
struct BOOST_PP_CAT(trait,_impl) : T \
{ \
    static boost::mpl::aux::no_tag \
    test(void(*)(::boost::mpl::aux::has_xxx_tag)); \
    \
    static boost::mpl::aux::yes_tag test(...); \
    \
    BOOST_STATIC_CONSTANT(bool, value = \
          sizeof(test(static_cast<void(*)(name)>(0))) \
            != sizeof(boost::mpl::aux::no_tag) \
        ); \
    typedef boost::mpl::bool_<value> type; \
}; \
\
template< typename T, typename fallback_ = boost::mpl::bool_<default_> > \
struct trait \
    : boost::mpl::if_c< \
          boost::mpl::aux::msvc_is_incomplete<T>::value \
        , boost::mpl::bool_<false> \
        , BOOST_PP_CAT(trait,_impl)<T> \
        >::type \
{ \
}; \
\
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, void) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, bool) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed short) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned short) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed int) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned int) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed long) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned long) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, float) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, double) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, long double) \
/**/

#   define BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, T) \
template<> struct trait<T> \
{ \
    BOOST_STATIC_CONSTANT(bool, value = false); \
    typedef boost::mpl::bool_<false> type; \
}; \
/**/

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, unused) \
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, unused) \
    BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, wchar_t) \
/**/
#else
#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, unused) \
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, unused) \
/**/
#endif


// SFINAE-based implementations below are derived from a USENET newsgroup's 
// posting by Rani Sharoni (comp.lang.c++.moderated, 2002-03-17 07:45:09 PST)

#   elif BOOST_WORKAROUND(BOOST_MSVC, <= 1400) \
      || (BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1800)) && defined(__CUDACC__)) \
      || BOOST_WORKAROUND(__IBMCPP__, <= 700)

// MSVC 7.1 & MSVC 8.0 & VACPP

// agurt, 15/jun/05: replace overload-based SFINAE implementation with SFINAE
// applied to partial specialization to fix some apparently random failures 
// (thanks to Daniel Wallin for researching this!)

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T > \
struct BOOST_PP_CAT(trait, _msvc_sfinae_helper) \
{ \
    typedef void type; \
};\
\
template< typename T, typename U = void > \
struct BOOST_PP_CAT(trait,_impl_) \
{ \
    BOOST_STATIC_CONSTANT(bool, value = false); \
    typedef boost::mpl::bool_<value> type; \
}; \
\
template< typename T > \
struct BOOST_PP_CAT(trait,_impl_)< \
      T \
    , typename BOOST_PP_CAT(trait, _msvc_sfinae_helper)< typename T::name >::type \
    > \
{ \
    BOOST_STATIC_CONSTANT(bool, value = true); \
    typedef boost::mpl::bool_<value> type; \
}; \
\
template< typename T, typename fallback_ = boost::mpl::bool_<default_> > \
struct trait \
    : BOOST_PP_CAT(trait,_impl_)<T> \
{ \
}; \
/**/

#   elif BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x590) )

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_BCB_DEF(trait, trait_tester, name, default_) \
template< typename T, bool IS_CLASS > \
struct trait_tester \
{ \
    BOOST_STATIC_CONSTANT( bool,  value = false ); \
}; \
template< typename T > \
struct trait_tester< T, true > \
{ \
    struct trait_tester_impl \
    { \
        template < class U > \
        static int  resolve( boost::mpl::aux::type_wrapper<U> const volatile * \
                           , boost::mpl::aux::type_wrapper<typename U::name >* = 0 ); \
        static char resolve( ... ); \
    }; \
    typedef boost::mpl::aux::type_wrapper<T> t_; \
    BOOST_STATIC_CONSTANT( bool, value = ( sizeof( trait_tester_impl::resolve( static_cast< t_ * >(0) ) ) == sizeof(int) ) ); \
}; \
template< typename T, typename fallback_ = boost::mpl::bool_<default_> > \
struct trait           \
{                      \
    BOOST_STATIC_CONSTANT( bool, value = (trait_tester< T, boost::is_class< T >::value >::value) );     \
    typedef boost::mpl::bool_< trait< T, fallback_ >::value > type; \
};

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_BCB_DEF( trait \
                                         , BOOST_PP_CAT(trait,_tester)      \
                                         , name       \
                                         , default_ ) \
/**/

#   else // other SFINAE-capable compilers

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T, typename fallback_ = boost::mpl::bool_<default_> > \
struct trait \
{ \
    struct gcc_3_2_wknd \
    { \
        template< typename U > \
        static boost::mpl::aux::yes_tag test( \
              boost::mpl::aux::type_wrapper<U> const volatile* \
            , boost::mpl::aux::type_wrapper<BOOST_MSVC_TYPENAME U::name>* = 0 \
            ); \
    \
        static boost::mpl::aux::no_tag test(...); \
    }; \
    \
    typedef boost::mpl::aux::type_wrapper<T> t_; \
    BOOST_STATIC_CONSTANT(bool, value = \
          sizeof(gcc_3_2_wknd::test(static_cast<t_*>(0))) \
            == sizeof(boost::mpl::aux::yes_tag) \
        ); \
    typedef boost::mpl::bool_<value> type; \
}; \
/**/

#   endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)


#else // BOOST_MPL_CFG_NO_HAS_XXX

// placeholder implementation

#   define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T, typename fallback_ = boost::mpl::bool_<default_> > \
struct trait \
{ \
    BOOST_STATIC_CONSTANT(bool, value = fallback_::value); \
    typedef fallback_ type; \
}; \
/**/

#endif

#define BOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(BOOST_PP_CAT(has_,name), name, false) \
/**/


#if !defined(BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)

// Create a boolean Metafunction to detect a nested template
// member. This implementation is based on a USENET newsgroup's
// posting by Aleksey Gurtovoy (comp.lang.c++.moderated, 2002-03-19),
// Rani Sharoni's USENET posting cited above, the non-template has_xxx
// implementations above, and discussion on the Boost mailing list.

#   if !defined(BOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES)
#     if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#       define BOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES 1
#     else
#       define BOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES 0
#     endif
#   endif

#   if !defined(BOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION)
#     if (defined(BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS))
#       define BOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION 1
#     else
#       define BOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION 0
#     endif
#   endif

#   if !defined(BOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE)
#     if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#       define BOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE 1
#     else
#       define BOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE 0
#     endif
#   endif

// NOTE: Many internal implementation macros take a Boost.Preprocessor
// array argument called args which is of the following form.
//           ( 4, ( trait, name, max_arity, default_ ) )

#   define BOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) \
      BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, args) , _introspect) \
    /**/

#   define BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
      BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, args) , _substitute), n) \
    /**/

#   define BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args) \
      BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, args) , _test) \
    /**/

// Thanks to Guillaume Melquiond for pointing out the need for the
// "substitute" template as an argument to the overloaded test
// functions to get SFINAE to work for member templates with the
// correct name but different number of arguments.
#   define BOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE(z, n, args) \
      template< \
          template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), typename V) > class V \
       > \
      struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) { \
      }; \
    /**/

#   define BOOST_MPL_HAS_MEMBER_SUBSTITUTE(args, substitute_macro) \
      BOOST_PP_REPEAT( \
          BOOST_PP_ARRAY_ELEM(2, args) \
        , BOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE \
        , args \
      ) \
    /**/

#   if !BOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION
#     define BOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
        template< typename V > \
        static boost::mpl::aux::no_tag \
        BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)(...); \
      /**/
#   else
#     define BOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
        static boost::mpl::aux::no_tag \
        BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)(...); \
      /**/
#   endif

#   if !BOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES
#     define BOOST_MPL_HAS_MEMBER_MULTI_ACCEPT(z, n, args) \
        template< typename V > \
        static boost::mpl::aux::yes_tag \
        BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
            boost::mpl::aux::type_wrapper< V > const volatile* \
          , BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) < \
                V::template BOOST_PP_ARRAY_ELEM(1, args) \
            >* = 0 \
        ); \
      /**/
#     define BOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
        BOOST_PP_REPEAT( \
            BOOST_PP_ARRAY_ELEM(2, args) \
          , BOOST_MPL_HAS_MEMBER_MULTI_ACCEPT \
          , args \
        ) \
      /**/
#   else
#     define BOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
        template< typename V > \
        static boost::mpl::aux::yes_tag \
        BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
            V const volatile* \
          , member_macro(args, V, T)* = 0 \
        ); \
      /**/
#   endif

#   if !BOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION
#     define BOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof(BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< U >(0)) \
              == sizeof(boost::mpl::aux::yes_tag) \
      /**/
#   else
#     if !BOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES
#       define BOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof( \
              BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
                  static_cast< boost::mpl::aux::type_wrapper< U >* >(0) \
              ) \
          ) == sizeof(boost::mpl::aux::yes_tag) \
        /**/
#     else
#       define BOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof( \
              BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
                  static_cast< U* >(0) \
              ) \
          ) == sizeof(boost::mpl::aux::yes_tag) \
        /**/
#     endif
#   endif

#   define BOOST_MPL_HAS_MEMBER_INTROSPECT( \
               args, substitute_macro, member_macro \
           ) \
      template< typename U > \
      struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) { \
          BOOST_MPL_HAS_MEMBER_SUBSTITUTE(args, substitute_macro) \
          BOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
          BOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
          BOOST_STATIC_CONSTANT( \
              bool, value = BOOST_MPL_HAS_MEMBER_TEST(args) \
          ); \
          typedef boost::mpl::bool_< value > type; \
      }; \
    /**/

#   define BOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
               args, introspect_macro, substitute_macro, member_macro \
           ) \
      template< \
          typename T \
        , typename fallback_ \
              = boost::mpl::bool_< BOOST_PP_ARRAY_ELEM(3, args) > \
      > \
      class BOOST_PP_ARRAY_ELEM(0, args) { \
          introspect_macro(args, substitute_macro, member_macro) \
      public: \
          static const bool value \
              = BOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args)< T >::value; \
          typedef typename BOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args)< \
              T \
          >::type type; \
      }; \
    /**/

// BOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE expands to the full
// implementation of the function-based metafunction. Compile with -E
// to see the preprocessor output for this macro.
#   define BOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE( \
               args, substitute_macro, member_macro \
           ) \
      BOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
          args \
        , BOOST_MPL_HAS_MEMBER_INTROSPECT \
        , substitute_macro \
        , member_macro \
      ) \
    /**/

#   if BOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE

#     if !defined(BOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE)
#       if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#         define BOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE 1
#       endif
#     endif

#     if !BOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE
#       define BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                   args, n \
               ) \
          BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
        /**/
#     else
#       define BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                   args, n \
               ) \
          BOOST_PP_CAT( \
              boost_mpl_has_xxx_ \
            , BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
          ) \
        /**/
#     endif

#     define BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME( \
                 args \
             ) \
        BOOST_PP_CAT( \
            BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                args, 0 \
            ) \
          , _tag \
        ) \
      /**/

#     define BOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
                 z, n, args \
             ) \
        template< \
             template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), typename U) > class U \
        > \
        struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                args, n \
               ) { \
            typedef \
                BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args) \
                type; \
        }; \
      /**/

#     define BOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro \
             ) \
        typedef void \
            BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args); \
        BOOST_PP_REPEAT( \
            BOOST_PP_ARRAY_ELEM(2, args) \
          , BOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE_WITH_TEMPLATE_SFINAE \
          , args \
        ) \
      /**/

#     define BOOST_MPL_HAS_MEMBER_REJECT_WITH_TEMPLATE_SFINAE( \
                 args, member_macro \
             ) \
        template< \
            typename U \
          , typename V \
                = BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args) \
        > \
        struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args) { \
            BOOST_STATIC_CONSTANT(bool, value = false); \
            typedef boost::mpl::bool_< value > type; \
        }; \
      /**/

#     define BOOST_MPL_HAS_MEMBER_MULTI_ACCEPT_WITH_TEMPLATE_SFINAE( \
                 z, n, args \
             ) \
        template< typename U > \
        struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< \
            U \
          , typename \
                BOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                    args, n \
                )< \
                    BOOST_MSVC_TYPENAME U::BOOST_PP_ARRAY_ELEM(1, args)< > \
                >::type \
        > { \
            BOOST_STATIC_CONSTANT(bool, value = true); \
            typedef boost::mpl::bool_< value > type; \
        }; \
      /**/

#     define BOOST_MPL_HAS_MEMBER_ACCEPT_WITH_TEMPLATE_SFINAE( \
                 args, member_macro \
             ) \
        BOOST_PP_REPEAT( \
            BOOST_PP_ARRAY_ELEM(2, args) \
          , BOOST_MPL_HAS_MEMBER_MULTI_ACCEPT_WITH_TEMPLATE_SFINAE \
          , args \
        ) \
      /**/

#     define BOOST_MPL_HAS_MEMBER_INTROSPECT_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro, member_macro \
             ) \
        BOOST_MPL_HAS_MEMBER_REJECT_WITH_TEMPLATE_SFINAE(args, member_macro) \
        BOOST_MPL_HAS_MEMBER_ACCEPT_WITH_TEMPLATE_SFINAE(args, member_macro) \
        template< typename U > \
        struct BOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) \
            : BOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< U > { \
        }; \
      /**/
 
// BOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE expands to the full
// implementation of the template-based metafunction. Compile with -E
// to see the preprocessor output for this macro.
//
// Note that if BOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE is
// defined BOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE needs
// to be expanded at namespace level before
// BOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE can be used.
#     define BOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro, member_macro \
             ) \
        BOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
            args, substitute_macro \
        ) \
        BOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
            args \
          , BOOST_MPL_HAS_MEMBER_INTROSPECT_WITH_TEMPLATE_SFINAE \
          , substitute_macro \
          , member_macro \
        ) \
      /**/

#   endif // BOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE

// Note: In the current implementation the parameter and access macros
// are no longer expanded.
#   if !BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#     define BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
        BOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE( \
            ( 4, ( trait, name, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, default_ ) ) \
          , BOOST_MPL_HAS_MEMBER_TEMPLATE_SUBSTITUTE_PARAMETER \
          , BOOST_MPL_HAS_MEMBER_TEMPLATE_ACCESS \
        ) \
      /**/
#   else
#     define BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
        BOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE( \
            ( 4, ( trait, name, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, default_ ) ) \
          , BOOST_MPL_HAS_MEMBER_TEMPLATE_SUBSTITUTE_PARAMETER \
          , BOOST_MPL_HAS_MEMBER_TEMPLATE_ACCESS \
        ) \
      /**/
#   endif

#else // BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

// placeholder implementation

#   define BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
      template< typename T \
              , typename fallback_ = boost::mpl::bool_< default_ > > \
      struct trait { \
          BOOST_STATIC_CONSTANT(bool, value = fallback_::value); \
          typedef fallback_ type; \
      }; \
    /**/

#endif // BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#   define BOOST_MPL_HAS_XXX_TEMPLATE_DEF(name) \
      BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF( \
          BOOST_PP_CAT(has_, name), name, false \
      ) \
    /**/

#endif // BOOST_MPL_HAS_XXX_HPP_INCLUDED

/* has_xxx.hpp
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
*/