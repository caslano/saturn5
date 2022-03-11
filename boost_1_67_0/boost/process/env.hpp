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