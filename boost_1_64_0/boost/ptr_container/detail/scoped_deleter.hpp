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
ldCffQ7Pyj6hMjLfqXEqoWzN+NiHyBJCgpm2mpZ2xTSmgH7m1DAl5m9SMG27OUZyFVlc9J1O85l9GD5JvC4VDbVDswcAJa/ck5DtDf0FkbUEaJUKiBEUyQj0OpoJIsUdzJJo88TXqucq8Pd88krFfSbJXxRQWqNZ33M7+VGLBVEKPj3RHL5ZE6E2V56dBxMAs28yz5J4dkSZdA25CW7eOFTFxLkRdksrvV/y1Pi9uYjhr9rkP0MeqsrFCaWB+j/fQo/Of++mCbMdOrj7Ffay4kchkj0ab6TAQLOP17bOOqxQgpaHJsAy3M7QIDedd3/cxW+lLRe2ggSVJr3PXGOojn6le5TFYjspkm6LMHI0tMDtjM3CDJLxBCHVLcbYEfZNwUAXXbtfwVSN5bG8vqpvT2bV9Q1hw2fy6mWp4lop6Wd1+SXxtS90+aVnucSGq2z287OyxW2o79F2DeUPZErJcJ/DSF9XlA4xHltYRNr3iRBPWTpFLy1A3idHNZTW9KbDgGvgmTPexJOg7HwRBMasdkZXZegYrqaEbji3+k/87Auqm+IoaUentZPJAg==
*/