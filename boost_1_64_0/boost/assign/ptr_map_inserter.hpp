// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP
#define BOOST_ASSIGN_PTR_CONTAINER_PTR_MAP_INSERTER_HPP

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
    template< class PtrMap, class Obj > 
    class ptr_map_inserter
    {
        typedef BOOST_DEDUCED_TYPENAME
                remove_pointer< BOOST_DEDUCED_TYPENAME 
                       remove_reference<Obj>::type >::type
           obj_type;
        typedef BOOST_DEDUCED_TYPENAME PtrMap::key_type
           key_type;
        
    public:
        
        ptr_map_inserter( PtrMap& m ) : m_( m )
        {}

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)       

        template< class Key >
        ptr_map_inserter& operator()( const Key& t )
        {
            key_type k(t);
            m_.insert( k, new obj_type );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 6        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    ptr_map_inserter& operator()( const T& t, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        key_type k(t); \
        m_.insert( k, new obj_type( BOOST_ASSIGN_PARAMS3(n) ) ); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class Key, class... Ts >
    ptr_map_inserter& operator()(Key&& k, Ts&&... ts)
    {
        key_type key(boost::forward<Key>(k));
        m_.insert(key, new obj_type(boost::forward<Ts>(ts)...));
        return *this;
    }

#endif
    private:

        ptr_map_inserter& operator=( const ptr_map_inserter& );
        PtrMap& m_;
    };
    
    template< class PtrMap >
    inline ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >( m );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class PtrMap >
    inline ptr_map_inserter< PtrMap, T >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, T >( m );
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

/* ptr_map_inserter.hpp
xHh5rmLk08BxCOB+018wmSUr8N2ESN3VjEk6UcmeihLFiRjGIItA2OSwW2oxaB918szEOjEIsV1PRUp7Pc6FrPKCHKUs82C/umucDT3yX1lmvp3i/mbD2l/3aQCjhEWcMA9uhPanOpBpt5EmpMk43Y60Vp1yVpKLPMC76uHl+prtgYGBtK8+3NSDz2kZlOyr2Qf2BTj2onDbxRwmfEjU3NSfnFNk3z6YsstwerUDVP/KnI6Od4cCd2bSnfDU3/ipY7l81Af7S0rYR1jVsUT+45o0Chjdy3HUyd3AnmyXM8Pw/H3by/JJ7Uqk4rOzK7jiTr4HEJyAaHZNj8h5M6S4ZLr44wjtoGNmUOc11iWE11Ow2L48GEjct5a9DBzQle50IQ1LTq1ZLLU2PRp7wd8eWupPHwJv5WhBtbYRO1SOo+c9AzVDAIQNcpmKkErJ1r6fbYMvOWqmOU23m4ujU87otD1xYVvB2rIy4fk5TcLt9xYq8HN+rNVJvn6tKRdVYCNFwPnjfc/iGMDnV1zHyRwA5NpP6aTCN9Rcuo++9+IDxP03jyEqVqMvirRM1A==
*/