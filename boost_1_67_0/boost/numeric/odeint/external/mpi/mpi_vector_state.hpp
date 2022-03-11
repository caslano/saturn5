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