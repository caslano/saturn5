//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_RECORDER_HPP
#define BOOST_BEAST_UNIT_TEST_RECORDER_HPP

#include <boost/beast/_experimental/unit_test/results.hpp>
#include <boost/beast/_experimental/unit_test/runner.hpp>

namespace boost {
namespace beast {
namespace unit_test {

/** A test runner that stores the results. */
class recorder : public runner
{
    results m_results;
    suite_results m_suite;
    case_results m_case;

public:
    recorder() = default;

    /** Returns a report with the results of all completed suites. */
    results const&
    report() const
    {
        return m_results;
    }

private:
    virtual
    void
    on_suite_begin(suite_info const& info) override
    {
        m_suite = suite_results(info.full_name());
    }

    virtual
    void
    on_suite_end() override
    {
        m_results.insert(std::move(m_suite));
    }

    virtual
    void
    on_case_begin(std::string const& name) override
    {
        m_case = case_results(name);
    }

    virtual
    void
    on_case_end() override
    {
        if(m_case.tests.size() > 0)
            m_suite.insert(std::move(m_case));
    }

    virtual
    void
    on_pass() override
    {
        m_case.tests.pass();
    }

    virtual
    void
    on_fail(std::string const& reason) override
    {
        m_case.tests.fail(reason);
    }

    virtual
    void
    on_log(std::string const& s) override
    {
        m_case.log.insert(s);
    }
};

} // unit_test
} // beast
} // boost

#endif

/* recorder.hpp
v9R/jf8G/wf93/D/2P8H/8WB8kAs0B7IBt4TmBGsC14dfE/wjuDDwUPBNaG3hxrC14RvCq+PCJvxPrlRe157RTvDOde5xLnB+UHnE84fOV9wznBFXW2uza6vuB507XP91nWOu8b9qPtl91zPZZ6wZ41ni+cuz4NI7eues7y6N+Ud9N7l/aH3Oe903aeH9Sv05/Va3yn+pf53+V/1PxB4FsdO3EjF2aGW0A2hp0Kzw98I0+BP
*/