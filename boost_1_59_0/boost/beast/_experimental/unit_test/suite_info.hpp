//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_SUITE_INFO_HPP
#define BOOST_BEAST_UNIT_TEST_SUITE_INFO_HPP

#include <cstring>
#include <functional>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace unit_test {

class runner;

/** Associates a unit test type with metadata. */
class suite_info
{
    using run_type = std::function<void(runner&)>;

    std::string name_;
    std::string module_;
    std::string library_;
    bool manual_;
    run_type run_;

public:
    suite_info(
            std::string name,
            std::string module,
            std::string library,
            bool manual,
            run_type run)
        : name_(std::move(name))
        , module_(std::move(module))
        , library_(std::move(library))
        , manual_(manual)
        , run_(std::move(run))
    {
    }

    std::string const&
    name() const
    {
        return name_;
    }

    std::string const&
    module() const
    {
        return module_;
    }

    std::string const&
    library() const
    {
        return library_;
    }

    /// Returns `true` if this suite only runs manually.
    bool
    manual() const
    {
        return manual_;
    }

    /// Return the canonical suite name as a string.
    std::string
    full_name() const
    {
        return library_ + "." + module_ + "." + name_;
    }

    /// Run a new instance of the associated test suite.
    void
    run(runner& r) const
    {
        run_(r);
    }

    friend
    bool
    operator<(suite_info const& lhs, suite_info const& rhs)
    {
        return
            std::tie(lhs.library_, lhs.module_, lhs.name_) <
            std::tie(rhs.library_, rhs.module_, rhs.name_);
    }
};

//------------------------------------------------------------------------------

/// Convenience for producing suite_info for a given test type.
template<class Suite>
suite_info
make_suite_info(
    std::string name,
    std::string module,
    std::string library,
    bool manual)
{
    return suite_info(
        std::move(name),
        std::move(module),
        std::move(library),
        manual,
        [](runner& r)
        {
            Suite{}(r);
        }
    );
}

} // unit_test
} // beast
} // boost

#endif

/* suite_info.hpp
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
*/