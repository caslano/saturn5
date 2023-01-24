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
J326i1BLnANC5SKJilO6PKpSo597wfxYDg5tAsXsq6MZuJpWstrlm5QoGHiBYGBRfA4T0591ewTk+T4nDHPaIjEMXIETAlKywExxYKActvxMQMKAIyGQKrBLKqGXh4eo6AX9TyJ6GfKbDleUdAtCL+17gWKY0Mus/ZLutNCXeahbEN05EEtlnOQsjUxTdgTsRyCdscxVeBY3DRw6EJa5GGoBaadFGmCZF2KbwjLj3lOxzDYxE4BjYgDHfH0smPSgsbTYWXW9VQxTeqwpwoNmfmjhb1l0dRB+cRnwi+iXW49f8sc3QKlBclLVy8oHepJlUbVUNsgL88UgpLdQD7ub2U2I8wpKMVg6bVmX76FYNPY5GkqQ2BohsT1A4rMddHbuUWg5BaZJ125Bc4VsMOaxQpEyZEoXxKLjR2jeKfYG2jqx0X+isuagiVw6JKJ6AI4pq5hnfUdkmpCfWxOwFcLlRZc3d7XotvizDL8CzUnuQVEgcmfH1iblyV4kPBTQ0Q5aILgE478HvFgJ+cHt+3TD93hrRUgHHV+xmJh/Ql8oxEn5BKkECy5OTyRJ4vLuFrXCltAHmlbxCyQY8WfZPxB78ws+Iq+B3vweS715xEw4oIRNRDMNRgzoLCGGGXa05AcjgHjYgg2weXqUwnLMiTWJ/ai045cIeLHwSxS8NKyhFzjTVer4JQZefuAXOAVWhpwy4e6Oh5dKfkmEl5tP
*/