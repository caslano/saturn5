// Boost.Geometry

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_PROJ4_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_PROJ4_HPP


#include <string>
#include <vector>

#include <boost/algorithm/string/trim.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct dynamic {};


struct proj4
{
    explicit proj4(const char* s)
        : m_str(s)
    {}

    explicit proj4(std::string const& s)
        : m_str(s)
    {}

    std::string const& str() const
    {
        return m_str;
    }

private:
    std::string m_str;
};


namespace detail
{

struct proj4_parameter
{
    proj4_parameter() {}
    proj4_parameter(std::string const& n, std::string const& v) : name(n), value(v) {}
    std::string name;
    std::string value;
};

struct proj4_parameters
    : std::vector<proj4_parameter>
{
    // Initially implemented as part of pj_init_plus() and pj_init()
    proj4_parameters(std::string const& proj4_str)
    {
        const char* sep = " +";

        /* split into arguments based on '+' and trim white space */

        // boost::split splits on one character, here it should be on " +", so implementation below
        // todo: put in different routine or sort out
        std::string def = boost::trim_copy(proj4_str);
        boost::trim_left_if(def, boost::is_any_of(sep));

        std::string::size_type loc = def.find(sep);
        while (loc != std::string::npos)
        {
            std::string par = def.substr(0, loc);
            boost::trim(par);
            if (! par.empty())
            {
                this->add(par);
            }

            def.erase(0, loc);
            boost::trim_left_if(def, boost::is_any_of(sep));
            loc = def.find(sep);
        }

        if (! def.empty())
        {
            this->add(def);
        }
    }

    void add(std::string const& str)
    {
        std::string name = str;
        std::string value;
        boost::trim_left_if(name, boost::is_any_of("+"));
        std::string::size_type loc = name.find("=");
        if (loc != std::string::npos)
        {
            value = name.substr(loc + 1);
            name.erase(loc);
        }

        this->add(name, value);
    }

    void add(std::string const& name, std::string const& value)
    {
        this->push_back(proj4_parameter(name, value));
    }
};

}


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_PROJ4_HPP

/* proj4.hpp
yT4VhAsG467VBsPz4wlYsODdkjSk5fh+pRhuY2Fnk+JiLPYe0WdxmaD8FxZrdm1GetSKnDBHp22ILEC6o3BOb/L1WMfv8lLElUGtvaNPLroUhbHeLIUevSzyUqqK4snnxL3zCSbfxSqRwmVX55OzBLsKFpzwQ1PrxeQ3zD2f3fxF29kBr6fJ+rO8nhVqS0lJGsGOvgdB+4yXtkX9We/AG6glEwpQvD3DYWMUbQREqZbzahktTLpo7q0eM0xCmeKqmRFsLs7wL8FVyDHx5KGtH4G71V6zvXI1DAXDtDtcoAk8yIgn3Dq7OkMsEB26pSV69992P4pImHvmsDGtNKL8j2ri/SuzS83i7BH3tGb5mf7We5Mz+2Tl2bpCganlQGFEFEXRS2h9rrEtDqyUZGyuAgVjgY3luRzdowXQ+Do+q5F/bHwYo/61uoQfGfbLHUu08kwo4vi67V2shNQ5K/HK5pKp6tFEJuVwd2wGHWZCECWx2Koy/Kw5HPHPiur1wSvJpVomBocr1QAgXfC7Xb/sEDpGEUZb/G/g2wrGvpmsXBZ8s8wFLCXmnWACuQ==
*/