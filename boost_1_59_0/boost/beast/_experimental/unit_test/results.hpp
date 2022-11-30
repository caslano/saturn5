//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_RESULTS_HPP
#define BOOST_BEAST_UNIT_TEST_RESULTS_HPP

#include <boost/beast/_experimental/unit_test/detail/const_container.hpp>

#include <string>
#include <vector>

namespace boost {
namespace beast {
namespace unit_test {

/** Holds a set of test condition outcomes in a testcase. */
class case_results
{
public:
    /** Holds the result of evaluating one test condition. */
    struct test
    {
        explicit test(bool pass_)
            : pass(pass_)
        {
        }

        test(bool pass_, std::string const& reason_)
            : pass(pass_)
            , reason(reason_)
        {
        }

        bool pass;
        std::string reason;
    };

private:
    class tests_t
        : public detail::const_container <std::vector <test>>
    {
    private:
        std::size_t failed_;

    public:
        tests_t()
            : failed_(0)
        {
        }

        /** Returns the total number of test conditions. */
        std::size_t
        total() const
        {
            return cont().size();
        }

        /** Returns the number of failed test conditions. */
        std::size_t
        failed() const
        {
            return failed_;
        }

        /** Register a successful test condition. */
        void
        pass()
        {
            cont().emplace_back(true);
        }

        /** Register a failed test condition. */
        void
        fail(std::string const& reason = "")
        {
            ++failed_;
            cont().emplace_back(false, reason);
        }
    };

    class log_t
        : public detail::const_container <std::vector <std::string>>
    {
    public:
        /** Insert a string into the log. */
        void
        insert(std::string const& s)
        {
            cont().push_back(s);
        }
    };

    std::string name_;

public:
    explicit case_results(std::string const& name = "")
        : name_(name)
    {
    }

    /** Returns the name of this testcase. */
    std::string const&
    name() const
    {
        return name_;
    }

    /** Memberspace for a container of test condition outcomes. */
    tests_t tests;

    /** Memberspace for a container of testcase log messages. */
    log_t log;
};

//--------------------------------------------------------------------------

/** Holds the set of testcase results in a suite. */
class suite_results
    : public detail::const_container <std::vector <case_results>>
{
private:
    std::string name_;
    std::size_t total_ = 0;
    std::size_t failed_ = 0;

public:
    explicit suite_results(std::string const& name = "")
        : name_(name)
    {
    }

    /** Returns the name of this suite. */
    std::string const&
    name() const
    {
        return name_;
    }

    /** Returns the total number of test conditions. */
    std::size_t
    total() const
    {
        return total_;
    }

    /** Returns the number of failures. */
    std::size_t
    failed() const
    {
        return failed_;
    }

    /** Insert a set of testcase results. */
    /** @{ */
    void
    insert(case_results&& r)
    {
        cont().emplace_back(std::move(r));
        total_ += r.tests.total();
        failed_ += r.tests.failed();
    }

    void
    insert(case_results const& r)
    {
        cont().push_back(r);
        total_ += r.tests.total();
        failed_ += r.tests.failed();
    }
    /** @} */
};

//------------------------------------------------------------------------------

// VFALCO TODO Make this a template class using scoped allocators
/** Holds the results of running a set of testsuites. */
class results
    : public detail::const_container <std::vector <suite_results>>
{
private:
    std::size_t m_cases;
    std::size_t total_;
    std::size_t failed_;

public:
    results()
        : m_cases(0)
        , total_(0)
        , failed_(0)
    {
    }

    /** Returns the total number of test cases. */
    std::size_t
    cases() const
    {
        return m_cases;
    }

    /** Returns the total number of test conditions. */
    std::size_t
    total() const
    {
        return total_;
    }

    /** Returns the number of failures. */
    std::size_t
    failed() const
    {
        return failed_;
    }

    /** Insert a set of suite results. */
    /** @{ */
    void
    insert(suite_results&& r)
    {
        m_cases += r.size();
        total_ += r.total();
        failed_ += r.failed();
        cont().emplace_back(std::move(r));
    }

    void
    insert(suite_results const& r)
    {
        m_cases += r.size();
        total_ += r.total();
        failed_ += r.failed();
        cont().push_back(r);
    }
    /** @} */
};

} // unit_test
} // beast
} // boost

#endif

/* results.hpp
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
*/