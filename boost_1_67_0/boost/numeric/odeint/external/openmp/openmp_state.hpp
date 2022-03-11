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