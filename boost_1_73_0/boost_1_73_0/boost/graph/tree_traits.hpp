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
ZKFHch14YHnX01xlS8J9FVZz5B8e99/ZRhNtIQft3hvHzSjs3Y/zw4x8je5weNre79ADDpWgV5gFZvdhs2m2D2/0C1I9WgzH9GgqOKFnPKMstufDFe8+G1SqF9vq9n5sHzcFC7mTxTveh2C2Cr2LCN2U7fgKnDSwmK9eMmTaWm94xW+8XTNi9ZNri+zaMAaKEyKxbRZkMAJsEXUZ8ZQPjTUekaBC9GgC7Gaj8V7xjKrCx/oUrIVn1kFnSk8xueadhzfxwjr4mzQCqIAPpYl9qkLX1qT/cK8BQJ+9ArzE9toKZLhJ3hRRBXZll1v91t4V7UdlHEghpkZ+K9ALM3qjjGKUx3g4aIYV05GLYO8o1sDjwJQ8+MCIUxUvVb6QGsGpFlNfOysQjehhEjIZTzkOSk1apTgKztMGd8PhrMYJQ5SR04WmxZZ87+3WGDMB0RdzjByly4JlP89Zg21Rm0Abd40RCj+4DNLFTf62PBlPhcl23S7ebRNLVtux0BWb+AVvWf5NXkmWyVALvt4xDwUXfqThx2U4zqwDV8XVWjuyuz5IrwyTbd5SNbZbK1DV7lHbi3uI8RN4F9NAcOgX7AYL0IUVVzgzX3DDfPs5lGdGbMkhJbYTvvzyGrvZjRpoOPn7YmcjvVu+DuWD04IE
*/