/*
 [auto_generated]
 boost/numeric/odeint/external/mpi/mpi_vector_state.hpp

 [begin_description]
 Copying a container from/to an mpi_state splits/joins it.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_VECTOR_STATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_VECTOR_STATE_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <boost/mpi.hpp>
#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/split_adaptor.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/external/mpi/mpi_state.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/** \brief Split data from some container on node 0 to the slaves.
 * Source must be a model of Random Access Range. */
template< class Source , class InnerState >
struct split_impl< Source, mpi_state< InnerState >,
    typename boost::enable_if< boost::has_range_const_iterator<Source> >::type >
{
    typedef typename boost::range_iterator<const Source>::type iterator;

    static void split( const Source &from, mpi_state< InnerState > &to )
    {
        std::vector< InnerState > pieces;
        if(to.world.rank() == 0) {
            const size_t num = static_cast<size_t>(to.world.size());
            pieces.resize(num);
            for(size_t i = 0 ; i < num ; i++) {
                iterator_range<iterator> part = detail::make_split_range(from, i, num);
                boost::numeric::odeint::resize(pieces[i], part);
                boost::numeric::odeint::copy(part, pieces[i]);
            }
        }
        // send to nodes
        boost::mpi::scatter(to.world, pieces, to(), 0);
    }
};

/** \brief Merge data from an mpi_state to some container on node 0.
 * Target must be a model Single Pass Range. */
template< class Target, class InnerState >
struct unsplit_impl< mpi_state< InnerState >, Target,
    typename boost::enable_if< boost::has_range_iterator<Target> >::type >
{
    typedef typename boost::range_iterator<Target>::type iterator;

    static void unsplit( const mpi_state< InnerState > &from , Target &to )
    {
        std::vector< InnerState > pieces;
        // send data to root
        boost::mpi::gather(from.world, from(), pieces, 0);
        if(from.world.rank() == 0) {
            // check target size
            size_t total_size = 0;
            for(size_t i = 0 ; i < pieces.size() ; i++)
                total_size += boost::size(pieces[i]);
            BOOST_ASSERT( total_size <= boost::size(to) );
            // copy parts
            iterator out = boost::begin(to);
            for(size_t i = 0 ; i < pieces.size() ; i++)
                out = boost::copy(pieces[i], out);
        }
    }
};


}
}
}


#endif


/* mpi_vector_state.hpp
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
*/