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
Bu7CJyb73J1fYiuEo/JldA1wjSnhA24UsmXB+Zy61MgrKhh45ZL/3obTQCSV0sembgf9KV+NdaGmsAkh6TDgbWnBnCGsgSr0LN1OxzDCATD9FPSBNrR5ddUDdY+IxBQMXiLrHP5gHdqmR1yrHx26/o09F+PqWk5JnSSkkEjP/VOM37p73iZbW+sPqm+6Amwdaj3SaI3Z6J8k5vAHaL/580AU/owK5cLa/9s9SjUgg5lbQL8LVQsTpcYcijaDocqt35q27v+B06+DE4Wi/LKRa50mq4ekM/ruc4OVzndHdwR3DvMzONqXkHvJIwoveUGtb9iwtAh/2At6QMP8F9ZCIUSltNAZwqtR/TxTptCD5jPp4yFn31pD7fGx3mjfbYqBB7chhutKvm8vpRkJkyxGY9HqIExuTDAUeDmaxWkQgt1mEI1BPm8jddhYvPJVWWVhqsE5PywEDMYWak+g5rNwHRj8z0084aKuAdBEsCKPHNYfnWudalvG2IPt2MiYyOw3taUMqT3z2UVUk4meRTjmhVCskGf0AsRoOZ64tQ4Tyv7z8RpywhblcmSKZw==
*/