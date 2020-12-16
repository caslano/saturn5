#ifndef DATE_ITERATOR_HPP___
#define DATE_ITERATOR_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <iterator>

namespace boost {
namespace date_time {
  //! An iterator over dates with varying resolution (day, week, month, year, etc)
  enum date_resolutions {day, week, months, year, decade, century, NumDateResolutions};

  //! Base date iterator type
  /*! This class provides the skeleton for the creation of iterators.
   *  New and interesting interators can be created by plugging in a new
   *  function that derives the next value from the current state.
   *  generation of various types of -based information.
   *
   *  <b>Template Parameters</b>
   *
   *  <b>date_type</b>
   *
   *  The date_type is a concrete date_type. The date_type must
   *  define a duration_type and a calendar_type.
   */
  template<class date_type>
  class date_itr_base {
  // works, but benefit unclear at the moment
  //   class date_itr_base : public std::iterator<std::input_iterator_tag,
  //                                             date_type, void, void, void>{
  public:
    typedef typename date_type::duration_type duration_type;
    typedef date_type value_type;
    typedef std::input_iterator_tag iterator_category;

    date_itr_base(date_type d) : current_(d) {}
    virtual ~date_itr_base() {}
    date_itr_base& operator++()
    {
      current_ = current_ + get_offset(current_);
      return *this;
    }
    date_itr_base& operator--()
    {
      current_ = current_ + get_neg_offset(current_);
      return *this;
    }
    virtual duration_type get_offset(const date_type& current) const=0;
    virtual duration_type get_neg_offset(const date_type& current) const=0;
    date_type operator*() {return current_;}
    date_type* operator->() {return &current_;}
    bool operator<  (const date_type& d) {return current_ < d;}
    bool operator<= (const date_type& d) {return current_ <= d;}
    bool operator>  (const date_type& d) {return current_ > d;}
    bool operator>= (const date_type& d) {return current_ >= d;}
    bool operator== (const date_type& d) {return current_ == d;}
    bool operator!= (const date_type& d) {return current_ != d;}
  private:
    date_type current_;
  };

  //! Overrides the base date iterator providing hook for functors
  /*
   *  <b>offset_functor</b>
   *
   *  The offset functor must define a get_offset function that takes the
   *  current point in time and calculates and offset.
   *
   */
  template<class offset_functor, class date_type>
  class date_itr : public date_itr_base<date_type> {
  public:
    typedef typename date_type::duration_type duration_type;
    date_itr(date_type d, int factor=1) :
      date_itr_base<date_type>(d),
      of_(factor)
    {}
  private:
    virtual duration_type get_offset(const date_type& current) const
    {
      return of_.get_offset(current);
    }
    virtual duration_type get_neg_offset(const date_type& current) const
    {
      return of_.get_neg_offset(current);
    }
    offset_functor of_;
  };



} } //namespace date_time


#endif

/* date_iterator.hpp
0zDc3eulXbk3gdY2O1qlhBbsrWxWdS3huvKc5voccOTLnBrK4sXJNuCdXOmzb6nC23rCSxrBu0nDG0Il+MXh37n7aveY3bfIIbpvKiVstSVcwgmni0fl3IDeogHb7Q34XY29X8/Yo/o160PRtLwOqrveFk0LlYAf0JHPZ1l9qJdOgdfWjcw97WYsVv8NWLxoxyKjRuuOo9Dm8l8+rf5v+DO1bFOxHbyoWKff7tCsU1Eqj9w05LiyU4wNox0/fP7wr3rD2K1H7qInxMI/nNfWTW8p8jKv7UHIC4B2YqA3CKAv2YG2IaAE7WmCwdAmZopV9byUC71tzvT5DRl6pndnoMMF0O12oE+vs8/0KW+pmT70fVHdKbq6rzLETD+bIofoyHcokpi1VHmxp7ts+BvMvmNbkHxhjs5RjhynrAdfiHS28Z6ouRT0PbiUN18TXEpp6n+WS4l5HmAp9PNq5pRs1zNnuRiOxBWvZ/LGrDkTKbXsBc5WnqvnyUxF4lx9kwrpnB6d83qZlidyZjwmQ8jJR1rsJc+7mL7WslQbtkPWpwt08Gh1JZ8/wff72TalT3PBvnCtMg2ZPud4IUskXtRNmpDeSho58KU5dHM1pxV/1eYgNtRCho5GiAutg4pmobs09IC6z0vnjRvvOzLE27p7V/OUK9lCFQjvXXmwk/dapiVq3nyPmHvrzbiHKQ6ZiyjheTPhVs6824wb/w7quBnnfSuybbJUoeMzOuYvuJxSKrzWLHwCakKqwu0BMzUbqWbZp8zU5kCG5SfWO3wMUaFUigBWtSZWd4jpII5jj7hsCGLUFAoXmZXcd7fVFeeYCUuRIEtcYCbMMBImmQlnUQLFXW1r/90R7b/W1v67I1rIhxG0C+2zkPw8HNaNyT5As4pMyC+tkUeV+rV8PwAurmMZpr8P+YQPk1kyvkOZfx4LaMB8iExH6kz9AHOPsCjTA707G8n9dTKW0EAd6jWPIbZJIDhplNRTJdH34fK7WGHcareBcdc1oveOfdWI86wxeq8YfhHM1I9XW0P3vZmwixLY+FWgEzL4KcN3ZoaHV0fA/cpMvVGlKjw/NFMDqw8yKzEbo0bvo0/D6mledwVykwkyY7VxrlwuZVh9XxYUe+3PLsP6f/oz9Z83/qf0n0vF/sfVG/4r08SupByc4fytdqeAunDuBZ0/CmcURPqyLA82v19RgLBDmX5lJikPjj4k51XIPPPUneBnXgA/86rmZz59SHBetaaJEb+2OoKPYmnEHKYM1W7NdjBrWigd63BRGu2UmPxXmlgWMZaTSKIWG0BLOwAPOsKhUYGCVaAXC/1uAN9l2UbZtVOyYcwN7Pg5HcL5I8wM3F7Lk0pKyZSEhcM2k8VZmn/AtKL/2TrGk8QuD6GQd9k6p3yNE+io7y8veTBTnisLSfAJaGxcSJV+iErDYWL/JwQHmSu8lz62jYWYF4OQGQz0BYqBpu9xYkwgF3MJwx4iKVzks9jQfhhEP1c+5DVIGR9gnDJeYpz8wVUk4q3vx8ZNc/aT7tX3QI5fmKXPm01iBgI+t4/6ClyGh0PuwLH48QV6IX414gvqq6gggncjOB5fhyXQ16RQGVWY9pLqhEdehRE3RqO5jr2dYkMzKSq8XUVVImoi9hMdVYYo7CT7dNT5iBpBUd/oqFMRdTSet8iHOmLUOlGe93SefpQHAyzWXn+SMCpXi5jM/1lzBY36Jwg9zbcU7pt4jjzwaJRJUO3hNm+bvqXYpWlGze8FzVhot3e7/S/yosJ0U1kcHLzCfgeSZXi/feNFQL/UDn08QY+6xBisniAHK4EtV7itoSluEZpGr0VPbXhK6ZuX9sKRDWeGexzKg651V/Hqgqg=
*/