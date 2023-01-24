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
KDXO2PsQyy7Z43Naw7JrS1dvb2wl6IiZi3KTbllYUiqqD76nWy8kM9kcb7ZgvYj0Dg5Zr0/20qAn4+LdUrY1mE0/vkiDUQ/YIsgXIyC9meeUXxhRfAaxLvhDLyN8sFV9G8L2/BnQakDkr70/uRKlevMaDQfABJPRFUYCTVGPOLdVceGWpatazUYW1l8hOOMY2DMogTf6GrZAG/Ku3vrPG5nxcxyPTuGpf9y2JvEwJm7tAGUlWK9+1PzLaRI0mi3qS42qMQvD76a8/e6PWzDcaCUXc1dp68OmcDetq1Y9SsxUB9toMmpss/DXp57kD9WjzyuEmnQ4kV+Cu1oLbnQ6EUfb1Pq6pmjbAiqrMsV7wE3FXtb9rKUm5MVpO6HVN84hj6/Ipiigadr5BU7LLU163qOCeMsNAzUdKHTKc6fwAxIUy3aFBzFWC3hpUNRVHVpz4aOjhg7Xj+t2gyF5x7LkMo82to6IjOjmhVd5mqe0e8jQaGGTpPpxnYGa2ksKzQCp30K6D7YNUo8DPY25saPyZ4NlNJN9uAb1ANUlV0YDky6/YP67Lqcbe8hNvUCsOE8PUYPMuQZ4le3RbNyJ3PziRY/2kmPR5tXO8eWNt1PP2410pzHZnux9m1umZKbi9Gh64++EeNSemu+nRxi+vTEiuX7+0YQRRvsoVoR2PvAiRDo9RxprtG/gy2vR27j1MG9k3onuRl9wLQ5xwhY/
*/