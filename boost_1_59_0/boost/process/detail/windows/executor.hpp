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
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
*/