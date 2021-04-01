// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_type_by.hpp
/// \brief pair_type_by<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::pair_type_by

\brief Metafunction to obtain the view type indexed by one of the sides.

\code

template< class Tag, class Relation >
struct pair_type_by
{
        typedef {signature-compatible with std::pair} type;
};

\endcode

See also member_at, pair_by().
\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Implementation of pair type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    pair_type_by,
    left_pair,
    right_pair
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_TYPE_HPP


/* pair_type_by.hpp
fftFuk2Lx2sMYKb0TqXSb7geMGRmIqqZjkZnqmfWNXx1FckRfUlPpw089o2Tb69zcRw0ODLL/Ptwwe9m0sawAuQZxmwJYDN6kSpeFG1FI5PJ8KwzJ4OrHYFh8Boj1dYcJ9cpTA4Juq6MgN5Ep+R0tZTXXM38UR117jEqodtUks9NQPufg8SUiASToPcPFXSLE+sbiu6NEXegd0y45+QS9nGbRPEDDQeAWh2aWvAw7Ib4F8MUzAXCD31loRu8I+QO4yKvl4hSOw0o/n1pFDpRFam+BVg3Xw3jd0FpsmSeYdkjjZABzhaB1QnRmc489VkSzrdDUPEUiHd3aBVyudSDOgm9LD0CxQQS7k20sTl2brpaUPnL50ACp4vQPSjxuifbwR8OAMons8RxwA65pbBJYJCAegiS2kvmoKJO9YGNlsZy+o0LNaUMnwMdCX94NnJcwLyk9GqJqAziPmYY/eACZSWMFPeP1UnpKmRb/w+P+wK8EiNP6G2+Qru3OG+YinIp3KwLXjUXwW4lRURe86T4S65xBiGyJyUfMufXH+Fgqrohsi59Bka/ZvZl1A==
*/