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
Xgf0GiFY8LE3CX0M6G1CXwD6CyE7/H2PkAP+fkgIpWM/ITQB/n5KyGUjWT2ov2mALiCEIra/JIQr1k2EKm1cbSaP1QK6kBAK6/6K0A9tXIMhj7kBXUzIZ+NaQXkM1SF/TQjV0S4hlAC0gRBKa20khNJalxE6HtDlhH5s478BzSONpysJLbORpB+gbkBXE+oDdA2hjI2E/gChis51hFBF53pCg4BuIPQvNhICBHQmoJsIrQO0mdB6G9eQyGMXAto=
*/