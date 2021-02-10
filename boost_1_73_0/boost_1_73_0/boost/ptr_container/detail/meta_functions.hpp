//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_META_FUNCTIONS
#define BOOST_PTR_CONTAINER_DETAIL_META_FUNCTIONS

#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
namespace ptr_container_detail
{
    template< class T >
    struct select_value_compare
    {
        typedef typename T::value_compare type;
    };

    template< class T >
    struct select_key_compare
    {
        typedef typename T::key_compare type;
    };

    template< class T >
    struct select_hasher
    {
        typedef typename T::hasher type;
    };

    template< class T >
    struct select_key_equal
    {
        typedef typename T::key_equal type;
    };

    template< class T >
    struct select_iterator
    {
        typedef typename T::iterator type;
    };
    
    template< class T >
    struct select_local_iterator
    {
        typedef typename T::local_iterator type;
    };

    template< class T >
    struct select_const_local_iterator
    {
        typedef typename T::const_local_iterator type;
    };
}
}

#endif

/* meta_functions.hpp
NVEGAAAjEAAAJQAJAAAAAAABAAAAAAA+kkQAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC90ZXN0dHJhY2UuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKiGh3rlgIAANIFAAAlAAkAAAAAAAEAAAAAANuYRABjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L3Rlc3R0cmFjZS5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtg1G1XkBQAACQ8AACQACQAAAAAAAQAAAAAAvZtEAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvdGVzdHV0aWwuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK9sNVZ5QIAAJMGAAAkAAkAAAAAAAEAAAAAAOyhRABjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L3Rlc3R1dGlsLmhVVAUAAbZIJGBQSwECFwMKAAAACAAtZ0pSDD3gjvwJAAAsHwAAIQAJAAAAAAABAAAA7YEcpUQAY3VybC1tYXN0ZXIvdGVzdHMvbWFucGFnZS1zY2FuLnBsVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUv8LunNiAwAAUQcAACMACQAAAAAAAQAAAAAAYK9EAGN1cmwtbWFzdGVy
*/