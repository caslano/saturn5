
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
    || (BOOST_MPL_CFG_GCC != 0) \
    || BOOST_WORKAROUND(__IBMCPP__, <= 600)
#   define BOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES
#endif

#if BOOST_WORKAROUND(__MWERKS__, < 0x3202) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER
#endif

// agurt, 10/nov/06: use enums for Borland (which cannot cope with static constants) 
// and GCC (which issues "unused variable" warnings when static constants are used 
// at a function scope)
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
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
v0A9sqWLIgWwwe/r0No9DMfX3NSLSaUtdWur194f+2lV+XLyPrPBMB1SpuNnyEDskkFto5YhuSO3Gf/ib6uziT/mY1lrS6DUfqv3gco7+23LhwfdmiVeWA5nTj/0b7Dv3q0mMX4Gsz8hh1BftSEquPv6X2gSRffHTHVRUuWx2Czmw+dQ3AXbBdM11+7t5BBmtGMh4/78JMLwvEHkV6btdUaMhl/cGIlU9ltixLPzrb7dzBVi2adTGaJBQ38pMbXaSw0Dfl1Hn8ieDDdj61t8jiHbcS4bdS2egOQVNHB1c0ZtQzjSJa4/CAi9SzRCBgAL9Hr/5UPzR9w8AKyfd6QA/JbSSKLBD/s4TYePh937HvTpp13jpQfFmeGgd6ONzR+5wVe0tQCsJpXz4HcrM8tnRq5fCQe1m/cWCb5LrEupfZVfNd1iLhSrgtu1GRgYuKgJwUThu+sixird7cnOQbyhIJ0A3qwvew/rIm5BNgJ492CHwZDNODxrNSe7dDqFUK+2mHfVfS07IiIidpuhJCcXHuiz3ioJUBmU0nh5lGpOerPbsCaw5n6FOlz68f1S3dXbtDlWdy6N8besujpJ4yIyY7h9Tu8mE1XQWnHE3cSs9qDED1XWQMcN9WQxN3L8XNjTSGOGT4O9G26LeidwNmnFkW33Y8f97ph7N1W+gFkbmEHqQ+UUk7KYVncZT+95SXffC8FUuc/AGhBcY3AF9Rq5Z7/NZ8CD8CDuIIEB3refZknPzOMUGoscukQ7sQGaapbS3Z8+nmMrXfjQkd/J+4Vw4VfYkveO84C0LBo6rHARnCAlbfblcRlAMzOBylGkFXrCFg4AF645LHCqapQYLHAmgZ44iBt6Y+5LJeX5ClrqcqjdK86MB43dVVEI5FIHF/ZJZ9ZHJIHmU+wMlKWRTGAX0JMbLHBeE0nJf5dYTOqqZrbMBepw4fb2+T3nu5KDrMsoV1ygoUG9xu1twIY2hCuRzYvqpk9NjBztSe6Ga3o4fKweXzCZY7qLJ73fZzEoMs7kTq0cmTGETSv/Par7idPbz24urBeADlq6FlJjqrds7DQPhH/sGTIsPgx6o34+y7PpG7g0uwRdiyqGBzv1izxfyxtlNR+e8mdsbBZzYEZithFn370zqotKT7PT6w2RnCOW2xO/+qDgNcUVbMsvPwtymXfN7zjKr5FEFW7evfxPhv1gu75VmFDLtcXd8nCW5Owdpxn34xWOowb6PmrIHSrcpmWySo71HvD+HFzU+VsLv2xOluSyLUMSs8MO3lRfimtSiit0Ba3vAHMuOXjhrYN8ZbFuoNrEceKf6hSQtC5HrHYQ1/vJ8EAngHTJo1/dwEWR3BDDFNDj2xCXJTJgNsMu4AsVOGYIkEbCOPL5L/7WJGuFg+x43E9KnjQIvhebJ1sXoWxT1XsIahiHZsx6SaJZNLbfeFEYgU2Mo2wy2hk5bacwVFZSbKRzqywKjnm/wMnJWVeBYu67+SO+5uaaIT4Qy+hsGTj6oHRmQvsXOvHo9A/m1PurdXUPb/v/+J7UVyk5We/khSM1PfoxzBbc3o+9w9LrRc0GHOJhZDixHP3lJ/NLMdQNsbenWY6tP3jAZQVr+DEEv2Knd7GfUM+EVSAiK+CMwN8+FUEH2+mHzd7w0LmgVn19zCg348SCnQmdpZx9b/npo7uZIyrqKeWknJ7aRYZ20flm4V29U2dkrnh6ge98Oe0Dr0nvToH+RNfWau75RucT3ywq/1jyllHWkQ1nwU7jnnisnQiv5/vujJ8HdHOQMeEdJpARgrQDjVcIXKhWF5kE2lIHK/ktAEx1OZ6VdU+G94w2CqZBzYK4rTcbsh68lFZFV81isn5XlswDtsEuKln/lKUxkwkbQrIQst2hIv6EjV+ts4jNI8cighWJQXTb6dnXzcD8h6JiYgE7R6wbgvfoeirHSTmhbriVl1j0XLD4Fkt/ApRDZYloUbBVLv+yCTsMnrT3o2m1m7C29QR71F7L5ZUG5j6/MOOeYhStLUI9e395l3i75cmPPQ0RNe69/rohjl2GJw6+tj2FQswelBr7/r24RunvaaAT4scQ7PMVOJWPfoMBvaiytthy0tbG2mLSSlmFPX33u65OFbX2GYK0V3Htk9O8fy/r1hBqL+hOjNGLhovnRsqGgv75Xfkpdsd39X12sP7Sgz3nxH17yCTh0359fW3fgc33neqs6YR3KbZZ2b4WSfkdgmV6bd7qLKnHYUIxXCbPhwNCHRiU+FOgvYhb85hXYs3AGj2Hbf4UaYe5Q2JEc1XZ9zYCJxTztWQJs4Ayi96vRkhvjJYaeRaDFnF/BjkaFYxUHIQL5XndPpTSpG5ikzi4JI+8q3f7u6mqnRf+OlGLh9DZKA7OTwPYrRg7crREelH++4CJBtppxxtmZs1xLlOPWNcH7pCyc3JMj9oZnAZPdBlf98bIqxx3lyaviG3rrg/Woc2dRpA9nrrd6iWllymI4N2NC8NWuNrNjFYtWr8pQqunqjkxSrPCPuNzzizzWVqd8e3Aa4MH9lIKFejrgO4X8q35QZJeFUNppIShx/337lNNPf+xuvZ2XBCv0FZBfcJGaLa17Qpl8RPFQo359Ub6Z5p5LPYnM2ktvEefco+UVkArkNYeHPC+B2NGv/tzV+1vf+2ZNdJYcjlOqT6o3tr92YGdu/CLlu9hjdmvUg+883w/IRSv3JsfqUGfNXUNtkvKN1yFiOVRN6VPu/pRyw4Cb2dMY445cU4D5wFqKmYVuiPrEuQM4IFUfga3mNiDkEx+gsixMlBHkTS5i1f0mXhJ3WttVbCmG6gZeC0WEw6aPwu5Tm0Gmr+A9BKbDrkCKk80y67wK/maJPWCAAkD3XJ/1A30bAbebt7w+Aw9Kt0X7WuB+CuNSRk+yP+d/a299j/Q6O0vGm4JubhIY4JuhtgZnD9/vkJj8wgHeLcuIjiWFENjlxkTcVy4l5vH1lveSbVplURcejH2nFjlOUPwx+V++9Z30D25DG0IHl366JUpO3kIZIo85ZbjbPIb5lp+qQmcrOL0lyrmPZY0ei126IILIpA5Z/u+nP30K7OjuMaFrfOZavTCX3tv7/tog83Y+DDxNoPe8Gx9ZSeX+Zvy3pBhHnD6QwVbwQ0xSLfiX/qgtLOpuYL+PBAyMBF7/f0VGEv2GVr+zskKnI7igXiF3piwT7SBjOEZPAScS4NfXzlpZei6DVlsGPAIaCvuhkr4cE1NCzw2rdKslTdAFRqGyOggb8VBT/N81hG6qePR2c6fNvFsmPfDyrFGmkNlHWBH0KlmAFyYhuG7D198UooZlSNfNnTZ4fGfwWhk5LIg05grLcBRqq4HgCKZOao/Dxg3N1uTsdEyCeLRWZ7FPHoLSqj0AATx/zFut1+TDrb2BOgUNAL/2GhlxkxjgJMsWSdB/8P+CKSLHuztq292yLP1MyQF34PIx82wib2HR6z8vypwJ9DZ4dj6cbC3sjCK9hJe1+pM9COFxCQqWW19RWGfODv3Cygvv61UeznHfGhhIY9i7lisKDH+SmDfjNidkxmLhX3/p3sPR/rLhIkX6w2/6xmofk0zL2aPPCj/K1HP+jFf7FqTyywbsxrDXmUwYM4q9hJr9o1juB/1OTjcxk8IrBzrQ+pF9RXcG6QW6QRrkWK10Q8sahgGjB/lNArPgxSFCmE/tAvOh2JqiMUNsLrXOv6SyohBfXtZdo+Pco1kKdXHK/xdPHn24wrpjLo2tEZF3XaZmex3ollLcoH+Q3PhiPNccfpkzgiyFDPLFdEIbOZ4YIdfl9QMxRO28UAnEvnRpFrSN01kGWDkpjdgGfRSl+OyPF66ZHgWkAgDeiCL5CFJxZqyjr/XVArpkOUQQyk7124YRx16hIxpsZHw8MDHAc47lvQ/3G1pgPYXne0Gnv94Fo6pwVMnBz8Au4EbR5KGKquf4EftdLncDyiEaSpB75RKlvYgNqiYu6d4stZveOWUqJBQySSFQj1ybPp/Jn7dlkkvH887s/CDozqPK6TIkDkgLeDkKNHc1maREoDeHpoQXDMispcHC36DO1U0mg/eMA89z4VbzxCuLPPZ+mdjZazH85mAj0KDBkrSxLtKsO/7zJIVwQXVdSfN1HNriQu+x9zQ3EF7qWOxew06Y6MrAygLBDyK5n6hnFRD9fOd2DtHYQkYMirmqelwv5dfGTcZihU051c5ejou6KlvbS3/ZOont4m1Q9CynOstzxRf99M1T/qwzZyc75xBs3gHtjxj23Th+3ZHzyiLXouOuXqB1hErfPXySajosVsAiD+4LtMSsOqR4g3y2cuCbXFMygSEiiRI9B7kMGBhtvPgGk8sRssoXzPzFouxqBfKzAjkvOS/KOyRLtlbG13q7PBmGiMdDzrCsn3Sdcc7O5AiG8Bv6ma89/U9N7jw0WG0lS4RlRZaKTzMA6rRC9zq4I2eRs3Vox5TAH/epQBgc4Td7Vk3xx+768aEjDAcaz9ml4pFSAwODgp+OBwPDzWVrKGfDxf29/5HKVOiPYX2LwBdP55X+d+c6Krw6uvrP7tx44bGdiHclzHxhr79M03OosjGM+1h5LjGZQrzwrTcsRjPRXo8Pddi1krLkIj1eK18dCgssCSx5cYafPJmoWRxILOC5v7R+eL683GnY2OmWuw2QTg6jyZRtb/rumZPyWamUSxCXF/T3M2p6xv40nL74V3vVW3E9rqmG6K7Z7MeXu83J9k4Tf79MvuklavFkboD7G91nF69xkWi9zuhii16ovGkCmHxBM49XzM5RhsdoXluhyH9ynZZe5t1lzc7quqe9BLPBr4l+/pj0GPgPLCTd1VQXtyDwD8SAlLn8cArh4N8XSE8pVqybeuhF3VfQ+LZof0Pr3siJWJAr0wwwZyXtLQyew2LZQN4CjeagP9lWSewIMRjgOsWJGkixdXU/UOlFiDg+9ec1WBAklhAwegDPTxpGuBvaSJrqt8BrB8oyhLe2oEfjhLIRtPhOaH1hPv9tN39fm87Xc4G1l+J7N+/fzceQo3T4/fkaZXj27eS7QySsooIxotO0mSq0IbuSwsiaWLt0C/J7O18p7IcRpPpJDRbStGi6KAABXXI4K4L1iBiF3q0CIUIW1ZO9JvtwwCl4IImnH58F/vt8VlX1gY9/L97YWwg8+G/6hjYuQEXz9M5aH4tdrmWa1QxkVRAp0+lDTOZtf+LXMRJR1f2Ndr2jQvrBzVD2OVs5ur7PMa+T4aUOkukVTpEjN7eX49Qu3Lv+pqK4xpJvgJeS5/YQVUNBD7sn3yFIvEYpU0BtO89MTb5OIZ+ZZR/QMzKtl6mPpvdp197S2UERvO36F6nk8ZJhnW1uLzg9RsEyrR3B+flaK5oMJ7/rIIKQFwWxuP3l39AzKMYqeeNtEvS/CyvhXcIFYmWcZ3v7QA2Nt9J4YKUQT/1O/Z6v8CbF2cWxGLqvdvTJAFgzr6Vp7XzACLiXRpGDq5an3498Ov76xxgvHmcJnLtmLU6sYhfSX2FQy4JlG3dW/RjqQtovr/3UBtsZAw5+tQTKTKNWahFnOTmHvcOZ17+Y5z/sf3GO3ELvY31M7vD7g1HnAkZ9XnqDBNOp2TKeZUs9Cb1v4BciaCwVReY2Nk6xLzV9qG6oCRMki/Mbaf3MEg37z148NZtuEhS26woxmqzXnoMLjFkSXRPiZaYk9z1svc/yE9HUbMfRl8JQDUIMxTWXrXp8tudc82DHoSU08ryKDq0Lb9/qImdbRsccXTlB7M3xIW77tn99NFkisr48gBqlwQbpB58o1Ft6lJpf/O7IKXrzPa9xJN/sbXV9Zof6dKkNSsKvdqNsTR9VLHH8vzdZV2j0rc12VnTHh8G2t71ZD8Oytf8rXYrrStGqILr44+h2Am97borKyEqm3bPoGLg2YWv+ysXborKYXiVN9skYuT+q5R0QKiHoorDMPg5JL9CU3ZgHmMzD5jlJF6zfxytLvHIE/mlG3hZnmwtBQBLX9TCp8ZiphTz/SBW0huvU3j106M1Ze8E8DyZUVe3GOTuNeczbRTdEn0u/xtzGKzXRUMUVk7//laDaQHmwL9KDrZ0AfkV4L2fDqPcAzLmewLU7L9MHSIKbiZGgK691vhUzEBNbwUcemESmo6d7vtqfAi43vFgEZUsd1R4otDyj/8SyMzLBaaUt+DNwzJd2GItvkiXEhf/LbOjUjfU2OSvMvGTPm1hHzKnGe+b99PXBV2oQ2rddlGyW528V7ctsM88aCls7G6ZyAeUulzhL71IEy5tMsSR5p+96CC8kNrb17tGV//JLP8TVc7mNWbw31pDl4XX0tzLK0g/dvLyqy9OLhhVsF4NsW5ZrEFLy+F+1isv/1azO6W/MsUKmS13C97Ghzd3HIRmv8T2HagxHgvoovXTztzx/H3ywTXpqAN/xImePfU90lTQvc7a7cbtommzB/mahTtov6p8fXv0o1zNhycprC0WWtjarinQ/i0DoYmcZL/higPjh/fcUoDKXkR8D38+KpQa/XAOM/loIDxaL3TZNqv5sEQOngD69QcnBCCq/3ni8bptHv9lsYuaSMqxdvvvftDlYAw/WGl6DF/XNmrc3gPGgMgqghD86hlNB+bJz9Be6RKvd1tCAHDdehPQOwk0UIeZxkgkg1pvQqKdIUdhWb4QyEdpVdkRotZIbF0E7JOOtLLejw768pnd/ljSm0OSYQM9jh0BZ768c+jWfj39y/q7cGo2aGJmjJJCd++pG31DvQOqsoscG1wFw4M9WlLU3VADxZvp2n53Q1Zf1rE96Kpw7MFmXTSv23Iv69/H9y3NxNv3urH7zFwaNLTSnX95x17v5jN2Cu/PfFJsINOKYe5cLrdGGMhosKGQnq2uD5aF5DLddFwOM+H9BmwFYvQ7sycYrWHMiC2lwYfHCKhq+X9ulTnag8xGwI9he1e0U7SCsYUW2n8DP9zWFzxBukGZadZqZvlL5txPONFq6ZnxuFATDSAsDxMS3om2zeruO3wbYL8T8lTQtpEmCh//MHcteuYu27SDgZ4kXo8B9kjQn3A76CbSmTEXlD+fqDpt5hqVLrH4aI5LWaxAVQtjiWS9846cWq8I5bgvtdEDzIJAzA5EDYgRZ+XJyaCzy1MAC8RxDXv9bmBBEtcDBe5221ZGVCOwOGgKY+WKfdLp1vnQn3pxHnOGG3zrCcRBJetUGhTfcNOf99SVytxq/dVfuQGhQNbjzrIuIMFhOG4a87HOESCtqtmcDiqRC5pbVJ6e7FQq/i9lMsCbU1Hwt3JGHy5WpQF808hK2/OnDlO+z0EoGDay/H9+Lr2OjdhcuUKh6RPhat8DK00RchSoia1myP62Md2ACPe+MVxsX9mTscL2vn0L/m9yiOUxSIlizZ8JgX1LYb8Ddl/loDPOfbijzr7vCDsF/eKjspyu9+LKltuLjsrIcjYb0MA3RuE8/t+nH6vpAfcS5363MRcyhmrc0msf5M0gs7PPfLb6Muz1uKTrppr67SNcH/WvSptduccp7H1CjOt2Grg59EbovbvJT7iT7/Hoi/4sXE27XHm5csh2csyPwtQhMPRwcERv0WefiIqMSHBp3WQinRFAY61Tvt2yH5sTGaqMpEnRUXVUeZzbV+a/FFrb7wEUcbiANvE7m9lEcl7Wc2Mf/86MSiChVV3ZDsZrsUGQt+Yk0RpCCqLFgKpo+vF3kOHcM3j+5TX+wWS15j1kRleyWSS79my/6YEeGgtleRNb0esrcegBsV8zd+AzH7UXKZ7+R0VP1si699pk8XthDr8UvQAZFy3yu4R0zD4fP5p52VFzCyDzA1i1sXBsVKUq9yjGMrThdd5ryzCTlHxeM7T+IGcS6EPllLDmtwDOk2BR4imwpT9neQogiPN3jHSo+TlNpD+XIBozYXgrBCj30P/nBo+01YsWYILkbWmh/dxSR+QOFydY09oDL47+J3GIXqLYmLl+0Fm5j25yLnYALcw818D6oxag90XIhhzEAY2U9/ATk1Z95GJ0XiPfE+DMexwcYbrM/xn+3F3dPO5XxLFjRR7u6/ozmN8XOMfaj9yV7s04NcDafEhksk+usPZfYuXnbnUaez14mhIMS/xw9Px0fhGTXraOZtBexPj1sLqzxOko6AAaPvxB1Zh2IEFmvNysKip5nq1bmJnBHoD5Y/XX8jLYAnM7lG69532syVzm8RRa1PgQ68lXppRSBSKkLGAhL+BCzjDc2ZgB/kWTqlFhhoiPFXfXldHaYp7bFu1RgoAXNgnm86zv6aCs3d0rRRR78lhDVNVMvy1M3X6xHr58oJSvpSbl2sONbynz3uia836jh42PwsFkGyjvEGzJx+HL0IM4mW8zuD+Cb+9e0ycKy7dfjkCjBwapRumZqh2Sbz+Cbn6ARv26Z6HwhyBhIpCoQ+YQW5qFJqRk6NuopiHiiWoiT1wAAiz90yow9Ip9/dc62wv97c4KTnzJoCSuNDLHL2TADwdgylWF27/nxAY0AbEVRrIWK4KW3ngtt2IHmxXpuH/HwPnPH22BC8WlkSxAGWxDlPB5PVEaWS+/hVWAOGDJYXoTOXd3AC1AyicjfJ5E4UdpJLVQ8TAdjow3Ayf9F2T3QAMTsp7457OY5HJvj1wZ/xuQpOmz+xxvQYV+gu8DWColT4LhCpdhXKTKT2euWxkMF6mfL0C4SCMlOcrZuRVKx1VUijuxyaeexIDGyiLGEOsV62znn+sUhRWWcl/MhauB98M3rd4boJh5ga/feHaADXVx9lsT3QTxuc8r8ESV2cpelHviB1UR0tOyOwzQJlP8HT3jq8jq8Ymftf+osXdRCLQ5Y2a2Hvtrgt5xy562/1OU4vJXGl1DZd9aIz1yxSWTVBgHQ2MqPgj78Y/edkuiz9io78xXFBIRbkIJzHCmK+fGoFAtDFh2BqHGNAURX5FWwZoIrkqoACg7g/Vf9JzI7xZsLbNMS3Oo6opCqfDgnI9nIA9QB2pdXM0CYbyuSXJOF6AJ325jwmY/xsWrcv4SscPY9A07mrRzFJmlXU4LyLy3hdzzlFgXybcDDoP7vv52drEm2KjaXMBs89QVe2M0V6FmSnhpcrMk51tQZzTonrvsHU9MIW95E/BnAGfPaKewy3vQY2xZmtS95LA7YaAjgljZNfglLdlQ2rWzEMsiT2T0LEbWyPGl6oMewV8IvP1qfq7u4MpJcCFNdAcjtg4=
*/