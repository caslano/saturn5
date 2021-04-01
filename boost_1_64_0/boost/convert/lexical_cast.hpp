// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_LEXICAL_CAST_HPP
#define BOOST_CONVERT_LEXICAL_CAST_HPP

#include <boost/lexical_cast.hpp>

namespace boost { namespace cnv
{
    struct lexical_cast;
}}

/// @brief boost::lexical_cast-based converter
/// @details The purpose of the converter is to
/// * Make use of the boost::lexical_cast functionality and performance that many people have become
/// accustomed to and comfortable with;
/// * Demonstrate how existing independent conversion/transformation-related facilities might be
//  incorporated in to the Boost.Convert framework.
///
/// The converter can easily replace boost::lexical_cast, adding flexibility and convenience.

struct boost::cnv::lexical_cast
{
    template<typename TypeOut, typename TypeIn>
    void
    operator()(TypeIn const& value_in, boost::optional<TypeOut>& result_out) const
    {
        try
        {
            result_out = boost::lexical_cast<TypeOut>(value_in);
        }
        catch (boost::bad_lexical_cast const&)
        {
        }
    }
};

#endif // BOOST_CONVERT_LEXICAL_CAST_HPP

/* lexical_cast.hpp
51msI7QSUSZfPvapa/3gBUnJEgoBnw4MtmiJ/1t/FUcNPTUVhgbZ5CUJI22y3ZH/RPbGwnGOkGNcQt6Z3bJ8ujmPZvgYh+YzVghiFEFYDhrFKULSeiOg9YQZaj5twNd4JsQRqaZbNzB5pLo53Jy6knuJeOZwTVZMPnH43pI59P0aWq1a546kLxuXY4OcUuAGygynCch3tLGkBjXIb/v/tFRoHaw9LRI/PhA0yHRm54Oqp+tmWpUxlkkwttDmH+MM+Vp6FhpK1/FFk7OFzIjsGhDIE0aIGWEzm2SsF40unGjridXvGVNRSQqvksi2x9L6v1dnT+/c1fDjg11Ha5P6IAf8tHcKztJQoifPg8cs49BgwRv4cxkkUOscy+krOMzX11CXkC5f2T+BE730Rjb5o7aQC5oKdCc7+C5vGxt0iEKrepL0Cl4UbyXSRD/JUAStvWfFRraVOn/+bfZm6aU8IdJ0skPtpQKAhg2BJ1bmjRo2HLXPn7fL44+VtDT4uGcbTOchgpHbSADUtBp2AoSLSwC/LQBHC27onKJTCH4CmA6KYlWF073w9evplg==
*/