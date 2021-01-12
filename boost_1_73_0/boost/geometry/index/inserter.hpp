// Boost.Geometry Index
//
// Insert iterator
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_INSERTER_HPP
#define BOOST_GEOMETRY_INDEX_INSERTER_HPP

#include <iterator>

/*!
\defgroup inserters Inserters (boost::geometry::index::)
*/

namespace boost { namespace geometry { namespace index {

template <class Container>
class insert_iterator
{
public:
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    typedef Container container_type;

    inline explicit insert_iterator(Container & c)
        : container(&c)
    {}
    
    insert_iterator & operator=(typename Container::value_type const& value)
    {
        container->insert(value);
        return *this;
    }

    insert_iterator & operator* ()
    {
        return *this;
    }

    insert_iterator & operator++ ()
    {
        return *this;
    }

    insert_iterator operator++(int)
    {
        return *this;
    }

private:
    Container * container;
};

/*!
\brief Insert iterator generator.

Returns insert iterator capable to insert values to the container
(spatial index) which has member function insert(value_type const&) defined.

\ingroup inserters

\param c    The reference to the container (spatial index) to which values will be inserted.

\return     The insert iterator inserting values to the container.
*/
template <typename Container>
insert_iterator<Container> inserter(Container & c)
{
    return insert_iterator<Container>(c);
}

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_INSERTER_HPP

/* inserter.hpp
I/emMm7NAPs23JvKuCtXcm/yPS3MQlhPhwC+e6qjXHPGw07Ms8aKuZX0/8JzRbnm5UFluN/bwZyETS75in1Pcgv9DNCs38CV9bi2MBMx7k29iqF89lXu5XZcyjz2tIoFdBzBtb0FCxA2/vbkJ1w/mK2wW6d/OnD9WmK+wq5tebiNfQhMxrr9t9lluQ4wV2FrN7RhPasBk3n2fn/n/Yy1Yv0PFWFeJ8KMhZXeULYvYw2zE1bn
*/