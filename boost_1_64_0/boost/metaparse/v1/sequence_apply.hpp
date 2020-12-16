#ifndef BOOST_METAPARSE_V1_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_V1_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/letter.hpp>
#include <boost/metaparse/v1/sequence.hpp>

#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/at.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
#ifdef BOOST_METAPARSE_SEQUENCE_APPLY_ARG
#  error BOOST_METAPARSE_SEQUENCE_APPLY_ARG already defined
#endif
#define BOOST_METAPARSE_SEQUENCE_APPLY_ARG(z, n, container) \
  typename boost::mpl::at_c<container, n>::type

#ifdef BOOST_METAPARSE_SEQUENCE_APPLY
#  error BOOST_METAPARSE_SEQUENCE_APPLY already defined
#endif
#define BOOST_METAPARSE_SEQUENCE_APPLY(z, n, unused) \
  namespace impl \
  { \
  template < \
    template <BOOST_PP_ENUM(n, class BOOST_PP_TUPLE_EAT(3), ~)> class T \
  > \
  struct BOOST_PP_CAT(sequence_apply_transform, n) \
  { \
    typedef BOOST_PP_CAT(sequence_apply_transform, n) type; \
    \
    template <class V> \
    struct apply \
    { \
      typedef T<BOOST_PP_ENUM(n, BOOST_METAPARSE_SEQUENCE_APPLY_ARG, V)> type; \
    }; \
  }; \
  } \
  \
  template < \
    template <BOOST_PP_ENUM(n, class BOOST_PP_TUPLE_EAT(3), ~)> class T, \
    BOOST_PP_ENUM_PARAMS(n, class P) \
  > \
  struct BOOST_PP_CAT(sequence_apply, n) : \
    transform< \
      sequence<BOOST_PP_ENUM_PARAMS(n, P)>, \
      BOOST_PP_CAT(impl::sequence_apply_transform, n)<T> \
    > \
  {};

      BOOST_PP_REPEAT_FROM_TO(
        1,
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_SEQUENCE_APPLY,
        ~
      )

#undef BOOST_METAPARSE_SEQUENCE_APPLY
#undef BOOST_METAPARSE_SEQUENCE_APPLY_ARG
    }
  }
}

#endif


/* sequence_apply.hpp
MH9TMXVrNdyuUd5j2wWMv7d9wGVhA7psUIf2FrTtWf8RdUwzjIXLa9vbo3iSeOfC7u1sRWVDGwQu8AhfvImRCLau03GX7JsZ29RJujZNY5WIz3sT6pgj1ui3I8bbdqIeyiMcTXd70F03OkyvnizeDYmVkeZqrEOCx+NU1LHOEIMTfBoeSWc7MK6N2cnvoQC3EvzeEBMv1OXtNVq39wQhv6Nh47lPZFmofLyv3MnQuMHQ2NnoeJqBTzZtN2c01jLmfZl4XY4MalHewTC2IR3S64PtzOF4gGqf7NpqyAj+nc1bGRvr7BstlhfE660D78DbfzTwsI56a4zmfXpd6Dsdjo05PLOO7cDJtQu3BeBMj+rxfO5ax2cCdP34oR01H6OC3djGbDngch/eo07vzdkYs5+CTIdU6m8905Ttar3NNTZygaG5N/fD2Di4lK/wWwW952PgbQz3/GQT5nwrwdGvVLzg68XbRYvqTBwLY8eLuQ6Csa3MRnsurdN908ZPXS7gt8X0mxWoj3SKfqR9k8NbaGLIriYc8Atfx/weaNrA7m8fjPpOlzoBLcpT3z0+A9yzGNenzzDp80z6nHI95/3PGN0vOuqGxxLuFHLvhncU7DmItOi/v9wp/7nLtawD379sm3SH+it7TtjBkcYOeowd9EY0AaN8Nab0A383+4aVOFfucO2+/aDwNRVVYXs2jHH+K/4sRRa8j6li3o82vK83vG+IeEcd9nzsMQZu123HwRd8tlLPJU+oY//CvpruDJmxhMopep/ndiQYn4G3ujnZjAnvyfeXkQYvpNv4e+BfZJ/ox5/F4+X7XNonfqlOv3H1x530N6xDMCbdA/jKyVrOo41/OgP0KN+X//dOjO/y/lWu5Tk76gOAOzpPAOcJfGs6V+mO53ZWd181bWDj+H/d+E6yOXwjwt4hz0EwnodroP5P8rv6czCHD9unfyjL7/4SB30UtKm9o7s/cHm+D4wKOijeXFdqcGOQ+w59UZ38Du1eE3Rvyre1LGmn7Y1o4Wizsb6O7P0c47e+JfzjeQZ2qYA9a2Dfhswu3/rGMwzudwWdewzs+6BzTwydswzuD3l+YPwG7BRjwElVun2vjhnrMc4Dl+36GmFXb0/U35xvh11diz5OulR9/Lo6hU9wxKQA/nkG/0aDfx7wbwL+swb/FoP/LPBvBf4ZBv92jU9wvFUF/HsM/h0an+CI4wv8daNNHF+NT3DE8QX+6Yb+LzQ+wRHHF/jTDP59Gp/giOML/LMM/v0G/yzg/8aM8/Yb/28F/JwY+IMCfl4M/GEBfzYG/qiAnxED/72A3xMDf8LMPy38jwJ+ekz5Pxn/ZuFPC/hZMfBnzdgybUfonPsT9SU9rr1Qp/fLfmdioF+T943h5fu1rpwxs31ly4K2eS05t6ZzeS/sb3U8tv+9jvfsXqwzd5vr3M/E/oUd/cvj4n0r/A16aq7wMsr/uw4ftFD+VYNHcOW3XgfeG8BrKiC3kdfJCR+HuOU8R0LsEbxTVKfjvgzuyLIiLpK6A59VsUdx9rDO7hMOfwfiA8jyltBTkBy+litJ+nIEC/kZkdTfwCw8kdTlKV+11UhT3sJHJfPtzw8c2ZkhTXakcleSOYe/vW8LGRYVjjWmzdBTywMD3dKkjmn6cS8vVY3xv7XSpekjr8vCnt7WO/o61yHX522X9HmpNdizD+dd/dl16UEfY4fGtpGfIJxEETF2ZoOXWeX6btX2vvzRqZ6hcC/RzatGBalsdrC7g3jLvS9clhTzkC3or4ep94U37Dp9D/+Y2ysmz92NEnn9ndl0NuB0pivTzeXi9DC6SD1MyqOHMUIP0Z5thZB5VBE2Jf3E7juy37BzHGo=
*/