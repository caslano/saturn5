// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_INCLUDED
#define BOOST_LEXICAL_CAST_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <boost/range/iterator_range_core.hpp>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

namespace boost 
{
    template <typename Target, typename Source>
    inline Target lexical_cast(const Source &arg)
    {
        Target result = Target();

        if (!boost::conversion::detail::try_lexical_convert(arg, result)) {
            boost::conversion::detail::throw_bad_cast<Source, Target>();
        }

        return result;
    }

    template <typename Target>
    inline Target lexical_cast(const char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const unsigned char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const unsigned char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const signed char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const signed char*>(chars, chars + count)
        );
    }

#ifndef BOOST_LCAST_NO_WCHAR_T
    template <typename Target>
    inline Target lexical_cast(const wchar_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const wchar_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR16_T
    template <typename Target>
    inline Target lexical_cast(const char16_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char16_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    template <typename Target>
    inline Target lexical_cast(const char32_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char32_t*>(chars, chars + count)
        );
    }
#endif

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_INCLUDED


/* lexical_cast.hpp
8P1V+Id1GvGXRDbYAQtjvNtw7y5cDqf4OJwn7uOwv3S9bf/vj7PV7P9vTLLn77Es83jhlO9QPQjVdgAaIRt9v+DGZHv8jp2wx8+bnrU9/sCs3O3xoTv7YY/b+x/ekBS/WoeutErs3+gPiYUE2zskQi1l21g1Ml74rs+dQY9KpdxPANJyoSdNugEpZh6mWfGzagp9wByrE3AfPMjlY+RDrJaUnJAHsW9MeG5t1fB44erPnoFbnW2ueOHZ7Co7cfRdYYdsAFUFHEnGC3+MNG3D5Pf3IRE3644Xzv0WfMLDrTXA9hzLEzs4PdAR+0klfJz3m48ZWYFnD4ln34SbZGXsM3guFF51oxnQa57pzR+UQZZxvBnt3+ut/S6NbRBQ2elVY8T+0onzI2pxfkSZeX6EUAgTKTPUmC00HkRhbGfV3VyTVnXh7+dedV3mj++aZfIYMGofOh2WGO1fo9musS1VRfHC7Q+LnagWFyUDHBwYT3h5v+r0sjPRvdqlakCpLjdLlWWT6Mpf16mGF2ba/elWGmWQlOxW2acyemuk3BoJ2/x+bRim6qERHU93KugeH1v5EP7rSnP8ZdGpdkyVIBsRLyxF0eAxa8mjqW58z8sfG/EjKcmbhkjyG5HkKZnkR6lJDsskj4okl8okq02/7Z353JGGAcDn1KODVjcgfChe+BASYTVe1XuwK1/hJ80fHvPQkNvl78Uj1pqVEPvje96OW/TO4Vm8azlVWf7Wes+aj4ixTp37mWaMn8FHa0GeCB2KF/75u9SETIRoJEc5c/4qbrVybyLkzN8R/t5r+nZfUMjpOfVgEC+5QIjD58CafEkqr4obzRnbcJL6FHz5NL9caqyvPjh40uDFfLSUd7xImS9S3sGfI/mi+wFGcPPMKdyS+YmsY6MuQJXymxbfQD4Xj+F8+8plTjzXnYvfcv920IUil5RbXtyaF3FyqKPRg329V7q3PhIv1L/uZWv/2lYZS1/sFLrB2C4EG/t8gOQGPYWnOB7ePJ1mxPfxk84J7dlBksvHcUNOQnZgFoD5nId8Wr/iMMXG4BnIC5UZmzQWHnOqGKYqEh5pHozUtlgE2VEH6ZGhbZ+i4bWUhtciqxKh9NZFoNsGox2jw8K8/OKZOB/ma1Bsp5rZlUvmOe/ZTOXVHttaLk4MKQZ/6HduMJmbLMiygAQFi/91kf5nse+Uc45UzH6ZM2HJk2CP3Pem4ngCVwOuwx2KowPX27juQmN5Fff+jO+PvaU47ugUZ8sMw0fJHzZo8LAT+aEvuOvHwT95L578WPaoQJHYXchnm6T16fv/XNWz/TlJdDcXUoniYdV5HRU2Lkc8KHG545texlSWJuxSy0rNykuTab/4N2eY3HELltgX0ZDWUpWJ9U+d8cIVX/U6xHYKz47kXW6VeUicfPBloSLnfFk09F9ukg19mjQCamY6a67Mi/34UtHOG/EQu6Ba7fx5/ETr+T3/cWF/zZWDYqct4Cxn/eNogRgxvyteuEZ8HVx1ihVYEqyZmtcmfs0QjsqVbGd3yHambmI7+3VswqViiUYQxuNTL8J4bK20jccRUBRo19/gRG/bOVJ9oO3mF3GsuoUHqS2wAsTn8KX6tI3nBy7qPWP9JPk/psuqMQ3iP21EmQorezaI7WLFr2axaB3bxRoxJ0fruPv9hzb2w17ufr3R4iuT1xvhoGe2Ezhrz0PFNr0oYbVFbHRQKZeBVcRm+MX6+9YvmeYZdG7VuWsXm/p6uwTFZ18kKH4q9o32yhfa5q91WwuXYkNPo0CmuiCc0NzS2IVih0Z3oCb//drc5thdU+QGKYiQGIO+jfBVprl4tOd1T57KhLhhzHS5PU73yDy3R/e4R04=
*/