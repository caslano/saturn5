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
e+F72Bv3Yj88gTH4HT6Of8EBeBkHYolgzsPQH+MwGAfjEhyGqzAZV+Nw3IUp+GdMwyuYiXcwG0NC2K9hJI7FJZiDq3ASrsbJuAOfxeM4FS/h82gNZbvB2TgbF+DL+BrOxfdwHn6O8/E05qEljGsTfB2X4TJcgStwJb6Dq3ALvoWHcA1ewDy8ihvRrwzbK4bhh9gAP8a2uAWHYz6Ow204Az/F+fgZLsJduBj34kb8CnfjfryKh/GveAQDwtk+MQqPY1P8Bjvht9gDC/Ax/A5n4l9wKf6EH+EFPI4/43f4C17Ei/g7XsKyZTnfwKposXOcQStGow2HoR3T0RtnoA/moS+uQcd87sFkur/GkngSS+MNDMIy5Ti/wPuxHDbBCGyNFTAZK+KTWAlHYhS+gvVxHTbArfggHsHrjnqMN/AMepJ+Bb3wJp4mPag89xXproXV8CGsjr2xBj6OtXEQNsYsfAhzsRmuxodxHbbEj7EVfoFt8BS2x79gB7yJHdEngu0UI7Eb1sDuWBt74oMYjc3wURyIvTED++BEfAynYQy+gE/gWuyPW3EA7sWB+A3G4l8wDn/BBAyqwHUSVsBhWBuT8EFMxuY4HNtgCnbCVHwcn8BRmI2TcRTOwNH4Oo7HdfgU7san8RuciD/iJCxRke0a/fBZLIPTsBFOx+Y4A+PwRUzHXJyEr+Ab+CquxIW4CxfhUVyMJ3AJ/o7L0bcS2zeG4kqshquwEa7BTvg2RuO7OALX4wR8D5/BD/B1/BDfw4/xU9yKNSOp78j9CO4LqHZ9VTvl+RhJ+KsfG50jnwf+ihXwEt6Hv+EDeBkb4lXsjNdwIN7Awfg7/glv4Ri8jTPR4sl2Dlb8AG24Ce34CXrh51gCT6I3nkZfvID++CuWQpuV7RQDMQDDMAjDMQQrYBmshGXxASyPO/A+3IOV8QBWwWNYFR3ls0u3e0idVuUTRmxW957qkc9hQ6yGjbE2PoTNsCl2webYD1vgn/BhTMeWOAZb4QRsgy9hW5yL7fFV7IhvYydcj11wO3bDw9gTWzJ/fbE9PoY9sB/2xhi1PN4eqk0o1e5cPj5C3FLrO6EE9RxHYUMcjU1wDHbHsdgfx2E8PoVp+DSmq+4s1f005uBsnIjzcAYuxpn4Jj6P6/EF3Ihz8BOci1tU93Z8BT9V6YdwPp7CBXgGF+FFzMM7qruEle0BfXAx+uISDMDlGIwrsCquxIG4CjPwLczG1TgZ38YX8UtcgN/gYjyBq/DPuBZP4gdYgFvxFH6q5uN7nIs/4iv4k+q+g5uwhAfnx1gGP8PquBOb4i58BD/HTrgXu+EX2Au/xMG4D4fhfhyFB3ESHsJpeBjb2tgv4CVZP+o34Ko9l3y8QGSTLk/BqTflMAm/wRFquxuFV3A0elipF+iF4zAEx2NZfAqr4NMYhZOwKT6D3XAK9sGpmIHTcAxOx6fxOZyJM/FlfAGXYS6uxln4Hs7GfHwZd+Jc3I+vqu35NfwVF6OPB+sdw3AlVsG3sC6+je1VdzRuwCfwPUzAqTgWN+FU/BAX4Rv4Lr6JH+AW3Ir5uA+34XncjpdxJ17HT/Gm6rbanN2euBMjcRfWxd3YCr/C7vg1RuNBHIiHMB4P45/wKKbgMUzD4zgWC3ATnsKt+B1ux9N4A8+g1U5dQBuew4fxZ2yPVzAar2MC3sAUtHqx3aMHjkMbPoue+Bp640oMxzVYFj/DSngcpTywKt2enpznYCmsgRWwJlbH78nXAMvT3R7blmA/h+0wBtvjEOyAKdgRs7ETTsJyDDdNDf88RuCL6FiOOehD934sjUfwJumn8TaexV/wMl7CGxhEPpbREoq+uIf0IPwCy2Mdx3xjXWw=
*/