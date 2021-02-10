// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/overwrite_tagged.hpp
/// \brief Hard tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::overwrite_tagged
\brief Hard tagging metafunction

\code
template< class Type, class Tag >
struct overwrite_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
passed tag. If it is tagged it returns a new tagged type with the tag replaced
by the one passed as a parameter.

See also tagged, default_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Change the tag

template< class Type, class NewTag >
struct overwrite_tagged
{
    typedef tagged<Type,NewTag> type;
};

template< class Type, class OldTag, class NewTag >
struct overwrite_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,NewTag> type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP



/* overwrite_tagged.hpp
StODK5UmtElGMWnDFr6bTddsUDaG04Zl7E6Dfr8/3AlUTqLTEHliRQLE1Imi7PlZ9NPkatZ5Sn6DYXPFxnC4ZOMJvOJ8suj4U/stQIRZfsu2GuKMx+8JCjoG/k/pw5OkHY9OAATGQ1O7UD7il+eaf0ZuH+BHsoyesYKx3SN7FDdYftrmsqjW2AyJeVqsCpbnWEAua7YGjgYUGRC8CFdtoYOAB84RPIdBHZT36Y+LT7OxATh/LkUYDKVrzUTR2UiRuJyPf7h6C8+IMkMX6/eiEGuGvYjYRZ0OtX+ruDYunBjbi0EMGQLnN06h/WqywEy/Xiwue4Nu/0bdFK+lNse+vrqxXNMifdvkSIvfeWS86SjnBR3SKHzp1Isun1QZsOIFV8jIQhpXqsw2a8C2wY8xddTrv8Z2VGmss4c1K5XN08MKxw5IrYavOQJDwRPwESu2EUjbk0oljYxljgNoSdrOjq7KUipMU7vAGtzwfNsOfQiJpBCwFd8qKjHqIY1BpI0suy1nxXZS33+wKnQdQZFvKTDUuAX6urHhRtXo8iIk44lEcUTDx7NaUR5cv1DCCOsZWIltNGYWKheXNUINHKepWNquXvOfTocp2EOENEDGDl1p0LIvC2JMLBPuWLXD9V7DcTt1mnF0F7glDSMf
*/