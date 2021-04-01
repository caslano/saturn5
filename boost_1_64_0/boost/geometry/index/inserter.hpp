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
ZMIhSD67rA8cqbEH9OVOnn6LgH6fCC/aZaDNzEC7INCnMeu7+/zjOESgzVmEsb/3dlxKe1rQtYkv/WZ0ZF4/Wngqv0rmNRG+uSnARhsrPzQqXQg+xH0OovuwdKD0oIqfYSm6arjjdg5XWgohnFShXDUmAKgpA2mtW1/+N86iMPQlqx88B29FQZjN5y26EYDksU0QadljgaUSlX/Y4MsmrsJx2L2NgHM4HTk0Hf5n1esc+A+nYX06SChkmxJNeklrnGwMDRImr1yCHmAVgrzIm9jFbqV/htyFK5UodCjv7HdR2nVTVx5qefCoos42HKPFrGnq3Xs2PVbqPcUMHHtyCg6pw4py6MwU2XUsSpSCPxeYXpGzL0+RMxODXK871LJNjdbRaaYdlYZdwPi0f/ELR1L1J0dn/QQQhqTNdbfTrRM8UaZA4kqctJlQ+sz6/izfuhxKeKULsCp2GRoIV7R7xIeRqS1cEYyaaMbFHGtnsT/h2/sb83xrBe7kdvA2v/1y0iJAXycAV89WHh5IuEa7LXUfhpIoIzfmWxQGK1VCBY+gh0FlBHlUdRb1Hw==
*/