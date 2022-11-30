//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_RUNNER_H_INCLUDED
#define BOOST_BEAST_UNIT_TEST_RUNNER_H_INCLUDED

#include <boost/beast/_experimental/unit_test/suite_info.hpp>
#include <boost/assert.hpp>
#include <mutex>
#include <ostream>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

/** Unit test runner interface.

    Derived classes can customize the reporting behavior. This interface is
    injected into the unit_test class to receive the results of the tests.
*/
class runner
{
    std::string arg_;
    bool default_ = false;
    bool failed_ = false;
    bool cond_ = false;
    std::recursive_mutex mutex_;

public:
    runner() = default;
    virtual ~runner() = default;
    runner(runner const&) = delete;
    runner& operator=(runner const&) = delete;

    /** Set the argument string.

        The argument string is available to suites and
        allows for customization of the test. Each suite
        defines its own syntax for the argument string.
        The same argument is passed to all suites.
    */
    void
    arg(std::string const& s)
    {
        arg_ = s;
    }

    /** Returns the argument string. */
    std::string const&
    arg() const
    {
        return arg_;
    }

    /** Run the specified suite.
        @return `true` if any conditions failed.
    */
    template<class = void>
    bool
    run(suite_info const& s);

    /** Run a sequence of suites.
        The expression
            `FwdIter::value_type`
        must be convertible to `suite_info`.
        @return `true` if any conditions failed.
    */
    template<class FwdIter>
    bool
    run(FwdIter first, FwdIter last);

    /** Conditionally run a sequence of suites.
        pred will be called as:
        @code
            bool pred(suite_info const&);
        @endcode
        @return `true` if any conditions failed.
    */
    template<class FwdIter, class Pred>
    bool
    run_if(FwdIter first, FwdIter last, Pred pred = Pred{});

    /** Run all suites in a container.
        @return `true` if any conditions failed.
    */
    template<class SequenceContainer>
    bool
    run_each(SequenceContainer const& c);

    /** Conditionally run suites in a container.
        pred will be called as:
        @code
            bool pred(suite_info const&);
        @endcode
        @return `true` if any conditions failed.
    */
    template<class SequenceContainer, class Pred>
    bool
    run_each_if(SequenceContainer const& c, Pred pred = Pred{});

protected:
    /// Called when a new suite starts.
    virtual
    void
    on_suite_begin(suite_info const&)
    {
    }

    /// Called when a suite ends.
    virtual
    void
    on_suite_end()
    {
    }

    /// Called when a new case starts.
    virtual
    void
    on_case_begin(std::string const&)
    {
    }

    /// Called when a new case ends.
    virtual
    void
    on_case_end()
    {
    }

    /// Called for each passing condition.
    virtual
    void
    on_pass()
    {
    }

    /// Called for each failing condition.
    virtual
    void
    on_fail(std::string const&)
    {
    }

    /// Called when a test logs output.
    virtual
    void
    on_log(std::string const&)
    {
    }

private:
    friend class suite;

    // Start a new testcase.
    template<class = void>
    void
    testcase(std::string const& name);

    template<class = void>
    void
    pass();

    template<class = void>
    void
    fail(std::string const& reason);

    template<class = void>
    void
    log(std::string const& s);
};

//------------------------------------------------------------------------------

template<class>
bool
runner::run(suite_info const& s)
{
    // Enable 'default' testcase
    default_ = true;
    failed_ = false;
    on_suite_begin(s);
    s.run(*this);
    // Forgot to call pass or fail.
    BOOST_ASSERT(cond_);
    on_case_end();
    on_suite_end();
    return failed_;
}

template<class FwdIter>
bool
runner::run(FwdIter first, FwdIter last)
{
    bool failed(false);
    for(;first != last; ++first)
        failed = run(*first) || failed;
    return failed;
}

template<class FwdIter, class Pred>
bool
runner::run_if(FwdIter first, FwdIter last, Pred pred)
{
    bool failed(false);
    for(;first != last; ++first)
        if(pred(*first))
            failed = run(*first) || failed;
    return failed;
}

template<class SequenceContainer>
bool
runner::run_each(SequenceContainer const& c)
{
    bool failed(false);
    for(auto const& s : c)
        failed = run(s) || failed;
    return failed;
}

template<class SequenceContainer, class Pred>
bool
runner::run_each_if(SequenceContainer const& c, Pred pred)
{
    bool failed(false);
    for(auto const& s : c)
        if(pred(s))
            failed = run(s) || failed;
    return failed;
}

template<class>
void
runner::testcase(std::string const& name)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    // Name may not be empty
    BOOST_ASSERT(default_ || ! name.empty());
    // Forgot to call pass or fail
    BOOST_ASSERT(default_ || cond_);
    if(! default_)
        on_case_end();
    default_ = false;
    cond_ = false;
    on_case_begin(name);
}

template<class>
void
runner::pass()
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if(default_)
        testcase("");
    on_pass();
    cond_ = true;
}

template<class>
void
runner::fail(std::string const& reason)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if(default_)
        testcase("");
    on_fail(reason);
    failed_ = true;
    cond_ = true;
}

template<class>
void
runner::log(std::string const& s)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if(default_)
        testcase("");
    on_log(s);
}

} // unit_test
} // beast
} // boost

#endif

/* runner.hpp
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
*/