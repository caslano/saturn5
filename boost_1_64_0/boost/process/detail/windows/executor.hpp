// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_EXECUTOR_HPP
#define BOOST_PROCESS_WINDOWS_EXECUTOR_HPP

#include <boost/process/detail/child_decl.hpp>
#include <boost/process/detail/windows/is_running.hpp>
#include <boost/process/detail/traits.hpp>
#include <boost/process/error.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/process.hpp>
#include <boost/none.hpp>
#include <system_error>
#include <memory>
#include <atomic>
#include <cstring>

namespace boost { namespace process {

namespace detail { namespace windows {

template<typename CharType> struct startup_info;
#if !defined( BOOST_NO_ANSI_APIS )

template<> struct startup_info<char>
{
    typedef ::boost::winapi::STARTUPINFOA_ type;
};
#endif

template<> struct startup_info<wchar_t>
{
    typedef ::boost::winapi::STARTUPINFOW_ type;
};

#if BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6

template<typename CharType> struct startup_info_ex;

#if !defined( BOOST_NO_ANSI_APIS )
template<> struct startup_info_ex<char>
{
    typedef ::boost::winapi::STARTUPINFOEXA_ type;
};
#endif

template<> struct startup_info_ex<wchar_t>
{
    typedef ::boost::winapi::STARTUPINFOEXW_ type;
};


#endif

#if ( BOOST_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6 )

template<typename CharT>
struct startup_info_impl
{
    ::boost::winapi::DWORD_ creation_flags = 0;

    typedef typename startup_info_ex<CharT>::type startup_info_ex_t;
    typedef typename startup_info<CharT>::type    startup_info_t;

    startup_info_ex_t  startup_info_ex
            {startup_info_t {sizeof(startup_info_t), nullptr, nullptr, nullptr,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr,
                               ::boost::winapi::invalid_handle_value,
                               ::boost::winapi::invalid_handle_value,
                               ::boost::winapi::invalid_handle_value},
                nullptr
    };
    startup_info_t & startup_info = startup_info_ex.StartupInfo;

    void set_startup_info_ex()
    {
       startup_info.cb = sizeof(startup_info_ex_t);
       creation_flags |= ::boost::winapi::EXTENDED_STARTUPINFO_PRESENT_;
    }
};


#else

template<typename CharT>
struct startup_info_impl
{
    typedef typename startup_info<CharT>::type    startup_info_t;

    ::boost::winapi::DWORD_ creation_flags = 0;
    startup_info_t          startup_info
            {sizeof(startup_info_t), nullptr, nullptr, nullptr,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr,
             ::boost::winapi::invalid_handle_value,
             ::boost::winapi::invalid_handle_value,
             ::boost::winapi::invalid_handle_value};
};
#endif



template<typename Char, typename Sequence>
class executor : public startup_info_impl<Char>
{

    void internal_error_handle(const std::error_code &, const char*, boost::mpl::false_, boost::mpl::true_) {}
    void internal_error_handle(const std::error_code &, const char*, boost::mpl::true_,  boost::mpl::true_) {}

    void internal_error_handle(const std::error_code &ec, const char*, boost::mpl::true_,  boost::mpl::false_ )
    {
        this->_ec = ec;
    }
    void internal_error_handle(const std::error_code &ec, const char* msg, boost::mpl::false_, boost::mpl::false_ )
    {
        throw process_error(ec, msg);
    }

    struct on_setup_t
    {
        executor & exec;
        on_setup_t(executor & exec) : exec(exec) {};
        template<typename T>
        void operator()(T & t) const
        {
            if (!exec.error())
                t.on_setup(exec);
        }
    };

    struct on_error_t
    {
        executor & exec;
        const std::error_code & error;
        on_error_t(executor & exec, const std::error_code & error) : exec(exec), error(error) {};
        template<typename T>
        void operator()(T & t) const
        {
            t.on_error(exec, error);
        }
    };

    struct on_success_t
    {
        executor & exec;
        on_success_t(executor & exec) : exec(exec) {};
        template<typename T>
        void operator()(T & t) const
        {
            if (!exec.error())
                t.on_success(exec);
        }
    };

    typedef typename ::boost::process::detail::has_error_handler<Sequence>::type has_error_handler;
    typedef typename ::boost::process::detail::has_ignore_error <Sequence>::type has_ignore_error;

    std::error_code _ec{0, std::system_category()};

public:

    std::shared_ptr<std::atomic<int>> exit_status = std::make_shared<std::atomic<int>>(still_active);

    executor(Sequence & seq) : seq(seq)
    {
    }

    child operator()()
    {
        on_setup_t on_setup_fn(*this);
        boost::fusion::for_each(seq, on_setup_fn);

        if (_ec)
        {
            on_error_t on_error_fn(*this, _ec);
            boost::fusion::for_each(seq, on_error_fn);
            return child();
        }

        //NOTE: The non-cast cmd-line string can only be modified by the wchar_t variant which is currently disabled.
        int err_code = ::boost::winapi::create_process(
            exe,                                        //       LPCSTR_ lpApplicationName,
            const_cast<Char*>(cmd_line),                //       LPSTR_ lpCommandLine,
            proc_attrs,                                 //       LPSECURITY_ATTRIBUTES_ lpProcessAttributes,
            thread_attrs,                               //       LPSECURITY_ATTRIBUTES_ lpThreadAttributes,
            inherit_handles,                            //       INT_ bInheritHandles,
            this->creation_flags,                       //       DWORD_ dwCreationFlags,
            reinterpret_cast<void*>(const_cast<Char*>(env)),  //     LPVOID_ lpEnvironment,
            work_dir,                                   //       LPCSTR_ lpCurrentDirectory,
            &this->startup_info,                        //       LPSTARTUPINFOA_ lpStartupInfo,
            &proc_info);                                //       LPPROCESS_INFORMATION_ lpProcessInformation)

        child c{child_handle(proc_info), exit_status};

        if (err_code != 0)
        {
            _ec.clear();
            on_success_t on_success_fn(*this);
            boost::fusion::for_each(seq, on_success_fn);
        }
        else
            set_error(::boost::process::detail::get_last_error(),
                    " CreateProcess failed");

        if ( _ec)
        {
            on_error_t on_err(*this, _ec);
            boost::fusion::for_each(seq, on_err);
            return child();
        }
        else
            return c;

    }

    void set_error(const std::error_code & ec, const char* msg = "Unknown Error.")
    {
        internal_error_handle(ec, msg, has_error_handler(),         has_ignore_error());
    }
    void set_error(const std::error_code & ec, const std::string msg = "Unknown Error.")
    {
        internal_error_handle(ec, msg.c_str(), has_error_handler(), has_ignore_error());
    }

    const std::error_code& error() const {return _ec;}

    ::boost::winapi::LPSECURITY_ATTRIBUTES_ proc_attrs   = nullptr;
    ::boost::winapi::LPSECURITY_ATTRIBUTES_ thread_attrs = nullptr;
    ::boost::winapi::BOOL_ inherit_handles = false;
    const Char * work_dir = nullptr;
    const Char * cmd_line = nullptr;
    const Char * exe      = nullptr;
    const Char * env      = nullptr;


    Sequence & seq;
    ::boost::winapi::PROCESS_INFORMATION_ proc_info{nullptr, nullptr, 0,0};
};



template<typename Char, typename Tup>
executor<Char, Tup> make_executor(Tup & tup)
{
    return executor<Char, Tup>(tup);
}


}}}}

#endif

/* executor.hpp
8OqyESV1yG5XLZU3O8R+vSsVnTPJg08Mf9lsYjiNL9UPrd/Y+fKIa4v5sOcBb2g9l+p/55Q4drT6YbS1oXVcqbTv1YxaKn7HpS6qkdbXeIr9YfPMhW4j6aXUPo7tGLKQ/s6oyHR5N7G3+Rs9tPe2d4iSopLcgpxxRYU6HikwScphkm577pN8asrIi8u5j084IwjnkKTxiK1/lscAH/7b+mf7pZ65QvKlKW7OkzrzNnEzVwq0vwOWP8Z+psjzo/w6IyMyK7xLZCWnG6NjL49da14Tv9ljhTl+Sl5ejmrrWCtFGB9KvE6qOl+nW+zrYv+J2B8nDtbYyNgSSo+tfvxc+lEJ5s3GGN2GlktadhrNVT7VFX8+qr3MfMX9fUQNc0ZUllGHDcbGelOZR7o0cUVmP2N99UTjm+qH3cH7dVDuzb6INOPZCHnf0OX8sIuZW65gP6it6J2VXtOIYHXYVzHNYr+V8n+Euj03MC7qq/C+OS5/in0sbpGUpTH6nvaTvsojrtnszCw6OlxXaL9E8mkZ+fSAhHO2LRzGj6aUyNtEsB/wpYwDvGI0Iazbjarar2vkHSPQHmXg14viV6qvQj1Gtgfb6vvQKZCyUWzdF3lH4K1b6ZSg85T4U1vatZOBvlqxYVuzNmhoIJ1Zhte8gPfXfNf5ulzdP952DqEuV8lh6z6r/IzJLRk7Uffnv5bn42a+JUTiFpluGxJcNxtD2DN9pMTXR3yPSHwP6WdEzqkj6cF0X4tOlqR7JTrB8Y6i/HE5Y/KLbPV4TSkPNYmDvXy0RBKBzDZGkFMoC4zSpd22j6O9L2NoVntNW5Fjf17VuWVSxuuq93FqI7m/Vxku/otEqy45PZSUX2oE1pHtS7TWIdYnzPJfjd21NYvYCLQo4VxWBmw0/HGw3p8Kdfl8UcpnnGsZO+tb4z5dKdiG1skeK/1Ss5/Rwgwts7b3IVo0a81hQ/H3z657mWW5lvEBqVO0u7bJXuqUS6hT5lGnZEq7HjpWcUfIWMUkXZ72iN+dJE9vtY2F9pdukHXv2ohemnWfpC2d3tywjRs0GyfvxxEr8G8NfaR2rgj2Kj2X/SsLzIr1xJMedijyhMv7gM6IlEPE/UnPl96ohMHG94kbjYb0nbqRjmTtjjjgVOIgbu39rccSHqiSZdLfol/pCfa5yF/1TPr7SrbzJdtIH6KcXlcXneYWIqNs/mqc+8Jk/zqyiW7moNVkzpec47pguu38Qr1+lLqgwvmM4/vJO4CsMwv68SN+bPT7EbFgdOgZjelKp0Et5rwloRO7tC3nLu5wWEundQei+5RfN3rpsDh3bOg5UzrcEvTGpvvjvnRFUGdcekWdtcFwvcsaOqy3Qwf7WnLODfG/7jMd/xCdcnRG+nUSr39P51OIjqd2UGflvnA6DbTOqlfC6fTVOqv3htGhhlZnbMWv/i5culYGdSLX3BqqU0fpvBrUMdcmx3m9cZ5518v5rt6w57CKO3ocwXPA1jYNc39oaZTf0Te85XBGsOh0QyePe+a+oSi2UaQrLirGCndmMr+TKpaNYl+wHK1bQzl64bfK0VpfsBytezh8OcI/9DiHCL2rR+q1lKH3H53mfr+Sln0Vet7jUfeFSScNa63lI5U0WzEzTkHv7zFPqjjtUGs/n1Zh7cTckwQxL/L7JcykpACXwlfgMrgEBu2f1b8t1k3FP3U9Pl1kAT8xrdJoadOxV7LnVNi/YJ5RYe/m9/Wh/io+Yfv9uO33xHT9W/wblAJt4eZjf7EKF0M8ApxkkyUlaSNprAJvhrco8wLXbkyqXwf/E6HfpGNwr83L/rzCqDzVefGMik+BWhP7M2a7svsJUytZx1kzNA+uxCzCLFY=
*/