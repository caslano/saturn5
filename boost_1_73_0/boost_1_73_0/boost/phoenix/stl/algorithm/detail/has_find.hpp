///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_find.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_FIND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_FIND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"
#include "./is_unordered_set_or_map.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_find
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
          , boost::mpl::or_<
                is_std_unordered_map<T>
              , is_std_unordered_multimap<T>
              , is_std_unordered_set<T>
              , is_std_unordered_multiset<T>
            >
        >
    {
    };
}

#endif

/* has_find.hpp
8Z03494NF0io++oNp6bvK6gbTKuiO07jEPseIY0BefEAP1RD0Z+S3C/F9YW5ajatEZ1XCQ93YH1THwyPXhMZ9sChH5163enXCkUC+QS+lR4O7AxdTnbImEi1cKN7jDtugzhPqUTRidF+1VQlROy4BWsKI7jTlgCUyaYs6lAhmDGYMl0DSYWN4WDFfJYvVPyzTGJIXbFAUyw2GiZa+2BMp5SsPqL+jk3mwTLsLSUeoSDSjkFUm99QyYm+t9mLn3/+2TJAVjlJCrauAqmC0BJEUgD3SbAxVDSSI+VmopoI1TkMAEeGzug/ArvfTogUURELXjVZG5MI962LL+pZwtJ7G6UP5BITWmUuW7o0A1+wD1AVr2HoV+wYCzDKoWJAviDv81cecIzNZbSJgSj4HHHjRtUJdYta0nksMyzk5ZzotGpa17AtZ0WpVDULLKReIqNZaQ1U0Vc/3nn1r21V89UIfQf+8pdCTdHQW+JEakh0xefN+i+tti6QoFQv3XtRV4cn/Zq0RI8E9ILoEjjY7hu8yPB4VxzsySCcadOKCMh6EPFgKi5TRBXuRyYZJMLwWbxkTWpaC+hSkCiC8oeXji1Yrvg5+BNPhyXFTgfUNcvuB5DmU1zf6bjjMWhwR0xlnR//7Bvp1u2j2DIeZYZi
*/