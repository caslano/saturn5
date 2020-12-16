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

#ifndef BOOST_PTR_CONTAINER_PTR_ARRAY_HPP
#define BOOST_PTR_CONTAINER_PTR_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    namespace ptr_container_detail
    {
        template
        <
            class T,
            size_t N,
            class Allocator = int // dummy
        >
        class ptr_array_impl : public boost::array<T,N>
        {
        public:
            typedef Allocator allocator_type;

            ptr_array_impl( Allocator /*a*/ = Allocator() )
            {
                this->assign( 0 );
            }

            ptr_array_impl( size_t, T*, Allocator /*a*/ = Allocator() )
            {
                this->assign( 0 );
            }
        };
    }

    template
    <
        class T,
        size_t N,
        class CloneAllocator = heap_clone_allocator
    >
    class ptr_array : public
        ptr_sequence_adapter< T,
            ptr_container_detail::ptr_array_impl<
                typename ptr_container_detail::void_ptr<T>::type,N>,
                              CloneAllocator >
    {
    private:
        typedef ptr_sequence_adapter< T,
            ptr_container_detail::ptr_array_impl<
                typename ptr_container_detail::void_ptr<T>::type,N>,
                                      CloneAllocator >
            base_class;

        typedef BOOST_DEDUCED_TYPENAME remove_nullable<T>::type U;

        typedef ptr_array<T,N,CloneAllocator>
                          this_type;

    public:
        typedef std::size_t size_type;
        typedef U*          value_type;
        typedef U*          pointer;
        typedef U&          reference;
        typedef const U&    const_reference;
        typedef BOOST_DEDUCED_TYPENAME base_class::auto_type
                            auto_type;

    public: // constructors
        ptr_array() : base_class()
        { }

        ptr_array( const ptr_array& r )
        {
            size_t i = 0;
            for( ; i != N; ++i )
                this->base()[i] = this->null_policy_allocate_clone( 
                                        static_cast<const U*>( &r[i] ) ); 
        }

        template< class U >
        ptr_array( const ptr_array<U,N>& r )
        {
            size_t i = 0;
            for( ; i != N; ++i )
                this->base()[i] = this->null_policy_allocate_clone( 
                                        static_cast<const T*>( &r[i] ) ); 
        }

#ifndef BOOST_NO_AUTO_PTR
        explicit ptr_array( std::auto_ptr<this_type> r )
        : base_class( r ) { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        explicit ptr_array( std::unique_ptr<this_type> r )
        : base_class( std::move( r ) ) { }
#endif

        ptr_array& operator=( ptr_array r )
        {
            this->swap( r );
            return *this;            
        }

#ifndef BOOST_NO_AUTO_PTR
        ptr_array& operator=( std::auto_ptr<this_type> r )
        {
            base_class::operator=(r);
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        ptr_array& operator=( std::unique_ptr<this_type> r )
        {
            base_class::operator=(std::move(r));
            return *this;
        }
#endif

#ifndef BOOST_NO_AUTO_PTR
        std::auto_ptr<this_type> release()
        {
            std::auto_ptr<this_type> ptr( new this_type );
            this->swap( *ptr );
            return ptr;
        }

        std::auto_ptr<this_type> clone() const
        {
            std::auto_ptr<this_type> pa( new this_type );
            clone_array_elements( *pa );
            return pa;
        }
#else
        std::unique_ptr<this_type> release()
        {
            std::unique_ptr<this_type> ptr( new this_type );
            this->swap( *ptr );
            return ptr;
        }

        std::unique_ptr<this_type> clone() const
        {
            std::unique_ptr<this_type> pa( new this_type );
            clone_array_elements( *pa );
            return pa;
        }
#endif
    private:
        void clone_array_elements( this_type &pa ) const
        {
            for( size_t i = 0; i != N; ++i )
            {
                if( !this->is_null(i) )
                    pa.replace( i, pa.null_policy_allocate_clone( &(*this)[i] ) );
            }
        }

    private: // hide some members
        using base_class::insert;
        using base_class::erase;
        using base_class::push_back;
        using base_class::push_front;
        using base_class::pop_front;
        using base_class::pop_back;
        using base_class::transfer;
        using base_class::get_allocator;

    public: // compile-time interface

        template< size_t idx >
        auto_type replace( U* r ) // strong
        {
            BOOST_STATIC_ASSERT( idx < N );

            this->enforce_null_policy( r, "Null pointer in 'ptr_array::replace()'" );
            auto_type res( static_cast<U*>(this->base()[idx]), *this ); // nothrow                    
            this->base()[idx] = r;                                      // nothrow
            return boost::ptr_container::move(res);                     // nothrow 
        }

#ifndef BOOST_NO_AUTO_PTR
        template< size_t idx, class V >
        auto_type replace( std::auto_ptr<V> r )
        {
            return replace<idx>( r.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< size_t idx, class V >
        auto_type replace( std::unique_ptr<V> r )
        {
            return replace<idx>( r.release() );
        }
#endif

        auto_type replace( size_t idx, U* r ) // strong
        {
            this->enforce_null_policy( r, "Null pointer in 'ptr_array::replace()'" );

            auto_type ptr( r, *this );
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( idx >= N, bad_index,
                                                 "'replace()' aout of bounds" );

            auto_type res( static_cast<U*>(this->base()[idx]), *this ); // nothrow
            this->base()[idx] = ptr.release();                          // nothrow
            return boost::ptr_container::move(res);                     // nothrow 
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class V >
        auto_type replace( size_t idx, std::auto_ptr<V> r )
        {
            return replace( idx, r.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class V >
        auto_type replace( size_t idx, std::unique_ptr<V> r )
        {
            return replace( idx, r.release() );
        }
#endif

        using base_class::at;

        template< size_t idx >
        T& at()
        {
            BOOST_STATIC_ASSERT( idx < N );
            return (*this)[idx];
        }

        template< size_t idx >
        const T& at() const
        {
            BOOST_STATIC_ASSERT( idx < N );
            return (*this)[idx];
        }

        bool is_null( size_t idx ) const
        {
            return base_class::is_null(idx);
        }

        template< size_t idx >
        bool is_null() const
        {
            BOOST_STATIC_ASSERT( idx < N );
            return this->base()[idx] == 0;
        }
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, size_t size, typename CA >
    inline ptr_array<T,size,CA>* new_clone( const ptr_array<T,size,CA>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, size_t size, typename CA >
    inline void swap( ptr_array<T,size,CA>& l, ptr_array<T,size,CA>& r )
    {
        l.swap(r);
    }
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_array.hpp
l4A5v7ExUM/SECks0IwU+pbn+E3y2CL5PK9S2TzjcEqV5zwtoXANxeXtIm3vTvPRp6KntnY+14H66o6XrY/gf/YmgQO9pDJ64N9R7TuTfW9IwpGGcWMlqhMMH8+kNEkSlPb2IEqT6E9wfCJRDuhP5Z600xJ1JVpTWqKP83on+k2091RmIi3R3kq7nGpvEOH/0yibCvxHDqE//iN9QM7JhbIkAxL79YtFQgZUVObj3vIMb+WMOO+ntJkV8NQo83rVUTblmZRXVlFRZTlz2vfOXVZeVWlRaZGsibvv8g44xXjj9TwFuPAsC6i8TlZeUXGxZyrckrdNZGfkmzJphJ5wOBQujTXMC4QtnqynSp5M+5Ze6s6hwosXSGdJsdaZ5pxbAdEjpUHCR9lAmrT8WIk0V5nmrSrnMdFTZFqFpwQOwF6kFsXlTCrSLTfqEiSRPzPSZFgQOKiUVVCa20qrVO2WVQASFOtB9V+WP4P6OVF+F+eCCsrFSCajXsR8cESDTOlH67FAwRLoHQF2hlAAvxSbV6Wo7xx2fiC/x4g4Hqaq77FiKNnIX06m+6lV9GCz+g+d1QIHceuc6NtXicebsbJ5wApAeGZRBWTtzDETJ9rHS+CmI2J0/qklTmmluvLhN9icdN6n3oIsD4Xqhfo+tYecR771xs/UcCjWRLwN5bonpef78SJjfT6eLJiHLTTRHvRYOdcKf3WgoD7OS/dF3QyRi1f3mtVdd3XFc5F1dj0ceX1EYbARTzQco3ITLW5LA3ReAQz1uVJfKm8AnZsdLePgiXjd8nAwFA5GF9vyaQjJq+nqLb8081W2NsNag71ardYBey7aUutHPx1cRz0lQqeJWuKUDiy11Mn4WluHNhKOrxMcecsER5mHn4jER3z16fwGvlPaP48O4yPgJqneHJku6KdD/f1H4JZFcLOGdHQsRGez6Wps4UADysTP9d7OTDojrK8JNvus0yj6Hy3G2+vJ26PvVGpvJLX3TjKfqOcN0ocao4k2VTwE1HmX1ZE6fHU46qv1w44VaJQqSo2vMVZf3xQNUzttFUjo0C+QTjCyNb+DUnVzQ7VHH4m6H1DdZQk54VlUHWiKkztcmgKeRYHqmEyw5cZOZbzwq6qui8sQO780EEH8hsQnvdvD68MXCrOqamyB6wy9sZFCfP8jjA07/XyPckyUkqoc8abk/yQNHfMsmeiog/HW+Gmnnko62Ceabf9Tsn99yOxgH2datv3P8HfurvucWoS9X64+gLaLJNbqCxqP/P9z+j/u//OPTOud3kWEr18qXjAN7h31Aan/zyWc/YrTwO80NjorS7yrvDmJl9EJ9SypW/Mzba96U04lb+f7k0r/fK1sd6FUnrLa2kggytLTrHRvoD5QHQ3ZPj0ZSp5TcdZ2H5WeKK7Sv1ayqCIwPwhEDeeGA35b9tQLL2I7BEahDXl+rvSR7Qx+TfBhKS4DOEqn4gWomXJ77slVQHNIb83vroNtEKwTNrQbk3QEktCW+GCwLgiP4ntAfI/m8MV3Docrvsew7wx8j2PfffB9MH1/q+BXWB/yR73+Ztv/4CzhDcyfGkl8nyO/C+3v8+S3x/6+UH4X2N+XCE9NkPV5mfBE+Pca4ZnHfY2vRnn+fb3wVPPvm4XHz7/Xo34T+75TeIL8+145nnx7PA8Kj4Iqx6dHMCZe5wlZx2vV+Q5weQZ8DjExwN7i+BVRPLqvfPOF4dEzZus8Om6LS5H3otPoTRS2B4zfxZgEuruW0x3nsTX2uqTY6Xw+irel2nmIc0M0SLphdzsvt6YmHIhEBMMXazcCzyfIbUyT8n5GmxlUj0IlhRv8lhyI+9j9wuBQ3gH+zHkyeJ/Ok9VMd7A=
*/