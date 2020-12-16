// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_PTR_LIST_INSERTER_HPP
#define BOOST_ASSIGN_PTR_LIST_INSERTER_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign
{
    template< class Function, class Obj > 
    class ptr_list_inserter
    {
        typedef BOOST_DEDUCED_TYPENAME
                remove_pointer< BOOST_DEDUCED_TYPENAME 
                       remove_reference<Obj>::type >::type
           obj_type;
    public:
        
        ptr_list_inserter( Function fun ) : insert_( fun )
        {}
        
        template< class Function2, class Obj2 >
        ptr_list_inserter( const ptr_list_inserter<Function2,Obj2>& r ) 
        : insert_( r.fun_private() ) 
        {}

        ptr_list_inserter( const ptr_list_inserter& r ) : insert_( r.insert_ )
        {}


#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        ptr_list_inserter& operator()()
        {
            insert_( new obj_type() );
            return *this;
        }
        
        template< class T >
        ptr_list_inserter& operator()( const T& t )
        {
            insert_( new obj_type(t) );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    ptr_list_inserter& operator()( const T& t, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        insert_( new obj_type(t, BOOST_ASSIGN_PARAMS3(n) )); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else

        template< class... Ts >
        ptr_list_inserter& operator()(Ts&&... ts)
        {
            insert_(new obj_type(boost::forward<Ts>(ts)...));
            return *this;
        }

#endif

    private:
        
        ptr_list_inserter& operator=( const ptr_list_inserter& );
        Function insert_;
    };
    
    template< class Obj, class Function >
    inline ptr_list_inserter< Function, Obj >
    make_ptr_list_inserter( Function fun )
    {
        return ptr_list_inserter< Function, Obj >( fun );
    }
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_push_back<C>, 
                              BOOST_DEDUCED_TYPENAME C::reference >
    ptr_push_back( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                   ( assign_detail::call_push_back<C>( c ) ); 
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_push_back<C>, T >
    ptr_push_back( C& c )
    {
        return make_ptr_list_inserter<T>( 
                    assign_detail::call_push_back<C>( c ) );
    }

#endif
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_push_front<C>,
                              BOOST_DEDUCED_TYPENAME C::reference >
    ptr_push_front( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                 ( assign_detail::call_push_front<C>( c ) );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_push_front<C>, T >
    ptr_push_front( C& c )
    {
        return make_ptr_list_inserter<T>( 
                    assign_detail::call_push_front<C>( c ) );
    }

#endif
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_insert<C>, 
                          BOOST_DEDUCED_TYPENAME C::reference>
    ptr_insert( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                    ( assign_detail::call_insert<C>( c ) );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_insert<C>, T >
    ptr_insert( C& c )
    {
        return make_ptr_list_inserter<T>( assign_detail::call_insert<C>( c ) );
    }

#endif
    
    
} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* ptr_list_inserter.hpp
ZaBhO9j5zz5inx+1DJrAbPGfJvYiG7+tzeNrxR4fs0yuEP+EKuEbaB3jbdyWxzDxm2mCegdPwX+2fp8uxpRTn0v2Yz/DK1NFn7wtl9yIcsnzlkvd9+Ao34N/+e++zUe47rMfufvkXhNmjel6Yc+v3sm//ohY36H/N74HTzTal8EK3QM9EY7y6ErpDDvCHvo9b4jKMI/X73on6Xe9fJVxnu7RAz/VaDuFN2r69eEETT9V028KB8AMOAk203Sb63fiFvpdsCW8QL9LXghb1+lR369vS/+t35V+zW9KV/EdaU3dt6S6o+6oO+qOuuM/8IjDzPkV3v/RAlwU+ALw078BnJTF+6DqtmZuXI7XMY0xGzFNeNfc2UneNWW/NytpXlLgkenDEnrf1PAHqB15ts6uPcmk2XdITcTYPd40TqrVPetInGfNQP4+grHvj5xrzqwCu+9AqoS70bQi7iGmqa6/tue07+4tU1WOKWv/9rxXeSK5v4yw/cpC98B7oc3D9fodpUTz0PXfns79tZY8LJ1duEAUKk+nhOfMD7yzf4i/o7J3un+ihi/hvkZKmIw+8u5MoND6aH8bN8wk5sfj7X3udWWxrKn9NwqugXsi+Yj7maxDrkTVd74X8ylhV7SKuJ+5pQvw8txPQZlH57mGb2/f5Z8W+zC1O+Zqud9UT/yyedM1/kgbv6UJyok+KvaPkeWo58mfMvcG7DkSJc1LI8/BVYxO5b1M9ryYluXKSrRMSqjn86clDa+X6K9Xz5ec0CIoC/x5iomZ/5vkGp43D1HPfOaYVLuXY0Yg7+e12N/8J8/Urb91Ix8iyqQ0wcixjpO1VsbRaKamRJRJ+bxivCPrmJaJhtf1H8dgv0jsh/iXmqQqOj16SDsNxsn3DzLnmBf4NlPstDbrMN84w81xvqbmOl9rE+8/zLSQ8I5ZL+Efd5JMtjnWHGNWmVQnlHZpL2DL9AIJe5h/Gfeq35P0fF3kevz1JE5viaNlfK74H+5frjoyxto4HWOW22Lxz/FfYlLs2v+TtV9wWcoL7hrK8P4MbU+16C8ameRAH5pO2h77OrWnIeu4Vc5rOo46pm8/o24FqdatT9DtpnTr1ivodrR163NI0G1bmnWz4V5JsW7ZQbeHrVvv/kG3W9KsW9+g2+iQm02vmXXrdWjQ7alU62bj3hNys/cxW92m5Re4jw3bp9q+psoekFLXIr69aR1RmXl/PXGjDujaBG0TU5OMHJfFBfqphTCBNtG2adU2MaWsfF417ULjtDO9tV4OFvvMuJ6c7ymnntmNOcJXz1yM+QEznos6D/MBxk0zKyVcF85Im2Yb00Pr7SCxHxXnrloaa1Y7LXw9zAzMHb4p5kS/Y072Z5s/YdK07yqQ8K8yuKh0Quc4Lb94PmuBtF4PkDDN4g4k1tO0uD2YHF+SuQTzma+tmeBPMudjPsTY9VgSp6XYh9vzJHiet6Ul/LHP27XiX2jiTVfTDxN83r6ZgTuh9Bmv62jC9cEf1yzy+/ycaYiLW/+bm1X//b5zpui+kXM0T5drmz+tsKJU6kdg/YFe/3vIQZ/ti9DZbnXq50s6J5qGppvV2z5H3FrE1PP+sfj3jQwf9Voz4ZLm0rd6ZK+L86eZ0H4e48R/TGS+y72lGQ1P9lW9txFxaeZN/zD6rRTde+fmTEsxJzcT0nfJN271k99QEoS169eqa7PUwcg2q26Bepmhbs0lri0r654m7dvep+y7kid1gDbcMWC/3trDn4EvNlRZSDw7QAfucsdZjcLbu+4oEKuta/g+dszQobHUHy238L1bRtrw2XYupa2Ef0v3iNDwej/axjROd7tGsrXE+Ydn7dKsOd59KFqI/0f6PNM=
*/