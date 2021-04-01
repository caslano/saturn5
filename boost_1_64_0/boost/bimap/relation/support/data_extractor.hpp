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
rvCxRTLkTr3EK1iR1uUl6AvgElA/SLEpdyUMtPnH2o6sDcLZQFti50zwnwh+XBxKlMWquBXx5PSbzvysFUH4V8/fU3GJhP4wtJjLloEi1tzo/s2uKbKcG0HarcZMVo2kdjVQ118I1sHEicAM4StlWzI/PM15opTy1uueLEZC9sl5oGTHKziKHn7HWMqbGjGRg+CM442DCEce55gxMcqX9IrjjQ0X9PmgqCkTiBlKr1rdU5PaqtzdHZzYmkw7W+rA9GLQiGX7//shRjIoorWwHStMD0fVWWGT+vUzO7YnjAl9/o2gG1bQcRn9HGfJSSk+Y8x+BnVWmp8F6WR8cB4PRViYapjm7ceyDHSn8sAvajTEe1tEfCy9SiK8KVJdH7l7dv9K5DhQV0igEGqcAQBC3Ij4Uf/RJOewQe9Phg7nRbORvaixIiNeByjQNWTVPFY0c4X8L7dyoHhMfbHCvv9LejUCOZmh9snDGZejmf2wQIKYVAj8iPnJcCXQtKoDyzM9v9ASnN/7OQRfx5ktohxJI4/Rk0y6VexUsRfdhOlq8zvVoRUfZoor1LYqFA==
*/