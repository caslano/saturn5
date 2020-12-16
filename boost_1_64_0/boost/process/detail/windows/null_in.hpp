// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_NULL_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct null_in : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    file_descriptor source{"NUL", file_descriptor::read};

    ::boost::winapi::HANDLE_ get_used_handles() const { return source.handle(); }


public:
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(source.handle(),
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = source.handle();
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
};

}}}}

#endif

/* null_in.hpp
3tf3qvuSum4IkHLiWKy626ru66q7l+r+a2TRY2ETxmdUceaB6BnKskn+HK4yYx03vvk859D4ESnZbs5Z3Ndvhtf1NUPqN0dT93WbvK7bQuHbom6/Z6rzqzrB+csfHwvcnycY+wjmkXSZR/Kav0+q50XKrZk6H48s7xz5IGbAhgPxLGVb4L7cYt2f7xnHgL/IcH2snzG2Elb39w8L3JepPgbU9pdzEetkzpZ3FnMMKPgny1pPU+eX01c3+3md1+11Whl8WOavuaUaa66hxUP/du6spPdhrjvLuWILCuRiWW65BDMPITnnzOeKvsbvKfQ51CkZ/nGOv35uxym/GVDj9S+nzkGtOaf8PbykX0XVL4p+u5mGLcPL31bOr5eXp78nx3TJU5l5cPx7T5hxXfqc3Mcs/nzE/z9QB+VYpdNlXcj2Pdq/6HVkjn/R684v/Ited15zyX9H5y+6fyio6FyAO/S0420sEcF5ZMmi9Tx9FG9P/0Ed7yTDXLFeYwr+Vg/358wli62fbuqzu/x8jH8kr3G7r8/kN+pof1lbQzMKfz8Uhm2l/+/Wv8qWZDXXN32u87PkKaGOoSyRdMczvcf0dsJ4Eyym++3vS57XLNMsNrkmq0q551RQ90lyfpjItOU+SQ5lO570LSTYJoZxRdaEeyOV/NqpuySVuV9S0VbDy8Pfo9Td3icpnO9VpRzzUFKfX/eWbptsc/OY7oAKapsLn/hmMducHtdNGTbQdVyF25qMb3QF5/bCxWToxB5Fr/MKy2ChKc8Eta0VLld+kfP9u3v3m3Xh8u63+2t6bzfbVtFtTtcj2T7elvFSR+9zdh9U3V6qW01Xb09/LVl0+6tfytkdp7a/Dqq7QN2DXVeq6PCbShUd/lypotuvZ+mi+UuWNvKbr08SmD+Ler/W8c9jxCLH9ltab7/Z6TxcTlXnrW2C1TfFLeo78tyHTpG8n+l1H0t3sde8pV23x9T40RS8+ffTSyTPKPbYQfq+fVnZZ/i428b1OF3vaclzWEyS/h9x36ms+22+tPvn0DJt/F36/928SP4SUn7Z8kOAwucXxvZFuZm28TEynreYZqjrbyHIo7ZBNS1vi6f+LeCnkjZAb0vvSrfx7PoN6Q5hj+Ot74F9Hia/0ZLfZuVjOBEcavx+TL7DbzdtK3dxjtwmWH2P3fXZhHkdku5vvndmel5BWZEmZVWkDhZUcU64PxXUT3mggvM3OdTBIUnpGSMyYrk+y3LWwa8r6OdVuox6St7B7uuc9LOafjvILLg/Xui88oxV5mqITEPOrZlb+ki5O/LkS96lLMursi3c4a+PpHW0mp/Rqnqt8h/i3lqA8RtVjtF8xF4fC4KxjkynC+P1dKbpaTWg7pTW19iuz67CZLhJ5MmU+3dJlHcUZTuPvP7+kbYgv05+Vb3stgocHfheZXH3TYq9/0J/xh+s6+E66Q6UfXLh8WBcqL6/Wvy1OPvhBYH6vov+/RvjK0yrT5Kud6xv/UxMnwvZ9e9vZP/2VoC+/yLdewKK7j+zA41u8/lLdA3njJVVdS8UZ0Xyvlqgs+6lZ4yJTRydzas9PNrPch7r9su4R+vt+h3J62W9RW0rbHNChmes3SzbzXWRdKMuHpTxZCY+ab7HJf0j3NVNhnXdd8rs8ZusRLf7NfO0SpcjwcKSZBnP3k5J/528p1+fPOo9mKDC56Nt5Dd3Z1Wev9s3qt9dfyD9PayO/gHBahqm5Skh4/PV76VYpPsd87NavZ8+raYVbakr+e2knZe07TL9RVLneXfKNP7AIH3OIuOQ+VfDXzZNr5QxvYTRpn17pPRP1dcFzvwrLZGSVrhMbGeyWMb+5hHJV/3vys1xrXCGbS4=
*/