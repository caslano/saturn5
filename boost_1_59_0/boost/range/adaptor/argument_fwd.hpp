// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_ARGUMENT_FWD_HPP
#define BOOST_RANGE_ADAPTOR_ARGUMENT_FWD_HPP

#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4512) // assignment operator could not be generated
#endif

namespace boost
{
    namespace range_detail
    {  
        template< class T >
        struct holder
        {
            T val;
            holder( T t ) : val(t)
            { }
        };

        template< class T >
        struct holder2
        {
            T val1, val2;
            holder2( T t, T u ) : val1(t), val2(u)
            { }
        };
        
        template< template<class> class Holder >
        struct forwarder
        {
            template< class T >
            Holder<T> operator()( T t ) const
            {
                return Holder<T>(t);
            }
        };

        template< template<class> class Holder >
        struct forwarder2
        {
            template< class T >
            Holder<T> operator()( T t, T u ) const
            {
                return Holder<T>(t,u);
            }
        };

        template< template<class,class> class Holder >
        struct forwarder2TU
        {
            template< class T, class U >
            Holder<T, U> operator()( T t, U u ) const
            {
                return Holder<T, U>(t, u);
            }
        };


    } 
        
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* argument_fwd.hpp
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
*/