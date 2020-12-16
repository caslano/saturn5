#ifndef GREG_DAY_OF_YEAR_HPP___
#define GREG_DAY_OF_YEAR_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //! Exception type for day of year (1..366)
  struct BOOST_SYMBOL_VISIBLE bad_day_of_year : public std::out_of_range
  {
    bad_day_of_year() : 
      std::out_of_range(std::string("Day of year value is out of range 1..366")) 
    {}
  };

  //! A day of the year range (1..366)
  typedef CV::simple_exception_policy<unsigned short,1,366,bad_day_of_year> greg_day_of_year_policies;

  //! Define a range representation type for the day of the year 1..366
  typedef CV::constrained_value<greg_day_of_year_policies> greg_day_of_year_rep;


} } //namespace gregorian



#endif

/* greg_day_of_year.hpp
jRR1U/YG8VANjk72pk8DdZiAKtxCybllE04hD7oTbpAyVeZEsFtu24UqD7elyhKoPU6qzIoJ//jAP/ShTKL7eWz36l7dq3t1r+7VvbrX//f6w/mPPpz/uIzOf+hzH4l0m/MffYYTG70GI+P5j4TzJZ/J2ziDkclbahzkaF6+SEYr8vzHOJuxQEtWPWT1B0WMFfL8R4rMU1pKrll1LDwyy2D/rM2j7H3+Y9oe7/MfsNGvm3UbbV94cw9ixvMfOu5eef4jwWNq5CmQy31LmMOnrJkwESNIQYw83wTa8WT7nNuWvnCY8ovDVML5ms/gLTPOYGTyliUcovnffQyQkCdAGG7Q2u4phxmHgquzAvXRCJlnhZRdEwoyGofsX2vzKHufAMn0eJ8Aadk0dKdkD1IChxwI9wBl4wkQHXevPAGS4DE1oAlSQbNTBEJZLeFy/CNB20ieHxJG3UCWESCLtgNZxs9kl/M72RUIZGje9s4oScgDIIwlaG33lKCcQ8HVWYH6aITMC0LKrinFOQ0y9q+1eZS9D4DkerwPgMBGv3DWbbT58IJ6gLLxAIiOu1ceAEnQGBpBlhEgI1s4FNVcQJbpDGTZPvfPHmJuKMz2GoyMk5MfFFp+UVgkFKJ58UkKWhGnPxhs0NruKYOWQ8HVWYH6aITMi0LKrgkDlkYh+9faPMrepz+sHu/TH5ZAYVG2gawJFHIg3AOUjac/dNy98vRHgsfUDCfI5ekPAqKsmTA9rCGnh7WvF9Km2cnvXJfz80At+X2glgllaF581oJWxPEPBhO0tnvKUMmh4OqsQH00QuZlIWXXlOOSRhn719o8yt7HP0o93sc/YKNfSOs22nzeQz1A2Xj8Q8fdK49/JHhMzSiDXB7/IJTJmi4oy/lEmeuyreB32VZIOCY9E8r6xxmMTN4qhDI0/7sPmxCPPv/BYILWdk8Z6ncouDorUB+NkHlFSNk15bhfo4z9a20eZe/zH/093uc/+gll3CnZg4JAGQfCPUDZeP5Dx90rz38keEzNKINcnv8glMmaLigr+ERZrPVI9T4AYnoM+gWi9YdXdAZvA+MMRiZv4wmIaF5+X4VWxg6AMN6gtd1TEgccCq7OCtRHI2Q+XkjZNcFgQAOR/WttHmXvAyADPd4HQGCjXyzrNtp8Z0Y9QNl4AETH3SsPgCT0mJpPcvyex1oERFnTyGMtvzzW9Zla9PtMLfqZ7Qb9znbDBDI0/7sP7BCQPgDCWILWdk8JGnQouDorUB+NkPmwkLJrSvGgBhn719o8yt4HQAZ7vA+ADBLIuFOyB0UBMg6Ee4Cy8QCIjrtXHgBJ6DE1n+SQICNz+BQ1jSAr+gWZKz0o+aUHJT8LtzP8LtwuIJChefkNH1oZOwDCWILWdk8JOsOh4OqsQH00QuYXCCm7phSfoUHG/rU2j7L3AZAzerwPgJzBIJOd6mnzLSP1AGXjARAdd688AJLQY2o+ySFBRubwKWoaQVbyC7K4G8jKqmWnkXk974eDXuGXg95AIEPzv/uIEwHpAyCMJWht95SgKxwKrs4K1EcjZH6DkLJrSvEVGmTsX2vzKHsfALmix/sAyBUEMu6U7EFZgIwD4R6gbDwAouPulQdAEnpMzSc5JMjIHD5FTSPIyh2BrP22b8INh/29BiPjERA/OKz6xWGNcIjm5behaGXsCAjDDVrbPeWw6lBwdVagPhoh85qQsmtCQVXjkP1rbR5l7yMg1R7vIyBVgcOabqPNN7LUA5SNR0B03L3yCEiCx9SEpn6xI0e2cCiqJVzOf/jekXOd7Cp+J7uKnydq3e8TdWQckTGELj8IRkT6BAhjqcJHyClBdYeCq7MC9dEImY8IKbumFNc=
*/