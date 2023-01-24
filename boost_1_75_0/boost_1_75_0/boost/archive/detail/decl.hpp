#ifndef BOOST_ARCHIVE_DETAIL_DECL_HPP
#define BOOST_ARCHIVE_DETAIL_DECL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2///////// 3/////////4/////////5/////////6/////////7/////////8
//  decl.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK))
    #if defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE)
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE) || defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

#endif

#if ! defined(BOOST_ARCHIVE_DECL)
    #define BOOST_ARCHIVE_DECL
#endif
#if ! defined(BOOST_WARCHIVE_DECL)
    #define BOOST_WARCHIVE_DECL
#endif
#if ! defined(BOOST_ARCHIVE_OR_WARCHIVE_DECL)
    #define BOOST_ARCHIVE_OR_WARCHIVE_DECL
#endif

#endif // BOOST_ARCHIVE_DETAIL_DECL_HPP

/* decl.hpp
5tfmi/GgicAX+pyzMrXV0S98dkC0z1YCL/7nBSuzIP/9K4+8J9m/B8J7on+yMu8sTzv3+B6xvSoCP9Ny0crceWr2S4EyyW8ncLfHL1uZaUucrgenSf6DgP/dL1bm7OQfU5a+Iq1jELgq3Azj0pQOh3SzuH5VS+CKryxA52zutI2qDqFfmAh8z4xrVmbiXuasx42pIv8ETj/XbmWeq8pJsk2U4v1JCPdrv2FlqBOvh92ukvgn8PDwTivzytPvTN+6WfKrCXzlX7qszJtT6pedmCn5bwSe3nnLygR45FoX/yHSqSDwyiU9VmZP0qYNm18U/ZZaAm/cdhfsWb366IubRTmbCFx9nOpiVm7N/YSrkeyHwLsVjl3Mxsm+eRMcpfUfYT8g1KmL+XN+5CuLdkn2T+BZpS5dzN3wU5umfCCO22oCX/jBsC5myVgub7Jesh8C3/7DiC7mj0/OpDwza6bIP4Gny0Z1Ma/suzLC6bCIX0vgZ7yUXUyu7OPvJ6jE+N1E4JeDxnQx5ZtnJr1ULdpJK4G/n+TWxZzULjdFB0vr3lMQPks/votJ2sS7eurEfqEi8NKt7l3Mz0m+y08eFemrCbz2xYldTNU137eihovjcwqB73nDo4uJ15z709sqyf4JfPfbk7uYGQ3rznx+Uoy7awl85zuqLsbXZ3aRa4Hk/wjwt6d1MdoUzaPvzJTGT5G+VxezaGf0iOij0vip
*/