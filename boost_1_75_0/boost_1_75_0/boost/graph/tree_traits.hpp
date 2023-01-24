//  (C) Copyright Jeremy Siek 1999.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_STRUCTURE_HPP
#define BOOST_TREE_STRUCTURE_HPP

#include <boost/tuple/tuple.hpp> //For boost::tie()

namespace boost
{

template < class T > struct tree_traits
{
    typedef typename T::node_descriptor node_descriptor;
    typedef typename T::children_iterator children_iterator;
};

template < class Tree, class TreeVisitor >
void traverse_tree(typename tree_traits< Tree >::node_descriptor v, Tree& t,
    TreeVisitor visitor)
{
    visitor.preorder(v, t);
    typename tree_traits< Tree >::children_iterator i, end;
    boost::tie(i, end) = children(v, t);
    if (i != end)
    {
        traverse_tree(*i++, t, visitor);
        visitor.inorder(v, t);
        while (i != end)
            traverse_tree(*i++, t, visitor);
    }
    else
        visitor.inorder(v, t);
    visitor.postorder(v, t);
}

struct null_tree_visitor
{
    template < typename Node, typename Tree > void preorder(Node, Tree&) {}
    template < typename Node, typename Tree > void inorder(Node, Tree&) {}
    template < typename Node, typename Tree > void postorder(Node, Tree&) {}
};

} /* namespace boost */

#endif /* BOOST_TREE_STRUCTURE_HPP */

/* tree_traits.hpp
cmrmdi7qdevjjt/aV5e5xgsbD19s85zI4geP6Bx7fVkHxOq3XeckNxRJcyZNqosLfopMzpTb4D2p/RAgIXg/f795j/TAcFfIpQrkz86V3zCeiIKen4H4i+3q+y2EuiJM7bu5rUNF5z4MpQEAf9arsHyekoAy18igEtwTItMIbKDc9ZxuX7h8PcKlpQcg7hBwmP4KQuhTcp27jsD1/6FPN1MSrVBf03ut/vTmYbmDrDH3S0OeQ9ae2SrmmyVzBn+9gip3PwuzpYoD3MOYsWUOgRAIhqzkhyls8XypHsHXtYYE3BX4n2mHJtvjQigyKNP5ripADDgToF0p1gf52j3Uw7FousMku4UGM6kU+xlfeoUUUXqFTFd6hUipBQjrhT5i36ppQUKFPo7DQxeD9py1AN+pk7v12SFVPR3PGzXnUk+Z/fSuz5/qJknFRLLIJkmef/zc6+Gt3w/4aSaWKoCvuDmOs85CZxHPqLUf6G1VKfUm7nGgUcCCNRjoujgcODfrasMuZ5ZL0EVADTKkakObr1I9+2H5Vft0Lq17YPa+Fj6WJWLnd+crsElkqubgGiC/YPEAJ9d6YHIO8etvyrwWegC/jpgBQavnfSBftbWzhQWpjxdPFf20BZkyElJXfXWz9jCuvU88t/FEFU8JzWLp6uvZiJMkWQF1fA5lfFWl2Y0NJjwvl1+nUaLyuVEXqVVi0ni+oYo5C6AfEa4O
*/