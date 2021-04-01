// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/apply_to_value_type.hpp
/// \brief Similar to mpl::apply but for tagged types.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/mpl/apply.hpp>

/** \struct boost::bimaps::tags::support::apply_to_value_type
\brief Higger order metafunction similar to mpl::apply but for tagged types.

\code
template< class Metafunction, class TaggedType >
struct apply_to_value_type
{
    typedef tagged
    <
        Metafuntion< value_type_of< TaggedType >::type >::type,
        tag_of< TaggedType >::type

    > type;
};
\endcode

This higher order metafunctions is very useful, and it can be used with lambda
expresions.

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {

template < class F, class TaggedType >
struct apply_to_value_type;

template < class F, class ValueType, class Tag >
struct apply_to_value_type<F, tagged<ValueType,Tag> >
{
    typedef BOOST_DEDUCED_TYPENAME mpl::apply< F, ValueType >::type new_value_type;
    typedef tagged< new_value_type, Tag > type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

/* apply_to_value_type.hpp
Uk4Wfh4gkbN3/yJB8nev1lPiDKr9cFrmg0edmg8i3v/LqCfGX4WQXZu9SBW4xaS+g8pfpPwQpLXO5srubgSnlUSk/A9yz3Rm81IvRoYKA8Yy831xnv+Xw4+f24nN8ZJRjnRjIHyVcDgYTef7N7+B/HrlTl078nBCirfwDul91BojyDyLomOrbV8vN6w/aRagJbYO8zJlmFVCLtRHKq847j75o8U5bRbF9BQHHOAvgulzj+8/fw7Pycb5ZQduxWclGqqanOjpXz3NAjSkFrecAlKOMuBkvFVW0AGzOzKI+hLBxXVt8wMCAWSpveEeptRkWvfeE2p+EkpFOjigdx286d9brHr+7sBoL1dxDrWzjEssAW2YZwQUbdvdulrwykOZANv6ChoLmo97ikO120QNYuDecyrXRF3pATlx0ZdF2KUemPDIA6UoSH1MRSkRBy4FHTzMK0cKosUpraYCzm3gF6iz/7/Vo0wiJWtpN1mZXCj+CsslaI6UdShGO7xBnYkTbkMvAjH8bmbOCgtOgywiUk7KruWa/wNyXvGl4nqtYNmRvnyF7wspSD1czQ==
*/