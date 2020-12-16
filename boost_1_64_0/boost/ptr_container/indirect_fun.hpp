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
LPdn7+3Qfkzq00vS1biUnz3Bh+Zi+/Gk0/+LSN9AGVaO99lbzEafteizz+/QZ7Td/fYRc9HvAvTb97/Qb3LffcURbnamr+lQMm2Dtq4+N8+neIQs30/tSZzQ25Npl2vt1WjtyTI8v1bTQz5mcRExR6V/5ZOfAtehg27ux9B2LLuFfAwERz6GBkYzm4kW6O2xpD5DSev4762h/H0pLb6Wu17Ho9l+6vx0aovGh2/FGCJsnlRG5S8h/TsW1zkpn+swLW72Bofq0eYzh7L3kjZRTMRj3MnxLGfTuq5m33xdvfyb3nqi9tX+WsezE6n9DQxv6Zv8R2x4IE21oe9BT2HwkO3rfSyLrzu1MYtoSt+vne7mfVEZra8z431RGR1eZ9l9kX8MGxPraznrC7ilcETv6xzWF+Fp0jta5zLaAL21SRvnoey4f8sPt51+Z7bPGfkl2Gd2zu8wlyXO31Ot78JCr4fqJHzOoPRWTkvWMwuqSsqTfLKLi0qKtDs7OIDE4Zw3cWeSdCck7+RjJtVl7o9Lh5flnhIl63uQrD+/nbK+MCmOGD3GSnFB5Pql0P1rKoO5N/jjNvYsZTevrffPj4j4/ewL3fx+9rxYLe5NJqzp9Em2Y+f70a3V4bZ3t3YGpNkWLnEn2/R+ot+8nsSjGL6torp/0/f01K5+B/JyRg9NFCNEluP0cKWbznjSku9jr0X6gXIM/K03lF+nyZyhPWgMTLbyt+GuYfQm0/I0PnId8hvje2VRVcRjABjqW2qHtu5vIk337XKptLyysmJPbml8v4Y0/qZ1J3wr8iyrEONYDMQb3LJXrFgYb7X45H3/iIV9WqLEP+f7t7Ggdv/WTmB4cBPhwSrC4UxVt2VOwB8W9I25tZTg1KIuOTZeS4F/cVntrEBgIU/vrNIFfUtcb5kWitltdUNbwcZYNCCojsL/Fm8AN8BrWNpeslx9fTCiMhRtqJhbtyTRhs87B6f+JfJMXU2RfWOGzmdk6r0HnLKXKhcb+P1YNfVU1M9zrl9SBucFhxbsdNZGhXMbs8Aty2bJ2BSFMGTI+BS8qdaz1bq1Ni5PaZXDsOzkdrRRWJZf5XVoxE5nrRxDOHObWhMcPnuaA430VvV6lVYSikUCVirhyO0qfVawsSbUkherrQ2EvcFjqIjM32DVCzTG7LQ7VFphqDoWSbQ1UnTu1Qnodqdb4sGkWKMM/1AzIuqfP1mOuDIpBWMdmoTfqplK0I9q/y63xGer6fg71nczPMsQINjyqmSI8BS0P5LaP1rVqGoMViNGZH4dqIjkgErPjVQHgyoV45f9dL7Xjc7aMf5zk85o5wHYBaGWRsHpsSLQFPBH80MxTIPT48xgOBrz16NKPsWttGmT8rzV/kaVqfLuU7w3psZpy6iaFnl0GQ7JhrxRPyh4MsW4up/TZAfoy/ktH+y8E5XwL+HrPjT/B2VfGIvEGokHkr4MjOEhNoaUf5O++nF5rubd0IAYRUU1km6ov4d5fx2kvX2S19IbiCrcFvG2H+Vtd5Amh1Pblk92cail3B+O2roG2psWnF+nEhNvtj/O+kvdGRerdFyc3oE+ZNoTqv2YwqVsVefwmL/Gys8BHaQATZ90y759VcW5FVM96jEbXCRQlKCl0Vn2473aijHXtlxQ5+3uZN8HFU+L4ubY85B6GX2T3hZZiDGT78Nzbu77IO2tMGr5KvOKVZ/sG306yuh28BX1hhWNdSKHO3C8GgSaLJN9eYtBlzbt+xShKn5JY97M1xp4Oy8iS1gKQuIL/cZpoIcqOVvQ/+BVc8RwwpuXOJ5qdNu2nFEeg+TqV1nh8cRVFId0tLJAo30lVcpDkaB0LON4h7y8WDQaarSmnVg=
*/