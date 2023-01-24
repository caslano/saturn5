// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED

// graph implementation based on a an mpl sequence of sequences <Edge,Source,Target> 

// incidence_list_graph labels such a sequence as manipulable by the metafunctions
// in the corresponding implementation header detail/incidence_list_graph.ipp
// to produce the metadata structures needed by mpl_graph.hpp 

// the public interface
#include <boost/msm/mpl_graph/mpl_graph.hpp>

// the implementation
#include <boost/msm/mpl_graph/detail/incidence_list_graph.ipp>

namespace boost {
namespace msm {
namespace mpl_graph {
   
template<typename EdgeSequence>
struct incidence_list_graph {
    typedef detail::incidence_list_tag representation;
    typedef EdgeSequence data;
};

}
}
}

#endif // BOOST_MSM_MPL_GRAPH_INCIDENCE_LIST_GRAPH_HPP_INCLUDED

/* incidence_list_graph.hpp
G85xzIeorQhEciaiqwHBrGnCT2/j1LHxq96T67XvOqr+nx5EG1U8ij/u580WTTscWRTsFY53WsdWvZ7GRHSzTVp5A6eMQHlg5lCtmA1sp5YgLGQDq6QYApNaTdMxQTCsU94YTM+iCk9jUMBTPYRT6VYY9RXUi3wViBMWhJ16w3aeXEEvxrzBN9qHGE0pG+zaLCp14RdmudYsrC4SJUc7i3pRF4dS3ZpDOeRvQKujjWH8G9gq6U6T8YXLwkB5eW1Y7Bp+a0LcR9rSEnKCmyZzlEP95gS8MWKPzdNVCfvQk/3QIwrng2Q3bFvn9W7pwYEufZ5Qaz5a7Z1+pSB1DKW6Uel61K/2XRhflxpWzMKe6I56uSaLUdVP2I6Ixo/crx7zBxbyWG2ofA9/smR2be3Qgg2zjnlXI/zlSieRZiT5j88Ucv4kavGlQR9v8Errc4CYAX+eR2Of9stH8vM831IpMtqAtYc3EmOPF5Z8DKbY+5hiXsy2dUstzRnE/ZC2TWfkwym/BP/oiT0bE0wlcfhB3WJz9syOMeQibPnZbCmfNMnpPzL3jO2cfs2M7f9S04QAim8bT/2wDYztEk12FOsnD3uTIlETxxGM7b+Rr3NwonM+u+7cJJ7Dx0g7vLqvNeWwXvfUcJcn0xPnAIUj9hKY95NpXPi7S6ACfwTWv3obnVbxcamJ7j5kgrwQu1Z3cABH5ajgBus4MQKI/jqM
*/