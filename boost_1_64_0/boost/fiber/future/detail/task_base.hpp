//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_TASK_BASE_H
#define BOOST_FIBERS_DETAIL_TASK_BASE_H

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename R, typename ... Args >
struct task_base : public shared_state< R > {
    typedef intrusive_ptr< task_base >  ptr_type;

    virtual ~task_base() {
    }

    virtual void run( Args && ... args) = 0;

    virtual ptr_type reset() = 0;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_TASK_BASE_H

/* task_base.hpp
KRZLyY2Xp4W4/M9ydC2hCY3UJkyBfTli9N7dntH/sOIH+roE51PntkBWxPguAzwJKp6OOjzTGR7/9coXe17aBRXbmcfDXaw+JOe7VxU0X3VRZpM6t9ctONTIeLy/Qv2THTKPff/nYUojzvRTPPdM8eA1P+5P21bb6L8fgqbr4q5H63LP/A0bJj2cMk9mNW7Ds55kWbPYQRpCbeXeom868VJTlFLeLDp6I5gW8Gbqpljo2+RMwvH5TRxHmo3OyMrCyGKUDltOKLZs3MkjXnsUeLw9MJQCpKNgt9zGrwL6gweoNi/VdszFa9trDeKjHX5Nda8QcDh0rx64hlM7287ous4x4vA105GdRh36UBNeY6Za2q2WdlPpR1rx0q3U0h61tIdKb2vJS/8s52F9STrjP/VCnv+Zjnuw4yP/sA0YmKRThUHNeclXLCbydiex6TMPre42wBqyCa53Cx66T1XQWwH9SC0vQVl6oGlWeIVITanFrq29kWKoLcP5pL64RtqNVkEeBuGmSl1X6VYPPNgIig64jIsgW/YUNHf9yfm++yV0viej8z1ZOt/2K1jA3nytMAzi0JiV14j1hejaYs1h5gAxveYbJNYB2zfEJ1p+yPvNDcY59tMta628VrfDgBRJHjWlhNVZtOuXnZP7vZXi3xdQUmNQUrOD8W87Nl6UifUB6JMcuddFgvJcyfSiDksWd9akmQZ/1IX7iBX7ZO1SOJGbBYKdKRAU6ZshnUbV4HLN4c6snnh5NlGa/2mOsTe2wkb6FliDrZiqtmLJ5Uzf8l/UDURZ2qgOMBA55OuLrUmn0mp6SUs34XUyXbfUTfISLHSJYwHMfAf2hYLvGhpv93/H3YbLg4c+aZDGhiH91800eRzw5rFjL9dV9RY13VxXKtEPJF4dMlR6lIERDc9CMY7JZ7vWKw7FSgtZU0mEV/8VRZiHIpwnRXioDSw65Uahz3uDMsIS6EwCtTLQdBV0GYJeFQVpDaXpvesP3PReCunyjqTNUZyq4d15dlSUjnQSEPuu8X6RKHcNF0MtMhH3+fsGYYeTkktjkkuTRXBHx0zS/7SprUFEataH1AXoyuUsqmIYVOFfL4plwH7G4LPbHkJRryuVs4CIUYuJUR89h4yaqDLqntbAqAts8PoOvnbvRPDZGbhxNb0oFku3l7Mz63oEJfcYYZ3JsE5SsTZCrFusko80WEXTaSmUIga7TH8t4WTRWhAm5tByuU5nEtDXUI5RHoro0VYQaWffC0jSVhNpx55F0nwqadNbAWnJVqEUE6Aok3ptSBKHAg+9RhlPCekLhPShZ03UrTUi3aeo/EKMWsiMlSUGubaWsGQwLFNULEfBy2Bbs3RD8OG04Kbg9QTrNIN9HmD9GUHdYEETswIiTYR2/2HvWMCjLI53l7vk8uISIBAeQoCAQRCCBDjeFwlyaJCAqEFQoygGBY1woVF5aUChB60PrPjWqpVan7XVBK0GUQg+QVtr0er5/uNZ3yCieJ3Z2d1/989/yQXB2tb7Psjd7szs7uxrZnZ2tnGAsmuLTEXLwolNWz1M8OousIZet1HZsxmNj4eLPXv+yfQtaAxNFUbWZ6CEMFD5yVlNfzofZT+IjKb9oFnEL2NTqRajCAVhTP6ws+IQlSccovLkic9ZNJVDIHDxx+CLc41uh1mjfo1lgUE2yWfD2S48D4UsqSibEXB399Md9zrxbWgSL8PY2b/NZ0Kt8kfe9/1h94kdW1o/P5s1SvdXtr8oWsnVqvEkkb7gt3FSfYcOrR67Sy4Ti+QkdfezXhg9Nf3gXBhtdv9tZAvt8cZpz/4RNu15jtoTvVO2JyTbU9TXegF5XdrBuYBsbc9j/lbjT4w=
*/