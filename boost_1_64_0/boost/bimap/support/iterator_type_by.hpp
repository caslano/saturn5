// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/iterator_type_by.hpp
/// \brief Metafunctions to access the iterator types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>
#include <boost/bimap/relation/detail/static_access_builder.hpp>

/** \struct boost::bimaps::support::iterator_type_by

\brief Metafunction to obtain the iterator type of the map view by one of the sides.
These metafunctions can be used outside the bimap framework for other bimap 
signature compatible classes.
\code

template< class Tag, class Bimap >
struct iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct local_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_local_iterator_type_by
{
    typedef -unspecified- type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Implementation of iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    iterator_type_by,
    left_iterator,
    right_iterator
)

// Implementation of const iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_iterator_type_by,
    left_const_iterator,
    right_const_iterator
)


// Implementation of reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    reverse_iterator_type_by,
    left_reverse_iterator,
    right_reverse_iterator
)

// Implementation of const reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_reverse_iterator_type_by,
    left_const_reverse_iterator,
    right_const_reverse_iterator
)


// Implementation of local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    local_iterator_type_by,
    left_local_iterator,
    right_local_iterator
)

// Implementation of const local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_local_iterator_type_by,
    left_const_local_iterator,
    right_const_local_iterator
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP


/* iterator_type_by.hpp
mZyPd7Ul27QdLWzDPFG7TVmz1rQp5h1ht5TZ0DQKbU/t+Gv50Hl8Jaq/sFrbINvRj+15vjdIPvBivnSUVl+aouolhf6Ax12cPOGEyQt1N0T1QCLWY7WTbnQLp4p5iRXpeZnGlcYbNH+D1+WevMLUSA00ek/nib2x6KLE6P3ddm3/Jsv82rlib4HRGykK6iVltr1NJ0xheiOa/pIe6ZruhMHdjsj5fHPeCZu0q5onKdqg7kD6IPciD9jvM8E8wTuZvisZsrC6qsyS+FZKfQ18S7nqh7o7zryfdLjRNt8Q2IcyXdzgh8kf7IfuQxkr9m8P2Wd8IXuxuveitMTOjWLON35kW847jsR1AZ9/48a65vTPF3cncjf0vdR/SmVp7cKaCr9zD6mfvcXuFZbWHd4/JN8MJ7Sh7qRrXlVKu6Rp5d4HOF3Okx6aV6buOHGW7y/Nq+2aV/0RWSsRuctux27UvDJL7QbePXkD00e6vpeFrZmrbvGx5Xfi0DY8qze2XJdbwzlTW+s5+rw+G7kTu9ZN3uGkiHm+Ow4Wd8Otdqy9TThDy3mTzh8f4QuEaQjs3ZOS4hEmjK4yiEmfoZpu6m6athNuO9JO6LzioL3xErdYaaOKa+xCkKlxu16ub7Y6878GuQHRcq1uexMOfTaE1LfJUrbWiJ0eYe//6fr+/5Zcn2H1IC1ykS66t/+IRvnOxhysM3VL/C4d5l+Ku13WOEI2y0qRd9b8FMogqVliv7N2brivpX5JX7WTkhp4NnWIjW14AhVN7+eT97vmaA2f7W+w7fxzGvPQMnF35PzX94L4bsRT2s4lpUsKaT+1TgbrmZOvmUG9Fct9Xtt8rZux0o5K/qk/mN11u0WZy4mgG3A39vc36rx1XbDb0Y44ev2IpyLc67vcK+XbLe5VH3j23RY+Rx67R68fcZvOgW+ZBhsjzN3/NnZzW4QLDYmQtura8PCpm3SpD4vluu2irL5qoet53yIO57YjDtc6cTB9JIvlnLlPiO6Lv0d43B7Efn5o3FTLwjNeaj9d60KYngXXj17P4tow3QTMRs8iND556eHx+R52/aHxUU0Ly6scYb9VXQuuH72uxW1t1LXYGcNzR+b671ub/b0RT1UdXvnRpkdWber3E+Zm++zz/p1Lrvlk/5BnXrp5SlbOW+OZcHtlrH3+znN/Hdf5mn/dP2DbywOG3jHjVPoWR9jnL/rl8k0pL6dvnrFq74WVhwp+4KUz4KWz4aUb0H4dAy/djNvl/NRZCzPfKjiQk+jP2nPViYce99Lx8NbBKEuxz9/y81N++Nady/+y8fYPq613R4311vG4WNJz/+TZWfVDb1y7o9ekGxP3fP4e70iSbi8uf+mZ/3xy04HLru/X8+G1F3TgmSXnM3+1Yu3hgQWPXbtsxoPX/PKBZ710Wrx0Y7x0Xbx1SPIlfe79wd1nXB0X+/nkhSf9qOrNk4rbr1vyb7F/+LUnEr575crGs145WFxxweA97dc58dCN8dTVOai6FxzSh7zVF+iDne/6fb7rd4nr9xznt/TjjZe5rbQl+vtMfl+gvxMQXXNcxx5kLINroWuO+7ls8xLYXc3psAYOhrVwAqzXOajLkJ3qX6P6lwzlwadzm4/XOc05ah6p5jw4DM6Aw2G+muepuUjtVcGR0A9z4fUwB2p8tE+ZdIgQH+yKDsta2A/eCI+D34a58GZ4opo/gk2W9sdqf/B4pIfM0efQOfnZ8DdwkJqHqHkUfBqOUfNF8LewUnVb6uHzOqf59/AmuBN+G74E74K74Bb4B7gVvgwfgq9ARHRc9sBXoc/WS4ad4JuwH3wb6v7p2qdJX6emi3v/9At1TfyLNF+L4DBYDGfABXA=
*/