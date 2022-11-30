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
                    ::boost::winapi::DWORD_ flags = 0u;
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