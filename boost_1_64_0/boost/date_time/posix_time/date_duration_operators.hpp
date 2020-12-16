#ifndef DATE_DURATION_OPERATORS_HPP___
#define DATE_DURATION_OPERATORS_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or 
 * http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/greg_duration_types.hpp"
#include "boost/date_time/posix_time/ptime.hpp"

namespace boost {
namespace posix_time {
  
  /*!@file date_duration_operators.hpp Operators for ptime and 
   * optional gregorian types. Operators use snap-to-end-of-month behavior. 
   * Further details on this behavior can be found in reference for 
   * date_time/date_duration_types.hpp and documentation for 
   * month and year iterators.
   */
 

  /*! Adds a months object and a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+(const ptime& t, const boost::gregorian::months& m)
  {
    return t + m.get_offset(t.date());
  }
  
  /*! Adds a months object to a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+=(ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += m.get_offset(t.date());
  }

  /*! Subtracts a months object and a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-(const ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + m.get_neg_offset(t.date());
  }
  
  /*! Subtracts a months object from a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-=(ptime& t, const boost::gregorian::months& m)
  {
    return t += m.get_neg_offset(t.date());
  }

  // ptime & years
  
  /*! Adds a years object and a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+(const ptime& t, const boost::gregorian::years& y)
  {
    return t + y.get_offset(t.date());
  }

  /*! Adds a years object to a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+=(ptime& t, const boost::gregorian::years& y)
  {
    return t += y.get_offset(t.date());
  }

  /*! Subtracts a years object and a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-(const ptime& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + y.get_neg_offset(t.date());
  }

  /*! Subtracts a years object from a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-=(ptime& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += y.get_neg_offset(t.date());
  }

}} // namespaces

#endif // DATE_DURATION_OPERATORS_HPP___

/* date_duration_operators.hpp
RWxRxQMeWOzIEzg4NF+Gk30lBi/Cl+JzJ0EZJDluSI4TyXFJ8mteTKvDKTM1Fwc1rFWkl+BY+3kNMAEGxJpkRd9wZQg85a/jLHV4F9pIUVdlRMzUJHyUHw8mo1UXI8kE6SzJ6V7mT+xi5OIhulErZ+AbVoA7NBBJghqVQNbWeu0cAzBlx7tzjKNLXXii4VjScCxJwJOSY9/xSI6dQg1kjjU5cCzCHDP3fxPHxiu3SdiNVN1Ts7xjI7Qgx5djbF3RXKQrmrWRZMdmPtuQnWOD0FIEAp2yoeq2drUWaVcrlG+13VJE+gzRxQn4bPnmcTFg65ca9s8z7J9H7J+XY783G8FWAZXtTCUJBEoBWcAvNNoyXwL7KkuMRYdv79fQyrtA4mSHZf1A4f/b7Ue7/xOzaNN5ehbVmwRvdkxD1wvagLpp6zj6nN9/FU2MxdcbcccFhTbAbTsXUTV0Pa0RnK8QPKwXEVNpdiAycEbcpA/+RreaGfEGMyM+nMQZsSxemsHQPn8h0vPPza1cWIG4yfLi4OTrnGAqpZeQeqkubbnijG/7Aid8nqHAZ0fVIVBhZLLx4vunJRg6JcyqCaTGk2/PCC6uvi+6Ais7XD0AhYqmEklx0kc0YkjLj+frIyiIbk36eXMSGeZ0GWAXrLJw3UV2DApf2nk16ctbQHTiGdg2UJ/Cxt+CwD7Zn2RfgALG22jxvigeN0UDgBWfMyM8dLKvt/4FVOzs+IueX2yJKNtDPCG1pG9N6SXFKLqJ4EN4c9TjDFcctWwhCWYcFGjym57nCzXd0pFyImRpglaU481ykGZrcwg+EGlMhi8lzBZqoJ3IpN6NwBVyMvBCaDiI1EWg6sDW9B5OAYrfzaPRxcZvCBe8TSQptF7GBOasOYj2QKXsD67VQFC1snQ4gsrWxGCMCYgbp5Syq3Jcz0/R8PVQuEKpD1Z0D1fnAIfDOUAfm9lnqUXI0gpEnvmeqsVpbSF4gtW6jm8j3I9Q2YBbxXT1p8dKPzmfuU6SRlNd3miqs1LnQIIhgk5riLMhIVJh9BIULqyWNdM2qo0FxlqBYj9OVz3UfWA/Kw3aPdk1sJ4a7EaixJ/otc0fEbs62BtP0I8LopWw81HKZ3yHTU+zWlfiC3/bvMkrulO29eR8jVPHJgeh00kLbnmsM0gJIsBNHW+5gmqvvwz2+mdibzHXAQVKj4YuD9409GxDx2aKfLNjC0pgPF86mbzPxFkZPaqmzNjFDZztJ9ra8mEz30ctcc1DFJn9fnyUzOYd5j/C2/spmCZQNvF0ve7Tby9Nh0AVJtOrMoFjj9SapMfC2ynYtFpgPGnp+T/NaqdfXLa9f3eaaP/0O+aLRU0qQDvMw+i9Un+OE2FmGYd5kAbk48SQhRHgVQ85zULH3OpZ8erUJF7lGxi/Qg8fXfdHeVGNRyuB66f4AAGUPdWQAk+QAjkSfgC0ReUdqkTmOoespcNgcZX9JKajfxIrWvBpxew6a0lS3kLJH3wtJIo1P5sK4b9ZKvtyAOzP7ptLWaRR+bNfqu8uLhmH5hdztUf1nG3EQRJ1novHN3Qdr9ePZ7w2Tv0ZeY/607/PpFenWIpgGK4g3mBY6c0MbGRUnRN0nQN0nQ6s86ff5dXpSR8Nf3gpEgcgScV/xe96ENGT84Owg7auHt5AQILXJ9IoU5MqlS54r8v3JCu/oha9wBQpfZVKP7xyeePfy624r6cf9SkVA4+2N4JXF95eLGYEW8xGGQVSUCuLs9CBImLOsXkLJ91KJqlkfTeEhFgEn8AZ/TmrXTmjYQNduaCsGm0TkjJRTVBHxYxDk6BwlKwBxLjXSFINTek5gsiAnchASUQGChEZcCIyUIjIQGE=
*/