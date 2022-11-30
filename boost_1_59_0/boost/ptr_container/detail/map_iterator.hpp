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

#ifndef BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <utility>

#if defined(BOOST_MSVC)  
# pragma warning(push)  
# pragma warning(disable:4512)    // Assignment operator could not be generated.  
#endif 

namespace boost
{ 
    namespace ptr_container_detail
    {
        template< class F, class S >
        struct ref_pair
        {
            typedef F first_type;
            typedef S second_type;

            const F& first;
            S        second;

            template< class F2, class S2 >
            ref_pair( const std::pair<F2,S2>& p )
            : first(p.first), second(static_cast<S>(p.second))
            { }

            template< class RP >
            ref_pair( const RP* rp )
            : first(rp->first), second(rp->second)
            { }

            const ref_pair* operator->() const
            {
                return this;
            }

            friend inline bool operator==( ref_pair l, ref_pair r )
            {
                return l.first == r.first && 
                       boost::equal_pointees( l.second, r.second );
            }

            friend inline bool operator!=( ref_pair l, ref_pair r )
            {
                return !( l == r );
            }

            friend inline bool operator<( ref_pair l, ref_pair r )
            {
                if( l.first == r.first )
                    return boost::less_pointees( l.second, r.second );
                else 
                    return l.first < r.first;
            }

            friend inline bool operator>( ref_pair l, ref_pair r )
            {
                return r < l;
            }

            friend inline bool operator<=( ref_pair l, ref_pair r )
            {
                return !(r < l);
            }

            friend inline bool operator>=( ref_pair l, ref_pair r )
            {
                return !(l < r);
            }

        };
    }
    
    template< 
              class I, // base iterator 
              class F, // first type, key type
              class S  // second type, mapped type
            > 
    class ptr_map_iterator : 
        public boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                        ptr_container_detail::ref_pair<F,S>, 
                                        use_default, 
                                        ptr_container_detail::ref_pair<F,S> >
    {
        typedef boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                         ptr_container_detail::ref_pair<F,S>,
                                         use_default, 
                                         ptr_container_detail::ref_pair<F,S> > 
            base_type;


    public:
        ptr_map_iterator() : base_type()                                 
        { }
        
        explicit ptr_map_iterator( const I& i ) : base_type(i)
        { }

        template< class I2, class F2, class S2 >
            ptr_map_iterator( const ptr_map_iterator<I2,F2,S2>& r ) 
         : base_type(r.base())
        { }
        
   }; // class 'ptr_map_iterator'

}

#if defined(BOOST_MSVC)  
# pragma warning(pop)  
#endif 

#endif

/* map_iterator.hpp
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
*/