/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_TREE_COMMON_FWD_HPP)
#define BOOST_SPIRIT_TREE_COMMON_FWD_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/nil.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    template <typename T>
    struct tree_node;

    template <typename IteratorT = char const*, typename ValueT = nil_t>
    struct node_iter_data;

    template <typename ValueT = nil_t>
    class node_iter_data_factory;

    template <typename ValueT = nil_t>
    class node_val_data_factory;

    template <typename ValueT = nil_t>
    class node_all_val_data_factory;

    template <
        typename IteratorT,
        typename NodeFactoryT = node_val_data_factory<nil_t>,
        typename T = nil_t
    >
    class tree_match;

    struct tree_policy;

    template <
        typename MatchPolicyT,
        typename IteratorT,
        typename NodeFactoryT,
        typename TreePolicyT, 
        typename T = nil_t
    >
    struct common_tree_match_policy;

    template <typename MatchPolicyT, typename NodeFactoryT>
    struct common_tree_tree_policy;

    template <typename T>
    struct no_tree_gen_node_parser;

    template <typename T>
    struct leaf_node_parser;

    template <typename T, typename NodeParserT>
    struct node_parser;

    struct discard_node_op;
    struct reduced_node_op;
    struct infix_node_op;
    struct discard_first_node_op;
    struct discard_last_node_op;
    struct inner_node_op;

    template <typename T, typename ActionParserT>
    struct action_directive_parser;

    struct access_match_action
    {
        template <typename ParserT, typename ActionT>
        struct action;
    };

    struct access_node_action
    {
        template <typename ParserT, typename ActionT>
        struct action;
    };

    template <
        typename IteratorT = char const *,
        typename NodeFactoryT = node_val_data_factory<nil_t>,
        typename T = nil_t
    >
    struct tree_parse_info;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* common_fwd.hpp
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
*/