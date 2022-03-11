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