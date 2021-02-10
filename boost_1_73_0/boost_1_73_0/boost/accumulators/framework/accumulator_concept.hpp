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
nHxWXr7wouqsDIOpysnE9eWcTF3bGRmK/kx8bDykaT8lb8OqVGRtqPmu1WNbFzfI3P3TXi/l4dde1Jny052tCw/LcRGI96G6xuz4+DLyvBrUAnZ4CIPT8lbkb1F3BfamFityN+FwJebWGechvN37rJw91YeXHueNpVvYJ99r4HkTjCrEoA866eMEWy4HeitIgWX7+bRIBkz/kBIAeU3vD08ARx+OO7xH2SS+j3eS+7lniA0Jlw8LWVONA3/wU3m2VX+eH8LUIlE0rn7nThfek/N8RWafVmb1aSGjF7r6p4LTLdEqBZzey/J5KZdPC3n82ReqLKJKXpW0pYPO8Umn3QLsq1aZ52zXQs4W5fc/Ts4oKQsptVLtlAN0EspsYvmGah8zdjIrhfc7nYM8hRdROXZVQOW5DeE87fcVxxXtbnRQU7bFfVZDdAUrtLIJSntb2X5VZHz+MS3PJ5MMD2B36lUjWcuGtpJoeIDZii6oIqO16v5W2VRd1U5d3Uhd1UJ9tHlKHQ6Hvc/L404cT1fgcxxQNV5fYqGmfRfxOxR+4fnPxfPpCDldW8SAVT7wJasmI3AB82JiSHJiNTVXkUNlUSBqryQOqM3KIgEYYlWxYPDcQ0XDZ5cMqwmGp5QLZWLhry0VPq+N8O8QICXy
*/