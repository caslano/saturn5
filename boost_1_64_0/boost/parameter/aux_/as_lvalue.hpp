// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_AS_LVALUE_HPP
#define BOOST_PARAMETER_AUX_AS_LVALUE_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    T const& as_lvalue(T const& value)
    {
        return value;
    }

    template <typename T>
    T& as_lvalue(T& value)
    {
        return value;
    }
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_lvalue.hpp
mXA3tjnvgnvtN5T4pDlYU5d6pJk6sHbDUphLeKOxFBXPbNIpXKxSDTS5e6PvLiASdoMBqq/tiPBuq/S1P8iJYjlVMbdAa7PRDT1tP4edECpTLwYPhbTtP5j9F3LbzaViJoFFPOIFLq57EnzMuzIqQZPu4Jridh8tyLqxTj1XuADIJysdf2H1NpwoPkxsYbjdgjUSQcCDfW6cRB2GHX6yy1dR7NfSO/l9vA1qRlTim+MWiREFH3/VzoNOAVzXpwCuHueGQN+dSnzcMNK5OEfPJMBjx2IHIsRcjIykjXkJrk7RBWa7/cGNAROfNzoUKBPp2/PGhwVCELJq6QVBmcMyHVBAIYp1mb9p4QbcsxpNG/L5SB/nwJ1Y0FOOs8bi17rVOCro653dHsW5wAmE2a3ybxEOTIGA1ImxuaF0XyogKXJ8h1aD62W9guwJs74TesCqjoFqIuLDud6zMqM/osEzJ2hdS+5YHwk2yrTCUpdjdfU5JreFs0fTGUtiipRhiq3xIAiQ7MzswV3YUhvxKuprjty81Pi2yzcv/J6XmPrUeTNUQcGXBN0BPMEr0g==
*/