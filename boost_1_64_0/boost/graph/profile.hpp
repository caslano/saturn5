//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_PROFILE_HPP
#define BOOST_GRAPH_PROFILE_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>
#include <boost/graph/bandwidth.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type profile(
    const Graph& g, VertexIndexMap index)
{
    typename graph_traits< Graph >::vertices_size_type b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        b += ith_bandwidth(*i, g, index) + 1;
    }

    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type profile(const Graph& g)
{
    return profile(g, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_PROFILE_HPP

/* profile.hpp
OMWGMNM5h5suxs9sXXZfJDSl2qjrkrk7s6nycXS3vf2ieyZ/wu37bXw/4g1QDIIdhnEp37n/DRBTe7sctlXNsqA/LwXRW48KYpmv1r9ImQkp+LQd0BWR9Q8IbG+eRV31aQVIQl0KUXxssPnghirSGKfDFM2k21KnvPaIZbF13nMcLzWnFrPFJqJV/wa/G7LHrwYlrIrS8IoG989fyOkNCsX7luB2NlCsyi/skrtEH/v7fhWVy4yCsGIMUgjIVjhlDfsf/vGz652MFb26khwexJa/SYeUvsxfTb2oMtKHqC8KXV7c7ol/JaYUeMB9Ese0STtur3XzRCiTOGojC9pDC+sPPAFPKkrw/UIfMA1033R4Pxwq5lGwe/JwFbHKmzAaSNhfi+4Pbo4e1bUcmkq+SB+AwJ98WLVj/YegbOzFqvMDkE1rts6Ts3SGfkT3PaOmxCCXc8fPNrZiRYoEVUyqiN1/Uze4MjOzQ1SRyDKnpFe6Iykvwv7W0IiQwIIdsjzLuXsk/E0pfpIJ/u7Po1L8gws3as3weS+0+VtcDxZsoJCJx733N5tlGbzs3w==
*/