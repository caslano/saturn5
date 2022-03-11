//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_INSERTER_HPP
#define BOOST_PTR_CONTAINER_PTR_INSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <iterator>
#include <memory>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{
namespace ptr_container
{
    template< class PtrContainer >
    class ptr_back_insert_iterator;

    template< class PtrContainer >
    class ptr_front_insert_iterator;
    
    template< class PtrContainer >
    class ptr_insert_iterator;

    template< class PtrContainer >
    ptr_back_insert_iterator<PtrContainer> 
    ptr_back_inserter( PtrContainer& cont );

    template< class PtrContainer >
    ptr_front_insert_iterator<PtrContainer> 
    ptr_front_inserter( PtrContainer& cont );

    template< class PtrContainer >
    ptr_insert_iterator<PtrContainer> 
    ptr_inserter( PtrContainer& cont, typename PtrContainer::iterator before );

    //////////////////////////////////////////////////////////////////////////
    // Implementation
    ////////////////////////////////////////////////////////////////////////// 


    template< class PtrContainer >
    class ptr_back_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        explicit ptr_back_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj 
                          = container->null_policy_allocate_clone(r);
            container->push_back( obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_back_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_back( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_back_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            container->push_back( std::move( r ) );
            return *this;
        }
#endif

        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_back( container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_back_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_back_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_back_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class ptr_front_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        explicit ptr_front_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj 
                              = container->null_policy_allocate_clone(r);
            container->push_front( obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_front_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_front( r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_front_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            container->push_front( std::move( r ) );
            return *this;
        }
#endif
        
        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_front( container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_front_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_front_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_front_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class ptr_insert_iterator
    {
    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        typedef PtrContainer container_type;

    public:
        ptr_insert_iterator( PtrContainer& cont,
                               typename PtrContainer::iterator before )
        : container(&cont), iter(before)
        { }

        ptr_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 
                        container->null_policy_allocate_clone(r);

            iter = container->insert( iter, obj );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        ptr_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            iter = container->insert( iter, r );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        ptr_insert_iterator& 
        operator=( std::unique_ptr<T> r )
        {
            iter = container->insert( iter, std::move( r ) );
            return *this;
        }
#endif
        
        ptr_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            iter = container->insert( iter, 
                              container->null_policy_allocate_clone(&r) );
            return *this;
        }

        ptr_insert_iterator& operator*()
        { 
            return *this;
        }

        ptr_insert_iterator& operator++()
        { 
            return *this;
        }

        ptr_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer*                    container;
        typename PtrContainer::iterator  iter;
    };

    template< class PtrContainer >
    inline ptr_back_insert_iterator<PtrContainer> 
    ptr_back_inserter( PtrContainer& cont )
    {
        return ptr_back_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline ptr_front_insert_iterator<PtrContainer> 
    ptr_front_inserter( PtrContainer& cont )
    {
        return ptr_front_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline ptr_insert_iterator<PtrContainer> 
    ptr_inserter( PtrContainer& cont, 
                    typename PtrContainer::iterator before )
    {
        return ptr_insert_iterator<PtrContainer>( cont, before );
    }
    
} // namespace 'ptr_container'
} // namespace 'boost'

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_inserter.hpp
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
*/