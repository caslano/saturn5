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
wL0S7kCOqD3hXfjncjw4ER03e2PvF7bDvQUOhdledoYPc3wbjO9dbms4pTd6iLfN4Zkcaw3jp9FWkLlId9x3cXwNsg73cNyHYDFcRNp39CYO3Edgu+mUdx/i4wMqwWqXOB4m96naPvFxtVE8fDrpTCIufqch7kXZQngXsgFZxznDOTZzuqft4iM2+8WL1IbxDnQsO8aHphPefeNA2UdeRzgknuNDobdt4+MwKJm6xy8fvxLCLHIT2YX4snXs6Eee0D+A7mLcW/gdTTlEczzo4xqOw7i78Tt4BulGMtQucuoMwsF8aLeRvIFjJRw7mUw+4H7cR2DITI7xOwHabSin4k6BhTA8lfKCll3lTfzunkoccBQsVjvLwdejx+8SZDHuPrjXMIbuQg4jQQm1HbFICpKNzEdWItuQQ0iNROwzI2nINGQJshk5gDiSCIukIBnITOQ+ZDOyHzmNRHbGZjIyvPNZe8ln/87+nf07+3f27+zf2b+zf2f/zv6d/Tv799/09++w/5+UXjShMP+fY////WierarN/Ha6VyBI81ILCYzjP9bNy2zm97s4aQIbhTl7Trr7GwQF2fjKvk/gf98nFiw/asMz09Euh0tsoOu+VT3v0UA9H4UXBX8K4DkD+ikP6X54j/NmZnNS8/6XU/eRW/uAJ0qYfQFdzD5gK56O8p7GHRJmsu5jtfyizV74UeLeJe/GWPZUOj8se2HlXQL2gRCPvFNm3o1LM/F0MPYXx4u7tzPZZn+xgcSTpOHL35cbbMK3k739w3Dninu58zxa1FhnQ/Q4rnFY78g9H21770HfY9ko4W7CxmDfUL5fR4waN//c6S/RsosS+3zTkuw2O9qtRI8dG1759mm/PgwGiX8tdVtpCzD2f3PkvB8F1DHnKzb2O1PlXL+6bGkhSLlt4O8l7GBb2CJjr+RCCfuVLex0EzYFBoh/H8pAyoj2PDFnarqWk9q3eUnivxGd3qER2lhHy7HzqAOO6XtLq+TYCkyuBtvLLdFua/9xOV+my6uezXtNIeLfNcCWXgkfpnX9hvhf5MK+sHc9G/ulMaLT3h6HqbuhxNEZfxBwD/uxW3N8a3SZvI7cTAYXIvOqkCtV3o32/N0D7vMUObY9RN0+ZG80/sgN/P494h4jMqp4r4k8e7zXtJjjafKusPWuSKj0vzvkGH1Y7QnSl8y7l2uMO8u8l0wbwG3V/3mhY1bJeRw14srcs9XtUPcvXv6Jqz3978Gt/p7jWJB5hu9oDufBl0hLwqO+xjFetPUxjumYpWESTP1miHu803vsGWB0zzX942pxf29sbN6zTuw9eY472g9Gim6u2oKz4mrvc3y5FP+h4j9N9Acb/dY+x4hQeKf4Bzoi1F73GHEPcXbi2FhHLfNe/MZ1+i6G2qh6VfROoPGJHGtsjtVwcszWF7NGSD/QvtRB4imy+We6u6AZk2qL/8t2/xH2cSdC/Dc5dOzgT8cOW3+/UtJR6LSlQc5hlf/lEkdv7/I341MrcT/KM+KR5F37qsobESJ++yz9ETF62r+qfhfW3b9Ih0f/mu2jf8336k+LvfrTEq/+ZG//0XUc8tccqafPK58mbNoaX+0/Oyvff/vXME18XrPVz+d1WP18tt/Bxr+ReW9lv74P2K0a7+h4l1Wq11iUZis7fd/Su6zMXGtDXYf8dUIaIG2QUv7b8oSvshqbl8PLO9l5U/yUl4YjFr1emvK6BL/9bj9cWn6qGy268Q3t5ad++n7t5bjfE3eE6trnLKqr9hKH4H5L3DEVyt4+FyGMmYtwPTD18NeI6r8r5aseyLNHPZBW04aHq1vbMOf1Xy8D6/mul7RK6mXCtfn+23El9ZJrK78BRjc=
*/