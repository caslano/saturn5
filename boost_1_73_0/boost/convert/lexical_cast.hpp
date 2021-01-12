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
gsbeHz4Il3zPzDFmE+ZbzPofbGsLpthCvzBmaCBgLcHEzgSMJ9x0zCLMcsx6zBaMo5C+JaY/ZjxmLuYqzL2YlzCfY6J0RMWYoZiJGDlfAHemS9qrR3rrr6BL+qrjGuuTRsZN7Z4rQIZ9GX9vhN7zBQ923PkZg2LssXMG9e3cswbz28frmf52rP2Tzh20rMNfpx8/f1DSmetMt3+2vunFRdQpZh1mC8ZqS51idseMbBv4zff/
*/