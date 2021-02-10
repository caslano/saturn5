/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0940)
#define BOOST_FUSION_CLEAR_10172012_0940

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/std_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail
{
  template <typename Tag>
  struct clear;

  template <>
  struct clear<std_tuple_tag> : mpl::identity<std::tuple<> > {};

}}}

#endif

/* clear.hpp
CxuXClTDog5MrEUdaxhd9W69jmVhE6Lj0HotdIIrXvIWtdxg70llurdHibeFHgPkThnh3+A0mfTdjSgqUk10LghvDWkb9WdekmmGS75aoYMJhGrFf50DYdjd41a42mzdEGbGiK7iLIttSC/1dxzFxzYEl16M86tENQaxoRUpRdc8jELfOuXsZ8xKKbJ66HgN/MQ6S+ZWJu4fVWDreksyDCrGxapogetOWFNJnrhPozBLopmVoJiQ4C1CS86U4K2+MzyGUJG6iWocY7DG3tJ7oZH8jRbyMy+Y+ae4NU/CeLOnIfTWaCZ7Rsvif6IbmZ15V7PM2mVOv4uTKIum0Sy1vkm7sfE/eZfxDO1ZbQ0SN4r7/asGoIyqPVQ1rff04j78Y8HT/tALX/VFgjswqVWH053cFThxiINVuhUVrpl8qLYJYiKSe2B6WHOid3dLznrIbeg4cJ8RdtOO26Q/BIqJQOBhim8Gxw5uN5gMpb6x/rWcmhqmvGtk3nsfzIJsbnlVNZyer52jI+fQGYb3MLBgjZL7zPiaae1tUsMtMCOr77SO0e0X55U5aaxRZNiQTElYEyRiyxs9dR0HJovEz66SEK692ZWPWlJ48AxWfh5dAB1GypiHPk76ruMCD5DhUBulFF6E0ccwj8x00k6M
*/