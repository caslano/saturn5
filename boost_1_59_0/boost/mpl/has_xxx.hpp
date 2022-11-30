
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

#if BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0x590) )
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

#   elif BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0x590) )

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
          template< BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_INC(n), typename V) > class V \
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
             template< BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_INC(n), typename U) > class U \
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