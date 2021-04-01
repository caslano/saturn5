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
Q0eS1FUCE5cFhPEeBdnADdVwNYO/RlMFBRxu5Qjn7JK5ZrHvzucCS5cNdf/0zB4OIVBnsBw10RirTFKTEqxIveJFOksys73Z3iq2Rcbw/qQP4y/Kb4dfOGNJOdjPTxWAr4PBBl9Yfn6WvkX9Cmoe6gMUWj0OjH5jkYqRSKZ5yhU40ph3nqLti3IZKdIjZ/jEqn1a7E4SZ2FZmfeHgcEn09X3HPGQhDRV4WyVwycqMvZLiaX+wiPK28/Fv7LEFwiDvrjy4xFgOGqnXYWVGGNIwRKL+2o+Uear1cRV12hhzwHIF9mgw3xOb+WtgQ3b+hLHh35jbqrmm+/Vk1DbkFlsGT0kF82BHgv8LtAjLdCqeaV7HmMCZBetrZ58Y8bz0NuqkkoNiRLzuUZ+auZyqorT26g4p84o/DvvVm2BAQm0qA2ErcAGp8JNZQh2obwvcwcxeNcsGzWjbx4MbgG+TNsggR34rUFjAAgcMfRVXSLLdXOkBNQEGlA7Y46kra5qqaYJ6pXwFmGY9R/PvpExRvnbHs1lo4ufWkICDGqBnRFbIG4VaD6REhT0SO42SA==
*/