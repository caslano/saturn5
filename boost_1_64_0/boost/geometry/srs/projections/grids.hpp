// Boost.Geometry

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP


#include <boost/geometry/srs/projections/impl/pj_gridinfo.hpp>

#include <fstream>


namespace boost { namespace geometry
{


namespace projections { namespace detail
{


struct grids_tag {};
struct shared_grids_tag {};


}} // namespace projections::detail

namespace srs
{

class grids
{
public:
    std::size_t size() const
    {
        return gridinfo.size();
    }

    bool empty() const
    {
        return gridinfo.empty();
    }

    typedef projections::detail::grids_tag tag;

    projections::detail::pj_gridinfo gridinfo;
};

struct ifstream_policy
{
    typedef std::ifstream stream_type;

    static inline void open(stream_type & is, std::string const& gridname)
    {
        is.open(gridname.c_str(), std::ios::binary);
    }
};

template
<
    typename StreamPolicy = srs::ifstream_policy,
    typename Grids = grids
>
struct grids_storage
{
    typedef StreamPolicy stream_policy_type;
    typedef Grids grids_type;

    grids_storage()
    {}

    explicit grids_storage(stream_policy_type const& policy)
        : stream_policy(policy)
    {}

    stream_policy_type stream_policy;
    grids_type hgrids;
};


template <typename GridsStorage = grids_storage<> >
class projection_grids
{
public:
    projection_grids(GridsStorage & storage)
        : m_storage_ptr(boost::addressof(storage))
    {}

    typedef GridsStorage grids_storage_type;

    GridsStorage & grids_storage() const
    {
        return *m_storage_ptr;
    }

private:
    GridsStorage * const m_storage_ptr;

public:
    std::vector<std::size_t> hindexes;
};


template <typename GridsStorage = grids_storage<> >
struct transformation_grids
{
    explicit transformation_grids(GridsStorage & storage)
        : src_grids(storage)
        , dst_grids(storage)
    {}

    projection_grids<GridsStorage> src_grids;
    projection_grids<GridsStorage> dst_grids;
};


namespace detail
{

struct empty_grids_storage {};
struct empty_projection_grids {};

} // namespace detail


template <>
struct transformation_grids<detail::empty_grids_storage>
{
    detail::empty_projection_grids src_grids;
    detail::empty_projection_grids dst_grids;
};


}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP

/* grids.hpp
c7jl4FuOMWtQzM59xfbjvmnWmYp78rnajebsUf19JfHDjWadjXDvv3Wqv39+ZPm9nlVUf6M+dr3ZRwPKzv78eUFTs5bGsYSWXn2JWYPKbvjc2v96FhGzx/L15oPe9qwD4lIq7q70U2XPupRt//EZZ5i9qeyni383xdRM9eevH3qX2ZvKll/bcYI5d8XMGlTvCe8Ws2u2bGH2T561jGwcy/ILZg81dRnpzn2mmN9Y4z3YHNVm8aDJR3iWEWvba4OHzsINVwdMXcT8lm0b/eg8s//Egpa9s+mwnGfrxVosa/rKRV2mLmA7VZs9l57zGc8CoxrjjrvinNGehcUClt1w5F2f9myamN3mFV/4abtnSdXmsQs+uMPUxW5T3WMuUW1uqbQ2mf2n2vxa0/A3POtTdtPa20aYs1z1d8enu+qebRNrtuy+c9bHzHXaanOselbZdKjEGWv8XrlfzG9M/ZuJYq2WnfSp36wy9bTj9DN4uz/1WYc5tunv3ImZHNR7WYusuKNUXBfYErClYMvAesBWgK0EWw22Dmy9bfp7Ibap+8GN0OZmsG1gO8B2mvUiptZLU1Dm3VjjPXRr0B3XHnT3N9k2dQ89DWwmWAfYHMv0PMwFmwc23zI9f4tUzcY8O+9ys66Vrbrx1xPM+lT1zK6b6zNrUMV9fuqaN8xaUvbnyy5dZdYE2G6xsGX3nXb3/ua8PqzRDjj7e58x9RRrtexbp7ftOwvEgpb5Lzv/Ds/yYq410a3iDmg94y6Tu5idw3Vzf3yjyV3Mrtl3um44wOwV2/R3RuyxqHvhnWIBY42v45oPd8cFxOy4v0RP+71nbWJ2za58uWeXWdfK/nnikJFmDYrZdVkQaHvKs6yYq545y/TazSt7fGLlLDMPYva8v3Rd4WZznonZ8/Dl85b/2tRa5R4qvni2ZwMq7hcnXHmKqeeHG+Nef/zSsjlfxOzcJzy1e5NnUTG7zcNf/OMnPEsoG7d54WbP0nZ/6vsBXaq/H/7yhK+auoi55r3XMj0PBdXmJ2aOf8jUU8ye92Mffc9n9q2y8886xLTZ1NqY35xXqytNzcAm26au4R1iZpzqGW5azK7ZwOivzzA1EwtZ9rMZt1xk6mLHqe9MrrZM77F+Zdntmz5p1pkaZ2r08Q94Vle29OwnL/CsZXRjm+c+futSc9YpG3/C9d/zbJpY0K7nn8MveJYUc+2xlGV6vaTF7JqdfETgAHN9ELPn6JbQjR3m+mCPU7226IOxlGAs/aq/Bz+70lyPqsqGH3jd5abWYIEx7v6ClunrZkjMzs/+N4Mni9n99cxZvd2sXWWRpi/ca85PMXv+Vj3w2Jvm/FRx95x5zwiz35Wt+UFX1bMi5NCn+tv6xa897dlGMb+xxs9PbFP9/Wj0n+7zbLeyk2aP+Y9Z10c01mzGw4csNutazHVtjIrZOUyIvj7ds5iYncNRbwwzcztXzB7LQVtuvtFc+9VYntnvrIRnOWXly47d4FmP6m/tpOCPTD3FWi0787ObV3lWEXPd81VVm+Hfrf2rqaeYa680haz81Gc5WsXsHFaG24/1LCIWsqw4+3Qz73NU3MG3rL/FnAVidn5vvrPkcFOzkPv+pVuNc91Ph99v1qeyERd9+I9mv9tjUa/DN6u4hyb2m3NwJ4yl6Uj3WR4UM/OgvxthmT5bE1abbeq9nnliLZbd8bObF5rrkbLFr4bWebZMtXnolmuO86yg4jbd+VrdnJ8Qt1HMb6zxNfo2p13p22nZMb6PNFjTWFmflpn1KeYHaxFrsezdZ9Zs86xdLGDZ3ZNv+7dnMdWm3L8Yi4MlwJJgKbA0WAasU+Vu7m3E8spu/Ob1Rc8Kyn4w+c1jPCs=
*/