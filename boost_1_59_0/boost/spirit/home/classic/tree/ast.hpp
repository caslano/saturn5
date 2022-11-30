/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2007 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_TREE_AST_HPP
#define BOOST_SPIRIT_TREE_AST_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/tree/common.hpp>
#include <boost/spirit/home/classic/core/scanner/scanner.hpp>

#include <boost/spirit/home/classic/tree/ast_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

//////////////////////////////////
//  ast_match_policy is simply an id so the correct specialization of
//  tree_policy can be found.
template <
    typename IteratorT,
    typename NodeFactoryT,
    typename T
>
struct ast_match_policy :
    public common_tree_match_policy<
        ast_match_policy<IteratorT, NodeFactoryT, T>,
        IteratorT,
        NodeFactoryT,
        ast_tree_policy<
            ast_match_policy<IteratorT, NodeFactoryT, T>,
            NodeFactoryT,
            T
        >,
        T
    >
{
    typedef
        common_tree_match_policy<
            ast_match_policy<IteratorT, NodeFactoryT, T>,
            IteratorT,
            NodeFactoryT,
            ast_tree_policy<
                ast_match_policy<IteratorT, NodeFactoryT, T>,
                NodeFactoryT,
                T
            >,
            T
        >
    common_tree_match_policy_;
    
    ast_match_policy()
    {
    }

    template <typename PolicyT>
    ast_match_policy(PolicyT const & policies)
        : common_tree_match_policy_(policies)
    {
    }
};

//////////////////////////////////
template <typename MatchPolicyT, typename NodeFactoryT, typename T>
struct ast_tree_policy :
    public common_tree_tree_policy<MatchPolicyT, NodeFactoryT>
{
    typedef typename MatchPolicyT::match_t match_t;
    typedef typename MatchPolicyT::iterator_t iterator_t;

    template<typename MatchAT, typename MatchBT>
    static void concat(MatchAT& a, MatchBT const& b)
    {
        BOOST_SPIRIT_ASSERT(a && b);

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
        BOOST_SPIRIT_DEBUG_OUT << "\n>>>AST concat. a = " << a <<
            "\n\tb = " << b << "<<<\n";
#endif
        typedef typename tree_match<iterator_t, NodeFactoryT, T>::container_t
            container_t;

        // test for size() is necessary, because no_tree_gen_node leaves a.trees
        // and/or b.trees empty
        if (0 != b.trees.size() && b.trees.begin()->value.is_root())
        {
            BOOST_SPIRIT_ASSERT(b.trees.size() == 1);

            container_t tmp;
            std::swap(a.trees, tmp); // save a into tmp
            std::swap(b.trees, a.trees); // make b.trees[0] be new root (a.trees[0])
            container_t* pnon_root_trees = &a.trees;
            while (pnon_root_trees->size() > 0 &&
                    pnon_root_trees->begin()->value.is_root())
            {
                pnon_root_trees = & pnon_root_trees->begin()->children;
            }
            pnon_root_trees->insert(pnon_root_trees->begin(),
                    tmp.begin(), tmp.end());
        }
        else if (0 != a.trees.size() && a.trees.begin()->value.is_root())
        {
            BOOST_SPIRIT_ASSERT(a.trees.size() == 1);

#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
            a.trees.begin()->children.reserve(a.trees.begin()->children.size() + b.trees.size());
#endif
            std::copy(b.trees.begin(),
                 b.trees.end(),
                 std::back_insert_iterator<container_t>(
                     a.trees.begin()->children));
        }
        else
        {
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
            a.trees.reserve(a.trees.size() + b.trees.size());
#endif
            std::copy(b.trees.begin(),
                 b.trees.end(),
                 std::back_insert_iterator<container_t>(a.trees));
        }

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
        BOOST_SPIRIT_DEBUG_OUT << ">>>after AST concat. a = " << a << "<<<\n\n";
#endif

        return;
    }

    template <typename MatchT, typename Iterator1T, typename Iterator2T>
    static void group_match(MatchT& m, parser_id const& id,
            Iterator1T const& first, Iterator2T const& last)
    {
        if (!m)
            return;

        typedef typename tree_match<iterator_t, NodeFactoryT, T>::container_t
            container_t;
        typedef typename container_t::iterator cont_iterator_t;
        typedef typename NodeFactoryT::template factory<iterator_t> factory_t;

        if (m.trees.size() == 1
#ifdef BOOST_SPIRIT_NO_TREE_NODE_COLLAPSING
            && !(id.to_long() && m.trees.begin()->value.id().to_long())
#endif
            )
        {
            // set rule_id's.  There may have been multiple nodes created.
            // Because of root_node[] they may be left-most children of the top
            // node.
            container_t* punset_id = &m.trees;
            while (punset_id->size() > 0 &&
                    punset_id->begin()->value.id() == 0)
            {
                punset_id->begin()->value.id(id);
                punset_id = &punset_id->begin()->children;
            }

            m.trees.begin()->value.is_root(false);
        }
        else
        {
            match_t newmatch(m.length(),
                m.trees.empty() ? 
                    factory_t::empty_node() : 
                    factory_t::create_node(first, last, false));

            std::swap(newmatch.trees.begin()->children, m.trees);
            // set this node and all it's unset children's rule_id
            newmatch.trees.begin()->value.id(id);
            for (cont_iterator_t i = newmatch.trees.begin();
                 i != newmatch.trees.end();
                 ++i)
            {
                if (i->value.id() == 0)
                    i->value.id(id);
            }
            m = newmatch;
        }
    }

    template <typename FunctorT, typename MatchT>
    static void apply_op_to_match(FunctorT const& op, MatchT& m)
    {
        op(m);
    }
};

namespace impl {

    template <typename IteratorT, typename NodeFactoryT, typename T>
    struct tree_policy_selector<ast_match_policy<IteratorT, NodeFactoryT, T> >
    {
        typedef ast_tree_policy<
            ast_match_policy<IteratorT, NodeFactoryT, T>, 
            NodeFactoryT, 
            T
        > type;
    };

} // namespace impl


//////////////////////////////////
struct gen_ast_node_parser_gen;

template <typename T>
struct gen_ast_node_parser
:   public unary<T, parser<gen_ast_node_parser<T> > >
{
    typedef gen_ast_node_parser<T> self_t;
    typedef gen_ast_node_parser_gen parser_generator_t;
    typedef unary_parser_category parser_category_t;

    gen_ast_node_parser(T const& a)
    : unary<T, parser<gen_ast_node_parser<T> > >(a) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename ScannerT::iteration_policy_t iteration_policy_t;
        typedef typename ScannerT::match_policy_t::iterator_t iterator_t;
        typedef typename ScannerT::match_policy_t::factory_t factory_t;
        typedef ast_match_policy<iterator_t, factory_t> match_policy_t;
        typedef typename ScannerT::action_policy_t action_policy_t;
        typedef scanner_policies<
            iteration_policy_t,
            match_policy_t,
            action_policy_t
        > policies_t;

        return this->subject().parse(scan.change_policies(policies_t(scan)));
    }
};

//////////////////////////////////
struct gen_ast_node_parser_gen
{
    template <typename T>
    struct result {

        typedef gen_ast_node_parser<T> type;
    };

    template <typename T>
    static gen_ast_node_parser<T>
    generate(parser<T> const& s)
    {
        return gen_ast_node_parser<T>(s.derived());
    }

    template <typename T>
    gen_ast_node_parser<T>
    operator[](parser<T> const& s) const
    {
        return gen_ast_node_parser<T>(s.derived());
    }
};

//////////////////////////////////
const gen_ast_node_parser_gen gen_ast_node_d = gen_ast_node_parser_gen();


//////////////////////////////////
struct root_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        BOOST_SPIRIT_ASSERT(m.trees.size() > 0);
        m.trees.begin()->value.is_root(true);
    }
};

const node_parser_gen<root_node_op> root_node_d =
    node_parser_gen<root_node_op>();

///////////////////////////////////////////////////////////////////////////////
//
//  Parse functions for ASTs
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename AstFactoryT, typename IteratorT, typename ParserT, 
    typename SkipT
>
inline tree_parse_info<IteratorT, AstFactoryT>
ast_parse(
    IteratorT const&        first_,
    IteratorT const&        last_,
    parser<ParserT> const&  parser,
    SkipT const&            skip_,
    AstFactoryT const &   /*dummy_*/ = AstFactoryT())
{
    typedef skip_parser_iteration_policy<SkipT> it_policy_t;
    typedef ast_match_policy<IteratorT, AstFactoryT> ast_match_policy_t;
    typedef
        scanner_policies<it_policy_t, ast_match_policy_t>
        scan_policies_t;
    typedef scanner<IteratorT, scan_policies_t> scanner_t;

    it_policy_t iter_policy(skip_);
    scan_policies_t policies(iter_policy);
    IteratorT first = first_;
    scanner_t scan(first, last_, policies);
    tree_match<IteratorT, AstFactoryT> hit = parser.derived().parse(scan);
    return tree_parse_info<IteratorT, AstFactoryT>(
        first, hit, hit && (first == last_), hit.length(), hit.trees);
}

//////////////////////////////////
template <typename IteratorT, typename ParserT, typename SkipT>
inline tree_parse_info<IteratorT>
ast_parse(
    IteratorT const&        first_,
    IteratorT const&        last_,
    parser<ParserT> const&  parser,
    SkipT const&            skip_)
{
    typedef node_val_data_factory<nil_t> default_factory_t;
    return ast_parse(first_, last_, parser, skip_, default_factory_t());
}
  
//////////////////////////////////
template <typename IteratorT, typename ParserT>
inline tree_parse_info<IteratorT>
ast_parse(
    IteratorT const&        first_,
    IteratorT const&        last,
    parser<ParserT> const&  parser)
{
    typedef ast_match_policy<IteratorT> ast_match_policy_t;
    IteratorT first = first_;
    scanner<
        IteratorT,
        scanner_policies<iteration_policy, ast_match_policy_t>
    > scan(first, last);
    tree_match<IteratorT> hit = parser.derived().parse(scan);
    return tree_parse_info<IteratorT>(
        first, hit, hit && (first == last), hit.length(), hit.trees);
}

//////////////////////////////////
template <typename CharT, typename ParserT, typename SkipT>
inline tree_parse_info<CharT const*>
ast_parse(
    CharT const*            str,
    parser<ParserT> const&  parser,
    SkipT const&            skip)
{
    CharT const* last = str;
    while (*last)
        last++;
    return ast_parse(str, last, parser, skip);
}

//////////////////////////////////
template <typename CharT, typename ParserT>
inline tree_parse_info<CharT const*>
ast_parse(
    CharT const*            str,
    parser<ParserT> const&  parser)
{
    CharT const* last = str;
    while (*last)
    {
        last++;
    }
    return ast_parse(str, last, parser);
}

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* ast.hpp
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
*/