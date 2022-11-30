/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2007 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_SPIRIT_CLASSIC_TREE_PARSE_TREE_UTILS_HPP
#define BOOST_SPIRIT_CLASSIC_TREE_PARSE_TREE_UTILS_HPP

#include <utility>                          // for std::pair

#include <boost/spirit/home/classic/tree/parse_tree.hpp> // needed for parse tree generation

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace spirit {
BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  The function 'get_first_leaf' returnes a reference to the first leaf node
//  of the given parsetree.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
tree_node<T> const &
get_first_leaf (tree_node<T> const &node);

///////////////////////////////////////////////////////////////////////////////
//
//  The function 'find_node' finds a specified node through recursive search.
//  If the return value is true, the variable to which points the parameter
//  'found_node' will contain the address of the node with the given rule_id.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
bool
find_node (tree_node<T> const &node, parser_id node_to_search,
    tree_node<T> const **found_node);

///////////////////////////////////////////////////////////////////////////////
//
//  The function 'get_node_range' return a pair of iterators pointing at the
//  range, which contains the elements of a specified node. It's very useful
//  for locating all information related with a specified node.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
bool
get_node_range (tree_node<T> const &node, parser_id node_to_search,
    std::pair<typename tree_node<T>::const_tree_iterator,
        typename tree_node<T>::const_tree_iterator> &nodes);

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END
}   // namespace spirit
}   // namespace boost

#include <boost/spirit/home/classic/tree/impl/parse_tree_utils.ipp>

#endif

/* parse_tree_utils.hpp
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
*/