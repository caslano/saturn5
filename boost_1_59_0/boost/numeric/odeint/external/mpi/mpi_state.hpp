/*
 [auto_generated]
 boost/numeric/odeint/external/mpi/mpi_state.hpp

 [begin_description]
 A generic split state, storing partial data on each node.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_STATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_STATE_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <boost/mpi.hpp>
#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/split.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/external/mpi/mpi_nested_algebra.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief A container which has its contents distributed among the nodes.
 */
template< class InnerState >
struct mpi_state
{
    typedef InnerState value_type;

    // the node's local data.
    InnerState m_data;

    boost::mpi::communicator world;

    mpi_state() {}
    mpi_state(boost::mpi::communicator comm) : world(comm) {}

    inline InnerState &operator()() { return m_data; }
    inline const InnerState &operator()() const { return m_data; }
};




template< class InnerState >
struct is_resizeable< mpi_state< InnerState > >
     : is_resizeable< InnerState > { };


template< class InnerState1 , class InnerState2 >
struct same_size_impl< mpi_state< InnerState1 > , mpi_state< InnerState2 > >
{
    static bool same_size( const mpi_state< InnerState1 > &x , const mpi_state< InnerState2 > &y )
    {
        const bool local = boost::numeric::odeint::same_size(x(), y());
        return boost::mpi::all_reduce(x.world, local, mpi::bitwise_and<bool>());
    }
};


template< class InnerState1 , class InnerState2 >
struct resize_impl< mpi_state< InnerState1 > , mpi_state< InnerState2 > >
{
    static void resize( mpi_state< InnerState1 > &x , const mpi_state< InnerState2 > &y )
    {
        // resize local parts on each node.
        boost::numeric::odeint::resize(x(), y());
    }
};


/** \brief Copy data between mpi_states of same size. */
template< class InnerState1 , class InnerState2 >
struct copy_impl< mpi_state< InnerState1 > , mpi_state< InnerState2 > >
{
    static void copy( const mpi_state< InnerState1 > &from , mpi_state< InnerState2 > &to )
    {
        // copy local parts on each node.
        boost::numeric::odeint::copy(from(), to());
    }
};



/** \brief Use `mpi_algebra` for `mpi_state`. */
template< class InnerState >
struct algebra_dispatcher< mpi_state< InnerState > >
{
    typedef mpi_nested_algebra<
        typename algebra_dispatcher< InnerState >::algebra_type
    > algebra_type;
};


}
}
}


#endif

/* mpi_state.hpp
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
*/