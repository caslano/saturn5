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
dluz3Q9sazpt6/pznzgoMH+pzV/m/hapbpUZ+nsSv3W/Op2TlvnwKvvVDaOjSIW5sAUcCdvB0bAzPAYOg2NgLpwLj4Hj4Hg4Hp4EJ8DZcA5cAYvgOjgLPqfxXoSFcKPad8Eio3PEsESvrwGcHLw3nBrD6TAdFsBMWAjbwRm6BnwmHC3pBa7nFDhN7TPVvgtWGp2DhYmqz9ZNd6Web5Du35cDD1B7e7UXwCGwCA6Fxbp2fL6uHT9b144vgSNUhnQkvByOUt0Do+EKeAx8EI6Bm2AefBOOg1vhBPgRPFave5FP5wN1nnSRI2mZcp2nn0d+toZl8CDXHU6CT8Ai+Cgsho/BMvgsPAM+BxfDb+GN8CJ4i3TCAb28fvgneBruz8LT4SZYAd+AC+Db8Ay4FS6C2+Bi+AVcAvfBc6Hjjn9hHLwAJsGLYBa8BHaH5XAs/C08Hi6D+fAqOBP+Dp4Lr4YXwuXwcngtvAbeBP8Afw/vhDfAP6r7Q/Bm+AS8BW6GK+FWeBt8H94Od8A7YQMf70YwHVbCdnA1HATXwCPh/XA4fADOgA/C2XAtPB0+DM+Gj8HfwRfhvfAl+BB8GT4BN8D18BX4MnwNvglfhW+r/WP4JtwB/w6/hG/Bb+DbMIV68Q5sDt+FreGHsCt8D/aC78N+6n4E3AaPgp/A0fBTOA5uh5PgDlgA3XqwS+qFzrXpHKVbDw/n9x7oHgm+QLtMhJ1hfTgUNoDD4CR4HEyGJbARvBI2hjfAFPgMTIUvwTS4G6bD72ET2MHdixR2hxlwPGwGT4CZcAlsDs+DLeD9sCV8GLaFb8BJcBtsDeO5p4mQaxT3FrAD7A47wYNhZ3ic+s+AB8IFsCv8DewGb1b/e2FP+CzsBZ+HveFW2BfWIz/7wQbwYNgEHgIzoBu/MzwMHgoHwmHwcFgEB8FTNNwZMAder/Y18Ej4BDwKvgiHwU3waPgmHA6/1fBJcfRPsD0cA3vDPDgAjoPT4Xg4E06AC+EkrQdLg3M1sJX2o42M6HKQo7tDOcGesA/MhkfAXrAE9obzYR94Heyn/c8h8BU4EL4KD4e74RHwKzgYfgeHaH9yJNTnnH7Pp45E2Zc1TZ9rTWAv2BQeDjPgCNgMjlH7WLWfATPhObA5fBQeAF+C7eDLsD3cATtqf9cZ7oVd4LcwS69votFv1fodfFHEWogeqgc+G3aCveBBcADMhn3gwfAQ6MY5DE5W/13wDaPfguHXmn4mfFHTn+yjX4Anww4wHx4Ep8E+cDocDgvgSLgA5sMZcBacCefAWfAMeAr8DZwNL4DF8LewRNvzXHgjLIUr4KnwZjgP3g/L4OOwHD4N58NN8HS4GVbAbXIdqkvGfteUa5f76xDIdznm6vN6no4HyuFQOF/XfJwGz3TT1+fzGfpcXqi6X87W5/Fi+DhcAp+H58JXjOoegefDBu7zC6bBC2E7eBEcDC+Gw+GlcCK8DBbD38Lz4OW63+2V8F74O/gIvAY+CZfDP8Nr4Wb4e5jA/a6AreFKeAC8FQ6At8Mj4B3wKHgnHAFXa73YEvy2BZ/XduHWA/Jaji06jnoPHgo/gMPgh1rPPoKnwm1wEfxEdSZ9Cu+E2+G9cAfcCOMd2W9AdAVt0f2VP4e7dX/gL2EK/Ar2gd/AgfA7OAga4s+FPngRjIOXwUR4K0yCa2B9eBdsqO1rp/1GwTNX77Ol3E/gqNRx3b2wK7wf9oQPaD15EI5XHVAnwrV6v4/qvsiPw9vgE3A9fAq+rLqeNsN1qvvpORjPudfDRvDPsDX8C8yCL8JC1eVUAjfCU+EmWKY6na6Er8Nr4Bvw9/BN1f30d3gbfEvLV+aYdY3VcdruEyD3JMdEHT8=
*/