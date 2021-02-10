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
mBbwlDRebEnXjXkCBqMSEivLD6MLw6xmU52vAcKOTCWtqwKMYAcAJRpmDqguElk5YKf5gkVjU2fgZ12zkjchXUAY2jq6pvPrLZoIo0xAN+fjd6MPY7o5uro6Go4/0uiMjoYfmdiv58MTuF6BWUXyvqykAfOKVF5mSiYNzz/u0+/0d+jg5PT6+C2zr40qbp2meZ1ZhXiC+qmIZWMa4c9dsKS6ykttLM0gra4tTTIdfwY+EzroL2j2O50fVBFndSLpwNhE6XD6du2oAs7G2dz0rcoln7aOObp8iPE5ZEMgqaJ7p1XS6zx0iI4/XF3QDkMMOs3X97TjRI6mCIpMDnDMiMaqLIuquihY4UPacwiQpUYRYgIRh7RTb2ep6CENP1xcDJ4FzISxpa2egTOIZgBNpUBoufc2nLAqRjwXOI6noqJJnf77P4DYOr0vURjfbDkB4awzCL6W53WZaZHgXWZJ6KMxF58ll4gJMyZ3nQgrKK103nGFi7FvkfuFp1GIXCI/8NWJKoWZR8gc1rzb45iORZYh/Nid5GH4TiRJd3thnqCzURy3G3s8umC/nI2u3kecTsOj96cBbRlZJCzK1vPQZ+cXDMm8lH0dxt8APR2e9J4zmNPVWevP02bB5xsiMvTxaDg+HY6v/0+tTD3h
*/