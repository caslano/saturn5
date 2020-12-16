//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WRITE_OSTREAM_HPP
#define BOOST_BEAST_WRITE_OSTREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/ostream.hpp>
#include <type_traits>
#include <streambuf>
#include <utility>

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
#include <boost/beast/core/make_printable.hpp>
#endif

namespace boost {
namespace beast {

/** Return an output stream that formats values into a <em>DynamicBuffer</em>.

    This function wraps the caller provided <em>DynamicBuffer</em> into
    a `std::ostream` derived class, to allow `operator<<` stream style
    formatting operations.

    @par Example
    @code
        ostream(buffer) << "Hello, world!" << std::endl;
    @endcode

    @note Calling members of the underlying buffer before the output
    stream is destroyed results in undefined behavior.

    @param buffer An object meeting the requirements of <em>DynamicBuffer</em>
    into which the formatted output will be placed.

    @return An object derived from `std::ostream` which redirects output
    The wrapped dynamic buffer is not modified, a copy is made instead.
    Ownership of the underlying memory is not transferred, the application
    is still responsible for managing its lifetime. The caller is
    responsible for ensuring the dynamic buffer is not destroyed for the
    lifetime of the output stream.
*/
template<class DynamicBuffer>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::ostream_helper<
    DynamicBuffer, char, std::char_traits<char>,
        detail::basic_streambuf_movable::value>
#endif
ostream(DynamicBuffer& buffer)
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return detail::ostream_helper<
        DynamicBuffer, char, std::char_traits<char>,
            detail::basic_streambuf_movable::value>{buffer};
}

//------------------------------------------------------------------------------

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
template<class T>
detail::make_printable_adaptor<T>
buffers(T const& t)
{
    return make_printable(t);
}
#else
template<class T>
void buffers(T const&)
{
    static_assert(sizeof(T) == 0,
        "The function buffers() is deprecated, use make_printable() instead, "
        "or define BOOST_BEAST_ALLOW_DEPRECATED to silence this error.");
}
#endif

} // beast
} // boost

#endif

/* ostream.hpp
0nKVabdW8XcS913etYq8114jFHYPGS2oeyzv0epdetER1Ln/5ru0y6/Ovf2J77t06Kf2/UCbFuzr+C3jeb5L137mX6ca9z6N+sSwQ1V9CPncMq9xqj/0P1jJtyn+1zr2Az+J//ViLlDhBzr1A3Tvqer3PjFvcqwfe8T9br1+II7G9QOHmDZVPxjWvx9wH4FcW21EK8mTOSKTU34j787/Yu9KwKuorvDMywoJEAMECFvYJJAAYQuLgAERwqZBUJEtCUlIAkmIWZBNCUIREEtkk91ooYIVjYgCIgoIFilWUGvRumCxlrrUVLHVFmv/Oe9/l3nvzWSRpbXfm++7+XPmLnPnzrnn3Xvuuef6efBkl8/c5fz8z6zl/DoOwP7EsfNpjp3PfObJk9UbP5Mvmb+1Gtc6PjfoXDzDofZjlcq97ta8yjLM4+cfhD5kPX4mv16QNMdgya6TZ1mO3fiZ8ebx83dCH610/Nxe6r7czLcop+rxs8G310ve2Sa+dc+7xI4/2ce7SP75P5lx8Xqpr9y/InZvc1sY93NfWX7b2V23Jf6+x9GXJx3dce9Py+5tnUsvDezsaSdAX3eD6MPOiPMDjgUGAKcAg4EzgLWBdwJDgIuAocD7gHWAy4BhQKPMBsDDwAjgm8BI+gZtCgwy7FiA9YEtlC9I6gGpz0308AX5KH2k7aDPvseBScAn6HvuKeB0+irMBe4Czgc+Q99wu4E/ow/DlcB9wLX0Zfg4cD9wL30aPg88CMQ7Cx0HfInrocb9VN6fw/ul9Hn4BH0efka6h8NJZwANuoT0OuBR4FbgKxp98Ll0NdSFJXr44BvP75MKNOKmAMdKPMoHZvN9C/meRcCHgcXAJ4EzgW8AZ9Fn3Gw+t1TNrUW/4bW+3pK+9loDY4BtuK4cD7we2I7foyPXl2NZj05s9y7AUmAcsAzYlb4Uu9GHZHfgEfoOfJvlKl+1nO/2I7+afdW20Z3t0ZH8GkN+7QQcD+zC9f84YBawKzCf6/F3A+Ppw7YXcCWwN3ANsA9wHbAfcAPX7U8BBwE/Ag4B+uvO9fuGwGHAVsDhQNqXcgwtcxsv+9LX+B3f4nf8Hb/j74HjuW4/Efgu+fkPwELgB/yuKF/620fA9fRluQl4lt/7E37vc8BngH8BHgN+CjwN/BwYZviQADYE/hXYCvglsAewArgN+BXwIPBr4LvAb4CfAMGbtD/gWIjjTU/7g3uQbih9Eo4SH4a0z+D7LQcW0NfnXcAV5J+HyDfr+H4IIkc2Ao8DNym+5W8a8E8WfNuffJtAvh1Ivr2VfDsUWAQcBpwNHA68BzgSuAA4CrgIeDP5NglYTh+QLwBvof3EWOBplrvE5CPR0x6CthDKDqJoYpCnLUSN7CCWIP8TRhkIFxCiJwVpSQglCNsn+WwdrvR1ldb/Cy7X+v8e0/r/ogBNrm+5/+1j4NgWkFvvuOuzC6o5R3Tm6632aGYJ/aJept2vfDoEvyt7tnWbsTjLaK/G4rcLfVzfwTLk7E4pI1q3021nSJ6X4OXlFxybu8rtKWWIzBA60XvdlGWck/iNHLszP36tIrh/bIrQu/TF+CWfot+kzuFo8Afxvybja8gu23F9fXmHEjVW3yv0eHf9zTvuvjciVFkZaTOK8zA3Kp5qXvN6Q9LvUPOLsUL/Rp+uvWeaA7iXu511LJZy84ov7l8Cyrv4axH8NsmS71l9t1aKdx6tyuztUWa5xZwkgu24QdLN0X8GyYrdg6qMBPcyZJ7q6SukgdHXJM0BnAPsp2VpO5T/n+Nyf7JunGe3G3Rbf7QpmCPUr+TLUEdQaMPazrOYSv0wl0DcvotxgcF+tUM6hrQOdIAwPVPaIUtHPvk=
*/