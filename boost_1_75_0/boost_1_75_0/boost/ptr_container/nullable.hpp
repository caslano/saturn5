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
LES1RR4fob+cVs7+8DFxUZGFDpndByqaxDH3uNrUw8njXLG3v1Geaw5K9fW5PzN0sP/y3lHmPQBQsuMeVXFj2AegoU/7SK6aRn9sTYIF9b5rYytJH8xMOvTYAVGqn720ZnUUXu8MvAydAvaJiDiuWic6aTJdt1htrvK4iutbpe1SpURosSlbtSL1R13mARRVMtn5d0XmylxZ3yfGVBlzSVWj6Jso4S9nLq2zPpgc8jUPtI6XbVjtWLLHB0Z5GBOpPDBdqMe64OYSd0QWTUTyIIGajAbNQaVJst0uhBdUzwPCD+HCK3wuwWdRhZXR7NUlKrLTGPenRYq2HAzi+3arLZZ3FVeXbZ+s6iZRHqXP6zTBp3FOZZZYjUmNl2/1tgP0rL6ZAByPHUePG2JSLbRMHH6rHAxfVhAv/PBxbIvaE887CjXCsAcTd5gf87RTVQM5HvUbUcEvxVSUphplbrg3STiWVyeadfejm0irZWasVqk7wsgxvGyuTKInWsTYurwi25UO1nbuTdNDhr2PHyXTVKfYrEDiiSgXqafkCSZ7Gdz8I7sIg4LQnd+yU9u2CvV8BuSckFlT/NTjwZ1IqMxbkgeri0Pseixqt0mHi0omwQ58v2qJBV3mQb0YYZrtKBo7tiOXXkedEcQxEY0W4/yiUtNkBfV5DMymPm79+xtLkvt6dZL7hplw6AfrsJwmaTauSSHqAgpuQBdWjC57
*/