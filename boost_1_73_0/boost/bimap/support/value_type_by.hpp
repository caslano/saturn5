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
V53d06nMInpyhz53OarIW4v0XazkyFgsnkiYuSJQVJtm0+BZRzqbEFq1TRtNpLMFU2g1di2ZzZkZoq0KWq1dIxLlp9t5CAezr7Px8OYPb6Pexo/Lvq0L2jIVWn5RrEA7yOsua9fN8aQ5Uhpj2nKVWjo1nioybXmbljdpo3xcK1RoiQlWZ4aVF93gdVa0a2YmyerMtPPZxCJTzonDrhXzyVJOaA1SM+OFJTH6jhaoNCYr2TWo
*/