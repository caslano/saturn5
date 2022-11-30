/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CLOSURE_FWD_HPP)
#define BOOST_SPIRIT_CLOSURE_FWD_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/phoenix/tuples.hpp>

#if !defined(BOOST_SPIRIT_CLOSURE_LIMIT)
#   define BOOST_SPIRIT_CLOSURE_LIMIT PHOENIX_LIMIT
#endif

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    template<typename ClosureT>
    class closure_context;

    template <typename ClosureT>
    class init_closure_context;

    template <typename ParserT, typename ActorTupleT>
    struct init_closure_parser;

    template <
            typename DerivedT
        ,   typename T0 = ::phoenix::nil_t
        ,   typename T1 = ::phoenix::nil_t
        ,   typename T2 = ::phoenix::nil_t

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 3
        ,   typename T3 = ::phoenix::nil_t
        ,   typename T4 = ::phoenix::nil_t
        ,   typename T5 = ::phoenix::nil_t

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 6
        ,   typename T6 = ::phoenix::nil_t
        ,   typename T7 = ::phoenix::nil_t
        ,   typename T8 = ::phoenix::nil_t

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 9
        ,   typename T9 = ::phoenix::nil_t
        ,   typename T10 = ::phoenix::nil_t
        ,   typename T11 = ::phoenix::nil_t

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 12
        ,   typename T12 = ::phoenix::nil_t
        ,   typename T13 = ::phoenix::nil_t
        ,   typename T14 = ::phoenix::nil_t

    #endif
    #endif
    #endif
    #endif
    >
    struct closure;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* closure_fwd.hpp
+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
*/