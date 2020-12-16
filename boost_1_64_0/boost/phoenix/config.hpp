/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010      Eric Niebler
    Copyright (c) 2014-2015 John Fletcher
    Copyright (c) 2016      Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CONFIG_HPP
#define BOOST_PHOENIX_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//////////////////////////////////////////////////////////////////////////
// This section is to sort out whether hash types or unordered types
// are available. This depends on whether stdlib or libc++ is being used
// and also whether C++11 or C++03 is being used.
//////////////////////////////////////////////////////////////////////////
// The idea is to set up the configuration without including the actual
// headers unless that is unavoidable.
//
// The client code should contain the following to include headers
//
// #ifdef BOOST_PHOENIX_HAS_HASH
// #include BOOST_PHOENIX_HASH_SET_HEADER
// #include BOOST_PHOENIX_HASH_MAP_HEADER
// #endif
//
// #ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
// #include BOOST_PHOENIX_UNORDERED_SET_HEADER
// #include BOOST_PHOENIX_UNORDERED_MAP_HEADER
// #endif
//
// The client code can then chose the implementation provided.
// See the example in test/stl/querying_find2.cpp

// There is no specific thing in Boost Config for libc++
#ifdef _LIBCPP_VERSION
#define BOOST_PHOENIX_USING_LIBCPP
#endif

// This may not be true for some very old version of libc++
// Current libc++ supports unordered_set and unordered_map without C++11.
#if defined(BOOST_PHOENIX_USING_LIBCPP) \
 && !(defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP) || defined(BOOST_NO_CXX11_HDR_UNORDERED_SET))
// This is either libc++ or C++11 or later
#define BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
#define BOOST_PHOENIX_UNORDERED_SET_HEADER <unordered_set>
#define BOOST_PHOENIX_UNORDERED_MAP_HEADER <unordered_map>
#define BOOST_PHOENIX_UNORDERED_NAMESPACE std
#endif

#if defined(BOOST_HAS_HASH)
// This is to sort out case of Clang when using stdlib from gcc
// as Clang thinks it is gcc 4.2.1
// This prevents the failure to include a header with a warning.
#define _GLIBCXX_PERMIT_BACKWARD_HASH
#define BOOST_PHOENIX_HASH_SET_HEADER BOOST_HASH_SET_HEADER
#define BOOST_PHOENIX_HASH_MAP_HEADER BOOST_HASH_MAP_HEADER
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE BOOST_STD_EXTENSION_NAMESPACE
#define BOOST_PHOENIX_HASH_template_rest_param class Hash, class Cmp, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Hash,       Cmp,       Alloc
#elif defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB < 610)
#define BOOST_PHOENIX_HASH_SET_HEADER <hash_set>
#define BOOST_PHOENIX_HASH_MAP_HEADER <hash_map>
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE stdext
#define BOOST_PHOENIX_HASH_template_rest_param class Tr, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Tr,       Alloc
#endif

#if BOOST_WORKAROUND(BOOST_GCC, < 40100)
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS , void* = 0
#else
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS
#endif

#endif

/* config.hpp
UAFVUAsN0AzboAO6YQACZbQZpkE8JEEqpMMSyIEiKIe1UAP10ATt0AX7YRBGIOYW2g+JkAKZkA2VUA2N0Aad0AP9cBCib6UfEAsJkAYZkAfFUAFVUAvboAO6oQ8GYAgC5fQFpkE8pMISyIEiKId6aIJ26IVBiLmN9sJCyIRsKIBSqIY6aIQe6IeDEP1R2guxkAxpkAFZkAfFUAG10ADNsA06oBv6YAgCH6OtkASpkA45UATlUAOt0AW9sB8GIaYCXYFESIGFkAnZUACVUAeN0AKd0AMHIfp22g6xkABpkAUV0ADboBv6IPBxZArTIB6SIBXSYQnkQBGUw1qogXpohXbogl7YD4MQ8wnaDXGQCdlQCdVQB43QBj3QDwdhUiVthQRIhgzIgmKogCpohm3QDQMwBBPuoN2QBOmQA0VQD03QCu3QC/thEEZgyidpHyRCJhRAKVRCI7RAG/RAPxyE6E/RRkiAZEiDPCiGCqiCWmiAZuiAbuiDARiCwFraC/GQBKmQDjlQDmuhFdphEGLupK0QB4mQAgshE0qhEqqhDhqhBTqhB/rhIER/GvlCLCRAMqRBBmRBHhRDLTTDNuiGPhiCwGeQM8RDOiyBIiiHtVAPTdAK7dALgxBTRdshDlJgIWRCNhRAKVRDHTRCC7RBD/TDMAT/YiEd8iB4qiXg9wF8azmBl/8DOzj+Nn3j3818n5XNN7yDpCmkk35OfyEbejjXSLqQfL0D6AHk8e9KzgffkTW9mf4kku8y+nALY3MrfYAi6A4gC5gURXmQDRXQCAMQM4a2+yxtBOLeSpuhAGp8XtY76jlZGuQ9xHmI5jedNaRpsJ/2xJI2/gT4dwXpEHTw7y7SLKji38mkSZ3IFxqhHllkkLZDJf/uJy2CKtgWlFMx5/jWaiHfrbVWjglUQx+0PcLYcj0Harg+CZIgjePyxuC8jCzJk8bvREZoVyxpBudbSasgD4a+Rp/q6T+/vY3mO+eDr2U8LkH3oGcO7eTcfq4FqHtoJfVTZkI7MuJ4+FbqKqfP0Ap9UPUcsiGthhTanQ2V0LiaFDpT6Q9pEnRyfgDK+T63iTSLc+FYNa8QOUF1ML2c/O/mWj3ygoNLaEt7cG0yhucNYwJr72WMF6E/3NcLa/n9wAjneoOxxYeR09uQMTQF/825PO6LheZ7Q/HGwqXIjmvZHA8tpTxohHTOJUIc51OhZ1Po2eQIaVwT58aPCUyDTGQ0ZQf1Bsv2uWnL6aFvFyZMDr0HrIMumHYBY3th6L1Q58WhZ/4t7ZR5AeMIVZDH77bSoQoSoYVz0yAV0vn2OC4eG7iAPlBfAHI2hb6RyYJyaIAOGITYaMYfCqAaWqEXYsbRBsiGCmiApB58yGOUU087i6mHulIoO2c8Y803jg23orMbaDN5RyDuNGQHeVANrdALgdOpF9IgEdXJhGi+meuiL9kxyAdaYBji/N4kD6qgBXoh/gzuhwKogVbogwnINBlaoB+C33kUQDVsgwG/38iBamiFCWdRBwS/qaiDdhiEKZM4DwVQDa2wHwYnUz92kAlroRXi/EahElqgB5L89qAK2mEE4qaSDyqhEboh8HrkAPVnU+c0+gV5UAUtUBN8nx4bene8BLriaAMknUf5UAp10AtDMO182g1LoBzqoA36IXAB5UAWNEMHHIQJ8cgNsqAKmqALBiF2Ju2BGmiBXhiBBPQ0A2qhDfbDhDdRPuRBDXTAQZiQgMyhAuqhA/bDBN9lZkMlNEI3DMOUN1MWLIFK6IXAW5A9FEEbBN8hDsI03xfmQBU0QQf0wwTfAzbBIMTgu+IgFZZAKTTAlFHv7CqhGbrgIEyYzRhBJpRCDbTACMTPoRwohQY=
*/