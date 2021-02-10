// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/data_extractor.hpp
/// \brief Data extraction functor.

#ifndef BOOST_BIMAP_RELATION_SUPPORT_DATA_EXTRACTOR_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_DATA_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::data_extractor

\brief Data extraction functor.

\ingroup relation_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

template< class Tag, class Relation >
struct data_extractor_implementation;

template< class Relation >
struct data_extractor_implementation< member_at::left, Relation >
{
    typedef Relation argument_type;
    typedef BOOST_DEDUCED_TYPENAME Relation::left_value_type result_type;

    BOOST_DEDUCED_TYPENAME Relation::left_value_type const &
        operator()(Relation const & rel) const
    {
        return rel.left;
    }

    BOOST_DEDUCED_TYPENAME Relation::left_value_type &
        operator()(Relation       & rel) const
    {
        return rel.left;
    }
};

template< class Relation >
struct data_extractor_implementation< member_at::right, Relation >
{
    typedef Relation argument_type;
    typedef BOOST_DEDUCED_TYPENAME Relation::right_value_type result_type;

    BOOST_DEDUCED_TYPENAME Relation::right_value_type const & 
        operator()(Relation const & rel) const
    {
        return rel.right;
    }

    BOOST_DEDUCED_TYPENAME Relation::right_value_type & 
        operator()(Relation       & rel) const
    {
        return rel.right;
    }
};

template< class Tag, class Relation >
struct data_extractor
{
    typedef data_extractor_implementation
    <
        BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
        Relation

    > type;
};

template< class Relation >
struct both_keys_extractor
{
    typedef BOOST_DEDUCED_TYPENAME Relation::storage_base result_type;

     const result_type & operator()(const Relation & rel) const
    {
        return rel;
    }

    result_type & operator()( Relation & rel) const
    {
        return rel;
    }
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_DATA_EXTRACTOR_HPP


/* data_extractor.hpp
l0UKN/YKKOhDMImNBSmswyFblAr4Wqn7EsHu6/t4WRSwvbX1CosGD3I/M5V2hRkLplwF0Z2Kuy3FiGUZGl6/PQ6p6rw5YlonwgZ88eLQugWppe7h9ZdXHltEhmZBoQrWnLPc4eXEywk9GKPTcYQvBKy655S9vBnreet+X/d2eEvq1M2g04GdBmxsQP0FdpV4ntV9Y9v+jPKU5h6QwpWg0WiUwUDDtcKMwbuEv2PdwauEF/MLufEiKBxSGv53zu0Ku2e4ROPwqN896J+Fa1CX5j+Dl9ALV3eEIlO85afc+ClJtVGaFVKrxmsEFs2Mu/LE4cWruBWUJhPNepplhaAipHuV+F7K4yvSC9wYbWzFjYiTgBcdb2U/Gr2v0JxmOIXcFFMRnTSI+0MVDZjifZYnu/CrvVQPimINDme8WtLVWHOayQVbWoglZyrPHmZVeVD5UrEhEmrF5HtkNbRwmmB/WZdDR1PDeX0N81IMbUM5qNY4inqhw4hJWb8X5W81qKKwtVf7VvsXUEsDBAoAAAAIAC1nSlLDS5gTpgUAAKQNAAAjAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3N0aXQyLmNVVAUAAbZIJGCtVm1T20YQ/u5fsVGnje1RbCCdaQI2UxecwMRg
*/