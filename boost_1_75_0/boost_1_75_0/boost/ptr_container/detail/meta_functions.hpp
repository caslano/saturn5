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
IZqXED31OSTlmFgTIJjEyRBlcdnGJqg+fNeYIFIOpD7EvbwLbkDru2WjCYj4CKvJom+VvbKh9S3IRg9PsoGNjWsx4t6KTVDbHTiKnp08B7AmUNtlfm/Mx+nYbLzQD5lypwIb8XC+jdlJmPu3vm2CZIkwEMhPXjtzJLR0zrUQl8TSVSr1xKTAwszltwiUsumMDdr15MN9LxgKZXej2zIgTFsNXRDqwi+BKOAkbIr8dRIKBJ9I1xSHh81VQKCmhNc1VrH1cDVeRqhlihLihKJglN55xpJ11oKpnB0Pxham/+84NSf4weJJPtP+6BilvoOJ9H6HHlDBxAj5PjWBvROMkP5IZImUikeJ8ddhmqptKboqQoMalDF5kDM0qBLrISyBQTVyEvmCUynHdpgiYSWMw5ISlg5OgEpA7jDkKhIRUH+VwLsdgrYUmwLHlEiukp4V0/GGjkc3Tak3dHAjQJfisuMPhiDvdE0Nuiyi1YW9XuRrwTkG0FM52YSADag9laC33j/XQFfArAtBElew3kz1F5gEzyojYIY8XupK4yWDtxKvIA8clzYDDgERD5TzP0+X38dessZDk+4D2qhu9r8S8G8fjYHrv8mv95qc/yPzo/pOit/ody596uc036k/4Qgchpz62AyxJUEj4Q7/9zs9IatPaQSYRoTlFLOS/MAr8Eo6v6BbJgptvVznnj9pxHbIOHOxogLm/74SemAU
*/