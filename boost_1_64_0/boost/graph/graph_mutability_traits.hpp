// Copyright (C) 2009 Andrew Sutton
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_MUTABILITY_TRAITS_HPP
#define BOOST_GRAPH_MUTABILITY_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost
{

// The mutabiltiy categories classify graphs by their mutating operations
// on the edge and vertex sets. This is a substantially more refined
// categorization than the MutableGraph and MutablePropertyGraph denote.
// Currently, this framework is only used in the graph tests to help
// dispatch test to the correct places. However, there are probably some
// constructive or destructive algorithms (i.e., graph generators) that
// may use these to describe requirements on graph inputs.

struct add_vertex_tag
{
};
struct add_vertex_property_tag : virtual add_vertex_tag
{
};
struct add_edge_tag
{
};
struct add_edge_property_tag : virtual add_edge_tag
{
};
struct remove_vertex_tag
{
};
struct remove_edge_tag
{
};

struct mutable_vertex_graph_tag : virtual add_vertex_tag,
                                  virtual remove_vertex_tag
{
};
struct mutable_vertex_property_graph_tag : virtual add_vertex_property_tag,
                                           virtual remove_vertex_tag
{
};

struct mutable_edge_graph_tag : virtual add_edge_tag, virtual remove_edge_tag
{
};
struct mutable_edge_property_graph_tag : virtual add_edge_property_tag,
                                         virtual remove_edge_tag
{
};

struct mutable_graph_tag : virtual mutable_vertex_graph_tag,
                           virtual mutable_edge_graph_tag
{
};
struct mutable_property_graph_tag : virtual mutable_vertex_property_graph_tag,
                                    virtual mutable_edge_property_graph_tag
{
};

// Some graphs just don't like to be torn down. Note this only restricts
// teardown to the set of vertices, not the vertex set.
// TODO: Find a better name for this tag.
struct add_only_property_graph_tag : virtual add_vertex_property_tag,
                                     virtual mutable_edge_property_graph_tag
{
};

/**
 * The graph_mutability_traits provide methods for determining the
 * interfaces supported by graph classes for adding and removing vertices
 * and edges.
 */
template < typename Graph > struct graph_mutability_traits
{
    typedef typename Graph::mutability_category category;
};

template < typename Graph >
struct graph_has_add_vertex
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_vertex_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_vertex_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_vertex
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          remove_vertex_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_edge_tag >::value >
{
};

template < typename Graph >
struct graph_has_add_edge_with_property
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_edge_property_tag >::value >
{
};

template < typename Graph >
struct graph_has_remove_edge
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          remove_edge_tag >::value >
{
};

template < typename Graph >
struct is_mutable_vertex_graph
: mpl::and_< graph_has_add_vertex< Graph >, graph_has_remove_vertex< Graph > >
{
};

template < typename Graph >
struct is_mutable_vertex_property_graph
: mpl::and_< graph_has_add_vertex_with_property< Graph >,
      graph_has_remove_vertex< Graph > >
{
};

template < typename Graph >
struct is_mutable_edge_graph
: mpl::and_< graph_has_add_edge< Graph >, graph_has_remove_edge< Graph > >
{
};

template < typename Graph >
struct is_mutable_edge_property_graph
: mpl::and_< graph_has_add_edge_with_property< Graph >,
      graph_has_remove_edge< Graph > >
{
};

template < typename Graph >
struct is_mutable_graph
: mpl::and_< is_mutable_vertex_graph< Graph >, is_mutable_edge_graph< Graph > >
{
};

template < typename Graph >
struct is_mutable_property_graph
: mpl::and_< is_mutable_vertex_property_graph< Graph >,
      is_mutable_edge_property_graph< Graph > >
{
};

template < typename Graph >
struct is_add_only_property_graph
: mpl::bool_<
      is_convertible< typename graph_mutability_traits< Graph >::category,
          add_only_property_graph_tag >::value >
{
};

/** @name Mutability Traits Specializations */
//@{

//@}

} // namespace boost

#endif

/* graph_mutability_traits.hpp
/VQ3GH6xg3xpr34LzjtmYm9k1W5E4tzYjGjN1eTwiuggPf0TxYe7kdNQ67lr9P5LDZqhJb1iHuqOSvwKgNDphkTENcJHw8bz+j9XpEf2oqJ2t6YPx0g5qA8/VM3XTis1fzTENvjqtY3YSKrQSuyggSB9lSSxvfKXCqhXiJh1ajvwG1cJ6MSDKepBli9a4BlfLGxRQ1TZYurlX9xpoCNhpyKwWA3tlH+HFv8z92PXm6UKqRgMmSQ3CQ3iR2PC1hBra2ID5S50NxrlIx5Cku58ytfzlBm9zw6HZDwjp0qwdPfpOJN2ZaDFDlZkEVGYvHWvJ4GLttSEZYe2NZIG4pjZZRlDz1glckEGYLwRJIUgNMcIJchL3tx1EDozEhWo/QGLqb/7WZppPSnGABNPYZLwTaI/WZOFS4RiLE9MH2ipIHSY/O03gclBRK3189hUEBuPpQOUginAEDrMbqFxTxSL9U42BKleeiSxtEiYA5Lfpbx+yEQLkYhDjJZDf6wyTWq+ssYEbhZcI6K4mHcNUwpP70i/PYi0Lzj1ixM+AGmL5FzvQJ2lZ6fPztKEUh5EM8BhdUK+xkbfSiTwU6yh2OYm21zXV9dDjVWGl4cQR9PTCuxiSsWyD/tSo9ZRRxhfauUkNaBFEt/nxYWgfhCl9SHN71/snXc4V/Eex3/GsZKVmZFxrcjI3kRWyCyFKDNchGuT7GTv7Sd7pmRHKg2UPTOSrJCQQqH7dX7HvffX3eOfe5/b87yf1+fz+Z3x3eccT8/34xBr2CTRKJbjS0ebeVuq6rwAvfVDD9YM45mLTkwKMRnNo7taw6eeFKlWHGMp3mLmkd4cVv8xVxOSpJZQlWH8vIKDsfZNSv+VB0q7GVUM677nDBi/F5Jq/Pbnpl4EA/5YaMyM9DVhU6dFbXzm0ae+eguXHoWatr+u7Eq8Tj97I8dSJL1OhoOSzkfOudFhfaMYb2/tjUnt24yxZFyPUcmBFrRmRrnL1IudQoas9h1C7SWap/HahqX8ne/K+trb6D15TvI/8+NqGT2ql6dd6eFRVno26LzHj+MDN2SN7ppOD78Va+Xk4NJ78fCLPL8h8UvnQqJbTb9726UNTXYmqgstap7YQ/6eSRjIKfhIY7sm//SwGGsnjkYK+taZqfZx8r70+UGOk0Vsx/b1uLvpT37XyH1DeqInR4VbaYK45zPD14s3xU3TA/Dcf5TWTS338ZlT2ZeK8J9sqox9yn3RfkRx67xWRrW0mcDO+lJLUFnLPAPtEN4V5b2IG0P1Xq2B5B03pWPfqwySd3Pds57+im9wIfX85hOV6K0IIzXaewoxZ949on42n3v0uqGJn0bP4zPnX1pFzoWEs2buuXBKDjxM9Vo/r0DenJVPN6RzriIow63++QqFj++4J//9L7HPCoUpTxuJ1Xr2X2NQTUhqvkoulBT5bUto+m4U488oXpWH9XXm2vovCN/zRFVFRLK3jIjPxvYtWxsymDf92I3PK2goOBXK2j5XrDNe8Py1oIQSrxrNT/xAIonu5x8uKwQ34+Xsr8xSKlEd20DNHcfVWB6/ONuNVtiTdeNLUPHOoTr/fdbg2kb1TORaYgnzarSxjxZvPO+TgqF5CcbfmdQ5eAh0tZS2agmwFUlO2QjqLWk1KWju+9DUuHI19eQw4hWVWdsNRNHQfaSkl63bxjVM0/guJvum4hXfcctEPChPqZWqk0bN1dKTq3ch9qhTVgVhKx57r5RldOYL1lu1tjTfqj80ytcrxKp2uFOwGKwPCmk7uT50Y6rzDrIQOOkflFzrp63SNRpJt6jLOyq9zPskmHzs3uvvS9JqZiInFkVMImLGh1juaZq3fV+rzTd5K1kveaU=
*/