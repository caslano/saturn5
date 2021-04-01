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
zOZP8rJTLuL6+ryYLc+z7//zCht+fSNHYHRt7yvxWCQiFBuIfTv8r6QzIy3zuKWyhLED/s5/lmV2ZoltUZq3LUWMwSI97rBRumVm0MlypB8X/ebuiWfWdbSlbl2Qh6AADAaJOyBNmbNisLhVUCpk9U9Rl0v0rfyXfZSgCNTLtPgL5NaSaLhK1/4/khjrBkEptN8ia+PhbvWHdT0KOaqzCKw5NTqrfIEiiMLJuotRptzRSV+SxjJUvzR8ltOQH8RLUfSrS6FPlJA1vJBpAZ9FLS+viIdNDF7kRf0JYIdycdrTf2XKUsHWXe5z2xf9Mc/Bqmr2NGmzWGmxkRo2nhTL4r9jomid6wy+qiMFh52h3yLlXbCHLUkdwMX5E3lOKCyiSHIuPEaBGsJ46UPii9bb+CCwnA+921aOBxWVfQkgsP2TxoHdNlbOZrTfF8D7fi9+a6PQJHFoEB0dQ7D+IWubrRuiRjRrFLi2c1NQT68saYLGz9ePtJscr8rLFMfLZppAr743S5Qr3S3mZORGZ7IED0EZ56TE7J4gxTXmOGWI+/XnB9w6o4682ehDdg==
*/