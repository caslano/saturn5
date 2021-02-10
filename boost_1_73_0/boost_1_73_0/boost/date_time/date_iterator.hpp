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
uE3/e2cXck6ukZKHw7KB2Z1vZr/5ZuytBnD8zS7HM3Dw6pXZb4YX3h+dYin+orl+2SHLHqD7oOMK728I5cPB6yE7gjd5PcDQemV9rAvznGVvCLcySZof3zivMvOIls6z9x+LZi/ZXaVhOD6C0fv3P8EJvDsd/eCa33MXPpGaUQ6JpvWayjsXLgpr+a0i9/eeoh9coBoI957BphVToESpd0RSwGfOclorWgBRUFCVS7bGF1aDriiUjFMYR/EynP3uwq5iedXj7EULqhItL6AiWwqS5pRtO5iGSA2iRATEL5jSiNlqJmoPw1PQVG5UD2OSIFwJIFvCOFljOKKh0rpRP/t+3kqOJ/ELkSs/fyTEq/Tmq1MtMZsN2YNoNGgBraIumP0ubETBSnNHitDYtGvOVOUe0sKAdeELCYpy3sOhK6OqOwKFpGfLNTuhweyZNjclamWi7SqxebYRae2BylbWGA5pwX2FQOJdaOuCSrvfEvEYpWfZUv5KyQ65FyBqzAoGQQJhMoA1UUy5cBumV9EihdtgPg9m6RKiSwhmyx7vOpx9Qm0wjCqB3jeSKsxCAts0nNHiWfBv2u+Ol17BeDGfRnGaXaZxtkgm2SRObuAMBqNz+KOtrcIHMOBsbYoP597ZuXeKBvOWUaL2maLa
*/