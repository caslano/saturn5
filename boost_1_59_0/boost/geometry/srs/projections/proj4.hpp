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
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
*/