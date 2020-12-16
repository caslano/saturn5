// -----------------------------------------------------------
//
//   Copyright (c) 2001-2002 Chuck Allison and Jeremy Siek
//        Copyright (c) 2003-2006, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424
#define BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424

#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"

// support for pre 3.0 libstdc++ - thanks Phil Edwards!
#if defined (__STL_CONFIG_H) && !defined (__STL_USE_NEW_IOSTREAMS)
# define BOOST_OLD_IOSTREAMS
#endif

// no-op function to workaround gcc bug c++/8419
//
namespace boost { namespace detail {
    template <typename T> T make_non_const(T t) { return t; }
}}

#if defined(__GNUC__)
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) \
         (boost::detail::make_non_const(expr))
#else
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) (expr)
#endif

//
#if (defined __BORLANDC__ && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)))  \
                             || (defined BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#endif

// if we can't use friends then we simply expose private members
//
#if defined(BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_PRIVATE public
#else
#define BOOST_DYNAMIC_BITSET_PRIVATE private
#endif

// A couple of macros to cope with libraries without locale
// support. The first macro must be used to declare a reference
// to a ctype facet. The second one to widen a char by using
// that ctype object. If facets and locales aren't available
// the first macro is a no-op and the second one just expands
// to its parameter c.
//
#if defined (BOOST_USE_FACET)

#define BOOST_DYNAMIC_BITSET_CTYPE_FACET(ch, name, loc)     \
            const std::ctype<ch> & name =                   \
            BOOST_USE_FACET(std::ctype<ch>, loc)         /**/

#define BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, c)             \
           (fac.widen(c))
#else

#define BOOST_DYNAMIC_BITSET_CTYPE_FACET(ch, name, loc) /**/
#define BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, c)          c

#endif

#endif // include guard

/* config.hpp
Fajr2ieTles1T4rr2s/AH7MPCDOYBXHmwp/jvmS5jkmFVDOte20/K1voQeu5kcmqjklUR3+qowrr2AwLPGax1dEcCtO7rUUc9zUgvT5DOjiExIqFXtXSonyIodPhYjMXsIAZhcbeQkYAyaCYZASJp6RzUPZXFgJvd7OgVEpsuPQbJQ9QTofeFTHcyGMxBtGg2o6AoHgYn4n+8F8stzuGh7a2B94vtraZnt9ya/uH+Gmmx1kr94G9t9O/FV/3uv1Wxc6X3WG/7lWR1utyvyEGJ7+Twzpd1oxD7+8WT/1dKTjBBOAEE4gTTELO/dcz7ZwaE46SrmJ90mi+sJwWEMF1+UpYF3mlhnSQW8nlHPNYDBCPFcnmiFZQnvKE+ekCiVuonBJwNmxngaVvkZgKbSg05FZcIMjL34fTbTxaZWlHWRbSy/Vh1HKTe78JQwHxeS3xC3lhzIe8Dr/QGVu1mdkrDpWyE7zFofQIJWTYEjxWgs+WkKISbLGpGMuXjXPN8+kAsiuFzsQDUXIIAV+aIYxpnT/u5Km8CqYt+vDPq/Iq6w1KuJISOgIrwdhiis1eqlf1082qqq9uFlVNYcbeZwYkSX7O5QvN2S/vZyC75SWiQCwRBdBNX5BbwQJ/BXUUN6/yFr3OxVznPKrzc4MXNx3TF+5zw39qhQ5rBMMaeDP7IpdUPEcwvYBRdy3LF2vZQVhnAP3vBuBJ/PRisa7CQ8wpg6pFpAjjCyKbazqQLxNxpiC994axUwXEEYJKgjrWswKFNdeB9Q5hcsNNCskK+KpzD2/12j/KPbx99XPyO1Y3PnQjWY+/IzQWtPxhcgDfdIC/uWHp/rFYXeYryre90GruvjaJ+3yu8nOReP+EEOC7oIqlmgYcSLFzYjwCv0I/v5Ki4ioSFVc9ykLubBYVP4INMT77w0/74gHPPyr1y7p0OaJ8O+0YRlyGE4EA30uA8wXgi+yAKxBwugU46EPI8wEyoLnfXaThajPVdj+WoFYR1G8fQajn2KEejlDXwZfl6j2HeTchyvrMYvPka6WMt9Cw4RHxUfrI0zD9YmFTv5FqnS9q/Yu91mrYB8eOlgDYfTj2O5/YWOtH2Beq82oHXprFBY2O9246C4gAod/bmxiu40/ceH7wBrXgr1zBC/5GGogT9AHJI1T5TTUP/jMUVQPmDSJy14fbqscK77Te/yuDrr0uRSv6TrkQD4JEq93BOTaZ/B/yfeGHhLxsAEjzmltZJgcB/QKaGrsNuf+73GVq7CKErniIp4aF0POXAkJeHaF8iZB6uztDeyM8w3wVtkDDITUqINcS5FwBea4d8kyEfLf22HgmOIVQ4zMT50lBBR2xirO1yB22EQYTczKMcxzmtHVfe6k1Jf9D1a5/EKu92F7tDwug2kHoYBcgmFdIq8HgbKJLEb1DSmB+IDAXuIF5GMF8oj9ZHvBSm+NUaoQoNc9e6mIstU4rRVOR9snFeqTYK0+13l6fey3SAm/uy2kll9OgusJepNhvoWK/U/PFGxzXCtlAedU1Z10lNzIDYYJmyD2QRldi7OIiGHd5x0oSUYWqbjvvfaYUKTejk2hLM4EMCmhpzb9dLK1v/Y8vrdp+pPKafbAfceVPYaHwoOr5Yj2uwObDl+Euu1lUsPfONDRb3I9D82wcmjfw0Hx/HrD3flToQpCK+FkUzdtSgZBCjfPonLdpb6cnxn/81Yw/0o9Q+XpRXfwvvI/xX87499DwX7+mPvzfvHbP8K979eqGZdrBQLStdcibfzerfPuxnjyC7l5orY+2ZC/hPjUFk9ICu9u/STSwYcA+q89swF5uZyWjnQtuCEU5Yug99UuU4L2hHYflrb5CvEOVlH/7Ouc=
*/