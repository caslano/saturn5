// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_STACK_HPP
#define BOOST_ASSIGN_STD_STACK_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <stack>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V,C> >, V >
    operator+=( std::stack<V,C>& c, V2 v )
    {
       return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V, C> >, V >
    operator+=(std::stack<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* stack.hpp
cknZy/wBUEsDBAoAAAAIAC1nSlIZVFezqQAAAPUAAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdHItZW5jb2RpbmcuZFVUBQABtkgkYE3MQQrCMBAF0H1OMQcwBV0oZCciuHBRpBcIybQNxEzMTBRvbxQrLj///3emNBmQojE58iFNau89egO7brPutuqEMRu44K0iCzi65oLM6NvFJh6xwO/YFxJyFNnAaRh6dbCCE5WngVkkK621Whz7Lw1fSR+/ErQiU2KEyu9ICYFGkBnBxiYGma+sXC0RuOZMRXgFNnmoaWE/Y2/FwmMOEZvoMNzfWJBOvQBQSwMECgAAAAgALWdKUvt1vixHAQAAHQIAACsACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy90cmFjZS1hc2NpaS5kVVQFAAG2SCRgVVFbSkMxEP3PKga/e7uAIoKIYEG/1AVMm+nNYB6XzKTV3TtzrYIQCDnzOI88tzrvQDseaUI5Mof7bsDtiTPdhSfKyw6e+YNgmtamDRyGwoU1NbsTfYLdy9DwMpQ+KV53wZn6oQmFB1SaW//a/SHTNIXHiodMAginkfN1JI6yQDsBGsL12ArXGbBGZ5ibPyIqbryWR7R3iCTH
*/