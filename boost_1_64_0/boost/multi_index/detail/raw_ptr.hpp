/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RAW_PTR_HPP
#define BOOST_MULTI_INDEX_DETAIL_RAW_PTR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* gets the underlying pointer of a pointer-like value */

template<typename RawPointer>
inline RawPointer raw_ptr(RawPointer const& p,mpl::true_)
{
  return p;
}

template<typename RawPointer,typename Pointer>
inline RawPointer raw_ptr(Pointer const& p,mpl::false_)
{
  return p==Pointer(0)?0:&*p;
}

template<typename RawPointer,typename Pointer>
inline RawPointer raw_ptr(Pointer const& p)
{
  return raw_ptr<RawPointer>(p,is_same<RawPointer,Pointer>());
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* raw_ptr.hpp
eY8VtYXcsvVYIF9OCdiDyegcVPl3sAIuFAHKudV+FrIQYi5iOAe9mvaDlVJ9Frijp7c1sGYKCwfYFKi5QNpZSDdoA9W4/sk114HfoAFLrgVxhzA3WouvP2b8vSJAsYfcGF4OHFTnHDxU69UFAa9RS7AFvD/AOgGdA3thPlbgjSxfbQO1LaQe6B/L9f+oxp+Qh78RK6kL40GtwPwYXX++KYY5NRTlK2ukmhZyDmxAHNf/jrajrxIaJrBFhlyiWlMoQd17z+b/IaZFUsuX+pNqFpkTqQYz5kRqzJIZ2EAKfsZSxHwwVfXDTImkCFBtwPdM5kSqyYw5kS5jFYF95wjgawE6B2gpkWTx5n3no0zmRIpnxpxITdhmCvE3Aa7CoD/a0kgWb3r/5UzmRKrFjDmRLmctA3c2UYjVwtcfMSWSIkBdG33ByF4YB2pznZ8dk3SvQJuyQPxxBtxXthnzviabb2RBlvg3fYTNiTQhuKgU/f5KJv0ldRR/SSJLM/lL9mP6Swy1xPOZmISYfUfbmTybo93p/kC/t54QaDOWEQcRmrGiXaQ8F552gc6DeU9hG5PnE+txDtaNP79coM3ZVPAdkQjBQfLz+Bx4s3IDTdeJtLdwMUmXmL+hBUsCBoo4Vwna/Gn5J+h9RK+px+1zIgVwXlzWJfLS8m+8FIWVFzyP20VFmcfYbUze39GQGe/vaCX9rx6LuA9w+jTUPlTQPq0ofbgNjQylfGlHt+g2pBEznnG+gpWAv6VbhNA//gV8/X2ePKRTrooANU5hs94GEpQ2cCVrE8gDBRxMDgcHTqRQDVP5cp69iUkffGOu/xVbHl0KqwsWyKM31SLGEfIivv4etMWmIkAdS9cz6W+4jHMw9sOfjgv0KpYYpecCa6T1h5Wo9rGqii53AW4jAAFKnPNKJnOVN+EcTH8/5SOBtmae2EC8jhgjGq7C54B7xbAWHIoEZV92BSOZwMHlnIP3U6YUCy2vZlMCZ36hLxSFoS84C7KR9mIUAeqZt6WMNAcOmnIO2rYf/qFA27DUKOAgUvSF3NX47SDTmVNQiBSzo4pQeSCL9bExURkb27KZAR9shLgrvSFmTmKopM2V40ZbbJkkyPi1uYz0BD9kM85BK/eyg0LLdmwOcJAYLWzC0jXYbcHP/00v9GNOkaQI055Msd4Wmitt4Rrm7wh7ErXE2js+EnXtHaikfySSS14RYY5XeI2RhsBDC87Drsn5zSGym1XAfLk4gpCm2mclYk4IvZK+LLTFpiJCzR06RedB88XdtHpyL4G2Z+drgS+mJsc12xAeHjxYyREUEea58yP63LkV52Hm6I+vF2gHlhQDY4WVEI0S65fYNrKqkgWOEdg8CBGKr3q0zsMVCg8dWeCGj8pIcX927/DYh2wvUrCzIsLcL3IYqQv7NldqsSxt+4GPshMrrgHryTgxf6pAnz9plcTbt1BEmMcLfmAyD9pDEufBF7M+WaCdWRnsX1rri34xJDz9wu5A50GIUNpDCiPfwPzhKs7DoSO/uwTahc0J+J1gPp37Enp7wPYvgADT2rI7I3fBPlZr/pnye+sMgXaVZwZJBOQQWYW4ly2qiL2+BgEqB4nXM/I29Ieruc4vu647F7jt6DBwYOUcNNG8DtMQc7FDFTOdfqzD5GYJ+l5WN0Z6AwdtuM7bVq2BaOdrWd1AjFuk8DOVo/cFTzfshgASVA6uYcQCcX5tOQe7y3/qLLS8jk2R+3mCgyHT0TnonO7j/48VAa/KUHNrJOnzhXaKz/F6Vgrzhc3AQ1k4ePBkOoYjRbqpIlS7UNxS5+EahYfubHOE2id6zwgPD+gsmPe4+UKqI3CQrO1llm2dKNAbWBpwMBk=
*/