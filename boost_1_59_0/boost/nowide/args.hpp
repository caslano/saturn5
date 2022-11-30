//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
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
    };

#else

    ///
    /// \brief \c args is a class that temporarily replaces standard main() function arguments with their
    /// equal, but UTF-8 encoded values under Microsoft Windows for the lifetime of the instance.
    ///
    /// The class uses \c GetCommandLineW(), \c CommandLineToArgvW() and \c GetEnvironmentStringsW()
    /// in order to obtain Unicode-encoded values.
    /// It does not relate to actual values of argc, argv and env under Windows.
    ///
    /// It restores the original values in its destructor (usually at the end of the \c main function).
    ///
    /// If any of the system calls fails, an exception of type std::runtime_error will be thrown
    /// and argc, argv, env remain unchanged.
    ///
    /// \note The class owns the memory of the newly allocated strings.
    /// So you need to keep it alive as long as you use the values.
    ///
    /// Usage:
    /// \code
    /// int main(int argc, char** argv, char** env) {
    ///   boost::nowide::args _(argc, argv, env); // Note the _ as a "don't care" name for the instance
    ///   // Use argv and env as usual, they are now UTF-8 encoded on Windows
    ///   return 0; // Memory held by args is released
    /// }
    /// \endcode
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
        /// Restore original argc, argv, env values, if changed
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
            wargv_ptr(const wargv_ptr&) = delete;
            wargv_ptr& operator=(const wargv_ptr&) = delete;

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

        public:
            wenv_ptr() : p(GetEnvironmentStringsW())
            {}
            ~wenv_ptr()
            {
                if(p)
                    FreeEnvironmentStringsW(p);
            }
            wenv_ptr(const wenv_ptr&) = delete;
            wenv_ptr& operator=(const wenv_ptr&) = delete;

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