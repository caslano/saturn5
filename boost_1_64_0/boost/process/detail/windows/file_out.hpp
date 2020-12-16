// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_OUT_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_OUT_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<int p1, int p2>
struct file_out : public ::boost::process::detail::handler_base,
                         ::boost::process::detail::uses_handles
{
    file_descriptor file;
    ::boost::winapi::HANDLE_ handle = file.handle();

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }


    template<typename T>
    file_out(T&& t) : file(std::forward<T>(t), file_descriptor::write) {}
    file_out(FILE * f) : handle(reinterpret_cast<void*>(_get_osfhandle(_fileno(f)))) {}

    template <typename WindowsExecutor>
    inline void on_setup(WindowsExecutor &e) const;
};

template<>
template<typename WindowsExecutor>
void file_out<1,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void file_out<2,-1>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdError = handle;
    e.startup_info.dwFlags  |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

template<>
template<typename WindowsExecutor>
void file_out<1,2>::on_setup(WindowsExecutor &e) const
{
    boost::winapi::SetHandleInformation(handle,
            boost::winapi::HANDLE_FLAG_INHERIT_,
            boost::winapi::HANDLE_FLAG_INHERIT_);

    e.startup_info.hStdOutput = handle;
    e.startup_info.hStdError  = handle;
    e.startup_info.dwFlags   |= ::boost::winapi::STARTF_USESTDHANDLES_;
    e.inherit_handles = true;
}

}}}}

#endif

/* file_out.hpp
W3rJ77/bhbyr4aZy47Hoh/t+q/O/l5TlCWa8meX4TVfnsbVOQ+YI6TFduVcZ3B+XXsftmoqM9d4njHq/WaZkDxru0xXSPnwSYx+vRaTfwQ5LHArjPzcOudMifnJV9daS+LyRJP3/wjyb7iHx62aXi5Z1vJltvGAOtN4dJK6JoePT+v7+WfIiSr+zDrpM8jj0Ga+YF80JW7m/VMLexprIGeZqM8N81OWSsriQNJaK3ReSxh/UmHbRDGtN+O0zA++ZZ1C+LjB5L64QZjW2Vne50vX78LjCHH8TIU+aVT73i268np/wltQTOfpe15J7UD1ml9E6Orgu8pC4yfUmGAO8eq2MyF42XazdP0vcBu/fpJho3q3896/c3GRudcdxR+43PvTkGN0iIjyyXwVpHSm6VeJt7+g6juWSx7X0XjhzJF/qu7ON5eZZrgP63e9t8eNqs8iM1ffji7nSzutxfkPyrGmgLOq8OjsizkiMCK4ZfFP8dzFe8K6ZoNMnstD7qvzFR/wNruWbQ3quEj8+jLGNIeh7vkHK+nF3TXqFndn1vr75nCuYtn3ibrNroZlF6AN1PA+Imz+7Yo1nXY7x1OEU5E4t0XuYKZ0nXCeMXGMTuxZ9hJ8dXRfos+A2iP3jMU2xZUmGMca1mLNPmhor3WlR/rSsJS0BnZelHA6V8Q6KoapvXsTeL79Fyhg7NNrKVm/17CQH9xGSNDQy9xutA+nSaVhveo35pAE9ndfJkpcz7eHr51ceX31Pv58i99CoX6Hc5cdFG6N1mUv2LOYON6XMka6Q8ZPg+uTnJdxV3g7GSVdH91nuwsjvzQJvRoV9Ks4K7vsxS94vDBe2CdzHc4hvV3qEuXyJmoNZg8lUfakS0b3YSEevpX/HRkzw+bpY7G7EpiQ41qHisZJ4LHW94no8ImR8Rae7vuRni0qle1aY9fJtqbdC18vXusx6ZyjnPlj5Xzxt6kRrDWjXaX69V+k5tzO6M+4Wa25RdRT3V+wWmR7jfeNbUp4QrI+krTP03kl7JO7XmG2M/UYf6opLeIZrqee6u9z/Ye5Y5vDcZbjI9RHmIPYuCCkvDnU269eJ918Cfscl67C7dpbQbW1SHwmjJnemiu4zTRRZqkoLcZS0rGTPo2pmJ7Prr8KX+leHfwexHSBxGE0cBgTq0fjQcataKvx7xE0592YJLuOM7dQlb2CCYd8tcfnKlW0MMh83G5jyjOmwVH2nr1Mk3Gzbs2OlXTcC+rncJW6WeJvyrhGsS1eLrJ2ZyF1zquNlPyz8Hz5FwpN0/SElsM7Vvq/KVilD15vbjaec2kTVruVToVjluljqbOf36grjuyqMyyUOTRz9t+rE5vqZe1Hu4wbG+z4NyHS+3eUdSBhWOaelL8zT4SRLHV/rN99FrTBL5AUg+H4SiNMm0nCbO2QtqTxf96HjX6fXsgcuh6vxQM/8Y3FmXJw3miHBvbJUL8JxnZ5yt3Z4cLxxgS90rPGoeWHSbAM7NUYYDxMwM9R4YQy/r+TGL8IsDhpkVwWIwV26+t4N/frLbN+7r+b3LMXa2F1E/i1PFz81FylzDeZaDOGjL+75bZlUNUZp81u4QvlzHQZ7rgNroV5LstZCpafZeWrmDbXWqRxTipmlOA/zPeZ6wtml5vXNx1yBuVK5ta/ZWhJyvTLdku9SsuPCgL8/hMQjwzafYFV6wCxLhBjSKG7Wqt+z4Nfq+i3buO3NyoRft2Ttc1ZX3qPms3Ipgvf6wTLGu9k4tfVL/nUNgbrdyJ3ALrPN1Rjwwbm/OQYsMq/DWG+cw1hvosNYb2qYsd6MMGO9NRzGen1hxnrrOoz1Nggz1ts4zFhv0zBjvS3DjPW2CTPW2x4=
*/