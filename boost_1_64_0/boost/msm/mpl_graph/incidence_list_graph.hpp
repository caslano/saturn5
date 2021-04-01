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
eT9Z57aA4MDX/XYPdtAfiK9VmAt46dJKVSjWJ+nom8DgyomVcT3rLdcoDVvWXrV9/aPw1nKrSSB/VDV+W1G3UJgVmMaUNlzf8Sm9m/uqMX6fXAEWXxGIP1sUkf4+ssLLSKXAdonLrluwI1VZaMTSrr0sQAK9KiE4Lgm4xdn9cU+QHGx7rpYv5NrD+FRAceMTAOILOXH2Pg7EPZa/ZBxNLx4OUkG6fdxIGGoJnSYqpGvRyPRnKrWkqIS6babt5p/ZP/TfempagrWimIe5gJCruKH1t+0RHx0J+movVqw5FlLN02ySRJMhkMIQXoOlnzdywtNrDPVFzict3jTuwiCZj2y54jCaluNm88sXnAZe1Jz/CiMFx8Y2S3ZBHnfxs38e12NSLfdx890eTwV6p1DttykVN/YHBjlXc3CRCGL/rmSNAa0joS5P9MJ3kJHuIYYtce4QWLpuCj/Pz6HZ/aM91VIEl9JTkqjQOqJUmJ2V96mnRRn/0rDPbR7ADXxUSAwwEwhsmqIcMMXVNkDENtG18wH1RpQBA26MKr7LSUGL7TTGRN82wi7OO02TmA==
*/