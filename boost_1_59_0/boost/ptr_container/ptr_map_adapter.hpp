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

#ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_MAP_ADAPTER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_PTR_MAP_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/detail/map_iterator.hpp>
#include <boost/ptr_container/detail/associative_ptr_container.hpp>
#include <boost/ptr_container/detail/meta_functions.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/static_assert.hpp>
#include <boost/range/iterator_range.hpp>

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
        class VoidPtrMap,
        bool  Ordered
    >
    struct map_config
    {
        typedef BOOST_DEDUCED_TYPENAME remove_nullable<T>::type
                     U;
        typedef VoidPtrMap 
                     void_container_type;
        
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMap::allocator_type
                     allocator_type;
        
       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered, 
                          select_value_compare<VoidPtrMap>, 
                          mpl::identity<void> >::type
                    value_compare;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered, 
                          select_key_compare<VoidPtrMap>, 
                          mpl::identity<void> >::type
                    key_compare;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered,
                          mpl::identity<void>,
                          select_hasher<VoidPtrMap> >::type
                    hasher;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered,
                          mpl::identity<void>,
                          select_key_equal<VoidPtrMap> >::type
                    key_equal;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::if_c<Ordered,
                     ptr_container_detail::ordered_associative_container_tag,
                     ptr_container_detail::unordered_associative_container_tag>::type
                    container_type;
        
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMap::key_type
                     key_type;
        
        typedef U    value_type;

        typedef ptr_map_iterator< BOOST_DEDUCED_TYPENAME VoidPtrMap::iterator, key_type, U* const >
                     iterator;
        
        typedef ptr_map_iterator< BOOST_DEDUCED_TYPENAME VoidPtrMap::const_iterator, key_type, const U* const>
                     const_iterator;
        
        typedef ptr_map_iterator<
           BOOST_DEDUCED_TYPENAME 
             mpl::eval_if_c<Ordered, 
                            select_iterator<VoidPtrMap>,
                            select_local_iterator<VoidPtrMap> >::type,
             key_type, U* const >
                    local_iterator;

       typedef ptr_map_iterator<
           BOOST_DEDUCED_TYPENAME 
             mpl::eval_if_c<Ordered, 
                            select_iterator<VoidPtrMap>,
                            select_const_local_iterator<VoidPtrMap> >::type,
             key_type, const U* const >
                    const_local_iterator;  
       
        template< class Iter >
        static U* get_pointer( Iter i )
        {
            return i->second;
        }

        template< class Iter >
        static const U* get_const_pointer( Iter i )
        {
            return i->second;
        }

        BOOST_STATIC_CONSTANT( bool, allow_null = boost::is_nullable<T>::value );
    };
    
    

    template
    < 
        class T,
        class VoidPtrMap, 
        class CloneAllocator,
        bool  Ordered
    >
    class ptr_map_adapter_base : 
        public ptr_container_detail::associative_ptr_container< map_config<T,VoidPtrMap,Ordered>,
                                                    CloneAllocator >
    {
        typedef ptr_container_detail::associative_ptr_container< map_config<T,VoidPtrMap,Ordered>,
                                                     CloneAllocator > 
            base_type;

        typedef map_config<T,VoidPtrMap,Ordered>                           config;
        typedef ptr_map_adapter_base<T,VoidPtrMap,CloneAllocator,Ordered>  this_type;
        
    public:

        typedef BOOST_DEDUCED_TYPENAME base_type::allocator_type
                    allocator_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator
                    iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator
                    const_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                    size_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::key_type
                    key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                    auto_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::value_type 
                    mapped_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::reference
                    mapped_reference;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_reference
                    const_mapped_reference;
        typedef BOOST_DEDUCED_TYPENAME iterator_value<iterator>::type
                    value_type;
        typedef value_type
                    reference;
        typedef BOOST_DEDUCED_TYPENAME iterator_value<const_iterator>::type
                    const_reference;
        typedef value_type 
                    pointer;
        typedef const_reference 
                    const_pointer;

    private:
        const_mapped_reference lookup( const key_type& key ) const
        {
           const_iterator i = this->find( key );
           BOOST_PTR_CONTAINER_THROW_EXCEPTION( i == this->end(), bad_ptr_container_operation,
                                                "'ptr_map/multimap::at()' could"
                                                " not find key" );
           return *i->second;
        }

        struct eraser // scope guard
        {
            bool            released_;
            VoidPtrMap*     m_;
            const key_type& key_;

            eraser( VoidPtrMap* m, const key_type& key ) 
              : released_(false), m_(m), key_(key)
            {}

            ~eraser() 
            {
                if( !released_ )
                    m_->erase(key_);
            }

            void release() { released_ = true; }

        private:  
            eraser& operator=(const eraser&);  
        };

        mapped_reference insert_lookup( const key_type& key )
        {
            void*& ref = this->base()[key];
            if( ref )
            {
                return *static_cast<mapped_type>(ref);
            }
            else
            {
                eraser e(&this->base(),key);      // nothrow
                mapped_type res = new T();        // strong 
                ref = res;                        // nothrow
                e.release();                      // nothrow
                return *res;
            }
          }
        
    public:

        ptr_map_adapter_base()
        { }

        template< class SizeType >
        explicit ptr_map_adapter_base( SizeType n, 
                                       ptr_container_detail::unordered_associative_container_tag tag )
        : base_type( n, tag )
        { }

        template< class Compare, class Allocator >
        ptr_map_adapter_base( const Compare& comp,
                              const Allocator& a ) 
        : base_type( comp, a ) 
        { }

        template< class Hash, class Pred, class Allocator >
        ptr_map_adapter_base( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }
                
        template< class InputIterator >
        ptr_map_adapter_base( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }
                
        template< class InputIterator, class Comp >
        ptr_map_adapter_base( InputIterator first, InputIterator last,
                              const Comp& comp,
                              const allocator_type& a = allocator_type() )
        : base_type( first, last, comp, a )
        { }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_map_adapter_base( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }
                
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit ptr_map_adapter_base( std::auto_ptr<PtrContainer> clone )
        : base_type( clone )
        { }

        template< typename PtrContainer >
        ptr_map_adapter_base& operator=( std::auto_ptr<PtrContainer> clone )
        {
            base_type::operator=( clone );
            return *this;
        }        
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit ptr_map_adapter_base( std::unique_ptr<PtrContainer> clone )
        : base_type( std::move( clone ) )
        { }

        template< typename PtrContainer >
        ptr_map_adapter_base& operator=( std::unique_ptr<PtrContainer> clone )
        {
            base_type::operator=( std::move( clone ) );
            return *this;
        }
#endif

        iterator find( const key_type& x )                                                
        {                                                                            
            return iterator( this->base().find( x ) );                                
        }                                                                            

        const_iterator find( const key_type& x ) const                                    
        {                                                                            
            return const_iterator( this->base().find( x ) );                          
        }                                                                            

        size_type count( const key_type& x ) const                                        
        {                                                                            
            return this->base().count( x );                                           
        }                                                                            
                                                                                     
        iterator lower_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().lower_bound( x ) );                         
        }                                                                            
                                                                                     
        const_iterator lower_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->base().lower_bound( x ) );                   
        }                                                                            
                                                                                     
        iterator upper_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().upper_bound( x ) );                         
        }                                                                            
                                                                                     
        const_iterator upper_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->base().upper_bound( x ) );                   
        }                                                                            
                                                                                     
        iterator_range<iterator> equal_range( const key_type& x )                    
        {                                                                            
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,
                      BOOST_DEDUCED_TYPENAME base_type::ptr_iterator>
                 p = this->base().equal_range( x );   
            return make_iterator_range( iterator( p.first ), iterator( p.second ) );      
        }                                                                            
                                                                                     
        iterator_range<const_iterator> equal_range( const key_type& x ) const  
        {                                                                            
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_const_iterator,
                      BOOST_DEDUCED_TYPENAME base_type::ptr_const_iterator> 
                p = this->base().equal_range( x ); 
            return make_iterator_range( const_iterator( p.first ), 
                                        const_iterator( p.second ) );    
        }                                                                            
                                                                                     
        mapped_reference at( const key_type& key )  
        {   
            return const_cast<mapped_reference>( lookup( key ) ); 
        }
                                                                                     
        const_mapped_reference at( const key_type& key ) const
        {                                                                            
            return lookup( key );
        }

        mapped_reference operator[]( const key_type& key )
        {
            return insert_lookup( key );
        }              

        auto_type replace( iterator where, mapped_type x ) // strong  
        { 
            BOOST_ASSERT( where != this->end() );
            this->enforce_null_policy( x, "Null pointer in 'replace()'" );

            auto_type ptr( x, *this );
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( this->empty(),
                                                 bad_ptr_container_operation,
                                                 "'replace()' on empty container" );

            auto_type old( where->second, *this ); // nothrow
            where.base()->second = ptr.release();  // nothrow, commit
            return boost::ptr_container::move( old );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        auto_type replace( iterator where, std::auto_ptr<U> x )
        {
            return replace( where, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        auto_type replace( iterator where, std::unique_ptr<U> x )
        {
            return replace( where, x.release() );
        }
#endif

    protected:
        size_type bucket( const key_type& key ) const
        {
            return this->base().bucket( key );
        }
    };
    
} // ptr_container_detail

    /////////////////////////////////////////////////////////////////////////
    // ptr_map_adapter
    /////////////////////////////////////////////////////////////////////////
    
    template
    < 
        class T,
        class VoidPtrMap, 
        class CloneAllocator = heap_clone_allocator,
        bool  Ordered        = true
    >
    class ptr_map_adapter : 
        public ptr_container_detail::ptr_map_adapter_base<T,VoidPtrMap,CloneAllocator,Ordered>
    {
        typedef ptr_container_detail::ptr_map_adapter_base<T,VoidPtrMap,CloneAllocator,Ordered> 
            base_type;
    
    public:    
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator 
                     iterator;       
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator
                     const_iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                    size_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::key_type
                    key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_reference
                    const_reference;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                    auto_type;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMap::allocator_type 
                    allocator_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::mapped_type
                    mapped_type;
    private:

        void safe_insert( const key_type& key, auto_type ptr ) // strong
        {
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool>
                res = 
                this->base().insert( std::make_pair( key, ptr.get() ) ); // strong, commit      
            if( res.second )                                             // nothrow     
                ptr.release();                                           // nothrow
        }

        template< class II >                                               
        void map_basic_clone_and_insert( II first, II last )                  
        {       
            while( first != last )                                            
            {                                            
                if( this->find( first->first ) == this->end() )
                {
                    const_reference p = *first.base();     // nothrow                    
                    auto_type ptr( this->null_policy_allocate_clone(p.second), *this ); 
                                                           // strong 
                    this->safe_insert( p.first, 
                                       boost::ptr_container::move( ptr ) );
                                                           // strong, commit 
                }
                ++first;                                                      
            }                                                                 
        }
    
    public:
        ptr_map_adapter( )
        { }

        template< class Comp >
        explicit ptr_map_adapter( const Comp& comp,
                                  const allocator_type& a ) 
          : base_type( comp, a ) { }

        template< class SizeType >
        explicit ptr_map_adapter( SizeType n,
            ptr_container_detail::unordered_associative_container_tag tag ) 
          : base_type( n, tag ) { }

        template< class Hash, class Pred, class Allocator >
        ptr_map_adapter( const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
         : base_type( hash, pred, a )
        { }
                
        template< class InputIterator >
        ptr_map_adapter( InputIterator first, InputIterator last )
        {
            map_basic_clone_and_insert( first, last ); 
        }
               
        template< class InputIterator, class Comp >
        ptr_map_adapter( InputIterator first, InputIterator last, 
                         const Comp& comp,
                         const allocator_type& a = allocator_type() )
          : base_type( comp, a ) 
        {
            map_basic_clone_and_insert( first, last );
        }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_map_adapter( InputIterator first, InputIterator last,
                         const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
          : base_type( hash, pred, a )
        {
            map_basic_clone_and_insert( first, last ); 
        }
                
        ptr_map_adapter( const ptr_map_adapter& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }
        
        template< class Key, class U, class CA, bool b >
        ptr_map_adapter( const ptr_map_adapter<Key,U,CA,b>& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        ptr_map_adapter( std::auto_ptr<U> r ) : base_type( r )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        ptr_map_adapter( std::unique_ptr<U> r ) : base_type( std::move( r ) )
        { }
#endif

        ptr_map_adapter& operator=( ptr_map_adapter r )
        {
            this->swap( r );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        ptr_map_adapter& operator=( std::auto_ptr<U> r )
        {
            base_type::operator=( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        ptr_map_adapter& operator=( std::unique_ptr<U> r )
        {
            base_type::operator=( std::move( r ) );
            return *this;
        }
#endif

        using base_type::release;

        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            map_basic_clone_and_insert( first, last );
        }

        template< class Range >
        void insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }

    private:
        std::pair<iterator,bool> insert_impl( const key_type& key, mapped_type x ) // strong
        {
            this->enforce_null_policy( x, "Null pointer in ptr_map_adapter::insert()" );

            auto_type ptr( x, *this );                                  // nothrow
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool>
                 res = this->base().insert( std::make_pair( key, x ) ); // strong, commit      
            if( res.second )                                            // nothrow     
                ptr.release();                                          // nothrow
            return std::make_pair( iterator( res.first ), res.second ); // nothrow        
        }

        iterator insert_impl( iterator before, const key_type& key, mapped_type x ) // strong
        {
            this->enforce_null_policy( x, 
                  "Null pointer in 'ptr_map_adapter::insert()'" );
            
            auto_type ptr( x, *this );  // nothrow
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                res = this->base().insert( before.base(), std::make_pair( key, x ) );
                                        // strong, commit        
            ptr.release();              // notrow
            return iterator( res );                       
        }
        
    public:
        
        std::pair<iterator,bool> insert( key_type& key, mapped_type x )
        {
            return insert_impl( key, x );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        std::pair<iterator,bool> insert( const key_type& key, std::auto_ptr<U> x )
        {
            return insert_impl( key, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        std::pair<iterator,bool> insert( const key_type& key, std::unique_ptr<U> x )
        {
            return insert_impl( key, x.release() );
        }
#endif

        template< class F, class S >
        iterator insert( iterator before, ptr_container_detail::ref_pair<F,S> p ) // strong
        {
            this->enforce_null_policy( p.second, 
                  "Null pointer in 'ptr_map_adapter::insert()'" );
 
            auto_type ptr( this->null_policy_allocate_clone(p.second), *this ); 
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                result = this->base().insert( before.base(), 
                                     std::make_pair(p.first,ptr.get()) ); // strong
            if( ptr.get() == result->second )
                ptr.release();
    
            return iterator( result );
        }

        iterator insert( iterator before, key_type& key, mapped_type x ) // strong
        {
            return insert_impl( before, key, x );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( iterator before, const key_type& key, std::auto_ptr<U> x ) // strong
        {
            return insert_impl( before, key, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( iterator before, const key_type& key, std::unique_ptr<U> x ) // strong
        {
            return insert_impl( before, key, x.release() );
        }
#endif
        
        template< class PtrMapAdapter >
        bool transfer( BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator object, 
                       PtrMapAdapter& from ) // strong
        {
            return this->single_transfer( object, from );
        }

        template< class PtrMapAdapter >
        size_type transfer( BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator first, 
                            BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator last, 
                            PtrMapAdapter& from ) // basic
        {
            return this->single_transfer( first, last, from );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    

        template< class PtrMapAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                            BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator >,
                                                            size_type >::type
        transfer( const Range& r, PtrMapAdapter& from ) // basic
        {
            return transfer( boost::begin(r), boost::end(r), from );
        }
        
#endif

        template< class PtrMapAdapter >
        size_type transfer( PtrMapAdapter& from ) // basic
        {
            return transfer( from.begin(), from.end(), from );
        }
  };
  
  /////////////////////////////////////////////////////////////////////////
  // ptr_multimap_adapter
  /////////////////////////////////////////////////////////////////////////

    template
    < 
        class T,
        class VoidPtrMultiMap, 
        class CloneAllocator = heap_clone_allocator,
        bool  Ordered        = true
    >
    class ptr_multimap_adapter : 
        public ptr_container_detail::ptr_map_adapter_base<T,VoidPtrMultiMap,CloneAllocator,Ordered>
    {
        typedef ptr_container_detail::ptr_map_adapter_base<T,VoidPtrMultiMap,CloneAllocator,Ordered>
             base_type;

    public: // typedefs
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator           
                       iterator;                 
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator     
                       const_iterator;           
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                       size_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::key_type
                       key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_reference
                       const_reference;
        typedef BOOST_DEDUCED_TYPENAME base_type::mapped_type
                    mapped_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                    auto_type;            
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMultiMap::allocator_type 
                    allocator_type;
    private:

        void safe_insert( const key_type& key, auto_type ptr ) // strong
        {
            this->base().insert( 
                           std::make_pair( key, ptr.get() ) ); // strong, commit      
            ptr.release();                                     // nothrow
        }
        
        template< typename II >                                               
        void map_basic_clone_and_insert( II first, II last )                  
        {                                                         
            while( first != last )                                            
            {                                            
                const_reference pair = *first.base();     // nothrow                     
                auto_type ptr( this->null_policy_allocate_clone(pair.second), *this );    
                                                          // strong
                safe_insert( pair.first, 
                             boost::ptr_container::move( ptr ) );
                                                          // strong, commit 
                ++first;                                                      
            }                                                                 
        }
        
    public:

        ptr_multimap_adapter()
        { }

        template< class SizeType >
        ptr_multimap_adapter( SizeType n, 
                              ptr_container_detail::unordered_associative_container_tag tag )
          : base_type( n, tag )
        { }

        template< class Comp >
        explicit ptr_multimap_adapter( const Comp& comp,
                                       const allocator_type& a )
          : base_type( comp, a ) { }

        template< class Hash, class Pred, class Allocator >
        ptr_multimap_adapter( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }

        template< class InputIterator >
        ptr_multimap_adapter( InputIterator first, InputIterator last )
        {
            map_basic_clone_and_insert( first, last );
        }
        
        template< class InputIterator, class Comp >
        ptr_multimap_adapter( InputIterator first, InputIterator last,
                              const Comp& comp,
                              const allocator_type& a )
          : base_type( comp, a )
        {
            map_basic_clone_and_insert( first, last );
        }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_multimap_adapter( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        {
            map_basic_clone_and_insert( first, last ); 
        }

        ptr_multimap_adapter( const ptr_multimap_adapter& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }
        
        template< class Key, class U, class CA, bool b >
        ptr_multimap_adapter( const ptr_multimap_adapter<Key,U,CA,b>& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        explicit ptr_multimap_adapter( std::auto_ptr<U> r ) : base_type( r )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        explicit ptr_multimap_adapter( std::unique_ptr<U> r ) : base_type( std::move( r ) )
        { }
#endif

        ptr_multimap_adapter& operator=( ptr_multimap_adapter r )
        {
            this->swap( r );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        ptr_multimap_adapter& operator=( std::auto_ptr<U> r )
        {  
            base_type::operator=( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        ptr_multimap_adapter& operator=( std::unique_ptr<U> r )
        {  
            base_type::operator=( std::move( r ) );
            return *this;
        }
#endif

        using base_type::release;

    private:
        iterator insert_impl( const key_type& key, mapped_type x ) // strong
        {
            this->enforce_null_policy( x, 
                  "Null pointer in 'ptr_multimap_adapter::insert()'" );

            auto_type ptr( x, *this );  // nothrow
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                res = this->base().insert( std::make_pair( key, x ) );
                                        // strong, commit        
            ptr.release();              // notrow
            return iterator( res );           
        }

        iterator insert_impl( iterator before, const key_type& key, mapped_type x ) // strong
        {
            this->enforce_null_policy( x, 
                  "Null pointer in 'ptr_multimap_adapter::insert()'" );
            
            auto_type ptr( x, *this );  // nothrow
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                res = this->base().insert( before.base(), 
                                           std::make_pair( key, x ) );
                                        // strong, commit        
            ptr.release();              // notrow
            return iterator( res );                       
        }

    public:
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            map_basic_clone_and_insert( first, last );
        }

        template< class Range >
        void insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }

        iterator insert( key_type& key, mapped_type x ) // strong
        {
            return insert_impl( key, x );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( const key_type& key, std::auto_ptr<U> x )
        {
            return insert_impl( key, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( const key_type& key, std::unique_ptr<U> x )
        {
            return insert_impl( key, x.release() );
        }
#endif

        template< class F, class S >
        iterator insert( iterator before, ptr_container_detail::ref_pair<F,S> p ) // strong
        {
            this->enforce_null_policy( p.second, 
                  "Null pointer in 'ptr_multimap_adapter::insert()'" );
            iterator res = insert_impl( before, p.first, 
                                        this->null_policy_allocate_clone( p.second ) );
            return res;
        }

        iterator insert( iterator before, key_type& key, mapped_type x ) // strong
        {
            return insert_impl( before, key, x );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( iterator before, const key_type& key, std::auto_ptr<U> x ) // strong
        {
            return insert_impl( before, key, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( iterator before, const key_type& key, std::unique_ptr<U> x ) // strong
        {
            return insert_impl( before, key, x.release() );
        }
#endif
        
        template< class PtrMapAdapter >
        void transfer( BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator object, 
                       PtrMapAdapter& from ) // strong
        {
            this->multi_transfer( object, from );
        }

        template< class PtrMapAdapter >
        size_type transfer( BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator first, 
                            BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator last, 
                            PtrMapAdapter& from ) // basic
        {
            return this->multi_transfer( first, last, from );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    

        template<  class PtrMapAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                            BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator >,
                                                            size_type >::type
        transfer( const Range& r, PtrMapAdapter& from ) // basic
        {
            return transfer( boost::begin(r), boost::end(r), from );
        }

#endif        
        template< class PtrMapAdapter >
        void transfer( PtrMapAdapter& from ) // basic
        {
            transfer( from.begin(), from.end(), from );
            BOOST_ASSERT( from.empty() );
        }

    };

    template< class I, class F, class S >
    inline bool is_null( const ptr_map_iterator<I,F,S>& i )
    {
        return i->second == 0;
    }
    
} // namespace 'boost'  

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_map_adapter.hpp
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
*/