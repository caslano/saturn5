// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/tag_of.hpp
/// \brief Safe way to acces the tag of a type

#ifndef BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>

/** \struct boost::bimaps::tags::support::tag_of
\brief Metafunction to obtain the tag of a type.

\code
template< class TaggedType >
struct tag_of
{
    typedef {Tag} type;
};
\endcode

If the type is not tagged you will get a compile timer error with the following message:

\verbatim
USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, TaggedType
\endverbatim

See also tagged, value_type_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// tag_of metafunction

template< class Type >
struct tag_of
{
    BOOST_BIMAP_STATIC_ERROR( USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, (Type) );
};

template< class Type, class Tag >
struct tag_of< tagged< Type, Tag > >
{
    typedef Tag type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP


/* tag_of.hpp
rsIP04G4uMYVWvuzy0WEjxDaftY2iNQOnHGkxpkkFGiM2eGlWKFTTNuRQxG5WtA1CxHMpCfwo37Hs+l0Ml5Es+nb6xAGb2tvrg73ujhqsWGsHTT1iRApEvvq1BqbRLM3HjRAKmH1pZ32hJrOMTzRWAlhMxajbD8iC0Htc1fAA/f3x5Y/+OQOD0tH2w0FSFU98G0qM2Qe8uoIbvnXOVYOp/uSnQB2XNA88njcP9mK43YqG7BcTM9n0Wi8uPhxMp+N30wW2GFcmv/hk3tTc6xf4nPdKrpo0UeCXPCOEad3DG87xer4sNqwrFeKre3NLJeyxDmW8JQYj7XcrbXpgkCSSWWn8dFvFXZFs90rV0gpq4Y3NT/xbMHzO2FcqZHxvTlGNye6I7kB4FUyRpGVQuGNx+fksHQ8Jo2zgdtx5eSX7mfStjmXRt+rnzeLMdxpOu19Mz46EIOn9q9geOi8rujnpz7K3XZNh1NPh9Gr0cUUnj6Fr+7dVfzQxB8J3+Ds778NgsYRH3CnhqzOdzP0JlkcYeon/SDI+SfCCXbx/hl5/yp9H8b0sXWvHuaUvydt6zQ6n119P8LmQ++z8/NoAXiB3hqu6az7PLnLnUzTyAQ+J63mOZuJOWmm1At671ec1SWkS5zpvFlD2CU6w2Hw
*/