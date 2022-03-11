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
+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
*/