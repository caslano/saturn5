///////////////////////////////////////////////////////////////////////////////
// accumulator_concept.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005

#include <boost/concept_check.hpp>

namespace boost { namespace accumulators
{

template<typename Stat>
struct accumulator_concept
{
    void constraints()
    {
        // TODO: define the stat concept
    }

    Stat stat;
};

}} // namespace boost::accumulators

#endif

/* accumulator_concept.hpp
sTexxXKHJ809dgGQyKfL8MDGVZKvl73+UR9pgPlMvNj6Hz0XuQUu0sSe2yB7GXxVSxvhtLZc2r6Wwy3SFRxOjlY2Ht9aQ1vToMScbj6sI6UX8URUPClYQ5LRIuVbTPAzB40WB/NfA7m/qADisUjOscDNKOcI6i1RvaXC/xbAwG6crq1+Cx4p0LFzR/rI8udsSw7E4bnVOJgBgYaPoKmfwAWyOuWiZE9aem7RnKfP9EWy/63ngrnRFqLh7GargsYrH3z7MCS1m8KdeodLWTyNpR+hz86qn8EHLj+i5yrntBDV1xZ//E0g9m+ubLOb8YODc5aSoY42O+FpaU6qVJ/IHoDckTknsPaiFjlBXJrI8Q9Pjocx7PpUP5ARtB6TC6vzkPaXCr18YPgXkKUwXzY1hl8h8Sd2m1ySL4ZT1LDYBwA4DlKJfYBReqGGYKFxeUalShrixsrE7W6zYOTFuz7QcxU7zYPiJr2HcUQ80DBYkOk95THKzozWfMuv8WDNNEvyjOBME3RnsmhTlpXJl1sPZTnT6u8VbZzvLqA3gsYJkk6258DApVhD3fw/h+FaSG7Vc4YfoZBf6WzLLCnLhlrbg/acXGiyScai2hV5J6aVp1kSG5ZZfgXY62toDAXlqUaPkSr2BojQh2kAc3SSocPmTFu2HPN3tQEOfsGkF+IT9ULoDwlC8zV6IXmMXtgL4X274uk3kB5LhA/uzdYP
*/