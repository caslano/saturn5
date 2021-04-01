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
F5Q+KeHzSgF9Pd9AlShZXMVo2PpWe91dDVcxBPvXUG+ODki79ajgPFtBLo8v5JUjCKOcfO1D2KxOJO2lhHT3S2/qcP+x2GjUM63gxdzLgY+Sw4kmbOYJhcbf5rGEX2yJ5d/dK1pC69whUOyDNGLmCMHXEM7krJRwF/Pfn8VkvXacmF67qAoR6YqRji9Q9H842MucyyIJYaFoRcjLyj7DDiWUQeSP0Nz8y/1e99SrA5XRxoHMybrZE9ZL8TsBfa4oKUHhE55tCZTQZ/uEHOQ+MzpaDinz5wp+WcZJ2/AHYiR28BZvhIXLETAEgnVdVIIpBtAJ5Bub5XMjmOAQKEMzvd9PXQimUoP8S0hJHEuuCsNm+y7H+VlgtkPFiB9OjXV3e17PXcu1krRbaS9unPMUZzrvfCuLq0gubzQnrY85RyMoNG2NfQBuZJ6chdshCGlw+z0i98qbAxIHoJ71VUFHMJJJmVjbRwrF2y0+6dfecLu9gkWUY4FgYrHY3+O7b8z3UOiD54bPyh2igzhP6JVmKEEISBeMqzNZ/2hG1QMMxEX0mnIZtY1qqO9oWw==
*/