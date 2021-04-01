//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593
#define BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593

#include <boost/exception/error_info.hpp>

namespace
boost
    {
    //Usage hint:
    //if( api_function(....)!=0 )
    //    BOOST_THROW_EXCEPTION(
    //        failure() <<
    //        errinfo_api_function("api_function") );
    typedef error_info<struct errinfo_api_function_,char const *> errinfo_api_function;
    }

#endif

/* errinfo_api_function.hpp
Jojk9d7q80bEZyGj+bqhtdh73N+71ADbARdQ/AQvPvkK7sNns0x9kNw3dJ35wkegBr1nr6qERmD4UoTlrbNU6wS0YYd0Hk6ImWH2nTY/aRjMdaDnnHmZhPVB9zCXRQfSYTBKSojs35etZ5q0oQnnf5PilU/rBKcuXdoX1kiCtuZlUTP9UZBqcbdaVpwDKrbp4qZEXeDbl2dBN+gV/LsHlJOXV1anL2kkkslGpvSVPScEkdcGK5kcup4o8HuB8KlXOI2Gu476jCY6IQT3elSQKZNeHrQpgNB7OM6/NbM2Lko0TigxpWi/Ma1sBAIdd7bYK7FQpz2tzrxI4dWi2mDskRUtJ21fUr2f36Sir0JhhAxZpk/4TgaD/Zv4LqNsBebYOAjm/LYM7keulTg2x0xQ8lrZ9KeVRd5+m9Py12n3ce1jhaCbEGDE9S2ZPrda1lJ8Mc2VP3tGfoxvzoIJ/ngVm4sa2/4vTa21F4Bn2L/vmBDqmsdIIH9/Bm8iwSzOaFXxQQwlNp82DB3jswzIol9EEufbYOSU4D1Bn7LVbGuLzQcQ4h1cNkNNab0FBw==
*/