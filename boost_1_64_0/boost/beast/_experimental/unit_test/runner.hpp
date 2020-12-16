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
0le9qF8jUy854m7is17SvOolqxr1kuanXj79L6mX+9Q2f5yOLTHI25xvcSX1UjRpsr960XAxFeplgPFraMrvIXV710sqfiu0f2g9adgQf+OP+seZ8v0kovrvzXmXbzev8k2xla+8Q+ijPAdpeYboHdsepJnug7qd+B3LfZWnnDN9TC7v/zIKFY2ZzL3kxEzedvZXvhpPnLkmxon7Me9yMX2hlfgv1zqwwrfS+sFtm7NMFb8EP9dovZcRnVXGlgTXU97JLL+mfijzV71+VqONu6+fDy43109fbd5vmffXMt+nZd5Px5aLkNmET1haSZmzCjCZ9jwxrygXdX1/2pS3Kb9eEkeylr8VZ5h5J7VhuCVV2zSx2tvM8rxJPnppPo7L/5Qh0hB5HbkR3cX+8yFfUfJMf3ZOUbHNZpqEfYYrj/l2ksYXZWtjRZPHaB0PMP4R5t59tbhfwcqkU22V6X2MykUqP4icaTlY6aXfmXqX9HiUzYYwfX9O67id1vHRe/2Wjdau/7p1Sb6aarloXLa6/T7EkjPNU3ndXmylX414LNAxttj9G93Y+/2nfxz2efkuypQc//M5Dd/B9M8B4r7aNv4WmjE1VfzCrXomrFkbwZ/RV9ydWZkIdLRFrDjwMWNEX9EZoeOyxuFxHc4yaya98LPCDja6LSu5XqoO//SbCj7vf8JhT9EbqXVla4/VaH/uMedOwuuYU43rQJk7xbgzPa/Dep1N8zFGWfWf0cjT3lYksojzlVZR/9k547Br4Lf+Ce9pP2BHyG+77tn7WoIu3ORrXxuLzEI3o5K+Rlcr9jGOmnFosoQdwT2NWT/U+MKM/flvQyz55/a9dpHmXUYp93B4E7oly/znp8j0Pf952inhf6Gc6mqeNE613RVv638DjF97+3zH2MnZa8Wl5ZNm9NvY9Gln2g/fwA84J+q4PtjoN6usf6HjNR81/SvPrD/+IjoBZfZBtG/t1+v8h2ast/2u5nU+6b6K1/mZ3nNbM9cq/IfntvOjHPJ3q/Y3t/8znG+2r/tmWvCUnMkUhd++puFaGNtrD4h7vKMr/w9R24N3SLjCAox/GLtiy0Uv3ZFAOxlAj9L2QHw+68vYXFsm/vmObuTpcmpK24WGa2psq7G+IXOuL//O3nnAR1XkcXzf7qaQbCCNEEKAAAFCTyOFZgihF0MPNYQkJEhCQgqEoiYURTgpCoqiGBE5QBTuwBMFERURFRQbBzbQs2PhsHGKer/97//Nznv7Xghevw/o8GVm/jNv+pu2/weeqsf4Z9T/+f3L625KP9eR+ZhWGuGpF+MAwsduNyzf8uycCpQy3sr40lcd5czhgzS60yZI5crlBzmtroznf+PYp+Z9gpR3eTyMas56SPkufxn4FGQzzfJZMvuy721X2BZCH+lssk9WIix2s/xymGZiDJhF9ulKFP726PPcRgshAzelFZ+7ZIp4wj3erbQfCM4h/0lKU4tV2s8rKpS/N3GBZPbSWuFV0jsk1uxiz3AjybQnPfVvsAyvH8WcZPN23p/kOciLZP8G9jNCr93vOR6DdYk4F6ogmTGQ8baY7eV/TjKPWVR9nc8a7OGfks1vWMvcs0On296grRXq2hrpvjPYT2/risuC8iX7SJ29iu0oW017TWvJeir4Oyne4OOQSXvYqL0W58zC4d8MdMs62iuHbSf2ameQ/TyPebq2KuTbiHlpLtm/NV2nTiP/c9xG1fBRhvO/MLCQ/D+V1rFVop4fI785kt98sV5+ivzyLAZnWOJdvJJkjuO3WF6kf6+J+tsdcu/Kbgq53UluT1vi0ab8TdqUfO5z4QrbU4tHdDrpDNpTlsG4Pa2O9bIvvxx68PwuEWY9wp8=
*/