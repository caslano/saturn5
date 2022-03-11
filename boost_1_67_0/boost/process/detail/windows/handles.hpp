// Copyright (c) 2019 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_HANDLES_HPP_

#include <vector>
#include <system_error>
#include <boost/process/detail/windows/handle_workaround.hpp>
#include <boost/process/detail/windows/handler.hpp>
#include <boost/winapi/get_current_process_id.hpp>

namespace boost { namespace process { namespace detail {


template<typename Executor, typename Function>
void foreach_used_handle(Executor &exec, Function &&func);


namespace windows {


using native_handle_type = ::boost::winapi::HANDLE_ ;

inline std::vector<native_handle_type> get_handles(std::error_code & ec)
{
    auto pid = ::boost::winapi::GetCurrentProcessId();

    std::vector<char> buffer(2048);
    constexpr static auto STATUS_INFO_LENGTH_MISMATCH_ = static_cast<::boost::winapi::NTSTATUS_>(0xC0000004l);
    auto info_pointer = reinterpret_cast<workaround::SYSTEM_HANDLE_INFORMATION_*>(buffer.data());

    ::boost::winapi::NTSTATUS_ nt_status = STATUS_INFO_LENGTH_MISMATCH_;

    for (;
           nt_status == STATUS_INFO_LENGTH_MISMATCH_;
           nt_status = workaround::nt_system_query_information(
                            workaround::SystemHandleInformation_,
                            info_pointer, static_cast<::boost::winapi::ULONG_>(buffer.size()),
                            nullptr))
    {
        buffer.resize(buffer.size() * 2);
        info_pointer = reinterpret_cast<workaround::SYSTEM_HANDLE_INFORMATION_*>(buffer.data());
    }


    if (nt_status < 0 || nt_status > 0x7FFFFFFF)
    {
        ec = ::boost::process::detail::get_last_error();
        return {};
    }
    else
        ec.clear();

    std::vector<native_handle_type> res;
    for (auto itr = info_pointer->Handle; itr != (info_pointer->Handle + info_pointer->Count); itr++)
    {
        if (itr->OwnerPid == pid)
            res.push_back(reinterpret_cast<native_handle_type>(static_cast<std::uintptr_t>(itr->HandleValue)));
    }

    return res;
}

inline std::vector<native_handle_type> get_handles()
{
    std::error_code ec;

    auto res = get_handles(ec);
    if (ec)
        boost::process::detail::throw_error(ec, "NtQuerySystemInformation failed");

    return res;
}


inline bool is_stream_handle(native_handle_type handle, std::error_code & ec)
{
    ::boost::winapi::ULONG_ actual_size;
    auto nt_status = workaround::nt_query_object(
            handle,
            workaround::ObjectTypeInformation,
            NULL,
            0, &actual_size);

    std::vector<char> vec;
    vec.resize(actual_size);

    workaround::OBJECT_TYPE_INFORMATION_ * type_info_p = reinterpret_cast<workaround::OBJECT_TYPE_INFORMATION_*>(vec.data());
    nt_status = workaround::nt_query_object(
            handle,
            workaround::ObjectTypeInformation,
            type_info_p,
            actual_size, &actual_size);

    if (nt_status < 0 || nt_status > 0x7FFFFFFF)
    {
        ec = ::boost::process::detail::get_last_error();
        return false;
    }
    else
        ec.clear();

    auto &nm = type_info_p->TypeName.Buffer;
    return type_info_p->TypeName.Length >= 5 &&
            nm[0] == L'F' &&
            nm[1] == L'i' &&
            nm[2] == L'l' &&
            nm[3] == L'e' &&
            nm[4] == L'\0';
}


inline bool is_stream_handle(native_handle_type handle)
{
    std::error_code ec;
    auto res = is_stream_handle(handle, ec);
    if (ec)
        boost::process::detail::throw_error(ec, "NtQueryObject failed");

    return res;
}


struct limit_handles_ : handler_base_ext
{
    mutable std::vector<::boost::winapi::HANDLE_> handles_with_inherit_flag;

    template<typename Executor>
    void on_setup(Executor & exec) const
    {
        auto all_handles = get_handles();
        foreach_used_handle(exec,
                [&](::boost::winapi::HANDLE_ handle)
                {
                    auto itr = std::find(all_handles.begin(), all_handles .end(), handle);
                    DWORD flags = 0u;
                    if (itr != all_handles.end())
                        *itr = ::boost::winapi::INVALID_HANDLE_VALUE_;
                    else if ((::boost::winapi::GetHandleInformation(*itr, &flags) != 0)
                            &&((flags & ::boost::winapi::HANDLE_FLAG_INHERIT_) == 0)) //it is NOT inherited anyhow, so ignore too
                        *itr = ::boost::winapi::INVALID_HANDLE_VALUE_;
                });

        auto part_itr = std::partition(all_handles.begin(), all_handles.end(),
                                       [](::boost::winapi::HANDLE_ handle) {return handle != ::boost::winapi::INVALID_HANDLE_VALUE_;});

        all_handles.erase(part_itr, all_handles.end()); //remove invalid handles
        handles_with_inherit_flag = std::move(all_handles);

        for (auto handle : handles_with_inherit_flag)
            ::boost::winapi::SetHandleInformation(handle, ::boost::winapi::HANDLE_FLAG_INHERIT_, 0);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code & ec) const
    {
        for (auto handle : handles_with_inherit_flag)
            ::boost::winapi::SetHandleInformation(handle, ::boost::winapi::HANDLE_FLAG_INHERIT_, ::boost::winapi::HANDLE_FLAG_INHERIT_);
    }

    template<typename Executor>
    void on_sucess(Executor & exec) const
    {
        for (auto handle : handles_with_inherit_flag)
            ::boost::winapi::SetHandleInformation(handle, ::boost::winapi::HANDLE_FLAG_INHERIT_, ::boost::winapi::HANDLE_FLAG_INHERIT_);
    }

};


}}}}

#endif //PROCESS_HANDLES_HPP

/* handles.hpp
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
*/