
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_DATA_H
#define BOOST_COROUTINES_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/coroutine_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct data_t
{
    coroutine_context   *   from;
    void                *   data;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_DATA_H

/* data.hpp
v7RlIFEILD/Sm334itr5R4M1VR9w/R8p6o29BPFmQ283W+kDwX6nTirWg15fmw+OQXbE5K1OdAVwPO2KYHfFwhGmy2W3/QLHg5d9f1P+cDoxjjH8g2RxtuaiXreZHiaWckrKptq9+stycmY4dL+4/sS99id+vLBGFIdaSvR8POyMZ33TlmfmxfNZAF/cydyzZlThzJYmcC8Jb4C1VOwFJpuqEjVit/8H7cF5cBOEd0ESmv7URqjtFr4XeR64kyjEEXU9gwMJQQ91gkU54MmQk8T+radneHfC+htQSwMECgAAAAgALWdKUnQO8IAsBQAAGAsAAC8ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0RPSF9VUkwuM1VUBQABtkgkYK1WXW/bNhR956+48B6WFI7crsBWtF0xNVEXr45lWHI6AwYEWqIibjKpiZQdb91/372k7CxJ0fahCmxJ9P3iuedcJlgN4Mk3u1hA4eCLV+Y+GV54PzjNWv2HyO2nHbLsI/g/dFzh/StSjeDO62N2Cl/l9RFOnFfW53pNz1n2FelWVCR9jch5ldEjrnjP3v9cN/tW3lQWTs5P4Yenz14M4YIrKWpIrFBr0d4M4XXhVn6p+O1tYMSbIQgLvA7u
*/