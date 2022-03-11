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