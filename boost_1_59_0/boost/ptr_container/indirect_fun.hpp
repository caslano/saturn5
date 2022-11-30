//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_INDIRECT_FUN_HPP
#define BOOST_PTR_CONTAINER_INDIRECT_FUN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>

#ifdef BOOST_NO_SFINAE
#else
#include <boost/utility/result_of.hpp>
#include <boost/pointee.hpp>
#endif // BOOST_NO_SFINAE

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_void.hpp>
#include <functional>


namespace boost
{

    namespace ptr_container_detail
    {
        template <typename Type, typename Dummy>
        struct make_lazy
        {
            typedef typename Type::type type;
        };
    }
    
    template
    < 
              class Fun
#ifdef BOOST_NO_SFINAE
            , class Result = bool
#endif        
    >
    class indirect_fun
    {
        Fun fun;
    public:
        indirect_fun() : fun(Fun())
        { }
        
        indirect_fun( Fun f ) : fun(f)
        { }
    
        template< class T >
#ifdef BOOST_NO_SFINAE
        Result    
#else            
        typename boost::result_of< const Fun( typename pointee<T>::type& ) >::type 
#endif            
        operator()( const T& r ) const
        { 
            return fun( *r );
        }
    
        template< class T, class U >
#ifdef BOOST_NO_SFINAE
        Result    
#else                        
        typename boost::result_of< const Fun( typename pointee<T>::type&,
                                              typename pointee<U>::type& ) >::type
#endif            
        operator()( const T& r, const U& r2 ) const
        { 
            return fun( *r, *r2 ); 
        }
    };

    template< class Fun >
    inline indirect_fun<Fun> make_indirect_fun( Fun f )
    {
        return indirect_fun<Fun>( f );
    }


    template
    < 
        class Fun, 
        class Arg1, 
        class Arg2 = Arg1 
#ifdef BOOST_NO_SFINAE
      , class Result = bool   
#endif           
    >
    class void_ptr_indirect_fun
    {
        Fun fun;
                
    public:
        
        void_ptr_indirect_fun() : fun(Fun())
        { }

        void_ptr_indirect_fun( Fun f ) : fun(f)
        { }
        
        template< class Void >
#ifdef BOOST_NO_SFINAE
        Result    
#else            
        typename ptr_container_detail::make_lazy<
            boost::result_of<const Fun(const Arg1&)>, Void>::type
#endif            
        operator()( const Void* r ) const
        { 
            BOOST_STATIC_ASSERT(boost::is_void<Void>::value);
            BOOST_ASSERT( r != 0 );
            return fun( * static_cast<const Arg1*>( r ) );
        }

        template< class Void >
#ifdef BOOST_NO_SFINAE
        Result    
#else                    
        typename ptr_container_detail::make_lazy<
            boost::result_of<const Fun(const Arg1&, const Arg2&)>, Void>::type
#endif            
        operator()( const Void* l, const Void* r ) const
        { 
            BOOST_STATIC_ASSERT(boost::is_void<Void>::value);
            BOOST_ASSERT( l != 0 && r != 0 );
            return fun( * static_cast<const Arg1*>( l ), * static_cast<const Arg2*>( r ) );
        }
    };

    template< class Arg, class Fun >
    inline void_ptr_indirect_fun<Fun,Arg> make_void_ptr_indirect_fun( Fun f )
    {
        return void_ptr_indirect_fun<Fun,Arg>( f );
    }
     
} // namespace 'boost'

#endif

/* indirect_fun.hpp
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
*/