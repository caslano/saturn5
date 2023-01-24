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
66AE5UkXYeUjiiA5tJSdxppt3fJ+yf8qP8HvuH0/HxgS6J+SE3goERUKyTn+mfHwl+Cyx5tc9vZR8CvFuzD+Qo6/ON5dlclimWx/uoeE80CTUHBEu8e5sagr8jI9rUKDmCOvI78f7IFis5LU76aiXlxmV24kNhcFM11YgGdX7L+h1KOXu+InqyfiR4//Xth2sT0l/9B4Nwof1qYaXdqUF+88q25WDv11mu3qRujWRwieKzVIy8EFJIdq5w777Eo6S+5LAEYaIEDybYiWnJumApvwHcLOtsO0YMqUNpq64zJYq0sR1p3Vkv3mWoOyIzAY4LV66sNhyo49f5w2KjvGHTKTsuNPyT8WsO6uwYHu13j8U+NpxrYoVx0jri8pDXcK7kM77MOJLP/5FWfiWmF0qJk3jIZRnwQKZ7OS8yPqGGDK8xoJqU6jLuFE02Klj4MkVjKI14REdb93S8NI5E3IKAhPTYoPTS5MWo5c505ZD9gJdq/9yY5mnt8hgeuvggFjVCzfRpjjHTjH39Ac1xFeNcwxoLTIvhjWxVnT5BzbZy9tqFR6BE9fuV6b5zM/8zzXa7auQwOR13gijnoAmCX/mIScAKLBrZ7A9YSUHrlKkntiRJhPj5gx0pcbc8JvVt46gmhcWwJA5BNuBpSuPHoYMFAPjOv7ZFj1IqpOdejsW6/pnxPDdEKD/sD1eu0grhfuihHGWAdrXE/vhulw
*/