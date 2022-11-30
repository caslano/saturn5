// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_ENV_HPP_
#define BOOST_PROCESS_DETAIL_ENV_HPP_

#include <boost/process/environment.hpp>
#include <boost/none.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/env_init.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/env_init.hpp>
#endif

/** \file boost/process/env.hpp
 *
 *    This header which provides the `env` property. It allows the modification of the
 *    environment the child process will run in, in a functional style.
 *
 *  \xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::env">env</globalname>;
  }
}
</programlisting>
 *  \endxmlonly
 *
 *  For additional information see the platform documentations:
 *
 *   - [windows](https://msdn.microsoft.com/en-US/library/windows/desktop/ms682653.aspx)
 *   - [posix](http://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap08.html)
 *
 */


namespace boost {

namespace process { namespace detail {


template<typename Char>
std::size_t make_env_string_size(const std::basic_string<Char> & ch)
{
    return ch.size() + 1;
}

template<typename Char>
std::size_t make_env_string_size(const Char * ch)
{
    std::size_t sz = 0;
    while (ch[sz] != null_char<Char>())
        sz++;

    sz++;
    return sz;
}

template<typename Char, typename Container>
inline std::basic_string<Char> make_env_string(const Container & value)
{
    std::size_t sz = 0;
    for (auto & v : value)
        sz += make_env_string_size(v);

    std::basic_string<Char> s;
    s.reserve(sz); //+1 for ;, end doesn't have one.

    for (auto & val : value)
        (s += val) += api::env_seperator<Char>();

    s.resize(s.size() -1); //remove last ';'
    return s;
}


template<typename Char>
struct env_set
{
    using string_type = std::basic_string<Char>;
    string_type key;
    string_type value;
};

template<typename Char>
struct env_append
{
    using string_type = std::basic_string<Char>;
    string_type key;
    string_type value;
};



template<typename Char>
struct env_reset
{
    using string_type = std::basic_string<Char>;
    string_type key;
};


template<> struct is_wchar_t<env_set<wchar_t>>           : std::true_type {};
template<> struct is_wchar_t<env_append<wchar_t>>        : std::true_type {};
template<> struct is_wchar_t<env_reset<wchar_t>>         : std::true_type {};
template<> struct is_wchar_t<basic_environment<wchar_t>> : std::true_type {};


template<>
struct char_converter<char, env_set<wchar_t>>
{
    static env_set<char> conv(const env_set<wchar_t> & in)
    {
        return {::boost::process::detail::convert(in.key),
                ::boost::process::detail::convert(in.value)};
    }
};

template<>
struct char_converter<wchar_t, env_set<char>>
{
    static env_set<wchar_t> conv(const env_set<char> & in)
    {
        return {::boost::process::detail::convert(in.key),
                ::boost::process::detail::convert(in.value)};
    }
};

template<>
struct char_converter<char, env_append<wchar_t>>
{
    static env_append<char> conv(const env_append<wchar_t> & in)
    {
        return {::boost::process::detail::convert(in.key),
                ::boost::process::detail::convert(in.value)};
    }
};

template<>
struct char_converter<wchar_t, env_append<char>>
{
    static env_append<wchar_t> conv(const env_append<char> & in)
    {
        return {::boost::process::detail::convert(in.key),
                ::boost::process::detail::convert(in.value)};
    }
};

template<>
struct char_converter<char, env_reset<wchar_t>>
{
    static env_reset<char> conv(const env_reset<wchar_t> & in)
    {
        return {::boost::process::detail::convert(in.key)};
    }
};

template<>
struct char_converter<wchar_t, env_reset<char>>
{
    static env_reset<wchar_t> conv(const env_reset<char> & in)
    {
        return {::boost::process::detail::convert(in.key)};
    }
};


template<typename Char>
struct env_init
{
    basic_environment<Char> env;
};

template<>
struct char_converter<char, env_init<wchar_t>>
{
    static env_init<char> conv(const env_init<wchar_t> & in)
    {
        return {basic_environment<char>(in.env)};
    }
};

template<>
struct char_converter<wchar_t, env_init<char>>
{
    static env_init<wchar_t> conv(const env_init<char> & in)
    {
        return {basic_environment<wchar_t>(in.env)};
    }
};

template<>
struct char_converter<char, basic_environment<wchar_t>>
{
    static basic_environment<char> conv(const basic_environment<wchar_t> & in)
    {
        return { basic_environment<char>(in) };
    }
};

template<>
struct char_converter<wchar_t, basic_environment<char>>
{
    static basic_environment<wchar_t> conv(const basic_environment<char> & in)
    {
        return { basic_environment<wchar_t>(in) };
    }
};

template<typename Char>
struct env_proxy
{
    using string_type = std::basic_string<Char>;
    string_type key;


    env_set<Char> operator=(const string_type & value)
    {
        return {std::move(key), value};
    }
    env_set<Char> operator=(const std::vector<string_type> & value)
    {
        return {std::move(key), make_env_string<Char>(value)};
    }
    env_set<Char> operator=(const std::initializer_list<const Char*> & value)
    {
        return {std::move(key), make_env_string<Char>(value)};
    }

    env_append<Char> operator+=(const string_type & value)
    {
        return {std::move(key), value};
    }
    env_append<Char> operator+=(const std::vector<string_type> & value)
    {
        return {std::move(key), make_env_string<Char>(value)};
    }
    env_append<Char> operator+=(const std::initializer_list<const Char*> & value)
    {
        return {std::move(key), make_env_string<Char>(value)};
    }
    env_reset<Char> operator=(boost::none_t)
    {
        return {std::move(key)};
    }
};

struct env_
{
    constexpr env_() {};

    template<typename Char>
    env_set<Char> operator()(const std::basic_string<Char> & key,
                             const std::basic_string<Char> & value) const
    {
        return {key, value};
    }
    template<typename Char>
    env_set<Char> operator()(const std::basic_string<Char> & key,
                                const std::vector<std::basic_string<Char>> & value) const
    {
        return {key, make_env_string<Char>(value)};
    }
    template<typename Char>
    env_set<Char> operator()(const std::basic_string<Char> & key,
                             const std::initializer_list<Char*> & value) const
    {
        return {key, make_env_string<Char>(value)};
    }
    template<typename Char>
    env_reset<Char> operator()(const std::basic_string<Char> & key, boost::none_t)
    {
        return {key};
    }
    template<typename Char>
    env_proxy<Char> operator[](const std::basic_string<Char> & key) const
    {
        return {key};
    }
    template<typename Char>
    env_proxy<Char> operator[](const Char* key) const
    {
        return {key};
    }
    template<typename Char>
    env_init<Char> operator()(const basic_environment<Char> & env) const
    {
        return {env};
    }
    template<typename Char>
    env_init<Char> operator= (const basic_environment<Char> & env) const
    {
        return {env};
    }
};

template<typename Char>
struct env_builder
{
    basic_environment<Char> env;
    env_builder() : env{basic_native_environment<Char>()} {}

    void operator()(const basic_environment<Char> & e)
    {
        env = e;
    }

    void operator()(env_init<Char> & ei)
    {
        env = std::move(ei.env);
    }
    void operator()(env_set<Char> & es)
    {
        env[es.key] = es.value;
    }
    void operator()(env_reset<Char> & es)
    {
        env.erase(es.key);
    }
    template<typename T>
    void operator()(env_append<T> & es)
    {
        env[es.key] += es.value;
    }

    typedef api::env_init<Char> result_type;
    api::env_init<Char> get_initializer()
    {
        return api::env_init<Char>(std::move(env));
    }
};

template<>
struct initializer_builder<env_tag<char>>
{
    typedef env_builder<char> type;
};

template<>
struct initializer_builder<env_tag<wchar_t>>
{
    typedef env_builder<wchar_t> type;
};

}

/**

The `env` property provides a functional way to modify the environment used by
the child process. If none is passed the environment is inherited from the father
process. Appending means that the environment will be interpreted as a ';' or ':'
separated list as used in `PATH`.

On both `posix` and `windows` the environment variables can be lists of strings,
separated by ';'. This is typically used for the `PATH` variable.

By default the environment will be inherited from the launching process,
which is also true if environment are modified with this initializer.

\section env_details Details

\subsection env_operations Operations

\subsubsection env_set_var Setting variables

To set a variable `id` the value `value` the following syntax can be used.

\code{.cpp}
env[id] = value;
env(id, value);
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
env[id] = {value1, value2};
env(id, {value1, value2});
\endcode

\note Creates the variable if it does not exist.

The following lists contain possible value types, with `char_type` being either `char` or `wchar_t`
for both `id` and `value`.

\paragraph id id

 - `std::basic_string<char_type>`
 - `const char_type *`

\paragraph env_set_var_value value

 - `std::basic_string<char_type>`
 - `const char_type * `
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`


\note Using `std::vector` or `std::initializer_list`

\subsubsection env_append_var Append variables

Appending means, that a variable will be interpreted as a
To append  a variable `id` the value `value` the following syntax can be used:

\code{.cpp}
env[id] += value;
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
env[id] += {value1, value2};
\endcode

\note Creates the variable if it does not exist.

The following lists contain possible value types, with `char_type` being either `char` or `wchar_t`
for both `id` and `value`.

\paragraph env_append_var_id id

 - `std::basic_string<char_type>`
 - `const char_type *`

\paragraph env_append_var_value value

 - `std::basic_string<char_type>`
 - `const char_type *`
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`


\subsubsection env_reset Reset variables

Reseting signle variables can be done in the following way:

\code{.cpp}
env[id] = boost::none;
env(id, boost::none);
\endcode

\note This does not set the value empty, but removes it from the list.

The following lists contain possible value types, with `char_type` being either `char` or `wchar_t`:

\paragraph env_reset_var_id id

 - `std::basic_string<char_type>`
 - `const char_type *`

\subsubsection env_init Initialize the environment

The whole environment can be initialized from an object of type
\xmlonly <classname>boost::process::environment</classname> \endxmlonly

\code{.cpp}
env=env;
env(env);
\endcode

\note The passed `environment` can also be default-constructed to get an empty environment.

\paragraph env_init_var_id id

 - `std::basic_string<char_type>`
 - `const char_type *`

\paragraph env_init_var_value value

 - `boost::process::basic_environment<char_type>`

\subsection env_example Example

\code{.cpp}
spawn("b2", env["PATH"]+="F:/boost", env["SOME_VAR"]=boost::none, env["NEW_VAR"]="VALUE");
\endcode

If the overload style should be done by passing an instance of
\xmlonly <classname>boost::process::environment</classname> \endxmlonly
the above example would look like this.

\code{.cpp}
environment e = this_process::environment();
e["PATH"]   += "F:/boost";
e.erase("SOME_VAR");
e["NEW_VAR"] = "VALUE";
spawn("b2", e);
\endcode

\warning Passing an empty environment will cause undefined behaviour.

 */
constexpr boost::process::detail::env_ env{};


}}

#endif /* INCLUDE_BOOST_PROCESS_DETAIL_ENV_HPP_ */

/* env.hpp
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
*/