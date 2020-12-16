//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED
#define BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#ifdef BOOST_WINDOWS
#include <boost/scoped_ptr.hpp>
#include <istream>
#include <ostream>

#include <boost/config/abi_prefix.hpp> // must be the last #include
#else
#include <iostream>
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::cout;
    using std::cerr;
    using std::cin;
    using std::clog;
#else

    /// \cond INTERNAL
    namespace detail {
        class console_output_buffer;
        class console_input_buffer;

        class BOOST_NOWIDE_DECL winconsole_ostream : public std::ostream
        {
            winconsole_ostream(const winconsole_ostream&);
            void operator=(const winconsole_ostream&);

        public:
            winconsole_ostream(int fd, winconsole_ostream* tieStream);
            ~winconsole_ostream();

        private:
            boost::scoped_ptr<console_output_buffer> d;
        };

        class BOOST_NOWIDE_DECL winconsole_istream : public std::istream
        {
            winconsole_istream(const winconsole_istream&);
            void operator=(const winconsole_istream&);

        public:
            explicit winconsole_istream(winconsole_ostream* tieStream);
            ~winconsole_istream();

        private:
            boost::scoped_ptr<console_input_buffer> d;
        };
    } // namespace detail

    /// \endcond

    ///
    /// \brief Same as std::cin, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_istream cin;
    ///
    /// \brief Same as std::cout, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream cout;
    ///
    /// \brief Same as std::cerr, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream cerr;
    ///
    /// \brief Same as std::clog, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream clog;

#endif

} // namespace nowide
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#ifdef BOOST_WINDOWS
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif

#endif

/* iostream.hpp
kx/RZgVdoj6z832n30S7kDlg+u8+xihmtnb7EXUhy86s3qGxT7CPKXYhU5XraDPFfBJD36KehfTW+2rlvzEGyXhd/l7dfyLaU0n3w5Nff0N8it0tcjQW8SkW+WnKRsSn2POPbR4gPsVqjDtwAPEpxr+N6yqst/AO5lOIjyyI2ZSaA3wxt5ItMUlrGt63BayoS2Rl6R6MGoQxEU1WEqa/X56gS6fcEyfzgyn3xIulny6ILL10IQbpPGRPvb7ZS/r38gNLD6NvS9MxziLtRMnO89B/VVwi1iStXcU2U2HVXOISy/Od2SLLq0XzmfmbpaT9O+GIjKGuS+w1SQvOLdfeCAt1iZ+FtNhynppIV98lyjEr2SrDF4xBsh4sz88XC8xHvzf8H193HR/VscUBfDYCJdhaNmhZHIqluBOcYg3BKbJooVhwh4UWaNHFKbo4RRcLDosXeRDcYbGiLcEd3snrfb85934+O3/d5PP9nJk5M3N1r5iFj1n77X/9jvrqmcUuweIWfy+/M1LfLDIwq7AgBdriIuvGrHK/DekwP8mqw/TvLor93izSw/TvEooni4Dpr7e6ycJh+usaHoV5yVYwezB+937UF8vrM9yjS2aBGd4JRBYJM7wTSGEBsoww/ft3RYPgcU6yYG2JIQuWQ6wiLl5Rn4csWDt9irhE1pYkWn7V7K28zkcWy6xCtz5L0c44OhZmVmPT52noa7K8zHq32Pk16iPryuxuho3yG8wNab1l9inLKPnuhkZmvKPnKS0XDMzSD+NH1ofZ+8FHhqKdjc1iLbN8r6K7YR1rYhYdmA1ttn8I+oysHbNvLNVOIa6pWQxjNqdUxsrIj+wAs77tMmyENaP1ndnLA7lao53NzaIms4Y5h5RBW8h2avYPLWNrz0iPvm5hFpuZlXEdno058YNZtGA2yN/4FeZuSxp3mP4ai5msAbMdBZ80xDpGNoFZ4VxhyD26lVlUZFbv0OfqiCNbzez1qqbyd8rWZlGKme9xhzfInSwiVNqKxSmdKLOdWeRjcT9FdXyCOUFmg+mvKwbImjOzCLc8ZmhvFpdS/2t/0/8Hzk0OwxzsbRZ/pZfWouGOHOjPMWYRGv6vJTfiwt18N1HmBLMIC/nXHtP/M1ac2Ye2TMI4kBmupZN1DfvXHiWP9dOEx8h9uhnvRH9I/2c8O0beczLTLOLCpEU4F4yQ90DSNQghLTrVr2Mw7vPlvH5Ay+nbT6zGOJB9ZZIWNX63A7kvNIs0KaQdrtHMhDm4XNsfaTan2cAUKJMsPbP2NxvcQA7cDPucJEWceUXwuGiy7Mxau7wFMAcVcW6yKcxiK228jv5cGTzORZaDWcu3ZS6gXxRxPm7GflHEJSnizH8o+oWZMS5WEReviPNwM+bHzZgfN2N+ZD8xy1YxAXHuVXRMyyyibJvT2BaQBSszQBYB0x+/JCnizKtpf8vs0oqEruhPsmBxsWTB6nMp4txkfZlt6fZ2DrZLa2i7y+xckYSDGCMyC0x/POEhszMbMqxsUYwRWbC2JJK11LYF95PHL3tFH8pcZxYjhbQ/Jsr7y2PWm0UMs2/NS9YijszNLPKfskvQnz66fsbq+8tbsSDiNppFPxZ3tv+D8ojbpB2za3bscYdF6OstZlGLxSU5+1bGfCGrqtlfQn8ftTNB5nCPlleSKn5BX5O1Z9Y69Q75fSey1iZp258UEPI+ObOoy+zDxOeT5D1fZjFWSPvc+XBqbHd30nFyiLQLNsd8xO2hfQcrs+9XBXshB788LrhLywlv+3ZEf5INZpaQXX4HNXpf8DgvWTqTtHzPD8ahnQeCx8WTjWZx18+Vz4wxOmTGN/fuJM/5hr8vgh02i8zMnC8=
*/