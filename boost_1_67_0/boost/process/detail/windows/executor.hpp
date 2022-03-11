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