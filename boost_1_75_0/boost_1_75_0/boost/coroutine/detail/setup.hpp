
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SETUP_H
#define BOOST_COROUTINES_DETAIL_SETUP_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Fn >
struct setup
{
    struct dummy {};

    Fn                      fn;
    coroutine_context   *   caller;
    coroutine_context   *   callee;
    attributes              attr;

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    setup( Fn fn_,
           coroutine_context * caller_,
           coroutine_context * callee_,
           attributes const& attr_) :
        fn( boost::forward< Fn >( fn_) ),
        caller( caller_),
        callee( callee_),
        attr( attr_)
    {}
#endif
    setup( BOOST_RV_REF( Fn) fn_,
           coroutine_context * caller_,
           coroutine_context * callee_,
           attributes const& attr_,
           typename disable_if<
               is_same< typename decay< Fn >::type, setup >,
               dummy*
           >::type = 0) :
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn( fn_),
#else
        fn( boost::forward< Fn >( fn_) ),
#endif
        caller( caller_),
        callee( callee_),
        attr( attr_)
    {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SETUP_H

/* setup.hpp
oFeisGFUqzYWlyNdL4zN3MxcJabHqCF/TYz1/BDTIpVYrNAbYM3qseaQ89Cnf3ws+aS1RMlYYtcGAi64J058BDDKiF9Ovyr+hp2Htd4Vt4VNXy8ZrfTu8gLtFvo2mvi44U26w/YTdzo0onv33BGe81XfZYppQt51A5Sw01L35bmrR2nnXGz1wrtMxLvYauix3OBJ39+97Z5GVHiKEAsCPAg/z2FYzKO+h/EUUj7zvaroYngUqr5ebeR+tjiemAllonqG/uUQe4IpStRJsE66uvg0NhlTX/QF6+lOb2hhqO9STHLnrAIXQSEBD6q5zjpmjBVS+0NwBWXZmoA7nP3lzb4P2TVd8DuDvUb6RuzIM/T0RxexgFyDUY1SjWH/tu39ahhcOqEbRHaAYo9kj2aPso7aSfYiNZUfV94tY66idaK1Uiyi2qKfqZndX+C+giPr/3zwt+t56nHbQJLiI71UqfaKcev+9oT9UW/aDXVXdENt47THd4Oqx6wHydP1zEvmmmO71VfQ8oohRIODzvaoDjx4MeRElxRW3L9lQidgnr7dnB7mDriw+oBPw+tRApGPokgR8Vg4PuMOPZ0qM4mJWl5rtksv1WiOF7bPaqALsS9lMTt3s1msHb2VnYw6nt/BFEn5fWC2Hd6K34LRURU/+4YzYLDqjMqtwWSGM+QkiEfgRybHUs1KIV5vMwEH41EeEw412p8yfAodCx3l
*/