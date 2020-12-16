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
dc0+8VLa000KParfpfgW0wbH2/t81AZp0b5hMV5mrf6Xw3vO6n+biMZmoWN9wv/daunBNsq/mvTlVMp/GuGZPMzD6RYPZ1TisXg4k2icJWhMsvT0HMrzMJW7nfKca/H3sCWj8wjv/Moi68SjPPPqxDtfWGnine9Qyvf+Ft4LlNGxzAmkbl7VEmppXdrhlhEA89rYJbqvm/IuJfqvK1VgbwfDYUh/QpkIu+9sRy6vLBaXESX8ZFRn51dv3NhB+R1+1tFZgyHwI99Pwru7n4N9FMRn2ncjjVNXUptcVVnS2r0Tim6W64zdCMKpftfY89zxXPa1lUbXrqOyrw/iwu/yx8jeQLg35sEFPR/uzYR7C+H2k926utL4H7Y/9TE9lms4PDW2aTfpeY0TJ+L3627VdsvAKYMXa/VxpPG6oGNOVx+qpYMzd73LO1tcjQimaN0YaR2trcu9SiHdjU/WxDStgqmgl39dHZsa67p6zWZLW+/yVaG2ltaOXpznoJMiRdILxkhSnqY2PO2dTUyHYcjrzoU/oeXU6FtDuEPLtUsf6FsJo+2eyblTyHQKymnt7g119TW1tzWHVrau4/XEvCkj8NvZ2NXG/Fow5J3r3yPPbOvsP7mN9ofv1nrT5a55ZOSe3D1yveBdynu2L64+0i/vw6gfr9ddPNiRVP690hctsa4LfeVEN7cnN4NsrBdeOt+/BLhzFpYSjE9NZd7vK1Mf5+9tW2UshfeGcorsh6djp3g9hN81b/ny9PW0dnd09rY1e/sJDGFb+yDZgcU+/yWSyuTScVeOD2nec/BaEslsPKLrFYxHMOdqHx7l3MHMA1On5MJDnm/8iKYRBU9Gdp/2ya6rEyq87ti+xnZHhd262VDUr4C99gzBUn2nlksgAOZ5yGessfsxy8f8LNnUz1WOGENk2Ax1dLZ4rWLDuW0e53Lxm32dL1r8fIn4+QL5008QP09WlrRHvCkZN0OpD0I8fMXQ8M7IflWXkdHnmhbTOcuvVcpzluaz2Ygd97koAahjPwrcqbQBs303n3mjvZkitkrbNByjW23CZXXevClUr29Svdy4y1OMDduc2eacwgrH4dt2QF+VmzZep3Xho9gazOfi0ecdaK85981zNsDtu1aw/+mgaqPo4n4LfFSr9AZOYPwpoAFb35OKRVB3s6/ybSHrqYG6C3MfTPD0+VOVReIUd2Fcdmg+RTQvlfNdEeNyvJwD6e0n3hdGrFHOLMzzvtR39XjnwmHqCH+HngPx+urTWn7Rfu0DivsGILt+c9eAkdszPrltOhSaiOKyW3TF+FXLKNhfPDvXIc4WMEDYimeL7ku0trShkbNbJRkJY3k+59IpsNb2faQLnsR6UHogsqihQQN960HRjh4NlLZ7y4L588nsEbze4Lr3/Xi0n9flxaJxj1e0k1znGkimh7tj5kv6bVFn22AgHkvLtTTXwCq2++nYhngG7kEs2tYi6cVx557FTwLpcl1OIZ3p0NgRHJP2wpj0gxLHpGkF1rN+SOOR6z+84BuPlrUiWAUX6nQ0rvJsugUD7RHWHfzDl6ZRII3048ekH3P942gS7uHWOPlgP9F866F1IE4+mLse99M8Y2pwPCVIIb/E+JuWk+m3NT+39pvmiNitluQwDG2X5tm0t0kf7/Z7iQB6rj/wYh7eQ6twUwjO/TL/ElrEH/Dar6evqbe7lZswAPbq9Ctr/P215Q/8hsbfl4raAuczsaE4jsPmeIlOwjjm42Ux9r8i1ix+Z833fl+Jx1qz+APx8seivoAxgHJa7YOQzr1m1ft1q947qaw/EZ7/fi9zuyb7yli7H4rpe/ZmU7v+2e8jY7KC8UtzQ78L6mHP2o5WKJ4=
*/