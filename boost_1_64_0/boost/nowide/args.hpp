//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_ARGS_HPP_INCLUDED
#define BOOST_NOWIDE_ARGS_HPP_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_WINDOWS
#include <boost/nowide/stackstring.hpp>
#include <boost/nowide/windows.hpp>
#include <stdexcept>
#include <vector>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    class args
    {
    public:
        args(int&, char**&)
        {}
        args(int&, char**&, char**&)
        {}
        ~args()
        {}
    };

#else

    ///
    /// \brief args is a class that fixes standard main() function arguments and changes them to UTF-8 under
    /// Microsoft Windows.
    ///
    /// The class uses \c GetCommandLineW(), \c CommandLineToArgvW() and \c GetEnvironmentStringsW()
    /// in order to obtain the information. It does not relate to actual values of argc,argv and env
    /// under Windows.
    ///
    /// It restores the original values in its destructor
    ///
    /// If any of the system calls fails, an exception of type std::runtime_error will be thrown
    /// and argc, argv, env remain unchanged.
    ///
    /// \note the class owns the memory of the newly allocated strings
    ///
    class args
    {
    public:
        ///
        /// Fix command line arguments
        ///
        args(int& argc, char**& argv) :
            old_argc_(argc), old_argv_(argv), old_env_(0), old_argc_ptr_(&argc), old_argv_ptr_(&argv), old_env_ptr_(0)
        {
            fix_args(argc, argv);
        }
        ///
        /// Fix command line arguments and environment
        ///
        args(int& argc, char**& argv, char**& env) :
            old_argc_(argc), old_argv_(argv), old_env_(env), old_argc_ptr_(&argc), old_argv_ptr_(&argv),
            old_env_ptr_(&env)
        {
            fix_args(argc, argv);
            fix_env(env);
        }
        ///
        /// Restore original argc,argv,env values, if changed
        ///
        ~args()
        {
            if(old_argc_ptr_)
                *old_argc_ptr_ = old_argc_;
            if(old_argv_ptr_)
                *old_argv_ptr_ = old_argv_;
            if(old_env_ptr_)
                *old_env_ptr_ = old_env_;
        }

    private:
        class wargv_ptr
        {
            wchar_t** p;
            int argc;
            // Non-copyable
            wargv_ptr(const wargv_ptr&);
            wargv_ptr& operator=(const wargv_ptr&);

        public:
            wargv_ptr()
            {
                p = CommandLineToArgvW(GetCommandLineW(), &argc);
            }
            ~wargv_ptr()
            {
                if(p)
                    LocalFree(p);
            }
            int size() const
            {
                return argc;
            }
            operator bool() const
            {
                return p != NULL;
            }
            const wchar_t* operator[](size_t i) const
            {
                return p[i];
            }
        };
        class wenv_ptr
        {
            wchar_t* p;
            // Non-copyable
            wenv_ptr(const wenv_ptr&);
            wenv_ptr& operator=(const wenv_ptr&);

        public:
            wenv_ptr() : p(GetEnvironmentStringsW())
            {}
            ~wenv_ptr()
            {
                if(p)
                    FreeEnvironmentStringsW(p);
            }
            operator const wchar_t*() const
            {
                return p;
            }
        };

        void fix_args(int& argc, char**& argv)
        {
            const wargv_ptr wargv;
            if(!wargv)
                throw std::runtime_error("Could not get command line!");
            args_.resize(wargv.size() + 1, 0);
            arg_values_.resize(wargv.size());
            for(int i = 0; i < wargv.size(); i++)
                args_[i] = arg_values_[i].convert(wargv[i]);
            argc = wargv.size();
            argv = &args_[0];
        }
        void fix_env(char**& env)
        {
            const wenv_ptr wstrings;
            if(!wstrings)
                throw std::runtime_error("Could not get environment strings!");
            const wchar_t* wstrings_end = 0;
            int count = 0;
            for(wstrings_end = wstrings; *wstrings_end; wstrings_end += wcslen(wstrings_end) + 1)
                count++;
            env_.convert(wstrings, wstrings_end);
            envp_.resize(count + 1, 0);
            char* p = env_.get();
            int pos = 0;
            for(int i = 0; i < count; i++)
            {
                if(*p != '=')
                    envp_[pos++] = p;
                p += strlen(p) + 1;
            }
            env = &envp_[0];
        }

        std::vector<char*> args_;
        std::vector<short_stackstring> arg_values_;
        stackstring env_;
        std::vector<char*> envp_;

        int old_argc_;
        char** old_argv_;
        char** old_env_;

        int* old_argc_ptr_;
        char*** old_argv_ptr_;
        char*** old_env_ptr_;
    };

#endif

} // namespace nowide
} // namespace boost
#endif

/* args.hpp
DQXLXpmF2M9ZhbdJWp8Dg6PQZuet4hhLlyl+UVnYBX2egy1j/dAuF62iBLPZ0xrNwJxM1o2V9+jjT2FId1kbS5r99sI1CenIOjFb8mrkcsyDV+h3BJbnjpXRsl2uWQX9j7CBwfI7k4lkTpj+2J9MVp7leWLCPn/EfoNiYOkWneks982bVnGGWUzBWwGwW3QvnVnPP+fIdzTJ/GDKs9JkFpj+2YNkshpaPXumpSvgMwVt9o9V3BHSarUcKtdLSLKKDCzdwo4mN+p5h9qFWcvbmbtjLN21ioNmaY0r3UHfJj6wiq8sXb/jreRv848RA5ny7hVZIDPPtl6rEQNZW2Yl6zrfoZ5PqM1gyrNpBhZClhWmPCduYNFklZhlLFAY8SWSbfeSlufYUPk9/Rd0D5dZpsN738jnX6xYe787bbBF5tiAGF5r/aDZ5Hpr1qIub6wijKV7PL7ZE4wJsrrM5hfZgfYMe0vxMfuUunQ36klWmNn3G27J987IeJ7htcNHyOdt6B4gs681zy1G/5H5M1sU5h6J2MnGMDuV+YJ81u89/X7kI228u8pZ7A9frGKIl7SU/3g3wnzmZRNhOaVtDc7XRK5hYxPvWZ6hK5pmRHzFbaK6kOYMfN8M7Ul2zcXKc9qCEXsNmxjvJ21c9Q55ka61TYQKaXlejCmE+NrYRElWl421HzXGWOpoEyVM0mKdf3qQLtwmWgtpwzOufoU5hCyCWbMGvzVFOo9NvGXWe8WbmfL+p01UY1Ywgj3jQlaH2a5M6+rL74fbRA1mq0IHyu/wk5Vm9qrToQXIk+yGWdq+zkPl3NrDJgazdIGWiIWY53vaxEJmCXVTh6HNyAowiyyW5TX6qJdNtGLlRfT/aR/6qI9N5EA65X3mvjax3kvayN/mn8TYHWjD/NJNXc+KLKO3tOlR168h9qE22v9g+vdehtnEALO0vHsDnqMuI2xiiknavqDPxZBulE30YJazxmr5W2uUTZz1krZ33Ex5HyzaJnpq1jXtd5l3s/9COnpE4Rkzv3/jbIh9mk38bZb2W+Zx8vxslg3nPV1ow+rkZxvQ1mRlmI25WkueC8+2idXM+sSc24z45tjEWhPLc1SoXMtyrk00YXbedisLYphH+6aQduh17xaY6+bbRHZmDXLNnID9gewCs8EXt27BuF6gjy9H1floz5CF+vjcv3VuhrYmq8Js2eWUPhgvZBHMgnPUPijfebWJgsxODup4FPUku84s2+isqajnYpt4wuzx6QLyd8olNpHoLe1w/O/yN40VNpGX98O1G3nQ1j/bRD9mz6MGTUR5ZFmY/bjFHox+ILtgkhZ/vuZ95LnKJl4x+yvqbl202RqbKMfs5NSTPyDdLzbRTkh75LtpO9KRFWBWbtyCFRi7ZEHMUsvWOYTYlXStGwXfQ3nrbMICU9aKJ+uuWee0eXdWYlG0C5k/TH9vO4EsAKa/X57MTbnPHrSemXJ/PoysF7P6YYPkcZMsvbqIDTZR2ywt+sz2o0i3icaESZp/kcqn5b08m3gtpN3xdNoi3xuk+ZpZyJJuGZFum028ZOb6/P1UeW/NJpax8u6GLy6FPLdjnJEpv72Q5WF2r8TjxYiBbASzbUf2f0Z5O2yiGLMe3fub0UdkE5k1HVIZfRux0yZ6M+s/L3d1tOeu9OsZRJaD2cTW+3/DHELGx1KbX45fQ13IOpil7Thw5Sjsd5t4yNJlnfHTCsS+xyZmekub3mKSN9rzoE18Z5K22zEjFukSbGI4sxav3nRDeX/YRBFWl3nt/pkr3/WyCS+WztN1K+JLPEb7NLOi43NaMdedkPuYR31P0cCiDSzGwOIMLN7AEgws0cCSyEKY5R4wH9e37pM=
*/