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
    const date_type& operator*() const {return current_;}
    const date_type* operator->() const {return &current_;}
    bool operator<  (const date_type& d) const {return current_ < d;}
    bool operator<= (const date_type& d) const {return current_ <= d;}
    bool operator>  (const date_type& d) const {return current_ > d;}
    bool operator>= (const date_type& d) const {return current_ >= d;}
    bool operator== (const date_type& d) const {return current_ == d;}
    bool operator!= (const date_type& d) const {return current_ != d;}
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