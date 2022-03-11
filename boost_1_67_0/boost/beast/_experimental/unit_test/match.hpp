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
+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
*/