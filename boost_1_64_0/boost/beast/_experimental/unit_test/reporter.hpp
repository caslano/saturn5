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
BC+DcQFcx+AFcCjsDa+EE2A6nA0z4G0wC94Dx8BlMAeuhePgTpgH98B8+DmcAL+HE+HPsMDY4dV9wLpPmfZgt8MrdvTDYaG2i0mwCVwIY2Ex/B2cCvvBaXAAnA6vgNfBq+AsOAfOgY/CuXAznAdfhPPhNxrvCTgTnlb3MXjAoftPYaqmM4rfezSd56PXAl6o7bU3vAj20XT0g9lwqPanYXAavAJeD/vDeXAAvA1eCpfCQXAlvAw+AgfDTXAE3AJHar+7Cu6DV2s+0uEPMEPzkQVrO6kv2AqOhR3gONgZ5mk+Tzp0ryE8pvmM1rHE/XebzrPu1XK/D6bB+2EhXA4nw1fgDPgAXABXwmVwFfwTXA03wofh8/AR+CpcC9+C6+C38DEYRhqegAlwPUyBG2Aq3AgL4SY4D/5Fv/vxHNwAX4DPwBfhVrgV7oTb4GfwZfg5JL3aHnUPmO5h82iP+j2WtrAZTIGt4HAYB7NgV1gIO8BpMB5eDzvChbATvB0mwD/CRPgwTIKPwGS4TuP5C2wOZd0N/hV2gzp/0n1N1KmP+dOdTsoN3q3Xp3v0uvNH2Asu03nCvXq9WQqv1uPW/K5U42/iY363XK9/f4LyvBs2UreGZx+N/3n7Sg2/SsOthlHqPgYXu+Upz+tYAzhXwz9DObjdf4GhcAu8CL4Er4Tb4DXwFVgA34a/h6/BZXAnfA7uhdvhO/BV+C58EyJyPSiFn+px7R+6j0HGlAr94339rs8HMAoehM3Ufam633DrwwPwK/gNRGRedRS63PMc2Aoeg23hcdgPnoAD4fcwH/4MZ8FabjvR8Efca+BP8Dl4Gr6neh9Ah85/XDr/CYAtYU0YD93pGwQ/goXwYzgZ1jL1qs+PYYyPei3Rel0Pw+GTMFLdOi/XZ670dR/z8ke0vB7VfrYOdoaPwZ7wcTgIlsBMuB7mwCdhLnxa+91TcJ66tV/rM0XKwke/nq/taQGU9VDYA94BL4d/gGPh3XA8vAfeCv+o/Xk1vBsug4/D+7SeV8J9cBV8X/UOwBWargfgD3pc7ajq8yyZS5JOTzuqF2j76q7tqwdsCnvBLrC3tv8REHGM1HHpYpgP++n4dAmcD/trPi6FD8BBcBVMg7vhEPiOxvM3OBQegsM0vVdq+ofDYCfnhfUh+tpe9BmHn3FgrbaXR3UcWAej1K3fG9DnADyH0PD27w1creZMRsNImA5j4BjYAuZoPY6FfeE42A/mwYGwUMtpkrajyXAcLIbT4bVwFpyq4/c0uBReBx+Es7W85sESOBPugTfC/XrcrGNUMp7203JI1fH0EthI3RqetW3/4eto+LoaPljD49brha4Rw0wf14un9XrxjF4v/gIvhM/qdeMFeDF8Dl4Bn4dX6XFNH43Uf/pe0vRt1fRtg43UvSvQgV1X7HEiuYjbZu18uA3uXxXkOAL92cIdWOAS+6UDsWWbj/izcVujB8KA1g5JQ1rjttu83ccNzBKOlyCW/dvWB2s49uAeiG6+ly3ck4UV7eEGXwjdwiS1O5KNJHM85ULC8XslMorfm2BlNnP342/ZzQ1h8C2Fu3AfR5JxD0TykcVuP+QI0q0neUGGkubj6E+DM3FH84GpPizWDkfcdncXcawd7MPxNejY7e/W4OZtG1yH33yO7YEnkUM90cVdI4X0FJfZ542Hlo3eeI4fgCnF6MMM6G2vdzbHFtns9ib8zWa7F78tHNuHlJKmk8hM0mvZ9D1ZjB8MuZb4kNP8ToGL0TlNmAx+R1+EJBAXv7vzeyhS6tZxtwNo2QCOnMK5Ebst4KG4gz6qYWwC34V7EbolyErce2A8/r7sBI/ieCn6h5FR5OmI238qbZS0ZeM/F0k=
*/