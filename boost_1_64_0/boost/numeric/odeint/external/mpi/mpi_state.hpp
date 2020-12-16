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
jcX6mimL7651CwyAua9tscq9hcqtp3H1Vir34/gr9yxMejyTyXE8yjzdDzKxNMLsHFg37VncLuQxifTQ5NQ90WRweS2YzDwfKcaXO6zx5c4KPNb4chfV4W6WXZFYoZBW9Mb2ZZ1mVyIP3N2XdfV6ZHpBSkTjPqKxeGQaoeZuc/gjACVaDxQdL7xcXSubew4P9bQt62jtxk7C0k5NtHCyJ/cHhY8wkX5vgj6Ytg/6zPdqfRiOwmX24t3uN/0slqa4uE+ZOWF6iNIf0jZNTNwJ/rC2bTTxyyj4saavPSL72ijG6n5L7x8lnRkmvf8M6cxjJYzB70aXP0f0E0Xk+HktxwAZ5c5LJun5QnBuUqbnJkgjOsdr2RrZu2cNHhfyq6b6pGOYa1jLKQE4auDGDjZoGjw/MfFfmudNMnbwi7KsUc7NHB+zTviYTwgb8KRlA75cgceyAV+h9vxq0T7b2NNxSGh1Y3tfq8sOQ3iN5ErBxzcEH9+0+PhWBR6Lj28TH98h3I4i7T6X+o8r04d1W3Mf4HZmv8Vdm3xKrqmMwpe7mfsFfnM9v2f1l2epXs9Qf/k+1es5wisyz0zHNiU3cv+0YIXi03dpXWhs+Q9dOZdiE7uxZ9wVMInBVJLVj4j2pf8lG/iCYwOtNTXcawm7p3tmHFV3sLWtmggd+InQgan/gfnC94Su/8zS9Z9X4LF0/RekEy9auvOM5dv8ivB+LcaXOvH7CSv/byn/S6R7L1P+V0Sevaw8v3d5ozx/oDx/FHnea+V5jfLMozyvU56djIf1V+4jbwj5/NmSz18q8FjyeZPo/dUqd54ln78R3t9FuaeLct+x8v+D8p9BfP+T8v9L5P+wyI/dPN5fqrT2lyqdx9pfqqT9pcoR+7p/HVyDguvgEys9vvCb+dodv7le+Et8TKo09dqT+CgjvNlyndpaj16i+2EqnIYn70TaLaQxaTLyer5piWvuP2A54jfzW2HxW0n8lhO/VcRvNeE1FbEbP3b4tfq1tgHWunoT7UvXinqUjXKtYXYRPl7QfMjyjNymSLmNco6fV19KXL/Ue1WV7Hsav8bVN2MTd2ie2Z7uU+nwaD41653n9fwj42zIeXe9hmM+LuaAMzwZ8DxvqpDBrJL2daHToq9Ns/ravpV4rL5WTzqzH+Ga/s409rdozKjEY9E4gGjMtPQTeumzM7MI70AuCzbNn+cgyjOXbMscynOwRXuJZcPmEd58C+8AC6+B8A618ObaezuEt1DwWiFku8iSyxGVeCy5HEk0PmCVNcmSy9GEt5jLwp68VV/K8zGSSyPlaRJ5Zop2a7H4a63EY/G3lGgsEzS+TuU+Pyb/2pjJ259MOtFQ3nqZtfYNONtJY4+h/wLXCRfcEEv78sdwJ0IsHUY/9uP2x7NE1g/X3+hzUwQ8BYBeYqckmSe78BCCCl7ChwVg+AAeWBkKwPuHUwFYLhF3TBqwg+XlsjrUCDCLtjknGEjbFM/EwXmwDHwkMp8MnGB9//spOdgRWktqq/TaZZM+FIe8zpoijOOEFZWlrSlOl+tbYi1wpc6vyXpjXbu02SXuMY6x+kYH6egO0vNO0tEuC+8lq792E16P0OUTRH/os/rD6ko8Vn9YQzTWWmVdZZV1HOEdT3jH+WSU0Geoed0V56cpVo3PoeGAgIHxOQvAMhsVnxmltcOlNI8+Uci2ehf2mfKuSY1yPq73v1g2+M2+SdiSWT/Jdj35JhGSWdTDM3NbmWeA8kDeOs8GyjNo0V5v2c+TCW8j4a0oYa2rsRex3019veamkAJpVOdhovvYu1pDoZlweMjrw4lKp93DueygXjz1cMsJl5ZcuM/z/EynSzpTYIeYkoEfq/c=
*/