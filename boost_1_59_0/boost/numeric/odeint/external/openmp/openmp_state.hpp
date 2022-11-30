/*
 [auto_generated]
 boost/numeric/odeint/external/openmp/openmp_state.hpp

 [begin_description]
 Wrappers for OpenMP.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_STATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_STATE_HPP_INCLUDED

#include <omp.h>
#include <vector>
#include <algorithm>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/split.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/external/openmp/openmp_nested_algebra.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief A container that is split into distinct parts, for threading.
 * Just a wrapper for vector<vector<T>>, use `copy` for splitting/joining.
 */
template< class T >
struct openmp_state : public std::vector< std::vector< T > >
{
    openmp_state() {}

    openmp_state(size_t n, const std::vector<T>& val = std::vector<T>())
    : std::vector< std::vector< T > >(n, val) {}

    template<class InputIterator>
    openmp_state(InputIterator first, InputIterator last)
    : std::vector< std::vector< T > >(first, last) {}

    openmp_state(const std::vector< std::vector< T > > &orig)
    : std::vector< std::vector< T > >(orig) {}

};




template< class T >
struct is_resizeable< openmp_state< T > > : boost::true_type { };


template< class T >
struct same_size_impl< openmp_state< T > , openmp_state< T > >
{
    static bool same_size( const openmp_state< T > &x , const openmp_state< T > &y )
    {
        if( x.size() != y.size() ) return false;
        for( size_t i = 0 ; i != x.size() ; i++ )
            if( x[i].size() != y[i].size() ) return false;
        return true;
    }
};


template< class T >
struct resize_impl< openmp_state< T > , openmp_state< T > >
{
    static void resize( openmp_state< T > &x , const openmp_state< T > &y )
    {
        x.resize( y.size() );
#       pragma omp parallel for schedule(dynamic)
        for(size_t i = 0 ; i < x.size() ; i++)
            x[i].resize( y[i].size() );
    }
};


/** \brief Copy data between openmp_states of same size. */
template< class T >
struct copy_impl< openmp_state< T >, openmp_state< T > >
{
    static void copy( const openmp_state< T > &from, openmp_state< T > &to )
    {
#       pragma omp parallel for schedule(dynamic)
        for(size_t i = 0 ; i < from.size() ; i++)
            std::copy( from[i].begin() , from[i].end() , to.begin() );
    }
};



/** \brief Copy data from some container to an openmp_state and resize it.
 * Target container size will determine number of blocks to split into.
 * If it is empty, it will be resized to the maximum number of OpenMP threads.
 * SourceContainer must support `s::value_type`, `s::const_iterator`, `s.begin()`, `s.end()` and `s.size()`,
 * with Random Access Iterators; i.e. it must be a Random Access Container. */
template< class SourceContainer >
struct split_impl< SourceContainer, openmp_state< typename SourceContainer::value_type > >
{
    static void split( const SourceContainer &from, openmp_state< typename SourceContainer::value_type > &to )
    {
        if(to.size() == 0) to.resize( omp_get_max_threads() );
        const size_t part = from.size() / to.size();
#       pragma omp parallel for schedule(dynamic)
        for(size_t i = 0 ; i < to.size() ; i++) {
            typedef typename SourceContainer::const_iterator it_t;
            const it_t begin = from.begin() + i * part;
            it_t end = begin + part;
            // for cases where from.size() % to.size() > 0
            if(i + 1 == to.size() || end > from.end()) end = from.end();
            to[i].resize(end - begin);
            std::copy(begin, end, to[i].begin());
        }
    }
};

/** \brief Copy data from an openmp_state to some container and resize it.
 * TargetContainer must support `s::value_type`, `s::iterator`, `s.begin()` and `s.resize(n)`,
 * i.e. it must be a `std::vector`. */
template< class TargetContainer >
struct unsplit_impl< openmp_state< typename TargetContainer::value_type >, TargetContainer >
{
    static void unsplit( const openmp_state< typename TargetContainer::value_type > &from , TargetContainer &to )
    {
        // resize target
        size_t total_size = 0;
        for(size_t i = 0 ; i < from.size() ; i++)
            total_size += from[i].size();
        to.resize( total_size );
        // copy parts
        typename TargetContainer::iterator out = to.begin();
        for(size_t i = 0 ; i < from.size() ; i++)
            out = std::copy(from[i].begin(), from[i].end(), out);
    }
};




/** \brief OpenMP-parallelized algebra.
 * For use with openmp_state.
 */
typedef openmp_nested_algebra< range_algebra > openmp_algebra;



/** \brief Use `openmp_algebra` for `openmp_state`. */
template< class T >
struct algebra_dispatcher< openmp_state< T > >
{
    typedef openmp_algebra algebra_type;
};


}
}
}


#endif


/* openmp_state.hpp
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
*/