/*=============================================================================
    Copyright (c) 2003 Joel de Guzman
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_LAZY_HPP
#define BOOST_SPIRIT_LAZY_HPP

////////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/phoenix/actor.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ////////////////////////////////////////////////////////////////////////////
    //
    // lazy_parser, holds phoenix actor which returns a spirit parser.
    //
    ////////////////////////////////////////////////////////////////////////////

    template<class ActorT>
    struct lazy_parser : parser<lazy_parser<ActorT> >
    {
        typedef lazy_parser<ActorT> self_t;
        typedef typename ::phoenix::actor_result<
            ActorT, ::phoenix::tuple<> >::plain_type actor_result_t;

        template<typename ScannerT>
        struct result
        {
            typedef typename
                parser_result<actor_result_t, ScannerT>::type
            type;
        };

        lazy_parser(ActorT const& actor_)
        : actor(actor_) {}

        template<typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        { return actor().parse(scan); }

        ActorT actor;
    };

    //////////////////////////////
    // lazy_p, returns lazy_parser
    // Usage: lazy_p(actor)
    template<class ActorT>
    lazy_parser<ActorT> lazy_p(ActorT const& actor)
    { return lazy_parser<ActorT>(actor); }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_LAZY_HPP

/* lazy.hpp
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
*/