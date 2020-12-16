// Boost.Geometry

// Copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP
#define BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP


#include <boost/config.hpp>

#ifdef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#error "C++14 <shared_mutex> header required."
#endif

#include <boost/geometry/srs/projections/grids.hpp>

#include <mutex>
#include <shared_mutex>


namespace boost { namespace geometry
{
    
namespace srs
{

class shared_grids_std
{

// VS 2015 Update 2
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 190023918)
    typedef std::shared_mutex mutex_type;
// Other C++17
#elif !defined(BOOST_NO_CXX14_HDR_SHARED_MUTEX) && (__cplusplus > 201402L)
    typedef std::shared_mutex mutex_type;
#else
    typedef std::shared_timed_mutex mutex_type;
#endif

public:
    std::size_t size() const
    {
        std::shared_lock<mutex_type> lock(mutex);
        return gridinfo.size();
    }

    bool empty() const
    {
        std::shared_lock<mutex_type> lock(mutex);
        return gridinfo.empty();
    }

    typedef projections::detail::shared_grids_tag tag;

    struct read_locked
    {
        read_locked(shared_grids_std & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        // should be const&
        projections::detail::pj_gridinfo & gridinfo;

    private:
        std::shared_lock<mutex_type> lock;
    };

    struct write_locked
    {
        write_locked(shared_grids_std & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        projections::detail::pj_gridinfo & gridinfo;

    private:
        std::unique_lock<mutex_type> lock;
    };

private:
    projections::detail::pj_gridinfo gridinfo;
    mutable mutex_type mutex;
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP

/* shared_grids_std.hpp
XfB4B5X72tKWVRsk34c9pC7r0CZ6eQ0JDMvTrk8ngz3SSOv8ql4KjllHZLsuZ9euvcA6S1Pt558KpkdTz9nTwMpKU+3nnwlWUZpqP3/XdFU41X7+RrAYaar9/DPAEqWp9vM3H4V1gDTVfv7pYP7SVPv5G45BPRCrNHLfS8w7WAtpqr3+s8Dcpan2+nf9Gvq0NNVe/15gdaSp9vo3g9WUptrrPw2sqTTVXv/iODxzQkyfMkg+JwfmIU31HYA0MCc09ZorHSyUWKZePq9vPEHqz34Na2f0HfBUsMbE6jy6XAnLE6yYRtrAZhuzsL9/o6y1pf3qOt0L+zTYJWKfvPk5GfvDKVirETu56R+xmIfTWnjWVtqmvFsGYB7ATCQt772z0rG9fKeF/XSkXfgmBOdgmWD7pME92gYHsO2eUc5j0q7WyGN7xx0QrkGQ4wUkxZ3D452TYx2Y3Gfd8pw/jHVodnMpxsyMJTOWxlgGY1mMuf4jZ/NizMSYmbFkxtLAppN6eFkoWmDbhRd6N5BwB/a4yXeTLljm0LJPV7shvzNyUVnfSpu99uFLPN4lregow8GkaDiuH0xX4NoasZDKbXEsMFzVig7E/I5loKX/AtfLddKGfRX3B4a7rhX3tCTvHz0bj+m8CesOYnHPDi9GuwP9jxzv+kfhOIYY72phLyFpTpU8z2O9g43WkX47ZYLcD+KRVjwlx0v5sokvtgmYCEcQ+/3S4rZoz5R1jrTY3ZuHoT2HZxJJuPuXxm/BPvZKXWYNVvaX7zu9hnBO0t7cO4nX3UxanQjWS+u25ffKWNZ5dWIsOV7D9+bNOBbk14kTNO/DnGfj8Qrr4NVIMk44VSyGZV1EJxaTtCwYVK4tmrtONCRpmXznVBbWbXmd8CTH+9hPI68dVtKJFHK88Md5/4lWBfYc1JLjHdLOwr7ykU60slp55dpotBGv5Zlr6MQOvbSi35xqiGXmpYPzn7SQ66MbYTiwhcTGXzwVjv3dWwdjnbRJe4q6YzsDG06s0PCAaCxrsN+IlVq+rjfWe10drNGlTRzTvwDmHQyen0frFOwzEMsaJnXNSd7LTypeVN6fVuehVKnpG+U9YZ0YqpP2banQn7C/N4Xvv5A426ff3obHa6E+nv6HR/JZDl8d3JOSNq7ilbUYp58O9n6TtmjHpSdYnq11oh6x8F/85PvvYMNoeX46Xr5P2UYn/knsUvwKPOcY28I3ekha7nVdMRLbSzuoB5L3tMnDJmK9B+pwHlnBbh6ZBOaEpp6HJIP9SSz1s84Pscw6wd5lxJqEJtnmEzD5hb5J7OQlHdZRKlgzYru/WSjfUwRLITZ2wtQDWNZBOnjeVNqyY7EXMc4uOvElsd6BNTdgHoJ1IlYjbeqczYOwvXTTwVpbWt6yv8vnaXvqRDgJt7Dr7dY49vTSwVxKWq1BKX9i/fXWiQ7Ero8s3x7rAewksdUPLlVAC9GJ5eR4b+N6nUfrq4N5nbTl0R3kPSmw8STchk4GzF8SfJ3BFw1+9+sm2I8M4Tpxi1iva81OYLgInRhIyuWH04/OYXlGwx6AJJy2WKEJmHe4GDKHWMLEe3g/TrlZZSJ5KBF7qCPmD8y2PjLYrY9SwTqjqddHrkNkuzbYtWsDmBexWpE/NcF6HyLL02C3dkoGq4imXjul03B2a6cssBg09dopKQa+24SmXjsZYnW4djLYrZ3MYP5o6rVTBlgLNPX6yACD4Gwa7sRwFwwHlp9Y/9lLg3EsB3NHU62rIDHyvGKwW1cZwOqgqddVYWA10dTrqlSwpmjqdVUWmAeaeu3kNUyOWQa7McsIFoqmXjulg2H92a2dssCKSrPsTY7tLC5n82LMBOZKbMA=
*/