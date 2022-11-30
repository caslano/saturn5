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
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
*/