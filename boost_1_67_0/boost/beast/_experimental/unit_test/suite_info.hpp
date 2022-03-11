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