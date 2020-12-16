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
ppiPEViFzXAGRuFMjMG7sDkuxFh8EOPwEWyJT2ArfBbb4Ca8Al/Bdvg2tsd3sSO+j53wY+yMn2ECnsSu+B12w3PYAy/in9AVRHuJ/tgLQ7E3RmEfjMWrsR32w67YH3tiEl6DAzAZB+JwHIQ5OBhHYwoW4HU4GYdhNabiLZiGs/F6vBuzcBGOwDU4Ep/GMbgBb8SXMRffxDz8K47Hj7EAP8MiPIUT8Bssxl+xBC/hZOTLr6oUg7Eco7EC43AKdsIq7IZTsR/ehEl4Mw7HGZiJs3As3or5eBtOxtuxEufibLwD78C7cBHOw6V4N67BBfgcLsaNeB9uwaX4Dj6Ae/AhPG6Md7Fexni8hPuN/lBj7n8w3AsX4TW4GAfgHEzBuZiJd+GdOA9X4Xx8Av9OOc/ie/gCXsK/ooPxuzEIP8cQPIm+LI8zRCk/9MOD5G+Kh7AFfoyt8B1sh7uwMz5B/r74JF6LT+EgXIcZ+BfMwRdwNG7EQtyEJbgZy3ELTsVXcAa+irfi6/gkvoHP4TZcjzvwZdyFX+Ju/AH3oPH5916MxPewLe7DTvgBDsGPcBh+jCPwE7wFj+IdeAyfwOP4DJ7Al/EL3IGn8CCexsP4A57EH/EynkOn8T0FjMLfsDtewCvxMg5Chw/zRy8cjU6chC6cit44B31xIfrhY+iPz2MAvoKNcBsG4n4MwaMYhl9hUwxrQnuG0dgce2Ec9sfWmIJtsBw74yLsgquxGz6N3XEH9sTdeCV+ir3wLPZGr3DaHwzFq7AJXo1X4HU4GIdhGqbjCMzAIrweKzET/4xZuAhz8FEcgS/gKNyJY/AIjsMzmIuXMA+NL8+Nx/ZYgH2wEAdiEWbhRCzFErwZJ+FcnIz3Yxk+iuW4HivwVazEHTgF92AVHsYa/BGn4UW8CZtE0N5gDM7ABJyJvXAWpuBszMbbsADnYineibfiXTgX5+N8vBe34H14CO/HI/gAHsdleA4fxrBmnB9xGD6GGbgKc3ANjsW1WIZP4BR8Ehfic/gwrsN1+DyuxxdwG76If8MNeAQ34ve4GQMjOY7xCtyKPfB1vAbfwFTcjiPwTSzBt7Aad+It+DbegX/FB3AXrsN3cTPuxj34d7yA72OU8f587IiHcCh+ipl4BMvwGN6En+N9+AWuwlP4F/wK1+PXuAlP4zb8Bt/Cb3EXfofv4ln8FH/A7/Ec/oQ/oV8012fYFC9hFF7GNqh82T/RgX3QC4egCzPQG29APxyD/jgZf2b62/EXvA/P46P4K27EAPK9jaG4F5uiI4Z+DLbGWEzBlpiBrXA6tsXbsR3ehx3xMeyE67ArbsZu+AZ2x/3YA0/glfg79sKg5rQHGIN9MB77YR+8BrMxEUfhAByDg3EyDsFbMAUX4HX4EA7DjZiJWzAL92M2nsIc/A1HYHgLrsuwNY7BrpiHozEfK7AQa3AC3okT8UEsxmewBJ/DybgRS3EXluN+rMAvsQq/wWq8jDXYJJZ+B8bhNOyMN+FAnIlZOAsn4p9xCt6K03E2LsQ7cSXehetwPn6AC/AkLkQVx/Gn76Mu8/xuEufq+8EhinzK/W+9g/YZN2AQbsSWuAm74cvYC7fgNfgW9sdXcQC+htfjVhyhx9+Ar2MevoFluA1vxR04R+fTn3fr3xMyTT2fdx9T7Kf4BUbglxiHJ/FKPIV9UVHe1XBauZfrDI7Ab3Ak/oA34Y94G57DOfgzPoa/4iq8iM/h77gBL+NWXT5l0H/Vv5PTvxs8q9eB/q/820+9d8CjmITHMA0/xxvxOJbhCZyGX+B8/AqX42lcg2dwPX6Db+H3eAp/xAt4Di/hT+hkYc5jCP6KTfECNsNLGIfKj/YWvfBq9MY=
*/