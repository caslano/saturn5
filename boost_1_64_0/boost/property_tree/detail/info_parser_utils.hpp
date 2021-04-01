// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template<class ChDest, class ChSrc>
    std::basic_string<ChDest> convert_chtype(const ChSrc *text)
    {
        std::basic_string<ChDest> result;
        while (*text)
        {
            result += ChDest(*text);
            ++text;
        }
        return result;
    }

} } }

#endif

/* info_parser_utils.hpp
rqCvi5UMKtQhKLg2XWQOFhajmJ69/jwhYtDerGCccOnx1uY/aue+0c+7kUxFBSEEpJ9rHt19EY79QmGxhExp57tf40l+c+HDzgjyifxkq2K3QZ2hyN3wTDF8DoudNqCwR0iaezGCMOIuE9N9J4FstNPPbVez4IZUauTtZ2JFmE0n50Gr+OMWVIbodMyzIKdwIMMCrxQVBvI2YaGc9wtcHa+sO4gR88MmqABOKwHHCQmIx6rnpezxGdxqlkqhBhg0IQbD8bQVs0B20O1nEZKJ+pNSaGDPLJ0xCxi+6F8O4hD8X52xFG4dOrI1+teM67X/IUn70WV74+X6yBJVf8FAMKTlgn5nFjLNaD2YmizUve9Zgjyjkd0z3xk/NrxPwM/1BU/C/cQWlTMHCdR6r3E8xiJDgINmVthUwChE5Bgiy1FjueeqY6XnvqXAhzUW15Swaaqh0g6L9bf/UKdFasqfEQCPwurssJIGAz9DKt8sb4CZ7FnbRFXZRY21il0/PshyJ3ab2CZjDb134aHNbWJlLhNQCvg4Uaw6d0/8a5TjJ/DTN2XyOvWPOeAp6w==
*/