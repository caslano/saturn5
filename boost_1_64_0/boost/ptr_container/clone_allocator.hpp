//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_CLONE_ALLOCATOR_HPP
#define BOOST_PTR_CONTAINER_CLONE_ALLOCATOR_HPP

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <typeinfo>

namespace boost
{
    /////////////////////////////////////////////////////////////////////////
    // Clonable concept 
    /////////////////////////////////////////////////////////////////////////
    
    template< class T >
    inline T* new_clone( const T& r )
    {
        //
        // @remark: if you get a compile-error here,
        //          it is most likely because you did not
        //          define new_clone( const T& ) in the namespace
        //          of T.
        //
        T* res = new T( r );
        BOOST_ASSERT( typeid(r) == typeid(*res) &&
                      "Default new_clone() sliced object!" );
        return res;
    }


    
    template< class T >
    inline void delete_clone( const T* r )
    {
        checked_delete( r );
    }

    /////////////////////////////////////////////////////////////////////////
    // CloneAllocator concept
    /////////////////////////////////////////////////////////////////////////
    
    struct heap_clone_allocator
    {
        template< class U >
        static U* allocate_clone( const U& r )
        {
            return new_clone( r );
        }

        template< class U >
        static void deallocate_clone( const U* r )
        {
            delete_clone( r );
        }

    };


    
    struct view_clone_allocator
    {
        template< class U >
        static U* allocate_clone( const U& r )
        {
            return const_cast<U*>(&r);
        }

        template< class U >
        static void deallocate_clone( const U* /*r*/ )
        {
            // do nothing
        }
    };

} // namespace 'boost'

#endif


/* clone_allocator.hpp
nWUKr8etIxV+UuFXqPEl4RlfjhYaHiNmCM3D09rPy1UWp6MDOJnM98zH89R8PN8j+wWRHXVDe2tDsBe4H+RhVY7ygDFB9n+V3/ekuWulz0LkbF6NM+9Q732cgLYQfthnZnpJR9GvFvrN/5JxQ7dVLv4c4+/O5HnencnP8u7MPNXG85U8FHjewVigxp39POPOQs84UegZi4rUWMT620k5yobtd9TOut81CB/2ha3btknNEYUyR8z5j21rO6b65wjVlv6+2dSVpvO0AvR3164rqE2PsWN3IdpjbY7tgbk46nN9eLe7ebEL63NNgfnPXqWmWlRfvkP5jW8jvOBkTIjjO9wcIfjsZ0+dyF8xvbG3a1pywOctnfJb+SL3tbvyHT3X02fylD9p6t+dgLq+7S55uP6tfDYXeGRtQRY/2vs5f+XUz2UkSHfyGo33vdDH1zR3dMmftrWZTmtNzT5G1xk3Y7vdHpcEaX9Lv99TFtIQbBHdqQzXgSnIbU+Ocks+HrE/QfvfRYGMbAx0zcKVi9w66VSB8Z72aZCjW/BG8XMlvEJw88kHCfskEN4Cw+9Cj42UtNrzFrMfAqxx1DjXy+MY9kk+8B+hX7S1G5N7yDP7crPtlB/aueTYTuyPRd992yI8GqY8f7HXA2zJcPKiwdG6eKtrV/nt2nu7au9BpdedQeuRbcCVFAe4IQmz7cjRbgwCXvlTVPqshK0cjmKdfLvQaB15THD8du244jmmeAqd5TmJeNuK47bKPypy4Zkz/9nyxPZzWr788qTHr7khDOE8vpfE46O9mNDT0ZTuzij9J7OJ4G6c5OGKx0qR5rae1gby2a/vp+0X6sr2Usnf2bsO8KiqLHzfmwABUUMI0mGSIIsoCAEREJGUCQTSzCS0dR2HZEIGkkyckoAFFRXLKriu2FbBAtg7Ym/YK4qK3RV7XUXshd3/3ndm3pnLS0hcd7/d7yPfly95t99zT7vnnnsue/tPu+uV5nAnrIfDXa90hzthPR3kQIamE/Sy1iHXS+3sk/j2lRWTDOqt6Q19HN4j60tnAHq8/sXtpln5RhLFdstIfrNIjz1/XNw+Qfn8naQYf5cZ2LGE8cXMDIoVpMW2OjGO/1SGxx/mZ7dLByffib4jjfl607h5OxiP/j6AamcZ2pnZ9femk9/Cd5Pfjeji8G5EqqZvdE1848JdvqcIBfk+z4Mc6nPX71qgeGV+WQHTKVgetZ5ML/kl3p32EKDKXDUxopdEWn6FRxIs0QyT/9QF2SFYOtWwaSd+CCBs2mFHA8n6hqeAQMd0DkonMPO4p6T/UBWiK402+9J7IvlFRWAohapMP6JFuv5qn7dpd4UHOMSlHUhpuDfI76JSnNbK3HziAYMpzVuCLTmYDL+LqutymXHeWmSdk2RRXeBBAj7ZlAZwYtSlSfAfEs+Tg9JwZd/EPVA5dzs2qpXC76FK8HjKiiltmMav9rNws8LH9MrhlKauIVJ/+1Mav8d5gJWWz2lrhEO82ZEOfPpAB34+yoF3j07m3exuKgGM+h2jxXIeS3dngbaV8Vi4ByWnJe55j7PqzqoosgPTyvSDLRyNr0zlnHIL/8dr+5AJDvuMieTvHv8+xJKJFWW0d5zk8P7koQ53pycT74A1QPV9WAK+3gRdT9HOmHO1GMB5DnI/P57G9gEFtMZqmFTOQ2lyKvK70KI7j1fewJxVkVtO5aYm0ifk8PRp8fScg8bx9CLLLxwhkK1UmTad7Zt23x/efX949/3h3+P+cLKvSUP8bbN2657Mj7Qzzt0d94fQPXwVgeZQtV9GiCrCmxr5soWET0br+Xr8Ir3N6kCwKVoh78REoqw1Lce+V/xntu/8M9t3Ltc=
*/