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

#ifndef BOOST_PTR_CONTAINER_SCOPED_DELETER_HPP
#define BOOST_PTR_CONTAINER_SCOPED_DELETER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <iterator>
#include <cstddef>
#include <boost/scoped_array.hpp>

namespace boost
{

    namespace ptr_container_detail
    {
        template< class Container >
        class scoped_deleter
        {
            typedef BOOST_DEDUCED_TYPENAME Container::size_type   size_type;
            typedef BOOST_DEDUCED_TYPENAME Container::object_type T;
            
            Container&        cont_;
            scoped_array<T*>  ptrs_;
            size_type         stored_; 
            bool              released_;
            
        public:
            scoped_deleter( Container& cont, T** a, size_type size ) 
                : cont_(cont), 
                  ptrs_( a ), 
                  stored_( size ), 
                  released_( false )
            { 
                BOOST_ASSERT( a );
            }
            
            scoped_deleter( Container& cont, size_type size ) 
                : cont_(cont), 
                  ptrs_( new T*[size] ), 
                  stored_( 0 ), 
                  released_( false )
            {
                BOOST_ASSERT( size > 0 );
            }


            
            scoped_deleter( Container& cont, size_type n, const T& x ) // strong
                : cont_(cont), 
                  ptrs_( new T*[n] ), 
                  stored_(0),
                  released_( false )
            {
                for( size_type i = 0; i != n; i++ )
                    add( cont_.null_policy_allocate_clone( &x ) );
                BOOST_ASSERT( stored_ > 0 );
            }


            
            template< class InputIterator >
            scoped_deleter ( Container& cont, InputIterator first, InputIterator last  ) // strong
                : cont_(cont),
                  ptrs_( new T*[ std::distance(first,last) ] ),
                  stored_(0),
                  released_( false )
            {
                for( ; first != last; ++first )
                    add( cont_.null_policy_allocate_clone_from_iterator( first ) );
                BOOST_ASSERT( stored_ > 0 );
            }

            
            
            ~scoped_deleter()
            {
                if ( !released_ )
                {
                    for( size_type i = 0u; i != stored_; ++i )
                        cont_.null_policy_deallocate_clone( ptrs_[i] ); 
                }
            }
            
            
            
            void add( T* t )
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                ptrs_[stored_] = t;
                ++stored_;
            }
            
            
            
            void release()
            {
                released_ = true;
            }
            
            
            
            T** begin()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[0];
            }
            
            
            
            T** end()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[stored_];
            }
            
        }; // class 'scoped_deleter'
    }
}

#endif

/* scoped_deleter.hpp
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
*/