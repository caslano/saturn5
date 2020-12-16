// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_POSIX_START_DIR_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <string>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    typedef Char value_type;
    typedef std::basic_string<value_type> string_type;
    start_dir_init(const string_type &s) : s_(s) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor&) const
    {
        ::chdir(s_.c_str());
    }
    const string_type & str() const {return s_;}
private:
    string_type s_;
};

}}}}

#endif

/* start_dir.hpp
Vf089KDEhzmuoGdidZoc3MdzU1Ms+v5lku6MUY1WXc2YiZIxU7zwa2vCqrneeq71mKDvkEnfyfmPsjn/1nM7qayv4IeclAEXwZ2c21Xh5rlVT7nW+Vc/S2ySdNOc3WjvIKOs0+bcUlbg+tH6udn2XKr0tmMpBn4S4V+/IFTXo6zIvnWwGq/jVscNetxdF+mV92fWqmh73nXd7McNZUMpo6XtWtcqf+C8qcdcnNTLqb870U72u+nfzRVlP1rPp54o9Uyk3omckvK7OAPeu+jn3R0SP8ESr869qnsdKX+f4zPuXKMcfVSbuBLlOA0tz/YpqTmW9097pNx05zDqeoXTzfNxqE0dJa96VjWvld2SN8s5wOnR91jDvMfK/Bcu9brGUu/hPGCb35vYKmWMdQ51lDWWcXds4bxGzfH+ujew3s9SMyzjo7eU3Ynz28gnY+8D3/EYH7Uc3vn+Jua0PvH+Z7WOds9qkmZSvP83+4Tugb/H72CfaGN2XOGwoFTg3/q7A4TCf89R7ycJpLN8Y1/NA1G/sja09IWarALuE8ruRP0m1Ndc8e4V8fy+foITkj/J2+Z074vLYdlJWRZbleLbnvzRNiZF2XSMG+2V1/p02pCL25aYfO/S178a1DN+blG2MMW3JSnu+sf/LVuS32sdA3sbmeLbbhTXlqS4tirFtaUqrq2KvU1T0bY2J8x1puW36RT5tji/PS1/P2r5+1nL30v03/IuQ/5ewN9jLX+Ptvw9zvL3GMvfxwhL/HoVpSNaRpDfSapu9cnuhA1gKdgQ1oFXwbrwGtgZNoYZ8HqYDW+AE2ETOBX+Dd4HW8MZsBmcBW+CC2ALuAzeDNfDVrBApZe1ul1K/6B0KctgBmG0S9m/8kMlGobCWBgGG8AIeAOMhDfDKNgGloZ3wDJwNCwPx8EK8H5YES6BleGjav8JFf8UrARXwSrwZVgN7oTV4RewPjwBG8JT8GrorXwj6ITXwhDYGEbA62EUbALj4d9gOdgM1oHV4FWwJbwOtoItYGvYEd4Cu8OOsI+S91P7aWp/MOwER8LO8C54O5yt9h+B3eFjsAdcqvZXqP0C2BO+BnvBj2BveAAmwSOwLzwHk2FDJ7oh2ALWgl3gJbAPvBRmwDZwLGwH58D28EGYDJfCFLgd9ofvwCGwJOc8FzaGw2B/OBLOgWPgYngnXALHwdVwPCyAE+Ahtf81nAx/gHfD03AqjHDzXAdLwWmwkdq/Hs6ALeBM2BrOhj3gHNgHzoV3q/174Xy4EC6Ay+AiuBkuhq/BB+H78CH4BXwYfgeXQIeH95swAj4Ko+BjsAJ8HFaFT8AGcClsBJfDTvAp2AuuhHfAp2EafBaOhj3gE3AdXAVfgOvgergJboDb4d/hLvgi3APzobKLU+8UpCxjWYBd3H66vh78FLaEB2Eb+BnspdYGz1ZrVY+DX6l54hu4BH4L18BzcBM0vPVR6XfB7+A++AP8Fp6ABOMk/BGehpWo11lYFx6DXGty3M6QtNKO2g713KeebZfBagTyytaWdF52gJVhR1gb3qrmv/HwajgB3gAnwiawG2wOu8NbYS/YBfaGKfAOmAb7wSzYX82bA1R/pMG74CA4B6areTIDPgwz4SMwCz4Lh8C1MAduhrnwVTgMvg5Hwn/AUXAnHA0/gWPgETgW0qc0lutXtStarb0fDyeq/uroUM876nlxGaxFuEn112TSRcIZsCOcB7vD++Eg+KBq18NwIXxUzfePw61wKdwPV8CzcKWqz9Mw0sH4hXXg87A5XA87wQ2wB3wJToab4DxYAB+Bm+E6uAWuh6/APXA7PAJfhz/AN6GHdr0Fy8KdsDx8G9aH78Br4W54A3wXtoE=
*/