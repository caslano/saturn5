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
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
*/