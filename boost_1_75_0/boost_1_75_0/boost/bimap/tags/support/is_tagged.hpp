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
pmhhOmPWjkmEWdMlZn0bMet7lYhZIbV2qUkr6Ld3ziPU+v1gRq3J7ZtArZnBqDXTgFrD2utRa6YBtWY2g1o7ch+g8cwkwq0Bxq3ZNU3h1u7N4VbEX02h17Afz49eF1cAeg3YCntEUCRh+0yRUiw4ddG0PH2MDNizKkAUXku8qr9E+3ArfShhJhbt3lu72DxeXr3OVFMzdakT1dSJjS57z7CxLStf9n7URpqRePBK2dQ5L/cqYH/uZjju3R5wJm3hE9+wT9C/4scCy1Xa1pVH4pHvdtvILcDi9w1XETtq2hhwdWFpq9uKhEGYw1b4Ck2APDwPD9hv2UbihG6yrt9m1Rh7/WRdsk1j/NXJYkOmoMni6BhBkwWpjSfrojY0OXKy2uH7pmizHFO0VB6CcRxa9f4VJSDuDq2DAfuuSoRf2LoB8GlYEeLyvUJoCDuMZPAdOI4f5CiyFayKgqSDtoIXo/gcczR52S9R0mcj7vCUJGwnTblEea2HIsqDu9wl08LJI8eR2YDvPCWAK3vcZGWk9w3AxWmylS280mLY3wn7vMsQ7S1jtHd6vx7tzZzKt8S3e40orM9GQmEKo7BlW6HYWAhHdBOVqVEWBpX5+0MqU8Nl7qcyNdj1nXPYS49jMSoPqcjHWEQFsKu2No3oTt0E2qG9CbsB101weheiSyOMByHywYvuJkrR721wbA8Aevb5G3DB7AKFJuyGPTwA
*/