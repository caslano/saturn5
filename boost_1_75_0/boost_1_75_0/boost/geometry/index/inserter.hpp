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
sIVHm/mjRG8u3W/pnJEIv04D4IiT+o/GPa9OwyQ5ob4jsYp/oARbmfR3hry+je942qQf0s/3MhBxgQPE1RR5rM8gduMX5n7vaWLGkltqnakrb9FPv5XDD/37yK2KoN/E2eAGhwAMucb3t1JNoiWtysMR6LRg+DttBRePYUtFQXlR6fdi2dIZKTlD5cv+tvp94+8mnzT0v1e4Jaq9evrtskWJVl9y3Rd5UYOfKz2WIxmymj/1Pv/t2ubnSp/sYuVFRLyPIdI9G4R7EbeskCgQm4NXPBzw3pzemJAbXfmy0ZF8eZP7aZWl77cBg8ue5hwcEtITa/YSvbbi4W0M+lLyqPNBqdR4k6nEO+An2z+pLZ/9f2ACVgwfQ/I9GUqkhH5C4iz/dIfGnNrQGrf7U8TaGkozYTIts24VM0Emh3X79xEJaQqu+1ITEGhDf6bv21f+iV9X7+Pdh5f8iHSHyPN7KM7Fu6t+jo84fV8vjkN0nUqNiJPXrX1CIOJWn9Y7ua+Kn+lKPtlkOkaKYfq9pkUvinvfmOp/X5Hn3t990Gr9wOyem1JlOQ/W/Xl9K3JiZV6zP8u7/IiTYGR43IB12CXe7Aw+o9mVWw3RgQ0Y171c/LbZs6gUUIXH9M3B7pcKPmS0XiKNEfPKyQnwzzGFv79s2qHpOezkpvcSRjD6nPd1Jy8FjRsJTPKkOb5VrvzYk2//l9d/0lu+pW/J3pJu
*/