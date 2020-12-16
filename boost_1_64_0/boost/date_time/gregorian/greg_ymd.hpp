#ifndef DATE_TIME_GREG_YMD_HPP__
#define DATE_TIME_GREG_YMD_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/year_month_day.hpp"
#include "boost/date_time/special_defs.hpp"
#include "boost/date_time/gregorian/greg_day.hpp"
#include "boost/date_time/gregorian/greg_year.hpp"
#include "boost/date_time/gregorian/greg_month.hpp"

namespace boost {
namespace gregorian {
  
  typedef date_time::year_month_day_base<greg_year, 
                                         greg_month, 
                                         greg_day> greg_year_month_day;
  
  
  
} } //namespace gregorian




#endif
  

/* greg_ymd.hpp
IshaqVN6auUib60cBiuvV6ZDpaw41rsByCRvyDncMr9zuFjIxwB2h98BbCCKeJc9ny9FGFz0uU/gQWuBwFM11hNwYoCioAGrZeYSEVIKoHkUZNakGwBCDOVZk0cD8D7iCUyd36EwCzEWU0uD/KgUCGlpEIaugBbripBlZK5bQZEq1IW8THzLZbRymdZKoDMnldKjASDWUyuHwSomDUAL7cUq5rcBjCrreJYGoJG8T376cGJEoz6dGNXcAMAe4ThnE1z0Cdpq0do4AxzWk6gCKAoKsEbmLREmpQCKhyAsB2mlcghZaB3CpQ3A+wJNTqnyOxRmISZiamniIZ0CIS0NwmWPHQModSsoXIVcyAxnNQae5wYGrZVAZ04qpUcDQKynVg6DVUIagBbai1ViWA1g1ytwo8tp9aVhDyQvrU75aSM1fttIjNsI2MvhUITBRZ85joliJxmwQ3ayKoBQ0AB1HrmCSSmA4gEEnlTpNoIQQ3lS5dFGvM9JA1PndyjMQkzE1NIkQzoFQloahKFOoMXqJGQZmetWULgKuZAZPkoqoVT9OFZfQ8UNRCfzdIUj3ts/7ZdVShqIltiLFeL9usLLdhKr/HYSjX5GSfGoz1FSghsA2Ovjv+Cij6EnRGszDIiynsQVQFFQgLwMjiuYlAIoHoKwHKSVyiFkoXUIlzYA71tZOaXK71CYhZiIqaXJhHQKhLQ0CJc9uw+g1K2gcBVyITN8lFSC5w4fpZXAZTYqmWcDQLy3VvplBfGYlZLYe93VdwMoO01Y7Xea0OxnnpyM+pwnp7gBgL0++tscKjnALlrbJLMB1pOkAigKCtAjg+MKJqUBmkeMVQ6krcohxFAemHs0AO+z6sDU+R0CU+5G1fxQciGdAiEtDcJQF9BidRGyjMx1KyhchVzIDGdNXu2plauVVgKX2ahkng0A8d5a6ZdVszQALbE3q2bfDSBSdnXSr6MoG/KzazXq02feyA0A7BFu4ZyCi74GoFG0toUBcdaTjAIoCgrQK4PjCialAIqHICwHaaVyCFloHcKlDcD7pl1OqfI7FGYhJmJqaVpCOgVCWhqEy96dAKDUraBwFXIhM3yUVILnHjillcBlNiqZZwNAvLdW+mWVlQagJfZmlfXdAEZ77wYoo/wgkrQe7qR4uOVCIgNUFSxXVwKqb9RMco1yLP/QRBiXkyOB8nCX3o0pHm6gaQ+3cBIC3pcoCbQOYY9rMpV0UXVNZjfXNSJLK4Dj9eJEN2sJp+Qo71u5fB4TKdt1d/vtuhf5sVzNfi1XS5TzJefXWEXBRd9W0SLmpp0BKa6kZgUQChrAJGBNK5iUAigegrAcpFV9I2ShdQhry1X+hg1OqfI7FGYhJmJqadpDOgVCWhqEoSygxcoiZBmZ61ZQpAp1IedFuTzWzDheq2We1VKlzJdRy7ynWg6DF0RkXkpqb++4z/W5stO3vN/p2wo/o9es39Fre5TLUE5KcT7BBeGC1Kbo7TIGNLKmZBVAUVCAAld8UwWT0gDNo4mVrlE3AYQYyot6Hk2goBRb6HFKld+hMAsxEVNLsyykUyCkpUG47KUvAErdCopUoS7kHlHkMmqZ12oJdOYkKfHtpZaI91LLYfCCiMxLSe3tHvTZBMq68Hr8uvBW+fFgLPLrwVgW5TKUc1IhnhWLN1tqU/T2UgY0s6YsUgChoAFMAh1OBZNSAMVDEJaDtFI6hCy0DmHdBMq/isQpVX6HwizEWEwtDfKjUiCkpUEYygJarCxClpG5bgVFqlAXcq8ochm17NFqCXTmJCnx7aWWiPdSy2HwgojMS0ntyWuVzyYQHXqXRtlW0uu3lazx01Gs8NtRXBrlYpbTVlwU4ILwVqk=
*/