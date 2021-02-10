// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_H
#define BOOST_MSM_COMMON_H

namespace boost { namespace msm
{
// wrapper for mpl::for_each as showed in the C++ Template Metaprogramming ch. 9
template <class T>
struct wrap{};

// tag to use in grammars where states are seen (init_<<, states_<<...)
struct state_tag{};

} } // boost::msm
#endif //BOOST_MSM_COMMON_H


/* common.hpp
zpfCRhq8EQ24MY2yG+B3zzqLUSurStVFEJ/eBbqwwN8ugEuR5IHLeBKcPWTs+QG/UEsDBAoAAAAIAC1nSlIprFOjhwEAAMsCAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTNVVAUAAbZIJGB9kmFLwzAQhr8H+h+Oyb4INYqCWEJhijgR3HDV7zG92mCXlCTb7L/32myrMBBK27ve+/a5u4iAPijpMWdCm8rS4xu7nXWlz9m8KJbDDZ4ei/jSOvvTMcHHIsGj7oydwQrdFl3qdYlMOGybjr6XMsjoxa8uruDm8hZeEUsfvUBuQo0maCWDtoZFiwx6rtQPAa/kN4LfedVYj9Chp4ste3U6G9WYwb30WsHE1tA2SE1N2IM1BlXvnMEgZ+xTmy+ijliC7zEH/odGk9meXw0BlUSKnNUhtCQ4hCCMXGN+HBDsdKihkrrB8k9vVMdjIQhl12tpymiVcT6dL1bF8zKb9h7LxVvB764h/YGTPP32qBUVyrBxSLM/bGPMUN0ee2joA52uOuh7BVkFdEDjGmYLtfTwiWhg4msbJkxsh1qyINdglW1y1nf1H+phqQmbWx+yU+6EvdO40tkXIdECNq7h04/Ht9Xz4jVhM6WwpfQ5P0/26/y7rhfENp01
*/