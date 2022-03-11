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
        int len = ec.value();
        ::write(_pipe_sink, &len, sizeof(int));

        len = std::strlen(msg) + 1;
        ::write(_pipe_sink, &len, sizeof(int));
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
            auto e = ::environ;
            while ((*e != nullptr) && !boost::starts_with(*e, "PATH="))
                e++;

            if (e != nullptr)
            {
                std::vector<std::string> path;
                boost::split(path, *e, boost::is_any_of(":"));

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