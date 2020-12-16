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
RKJD212P3UssDNYH7Iw4DIdZMCtTZgBo/d7FiCPQQMBhtDdcwq4d5Q6w2lODo9xEXyNVG855o6x63ti8iN0yy8+RdZ3yaX5j5dtIY3Ioeab0oGf3HGn9ZMcM5pMo3eIjEWHfc1QXFb2QyIl5FYhE1/ExAccRy0pnOfzeI7XvlbGk6folzy/m+dbF08QYyu2xNVHVRF4ly6Nq7F5jcUjORl1sZHM9IsFXK5r9uY01soV4fgz0dZSKXVIQDKvYJYuVjWUwSKqZ0fw7cfq1XvLLLea80zGL7pI78wLIMJhkVGX6n/jXIuJHG1jsGRYrQV1YtX14FfQsOqC0VCutOAjI8Phj3eUaWohbGZwnEulpoA2AhtM00hhuUznEKgvPC0ZhZ1lchRUhQWa1s1jZwRH7pRY2Ynpz7Rhu+3aer/PerYPyydEe9hvXKjnugDfJNnOc1H8UHyHJS7A9Xs2dSWXKm0w60RIGhx86oNcsSIqDRyXwBrccNRXTY36VBCPVduAxLX2KYxOW3jcc+wc7bqRlC0uTUMXYnbpAWZWXKuQ3019a0w+Y/lLhb0nCtQxbJ6Isu70+LC9AN8q5njXAzi+GdtaoiJztE9wJumfVGb/OSuSz6vw+u4NOVUix8k5i6zrMeX1obZ3BPi4J18rrFkeC1TbgMAZd55LgQ7rEC7yK0vlkiY//Ybxw1GN+w1yVH1q27YfmFhRPk/bZpyFvNb0hsgz/S23mdPyleomz8gD730VttHIWWekhZoN/EvcGzqYxyH6W0/rptoMZzEbBY7b8hfbp2PeocucyO4Ec+1r88vdKz0O+43lrO/dFcgzn03jjY7gA39zecCGzN5yl2WUuZnmrB1l5+KvyLqE5HtKLrQO1T2XteOdS/3Q8S4sfpVknaTkcn9UJTPvvEF2RtFdwOI6mJG7bd4RtO+vKua8h2GY5taPNrTnpbb+msDw3igbt8421ihabEm9DrlO8MVoXjMhgDvWI+2nro1HF8yKSF4a5Tf/5NMnvqkNNi2XQBorjRDb7q/Rz5HwZIEKiiuxSDVRPVPN03A93oL60GV7DzoeuZefC12VzuzrfOzXyhhJ61vUKRnRmrJWI7xlvSNpj6UNiR1pOORjx0qR4bdXz4utztMLB+rguWcPTU5EO9FgYDTWJeFp3pFUGo0mxTdLw5ttsvmfB9xz23UfmE4+25RPKaGluWU7F44BsYXr3EFnWIX0Y0qF11OfSiRtv6wDkMV2X9hIt3rpQi/VYKkvPATzsqOK0L8RcxzK45DB9b7yo80ZrihqbYra+OUmllcWiSOS65RSVruIFqjcL07GWN7G1LBAylnBFZVW5DPw8y1pDnoK1m+sYN9YzTYsSNnGiZxoLhSZb4glT9ArK72XD/1DsNqlX3QLY8FFTXyo9QzTJdKRRrHToGrcyWLp3homCgtPEx7VG/5V1CGhQRMfLVTwhQffrGd3fTnRfmgRHZWW2JsjgAT6YGIg6KyT+tkHxxCa7Z8xvLsW8vYPLld9pzbmc3JfeE7uL5lHYLr64a34j4XQPg9O91H4jlxf6WTnxesCpobaRQrNS+t0WjApD4RaE55Enrv4End1nnaE7jBB2WzpHv5+fo7djnR3xox20Kuf6oK2bIPadDYP5pKNJ+MP2Ru9Ashh5FO/OUTZ1ALdlX4+pvth7jilOb/0gln622P2z+2f3z+6f3T+7f3b/7P7Z/bP7Z/fP7p/dP7t/dv/8H/68fRPujXxiii93uMRFZaZY2wNvtw4yEPDHEB9vMcXQ703xylghThmCd0hQ9vYD4buZgTumV7pE/xmwiY4wxbhnEXvnz0LcONgU7qmmOLoKcfOnuEQD0qZcinuR/V0=
*/