
#ifndef BOOST_MPL_ASSERT_HPP_INCLUDED
#define BOOST_MPL_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

#include <boost/mpl/aux_/config/nttp.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/pp_counter.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>

#include <boost/config.hpp> // make sure 'size_t' is placed into 'std'
#include <cstddef>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1700)
#include <boost/mpl/if.hpp>
#endif

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610)) \
    || (BOOST_MPL_CFG_GCC != 0) \
    || BOOST_WORKAROUND(__IBMCPP__, <= 600)
#   define BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES
#endif

#if BOOST_WORKAROUND(__MWERKS__, < 0x3202) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
    || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610)) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER
#endif

// agurt, 10/nov/06: use enums for Borland (which cannot cope with static constants) 
// and GCC (which issues "unused variable" warnings when static constants are used 
// at a function scope)
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610)) \
    || (BOOST_MPL_CFG_GCC != 0) || (BOOST_MPL_CFG_GPU != 0) || defined(__PGI)
#   define BOOST_MPL_AUX_ASSERT_CONSTANT(T, expr) enum { expr }
#else
#   define BOOST_MPL_AUX_ASSERT_CONSTANT(T, expr) BOOST_STATIC_CONSTANT(T, expr)
#endif


BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

struct failed {};

// agurt, 24/aug/04: MSVC 7.1 workaround here and below: return/accept 
// 'assert<false>' by reference; can't apply it unconditionally -- apparently it
// degrades the quality of GCC diagnostics
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#   define AUX778076_ASSERT_ARG(x) x&
#else
#   define AUX778076_ASSERT_ARG(x) x
#endif

template< bool C >  struct assert        { typedef void* type; };
template<>          struct assert<false> { typedef AUX778076_ASSERT_ARG(assert) type; };

template< bool C >
int assertion_failed( typename assert<C>::type );

template< bool C >
struct assertion
{
    static int failed( assert<false> );
};

template<>
struct assertion<true>
{
    static int failed( void* );
};

struct assert_
{
#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
    template< typename T1, typename T2 = na, typename T3 = na, typename T4 = na > struct types {};
#endif
    static assert_ const arg;
    enum relations { equal = 1, not_equal, greater, greater_equal, less, less_equal };
};


#if !defined(BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)

bool operator==( failed, failed );
bool operator!=( failed, failed );
bool operator>( failed, failed );
bool operator>=( failed, failed );
bool operator<( failed, failed );
bool operator<=( failed, failed );

#if defined(__EDG_VERSION__)
template< bool (*)(failed, failed), long x, long y > struct assert_relation {};
#   define BOOST_MPL_AUX_ASSERT_RELATION(x, y, r) assert_relation<r,x,y>
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, x), BOOST_MPL_AUX_NTTP_DECL(long, y), bool (*)(failed, failed) > 
struct assert_relation {};
#   define BOOST_MPL_AUX_ASSERT_RELATION(x, y, r) assert_relation<x,y,r>
#endif

#else // BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES

boost::mpl::aux::weighted_tag<1>::type operator==( assert_, assert_ );
boost::mpl::aux::weighted_tag<2>::type operator!=( assert_, assert_ );
boost::mpl::aux::weighted_tag<3>::type operator>(  assert_, assert_ );
boost::mpl::aux::weighted_tag<4>::type operator>=( assert_, assert_ );
boost::mpl::aux::weighted_tag<5>::type operator<( assert_, assert_ );
boost::mpl::aux::weighted_tag<6>::type operator<=( assert_, assert_ );

template< assert_::relations r, long x, long y > struct assert_relation {};

#endif 

#if BOOST_WORKAROUND(BOOST_MSVC, == 1700)

template<class Pred>
struct extract_assert_pred;

template<class Pred>
struct extract_assert_pred<void(Pred)> { typedef Pred type; };

template<class Pred>
struct eval_assert {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename P::type p_type;
    typedef typename ::boost::mpl::if_c<p_type::value,
        AUX778076_ASSERT_ARG(assert<false>),
        failed ************ P::************
    >::type type;
};

template<class Pred>
struct eval_assert_not {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename P::type p_type;
    typedef typename ::boost::mpl::if_c<!p_type::value,
        AUX778076_ASSERT_ARG(assert<false>),
        failed ************ ::boost::mpl::not_<P>::************
    >::type type;
};

template< typename T >
T make_assert_arg();

#elif !defined(BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)

template< bool > struct assert_arg_pred_impl { typedef int type; };
template<> struct assert_arg_pred_impl<true> { typedef void* type; };

template< typename P > struct assert_arg_pred
{
    typedef typename P::type p_type;
    typedef typename assert_arg_pred_impl< p_type::value >::type type;
};

template< typename P > struct assert_arg_pred_not
{
    typedef typename P::type p_type;
    BOOST_MPL_AUX_ASSERT_CONSTANT( bool, p = !p_type::value );
    typedef typename assert_arg_pred_impl<p>::type type;
};

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#define BOOST_MPL_IGNORE_PARENTHESES_WARNING
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

template< typename Pred >
failed ************ (Pred::************
      assert_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type )
    );

template< typename Pred >
failed ************ (boost::mpl::not_<Pred>::************
      assert_not_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type )
    );

#ifdef BOOST_MPL_IGNORE_PARENTHESES_WARNING
#undef BOOST_MPL_IGNORE_PARENTHESES_WARNING
#pragma GCC diagnostic pop
#endif

template< typename Pred >
AUX778076_ASSERT_ARG(assert<false>)
assert_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type );

template< typename Pred >
AUX778076_ASSERT_ARG(assert<false>)
assert_not_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type );


#else // BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER
        
template< bool c, typename Pred > struct assert_arg_type_impl
{
    typedef failed      ************ Pred::* mwcw83_wknd;
    typedef mwcw83_wknd ************* type;
};

template< typename Pred > struct assert_arg_type_impl<true,Pred>
{
    typedef AUX778076_ASSERT_ARG(assert<false>) type;
};

template< typename Pred > struct assert_arg_type
    : assert_arg_type_impl< BOOST_MPL_AUX_VALUE_WKND(BOOST_MPL_AUX_NESTED_TYPE_WKND(Pred))::value, Pred >
{
};

template< typename Pred >
typename assert_arg_type<Pred>::type 
assert_arg(void (*)(Pred), int);

template< typename Pred >
typename assert_arg_type< boost::mpl::not_<Pred> >::type 
assert_not_arg(void (*)(Pred), int);

#   if !defined(BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)
template< long x, long y, bool (*r)(failed, failed) >
typename assert_arg_type_impl< false,BOOST_MPL_AUX_ASSERT_RELATION(x,y,r) >::type
assert_rel_arg( BOOST_MPL_AUX_ASSERT_RELATION(x,y,r) );
#   else
template< assert_::relations r, long x, long y >
typename assert_arg_type_impl< false,assert_relation<r,x,y> >::type
assert_rel_arg( assert_relation<r,x,y> );
#   endif

#endif // BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER

#undef AUX778076_ASSERT_ARG

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#if BOOST_WORKAROUND(BOOST_MSVC, == 1700)

// BOOST_MPL_ASSERT((pred<x,...>))

#define BOOST_MPL_ASSERT(pred) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          boost::mpl::assertion_failed<false>( \
              boost::mpl::make_assert_arg< \
                  typename boost::mpl::eval_assert<void pred>::type \
                >() \
            ) \
        ) \
    ) \
/**/

// BOOST_MPL_ASSERT_NOT((pred<x,...>))

#define BOOST_MPL_ASSERT_NOT(pred) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          boost::mpl::assertion_failed<false>( \
              boost::mpl::make_assert_arg< \
                  typename boost::mpl::eval_assert_not<void pred>::type \
                >() \
            ) \
        ) \
    ) \
/**/

#else

// BOOST_MPL_ASSERT((pred<x,...>))

#define BOOST_MPL_ASSERT(pred) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          boost::mpl::assertion_failed<false>( \
              boost::mpl::assert_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
    ) \
/**/

// BOOST_MPL_ASSERT_NOT((pred<x,...>))

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MPL_ASSERT_NOT(pred) \
enum { \
      BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          boost::mpl::assertion<false>::failed( \
              boost::mpl::assert_not_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
}\
/**/
#else
#   define BOOST_MPL_ASSERT_NOT(pred) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          boost::mpl::assertion_failed<false>( \
              boost::mpl::assert_not_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
   ) \
/**/
#endif

#endif

// BOOST_MPL_ASSERT_RELATION(x, ==|!=|<=|<|>=|>, y)

#if defined(BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)

#   if !defined(BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)
// agurt, 9/nov/06: 'enum' below is a workaround for gcc 4.0.4/4.1.1 bugs #29522 and #29518
#   define BOOST_MPL_ASSERT_RELATION_IMPL(counter, x, rel, y)      \
enum { BOOST_PP_CAT(mpl_assert_rel_value,counter) = (x rel y) }; \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        boost::mpl::assertion_failed<BOOST_PP_CAT(mpl_assert_rel_value,counter)>( \
            (boost::mpl::failed ************ ( boost::mpl::assert_relation< \
                  boost::mpl::assert_::relations( sizeof( \
                      boost::mpl::assert_::arg rel boost::mpl::assert_::arg \
                    ) ) \
                , x \
                , y \
                >::************)) 0 ) \
        ) \
    ) \
/**/
#   else
#   define BOOST_MPL_ASSERT_RELATION_IMPL(counter, x, rel, y)    \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assert_rel,counter) = sizeof( \
          boost::mpl::assert_::arg rel boost::mpl::assert_::arg \
        ) \
    ); \
BOOST_MPL_AUX_ASSERT_CONSTANT( bool, BOOST_PP_CAT(mpl_assert_rel_value,counter) = (x rel y) ); \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        boost::mpl::assertion_failed<BOOST_PP_CAT(mpl_assert_rel_value,counter)>( \
              boost::mpl::assert_rel_arg( boost::mpl::assert_relation< \
                  boost::mpl::assert_::relations(BOOST_PP_CAT(mpl_assert_rel,counter)) \
                , x \
                , y \
                >() ) \
            ) \
        ) \
    ) \
/**/
#   endif

#   define BOOST_MPL_ASSERT_RELATION(x, rel, y) \
BOOST_MPL_ASSERT_RELATION_IMPL(BOOST_MPL_AUX_PP_COUNTER(), x, rel, y) \
/**/

#else // !BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES

#   if defined(BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)
#   define BOOST_MPL_ASSERT_RELATION(x, rel, y) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
        boost::mpl::assertion_failed<(x rel y)>( boost::mpl::assert_rel_arg( \
              boost::mpl::BOOST_MPL_AUX_ASSERT_RELATION(x,y,(&boost::mpl::operator rel))() \
            ) ) \
        ) \
    ) \
/**/
#   else
#   define BOOST_MPL_ASSERT_RELATION(x, rel, y) \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,BOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
        boost::mpl::assertion_failed<(x rel y)>( (boost::mpl::failed ************ ( \
            boost::mpl::BOOST_MPL_AUX_ASSERT_RELATION(x,y,(&boost::mpl::operator rel))::************))0 ) \
        ) \
    ) \
/**/
#   endif

#endif


// BOOST_MPL_ASSERT_MSG( (pred<x,...>::value), USER_PROVIDED_MESSAGE, (types<x,...>) ) 

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202))
#   define BOOST_MPL_ASSERT_MSG_IMPL( counter, c, msg, types_ ) \
struct msg; \
typedef struct BOOST_PP_CAT(msg,counter) : boost::mpl::assert_ \
{ \
    using boost::mpl::assert_::types; \
    static boost::mpl::failed ************ (msg::************ assert_arg()) types_ \
    { return 0; } \
} BOOST_PP_CAT(mpl_assert_arg,counter); \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        boost::mpl::assertion<(c)>::failed( BOOST_PP_CAT(mpl_assert_arg,counter)::assert_arg() ) \
        ) \
    ) \
/**/
#else
#   define BOOST_MPL_ASSERT_MSG_IMPL( counter, c, msg, types_ )  \
struct msg; \
typedef struct BOOST_PP_CAT(msg,counter) : boost::mpl::assert_ \
{ \
    static boost::mpl::failed ************ (msg::************ assert_arg()) types_ \
    { return 0; } \
} BOOST_PP_CAT(mpl_assert_arg,counter); \
BOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , BOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        boost::mpl::assertion_failed<(c)>( BOOST_PP_CAT(mpl_assert_arg,counter)::assert_arg() ) \
        ) \
    ) \
/**/
#endif

#if 0
// Work around BOOST_MPL_ASSERT_MSG_IMPL generating multiple definition linker errors on VC++8.
// #if defined(BOOST_MSVC) && BOOST_MSVC < 1500
#   include <boost/static_assert.hpp>
#   define BOOST_MPL_ASSERT_MSG( c, msg, types_ ) \
BOOST_STATIC_ASSERT_MSG( c, #msg ) \
/**/
#else
#   define BOOST_MPL_ASSERT_MSG( c, msg, types_ ) \
BOOST_MPL_ASSERT_MSG_IMPL( BOOST_MPL_AUX_PP_COUNTER(), c, msg, types_ ) \
/**/
#endif

#endif // BOOST_MPL_ASSERT_HPP_INCLUDED

/* assert.hpp
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
*/