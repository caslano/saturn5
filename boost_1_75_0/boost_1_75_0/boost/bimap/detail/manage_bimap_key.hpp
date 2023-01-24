// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_bimap_key.hpp
/// \brief Utility class to manage the set types of a bimap.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

#include <boost/bimap/set_of.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/** \struct boost::bimaps::detail::manage_bimap_key
\brief Metafunction to manage the set types of a bimap.

\code
template< class Type >
struct manage_bimap_key
{
    typedef -SetType- type;
}
\endcode

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Type >
struct manage_bimap_key
{

typedef BOOST_DEDUCED_TYPENAME

    mpl::eval_if< BOOST_DEDUCED_TYPENAME is_set_type_of< Type >::type,
    // {
            mpl::identity< Type >,
    // }
    // else
    // {
            // Default it to a set
            mpl::identity< set_of< Type > >
    // }

    >::type set_type;

    // Returns set_type and evaluate the concept_checked_type

    typedef BOOST_DEDUCED_TYPENAME mpl::if_c< true, set_type, 
        BOOST_DEDUCED_TYPENAME set_type::lazy_concept_checked::type
    >::type type;
};



#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP



/* manage_bimap_key.hpp
IkZ2clGFuEgied+C3wZhg2h6ByL2FnlLaWeJEFYZt0QYtH7K0M+Nt2j9JDhPfSXgHPGVCmf3r1Q4v96kwvn+Jj2cwzaFgPPapuDEuL1BcI6q0MP5A8DZuR6cERsFnI9uUOG8cYMK56lSFc4NpXo4x5SGgHNuYRNwZoaA87NyPZyPRYGr15uD4ey6XsD59DoVzlvXqXBGrFPh/PZLPZzTvgwB5/E5TcD5cav6cLYIgLM94HNr/2A4r1sr4HxljQrnw2tUOLuuUeE8vVoP5/OrQ8B5U1NwmkLAeX9ZAD5bMDgvqwena5WA898lKpyzSlQ4rytR4WxRoofzw5Uh4HxudhNwjm5ZH85VmwPoU2ZwPpUCcOp4o/ytdyewjanR3t+MHrQSTmLVzVtuZq1H44qHnZjxOXWCwRLJYFF2Xwwz+O7MArFsroXzOpVxqvwlmvgL6qPESlTdVVuJXPJWwBZo0SVvD1BUeqywaKx81mxYjyYQE8SKESbWoXMjwMp5C1uHwL4mGWMR3gHrTnvkeSI/mB0US7RW4grzvFkc9eIKE3pNYqx7/3BVZldhvjEY5rN6mK35tE0PAnTucAEoXDeOD91g3jmUzXvzUExDqi/FhRQ71DFUh8rVDm2MDOgQ4G1WMQ8axYbFOlxdP3OntjWAoaiTiaquF0FchlVMd+88RhADyEDu7uj2awwb9uvKq1szePy2S14Es7dyi5Ry
*/