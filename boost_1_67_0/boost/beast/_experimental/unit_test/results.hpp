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