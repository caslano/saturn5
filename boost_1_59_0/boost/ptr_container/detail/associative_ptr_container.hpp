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


#ifndef BOOST_PTR_CONTAINER_DETAIL_ASSOCIATIVE_PTR_CONTAINER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_ASSOCIATIVE_PTR_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
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
        class Config,
        class CloneAllocator
    >
    class associative_ptr_container :
        public reversible_ptr_container<Config,CloneAllocator>
    {
        typedef reversible_ptr_container<Config,CloneAllocator>
                                base_type;

        typedef BOOST_DEDUCED_TYPENAME base_type::scoped_deleter
                                scoped_deleter;

        typedef BOOST_DEDUCED_TYPENAME Config::container_type
                                container_type;
    public: // typedefs
        typedef BOOST_DEDUCED_TYPENAME Config::key_type
                                key_type;
        typedef BOOST_DEDUCED_TYPENAME Config::key_compare
                                key_compare;
        typedef BOOST_DEDUCED_TYPENAME Config::value_compare
                                value_compare;
        typedef BOOST_DEDUCED_TYPENAME Config::hasher
                                hasher;
        typedef BOOST_DEDUCED_TYPENAME Config::key_equal
                                key_equal;
        typedef BOOST_DEDUCED_TYPENAME Config::iterator
                                iterator;
        typedef BOOST_DEDUCED_TYPENAME Config::const_iterator
                                const_iterator;
        typedef BOOST_DEDUCED_TYPENAME Config::local_iterator
                                local_iterator;
        typedef BOOST_DEDUCED_TYPENAME Config::const_local_iterator
                                const_local_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                                size_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::reference
                                reference;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_reference
                    const_reference;

    public: // foundation
        associative_ptr_container()
        { }

        template< class SizeType >
        associative_ptr_container( SizeType n, unordered_associative_container_tag tag )
          : base_type( n, tag )
        { }

        template< class Compare, class Allocator >
        associative_ptr_container( const Compare& comp,
                                   const Allocator& a )
         : base_type( comp, a, container_type() )
        { }
        
        template< class Hash, class Pred, class Allocator >
        associative_ptr_container( const Hash& hash,
                                   const Pred& pred,
                                   const Allocator& a )
         : base_type( hash, pred, a )
        { }

        template< class InputIterator, class Compare, class Allocator >
        associative_ptr_container( InputIterator first, InputIterator last,
                                   const Compare& comp,
                                   const Allocator& a )
         : base_type( first, last, comp, a, container_type() )
        { }
        
        template< class InputIterator, class Hash, class Pred, class Allocator >
        associative_ptr_container( InputIterator first, InputIterator last,
                                   const Hash& hash,
                                   const Pred& pred,
                                   const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit associative_ptr_container( std::auto_ptr<PtrContainer> r )
         : base_type( r )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit associative_ptr_container( std::unique_ptr<PtrContainer> r )
         : base_type( std::move( r ) )
        { }
#endif

        associative_ptr_container( const associative_ptr_container& r )
         : base_type( r.begin(), r.end(), container_type() )
        { }
        
        template< class C, class V >
        associative_ptr_container( const associative_ptr_container<C,V>& r )
         : base_type( r.begin(), r.end(), container_type() )
        { }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        associative_ptr_container& operator=( std::auto_ptr<PtrContainer> r ) // nothrow
        {
           base_type::operator=( r );
           return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        associative_ptr_container& operator=( std::unique_ptr<PtrContainer> r ) // nothrow
        {
           base_type::operator=( std::move( r ) );
           return *this;
        }
#endif
        
        associative_ptr_container& operator=( associative_ptr_container r ) // strong
        {
           this->swap( r );
           return *this;   
        }

    public: // associative container interface
        key_compare key_comp() const
        {
            return this->base().key_comp();
        }

        value_compare value_comp() const
        {
            return this->base().value_comp();
        }

        iterator erase( iterator before ) // nothrow
        {
            BOOST_ASSERT( !this->empty() );
            BOOST_ASSERT( before != this->end() );

            this->remove( before );                      // nothrow
            iterator res( before );                      // nothrow
            ++res;                                       // nothrow
            this->base().erase( before.base() );         // nothrow
            return res;                                  // nothrow
        }

        size_type erase( const key_type& x ) // nothrow
        {
            iterator i( this->base().find( x ) );       
                                                        // nothrow
            if( i == this->end() )                      // nothrow
                return 0u;                              // nothrow
            this->remove( i );                          // nothrow
            return this->base().erase( x );             // nothrow 
        }

        iterator erase( iterator first,
                        iterator last ) // nothrow
        {
            iterator res( last );                                // nothrow
            if( res != this->end() )
                ++res;                                           // nothrow

            this->remove( first, last );                         // nothrow
            this->base().erase( first.base(), last.base() );     // nothrow
            return res;                                          // nothrow
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    
        template< class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_convertible<Range&,key_type&>, 
                                                  iterator >::type
        erase( const Range& r )
        {
            return erase( boost::begin(r), boost::end(r) );
        }

#endif

    protected:

        template< class AssociatePtrCont >
        void multi_transfer( BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator object,
                             AssociatePtrCont& from ) // strong
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            BOOST_ASSERT( !from.empty() && "Cannot transfer from empty container" );

            this->base().insert( *object.base() );     // strong
            from.base().erase( object.base() );        // nothrow
        }

        template< class AssociatePtrCont >
        size_type multi_transfer( BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator first,
                                  BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator last,
                                  AssociatePtrCont& from ) // basic
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
 
            size_type res = 0;
            for( ; first != last; )
            {
                BOOST_ASSERT( first != from.end() );
                this->base().insert( *first.base() );     // strong
                BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator 
                    to_delete( first );
                ++first;
                from.base().erase( to_delete.base() );    // nothrow
                ++res;
            }

            return res;
        }

        template< class AssociatePtrCont >
        bool single_transfer( BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator object,
                              AssociatePtrCont& from ) // strong
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            BOOST_ASSERT( !from.empty() && "Cannot transfer from empty container" );

            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool> p =
                this->base().insert( *object.base() );     // strong
            if( p.second )
                from.base().erase( object.base() );        // nothrow

            return p.second;
        }

        template< class AssociatePtrCont >
        size_type single_transfer( BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator first,
                                   BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator last,
                                   AssociatePtrCont& from ) // basic
        {
            BOOST_ASSERT( (void*)&from != (void*)this );

            size_type res = 0;
            for( ; first != last; )
            {
                BOOST_ASSERT( first != from.end() );
                std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool> p =
                    this->base().insert( *first.base() );     // strong
                BOOST_DEDUCED_TYPENAME AssociatePtrCont::iterator 
                    to_delete( first );
                ++first;
                if( p.second )
                {
                    from.base().erase( to_delete.base() );   // nothrow
                    ++res;
                }
            }
            return res;
        }
        
        reference front()
        {
            BOOST_ASSERT( !this->empty() );
            BOOST_ASSERT( *this->begin().base() != 0 );
            return *this->begin(); 
        }

        const_reference front() const
        {
            return const_cast<associative_ptr_container*>(this)->front();
        }

        reference back()
        {
            BOOST_ASSERT( !this->empty() );
            BOOST_ASSERT( *(--this->end()).base() != 0 );
            return *--this->end(); 
        }

        const_reference back() const
        {
            return const_cast<associative_ptr_container*>(this)->back();
        }

    protected: // unordered interface
        hasher hash_function() const
        {
            return this->base().hash_function();
        }

        key_equal key_eq() const
        {
            return this->base().key_eq();
        }
        
        size_type bucket_count() const
        {
            return this->base().bucket_count();
        }
        
        size_type max_bucket_count() const
        {
            return this->base().max_bucket_count();
        }
        
        size_type bucket_size( size_type n ) const
        {
            return this->base().bucket_size( n );
        }
        
        float load_factor() const
        {
            return this->base().load_factor();
        }
        
        float max_load_factor() const
        {
            return this->base().max_load_factor();
        }
        
        void max_load_factor( float factor )
        {
            return this->base().max_load_factor( factor );
        }
        
        void rehash( size_type n )
        {
            this->base().rehash( n );
        }

    public:
#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(70190006))
        iterator begin()
        {
            return base_type::begin();
        }

        const_iterator begin() const
        {
            return base_type::begin();
        }

        iterator end()
        {
            return base_type::end();
        }

        const_iterator end() const
        {
            return base_type::end();
        }

        const_iterator cbegin() const
        {
            return base_type::cbegin();
        }

        const_iterator cend() const
        {
            return base_type::cend();
        }
#else
         using base_type::begin;
         using base_type::end;
         using base_type::cbegin;
         using base_type::cend;
#endif

    protected:
        local_iterator begin( size_type n )
        {
            return local_iterator( this->base().begin( n ) );
        }
        
        const_local_iterator begin( size_type n ) const
        {
            return const_local_iterator( this->base().begin( n ) );
        }
        
        local_iterator end( size_type n )
        {
            return local_iterator( this->base().end( n ) );
        }
        
        const_local_iterator end( size_type n ) const
        {
            return const_local_iterator( this->base().end( n ) );
        }
        
        const_local_iterator cbegin( size_type n ) const
        {
            return const_local_iterator( this->base().cbegin( n ) );
        }
        
        const_local_iterator cend( size_type n )
        {
            return const_local_iterator( this->base().cend( n ) );
        }

     }; // class 'associative_ptr_container'
    
} // namespace 'ptr_container_detail'
    
} // namespace 'boost'

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* associative_ptr_container.hpp
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
*/