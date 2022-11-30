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
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
*/