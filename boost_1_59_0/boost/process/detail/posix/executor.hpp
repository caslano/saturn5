// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_EXECUTOR_HPP
#define BOOST_PROCESS_DETAIL_POSIX_EXECUTOR_HPP

#include <boost/process/detail/child_decl.hpp>
#include <boost/process/error.hpp>
#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/basic_pipe.hpp>
#include <boost/process/detail/posix/use_vfork.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <cstdlib>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Executor>
struct on_setup_t
{
    Executor & exec;
    on_setup_t(Executor & exec) : exec(exec) {};
    template<typename T>
    void operator()(T & t) const
    {
        if (!exec.error())
            t.on_setup(exec);
    }
};

template<typename Executor>
struct on_error_t
{
    Executor & exec;
    const std::error_code & error;
    on_error_t(Executor & exec, const std::error_code & error) : exec(exec), error(error) {};
    template<typename T>
    void operator()(T & t) const
    {
        t.on_error(exec, error);
    }
};

template<typename Executor>
struct on_success_t
{
    Executor & exec;
    on_success_t(Executor & exec) : exec(exec) {};
    template<typename T>
    void operator()(T & t) const {t.on_success(exec);}
};



template<typename Executor>
struct on_fork_error_t
{
    Executor & exec;
    const std::error_code & error;
    on_fork_error_t(Executor & exec, const std::error_code & error) : exec(exec), error(error) {};

    template<typename T>
    void operator()(T & t) const
    {
        t.on_fork_error(exec, error);
    }
};


template<typename Executor>
struct on_exec_setup_t
{
    Executor & exec;
    on_exec_setup_t(Executor & exec) : exec(exec) {};

    template<typename T>
    void operator()(T & t) const
    {
        t.on_exec_setup(exec);
    }
};


template<typename Executor>
struct on_exec_error_t
{
    Executor & exec;
    const std::error_code &ec;
    on_exec_error_t(Executor & exec, const std::error_code & error) : exec(exec), ec(error) {};

    template<typename T>
    void operator()(T & t) const
    {
        t.on_exec_error(exec, ec);
    }
};

template<typename Executor>
struct on_fork_success_t
{
    Executor & exec;
    on_fork_success_t(Executor & exec) : exec(exec) {};

    template<typename T>
    void operator()(T & t) const
    {
        t.on_fork_success(exec);
    }
};

template<typename Executor> on_setup_t  <Executor> call_on_setup  (Executor & exec) {return exec;}
template<typename Executor> on_error_t  <Executor> call_on_error  (Executor & exec, const std::error_code & ec)
{
    return on_error_t<Executor> (exec, ec);
}
template<typename Executor> on_success_t<Executor> call_on_success(Executor & exec) {return exec;}

template<typename Executor> on_fork_error_t  <Executor> call_on_fork_error  (Executor & exec, const std::error_code & ec)
{
    return on_fork_error_t<Executor> (exec, ec);
}


template<typename Executor> on_exec_setup_t  <Executor> call_on_exec_setup  (Executor & exec) {return exec;}
template<typename Executor> on_exec_error_t  <Executor> call_on_exec_error  (Executor & exec, const std::error_code & ec)
{
    return on_exec_error_t<Executor> (exec, ec);
}


template<typename Sequence>
class executor
{
    template<typename HasHandler, typename UseVFork>
    void internal_error_handle(const std::error_code&, const char*, HasHandler, boost::mpl::true_, UseVFork) {}

    int _pipe_sink = -1;

    void write_error(const std::error_code & ec, const char * msg)
    {
        //I am the child
        const auto len = std::strlen(msg);
        int data[2] = {ec.value(), len + 1};

        ::write(_pipe_sink, &data[0], sizeof(int) * 2);
        ::write(_pipe_sink, msg, len);
    }

    void internal_error_handle(const std::error_code &ec, const char* msg, boost::mpl::true_ , boost::mpl::false_, boost::mpl::false_)
    {
        if (this->pid == 0) //on the fork.
            write_error(ec, msg);
        else
        {
            this->_ec  = ec;
            this->_msg = msg;
        }
    }
    void internal_error_handle(const std::error_code &ec, const char* msg, boost::mpl::false_, boost::mpl::false_, boost::mpl::false_)
    {
        if (this->pid == 0)
            write_error(ec, msg);
        else
            throw process_error(ec, msg);
    }


    void internal_error_handle(const std::error_code &ec, const char* msg, boost::mpl::true_ , boost::mpl::false_, boost::mpl::true_)
    {
        this->_ec  = ec;
        this->_msg = msg;
    }
    void internal_error_handle(const std::error_code &ec, const char* msg, boost::mpl::false_, boost::mpl::false_, boost::mpl::true_)
    {
        if (this->pid == 0)
        {
            this->_ec  = ec;
            this->_msg = msg;
        }
        else
            throw process_error(ec, msg);
    }

    void check_error(boost::mpl::true_) {};
    void check_error(boost::mpl::false_)
    {
        if (_ec)
            throw process_error(_ec, _msg);
    }

    typedef typename ::boost::process::detail::has_error_handler<Sequence>::type has_error_handler;
    typedef typename ::boost::process::detail::has_ignore_error <Sequence>::type has_ignore_error;
    typedef typename ::boost::process::detail::posix::shall_use_vfork<Sequence>::type shall_use_vfork;

    inline child invoke(boost::mpl::true_ , boost::mpl::true_ );
    inline child invoke(boost::mpl::false_, boost::mpl::true_ );
    inline child invoke(boost::mpl::true_ , boost::mpl::false_ );
    inline child invoke(boost::mpl::false_, boost::mpl::false_ );
    void _write_error(int sink)
    {
        int data[2] = {_ec.value(),static_cast<int>(_msg.size())};
        while (::write(sink, &data[0], sizeof(int) *2) == -1)
        {
            auto err = errno;

            if (err == EBADF)
                return;
            else if ((err != EINTR) && (err != EAGAIN))
                break;
        }
        while (::write(sink, &_msg.front(), _msg.size()) == -1)
        {
            auto err = errno;

            if (err == EBADF)
                return;
            else if ((err != EINTR) && (err != EAGAIN))
                break;
        }
    }

    void _read_error(int source)
    {
        int data[2];

        _ec.clear();
        int count = 0;
        while ((count = ::read(source, &data[0], sizeof(int) *2 ) ) == -1)
        {
            //actually, this should block until it's read.
            auto err = errno;
            if ((err != EAGAIN ) && (err != EINTR))
                set_error(std::error_code(err, std::system_category()), "Error read pipe");
        }
        if (count == 0)
            return  ;

        std::error_code ec(data[0], std::system_category());
        std::string msg(data[1], ' ');

        while (::read(source, &msg.front(), msg.size() ) == -1)
        {
            //actually, this should block until it's read.
            auto err = errno;
            if ((err == EBADF) || (err == EPERM))//that should occur on success, therefore return.
                return;
                //EAGAIN not yet forked, EINTR interrupted, i.e. try again
            else if ((err != EAGAIN ) && (err != EINTR))
                set_error(std::error_code(err, std::system_category()), "Error read pipe");
        }
        set_error(ec, std::move(msg));
    }

    std::string prepare_cmd_style_fn; //buffer

    inline void prepare_cmd_style() //this does what execvpe does - but we execute it in the father process, to avoid allocations.
    {
        //use my own implementation
        prepare_cmd_style_fn = exe;
        if ((prepare_cmd_style_fn.find('/') == std::string::npos) && ::access(prepare_cmd_style_fn.c_str(), X_OK))
        {
            const auto * e = ::environ;
            while ((e != nullptr) && (*e != nullptr) && !boost::starts_with(*e, "PATH="))
                e++;

            if ((e != nullptr) && (*e != nullptr))
            {
                std::vector<std::string> path;
                //the beginning of the string contains "PATH="
                boost::split(path, (*e) + 5, boost::is_any_of(":"));

                for (const std::string & pp : path)
                {
                    auto p = pp + "/" + exe;
                    if (!::access(p.c_str(), X_OK))
                    {
                        prepare_cmd_style_fn = p;
                        break;
                    }
                }
            }
        }
        exe = prepare_cmd_style_fn.c_str();
    }

    std::error_code _ec;
    std::string _msg;
public:
    executor(Sequence & seq) : seq(seq)
    {
    }

    child operator()()
    {
        return invoke(has_ignore_error(), shall_use_vfork());
    }


    Sequence & seq;
    const char * exe      = nullptr;
    char *const* cmd_line = nullptr;
    bool cmd_style = false;
    char **env      = ::environ;
    pid_t pid = -1;
    std::shared_ptr<std::atomic<int>> exit_status = std::make_shared<std::atomic<int>>(still_active);

    const std::error_code & error() const {return _ec;}

    void set_error(const std::error_code &ec, const char* msg)
    {
        internal_error_handle(ec, msg, has_error_handler(), has_ignore_error(), shall_use_vfork());
    }
    void set_error(const std::error_code &ec, const std::string &msg) {set_error(ec, msg.c_str());};

};

template<typename Sequence>
child executor<Sequence>::invoke(boost::mpl::true_, boost::mpl::false_) //ignore errors
{
    boost::fusion::for_each(seq, call_on_setup(*this));
    if (_ec)
        return child();
    if (cmd_style)
        prepare_cmd_style();

    this->pid = ::fork();
    if (pid == -1)
    {
        auto ec = boost::process::detail::get_last_error();
        boost::fusion::for_each(seq, call_on_fork_error(*this, ec));
        return child();
    }
    else if (pid == 0)
    {
        boost::fusion::for_each(seq, call_on_exec_setup(*this));
        ::execve(exe, cmd_line, env);
        auto ec = boost::process::detail::get_last_error();
        boost::fusion::for_each(seq, call_on_exec_error(*this, ec));
        _exit(EXIT_FAILURE);
    }

    child c(child_handle(pid), exit_status);

    boost::fusion::for_each(seq, call_on_success(*this));

    return c;
}

template<typename Sequence>
child executor<Sequence>::invoke(boost::mpl::false_, boost::mpl::false_)
{
    {
        struct pipe_guard
        {
            int p[2];
            pipe_guard() : p{-1,-1} {}

            ~pipe_guard()
            {
                if (p[0] != -1)
                    ::close(p[0]);
                if (p[1] != -1)
                    ::close(p[1]);
            }
        } p{};

        if (::pipe(p.p) == -1)
        {
            set_error(::boost::process::detail::get_last_error(), "pipe(2) failed");
            return child();
        }
        if (::fcntl(p.p[1], F_SETFD, FD_CLOEXEC) == -1)
        {
            auto err = ::boost::process::detail::get_last_error();
            set_error(err, "fcntl(2) failed");//this might throw, so we need to be sure our pipe is safe.
            return child();
        }
        _ec.clear();
        boost::fusion::for_each(seq, call_on_setup(*this));

        if (_ec)
        {
            boost::fusion::for_each(seq, call_on_error(*this, _ec));
            return child();
        }

        if (cmd_style)
            prepare_cmd_style();

        this->pid = ::fork();
        if (pid == -1)
        {
            _ec = boost::process::detail::get_last_error();
            _msg = "fork() failed";
            boost::fusion::for_each(seq, call_on_fork_error(*this, _ec));
            boost::fusion::for_each(seq, call_on_error(*this, _ec));
            return child();
        }
        else if (pid == 0)
        {
            _pipe_sink = p.p[1];
            ::close(p.p[0]);

            boost::fusion::for_each(seq, call_on_exec_setup(*this));
            ::execve(exe, cmd_line, env);
            _ec = boost::process::detail::get_last_error();
            _msg = "execve failed";
            boost::fusion::for_each(seq, call_on_exec_error(*this, _ec));

            _write_error(_pipe_sink);
            ::close(p.p[1]);

            _exit(EXIT_FAILURE);
            return child();
        }

        ::close(p.p[1]);
        p.p[1] = -1;
        _read_error(p.p[0]);

    }
    if (_ec)
    {
        boost::fusion::for_each(seq, call_on_error(*this, _ec));
        return child();
    }

    child c(child_handle(pid), exit_status);

    boost::fusion::for_each(seq, call_on_success(*this));

    if (_ec)
    {
        boost::fusion::for_each(seq, call_on_error(*this, _ec));
        return child();
    }

    return c;
}

#if BOOST_POSIX_HAS_VFORK


template<typename Sequence>
child executor<Sequence>::invoke(boost::mpl::true_, boost::mpl::true_) //ignore errors
{
    boost::fusion::for_each(seq, call_on_setup(*this));
    if (_ec)
        return child();
    this->pid = ::vfork();
    if (pid == -1)
    {
        auto ec = boost::process::detail::get_last_error();
        boost::fusion::for_each(seq, call_on_fork_error(*this, ec));
        return child();
    }
    else if (pid == 0)
    {
        boost::fusion::for_each(seq, call_on_exec_setup(*this));
        ::execve(exe, cmd_line, env);
        auto ec = boost::process::detail::get_last_error();
        boost::fusion::for_each(seq, call_on_exec_error(*this, ec));
        _exit(EXIT_FAILURE);
    }
    child c(child_handle(pid), exit_status);

    boost::fusion::for_each(seq, call_on_success(*this));

    return c;
}

template<typename Sequence>
child executor<Sequence>::invoke(boost::mpl::false_, boost::mpl::true_)
{
    boost::fusion::for_each(seq, call_on_setup(*this));

    if (_ec)
    {
        boost::fusion::for_each(seq, call_on_error(*this, _ec));
        return child();
    }
    _ec.clear();
    if (cmd_style)
        this->prepare_cmd_style();

    this->pid = ::vfork();
    if (pid == -1)
    {
        _ec = boost::process::detail::get_last_error();
        _msg = "fork() failed";
        boost::fusion::for_each(seq, call_on_fork_error(*this, _ec));
        boost::fusion::for_each(seq, call_on_error(*this, _ec));

        return child();
    }
    else if (pid == 0)
    {
        boost::fusion::for_each(seq, call_on_exec_setup(*this));

        ::execve(exe, cmd_line, env);

        _ec = boost::process::detail::get_last_error();
        _msg = "execve failed";
        boost::fusion::for_each(seq, call_on_exec_error(*this, _ec));

        _exit(EXIT_FAILURE);
        return child();
    }
    child c(child_handle(pid), exit_status);

    check_error(has_error_handler());



    if (_ec)
    {
        boost::fusion::for_each(seq, call_on_error(*this, _ec));
        return child();
    }
    else
        boost::fusion::for_each(seq, call_on_success(*this));

    if (_ec)
    {
        boost::fusion::for_each(seq, call_on_error(*this, _ec));
        return child();
    }

    return c;
}

#endif

template<typename Char, typename Tup>
inline executor<Tup> make_executor(Tup & tup)
{
    return executor<Tup>(tup);
}

}}}}

#endif

/* executor.hpp
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
*/