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
qdVS3t2uhyagfWAIJaTsoYqa2w0f0xbLOTFXCxKaxuNyZR1aA6z3kphjSpNFO5FyUCo0pbvdCKcOVubhG8GezpUg1XQo1vKwJlRRrJnRA0J4abEkzIm1rp3E9FAohJQboLJjh/ediXI6hbORULIzh8gXD4VwB3qK5+yDIXSecFS/xL/Qe8LpSDhZRdWjBOsa6nNGL5utyJTjknbgPizFTK0U2USSSOZUhg8zk1NOaUooUwvVRDlRTLnDU6KUnAxFTQacQAfMpTJwhLkFBdGEg5m0kC+WQhd3yoWQ5YVGsICdnEqOT4Qt7+peQyXlUjqTLh0aTR3KxcVZF3pOLWRloOIpu4S+ls7nQhCiyyTKmRLMXZyYjmfzKVv00fBk6kZscDBayo10viAqdwSjEJ0xmyhNBncptxg9xfXYHKqruxKFKkmzYu0k/PwgzGiSgNWcEMOIPTlawiLYTuTKBWHNuTnTOCXmiHRuPB9GHCKyZ5K2aLswiw99n8pk4riyiXQulOdUoYP9ymOhiMnN5e/aaIBya3JqI5O/0amcqVJeNsNtv7ntN+Ktk3r8MyejWXNBqAHw9hh0b5coViE1Ru9ovVn+ojdyLsSVxVWP6x/0s4zdW2d/zv6c/Tn7c/bn7M//zY9ePzwBL0rPL0o0zzClWjrf7kFnx5mTZFZoYL4BM24K1JWc2thRo7TuYXQIcdVRXphTPzo3xa858xqqhuznbJ8F5SvwlKJ5hypnZadgW3PGeM0r02UhuTZVA68LieR6VAIukUrVnByCI4A5XXNeyTsmkT09Z7C1Sq7LfE3DbR02tn3GsyXSuS3zaRI35jJvzWm0wl4tJw/U5+1gVTz2DLJaYJ6Fx9ZK2RA9urbgSriAkdmCkKmjxkbPpu7fEULycLG/+Qc25xk5vf2SNuYVJw4Rf649hXEe8fVawvahMwdqznbgBKEWW/PKE5k1eCfDVDO/HCEkW4YO27jL1xCHlDiaLJRq4SoKZEzGAol7oFWBMKews2MRtURZa5F5IpWeJU8mkZsASWXl5iTiielEOpMYcw8mQ/OnQGCwxuI4EOM1/nemgYlPgamd2bQRU4CN8Rsh3VRb8t73bkuUEIAdK5fEdJDMZwtp2KVNLyvvecaO82/vyODs8mquChtLlHHQEB5shJRDUNiTKBQfGYp3d/X3b+/q3h3vGdjXNzw4EN+3KYzXzhndmlfooFZHAbsafGR+gYnZ0ZVQbbegkI+wQvhxzkwMmLuj25OpRCkRQmEE2EEXoiA9VaT/n31nxnz9Zb7L2H/BqywL4VbDeyn/Ta9rjM1/3/Hf/MZCTTaiVw3mK8v/47sDLFI/p8FrSag/m7z+n5+Hfvullbup4md0wvNsUfNjV4STo/aE8dtDZnEWEF7m0Fnj/9ak7rOp2v/aBOxwi+qzudL/ulzpeWYkV00wDtFeYbKGz2b1/vdl9daSoHs24fb2T7g9s7mzIRJha85vDZl0OoYAazFtO6N9YhGbtVNprCeJlTyj6sglSulpG1uJK+IbNqzftGnLRRs3jmKpUlQ+zfkCPB95/uuSWbchE6XQYlX9uWSpZT2uFR9ZWY6PSOH37tjsMp9vlL+zayzr1GrLOqbgTSu95VaBV9sKfKxuTfW6Lmyo3L/jTpZ1WNW1YbVRUH0kuv3O+GAMPjTzTPxejd8vB+97n29ZT1yCD/ngo1SLQdcDGe4Bud+4yrLWgd+fUPcu8L4CH4y5qa3C78mq7kMqk/V9+KDe6TpvnX+GnkE/FwI/CRkawesDuF4PfR9TpVz7efL3vZd44c9QWbNPRN3fbq3Aj9d7y/0Q+AeiPd4CWd9/jmUNQY/7AbZ1hbfcAdiiCeWego8=
*/