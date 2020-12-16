//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_RECORDER_HPP
#define BOOST_BEAST_UNIT_TEST_RECORDER_HPP

#include <boost/beast/_experimental/unit_test/results.hpp>
#include <boost/beast/_experimental/unit_test/runner.hpp>

namespace boost {
namespace beast {
namespace unit_test {

/** A test runner that stores the results. */
class recorder : public runner
{
    results m_results;
    suite_results m_suite;
    case_results m_case;

public:
    recorder() = default;

    /** Returns a report with the results of all completed suites. */
    results const&
    report() const
    {
        return m_results;
    }

private:
    virtual
    void
    on_suite_begin(suite_info const& info) override
    {
        m_suite = suite_results(info.full_name());
    }

    virtual
    void
    on_suite_end() override
    {
        m_results.insert(std::move(m_suite));
    }

    virtual
    void
    on_case_begin(std::string const& name) override
    {
        m_case = case_results(name);
    }

    virtual
    void
    on_case_end() override
    {
        if(m_case.tests.size() > 0)
            m_suite.insert(std::move(m_case));
    }

    virtual
    void
    on_pass() override
    {
        m_case.tests.pass();
    }

    virtual
    void
    on_fail(std::string const& reason) override
    {
        m_case.tests.fail(reason);
    }

    virtual
    void
    on_log(std::string const& s) override
    {
        m_case.log.insert(s);
    }
};

} // unit_test
} // beast
} // boost

#endif

/* recorder.hpp
5k1bObprKKnsyaHZY2ib19N8VH8To3lr7P6lm70MqaW690XHaqe2Wy1fDRdp5sxrxL2Z62VXPcaKq8RxMfXcxvtaYfr/Kgm3y3G3Xmd1/J8g11l9rrhFdJ4hNVdhOyGo4vcaNQ215Xzn+Dy/ZQu+me55Nd/wtva/nsF30NzXhOzSiteElGqM6drXrDGdfHruRZ2fXHGN6XYqOKFsPYY+wRfT9eO3fvaiouu5RzbyDNaOiM/nHtnY33mlS/e1HfizPV1Fedfl+F3zQtczXYlnkC5/e9UL1V5+ps6HrtI1ztll4wk3f6RLJvdVr3HeKWEGOTqb+ZDG43+NE/+q1zhVx6MP2Oek94p/D0cb2xpny//QGmefrr7XOB2bvcuz6jVOwvhf41R/+xpn3G9sD/7WOI/L9/L+9Tbe/1k2z33bivdng92/rXjsq3H8gSteqVHvpp8eb7nhnZbtlve/0J8NeX82zM/cFvoEsS3/8wsjh+2ZdvXDWT+N67vz/EOkp7fE3/2Hdm2Hfj/z5nX9RkYeqbXwBsq5v/v4JX3+3De96y/zGz0Yf90nxRewaLNNbLZvfWv4l4/kNz38650r+rzf6qljvHMlx0s+HtHi3oy1debV3eWM+P7hZ8SOOMeLmyw4MWfw0pHz2l+5PCS59iF/Nt7/ebbl/dnAT5N07r8x+7bVjb/beLhR1sEdc19o79/GfrGkc+7Dy/Z+sj0hYc72y6fl3br6iL9vBJy5zX9/NvBDOI5+2v19D6/NT14cX/rG1z/f2rbMdn004tA5J2OYzNcC9XcIcgw3fU7fwxR/8asBdZlA7CXXg51hI5gMo9R9DKYgGRp+qIYPhMkavr3aX+4A4+G5MAV2gpep+xgMMu/fyfuHJr2nNZ4hDFxt4FDYAw6DKfAK2BuOgBlwNJwM0+HtMAMugdnwEZgDn4Fj4UtwPNwJ8+EBOAmegsWwmfuZKGwFp8EUeB0cDmfBq+EN8Do4R+2zzYMr4c1wHbwFvg4Xws/gIvgLvBUGqH2rNvAq2BbeBrVe9N0wriM+6qUBevVgCIyCoTBG3WoXSt/FYoal4e12oS5AryHsDpvDHrADvBD+DqbAgbAPvBL2hKPUbdnvCdH4p2v8dvs9HdCLgPGwPTwXdoIdYSLsBrvDTlp/CXq+RDgYJsNM2AXmqb75LoCWS6Ke127Hv7WWSxsYC9vClrAdbAvjYLy4NR/m/Rh+a7vrIO1F7ZWiFwl3wJ7wNZgKX9fyeANOhKXwWrgbTodvw7vgXrgeHoNPw0Da+yvwTdyvqvs9+D7uj9Re/C/wr9DdRw/AxvAgbAo/hl3gJ/ByeEzbY6Dao/7CnR74JZykx2erex48Am+DX8E71H+FulfBb+E6jXe9+r8Iv8e9A/4AX9fjH8IfcR9XN+1Z3EHwZxgD3cfj1Z2obne5lyAJWo/Xaz02hCu1HsO1HhvBZjBC+39jbU8ttD1Fwi4wCl6gx1NgE9gPNoUD9fhgGA2Hwxh4tR7Pgs20nTWHE/V4EYyF09R9DDKW6HsOlKWmOwQu0nS/Sv4i4E4d93bBVvBNmADfgpfDvXAcfBcWwX3wD/A9eDf8CK6AH8In4F/hm/BvcLf674cH4UF1q11MfQdA3iUgfZ52MT9BLxJ+AZvDbzR9x2EHeELT6bYXexE8iXsQPAWnwNNwPvwF3gsdaqetBnwYBsInYC24AwbB3bCu2isNhp/D+vAUbAB/hg1heyf1CS+HUfAq2BQugDFwPWwGn4Gx8DnYAm6DLeGbsA18D7aFtSiLeFgPdoRhsBNMgZ3hcNgNToUXwBtgd3gn7AFXwIvgGtgLrod94GbYF74ML4ZvwFR4EPaHX8MB8Ac4EP4=
*/