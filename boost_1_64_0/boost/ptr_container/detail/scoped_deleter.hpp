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

#ifndef BOOST_PTR_CONTAINER_SCOPED_DELETER_HPP
#define BOOST_PTR_CONTAINER_SCOPED_DELETER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <iterator>
#include <cstddef>
#include <boost/scoped_array.hpp>

namespace boost
{

    namespace ptr_container_detail
    {
        template< class Container >
        class scoped_deleter
        {
            typedef BOOST_DEDUCED_TYPENAME Container::size_type   size_type;
            typedef BOOST_DEDUCED_TYPENAME Container::object_type T;
            
            Container&        cont_;
            scoped_array<T*>  ptrs_;
            size_type         stored_; 
            bool              released_;
            
        public:
            scoped_deleter( Container& cont, T** a, size_type size ) 
                : cont_(cont), 
                  ptrs_( a ), 
                  stored_( size ), 
                  released_( false )
            { 
                BOOST_ASSERT( a );
            }
            
            scoped_deleter( Container& cont, size_type size ) 
                : cont_(cont), 
                  ptrs_( new T*[size] ), 
                  stored_( 0 ), 
                  released_( false )
            {
                BOOST_ASSERT( size > 0 );
            }


            
            scoped_deleter( Container& cont, size_type n, const T& x ) // strong
                : cont_(cont), 
                  ptrs_( new T*[n] ), 
                  stored_(0),
                  released_( false )
            {
                for( size_type i = 0; i != n; i++ )
                    add( cont_.null_policy_allocate_clone( &x ) );
                BOOST_ASSERT( stored_ > 0 );
            }


            
            template< class InputIterator >
            scoped_deleter ( Container& cont, InputIterator first, InputIterator last  ) // strong
                : cont_(cont),
                  ptrs_( new T*[ std::distance(first,last) ] ),
                  stored_(0),
                  released_( false )
            {
                for( ; first != last; ++first )
                    add( cont_.null_policy_allocate_clone_from_iterator( first ) );
                BOOST_ASSERT( stored_ > 0 );
            }

            
            
            ~scoped_deleter()
            {
                if ( !released_ )
                {
                    for( size_type i = 0u; i != stored_; ++i )
                        cont_.null_policy_deallocate_clone( ptrs_[i] ); 
                }
            }
            
            
            
            void add( T* t )
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                ptrs_[stored_] = t;
                ++stored_;
            }
            
            
            
            void release()
            {
                released_ = true;
            }
            
            
            
            T** begin()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[0];
            }
            
            
            
            T** end()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[stored_];
            }
            
        }; // class 'scoped_deleter'
    }
}

#endif

/* scoped_deleter.hpp
9gwysD5lh/aaUkd910SbHuSo0//hqaMvcdQmu9P/NnFVYaunTm5w1ckPUm7a7PKJvC39B3g7mvp/66pZyH3dga4a0Y+8B3sq+TBvfz/gqM/XpR8vQAYbPfXPpz311308tekRnlr/Nk/17Ed56SsXr+eq9/Id1bypq1x01yXPOqrlSlft8pareu/lqc1KXbXxno7aamvk8BVknrT67uyqhUfCrzvoG3ORW+SkCNov33LUX3kg6a75rvp9kX/pu6eKU546poejthzsqJP+5Kq5ZyLXf4L3DmkVe+q2Zz110hO8e0V/u/pOV02odVXqKPrfMkdN+txRa6jXGxtDc6irGshnSZ/gXcv3ZnvqhB2R42c8dfcGnjq0B7rrTl+ve+qX1fAIXtVuSrl2Rf6YRHr5dk89wITVC8w/7fl3V626n3YkrQX05evmeWoP+p2zs6Ouop+PnOqq3N1cdV6KeXxkbuJoR+XSd8p7w8eVrtocPi/fgHi/oC8d66mW82nPzdFpNyIzxF16FG38HP16uaP24H2nmzdDNlfQv6jLS0zqPbSho6qnOmrc26566j1HHU09C4931Oufcdc9/Hy0l6ueow9OL1fq5X7o7v7B3qcN+Nbj68+Xw7cl3xHIxyj6zhtXeeqaSvQMZfn8bU+9hF67fgdHjf8UXb0R9uLPrtoROas+z1OfnOqp1g/hzW6OOoN69Zvsqv0Hofepw+70hdxHlfrqOGzYPPZ4k8dcvtl8zR2euu804lQ46oQHPTX5AuL9lXZd31OnoY/fWsPft9Lvp6LPyWfDKx11OPFO5Tub73y+U/ge4XuS71m+l/he43ud7x2+B/ge82nb0LPHo8/3d9Xna7ALJzqqxy6OOmZv6otuen9DdAFt/9Wz6K5vHfUE+vygq131ZYuj1lnlqXLa9WT0VM5YT/3jZod5SPr9MawXfEfaTDTeMtxRiwdTxnuQwdPh+XDsM/rymmbkHzkqOcVRe9FO0/37US7CB5jrqPm+jH7LvUIXUe6+rvr2DHyF3/H23RJXTZ2NLj+L/nqAq25Ff+1A298/BJ7egA59A121paP6LqOf3st64Mmeuhyd/o9mV91H+occi0wtcNVFh+NT/M5R37xDnYay/nSQUuPoS2sGOqr2A0dtdrijPjgPPbIXfXMd9BH9KzWL+26+pC7juG+ceq2HHn/gClfdSf9LHUrcC7ALtNk533rqRcp1x0J07LrosSsc9dVi+sEBsGUrR1V9iexejA+EP1QHP74+DPuOzjpxALSPo9fp37W/wraib17bEj8IuV7/MGSqw1ELSXObcY7qSXq/HOipc3bEb1rhqbnwJ4EsfbCDq+7ZkHn+C9FzL7pqRgl+zPHQfEW/pW3XbOKp825Dx57pqDe3JF0m169nLvnaHPS3clT96fhw8OimelddxjrG8Pu4N6yFtuiPTZ7pql/901OnP0dbEa+Ur5yvkm/jAk8t+ptSV5wJb3fFz4Knl6LDP6AuTcX0g9dYK7jbUzt9xLmSenREM+1Wyi+6MDUFG4Mcb/sG9hxef/ENddwNWdnFVVfdxTogdvJA7MmQfOivQK7pT1/ciL9Cvs9Ppw3fxEc8x1EHXeXodebV9LW6OZwjmeKpMzf31Lfw+c+LHDX3Wnyxmz11bpOj/kLcZ/he4HuN7xW+N/ne4nuY7zG+R/h8uqdF+M7boFPmO2pVjasueBK9+pWjHlyG/G/lqm2Q3VnzqWMx/IFPE8721AFNyJbvE12N7OKfPLg/+uIY8qaMd6K35s2gXin69FLkYHdPvfYyeaGbvoEHQ1cjD+jUdybB/xmuGrQtMveoq65A7sZSj6ORua2oY8Fjnmrf1lPz3/LUx9g=
*/