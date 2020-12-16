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
HjpyxzjPmnY22juv7D7asxDYNDGdn5lby/Q4OyBuDthcsHlg88EWgXWBLQFbCrYMrEfMtVdWQj1Xi5k1r15vblDz13VyfN9rEhjLAFgdzPe6+3rbbJmOC1im8wtapvdmCCwsFrDsvJX/uN2sXbAE2Dzob75tep2BdYEtEfNbNvg5arOWxOx5D0yLTzTrRcye90m3XWv2bT/0V4Z5qKi6TIgPqXq2Q/WXXrLG1Kz5jUb73mVPX+hZm5jd5i9P3n6mZ1ExO/fOa7Y95llczJVDAiypbPl7Ex/1LCWmr8Vm/sTsWg95qb/X7HcVN/jZQs96xVzXsSJYCXLot0yvwbIa50W/+PjDZr83zoOs17tWedb0ZqOd+dFvPW32GNg0MTv3UcXXd5l5eBPmwTJ9f50CS0ObGTG7nn9/+vwve5YVs+sy7rSja551K7t++BsrzRyp/L5/y5Wf82y9mGseNoBtBNsM+W0D2wG2E2w3WFPdbX6wFrBWsDaw9rr73jsGNqfuPs/mWqbX2Tzb9DkP41wE1lV37/elELcMrAdsBdhKsNVg68DWg20A2whztBlqtgPidqq4YfMOWmLW9VuN59ny5w55y7PQW41nwWvPHnSuZ9G31Fmwdvm+9/TFXGOZAzZXzJXffLs/9Z5NFtrMqTZvGN7Xb846lfstT25dYuZdrNWyT/zwcwebOVJ1ueYbo4aYeVDjXLDsub945tvlfk3SLNZi27/GnmjmQdm/Hnh1gZkHMdfejFmm6xJXbW76zHc3e5ZSNmPyLyd51ilm51c4ZNM3zL4Vc81fD4xzhZjrvry0C679UM+yWMiyP31q0ZNmP6j+Uhesfc+zwNvucQZtU++LhsRcuUeUzRhzV4+ZIzG71mum/qHZs6SYPU7/uo/EzNmq7Iq+kRd7lhfTr+1NrcVCdn5bJk4z9VRxMw4cN8GcPaq/7VMzz3tWVzlsPn5kk6nn7kar//sr5roSFrP7m+zvMPM3TdmBu2pm7SbE7BzG7b/rJVMXMXucke0vrzZ12e2e2241zjdPfe1XnhV3wzMPsBJY/27369sKxFVVfvZ3lndDfk3vNOa3fdKQNZ61irnu2SMqbkTTpRvNGaLs9l3/ecCcIarNrdf88lkzR2KucXapNge/02Su/TDOgmX6vmed1d8ofZ0G2wC2EWwz2DZlw14be7W5doi1WLYoefwuM3/vyjxZtmbo4qmetYkFLHtvw21mLUWVXfH4BlPrDrGgZedcsGTAs7SYGaf6PENGxY2fULvKXAPE7Bw+fn3TkebssceifoOhT8X952/PXGLOcjFvrxwqf1+ZP/Fwsx/EWiwLHT/8dXMuKVt63e/Nng6857awmOlP7c2oWLOxxmtqDOISYCnb1Od0MmIBY+r5vFjIsofnX3uR2Q9iQWON58R6sGqjWb+VJOcLxAV9+zltsmW6zYSYqad+XQyWEnOtiYyYa03kLNPz3gvWJ+aav34x15ooQ1wVbMAyvSZ8+zWO8yuPHGXmPajs2VBzlznLxVot+9oTW/rMPIiZHNR+T6o2l/dc6ze1FrPX566u6SeZ9Slmz/udUy9fZWqt7MWPVj9szmvV5oIHR5q4sjXOoP6MLlhVzG9M1Rri6mC+IZapeW8GCygLP//rs8z8gYWU3XPlwWbNh8VaLDt36t1N5lwSC1j2+o9vOtSzOTDOuWDzbFPPC+bbpp8J2KaeiXeJmTlSz6yWqhxmJde8Y9aSyv13tz/yktm3Km7wdys822Cbfr9Rtdnzh1sPNmvCjlO/Der/gDuHVjFXXdrA2sXs/mJ3T9lo5lYsaNlB1537azN/yhZ876F2zzrtNtXn3ZbCWJaB9YCtAFsJthpsnW0=
*/