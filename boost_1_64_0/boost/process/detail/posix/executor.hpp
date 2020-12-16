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
tRvzGuZzjP8QuwVj+mHGYmZhFmNWY7ZgdmNewxzExDEoTMf0w2RjCjCLDtedM/Wf2nuPc6b+I/vv/befMbX2sPe/ch++LYe9dXvx/Yv24tt12Psv249vL2EfxKTwYNEPMxFTjrkcs+mzur366n51v7pf3a/uV/er+9X96n51v7rff2L/P6byzSv4h/f/S2WecCUfCQ/eFniNOb1sbl4PJvQF9wWsRh65LyCyyH0BkTn3BbRlXsf+eakq8+medRMyx2WNmGTrRon8J+OzMnPRjUPmvl/dHx371e3U/epivbx7hTFwHv7K82RuU0FZXrCQJP6wfWgKC/Iq84vd9/RS//xLNmvCUWaelOVYFzVXdI561uPjHY/XZb6THU5qeDgl+cXFZdMJLrSeZbno9fBcaUW7zQfUcJx72ph8mTC2Tw1oPMyZHT7X/XU0jMh5kO576Ni6WmYXVBcVVrnsn+OmW5U/rbjQff8cOx+qW1HIEubK0NrTdId+eoR+dbDu5lF6NcwGNfMD90i+24n/drZ/JG7xVVcWTq+YX677a3Ry6HdyzQv63e01vbH5HmRtxW9Xh9+ux4orv7yiu+Ytw6Gf4dC350vOyq+cZe+RUSPu33tu5v/9HnZjYM5cPPLV1N05STbnwWfx8JzMpTu+vRoaBOaUT7XnNKc55y9HXB+pznnM9nUgfvy23NmuzR4rOufYbqvIU1z2iGhq4pZ2JrIWRibtScJMNzLTbkTeDlaL3LQPkXcy+qbeJeyuTnn3YBgZRmbXm3Me5TV8pxGSpy7wIljTMngAkIfPFgW9JQJdB++8RnVtOnNk7xTd2VENQudTir2lWx9EuJFzLUvyZxZNN+ca3iPuhVE13t/JnkCN8LNOZONc+iK38KSCzXV0i7g/5Nr/qF/HPONSM894+/SAywi1s8qyMGBvZq5ZK9g2qBL7OuoxTeYKmzBeF/saM1f4ZAkjqlaYlKOcFTda9J/y1TNxFJk15fMlPXs8gzVNTZFliv8La4eH/ylkPnDiWg9HX3qv5Hd81DW+u7TPNfmg0drr6DIkHckmX2+LPS64Lpl09hH76z5nPJZj/8bzxH2Db4kvUeuBO4qkLbgX1E2BQHXflNB5m6mhPGv7kpJ1rPu9TdKe5Ch/aTeo2XX2iOikOuZ4B4clobQ1gvGSjpHcD3z4Q4ZtrMjqh+/fUE6JOOI/RXR+jY4j/XnlhRUlkgfOzXTu7VFQyCRmLT8ofoeqPRRftBU68/GGRNuMpQL+jHmeDOXACHNM9z+52F30jNt46DDSt/ayjncNVnSStDXdpzBV+9lhibX7xTgjl/qKmNct16qM1Ra25PvANotaoezzzJ460jYob3RFJnEdMDK7Dpx77exsxH+6P09X5VdJcIb0adrA3PbasetslOhOJb6h5E39EtIsX5z1sc9j+hHbzX2vnUCCBol7kYQV9wNh2W4uZyJrGx8v7km+27znmz0P/jorIMv0jGXtwhWEksh9NWzPALKrdzGzV8FMCSfb+wwrRPZjPvGcZfZnKZfw1ngyGG//mU37mnrizDrw+8TtCk+UrO3fZcfjvFfqdf3Bd0ePRpzbLGXwOfJ7JP6rfK8wMWMKZSB9Xsvw/Wa2is59XJnXu+15J+mJLgroDJNwDxDuz8XP/b7vCHexz7mHkX2vTNM6XjQTXWZLdaXlLKbc1lhJpm99UPI53OxbtEl0n/SkMBvte1LU0LNBdUPlX0/SsIs0/ELScK/va9KwiDSkOs6Bzist4xZfNGO+7iNzBP1K0X/a15j2sBr9NKPPfT/YheUVFM4oKi0ssNLwswM/ZeLnOV9HVpo0w99anxnXmzqvdKyNLpb0sweP9mf54v8=
*/