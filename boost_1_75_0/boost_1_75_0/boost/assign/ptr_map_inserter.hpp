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
28V9z53hroBXg/iFVg6meNs5s5ruwk5mVwq34X26q820IKOJcdPW1d72cyZK09uYY0wvdgg7kp3CzmTnskvYdexW9jv2e/YnYOEdtoB9zrpyPtwnXABXi2M4kTO5ltDYcTjrN9wluxLYiS/CF+NLw0PV4ZvwLfgOfG9oPWtu04o4a152A9BvN3+QP8X/zOfz5REpOfb9eq5SCamcVEmqAf4zoIcHQQFPlOZI30jLpLVwb/ukg/Bt1hq7VdH7WvKUS8vN5TaI/a+BgpvlbKixk/JP8jXEb0WFKLzSWGmrdITz6A3P8bmSokxV5itLoRs2KLuUw8pZ5KOPKqJvFa05YmmSvkTvYcxw1Fyke1PjrH4l68kOUpMOBdt9Aac2nz5OW7PznZh+zGimP7efE/gFfIqwUNgk/CCcEi6INaQc5bB6Xt2i08ZXxgxjjjHf+MZYaqw01hjroZy2GjuRn99B7x013hh9zRN2pUcu+DjPvPHXZ11kedtrGdazLjzhedZAWfnQvrRfYU1HEB1M//WZEb8ytxlPtjhbmQ1mm7Ph7HJ2Nfstu509yP7AnoX2sua8I9T2aic4hB5wX59BOy1RV0CrcqZhdoDy7A1sPmGeheb0tnN9HzlJbtJ36Uf0n7QnU5SpwFRh/mR2Cd8J1ox6oFxDLqaX0Evr1fVaej3d0BtCJ1I53tQwZ4r6f+IJJY7apn93l/SH++jfrSr+
*/