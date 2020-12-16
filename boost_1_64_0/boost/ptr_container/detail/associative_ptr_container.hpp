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
3ztIEIbNFmGRjquJ0sw491Ib4eST8PdSJuUdO/VRuG43iNJxF0ZhZjRGqKjHIsF3pu0KOpob03EXizDwgo72heOkPt88UydoldCaX5CWiSbR3pOqmCssnF1VYumV5hgae16/BRqLQNfTfr+4NZtOT+vLPtEWm5aU9fi6w5u0n1FGGBMNWh+Hfk8HWNHiwBfI7Z491y98Z9vzR4U9j2zA3v2DOxzte8JWkC93YWfdu7dqoP0ml5wvjH1fK2N/23LiM2YNCml8lv3BKps4L4bPktetdSYm/LPmTJ4R9RPvOg0Ub8ybJUXZHgcTjlT4zVSgB52CB+ZNdX3KJSX2MR5q0uzwtz6J+YyjwLPfeUMRjDDPCgndeHPc28loCv1SnkjzmLg0tWowryaLNFfH0ppdQGK8fVxnaeZHuuz4zmhQoa1sUR3+o3S+T8LC3rJkk+wnJ3ZK394o17lO7rSM+tCs2u7H6fRLtnL96NTOaRtbfS0leHlaHK3Y1OrL7TnQnN0c+N+DjCyfB+bf/dXoY93qrwbLkuf3YuV5gT/moGe1tXADQqPZ+i303uXk37QoMXl2eVEV907o89WNNILsw1cJHVQ2NSIJw6/PDCczf2Y5sgs3Z4RnvhtzO2F6F7V1Z9Hd4OZtPbo/m0XY7dvGbnopG/cNlHdu2nTybIrJo1XsPZB4fWPKnKEQb5XH7MUyajys9/0D4/ZrRfV+gHC/yYJrjOlTgqePCJ4w7xc+mCbOopl5P9Fq6bmJgWaNxxyilWcE7HPOWIZYHMWWzut98gpe8/Utq36Y9xN591r4rgQMYK7RnIwWOlHQEB6sQIR5Pqb955YGXUnhR10S6HV2VUblexKsblFLK0WkENE6zI2WjNrjtQsMn9M7s0W//M7oTfEQh3HGanClorZ6wcrDX6oJw17KkN/Mu5NfyYxnHsSIwl/LjGuCzX1QhJ2yJz4ldIO71/d5nztunnLD3nF9/+PAp5FXEulrDsK2/cdA8fa6WQzWuxoZDqTP6g2U9/s01tvrjV8SziVI+nEK6Zd+BW7OZ2qh4Lh5mp/fBGFCO8bcQWjOioq8xP74Vck2MTf6w8DwPRJjFc0zJ6EMeDnWPUI8p8+fQW8W/FonpONscGlR+JRXJCO/yAn5tdQ3PljqxWk+rRuGhSF4MVJXrRdfBs16qRfWN3QyXN4fsJEJBxO7Q8XcRhQOo1K8sEQfa43686ZhOEttjXV61GEOdUX1/B5+Bl6AeU5KtE9P4ptBPldq6MzT9rJ3mHYlq/FlJZqBOgP/HA8DEdlnq3qKd/3NfMXWdtiUkvKSikllpQtKiiOyKI3Nw/z8k1DmCc4wbIvMeuqVrTD9gVFbpFo1F6Mdu9LvyZV0LfRcM/yS7TUoS2Yyz1AMzrH7YHSVSEizZY61n0jM4YT5bJ2VjvUu6EDz5h4aQvdVwadPZJhp0fQdXDnpfQGQmAGPaKdvieur7uiCLDFnqXW4CBF82Z50GR2aTEMGRnI4zO4PWlB0G0bnPy0ae30yn3B5x5f9bngB4VoTGH0QxnPAffvZWdlG2u1ueojsz3f0iqfxvR9JN8pOS0+RBFIp+TXG0JkNblnvyY7LkGczhha8mEC4rr6uVHgRlXjzIUYOO8S9xLtmhWefby2UddGrPKbSohzFmfXQR0f9PfmDI74JexLPs716x/f/sH1zstJqazKbRHVSUnaNDQqPqaf9kpKcKAwrm44zJce8SyfEOsxvWlg3X7CRST+yLHeZkMfwwCHDj2QNiUg+ltt0ekhBgvK8aVZeme8WVlhpaG1g/IrZhDF4VD38OWSDzQXz5/k3ccC65Wsgq3vG+Roze8et3S7IEe9D+QKUqPQ7ZXk=
*/