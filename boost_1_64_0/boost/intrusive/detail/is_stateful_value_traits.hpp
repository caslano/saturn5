/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2009-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1310)

#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct is_stateful_value_traits
{
   static const bool value = !detail::is_empty<ValueTraits>::value;
};

}}}

#else

#include <boost/intrusive/detail/function_detector.hpp>

BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(to_node_ptr, boost_intrusive)
BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(to_value_ptr, boost_intrusive)

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct is_stateful_value_traits
{
   typedef typename ValueTraits::node_ptr       node_ptr;
   typedef typename ValueTraits::pointer        pointer;
   typedef typename ValueTraits::value_type     value_type;
   typedef typename ValueTraits::const_node_ptr const_node_ptr;
   typedef typename ValueTraits::const_pointer  const_pointer;

   typedef ValueTraits value_traits;

   static const bool value =
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, node_ptr, to_node_ptr, (value_type&) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, pointer, to_value_ptr, (node_ptr) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, const_node_ptr, to_node_ptr, (const value_type&) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, const_pointer, to_value_ptr, (const_node_ptr) )))
      ;
};

}}}

#endif

#endif   //@ifndef BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP

/* is_stateful_value_traits.hpp
HZX7tg7KvWo/y+3PxQ2L14X5lHtjVLl15XTTkvqqJHV14wEq37XD4+3a91G+1kj5VE+lmLIDToMxP6w6bLTrVkmXkfCdrDXJckfNCWs+sbo8YYS97LssZWcgYCsMCs+vvfK/3EH5dx2A8mvbY6y3lh8FsZTfcyPtoO1D89stO3L3v+ynRfTaUvb7vWegrez6aedbb+var0dRB/UoPAD18PV/VHw9NnjPSks9ZPfjDvpgQgdlLzmAZS85zF722bayywrm9ste2UHZZx/Ish8eTpCvCfOgByh7S2zZGxOPO+bcyrWSLsdabmT6cxOj5TmrAhPZGveznpH5BfIiXvOKHbuOsNd/XVz9Ox67Im2wvp02WBfXBr5Q+37tB7QNNK8YHZhQbG+DVksbJBz/zHnbdurfGld/FWitP/wHtP6aV8wYOv/I+Po/CP+uuPonP4ZG2uLlxG2BfK0b6U+QtrAIt7YLafezXQZru5Av8fZ8TR2Zf1R8G32DtE61pY10fG6vXULVidsFmb6OHCvtogLtbQH//rVFREfIi3jNK7b+R9vrX2ipv47x7da/qJ36F8bVXwVa6w//Aa2/n1fUfOg2rX+m8S07Cf4Sv/7ss2N8Wz+fxJyw+a1WdEz4wtchF3oA2oj8UlN+tG8E3+3xbdsL3CRp0u3fltpW+q3n++z31fm0crl+p8ynnQ3dDonPPfW/bTRzRQgKLsBlPyPdnEeQea/BhLupD1ALRKa+/bCyt4fJzze0huvQ4VxvpE+RGfuM9/fpXHxsOEE5hc0CZ4Oyb+Ilkbbl/q+oamx0Es9njxHeWa6lTZETPT/JDenbZN+Ua43OGU6Bvw/cYolb6FxEKedBtVDs3lkDlPc84T3WTcGHqQVtvwGPu1tA9X3g19iEaxfhsE33ROE/x/XmMYehU6VjdK4zOD4rLSUreFhWWigyP8mcJ6Tz7MrfNEbnNdMvjJvXHKA8G3yZLY9nZSD0WITC157cZ325Lb825Zpz/L9Ufbk9Ozn78nEL2rEvq8/cadIe7GWj+82s1fAmDT8Vc73Pgujr4wjr9aj3pv7Hxe8ZtBme3QsiOtVonXvrEXXfJvDPX5DceJYTp/vRY8rY440yKj4Br1Pjl7FT829OTfLzbwav+r+VN8yzrkvxeX19m3WA5urUjqb+aeQfM+YOOyF+TN+CvOy29un0/Fg4rRvbz/64ViDXg7Y2I23n+t3iX5RQF5aP1T1paOBDwCfAZngLzbrqvJWtrgMi44vwb3Bv5I7cwCzYD6Ez3N7253iNZe8pY2w7Xa6vca8i1R2Mj5ugsW6e/RlfE2vX1bLadQr+2DGZ/ct0TB4n13qJrCcH6f5+c6oaIr7IL+J/G3vN9EXO8MfeemeAPh9KROZX3c8hdx27Fj4FTXBzfb/k27I90vFNcbD6JRfth1+yZZ8t4/yduH3wpG7Ui3its+FzbMZHfI7vr4neV26TH9bxUPctKz3JP2dGrg+M7FldK/pVXlNTV1Hub10GlFcsSPaeQoZvv1uJHhecFFkjmBm3RjDufSGJ/Ymj9oQ9OcxcqfWogK7kyrpwPTyjd7u2qT7gvcJ7sf37V+uiZ3MZflXJ+6kmnKPWOrSM8/d9kTpk8c+N3r1eJ3WY530DlteU+X1i8yc0ff0fk3Tn4wuQaqsTcju3ZqawrvNrF0mTyIfQH5sOFZ5ubiH/ng5th9i8yOaHgrz2fQr76lhxpvDtcgpp4ft49/oNaPNTUXmk02ejtoG4SZTPqbH7q2g6HSNPlraXyXebr4pZZs3DsC2p/EIjTaGk6dhHp8hIU2SkSbSmeFC9dz1F9YN4L0wJexOX4a8FbnTydZx/VuRdwHOnm3MuGmM=
*/