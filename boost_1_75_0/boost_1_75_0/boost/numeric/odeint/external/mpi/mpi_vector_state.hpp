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
6DOnQkq2ShDupCrZ15EWtpnvq3zxofcZX4RR3lbmozwKwh/RUjytpnDn5hCZYYNAEjuKvjT+Mmod0nAaflfS8Msq00efvVZNKbrnZwvOHgFkXRZI1rXCp7Q2gBXWqHiMlN+8QFspINI1+wkZlKA2esZGtlyiGXNuRLq7t4AWshAyJtZv/BSnJa3lRbXlKZe8VEHfX0hscMdLEzaUmelSHRnjnCLLXnVijWI3Hd/3b8RjFDHyW9R7KNhYRG5FS3aUs1JRNsmhU9Iesok0kBaSqAZF2VpNl87aOxaZaD7KctPxFl8n0KL7s0xuc9xGTIp5ZjNu6MFMgxt6qzfjegVH0pqyCof0Tbrnrqh0zwOx6Z7Zqj1fWLoki2nGW1EVKx01FS6lkTI0CsJSIMzlFL0P5+CGjmt4ujs3XsiAXgHp5NnDtOlQAtKW/IStTiEx5Aa2WMN3m395i43AgvjGC7h2DmkHN7eI9Q9vGA/iwwDUFaQZt2JVOiAyUGA/nLfTjO8BcIbT9X77oPxULN8E5Td5tRyfX8IVvM53L9PVofwGH/mODmN3NEL8Dyw+SE5x70G9+Z2xbr/B1Q/GxPkftTEBqxWoQSReqizttzKeEPM1xZM8FCzB8DJe1suI1c1woSA2heS0ZuOUFC1eY/q7fNDNpgnawn6QRGHOpdVxNNkhfYU8fniqZmYcYFHb2AbeOzeKhKPRqZZVZ5qZt5ef
*/