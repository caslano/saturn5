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
diI/QQyGjN7ncxxlZPPsNHIpOlR8+wOwo4fnNdPXqkehxn30qUhY5GrC4L5FVAPLdxtGGykQvz8qsgiIvBxpvuNefCf8/R8FmD32SL/VKJf64Hd5ehHDsBTIKPsSqBL3dhy7uNaX3FZxpjwIzTLDkoWUbHPT/R1qtas1xgzuhycfkV8S1oHMqOF5PDdB86NG/QcPRPGPKABEB/fVZFBkNIgtyVn6Gs1yMVYdJ+4BCggee9vhCmLlbwVrVbl06LNvlMaq4ZQDWCtXPHXC4iFIXX9eOht9MbveIKY3vGLxgo0s9l0T5oFWF/AjlwBCxpdCYBByWu7sOGgbSNL60MzyTU21KVzmj2h9FgNk4C6mVKfYXblqYP9V4nmtaGDw91nMfyOf43AHa0vAVf/e3C0xCY3/7c0SZD0VVTgLRETcj3ovh9oYGQ4A1GLHTkEw7jUyeJOh0obiTwCqFWLEfoSKqcW1Qs7njR09tKI8jS5hJeMh5eC4WYEULEg44RTVCyJD8agBJVnuGwznIXT9Ap6NEO3oQkfg+TYFT1yPLF2vnuknluF6U1hGlEaVtg==
*/