// Boost.Geometry

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_EXCEPTION_HPP
#define BOOST_GEOMETRY_PROJECTIONS_EXCEPTION_HPP


#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>

#include <boost/throw_exception.hpp>


namespace boost { namespace geometry
{


// TODO: make more for forward/inverse/init/setup
class projection_exception : public geometry::exception
{
public:
    explicit projection_exception(int code = 0)
        : m_code(code)
        , m_msg(projections::detail::pj_strerrno(code))
    {}

    explicit projection_exception(std::string const& msg)
        : m_code(0)
        , m_msg(msg)
    {}

    projection_exception(int code, std::string const& msg)
        : m_code(code)
        , m_msg(msg)
    {}

    virtual char const* what() const throw()
    {
        //return "Boost.Geometry Projection exception";
        return m_msg.what();
    }

    int code() const { return m_code; }
private :
    int m_code;
    std::runtime_error m_msg;
};


struct projection_not_named_exception
    : projection_exception
{
    projection_not_named_exception()
        : projection_exception(projections::detail::error_proj_not_named)
    {}
};

struct projection_unknown_id_exception
    : projection_exception
{
    projection_unknown_id_exception()
        : projection_exception(projections::detail::error_unknown_projection_id,
                               msg())
    {}

    projection_unknown_id_exception(std::string const& proj_name)
        : projection_exception(projections::detail::error_unknown_projection_id,
                               msg(proj_name))
    {}

private:
    static std::string msg()
    {
        using namespace projections::detail;
        return pj_strerrno(error_unknown_projection_id);
    }
    static std::string msg(std::string const& proj_name)
    {
        using namespace projections::detail;
        return pj_strerrno(error_unknown_projection_id) + " (" + proj_name + ")";
    }
};

struct projection_not_invertible_exception
    : projection_exception
{
    // NOTE: There is no error code in proj4 which could be used here
    // Proj4 sets points as invalid (HUGE_VAL) and last errno to EINVAL
    // in pj_inv() if inverse projection is not available.
    projection_not_invertible_exception(std::string const& proj_name)
        : projection_exception(projections::detail::error_non_conv_inv_meri_dist,
                               msg(proj_name))
    {}

private:
    static std::string msg(std::string const& proj_name)
    {
        return std::string("projection (") + proj_name + ") is not invertible";
    }
};


}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_PROJECTIONS_EXCEPTION_HPP

/* exception.hpp
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
*/