// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/serialization/array.hpp>

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal output archive, which ignores any save
///
/// This class implements a minimal output archive, probably an output archive
/// archetype, doing nothing at any save. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore
/// saving of most types

class ignore_oprimitive
{
public:
    /// a trivial default constructor
    ignore_oprimitive()
    {}

        /// don't do anything when saving binary data
    void save_binary(const void *, std::size_t )
    {
    }

        /// don't do anything when saving arrays
    template<class T>
    void save_array(serialization::array_wrapper<T> const&, unsigned int )
    {
    }

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::save_access;
protected:
#else
public:
#endif

        /// don't do anything when saving primitive types
    template<class T>
    void save(const T &)
    {
    }
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP

/* ignore_oprimitive.hpp
uDLgdgCnnLEKvBS17rmcAzHDGSH/xtt1xPXG27lNnHe30aqot9LI0VOotG5IR+3EAebVwWWKMlJsieLbryPHqwrrzS/i/TF3k2vOtzNSlJFiS5RyjHZfcWCd/ll4g2y4p7wCvaXfDNN1soNO5nGLN52jHUwKsHu23n0lXYCtS899LKbgx7RWvQWmj2WNTIUHasGsS7gl4gxKnGsS55qEWyLO4B8Qlru3+l8JS6vRAydTcy+TRn+Hz5hUoPcxEZSJYIuEqoxSAzJByQS5gfJNPotdlOxqUcKVAbdFHHJTJc4lCVcG3Gb8H7fYrqCD4oCs/3UG3JVugEHA94nw1ho5mJzvJZXzba2RS+JmmBXf7ho52oCr+rfoIYxwDDA3IlOUkSI3giPQIrnoSj6LPQVZbIv2P6npzez9G+3WJFwZcDuAe6PcGj4D3VBdaqgu4cqA2wE8aF8jrn3ddLOJ7GsSdazit360dVaVeq4491xx2t+c91IaQYMPf/tG3L1TRmDvlDsf0zvkyjfeT1FGimWgiLAWIZmiTBS5kaBs19Dw4G0teXun2DQAL+p6DayntznSW+/KFGWk2DKlZIC5EZmiTBS5kcD+10Xu9Li75TcjsFS+vVNygb1Tct7eKWfcH1MHQ9kayppQFoUyHZSx+2LqEyjrDcbUYlCmhdJ4NKY+hPI8lLugXPJoe++U9tE+gu/HNvl/zgD/j7Y/tGOpt1t3nJ0w3FlJm3XVJFzJuO6s/oZtwFq7Qad1FzgH3/wPm0Fv/pXtVbAXnLOxc/sGtAHYqK13iAOvAXRpzibOQUcHt2p04B3E1585vLyJtO8hb/lipCgjxZYpVQPMjcgUZaLIjfwrXTpuPvWVpwXkte6TVxr41kmqGr4rrWupaki4MuB2APekqgFSVfmLGyJ5bYC8VtjlqGAsXdnU+Wrd4Fi6wi8dwh6V7FU0EZRMkLe79I3UK7wVo7yLWoNHDzJFGSm2RNEK9gzcbBwI6GuGgUKFd9dv4L9/pbiSvHZS/n8GHthKK24zp4octnRy8LBJ4bQ3/2omNdoNH7aCDxjLttdO8GGf2fZa8so5lZPfgszNM134I7pwhPVlmtvbazuspvcLL/WRoOCP9Pnk8Hy2h/O5pvOyOVXyKbCUW4DpO+PUncbGxrSjQOsWWL/s4fEzp562f2rLxXpV4hGYDzh1Y/hB5mH8GzksfhJ9OBGqHNKdHCw/E4VnMoBQ4t7zDoLrAs/0GRctC9+BDQkRNsXyTU10TtLfGWti42tit4mbmOSMi1aE78+cuhX+Ao7RRJY+o0rxh4fxr3Xo0nB7zpyi/6I94Zt+n4GXnAH8fuqzh08YnSZxLxFffp859G/eVRu9G/gN4DeUzQE/v/mzF+GHMy5ak8A1CZww2uXcsS94nk/F70+v2VWLjD46MLAXfNlkAOM6cufh47Gyp+JZb5wdWJYoF2GFTbWgD1w42WL43Uls1ro3JeDU4uZ4CafiX1bZAXyQoLUX4X9UXPiga4AlGE8lNZ5K9i9Vck3FWV10lgN0lnSuTS0/lX6n4Pf6fu7kVgH7Ma5aaly1bHMtEpZ1msLy9Kk7onw90MG59WdctCo9S/w7KT3LD/bGZ7kqP0snwmI2AWobxGKyROZ24ouCBNU38KTyog303dqAquPfSQ7d/Uyqmiv20//swDok3TBcSdxLJzdn7jDVlNLMsx399OHMi5CS+6Sf/jcrnjp4+LT4cz4n+tC8vNFMU7JBt6N0BWeeWQXt6bfKy8CXZj86GfQ1T3d2oAHYASeFXnD2P/nrsX+nlf33HGhfd6L9/8HubgGboHMPVcN/vHIL3Fbaym9qeOF/JlVEAm+gP9jBG+hPnxg=
*/