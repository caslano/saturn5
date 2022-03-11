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
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
*/