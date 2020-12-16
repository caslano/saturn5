// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_by.hpp
/// \brief map_by<tag>(b) function

#ifndef BOOST_BIMAP_SUPPORT_MAP_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/support/map_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>


#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

/** \brief Gets a map view of a bidirectional map

Convertible to \c map_type_by<Tag,Bimap>::type
Instead of using \c map_type_by<Tag,Bimap>::type this functions use
\b Boost.call_traits to find the best way to return this value. To help
the user of this function the following metafunction is provided
\code

namespace result_of {

template< class Tag, class Bimap >
struct map_by( Bimap & b );

} // namespace result_of

\endcode

See also member_at, value_type_of.
\ingroup bimap_group
                                                                        **/

template< class Tag, class Bimap >
BOOST_DEDUCED_TYPENAME result_of::map_by<Tag,Bimap>::type
    map_by( Bimap & b );

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES



#ifndef BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Since it is very error-prone to directly write the hole bunch
// of relation accesor. They are buil from litle macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and mantain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necesary but they help a lot to
// the reader, as they undercover what is the signature of the
// result code.
// In the end, it is not quicker to do it in this way because you
// write a lot. But this code has no complexity at all and almost
// every word writed is for documentation.

// Result of
// -------------------------------------------------------------------------
/*
    namespace result_of {

    template< class Tag, class Bimap >
    struct map_by<Tag,Bimap>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of

*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    map_by,
    map_type_by
)

// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    map_by,
    Bimap,
    b,
    return b.left,
    return b.right
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    map_by
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_MAP_BY_HPP


/* map_by.hpp
9ruI2Y5jiZj7yfwD5uJwaJxJAV1HlGNJdYnlhOtNuT6Y+prYyji87+pUSaMJUm9mMW9ogJUs6bH7p3b5jxBzzVubA8SNhp18e03zjUiJ+UM1p6m59+W6loqap6g5Q81z1DwsK2De0eL6XjVnqTlmecD87/6h5WR3J10Tngp8mjIZN43LQ8pJbXn1pWXFdcWVWHHXoSV1Tvurbs4w7eL5K2xzocmLohi1w106mbwoN+Pdr8u169Tss/pcaZv7yP1ulRaD+1lOWblD/I83ZeXiK2zz82K/jxQWGag398cLc39TnnQOQKpUWcaexM8eMTnWb3Vd2PAyN1LsuMfxuV6Ya+pMmVwfH5Pk+53VyRnrN21N0wqdw6Pp9J6Yt/karBfVDqubr3DmAuSbuCVrvdG0uNSZF3az2E+OSSY9duNPyzRJddL7zKVM/ZhZvcik+6NiZ0Yr6e5fUrvISaN/if3Tecr0DKlnL8n5obLebQ732ktFGZ1JeTq5zErn3BrMbyNjOBdb1iEhOWGUaU/HZloSxs5yv8K5pbXseuKkueZLgqxpa0vwHoMSGe+z73H8yjfsc/vwP5tz4/Scy3/jNrgW8ne4V66248tiWq/zKTFS5wlPsqTBfEkjy5gnqdleN/ciSQeLNn/0OEvPFTjnTgyem+ucGxs8N9M5NyZ4bopzbrQVnBMXI88LwkQ5cD27Kfeco9yHtT1azvXcreJW8lXah13aPuRoe/FXNZ+g5v6S/oy1qnmamseq+WE1n6TmdVfoWoHB62qepOZP1Jyn5s/VPD8zYO6p6TmF6+59lIp0P4KEAKyOyCDs+K+y7TcVMqdwYXElep4lFdWFfpQ968oKq2WB8tpW3juypWCjdyp19dC7gfY84GweC1vznG6xZnBysiVHlvrQG/mAwtIg4WggADU0CmNGhbaXnDXvJGpX3znqI7Qzq+R6xhHDre9y+v7APVq8Q+GhHNWI6kFa2bZ+rYZ1aW1VIKV0bl5frtFuT64vKyt1hVftH2/Wp39FzONkzmJhlsvNlOr6qjp9tzLujjPzpV4Wc15gvmKKuJtaXbOk2N22vyR2zhZzvvFjoLjxdxA3p9csmllRW+fMX90pdk4S8xzjJlv24Ukhv8o70/ZIu3A8jU/sCckx/O9otbkNimmQdlHaEe+5V9kz3OvX95V3aZOWZq1s0kvPm/Qy81hJE65pmqhfBZB4c97EW+rJ4atMvQzJ815aYvya5/OQgdjJa2iR54WVreU59kPzvELMJx0xz3EXkudlYj691TxfKHZmmjzHD5Pn/QPhm0nt5vXYyfOiBmdfnTnGTXbEcuKey4o9Mye1yGo937+j+e4uJ/+L/O8vfmka6Pkij3JxQ0PkcpGcGt4WHIednU65uDTYGKTKu0bkcrGzRbn4rMFpCwZa3uViZ4tycbDBaQtu9SgXHzeEtAX4ceS2YH9DaFuAG9MWZKUE9g0a9wXaggEr298WkJaRygIx8S4Lt7ajLchaaZ65IXsdDU0LbwuGYadopZPnpjHQujDEoz3ATUi+X7eybe0B7kLy/ZqVTnswdEDkfL96ZUh7gB9Hbg8aVoa0B7hpW3tQtLLt7cHDK4++PRhyFO3B0AFfvD34iSkbzvzejTFe83K91vv2Wifda/7tl78OxLFaP72DrNve7Y/Xl1v/mtrz5XNfOO/kKR9Np3eiq33+hmcnXTX0g8qfPH/3zNm9VjYzn/mCXPv8xcsWPtCv/K24+pPOuv/ac/+0hLmlcv4nf3/wwmlPbL7R9/HnX+t+88bNrDcs51PGbD5lXFWHhbuffOTde3788/vav25+5PnJx26esMf67B7zur3mObd//wCv+c8HLcl7jkA=
*/