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