/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_NO_ACTIONS_HPP)
#define BOOST_SPIRIT_NO_ACTIONS_HPP

#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/non_terminal/rule.hpp>

namespace boost {
namespace spirit {
BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

//-----------------------------------------------------------------------------
// no_actions_action_policy

template<typename BaseT = action_policy>
struct no_actions_action_policy:
    public BaseT
{
    typedef BaseT base_t;

    no_actions_action_policy():
        BaseT()
    {}

    template<typename PolicyT>
    no_actions_action_policy(PolicyT const& other):
        BaseT(other)
    {}

    template<typename ActorT, typename AttrT, typename IteratorT>
    void
    do_action(
        ActorT const&       /*actor*/,
        AttrT&              /*val*/,
        IteratorT const&    /*first*/,
        IteratorT const&    /*last*/) const
    {}
};

//-----------------------------------------------------------------------------
// no_actions_scanner


namespace detail
{
    template <typename ActionPolicy>
    struct compute_no_actions_action_policy
    {
        typedef no_actions_action_policy<ActionPolicy> type;
    };

    template <typename ActionPolicy>
    struct compute_no_actions_action_policy<no_actions_action_policy<ActionPolicy> >
    {
        typedef no_actions_action_policy<ActionPolicy> type;
    };
}

template<typename ScannerT = scanner<> >
struct no_actions_scanner
{
    typedef scanner_policies<
        typename ScannerT::iteration_policy_t,
        typename ScannerT::match_policy_t,
        typename detail::compute_no_actions_action_policy<typename ScannerT::action_policy_t>::type
    > policies_t;

    typedef typename
        rebind_scanner_policies<ScannerT, policies_t>::type type;
};

#if BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 1

template<typename ScannerT = scanner<> >
struct no_actions_scanner_list
{
    typedef
        scanner_list<
            ScannerT,
            typename no_actions_scanner<ScannerT>::type
        >
            type;
};

#endif // BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 1

//-----------------------------------------------------------------------------
// no_actions_parser

struct no_actions_parser_gen;

template<typename ParserT>
struct no_actions_parser:
    public unary<ParserT, parser<no_actions_parser<ParserT> > >
{
    typedef no_actions_parser<ParserT>      self_t;
    typedef unary_parser_category           parser_category_t;
    typedef no_actions_parser_gen           parser_generator_t;
    typedef unary<ParserT, parser<self_t> > base_t;

    template<typename ScannerT>
    struct result
    {
        typedef typename parser_result<ParserT, ScannerT>::type type;
    };

    no_actions_parser(ParserT const& p)
    :   base_t(p)
    {}

    template<typename ScannerT>
    typename result<ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename no_actions_scanner<ScannerT>::policies_t policies_t;

        return this->subject().parse(scan.change_policies(policies_t(scan)));
    }
};

//-----------------------------------------------------------------------------
// no_actions_parser_gen

struct no_actions_parser_gen
{
    template<typename ParserT>
    struct result
    {
        typedef no_actions_parser<ParserT> type;
    };

    template<typename ParserT>
    static no_actions_parser<ParserT>
    generate(parser<ParserT> const& subject)
    {
        return no_actions_parser<ParserT>(subject.derived());
    }

    template<typename ParserT>
    no_actions_parser<ParserT>
    operator[](parser<ParserT> const& subject) const
    {
        return no_actions_parser<ParserT>(subject.derived());
    }
};

//-----------------------------------------------------------------------------
// no_actions_d

const no_actions_parser_gen no_actions_d = no_actions_parser_gen();

//-----------------------------------------------------------------------------
BOOST_SPIRIT_CLASSIC_NAMESPACE_END
} // namespace spirit
} // namespace boost

#endif // !defined(BOOST_SPIRIT_NO_ACTIONS_HPP)

/* no_actions.hpp
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
*/