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