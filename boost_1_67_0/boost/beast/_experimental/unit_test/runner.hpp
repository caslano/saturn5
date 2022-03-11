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