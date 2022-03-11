#ifndef DATE_TIME_COMPILER_CONFIG_HPP___
#define DATE_TIME_COMPILER_CONFIG_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstdlib>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


// This file performs some local compiler configurations

#include <boost/date_time/locale_config.hpp> //set up locale configurations

//Set up a configuration parameter for platforms that have 
//GetTimeOfDay
#if defined(BOOST_HAS_GETTIMEOFDAY) || defined(BOOST_HAS_FTIME)
#define BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
#endif

// To Force no default constructors for date & ptime, un-comment following
//#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR

// Include extensions to date_duration - comment out to remove this feature
#define BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
// these extensions are known to cause problems with gcc295
#if defined(__GNUC__) && (__GNUC__ < 3)
#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#endif

#if (defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) || BOOST_WORKAROUND( __BORLANDC__,  BOOST_TESTED_AT(0x581) ) )
#define BOOST_DATE_TIME_NO_MEMBER_INIT
#endif

// include these types before we try to re-define them
#include <boost/cstdint.hpp>

//Define INT64_C for compilers that don't have it
#if (!defined(INT64_C))
#define INT64_C(value)  int64_t(value)
#endif


/* Workaround for Borland iterator error. Error was "Cannot convert 'istream *' to 'wistream *' in function istream_iterator<>::istream_iterator() */
#if defined(__BORLANDC__) && defined(BOOST_BCB_WITH_RW_LIB)
#define BOOST_DATE_TIME_NO_WISTREAM_ITERATOR
#endif


// Borland v5.64 does not have the following in std namespace; v5.5.1 does
#if defined(__BORLANDC__) && defined(BOOST_BCB_WITH_STLPORT)
#include <locale>
namespace std {
  using stlport::tolower;
  using stlport::ctype;
  using stlport::use_facet;
}
#endif

// workaround for errors associated with output for date classes 
// modifications and input streaming for time classes. 
// Compilers affected are:
// gcc295, msvc (neither with STLPort), any borland
// 
#if (((defined(__GNUC__) && (__GNUC__ < 3)) || \
      (defined(_MSC_VER) && (_MSC_VER < 1300)) ) && \
      !defined(_STLP_OWN_IOSTREAMS) ) || \
      BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x581) )
#define BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS
#endif

// The macro marks up places where compiler complains for missing return statement or
// uninitialized variables after calling to boost::throw_exception.
// BOOST_UNREACHABLE_RETURN doesn't work since even compilers that support
// unreachable statements detection emit such warnings.
#if defined(_MSC_VER)
// Use special MSVC extension to markup unreachable code
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) __assume(false)
#elif !defined(BOOST_NO_UNREACHABLE_RETURN_DETECTION)
// Call to a non-returning function should suppress the warning
#  if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
    using ::abort;
}
#  endif // defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) std::abort()
#else
// For other poor compilers the specified expression is compiled. Usually, this would be a return statement.
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) x
#endif

/* The following handles the definition of the necessary macros
 * for dll building on Win32 platforms.
 * 
 * For code that will be placed in the date_time .dll, 
 * it must be properly prefixed with BOOST_DATE_TIME_DECL.
 * The corresponding .cpp file must have BOOST_DATE_TIME_SOURCE
 * defined before including its header. For examples see:
 * greg_month.hpp & greg_month.cpp
 * 
 */

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_DATE_TIME_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_DATE_TIME_DYN_LINK)
    // export if this is our own source, otherwise import:
#   ifdef BOOST_DATE_TIME_SOURCE
#     define BOOST_DATE_TIME_DECL BOOST_SYMBOL_EXPORT
#   else
#     define BOOST_DATE_TIME_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_DATE_TIME_SOURCE
#endif  // DYN_LINK
//
// if BOOST_WHATEVER_DECL isn't defined yet define it now:
#ifndef BOOST_DATE_TIME_DECL
#  define BOOST_DATE_TIME_DECL
#endif

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_DATE_TIME_NO_LIB) && !defined(BOOST_DATE_TIME_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_date_time
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_DATE_TIME_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#if defined(BOOST_HAS_THREADS) 
#  if defined(_MSC_VER) || defined(__MWERKS__) || defined(__MINGW32__) ||  defined(__BORLANDC__)
     //no reentrant posix functions (eg: localtime_r)
#  elif (!defined(__hpux) || (defined(__hpux) && defined(_REENTRANT)))
#   define BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS
#  endif
#endif

#if defined(BOOST_NO_CXX11_NULLPTR)
#  define BOOST_DATE_TIME_NULLPTR 0
#else
#  define BOOST_DATE_TIME_NULLPTR nullptr
#endif

#endif

/* compiler_config.hpp
hXOhNvMHfPSf+wr0gS+R9EsKA6/TfBLuzwt5tYBnh1MJC77yoPnzapZzLwnTVC9YvXXmMMq7hyX7to6z2ovvjzMoZ7QEShNG3Q4WlY+kKsUfbnwLCCFZaSTW7T3sQdAdydPJ0N674rQNc5w7VQ1GdVA/y35kjhkI/EqqBNPg72h+00XexCctNDJeUGsKnxR3jLsJpbtSlj0AoBkA8Km8OEGdpXx4XHcqHBtjf0qM6dtWtiLDi8UslICL/VG6DQfbKvv+SJmQBjGMoxPXDtYRCy7coteXwzN7Qa0t6oKeKr676oBLxpwG6Ickn4yHGW9GaiXtvgxHGXAxAH8ftmg6fsBD2z1YU3vo4QSV7gp0RYs/2bxy/J8MPeE2GuILBsofZC4uSd8iWiAf7MHMwodSImfrxP6E69VP3npjm9RTI8HXlRZeKbEDThHUEei8uUKk5u/PtDdsFaAmHSNQvteX32OTFm8CftPA1RwTd6/shJrWdoQzizOtmKtZOlIGypxwi3jObWo80a1zYTx2lgPE/fC6wnCrnQktwTZ4D8iBKL3DCwVCezP40DK1ZLNXqNO+YWhrrrU44pOarS/FyXtUelJXnIP0XNgqX6TxbPBcbE7Ek0cJ0M59wccEgK727I6BffUYdA5zZlt1FxwGTU2LOD/K5qRhvuiJcZevSLIEnrWY5wDazbofUlytOlyQu3vdTtX5iubPhevy8lhQsW6RIMX6u+i0zjtaG2JycrCF+c6zhpWNj80n5vo2skdy8EUeHtHN5wUb7l2neb8MyeisrZjOI4MJ27n2S8zp4tDKNpsmKHA0CvDyT7P8UlWkT3fjQcbdHP9uLzP9vi/V5sPCvoK7UZ2SLmdVNwU1b3RN+AfsKWk0bX1jDhhVxHiBepkrTh1t0fijTc0ABCz708DClNg2qR9mn9SthLGq71gRpdqyvapNaYbaSu5MWReUx+gLYrVUZDTsCV416OHagJS9imrj0GPDUzqka5Z22iomPweAV0LJHYmWjCrtKgpF17Smc/fs/efJl/d/PdtJ8KhEFJnK9creZuBYuPpoN+4a+k1vQ+v7CBpvuY8rGd1dlFQY5xk9qTOgcPMcLTle5RKtTXHXEsVnkF1JFYSs9s36CHPwraqKgJ2jpHv9+HTSMDa6kNTEpVreulg6L95keR9dh9imWXcDwwG4YhAxPfjeqBTwmWUUWWAypaRIorORtgfRrsRsT7LQdVM8uxnFUbzM3N8zhw1v+b0qMk90JyBw2EWJqfAWgru2LGws82y8Cu71gU5lefgENW6k1rF5UTdGp1E5S+L4Ue+HMlTT4uwhU2Mp6ql9mrwjgU4yFv3zqKggbNPUdV8kOLt7lU1NXboOe+4k0JKbKpe/i52kRVsnToE3hVPiE6ZYKksrhGoEFV0rM/UAia+tzUGlEjVBOTZsssW5lPN16wsa2drzQcKxNp1giYGWvxcvjWh7Ax5NZ+8+rU6g3jKRT7ttp4jgYAaoCiHRBZxHd4wk6LEJ8EHjZn5Ne+RrH9vfExKYAWHWjnUBgdJxyiTSORgsJpsX3jGAK5BLkHJBfePtUN+GUyxhEIyXgyqpXzQSxp7libTstUq5w/9E4T982u0TDHN46qb37k2HYqw2zfmh60qtvyy0JZRQld/Jnmv+EYom0BzZ+FZMpLMkPHrCiFByqeF0uTieJKAVZWgK1rahIALPZin2QspmL3GKni46HX9bDFvB9DegdwmKpPzet9fsdX7WbNExMYDoIzw/6aT6y9kRCWErPlV/wx966ly1CscjTolRU1Yr7ga9DT/dsRKs2nAqiFRb+QO1D75yNfkQvWB53FVDmYY6nE0MNrEk6pKMj/AsY4CrH2WKboTjmYNGJfNdyHC43Wwel/5qyNskxUjM/1QsJLVVADulLIGj1Wo9dCkrtPvP12UixlzvfmDTkJtT/9TIp3WmEaoK6g4sZALIDAsMb3Q90Ms54mR7hrH2w6bBM5Wcgf7ki9MOI60kDB0eSgnpL0DbGYaxKgBQprM9O7X2KpAtS1lY2ggI/UAm+sNMb7hHpHzVvidtASG1YDKuyoZjtsevcyYs2XXujTsxM1QKiL8g0qQY4QJng27Wte2Jwm8+mIg/OiGgZm+KNP5cLI/NCKpZ4d2qGRUbzCnwxR1f2iweN7/yL/0jXl/t9w6OnkRneCXmzZU4zedOThNjUfo7/xy12ryj24QxAG/JfF0JniFzjOiwWzup5lcGHz/w6CkyT5m1Y546T3FtIpDnu24MEk0sb3yjfFRZR0rCcjQeiUXKSzOic/i7El3ZxI8sbfY2VZjzdSEGjJYrq1v6Q2YmCYGrW8RKXLncyy4ymmUihDMl/WPFcbP1sPhan3r0eO8XwiBdX5tT3VM0C4ut/y7PfG9GM14EGGQvkQn/Trx/B9e3N1lByB6AegKOqGotXTKrUVZWlDbd4fosG3Zze4l5rH5f6gwuhUguXvNWaBP8X9cegtanKevodPuRjj3YVdMbP864C6oYGt1b0cN1IooKViikZwwRK9/poY4zcFpjlzG6ZbYglpmOPgOjYSZtgKCLxyDVDnVC5HDKkjoF5jkocMjYSc9MlBmuhDfIanl54wTsG8uivtwQLQ+AliLZVSC/ZtC78Vjv5Kt9O8U9FUMqGX86j0xmygg024YisYcr0IquIbXk23HsacCv7MzQaV7RHhPRAI1m0bZFZEFci885p25eeGsIysfLNVZeT3ZCZZsM3s0MO6zhp/WOViC/LRsYZZBKc+bE1Ka1J7g6Mfipf7ldN3ddNjPrjWHM090OH6kTQ4W9y9oOwtXmsfaLRDa16Oeocr8WUp+qB3t0o/8NAf2HZAig1oY1f0sA04njT3MmEArWEwaX3X5KNT4svqWvm1WH3RyvkK9iWSOWr+LJHFBGPBIInn9T7ZUEDwXBpi6psMHf0wrvSMLFj0ayqchutXNokJvkWgP4/hFzQSomMGyep4BtPbF7ptewRaL793dlcu4P3JoZz/P1TaoNOvi8Dp6Qeb9HLreiBPia8YXPW6hxNmhA4wyNywLVVuLsz3Tr6TBanfHaPR5Ci6rX13+pf045B4g0AQg0IqjujlO6cno6R+z/rBMmyCHY5KWsQXqrHVYc7Ggb0Nl7g1Vi19+1seNo0CAM11NsMAoMBtDZtm3bvrNt27Zt27Zt2/b2z7aNu4eT9LFJmzZft0SFHwte26c3jKiPwEFLX4sN0IxqfNnrFa6G2/hMYyXK/E+nk4aEeMN/nUiP6JRAwCNuvvZqXzvf6ScZs50wYmAs2qV1EhAo4SiqULA5oNOJM1VDJkwSkW3jR7nLJrjMFIOZKh4j6vVjYfk6KIffibyyTxG5LPPGztaAifDVgnuwAYqK5NrEBZoj88nKuT1yFFkq4DDT4obqSMhoU+wfbuQ0tAhp9ZPaTBPTi52rm7/0TEw8OfaHJO50lNQjl4GnH1dAwhzZn+io5Wi+z25tkCXCe2k2kkTI4qnAIMjin2wtvFaiTMX3GYY3TYW+kz4nc4RHiSoZeHeERwlwnf3ml7WcTY696s/Ln462RK1c6aELzK2GmUBI1yC7iLdOXGSswz+CtRKaECR6lGvG0ZWWR808KLsekxha8rPbS2Fw7Q0pCi5UwkC22+Q0wCEZwHc5E82A27QPJFZUasQ3e1bmFcXyNu82WeWJt+KGXlI8iXH0xNxiESNj5OFVnBrD5HHhzkM7hHDZ6pX/RmfCRe16rZvfXLduLvP4VmIP37PZvIpvZJ++SdDx1mcSn7nLxHY9YeShKnpG5jf88rEYQcq67+18DOrJIUqVUuDMIey801NLB7kafG04tIN9psSWICRRwVJ52MHKyBvRphecBSbzU4LJOAytgh48Vga6MRKX24KH2jEZK91SxFRaJHd3qBYnpMvh6jtf5gtlAaQ8b+wKxnftr1zMZ9CE6OFDh+Ylu/L8j57AlOETmqQ1e7g4fzSdGGmTK6lDicKas+FG6Yub6ca8oWFRO8oc9Bfl8IH3wt/eiTXhL/4zcV9GEf3d0T25zBeqb0ToowjD9jx0zEvI+05LgfaT0uD4pS4K3HlgLEgWmzj0Qu/xDfV9RNZIIoQcVIhSOiArghfsIcBXCdmWk0KGspBV8uio8BZpmGOoXVX5ZAB9Oc3byL3KQCIIezbf5BoBeLrl5Ncq6v2a4MdsJGQwWPELJ8Yhrov7WebLnOuk1COJq/FCAR8J1WltvHpAm3tN5g694YvEhLMJcITWYfoqiXHZYVX/MlraATgpeuSHtlS5sQcdd0enW5U0gysh5xU7agnM55XO435L6k4yMmtse8r5L+BJeFQTkq5OpGrdrTXAwj0KLOCUQwSmnoiI8y1O6wD6jvN5tZxhh/Hm9AYnjugiZKrczFQmU01DxsF05kuh2Q40Uvh0k2sW1f9gwpczncUz1owAINATsdQ9LsGp2B+5H0wcNp8EpGF8bjdPcDkIFhjvKo1cAC+0d99Ix81XjC6cSNPfP5Ci/0Iy7Sg2lb4rYX2OmTptHzGAHoIwV2KTT6KFejk02Es4r5NC3K6jHeO/w33IyfDbf97UOq81PT0FiEolQtumyt6mElUG6kKbD8KnIDbC7gIoVlpRgV+8BkzIzz48n7wA3X8PBxt5x4Tdn1xX1dIwgRWBDVSwd1uxv3db85qFKqgEod3zGXqCHQFj94vOZUL+t9VpgyntovpTnnWVS1JqFUOjaUDZaH37vwTKfYOfH5LUJt2yzYK258jVzz3wkDTISI7u5GJ1fIn9NLkVfBWQNHSLZchTAknTsq4peuWjwPh16GaAcd+aMvF59Dk9J1wATV+wSfb8lxIwskCvlcXqVYcOkG4l7VmwdWAPMHsRTso8barZQ0OmpxkT4OnpGeGFA5vpsss+jwilKzMhEakob44vECLvetzBNj1SaTJxaasks8hmRBx5L92yfdHjAKWSa5Yu3wnTEPdvgSftLEJ8xLUsU2pj/70dzdIXmMOQgBw2AZdIwOKQ81BvZyHEJcsWmnQXdMJ7EntKUKXt1+SfmGXHK4z2n+m4VU+IjczSHZjf+xv/Bg3oqpN99pfcxLLnivzMLlaB4088QcOg/S4OiFsycLGDzValislvPfD++rowJKzxk+U2v6EcnPNlOHRWtKYQBQ1E2hWg8aSJWnZhjKPdMEMZRjwzsfjttxm/yqB6YVeouzBzoauuaf3lnZtWyqeJJWF+x+ItG60U9xf8hvEnwpraMMmq7dy+KqbPHUvatuonxJbhrsiUpHrzqaUy/3zVGWjsIxjl24CBEilwDWFY7zgb56TvIwFeljP6IQTHUFOXNQAkB3tbHygS6+8iNwgy4ifzVwR+2jCKBP0YZoek2yiQ3Tukjn0elGr/a4B9kGhfefS3k3ByGt0lxFXLnG+dHaUUZgeTOBWmlOQw1+qZdzrZqn/vN5Zv/WTBevoa/5VWS3ZI90QHcxMGnky2W6DNEO0H0Y+W+lcjxoMTDkYO1+pMF6eZcl/23SkjfsjoN7O8yJErlLcIyrWaZpJGPxuHsBrx4tkNhPeqSL1HpU2kwVsbOZLMDbalA1nUk6vRWiZl9GK9HKmiwQNZo0DbQRq/WgYgiQt0ZSNhd+nJEuzZUNB6mvtaO6Fj8AD8o2JjT8pjCUpovRN3IcscxwO73UCjIoDBFlZnF0D8l8X9GJtH5xqJTcZMg9tvUshvDvAQIzjrmc6KihqlLJ69rlYm+l31JdKLxRK0g2g7gf6QLfgbjQRHLg2gCyd4emheEfU4BPi8CYAt8PHohDnE06W2GozwJkP9pvX5SzwzjCCym3InAgWQG44dn7MdAPbwgNIjJBPEljUL8whax4RHrP25EvFva0K/Ca5b+9X25Tyrv3hLC7IxoPIIDIsRhYGzXXz7rSQUwByeuUJvew2s0jATwH5zWV82RKo1fbCDPV9Jjz4eIxLeE/7IAE016BjXUxlCsUMsV9moH+26rYNHgBEU1tnz1GK8Tb0wd5EcKuvkd82MM9p3vTgZamF8nSD5NgEVRn0hIeme6sKYzqjNmXhXoT3kjoLUIMLJlZRCmeZ3QbEeFhqyw2F2X8aV1NPLI1XFacaBdfLu6z/FeNeiFvBBSWhg9eZESc25uuyuQpL+a8WHbZyLtoyLab0An11pssqgftwmEvrcnjaD8mQ/FzvS2f0cPHEYqNGDcAVt6uw5GrHIQqNi6PvCZT0/KiZTs4qpbh3rIIG29P3xGkdvoJgOynjVgZQMbq1HyjHKVzTtRNNs7o7X7eCHf3MpexzWhiKJkH6aAABilSxDvGC7+pGFbyRVdqnmRgWt7w0vg8N+ykRW/LbSft1bgy1NrxdLk9M9pNVdfrtasOY8QUPhQMgbqE9G+e+C37/uUuJavdIjQFc7jau1A3c6BAhY5XvjGZJc+EdOHv9aH4qWgExY/KgdQRzcoLiTS5gm3XpK2AZKZfSyFI1YpFd33nbEz0xYqYRReOo2X9yZ4mzIuN5xtPCP84DWS/gPbdSoFcAeL8yHksAUidO1gRysHrmfpcUcURKfXmQbmMZLUhlZS8dRZb5DB2kZEZUXWu2gUXhQjWFf4O3vbyD9pZVZ7LCfrnIChjskFp5LvZIRvbTkD1xif6PzloAt4XGFH3XmxhBlu1aDY6Uf8U9IJPA9H6IVN2sCp2u3/LDPA2vHAj0Up3kRPxOag6aZn6kYDFPS8LJAJhmV4IHLaDDcpwGa6RnnDMmP1Fp1spc8Jio/GPyabIIvJjPTFRR3a7sCdJUPsc2saiV4BqAHx5Jn11gMG79qXR3SkXN6V0VZkLuSLKKwd4t54xxy1fyIBpXFY0oA6w/DWP/FzrnmB8A3VtSEarYCBdcVCewxSlOL2g6qr6lj13su+DbaM104QH+YhBTvYnLJOcZzqB5B/4ywKFgACzIQVO+FWW7TaNs91Dl6TJ1hqIGg3QdP2US8pThtjiWyqNDKvpJf0OKaceaaGz/IGmm1aNBBK1pOfatRQZjTQN+JU5cZYSle4IAnB1Qqjm9uDuU6OJ/pw0jyazsLkycvFwZTIj17/euf5zr2Iq2Q5RiUptKYLXtcrMYl0VgBILkzNOpb4IAa8T/EWWcPQzvgYnMDGlp+ZMn7OzgrconTaMajSeTY7jVUvbrxU18TNrY8meAoE+uk6PzuTaak7xTfn+1Eo4gPP3ALRIke3x7PXuXAwo+wyu3lYawSC0Yt+1g2mGuHvgsvPyBA7Gn29D8l/Qh5hENLwhD9DgKoc+/BGq9tUuOIJBETOE7ZkhPUlNVHNEbgm8W/9AWH0PecMLAKIzL8h51a73kZcRleRymj2Mr1FUUzrR97nM6ymiH1H5/U63ow6npifQxkByQLliUQM2xtmxE4uaSR9LSVHFCh2PQjBw5PPIUoKsi9O1z5pCwo4aCPvg17K79fJQ/06Tft8mQGJeclWBGQHu7bJuUh9A/jzHaQKpDOIYf9bj3LrYb7hlRAqFrQNCwrgVK0ywGtWGkJB4FIxF1ENBRgxtI6DTcaKDcEpNPfz9iIxUd2YAWbjJFaDZWVjKNriSxBihfDu5QEGZ8m+yje7tMBHLnNHZCPHUzuJjnpiyotTlnnmtBMyagza1TU/m2gD57/FT48sE2J6dVjgSUmNsantpXpyWhm7NR8soWnKyAbgIyl4qVnYxlh/vCiyT8v1j2tAiyPWR/t6gjYkz0mGajKSXkrlrf+KIWU03JW6wv9N/7iDTALNIYdxkwhMHM4v/RuOB6+vDSS+hFRDL+pXffgg1EhTLtLeaTNvEIJVGpEfFGQfV/Jt/21aZ8xZmMPXMY/0GYTE1X24T0f+2KQNdODk8vcFpmLamaY0Tzo8wl4OZJeYV5hsrTjAP1JxRi/T580gkoUDxKnIPOIsMPexMGRaKNE5p79ELQii4lfCfyFOsDOWf9TmuO5RLPmaSCshe4dbwY+haL2dJnLxodpzfJCG4c1TRPa52NrAYEf0UUYznNZKDmwjFxEeMIVGiqMG8HFMGDpDMcQKRj29ca3pSA7u1hwbBwy3TnWzGAFnwOVAMRugiR0iJ8yuujj3oKAYUYXgGeiE6I7Rb3eh6ijmp33oeqZZ3v24c73WypJYt0ppJdpaPBw9mLCPcWmJr6U+R3cT6iYtWueW4uAp9IIMtmgifcDBYoh8gix3+KW0F8b5tXv+k+Z6UzrrbBu/8oOUXHVsZ5Z5WBIq1A5eMtqoFVACefQ/JlsAtzTX6lR66UL5DFkTFZqNa40QGMhwQMpDwBX478hBlcNvch5jPwp7xD1pxP9fINCZ+qD+YsfGGSjjPcOSsj+rM3Jq2it8TO2utxVOoxZURfQ9W1JVnb3DnumAMaKMjM/B5z/NnDQHgwCFANHY0R/p30MXJ3O5uTl70ShEZGaJwzhzBpODUVS8SFj5C47C5PSL341lg7dRFoI2jI0Sx+JSU9ltT8R3L557RreCUuZzMQqadcilP26il9FBX/W/3GGJoGKvp4ldSSMi50yJCAaiJDFgjS6kv5UW1wDvxA6oExgJR4W/Fde1OdI82yb4b1g20D0svIbTsFCLGABjQM9qUH3A0zVFHDmqcXAaog30CxL7PoL+MVyrYjHd3Acnz8QOesG5moSTBxOSKxCXXyxQOIoq7r+1HrHFLCzOja+NFLnENRp6oQSniy1aj3XkLGjP28Y6DxgKXb85kgyGsFxAP8mqWB8yqx4CEQ6EKav5PozXCjIenBl8BlnPQu0Djozn9X1Ki4VlF3q/1+ruZW7FZawoiCzfxcLwU1yofzbFBY0Q4EZE35tj3DRxqCSvObRWVtR2lkjYHAmK6Yjpc1J05NjDbIa6E0hI8QgaO8gdRxkflz9kjCisMR6HNZr75cWeUHUqj+7lLPRSVC048ONTs3bj2I9ASq0439RGaP2lGecUzU+lkLF8RmhjuMJfcdrWIzvy8nHTFmupsVTkhaPlj7329gubtZtj+8Px3X+OBygejF1h2+BnwuwsvROnPdlJvBtbv+ha22IHhgi4p0aIg5H0k1AqWT2xeNDeONNyjK4dRc0cIf/RNIgeEp6iGO1gxibSbz5hAD0qwOT/hy+a6/iuzguQ3EX1GfJSUO16ZeSKIMEL0V7aLLqF/ARs0SLKqZWjN1CaC2jHEDUsr1CdexQ3dEDZq6/4tDyEzJZ1irolmBeqYYHVbB+rcTYsDDqqGE=
*/