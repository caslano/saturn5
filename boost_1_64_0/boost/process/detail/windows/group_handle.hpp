// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <boost/winapi/jobs.hpp>
#include <boost/process/detail/windows/child_handle.hpp>
#include <boost/process/detail/windows/job_workaround.hpp>
#include <system_error>

namespace boost { namespace process { namespace detail { namespace windows {

inline bool break_away_enabled(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    return (info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0;
}

inline void enable_break_away(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
        throw_last_error("SetInformationJobObject() failed");
}

inline void enable_break_away(::boost::winapi::HANDLE_ h, std::error_code & ec)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;


    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
    {
        ec = get_last_error();
        return;
    }

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
    {
        ec = get_last_error();
        return;
    }
}

inline void associate_completion_port(::boost::winapi::HANDLE_ job,
                                      ::boost::winapi::HANDLE_ io_port)
{
    workaround::JOBOBJECT_ASSOCIATE_COMPLETION_PORT_ port;
    port.CompletionKey  = job;
    port.CompletionPort = io_port;

    if (!workaround::set_information_job_object(
            job,
            workaround::JobObjectAssociateCompletionPortInformation_,
            static_cast<void*>(&port),
            sizeof(port)))
        throw_last_error("SetInformationJobObject() failed");
}

struct group_handle
{
    ::boost::winapi::HANDLE_ _job_object;
    ::boost::winapi::HANDLE_ _io_port;

    typedef ::boost::winapi::HANDLE_ handle_t;
    handle_t handle() const { return _job_object; }

    explicit group_handle(handle_t h) :
        _job_object(h),
        _io_port(::CreateIoCompletionPort(::boost::winapi::INVALID_HANDLE_VALUE_, nullptr, 0, 1))
    {
        enable_break_away(_job_object);
        associate_completion_port(_job_object, _io_port);
    }


    group_handle() : group_handle(::boost::winapi::CreateJobObjectW(nullptr, nullptr))
    {

    }
    ~group_handle()
    {
        ::boost::winapi::CloseHandle(_job_object);
        ::boost::winapi::CloseHandle(_io_port);
    }
    group_handle(const group_handle & c) = delete;
    group_handle(group_handle && c) : _job_object(c._job_object),
        _io_port(c._io_port)
    {
        c._job_object = ::boost::winapi::invalid_handle_value;
        c._io_port    = ::boost::winapi::invalid_handle_value;
    }
    group_handle &operator=(const group_handle & c) = delete;
    group_handle &operator=(group_handle && c)
    {
        ::boost::winapi::CloseHandle(_io_port);
        _io_port = c._io_port;
        c._io_port = ::boost::winapi::invalid_handle_value;

        ::boost::winapi::CloseHandle(_job_object);
        _job_object = c._job_object;
        c._job_object = ::boost::winapi::invalid_handle_value;
        return *this;
    }

    void add(handle_t proc)
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            throw_last_error();
    }
    void add(handle_t proc, std::error_code & ec) noexcept
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            ec = get_last_error();
    }

    bool has(handle_t proc)
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            throw_last_error();

        return is!=0;
    }
    bool has(handle_t proc, std::error_code & ec) noexcept
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            ec = get_last_error();
        return is!=0;
    }

    bool valid() const
    {
        return _job_object != nullptr;
    }

};

inline void terminate(const group_handle &p)
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        boost::process::detail::throw_last_error("TerminateJobObject() failed");
}

inline void terminate(const group_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();
}

inline bool in_group()
{
    ::boost::winapi::BOOL_ res;
    if (!::boost::winapi::IsProcessInJob(boost::winapi::GetCurrentProcess(), nullptr, &res))
        throw_last_error("IsProcessInJob failed");

    return res!=0;
}



}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_handle.hpp
hs5T6OQwT6Hbr8d09fjvHvFXfeNB1jfMWPHAimPF/5a5C+HmKxIf6VMOlXsmzYLIypHN0mtFRCb1qrjXdW0S9ahtjYday3FyTsW1FnGXWWst7PMjx4025G+QOzBO1V7WIGMuD45BB3cDNRzHcPcT9h2iW8MdbDNukuv+TvMr8DfcGKVqg8W+tttpLFm71e/pUjp132WF2NdzO40da7d63f/03IJpsn+W5PN9Yp+m9lelDZDrDk5jx9qvinuI8I5rG0scMF+P33DNfq1y3diIpY0OebfV/YbhpYG2tYdxpv7+K+4INeQdUfQXid3ZhsM7inw7DTfva5PEP9Yd0n/R/q6XeEzSfYspEk6aU99F9L3z5H1e61+Bvrw36r3IxhTa/f9cwi/8lf/qO5+u59/DfICxt3e36HYutH1wbhfmplOmMEqmzZp0rSNtQN1TbAP89T3pq1jfO9Tj3op1sK7v1bNLuVX1vT4zVcqjyA6E1AX255VtEuUvlwjEwotg81q8884PPq96Z+3QZ8zpecSdfexL7Vc5q7kuL8lwyQK/TlxoubX2+xb79dYe5HKdEFJm1dii2B22PTu5OSWTc6ba51cliU6TwB7V5EWGXFcz9XiSuLHeYz6SNFRlRCpCP0snRXaOmWfcGxovPTfAI9dn28YRxhZC3Wd+T/wYaMaTU1qHsMkeHfb14kcH7kUTnV9tRBah93Q7ItduPTejh1x/acg+DqP9OR7c82E6Wz7c7/gNPKi7bExwz4fS6532fKjFdSTXa2VNOVTl/YZ0q6zHhf+mrcuzLruqPWkscabOUWv55lvXUj7PV+WzW17As7ewPANug4NoTzotlPI5IY/GUObl5Y+llOrNwvXYuPUtySpfoxeK3Kn84u9vtycjxf4e06k9UW5Dy7W+tylXSHtiVEfbqf7dLe6bmcH616vb7q7iPg7zuujEKZkpsl9E5vndetor4Z9U5zpbe/+oo5D18zJG/IsyzuLeR3O99rffBXQ5qFGJOm/PFVadl67KCPfL1p90rPec6jMpPwcWWmtD7fXbyvFqbMYI2J+HuSCN+KW7uS4tKCqaNK04R7psct8WyPcMuXYsH7gL/Y6m92FzKhPoh3xjLMmdYDjP39S6tn2QS6bM0uWjrtjX08+z7OfhsA7KE+YZ9KctTdIWMo9Ep0G1K1oucZX8bKvOyyj+G3v3AR9FlQdwfDe7CWlAOgECRDpSDAhIU3pvkSJRShJIIDnSTEIHDYgUQQ2CgoASEGmCgqCCooSiFFGRDnIYBD0UUES6HNxv//vyZrK3Obn7XPl87kPu/n6ZN2/amzd99k2yc8STraxT5Wy2x8gpsj2mxg9PlDM8tkZGKCcxxnMQ3X6ycd+rhgw3gSv/LhyvI7jDsZb8bZhfNU6mcNCSp8vJSDd/M123uaa307aS5yF360QPb7TNn86vyjP1+1N1pP9o60CGHmL1NK0PFsc0jaZTycdTJdO9W252mM57ZDwR+p7WWGcZsW084fo7O8nfXvp3tTYij7thjOMVy5udqu8RPyzz4avLbZoM48/TDI7/ehmd30bhH/p+YS3JN85amTr1KGs72erh3Afo6YZYGlPXqA9SzzYSoUxwvulY8Cox3xxybLib3+b5O7fPqUbbHZumFLYRUF+3YfCikVbfoq6PW+q0JnrfIedBun6p+q3PhXT9kH1FjAzP77IL9xWqbkfIXsf5PRl/rIq9qdtrp+q6ra5eEhiPfHeBdFJMxxavaXJ/0+2+g/G47AuoT+73GzpvkHmdt9Pv8spx3+XbEHr/fUCG/VSvy1dlnpob42IfQEN6fNwpUZ9jPCZ5QvQ7oO6eIf0q462hz0NyZZgIU/0=
*/