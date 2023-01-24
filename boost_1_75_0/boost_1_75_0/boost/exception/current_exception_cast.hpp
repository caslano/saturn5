//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E83C166200811DE885E826156D89593
#define BOOST_EXCEPTION_7E83C166200811DE885E826156D89593

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class E>
    inline
    E *
    current_exception_cast()
        {
        try
            {
            throw;
            }
        catch(
        E & e )
            {
            return &e;
            }
        catch(
        ...)
            {
            return 0;
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* current_exception_cast.hpp
sQ17eKztt0Aboqv8JzRwrRBvBb4Wf0q6dWFx2/zK3mKQC1vCzoLn3srBTh2hJjSIUKmAUO06k1EMDR6cxUvL5OYtIVT5+UHEpu8fpMsvxa85NgIx57MHme7XqyNRQ9avvbuV9QvrRZDVaxPkGICz7QKfMvxfIOINrRw/z+sP81VdOw8K65H7cw0eonG3QurIRVG7XuU2qilJn7x1RSaUeOOUE5B6NMO/ro5OK64aDSu1HjLVc+NuA92ISIU+clEUWmVVa2VZVeh7GCuiJPSUYKjTIsn3rZxGVmWyrtFwnPAPRFL4p2QVrJKvbGswu6pr8KN254pyjRgTamt7LeIctrYVUXZbmyyfYU+Bi7Y2X1ZKEMxtzcHcVineC1yDx8ttaXC1CmZ0eK57BMVxsDEt0I7fQbNZksqCiRWYrIS0SeacnoYecdf2BiFn74B85QU+4txokkgait7071poOalUVpc6TYlzlZc7jEZOe2+9Xp10JcrgxeK88IklWF1jWmJOftq0RK+r4gUDzKgYKv0UWdn6u8qRIlccKI6HWvM10gWUUg4uIIGXdXeiOfi+UR5MuNf8BSQHBaP0rPozr7fY8UDUbIPZXMy91px9scqq76tq1h9qrQIxmHYxbD7x5e9zPTIDbQIOFgbTxieLpr1WJgdC+f3xncBIld//q5FYWyGPaysEc6kiBgzlowjbULaazoupskKeKmTRA5L8
*/