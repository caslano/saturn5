
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
yhIaZM+kWgSvhYp2V/DqiSGmdQDKu7bGcJgWtMs4Jt6Crs5oq+11InZRhizrlL9Qsj33DHiNrMB0IvAiEzZEMGHBtRdfBMsYrp3FwvHjFQTn4PirAe/S8z+hNhhGbYHeNy0VyKIFVjUlo9mT4D+00w07voDZcjEPwjhxv4TuLE6OptMk9q5cpJtcRXAM5tEp/NHVKPKjtyaYJdsoFcCJfXxiT3FD/UooEdtEUKnqjR+UlkD06AJ858o1vh9ifQiSVZR3EnK8tXvf4BB5B2h1mPJasrpTahYNYlKNGa38IIy8yLDr3PiJ1WnZZRTOFJFeocUHQ8dMOe5/y2+kTuCgQO2UKKHvcrOM/58WJa9voGIlypciz0yM32t2n9xotvDC2At8IyRYSdKbouAkKhp2CVQaq7sKR4VS3Dr3HmOt81ArmbA+KcQQtL1F010i4A7lojEu4jgEIYnshMoZzqUhaWML3h6dwKhPKFFFgXNsapqNDdVeDAMShM5R9thsdcaQJWpXA7b0r44KCaoChNXD0XO1MQpKsIFs8IYBo4qJ+sVybihyx37es8bj3WCyNPtdnA3PtqpNkQfOyHp7R7b2kM5zZzmPDQw5fZJufRougjiYBfPIUKz1lvvFuQrnrhZHX2qd7l8fCQHvI0dY
*/