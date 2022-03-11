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