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
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
*/