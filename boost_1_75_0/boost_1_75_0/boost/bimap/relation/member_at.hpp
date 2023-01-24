// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/member_at.hpp
/// \brief Defines the tags for the member_at::side idiom

#ifndef BOOST_BIMAP_RELATION_MEMBER_AT_HPP
#define BOOST_BIMAP_RELATION_MEMBER_AT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief member_at::side idiom to access relation values and types using metaprogramming. 
/**

This tags are used to specify which member you want to acces when using a metafunction over
a symmetrical type. The idea is to be able to write code like:

\code
result_of::get<member_at::left,relation>::type data = get<member_at::left>(rel);
\endcode

The relation class supports this idiom even when the elements are tagged. This is useful
because a user can decide to start tagging in any moment of the development.

See also member_with_tag, is_tag_of_member_at_left, is_tag_of_member_at_right, get
value_type_of, pair_by, pair_type_by.

\ingroup relation_group
                                                                                        **/
namespace member_at {

    /// \brief Member at left tag
    /**
    See also member_at, rigth.
                                            **/

    struct left  {};

    /// \brief Member at right tag
    /**
    See also member_at, left.
                                            **/

    struct right {};

    /// \brief Member info tag
    /**
    See also member_at, left, right.
                                            **/

    struct info  {};

}

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_MEMBER_AT_HPP

/* member_at.hpp
tVkNb02etHdy2TQXqwCR7QUK13xLGkptpNRA0fFBzGIbpVZtjYFNKw/eSTUX16/5+jASj3hUZKVHMknjvfC9rv6uVP+xDqL+TztS/YVa/YX16/8FpWdVJI9VCjuo6kddFGFSA1Rw766xqn4uVhV/daC8j5UJOQoVTXiRwFr4opEAwCi2t9wWFAXYqoGrxuUt1n8rDvy2UP9tof6bUDb6bbszSJuZwUf42wxx1SID5RC9nq9cxLoHwWtXmaZ4DxmKj4SvE1EkJB1iTzsbH1Mbel5oTc+/+PMX/jzRGmWtT3j2fZRczJPllCzmyRJeaBl/LuXPJfy5kD+LWxMQhVQ8jyen8uck/nyEP+/nz1H8eRsVG9pajburPwP2jY87xgQ9kl5NL38nFJXWdPm0fW5NGvhxdsnHuf10hkt+fFbSQbQILzdBlLRzklyEWpq536LGOzHNN80I57S9S0B7XOR4zymPtDhTRka7WxSFOb2DLRHVUS4fvK5UXjloZMM3+ojkuzWajj+P+IsL+T5uMnrXHv1p0eiDkpx+hO4dHGRFP6VDS9J/VURo7tfmM7gXS770+X7bgeHkyuxTUnHOx/jxnM4nox/50SvJ5bckZ75E29XCl877iwNfpiofvljvZbJSuYC9RAV24Jd4Jf9l+CKjaptf9elAPVvJo3tD69Uj1W1m0Nd7IiiUOddRa1/R4fhg+NoZNFc21DNmrkQd
*/