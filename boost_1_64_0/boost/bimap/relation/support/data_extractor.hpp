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
+5dlsjn86vOjcT8U948VygT3TnEhPciRHt9ja77HQotcv47aCj+wW1B+x1z1bEJBSXH+yCml+SPSivQKx3vxbKZ6NIzvk8MgJxG8juMiuduJTPxL6yWQImaEF8u5JjJMLNyGuSV8vdBwPZDrLbQich7Ij1xf3etWbHvhxizYONrnZhDtkzUa9Wk37ORr2G+vCpfhZqo/w2TZId9wU75JlmucH1Chzsyzsn4BNoRtttPhKs+StKJrqzOCy9JYZ5pHOf0WlE4xlJ/RXxb7qx9G73fpJMO7avSXa6hbL0X+63UL+YIc+TKUD/IAGfLg3vuPyyeZ1zXN4P3/x8JmoF3ruddVPiNL8/nFxR/UWCOvepvF5eP2X1PWtXHkHoo5xwqVa2fyzzHoezhyuBh5ZuUd5L4dc5dthn0wi+h6Veezp+vdRTqdVQEZXKudMvg2niVZYtjPaCldb4q5ETchpe7hzr1cN+D9G486GGxNCNYSg60Qyb2M1oeTRTn1CI9g/4fhf4LTf2CKfFbd2Y/bveY66jS3iSKKn1lncsvyMdZh7KblXYd3wP9ZfkZjqCWAWpfr2yuush5jqL/sN0rmfX2lbVhcF1yW+8G84srbmIr5Wuzwztcb8Bu2z5gvtHF3jjTLF/uNglv+Ro2YIuuHvK6X+T+Zb343+PcFaVRod48F+G53i13thPOr4prb3eIK7e7919DuFl+l3S2upN39TYV299E9/75291vwMeXG6bJvHuOUa6+Hjxg+sfHKJ9ZtGnAlvrzAfMxgl9Upf+OdvL+vHRt78ueHVrT/oO6L57BHGsk3fDawzuNDnwucG1SuRF1c/fL1jyX8nsYA5jzcYc8nkct655QsHvPxti2/QdlYSL562buf701JuXdvnylFv332NPZRIXlpzPwL9/Z6YtDchgOWh2UEHDcb2zAfG2hH/nO+q1+v78VpDzx/y6Do0/bfzDTX3QdSuusGTs07bVu4asaayGPlzy7ZhW8AmuNFhtq/TmA27ATD3+dgswR/C/I371H+fk+GFTxPLAysCaaCtcBmYG2Qw/P3E357jOENevMQMAKsDUaCddl9DsyDPcbpD+LwDthu7ooKf1FgOzAW7ACmgB3BLLATeDPYFewGdgFvJbeu1xccfxTHb9TrR3H+osFwsLrMF/9mgTN85Cue1xLVBePBJM5XPbA92ADszPJ/sHcmgFUUZwCezUUgAUIIMYQrHAJiOOQQUITIIeFQwiGkiiRIgEQCxCRcihpabGullSoo9QLFWrxBqaKija21tMVKW7TU2lZb22pLW7TY0tYe3/7vf7P78t6GRKDnW/jzvdmdmZ2dnZndnf+fmTlwAJwLB2r8eUbbak0X1yG/szT+kZ4/2sbj+ytGqhrJx6Gaj8M0H4drekdoPp6j+Xie5uMoOE3dexLRPb6LToI+873I1FH0vSM7kHdw18MjyxPMG9DVcySdh1ShM0B6nefpPbbg3okc4vdBOJVjlcgm5GHkGPv2w8NI+mj68F25kv5+pAwpwL0J3ofM5fce6OpM1o/m3O5+mFEd0pfs5/dRZCjuqUglstE9hhxGRowhXchR/K6FnWtC+pUN/B5fE9KxPMzvF8dA3AeRY8jbuA8PSTZJBZyrFh2KK/wugMcIUwrHF4T0L1OXk25+17EvZyC2zPzegezEXQ8Pub8HEg73IZixgnBIAfJhAXHBoYTrfD7++D0KzkIO8PsIsprfOSvRcyCzkLpB5A/c4PpH7sN9ENbDnLHEixzg+DtIzirShns9MmgVfuE+5DBSjns9kj6Oa+D8d/K73vV/FmFhPvsLkDLkKPvWwl6D2b+afEbWI6Nwb2L/DuRh3MW434b7cB8=
*/