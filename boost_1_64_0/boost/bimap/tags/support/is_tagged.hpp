// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/is_tagged.hpp
/// \brief type_traits extension

#ifndef BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::is_tagged
\brief Type trait to check if a type is tagged.

\code
template< class Type >
struct is_tagged
{
    typedef {mpl::true_/mpl::false_} type;
};
\endcode

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// is_tagged metafunction

template< class Type >
struct is_tagged :
    ::boost::mpl::false_ {};

template< class Type, class Tag >
struct is_tagged< tagged< Type, Tag > > :
    ::boost::mpl::true_ {};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP


/* is_tagged.hpp
9/wEuDADDwNhbN1k0P9otZ+gVm7J40k/z33I8plvhwQpd9MyNx+dEc3CR1VOfQkMyr1p3D1o9ajzLBolte5hshwrpVKS9zkZu4xKmOunYi0Dweg7ZgQ9kYiLlfqC+A9XHtLCmyPsWgLMUKxxprzE2zIMqFjo0vr/F5Z/nxyj8MODJb0QQWGDS8mb+KwT15Z7t0jjBbrX7gtEQ6SRPQrasqFrUh6iJ2niVYb1DTj3AqOJOCYzdiCKrW55VFRdfE1i9jk9YvmbPtNr7ZLvhizXXiTs1IpulajA2WtpZCW/EGB4i/mE1OO5nTP5zpHf0CiITiU2zsSqdmeUCv9Rcbbcs8Fcdw6TfoUyvjqLcg4yHwL6WWtL4aoLujn+pM/EW2QI/tz0V70wGuPadYfnRyPLFb1boiMtPmVGSDq05RCBBZNn32rRTkOi1y5nnAAObn0fQF79Yj77PA2EJJqN2JLmtJPntj6veDf2Qu8ESJbPOqrjr3ElvD6Hr1e8MkbY2NJG3Ps+/yHrTGvDrN2fhoKiR+ZqkrHr3Wt5eQyY2ztZbQ1w7Uls0JfCn1BuHg==
*/