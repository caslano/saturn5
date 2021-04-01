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
FO1O/Z6XvoUMWomtTA7/sxhdGZRVD7YHhx2UdmM4BnldaXofZqBmgWyl+73ppMN9l5G7+HkXrIqduuarTbXKHnmbp7sOsw/5smma/GdJbPRFGaruMa6evFUvkU6f7PD3jhUAUgfKWGybhATmQoMjaXXcZZ/cc4Ee7t/Ver4MTAqc5ZiHJFatFsWK8YC6phlhzCrSoYox+hd2ED0N5FoSGcK353r+nsBjQKZx2o2hDpm4XYiM7aEtWM+B3FE5f3nadnCw0f1YJ6ULXeq6Rbp/BMyI4t7YX0696tSQbZzO0LECztLavFAywVKn87Slq+kOnO4OVCC6bkrtYsfZ1Hmjg3znu9wd6si2kmuJgHuXCD+LSecNwv/UhFK7yxCjQtxpmuw+DryGQyZWz6WLKcNeL5zxRWKAp6bCq1pQelvlZrkCQE/xv3XxpTCf12fU9nxBtN7itMCwILHeSDepLsXToPNOExdleGEp1Z/cjItXCBQHFCkMHVt/+nUAUVpE16ZdyQpNlm/fIOvToI+/oa09ah5pTksyeY06kr6uatZB/XEglOm3g/Oc3f3P7w==
*/