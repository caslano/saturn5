/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the function boost::iostreams::detail::current_directory, used by 
 * boost::iostreams::detail::absolute_path.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED

#include <boost/config.hpp>  // make sure size_t is in std.
#include <cstddef>           // size_t
#include <string>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/system_failure.hpp>
#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <unistd.h>        // sysconf.
#endif

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams { namespace detail {

// Returns the current working directory
inline std::string current_directory()
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD               length;
    basic_buffer<char>  buf(MAX_PATH);
    while (true) {
        length = ::GetCurrentDirectoryA(buf.size(), buf.data());
        if (!length)
            throw_system_failure("failed determining current directory");
        if (length < static_cast<DWORD>(buf.size()))
            break;
        buf.resize(buf.size() * 2);
    }
    return std::string(buf.data(), length);
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    basic_buffer<char> buf(pathconf(".", _PC_PATH_MAX));
    if (!getcwd(buf.data(), static_cast<size_t>(buf.size())))
        throw_system_failure("failed determining current directory");
    return std::string(buf.data());
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CURRENT_DIRECTORY_HPP_INCLUDED

/* current_directory.hpp
zo6U29FWyNsuTfvIlrh347qzaR8L5Z6wt60am9Ot4jfTClPfXdBcNK59mj7QcRpPVsyzC0zfb7b4p9kvkjO/tnjM7Ni2OGu2f1tspuFPEf8f+CZlKL4dmr7lCRJmA72I0EZtsLXmsUTC3GKl04oGYWE6hNyfirp98kWRfJk2GLm2aq0NunaxxBXEwUbTk8sa7X3njsmLlq4qbDN7VcQuVmFr31XHUo5koIV29JtDSTAFbg1T4bZqLztSr+fp9VmwJTwfbqNnCrWBX8C2cANsB1OdPzBwT5gO94Md4S0wA66CO8KX4E7wa5gJG4dYMwvbwu5wCBwFc2BPOAxmweWwN1wBd4VrYF/YQs/T3R72h+lwAMyGA+EQOAjmw8FwPsyCJ8Pd4EK4O1wMc+ASOBSuh3vBr+He8ADKcTg8CO4Dx8N94Qy4H1wIR+mezOXu3wWYq2We4rFRztfyPxU2gufCAfB8OBReACfCxXAKvBAugBfB0+DFcBlcAm+Hl8BX4GXwQ3g5/BQuhfV4/tWwObwGtobXws7wetgT3gj7wZvgMHiLyYf+hsAsn3yM0XyM13wUwCx4GBwJC+E4OA0eDovgcXA6vBgWw6vhDPgoLIGrYBlcA8vhe/Bw+AM8AoZsfi9hEpwNm8GjYQs4h3/bwWNhD3g8TPbYb0divy1DKwM7biCBBBJIIIEEEkgggQQSSCD/UgmjRZvR/j+xKE/+MwULfmQFwF9fA5DkXQOge/2vtJlvgmfC850zAqbLGWb7DRw+ZLzz7PFFE6fl6/l/xWHZU18+xXPm2RES/mA72W7knUfVeGx3ntTzDb7SgiPyud+1eRU74cYyt9XYM5cae38DvZ+5H2TmxBLn+TrfN0PCldvnMduVpGnkHHgzT5ki8bcy8/RjJfy31l24vWwlq7tt9ZJwFzNPWB8rYpOY5xV6zmZ/Te5vZOxv78p1gj3F2oq43HnV8tL88W7tRc/86yPPOIOchqzdmH+egTbSs/CfEr9tuFa7rMR7nOc8d91fr/maLf4vWedZPXRe383DEsJsxQzyVO+5+EdYnjJLknCvW/0Jp/Vi4jdnIUiYOsamuD2OjrZTdeZXvQcGNFBSw8c185wPnypzu/WlDVA30nqace2E57naGpzn9m4qdcn/V7SNXJ8Rd31t3PWjcdfvxl3bxZHrT1Mi150918ztmndhYR1L5Gg828NiuJh3IXdG9F0onD4xT14IbYsY5PATBzPnPUPC70L9pnjfBY3HFrdUad/qxhMbmfUgkw4vy4+220Xi38U274RPPA3i4qlKxgH7otcedrX4t7Sv5iS6j63mZt3NWSViA5L2tvzHX39dJuFaSzxrm0ibmeSuLVmBf7QtleRD8z7NlPv2suvzLt1tHWXWwmRK/IkS/yPcf4SEG2nH2OM0jp4StiL+3tizMTQ/+4lfr43zQdgLqTNpYe6aEZ7rtt/6POiWFhG9qUmk/ZaF/dqvNbhZ3PcNGmHTvV6eY+WXlERtt04bSHXbgMd2m2rqsr6UHeUppcm1pIl0OqmUNrlKyoX3TdvsK3q9JD1y3U6ey1yzXg/V6yv1+oYS9/7YNr1GjR+t8NwG/oDOI++ZpWIzkzY9q6SgLF8btV+bTnPKW8IXYXNo6WMv0/j4J6Z9eH6nDhT/d63tKBW/trWS8vC0CVPP98h9071twNg5J4nfbVy3wLYwzrSjleK+g/5W29ZyuU4iLSZt/CaPpw6jNrmxEuYd2kOKZd4hz3m0Tv1dImGu9W1jP+HfjDaWoG3sidRo+8oKb9r3M5z21aUstn2FtX2leNrXSm1LKVp+uMnzSRNupEl/RyN54n5tU8v0eqm2mS/0+lq9blrmaUM=
*/