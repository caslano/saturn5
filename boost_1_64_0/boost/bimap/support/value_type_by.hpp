// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/value_type_by.hpp
/// \brief Metafunction to access the value types (std::pair compatibles) of a bimap

#ifndef BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::value_type_by

\brief Metafunction to obtain the value type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct value_type_by
{
    typedef typename Bimap::{side}_value_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of value type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    value_type_by,
    left_value_type,
    right_value_type
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP


/* value_type_by.hpp
i+8fy9pN7dpD1rV/bJv3jv0i+8Yegq69YyPtG9tyz9gj7hXrtU9smuwV+9XtE9uWPWKLrup4TPaJ/bL3iG3L/rDZzyRaeUjJM9H+7+gRPaJH9Ph/Pr6y73/UZ4/F9789D+AhXkab5Pu/tt7vr66pKy2xva+vLA3MA9jG9Wa5XlFVUVdRXFlxuWND+wcO8lI7Vb8ltwb10W39ePg58sc+jEuXBtYSmD1rauGi0rpRrB9dVsy07uAnpWhdq64W86c55IzRtf+FuB9hdDynltnmAqsTf5H0RFNhvNg52cpE5+Aw5gO+gM5hh5hYf9LQDjHJcZ3CdcP0fsnitk9E3bDu8F0JzykB/QP1vyAm4H/sWbbfcUnxgZsket3jHfFjcMR7pML35Xqm3GMA3/8dObeNVD6UIWtRC+sxL7WlDfMm7H6NbaWmXyOkD2BarCnDZj2BR8n7/WVOvlUEst3Ov8KyyuJFtZpfn/YQnf8S1/rf6i7uiH0EQd05/KB/QvwICdeeCOF6jHBZiyKHK/DTM1y4OzbhWqYBinfV/Y+ZmJniES7tdvEKl7qLP+pwBfUz0+LDw7WD9Mr2CFd9bU1hCYrlrYUt+wuGLZhm98VHTrNcj7AtLa6sL/UMF+6OUbiWdQgvY02kWV6EcNW2KPsHw8Ol7uLMmgk+S1yYtiOvnWXwoAm3o2eMv5wTf0PyP79jeBo/0Z/zHnEx+e8dH3Ubb3TYfZZxZfSL8tuZF+44pWuc8Jtzxu8QHar5qnCco/3OQ5APKDtFrnhptIpL8DV0bxgTF7XfS67/Hfc+q8Ke9abxCF5Pl+vPpUvemev55np30//8n4wjt7u654J7DxWz5ghh4JyEwaw5wn05J/cNKaf7EsLz9mnydqM7DcKrtsTlVclXP5edtNjYzjzDD8IlfoSEqykxPFy/secXhoerti3h2tqG8rb1C4Tdu7w5/fop2hn+nJa3Zu0TbwqLU21hGa9GteWm/nDYNczp0/+PuKlRs8/aL+ausiYDU42tgk6EJdPWae+cnNxwkxVcH+H+bgGR9RbU7grsxondhgeDZTAvNWBngNrZjp147MSelnRmUk7S4KSBvPFk8CrSI93MtyxOMRLi/2u47WD73zXXlPELuwfs9G3D+0X3cuKmZdidnhs6W3J8gHRH3kZ22u+e5WHpKRNFg+3R7VIHF1aVmfZI3OiYiOrBi3mndQb3q0S8xlfONm6HmnWmDol5uOzM1KK9Fv97Yn5Z7Oy2ZvK/DtE1idSvdNf7Z02pW0/xigr7epqafdbtYu5Buqp9XZMkjV/nyLUZ4tfPpAwtrbRc74oXy/XuRo+S67WlC+tk05l0tfN3Cc9U+na7odOTom6DcewmbjPTLQ55stZarr18xon/VYQtSXR00yj/h5Lp5yYiybENjcnx8cmxo/lvWV7lU9xkkc+f2G46NWwMlp+vqZ1MzLb7P2eIyBjWIspuQhvGsYJt6O3SNlIe9LkxPnxsS9vRsGekaa82dbXk2IX0Rx6xf/Njf0XksqgfJ65yZZ8Iea6o20FGdzbtYtv8QKtlETdmrO88zNniZmPE94ZyY3+EmKsw9xH7d4v9myRf7Y8py+gGD5XrN0csnz1hplz/nvnmSrAkouYba4Jcr7M6WrEh+zOly/lBVrprf6bT5dwSbE6xgvuVvUcef4rsRZo1vzvqvkvvZBw5z2X/nIvdey65988xeSDnp3mUg/zwcmDapDXyH50ybeNfRw715t/i8HJQXyWtkklL8rOy0vlWUzcZJm0zxLwpYl3PkWu3muef5bxvSdmZI9cvUDPa+Yu1/lKTtlB2G4hnkt1Gd+lr2mhTD9XOJrXDc+K+lnYy1c7uFK4=
*/