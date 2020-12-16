//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_MATCH_HPP
#define BOOST_BEAST_UNIT_TEST_MATCH_HPP

#include <boost/beast/_experimental/unit_test/suite_info.hpp>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

// Predicate for implementing matches
class selector
{
public:
    enum mode_t
    {
        // Run all tests except manual ones
        all,

        // Run tests that match in any field
        automatch,

        // Match on suite
        suite,

        // Match on library
        library,

        // Match on module (used internally)
        module,

        // Match nothing (used internally)
        none
    };

private:
    mode_t mode_;
    std::string pat_;
    std::string library_;

public:
    template<class = void>
    explicit
    selector(mode_t mode, std::string const& pattern = "");

    template<class = void>
    bool
    operator()(suite_info const& s);
};

//------------------------------------------------------------------------------

template<class>
selector::selector(mode_t mode, std::string const& pattern)
    : mode_(mode)
    , pat_(pattern)
{
    if(mode_ == automatch && pattern.empty())
        mode_ = all;
}

template<class>
bool
selector::operator()(suite_info const& s)
{
    switch(mode_)
    {
    case automatch:
        // suite or full name
        if(s.name() == pat_ || s.full_name() == pat_)
        {
            mode_ = none;
            return true;
        }

        // check module
        if(pat_ == s.module())
        {
            mode_ = module;
            library_ = s.library();
            return ! s.manual();
        }

        // check library
        if(pat_ == s.library())
        {
            mode_ = library;
            return ! s.manual();
        }

        return false;

    case suite:
        return pat_ == s.name();

    case module:
        return pat_ == s.module() && ! s.manual();

    case library:
        return pat_ == s.library() && ! s.manual();

    case none:
        return false;

    case all:
    default:
        // fall through
        break;
    };

    return ! s.manual();
}

//------------------------------------------------------------------------------

// Utility functions for producing predicates to select suites.

/** Returns a predicate that implements a smart matching rule.
    The predicate checks the suite, module, and library fields of the
    suite_info in that order. When it finds a match, it changes modes
    depending on what was found:

        If a suite is matched first, then only the suite is selected. The
        suite may be marked manual.

        If a module is matched first, then only suites from that module
        and library not marked manual are selected from then on.

        If a library is matched first, then only suites from that library
        not marked manual are selected from then on.

*/
inline
selector
match_auto(std::string const& name)
{
    return selector(selector::automatch, name);
}

/** Return a predicate that matches all suites not marked manual. */
inline
selector
match_all()
{
    return selector(selector::all);
}

/** Returns a predicate that matches a specific suite. */
inline
selector
match_suite(std::string const& name)
{
    return selector(selector::suite, name);
}

/** Returns a predicate that matches all suites in a library. */
inline
selector
match_library(std::string const& name)
{
    return selector(selector::library, name);
}

} // unit_test
} // beast
} // boost

#endif

/* match.hpp
MHR+7SOWfmtT78Xi3qZjbNm8JJ3z29vkJI1TrzEaRwu/tipXin9d04e24DZjrw/77gvFv4e6mVO/qdek8ntbmbNb+jtEv5fRbyr6kY442lWQrqvYvtUnc95ofu+v2p6NfhNCn7FKvWuZ2+7/KVeOS7nq3MKMjVp2nnOIRS3KIh+j31K9GrmxIeX4F+/6di/PFGRzMu/1bfNcIkvCpDErMHZLNZ4wmy2hQmmsWufqH2Wbe+Jt67u5Nh2v+x7zHCdP/HvS0oLMc5xm2m8/bVz9+ZptjdHLTpCk2Wuupun0Ks8M/UZCE13bC0Vucj/LqFieORO1PP2s72kY/VaVd9kZ/ybWcw7a0W97zmFsdJm8euZpXauK+zWKCH+0Yp70yb3fZ/cappnPPA9Qf9uaptieys7ROLU92OOYJHGUrwkNNv6NrPvcf3j/h5aPR5lpP9S2oGm09cNJoku6vNrH4Ta6Fqr97VNkOrqLn7KXJY+GTXfz398ekTBvOTaa/qbxaF+ZWla+3cw8xPi38u5L9nmBjpsytJi5xKsS7inbXFyGGFPG/ubMGtd4uoperz3jSgsVfy5EZk3ErJ3GN5R5LXNajpXboKdPV23v2f1s4dINel0d476yEg/Hfn3KOpafl8Vh8+zAu//rNXdqWZ13M/NW23iKol6HrXYgZaZtwJrfSjn5mMva57tSPuXfvSxLB2Xi2Xb6nOOQv1ku0gInw+tJ35YN3m1HhxatgxnaDmz9UMNEmTnse+LOck10BvjrmxpmSIU2EqH3b3034s8bgy6e2Qfwf7leTiH5M9fgZ0UvwHxv43lxd3TOdgRLv/9B+oi5Xpl2oc8ste2VX3NTJHwt832F28Q92vks/9vWvcz6aJj4x7vCjG3lAqxEj83PHFdk0rhC02jm1uTBYdtjUOtpt/8njk7cQfbiOcoR0ryEgSXK/RwlMCoguWadgNCaNQMi67av26ZuVt12NWsE169d0xUQUrc1DogV5cDAmucGt5zDtbfa8wN/85qkjZ7zmn64fcxrzDORRuJ/2NmBcjuft0Kt+crPkq8Uv/ObyyRcT+Kxl/UTlLW7xEPleVEX8hJMyNakuw0Sp303HYHizoSnkI4NPffiLK5ibC6BM7z65CY/YzPtiGO2OaPq6lqbx7x3UXsvm5p6jUt71qtvVb6XT/Vj/PUh/Ku+vmkc/q5v6h/+X3V9s8oxJN4hf2t1P+Td1r6gJ+3lyCdS2B7ktSfItLGdottcy9QK29Rjj5CWp/o1M2uab4h7oWME/0/R/q/3puaZTahcA5Lt35jPctj2BX0jcWSw2tnFZ/8ZiM5f0XGfoQ95z0RscWXyn+lnX2hcnembaYh8k8nav6ZyTjX21VRnr5FVB9h9l7+fdY7xAzIWvcL1XnWgUwzv+YXZiyj6H2PxnlUEM8fQeHTOnt2w4trfANH5bfOMRyTctn/KPMMe12U+5hnWmJtim2cwDrFOduZzjQuftM01/MwpInROQZmZ9bB/57ziMjOv8OyzpXpz1FjXx+rD8aQxpMSrvei0on55vY+3jX2qH6XfYKZdi/snds0E8PVjv/MKDRdrrrVB+kzYmucuEf/bHFfwv30/bAc5frHHftjJcmwDdXulzzY2HFcv0fnE17Necz2dqXmx1qbXi7u7PkPA6ra4Ix1c8VRHj1Gqul5h5jD2783Fic5CR/+ycBwz4bznN8Zudjf80aowl8m15aUjbbkO7ihtw/bnd6fgxU15Rxrur7bt4cBQ0uWxLpVW3nbHm2/T+7iXHO6j3WboPhx7u831cy2OTPJ9vxn7rGd7rGKfuOr7v9eMrca1WOPwdy3G/7/vXtMqx6Nql/9zpKHayop1f5c=
*/