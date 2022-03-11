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