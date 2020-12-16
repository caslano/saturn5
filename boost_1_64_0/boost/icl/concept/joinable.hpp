/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_JOINABLE_HPP_JOFA_100920

#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

namespace segmental
{
    template<class Type>
    typename enable_if<is_interval_set<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches(*it_, *next_);
    }

    template<class Type>
    typename enable_if<is_interval_map<Type>, bool>::type
    is_joinable(typename Type::iterator it_, typename Type::iterator next_, Type* = 0)
    {
        return touches((*it_).first, (*next_).first)
            && (*it_).second == (*next_).second    ;
    }
}



}} // namespace boost icl

#endif



/* joinable.hpp
LaZMhz2hcuVoFhCoTTe6azApygMV54+zlXo78OZGKgs1nY+wQ8I0R+gnVdMA3V+hR+t/b2QD90RpptIX6lX4S+Gyiszj+nKynbWJLDuu4kymCzn6JpBYRTX/YF5K/4SXw1yoEEKTH5P2s/kkLTEJngEbaa/LcPZC3x9Zyao0wfAKWrcvZo2KifCVl6cfyosQL8oxMUigQ3J/0uo/EvjRfIpSlBwQZ/WXXPX68GvEZd775Sp9jE/hf89H05g7TyhqbgJdvTmF/zq4i+olHZho5VfYXX/Ec4NAL6z3kbH/U0rRPcFtn+hCqUYG/+7dQJZBC/sxrwHlbSPYGUHuHXPMiFblmkPB+zU6w3YiaulqfqtBnjSqVpJzbgDNeujKixeNoHtlnwTMcxXRlgA2cPYbLLf7MEFxG96nb+KomQ0WBpxHWOJ1Mpm/C3pXFTBnvANVn7Gk2nwpnqKmhPqdvnRqnCaKn8fT86OlZLvpPSuoeEzDxxzn9W80aYb9K/7X9hiaGocyl2XDqS5nK3fwmYLsgtd03i8EbYvv03JlHYQdiKfabYwc/L4gcnIGinc/4T1n7GB2VZnlW4bCfvR2unjsHh0pL4Bw4WN8jxrFn/zUQoeLKLdys6a41y+4QlslnvkokXW8M55myrIjkxZS/+m1cBjmRpVKj3jMt5kwzdvLB5uKSEjjNZO3UsDH2bIUnysHc/ccdm3+J1is9eEu757heN5PSsk0IK4whA3EPsVWTzG8cYyhfplsvvZ6IZXoraNiybUYNV6UlRnq086S53Tilx39CHChV65tdHaMBs2qdaMrDzR555hp0IUlmyUtR0eYGe3+7yvl3dBgz6M6UVi4lCTvKcJ4YwST169CT+g3SCga4udJVf7Fazb1HTVj7t5OSOLP2bB2I7JP/sr+Tk2DZ78Z35p+CvqPtJB8KgM2amf4wWmfUfdtGZtovR4QvwXfsZMwUnUxTTD2R/JMDWyNdqaGz200fG0MuR0hwbnqxcBwPVZd+wTlsvok55GMbMsyHP6xgOZlxfOFGeEwNBWH960cuJZY0VjDBfTm2hZB71zgWQ4/48pyQQj/kIs9UqLQHKiib97t9F/yBTZexBQBMvb8R9dCulr9k1nGLaL+bePZ1GQtWsrVUf/1BGIWHuOi2bupSV8ZBT3myA9zYatmrqYxOrf4HjETxOa50Cr1JzSvJguOcYrYuT+bTd4ynZ6YRbGmzu+km6aGhDxTshv5jb1yuUSblEbRwbv7yWSoDE3tcaT1y0ZDq7aXXMML+KWyVDqx1JPNHxChPYemskXbu2j5mhBSWydM0pNvoHTydpz7vh5RFlm4oDmNRx7to8zkWwgVHY/SQzr8je8c2nlAiU5P1qO6KVV8334zkumQ4X54TxdP2rPydc34tjKW57IS8p4gyBiqTbBSwAA+lV3EAzUv9s02H9VJteTQLEnJ4WZc700vKer6kNCZFpKoc+Tthypw18WC/60bgoVeN/h+82rqVn3IK1YtpH1yU9FzQx+3C3YLcoixlLnyCu6q98E5MpWMJo6GvPxzFnjzDj1uPYSNzZNIT+0ipujPRO+ZRfRxThqZNrxmYhdEaHVaF91x+o2RB23Z3Ud/aNOiH7S17D5V2J3HHLnRWDspBGu9VqNoYwS/4DMJeocS+Wd5DXqAKjbjVBfa/o1l6QYjYC+9jnoDsnG3uIatD19N53qVKGK6DTzWC9Z+23KSbU4hLY8curo9i61zKUepWy/3K5Wj0GULmOnqShIZs5P+XY2hwWIH0txkRF/c7fFw9z9SOzaDR9VuoXlsCslFxVCUdTxffmkNPY8Rhd2ALvJ0lMEeiBLtYzT/qixtPhQH++Q4zNs=
*/