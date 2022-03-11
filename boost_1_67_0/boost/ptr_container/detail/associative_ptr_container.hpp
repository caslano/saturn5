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