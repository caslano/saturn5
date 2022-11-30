//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_REPORTER_HPP
#define BOOST_BEAST_UNIT_TEST_REPORTER_HPP

#include <boost/beast/_experimental/unit_test/amount.hpp>
#include <boost/beast/_experimental/unit_test/recorder.hpp>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/** A simple test runner that writes everything to a stream in real time.
    The totals are output when the object is destroyed.
*/
template<class = void>
class reporter : public runner
{
private:
    using clock_type = std::chrono::steady_clock;

    struct case_results
    {
        std::string name;
        std::size_t total = 0;
        std::size_t failed = 0;

        explicit
        case_results(std::string name_ = "")
            : name(std::move(name_))
        {
        }
    };

    struct suite_results
    {
        std::string name;
        std::size_t cases = 0;
        std::size_t total = 0;
        std::size_t failed = 0;
        typename clock_type::time_point start = clock_type::now();

        explicit
        suite_results(std::string name_ = "")
            : name(std::move(name_))
        {
        }

        void
        add(case_results const& r);
    };

    struct results
    {
        using run_time = std::pair<std::string,
            typename clock_type::duration>;

        enum
        {
            max_top = 10
        };

        std::size_t suites = 0;
        std::size_t cases = 0;
        std::size_t total = 0;
        std::size_t failed = 0;
        std::vector<run_time> top;
        typename clock_type::time_point start = clock_type::now();

        void
        add(suite_results const& r);
    };

    std::ostream& os_;
    results results_;
    suite_results suite_results_;
    case_results case_results_;

public:
    reporter(reporter const&) = delete;
    reporter& operator=(reporter const&) = delete;

    ~reporter();

    explicit
    reporter(std::ostream& os = std::cout);

private:
    static
    std::string
    fmtdur(typename clock_type::duration const& d);

    virtual
    void
    on_suite_begin(suite_info const& info) override;

    virtual
    void
    on_suite_end() override;

    virtual
    void
    on_case_begin(std::string const& name) override;

    virtual
    void
    on_case_end() override;

    virtual
    void
    on_pass() override;

    virtual
    void
    on_fail(std::string const& reason) override;

    virtual
    void
    on_log(std::string const& s) override;
};

//------------------------------------------------------------------------------

template<class _>
void
reporter<_>::
suite_results::add(case_results const& r)
{
    ++cases;
    total += r.total;
    failed += r.failed;
}

template<class _>
void
reporter<_>::
results::add(suite_results const& r)
{
    ++suites;
    total += r.total;
    cases += r.cases;
    failed += r.failed;
    auto const elapsed = clock_type::now() - r.start;
    if(elapsed >= std::chrono::seconds{1})
    {
        auto const iter = std::lower_bound(top.begin(),
            top.end(), elapsed,
            [](run_time const& t1,
                typename clock_type::duration const& t2)
            {
                return t1.second > t2;
            });
        if(iter != top.end())
        {
            top.emplace(iter, r.name, elapsed);
            if(top.size() > max_top)
                top.resize(max_top);
        }
    }
}

//------------------------------------------------------------------------------

template<class _>
reporter<_>::
reporter(std::ostream& os)
    : os_(os)
{
}

template<class _>
reporter<_>::~reporter()
{
    if(results_.top.size() > 0)
    {
        os_ << "Longest suite times:\n";
        for(auto const& i : results_.top)
            os_ << std::setw(8) <<
                fmtdur(i.second) << " " << i.first << '\n';
    }
    auto const elapsed = clock_type::now() - results_.start;
    os_ <<
        fmtdur(elapsed) << ", " <<
        amount{results_.suites, "suite"} << ", " <<
        amount{results_.cases, "case"} << ", " <<
        amount{results_.total, "test"} << " total, " <<
        amount{results_.failed, "failure"} <<
        std::endl;
}

template<class _>
std::string
reporter<_>::fmtdur(typename clock_type::duration const& d)
{
    using namespace std::chrono;
    auto const ms = duration_cast<milliseconds>(d);
    if(ms < seconds{1})
        return std::to_string(ms.count()) + "ms";
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) <<
       (ms.count()/1000.) << "s";
    return ss.str();
}

template<class _>
void
reporter<_>::
on_suite_begin(suite_info const& info)
{
    suite_results_ = suite_results{info.full_name()};
}

template<class _>
void
reporter<_>::on_suite_end()
{
    results_.add(suite_results_);
}

template<class _>
void
reporter<_>::
on_case_begin(std::string const& name)
{
    case_results_ = case_results(name);
    os_ << suite_results_.name <<
        (case_results_.name.empty() ? "" :
            (" " + case_results_.name)) << std::endl;
}

template<class _>
void
reporter<_>::
on_case_end()
{
    suite_results_.add(case_results_);
}

template<class _>
void
reporter<_>::
on_pass()
{
    ++case_results_.total;
}

template<class _>
void
reporter<_>::
on_fail(std::string const& reason)
{
    ++case_results_.failed;
    ++case_results_.total;
    os_ <<
        "#" << case_results_.total << " failed" <<
       (reason.empty() ? "" : ": ") << reason << std::endl;
}

template<class _>
void
reporter<_>::
on_log(std::string const& s)
{
    os_ << s;
}

} // detail

using reporter = detail::reporter<>;

} // unit_test
} // beast
} // boost

#endif

/* reporter.hpp
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
*/