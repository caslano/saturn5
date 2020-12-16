#ifndef BOOST_CORE_CHECKED_DELETE_HPP
#define BOOST_CORE_CHECKED_DELETE_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>

//
//  boost/checked_delete.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) 2003 Daniel Frey
//  Copyright (c) 2003 Howard Hinnant
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/checked_delete.html for documentation.
//

namespace boost
{

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x) BOOST_NOEXCEPT
{
    // intentionally complex - simplification causes regressions
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete x;
}

template<class T> inline void checked_array_delete(T * x) BOOST_NOEXCEPT
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        // boost:: disables ADL
        boost::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        boost::checked_array_delete(x);
    }
};

} // namespace boost

#endif  // #ifndef BOOST_CORE_CHECKED_DELETE_HPP

/* checked_delete.hpp
mHqzkqtWCnTG9CnyN7/OdT3jIMRbmowenw7oMAYN67efCfBoTnr67RHsEXWrzpuTn/Vo9LJm8Z/z8HoZa93ef8/68x7efwv7i4yHsTnv/DLjktZ2+qpH59vpBg/Pdgrbx+30DY/Gt9ONHt63k9/et9O3Hby1U1jjSmOXia+0B2Q8Vbh0Pf8m8P818tojQPuMTvLaJMGevBY5qzs3uuZ+T/oxMDg4tGPczfO/7+DcXP4HggPQ1B78XDnJMOg3xwalny4shHUD5HeCx5gT/EdLNBx5CFyF8ziBc2xiuPgo53eAm/HmPA5wM46c9wEu40/ff9j+Syf0uN0K+PH3RU2pC+06HLf4fuRVzritjOQ7Zh7jj7OamAugO7EVnS4KTjXzKEg2nLdeYTOiRaXc52rOP6jv0Bn14bJzB/bnGV61Jhv/kuG9XSG9Z/tfOvDeyG+0QLrnO4AEdYLfgA/gAf/fMhz8PXrWn+mN/t30W0iAp8cX2hiuvwOXhSjfVrC5XSsV/CgPDhu7dQ3AlHjfpwHXLn3Q9WnAxaXlrTz0YQT+eWQXcB36p6odhXHlquia/GcZu8HtIyNDg+G3h3d5eNXPSGwx9aogthiM+9sZCuqvOzwWCj9X7FF4P/b8dYnA/dgj9Bx7GB7GHg0PY4+Gh7FH4GrAZfwWoNDxycNVrQM4gd0NsOdhTEsEuwdg1wL2wAUWdj/AVE36g4quw7EvTuHZs/Cdcz82cU1Vt8FZFgyEDHBGyqtYA2N0biE6Fmc1HdqHvqAyzBQJHexYa7754u5mgkhW2JtrlGdLOF7I7uMdIXb7bGoPypMB55toqlnW5hhpk78n2jhjLvLkcNX4lIXDqfQa0SM8iofZsVkusEsUjGz0IMB1e6XRbKOZq+4t1aeVQ4SytSOG8KDGIXDtiOSHAteOSHFH4FL7WOHbOF0s2MTt/WZA5luTxVgd5NvsW77PoI3vWJjnAY3rVIsiPjWJ/oTrCqBqvGkMwSsdQIrPgGmDH0V2Akxlmj5MGc5r637LVU7p9IDweACmBqPt31cxNi3PlMJYfWs0B1x7PNkD7ThOrwNOJOUm1T+8eKno/Xh5icBNXGRbAK4tFNKH8VLDw3gpcI6XzF9Zu8P4NlONfUfz22P8O9GnHQ/I/WAz8J3qUMZsaTYi4/fRMTmDxgTt1IFLZA3E53RA8nipt4OE3l9zYWeLU5f6/PMX4Dh34jaGF9sacD2UITzIUc5EfwAPfufp6aqfOzfltg1tk2IO5oQnm3OgsuYfzXUAF5dw9YeVhE0H9VKMl6rrhnPoP3PWsxOpZ/v16mCOCDycIxrOc4TpwzkicJ4jzEfmgl+vTg3V5lt1Yo80YQrtca9Fc52X6Fb2nWr/zNWP4r5PKprAdgJn2zE8tJGGh3FE4H4cEXrOu6aORyzEvN8M/G6B7RHYyQrW5tvhEzPYJPTLX9H6/8KoPatqnmwd2DLUP5HbVK7kuR5yFnDCUN8azyeN9I413Y+ogyZ9NHLdGrOPa9h2yKZna1jFnbtZTZI5jHnLa+KBjN/qfsPvHOKn5rn/Vu5ziN/OWtF5j+ssr20v6f584NQ5BFQ3sBcAhlt1dcD07z3LWDwKuD0yPi8RWI+CHcr4JLHxeVB0fC40fUuC8bnI9C1xx4dyzldZmuhYXEz8h71a/RtsW9/uvnxrW98v1qw368ubSJaMk6F/s4wFht3A3ipjsbq/vXvlYuPZnJ0Fno0fFbXxpZCD95SzZmv7SIdb0pwAdiebvk3ot21M72nPFtN9gm3zLbQpe359E2DNtM+H1Jck7Mu6NvqS9K9dp/34MpVvwWe/DxrkWu3dja7gf+qia7A/O5Vk2z5ersZ3RDU=
*/