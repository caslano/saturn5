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
CP6w6vj1fX7ts9BrBc29VhB67UvxGrrSuFbbyCWnioMGYFRVZTXwW1ncHlkjiZNvQWQTJx80N0E0dw00l97jbMdok73EQgcs2tqIRoGv2s7nXicREyof/5Hw0JO0Qw9jJBV0EynlErT4ch4iHQKO8z9b9KRykvG4U+1lVXROz8yVMnoVxUqyXXUc+AYPl1505NMBuAvRWDVGYJsVsaZ0jTf2iVNmQN320ufx3Ywx+XDWyEOAUniX3hyTr78auD1fzc2T62/A+t5E+Qw/QUKs0qwNht1aP+dQHuQDE6zN0aZ1Fkl+r29yWjUVcWip1o3XlypmIc/tGTOPDyM84QsXeydoDjzDMYDinKQniW6xwL7Jgg2pT8PuzTQNHrmzR94qIkFwepotLvXWYl+92dshZHeyVYnbCh2/AIeAEVKC8cZnx7bgbhdDmovxIV50NjmkuZaGQzo9Rx/Ste9FiWx9aMPiCUzJx0HhKxd7720wqOeJYrpsC4KEO6NnUawbM9lYYUxuf08YU468JQuDAYSNSa7XRzXXwh4z127RRoXJBnlU2rNuW5gpIXT15iZBSOQpU7fB4RyMStuLViIhskWTXlGECd7+6PlcsY6k7JPYSAPxIuLwf/Uje6PyKM1//s5K5T04/pQ38Z/X8J/5+M88pgeUJUgPbFUWfwll6nIqq4efucojXKFqCf2U889yrK7cwcQD0w4xn/2XaYdT
*/