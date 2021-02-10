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
kJWQGm2NG0by1kHEAjxbZiaHIbvt5DPWHnGwJjSagFg2SB4mvxI0fjN7yprybz4/Fc3/N5OPD9v8hqtLkDuI6OlvomUfJGhFoPfcBSl9lD01dhdjdkGxsyvYZJWiiUMGodsFiHmIO9KC9X/O0zevJMhppf4o/knPa0L30uENIZ4aBAfFg50/Z2U5RTIEAibAv49yodnCDYJlGxcpEUdwvckTijuyLuXYMPAJZT6QnIzf9IxruUQc03b+pXjoLST2euJLFwdwgiFFsE/mGPpsbp6iPyratok1JMtc5NUIqxnSDdtgf3iGAssaA7PA7m6BSImmYT4YZ+MryhsfjEVzwm9gm8rpJ6G35FmCjqvlTUFvFkDyqqSHJmaksSADC5ADYxc4tGg3oyugxwaLYNwGENZiMUtmZVXleGlBGgZuDk7krxis5vuo0vOMVK4+ng2oJLzxqtuWJtOS2Q0ej0P4egyqLDuNkbPjjdx9dXR8OtwbvfqFVFivdl//9DxsgZqx0fD4+Og4ekGOt/4NS4BIym+yx6iROivnCLCTBfEKhvSrTxXCJDC/pA0lcYE4bOV5SUZgppMzSihUC4Xj5Ag1MC+UNOIS/ZgBpDRSbgulUexQeyMHZp1DJTrFsi7H5bQiRigBTAFQQQSTWHSO
*/