// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXE_HPP
#define BOOST_PROCESS_EXE_HPP

#include <boost/process/detail/basic_cmd.hpp>

/** \file boost/process/exe.hpp
 *
 *    Header which provides the exe property.
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::exe">exe</globalname>;
  }
}
</programlisting>
\endxmlonly
 */
namespace boost {
namespace filesystem { class path; }

namespace process {

namespace detail {

struct exe_
{
    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator()(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }

    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator=(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }


    template<typename Char>
    inline exe_setter_<Char> operator()(const Char *s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const Char *s) const
    {
        return exe_setter_<Char>(s);
    }

    template<typename Char>
    inline exe_setter_<Char> operator()(const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
};

}

/** The exe property allows to explicitly set the executable.

The overload form applies when to the first, when several strings are passed to a launching
function.

The following expressions are valid, with `value` being either a C-String or
a `std::basic_string` with `char` or `wchar_t` or a `boost::filesystem::path`.

\code{.cpp}
exe="value";
exe(value);
\endcode

The property can only be used for assignments.


 */
constexpr boost::process::detail::exe_ exe{};

}}

#endif

/* exe.hpp
U4a9lOcZ2rn6GYd138XgauBddP1kemu4pznsHepeVj5aSe3JMtrf1SDrJPXTQ9dPeLi78P66fq4h2lPnGe76mVBVVMQb7gsqKm921w3vySG9kOd+WsdHjuTtU1+96HIc+h28Uq9yu03Z6maS5GlR77Gppzfr6TF51+e/rydZb897ffTyRuj9d6Ck6eWoUx8ZEe5C/k4YCbt1W9XtnNRHcdH0wqKCikKma7idOi15G5n1kyjDzvrqh3J1/ZjtlPHC8NKaBt4bQv7626oIPa+BMn6zSmDqB5VT8sW7arcZTTBP8j2q4tVE/cx31k7SAhgeIMd0iQwvtZVRUGl/x8tkGX+78la++tnB5JPaG39zTZHMS9Z3puSbpsaQ0/aO5ZLx40vJZT3nt8jIx1KHsEWmEgFm3unmc1aXS54UFak6utMY2iBpcbK2YewnTv1s0zz9rtX/pq2LsLd11jaRtmZuA23N0kj9nCDJx+82iM6Uudh9LFkn2//w3T6LbW3KgCb/+hxGXvuzrCWv7nbU+54Re9kJUrZ1zgvHFTL+YZk2xDZtSJ1ppyr3tMzKPD+ulvFLZNpw27Th9mnt772xnWsjfjbGxsq0kbZpI23TBuj5su+b070i425U0Wx/b/XHZ7m+WU/bGvgfvmuIujfPd7WeM2rVseQNwQTJW2KmhSPLKmlklbRI+3tx6rQ/zaOV/HtNL98rRBBpiVIvsysKqitz2Rsr2YX+7f7DNP/yfU/jZfyDqhNHTiFR336ly5B5sW78qzT7MUa5obK8VdX25yuvkmlu4P6vvc+i+8B6/yqUPA+ojqx9AZHAdgsgfX+Y9Xzc/CZux2s/1ON2oRzT/8W2tNc7eWQ93NusstZ2ONDKXdjdxvMTsBx7xPDHL7IdKqvorOZW10ydMEF5nhdNeu1ncHeWvMN96tk2uhxHrW0ozxn//fLl7jIuxOXp37WU4dE+57xS691GlFXnmfcTppaW1n/c2/Pan9Edq7dLaxk/yudKdZzfkzzB2/8L1ErvhbJsZ1m2K2V8jrxbZ3yYfma3rd0YKeOPS/kvSfnTy+3n+shfZd1UtHlOcV8hFRW6r5fsZe24SF79PO6Wsp/J5YU80/wcy5Ik80rx2eFVKe1ezxhdXn658TI8s20YesHIN8shw/x1/e/GcAdlex69mXfvb8a4Gfb3JZnLEyTjCvTxw/B5Y3gQT3c/oW5wLHfG6vLvkuX60ftOVeS4zovettdjaohzjlewuYwFfMynzHNauixfOPPk/Kj3gSRJW8d5taus/5Bo63n2cvyRx0j/ONq9DXrY6u0zWa4nVIS5DhMranLz9Tv+rOP/elnOll691HJ+a5Srou3LzxLbl1+ev848p8i4ma5xPKim2Gu5LFtvWafqAi6SZfnPk+8N2c57nGcdXfU5X+fh/YRTy2vM9ww0lTpNNfvZ+2W6QcqL/zzbK1/ylKkwvQzvSZ5YlsBHyr5K5l9aMZEDsqKqSAXr/cMp093lNJYxOkrP33auaSnjE/W8HXpZXlGBpEn/KlSOj8k1bCzzfU2Sh/ma5yD3GV3Of3rbPS/b7lp9bjXzyPjz5vjDjnrL0Ov4jeR51FFfGWds441t7JJ1s1/nW8dbr4uyb+lhWiMZ9pH3+sSz7/SM47MyMgb6Twt0zH4g0M9LmX3tp0Jsz5XX+UeS/09Gft/Zv9mfK2/PM9OTJ2D2aw3lWWXluauhPDvJU9DEWLbbvq77nPtYnee8J4/jdq9AP2egI11W4V+uQ/N4zj/ybPzbQxuadyJ5imTet++wz9uep5A8E4w8AXOa1i1nEs/YH6Xcz4SfqJ8JfzPxvX6O+2Hb38Gh5jPj9XADeXUUS3mkWX0=
*/