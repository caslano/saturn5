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
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
*/