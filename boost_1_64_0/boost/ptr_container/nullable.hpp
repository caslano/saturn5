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


#ifndef BOOST_INDIRECT_CONTAINER_NULLABLE_HPP
#define BOOST_INDIRECT_CONTAINER_NULLABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/config.hpp>

namespace boost
{
    
    template< class T >
    struct nullable
    {
        typedef T type;
    };   

    namespace ptr_container_detail
    {
        template< class T >
        type_traits::yes_type is_nullable( const nullable<T>* );

        type_traits::no_type is_nullable( ... );        
    }

    template< class T >
    struct is_nullable
    {
    private:
            BOOST_STATIC_CONSTANT( T*, var );
    public:

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(push)  
#pragma warning(disable:6334)  
#endif  

            BOOST_STATIC_CONSTANT(bool, value = sizeof( ptr_container_detail::is_nullable( var ) ) 
                                                == sizeof( type_traits::yes_type ) );
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(pop)  
#endif  
            
    };
    
    template< class T >
    struct remove_nullable
    {
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if< is_nullable<T>,
                                                      T,
                                            mpl::identity<T> >::type
            type;
    };

    namespace ptr_container_detail
    {
        template< class T >
        struct void_ptr
        {
            typedef BOOST_DEDUCED_TYPENAME 
                mpl::if_c< boost::is_const< 
                              BOOST_DEDUCED_TYPENAME boost::remove_nullable<T>::type >::value,
                           const void*, void* >::type type;                                                       
        };
    }
}

#endif

/* nullable.hpp
Nwfexfma4vyFSgXflkc6+Cucp3VQ5sf1ymszbFtMTTr5OJBe+zqt6dBWdDemtCkY0BmW4klZ7OzqaO2ctgtW/S3q423qIz6evHT5y8piPO9Q2a1J+wG9nCHeo3LvUzn5fzmPZ0pjatJsHcfSXamPmL79Rxo7j63+Cenvi3qSrYC9I3wy2Sr12Pefs30ExV/T3hOHD2W8DLPFZLEyXVDmK5rbNu28TeY/7ea/HCadxHaq940Gu2fd1D7B7jsq971dLu0Zdmb7o7ZOP1FffJ1+pjZ+0fqS8ObxAHcwONNasHykZhI8GLyEBlcz0+rLlWnH3fsj1f+R3snolMhz9XITTEWKbV/aux98VbSz3NRM6xt5VozxXsn2pWEZ9thm93C2/3TPtOc3m+WnEd7shXxua5Hpehtpmbu881ggAzepCFf8oJ6nE29Oz0xeu574XqS9Q5GRaa9XjWaj2yeT6IfNx+muVR/WRk+C4xaCWz8258a+zm8GDGD1b9b2+oNY3qDeyXlu5HH8ak6nudJ5Oh+nenMj0/6WuD+d/MT2JTjxNwpfcJONNIXjeor4A+HfsExGj+xdmj16szcUmR1iOJtHtEfy3bQDNLx/oT/d+2QwGslw61gqI/M3E+6PyuSxdmQ7tp/b5v5W+b77JMfVyMlM5ntNWty5sTTXg2iu9BYEveHD33mg8XA/gUyeT/Nh+RMzyfeB0TrhhhrnAPxy35pJrL0g8wHsSbJrMsufj/x9NDyfYsEfNGHztrzMZH6Vj29upymw20Se3WeM+iyk8lh7goken1Phs1oDfu+8KFM7M+tPa6WVm5HJvjGea9K5j6Bex8KT0kwbJ0sHWmPg689xslzDqXAfHqseZ25snJRPffJyKaIyc5dxcpnypC6wMc7lkEv8aybnX4Qfs5DG13U2retMtq5ztXX9o7auR3C8Z+v6INHSkUjjcJbpUS3291FEG28yuXkTk5vV2hhqaAzzMq0xBFgfSCPcT/bRmG/zDJTR3gNg64y8NuO3LozPl8rq77M2MFqksZCdn+lLjBZDjNc4l7fSOK85WluDIJv/gAHOciFKMN7itvlPM8HvjgwL5lsYzBdpMF9Mfc6iOscwOLh6UXw0fleZwXQzjYf8RNn70HRXmdEGL6v7n57I5snL8XkuZW39QP6dTudCp2Ry/U/+2jJqYXqy/reMYHcawYTX+y6t9XpnUL0zqV6SL0AnzTfA1L6NVmKitr3/VOu4gtHvOapvphuTHf4vSOdwOzfTGh/Kq/7fV2eIdP5I78rx/CMwPsJz4s/JNKPj+QUMX1Ce1o29dU/jAY+n/izYRTS+JfMvQRqve6lGk3dpPr+raR0uc2jrcq2tK1hb0tf0DXcyj1zDxsnPNjEm0rGSafPuHtqbKJR/ozueT2vDxq7T7nVU53K7DxojvaWg6f43clnrcGZ+s4RD/NxQ+HAfMdeXOxP+SPItfN/s8eMSZ4Z6HsLC5tD5oVPe2ByK66Pl4b/ZiXMRPc9TWohjuamU38mpLvUpds6rKIHm7jzWUk9ZKR+rnicrj1PvFU1ksVZuBWxY2aJivCBsHcjoqSA21HX2BVaWArqOj2uw+RW40V9WocjVOStxTrOe8YoptN9KI7+ibO27SfvuoX1Hte+e2neMfW8g28sGhWMN8g5l7RjAXdnl7bQYIKbS7rTTguPJNnMXSxs9zip3N0uLt3cPS4u3tzrd7iPeXqeedlq8vXvZWGR7WaKzXLuh9yE9Dessc5Q50fpXwVWe79k2yfIo2erJZqQszOyMtiIQCYSb429HuFWaPEKwv/dMlBkt7HOseFqOmE728gcymW3pN+LE0qTzjKLEOxRuyxPLiqUs7DQ=
*/