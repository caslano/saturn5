
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
hDNRxnRd5zmQINjIe66Gp+LaZFSaduTkBAVQdMxrsK9HdP6NtTKcRHwjhnbq0Y5uWXx7z2Zf5bGWRQd1hZ5cPXqbi+qHQ8CqHXoSxBaheGTYp54AXczY/ACG/U4qgIA6i+HWrUyOrHQWpLGtp6b96aZ0cZEPwDLR3FGgDwFTIlgirHcAcMxzEzSOvczcLPWLq0Z0RGqxK/UcXyEvSFrNp+9z6kk6jsSOQsyS/eewAm2+iTM1CjPfiCypX1epzQRahMyaNXue5VZoDCx3FsLXFpSbVOY79vEzewz4XEafZWuS/u43SzwUo3QKQGbKMbWp76jgHPIS2RBfnJ++8an4g2nYkPwKNmiLY5ezLCmPV1o1h5FTUUhiDdHjAnNXgQw0+i3FigYC3pjUOp1FtndIOzjokjwI7aLEMqMjMwdiYu0P6O0aSvl0DTn0Lwmn93ewcaDDJD0vwsvMfH4iVk57wdcQCKB1aiPjeBPKrrgPe/VjFnzuCe4Jg+sY8zHY4tcLUj/eymiZtSfDYcTqFCwSctcLFF2TNI8Goi8MLvonGwOKEax8VGPD+zWEjQ==
*/