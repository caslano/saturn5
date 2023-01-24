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
iH/5cIj48VMZDiy1MceLXyR95bqhO7SuGgVPauhCYf9FNte/9rHexP+L7f3/c94+/FdquYMj7YKnuPcwGUPCO8V8K30IEUt8Aot4SuEbfVIWdwaYBjG7gZJmArsf/zJdws5778U0Y/WkMsulRWWQ3i+rflnDn7m4i07fvttmFssuF4fhFtpOYtlGMSlHkf9aKetK+Ae0/MwitW8hcrRVAm/XJAB4vroghFgFTmS18AZdHhhuoBq8vZDMnDg2pd/F06ty8bJ5il9JkeWFtqNsQSBxXVHUzEXECwAaH3jFqyFWvDBgfPSrey76r+cC6Blfx7stuslL0eu14Tt51HdDYggAHgrVZ1VLNFOo+VPjE126wdGLF2F0u6MrogtxqWUCEVcIS8+mplMZZe9RxJpLjcZuXZtlWlx+Up6bjPTkGRoF8+YwEYtd7Q9Vstyg7/Wy4jacoqZoWHxp59EB90b55dyT5PoPmR1mJHbRK8+b4humGTBu1GOfWm4Igkukzr8vKHdB77C/fgI9HUwohyXmUUBAQrPN+FRaFSFP3JvAThbYCkMYQUWc+M7TH49nDQ6vLx6She67SMuOnV+2k/uweTBVNx2bBstHbptjQ4EbzUV/uE+NuHqwj33K3ozKC99a2dr+RaJdJf0UQn8fgNov60a4v++D36KcXiPiMlEbaKJoJ8+znzeXnmPdPPNXOPo7sbxbcpPQlfIX5tEf
*/