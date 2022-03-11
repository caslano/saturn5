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