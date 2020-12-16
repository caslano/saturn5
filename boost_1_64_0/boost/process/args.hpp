// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_ARGS_HPP
#define BOOST_PROCESS_ARGS_HPP

/** \file boost/process/args.hpp
 *
 *    This header provides the \xmlonly <globalname alt="boost::process::args">args</globalname>\endxmlonly property. It also provides the
 *    alternative name \xmlonly <globalname alt="boost::process::argv">argv</globalname>\endxmlonly .
 *
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::args">args</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::argv">argv</globalname>;
  }
}
</programlisting>
\endxmlonly
 */


#include <boost/process/detail/basic_cmd.hpp>
#include <iterator>

namespace boost { namespace process { namespace detail {

struct args_
{
    template<typename T>
    using remove_reference_t = typename std::remove_reference<T>::type;
    template<typename T>
    using value_type = typename remove_reference_t<T>::value_type;

    template<typename T>
    using vvalue_type = value_type<value_type<T>>;

    template <class Range>
    arg_setter_<vvalue_type<Range>, true>     operator()(Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, true>(std::forward<Range>(range));
    }
    template <class Range>
    arg_setter_<vvalue_type<Range>, true>     operator+=(Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, true>(std::forward<Range>(range));
    }
    template <class Range>
    arg_setter_<vvalue_type<Range>, false>    operator= (Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, false>(std::forward<Range>(range));
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(const Char* str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(const Char* str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (const Char* str) const
    {
        return arg_setter_<Char, false>(str);
    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, true>     operator()(const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, true> (str);
//    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, true>     operator+=(const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, true> (str);
//    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, false>    operator= (const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, false>(str);
//    }

    arg_setter_<char, true> operator()(std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator()(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }

    arg_setter_<wchar_t, true> operator()(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator()(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
};


}
/**

The `args` property allows to explicitly set arguments for the execution. The
name of the executable will always be the first element in the arg-vector.

\section args_details Details

\subsection args_operations Operations

\subsubsection args_set_var Setting values

To set a the argument vector the following syntax can be used.

\code{.cpp}
args = value;
args(value);
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
args = {value1, value2};
args({value1, value2});
\endcode

Below the possible types for `value` are listed, with `char_type` being either `char` or `wchar_t`.

\paragraph args_set_var_value value

 - `std::basic_string<char_type>`
 - `const char_type * `
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`

Additionally any range of `std::basic_string<char_type>` can be passed.

\subsubsection args_append_var Appending values

To append a the argument vector the following syntax can be used.

\code{.cpp}
args += value;
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
args += {value1, value2};
\endcode

Below the possible types for `value` are listed, with `char_type` being either `char` or `wchar_t`.

\paragraph args_append_var_value value

 - `std::basic_string<char_type>`
 - `const char_type * `
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`

Additionally any range of `std::basic_string<char_type>` can be passed.


\subsection args_example Example

The overload form is used when more than one string is passed, from the second one forward.
I.e. the following expressions have the same results:

\code{.cpp}
spawn("gcc", "--version");
spawn("gcc", args ="--version");
spawn("gcc", args+="--version");
spawn("gcc", args ={"--version"});
spawn("gcc", args+={"--version"});
\endcode

\note A string will be parsed and set in quotes if it has none and contains spaces.


 */
constexpr boost::process::detail::args_ args{};

///Alias for \xmlonly <globalname alt="boost::process::args">args</globalname> \endxmlonly .
constexpr boost::process::detail::args_ argv{};


}}

#endif

/* args.hpp
N77s9x9nND7Wvsv2ngO6cv5Fef+JlNdr5zjhGe41P1/spondxBh2Ey271rsWKssKZITsttnj+qBDTc72XZImMnybz5VrHmV3mXGOMZvz8hPRuzLn2yYBk6n5VXuTK/UegtPfzEU3PLxo8vRy56eGEVu3E768r2Nrb3b/MFuTSsu9dzSI7gbeW3Om5LVr9t2N0XXzwbWELlmz4pbTi5LuZhL3Cuc4Endvk/6RcceOp+Ykthu3/S/0XQlaBueJv6bYuhZbvxVbLzU5C1vefYaqijLnng+ts6CksnDcJLkp4LXz0TJeVz/WxR8nNveRt/vE5lNNOmJTxyD2+2ZErx3HniNl/33OROrX6xeLKgqrgteTQeh4chGL/ADH+PE7aHgPB/q9+8u4s8kdjTi27ldljDuEcq/RJeMdvQs5P1K0XftY0+7IVvrsd0HwQ7I4lOYHsN9U6vi8nKep47D7O6pj0GkpOoNzNqIT7Xn0A6Q/CfluSdtk01zHRQMl7c+kzDc5iesSd/qvTE4z25Prm/3Jw82glCrqGj00+kg6fTWSzTL/Sv/gQKZ3v6zAefAvLUDT8zbHulzq4/MmY6gPW9dtatZ16LcjHd2j/OLn2wg51ho5J8eTt7Fiq0n2wsbBvNWVnmVaxSQ93mccL0vyUdLkj1oHVr0WVmpdHcDWKqn/53O6Zdt6qqb2itDbLnrrco5SvT1SbsGZzmPHVATv06EnbS3dO48Mnzbat4yUfFxdb5XvzhojEjeYhjV7mrE1d/u6JN9o3k8+yd80tVEgL/0Ws7BesB2vIR8N5bjjcndn2+czea2ePJU7umH35O+Rc2AfV95GJkvvlS06T/qWGonmEvN7c7T/A3+vgGO78Q98xPbFOR+H9RU6Z1l6eBO81sI6w6QOMhqaA4Gxca1T9bzTdpAs6d1Oei+TdvdVdolnU9+RVqAvI/HO4S6SXm+sky/+eLG1nOR9K7bmZn+i9Tw/S/o99551Br5MqefG6g+1ldpi41vSU0vCq5rsbRS0sUDnbYy1xueTChyd7YzIVvhlzgXx7D4jsn3ePM7R76h+7haLf2Xw/CfuQinXL3LGZoefn9O0Pb1K3kolb/Vz5jYJtqfnrHOnjeodxNYzondvdq7qfSjtTqZzuc93h2Avy2279tzxgvH8TA7WDTonyXmTn71JzkGvf5EbNAWTw/a7Gyq6v0gNJNzvE5lbti3qx5ml9aKe7228up0s8Wu6Y9yHRko7DnxK/d7rizff4XR8qHYbpPpN2+TOyTv9TnorSO80sZGUPd3qwzXvpeX2/IlRUpZuOzpGrlUJku9Z2GkgdsZnP4+dLDff7lAjeKPa+u1Uv0Ty7h/o9yOz++V1GSt9H6U5djth91yx2yz7V9ht/mO71gPC8P0HdxLX62umlczUy5Jjdx1hr0v7uSUnNaxP0vtvVh1dM9bRO9aXoGUZfr5vd8/1DdhsJO2oOOc52lG0d0g5eq3QO030euT83taz97HTeTbVopeSMzNMr0p/hnq/k7tJeobH92WUnhNoZLLDyvNX9Vb6Lqt5RvIT/tzUboGHMp6Ruq+L/QvEfnxOpV6/ijJ0zFMVTMMezo1CKaec3CvCyqm0vLKQEa11flfIeKMlvVRD97fDWpHNMrmmtRllEsVmGsfdLDY35pyYHaVP1O3PQv3AbLl+F6k/lKfVcp3aRPoukjz4csqb2O137Hitbjnmao75aznmhzkjOGZYu9DKkWsBeh+I3m9yAmFp0/NPh4ryuzZsrplzkyxoIxf5YknTp9kFpCnsd5bW16ahMnaJO9nsC+iYRM/Pu8mXzKXT331cH7UutpHX7pK203NXah7GZGjanOGgtvveHD8=
*/