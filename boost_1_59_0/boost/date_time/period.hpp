#ifndef DATE_TIME_PERIOD_HPP___
#define DATE_TIME_PERIOD_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */

/*! \file period.hpp
  This file contain the implementation of the period abstraction. This is
  basically the same idea as a range.  Although this class is intended for
  use in the time library, it is pretty close to general enough for other
  numeric uses.

*/

#include <boost/operators.hpp>
#include <boost/date_time/compiler_config.hpp>


namespace boost {
namespace date_time {
  //!Provides generalized period type useful in date-time systems
  /*!This template uses a class to represent a time point within the period
    and another class to represent a duration.  As a result, this class is
    not appropriate for use when the number and duration representation 
    are the same (eg: in the regular number domain).
    
    A period can be specified by providing either the begining point and 
    a duration or the begining point and the end point( end is NOT part 
    of the period but 1 unit past it. A period will be "invalid" if either
    end_point <= begin_point or the given duration is <= 0. Any valid period 
    will return false for is_null().
    
    Zero length periods are also considered invalid. Zero length periods are
    periods where the begining and end points are the same, or, the given 
    duration is zero. For a zero length period, the last point will be one 
    unit less than the begining point.

    In the case that the begin and last are the same, the period has a 
    length of one unit.
    
    The best way to handle periods is usually to provide a begining point and
    a duration.  So, day1 + 7 days is a week period which includes all of the
    first day and 6 more days (eg: Sun to Sat).

   */
  template<class point_rep, class duration_rep>
  class BOOST_SYMBOL_VISIBLE period : private
      boost::less_than_comparable<period<point_rep, duration_rep> 
    , boost::equality_comparable< period<point_rep, duration_rep> 
    > >
  {
  public:
    typedef point_rep point_type;
    typedef duration_rep duration_type;

    BOOST_CXX14_CONSTEXPR period(point_rep first_point, point_rep end_point);
    BOOST_CXX14_CONSTEXPR period(point_rep first_point, duration_rep len);
    BOOST_CXX14_CONSTEXPR point_rep begin() const;
    BOOST_CXX14_CONSTEXPR point_rep end() const;
    BOOST_CXX14_CONSTEXPR point_rep last() const;
    BOOST_CXX14_CONSTEXPR duration_rep length() const;
    BOOST_CXX14_CONSTEXPR bool is_null() const;
    BOOST_CXX14_CONSTEXPR bool operator==(const period& rhs) const;
    BOOST_CXX14_CONSTEXPR bool operator<(const period& rhs) const;
    BOOST_CXX14_CONSTEXPR void shift(const duration_rep& d);
    BOOST_CXX14_CONSTEXPR void expand(const duration_rep& d);
    BOOST_CXX14_CONSTEXPR bool contains(const point_rep& point) const;
    BOOST_CXX14_CONSTEXPR bool contains(const period& other) const;
    BOOST_CXX14_CONSTEXPR bool intersects(const period& other) const;
    BOOST_CXX14_CONSTEXPR bool is_adjacent(const period& other) const;
    BOOST_CXX14_CONSTEXPR bool is_before(const point_rep& point) const;
    BOOST_CXX14_CONSTEXPR bool is_after(const point_rep& point) const;
    BOOST_CXX14_CONSTEXPR period intersection(const period& other) const;
    BOOST_CXX14_CONSTEXPR period merge(const period& other) const;
    BOOST_CXX14_CONSTEXPR period span(const period& other) const;
  private:
    point_rep begin_;
    point_rep last_;
  };

  //! create a period from begin to last eg: [begin,end)
  /*! If end <= begin then the period will be invalid
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  period<point_rep,duration_rep>::period(point_rep first_point, 
                                         point_rep end_point) : 
    begin_(first_point), 
    last_(end_point - duration_rep::unit())
  {}

  //! create a period as [begin, begin+len)
  /*! If len is <= 0 then the period will be invalid
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  period<point_rep,duration_rep>::period(point_rep first_point, duration_rep len) :
    begin_(first_point), 
    last_(first_point + len-duration_rep::unit())
  { }


  //! Return the first element in the period
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  point_rep period<point_rep,duration_rep>::begin() const 
  {
    return begin_;
  }

  //! Return one past the last element 
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  point_rep period<point_rep,duration_rep>::end() const 
  {
    return last_ + duration_rep::unit();
  }

  //! Return the last item in the period
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  point_rep period<point_rep,duration_rep>::last() const 
  {
    return last_;
  }

  //! True if period is ill formed (length is zero or less)
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::is_null() const 
  {
    return end() <= begin_;
  }

  //! Return the length of the period
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  duration_rep period<point_rep,duration_rep>::length() const
  {
    if(last_ < begin_){ // invalid period
      return last_+duration_rep::unit() - begin_;
    }
    else{
      return end() - begin_; // normal case
    }
  }

  //! Equality operator
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::operator==(const period& rhs) const 
  {
    return  ((begin_ == rhs.begin_) && 
             (last_ == rhs.last_));
  }

  //! Strict as defined by rhs.last <= lhs.last
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::operator<(const period& rhs) const 
  {
    return (last_ < rhs.begin_);
  } 


  //! Shift the start and end by the specified amount
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  void period<point_rep,duration_rep>::shift(const duration_rep& d)
  {
    begin_ = begin_ + d;
    last_  = last_  + d;
  }

  /** Expands the size of the period by the duration on both ends.
   *
   *So before expand 
   *@code
   *
   *         [-------]
   * ^   ^   ^   ^   ^   ^  ^
   * 1   2   3   4   5   6  7
   * 
   *@endcode
   * After expand(2)
   *@code
   *
   * [----------------------]
   * ^   ^   ^   ^   ^   ^  ^
   * 1   2   3   4   5   6  7
   * 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  void period<point_rep,duration_rep>::expand(const duration_rep& d)
  {
    begin_ = begin_ - d;
    last_  = last_  + d;
  }

  //! True if the point is inside the period, zero length periods contain no points
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::contains(const point_rep& point) const 
  {
    return ((point >= begin_) &&
            (point <= last_));
  }


  //! True if this period fully contains (or equals) the other period
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::contains(const period<point_rep,duration_rep>& other) const
  {
    return ((begin_ <= other.begin_) && (last_ >= other.last_));
  }


  //! True if periods are next to each other without a gap.
  /* In the example below, p1 and p2 are adjacent, but p3 is not adjacent
   * with either of p1 or p2.
   *@code
   *   [-p1-)
   *        [-p2-)
   *          [-p3-) 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::is_adjacent(const period<point_rep,duration_rep>& other) const
  {
    return (other.begin() == end() ||
            begin_ == other.end());
  }


  //! True if all of the period is prior or t < start
  /* In the example below only point 1 would evaluate to true.
   *@code
   *     [---------])
   * ^   ^    ^     ^   ^
   * 1   2    3     4   5
   * 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::is_after(const point_rep& t) const
  { 
    if (is_null()) 
    {
      return false; //null period isn't after
    }
    
    return t < begin_;
  }

  //! True if all of the period is prior to the passed point or end <= t
  /* In the example below points 4 and 5 return true.
   *@code
   *     [---------])
   * ^   ^    ^     ^   ^
   * 1   2    3     4   5
   * 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::is_before(const point_rep& t) const
  { 
    if (is_null()) 
    {
      return false;  //null period isn't before anything
    }
    
    return last_ < t;
  }


  //! True if the periods overlap in any way
  /* In the example below p1 intersects with p2, p4, and p6.
   *@code
   *       [---p1---)
   *             [---p2---)
   *                [---p3---) 
   *  [---p4---) 
   * [-p5-) 
   *         [-p6-) 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  bool period<point_rep,duration_rep>::intersects(const period<point_rep,duration_rep>& other) const
  { 
    return ( contains(other.begin_) ||
             other.contains(begin_) ||
             ((other.begin_ < begin_) && (other.last_ >= begin_)));
  }

  //! Returns the period of intersection or invalid range no intersection
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::intersection(const period<point_rep,duration_rep>& other) const 
  {
    if (begin_ > other.begin_) {
      if (last_ <= other.last_) { //case2
        return *this;  
      }
      //case 1
      return period<point_rep,duration_rep>(begin_, other.end());
    }
    else {
      if (last_ <= other.last_) { //case3
        return period<point_rep,duration_rep>(other.begin_, this->end());
      }
      //case4
      return other;
    }
    //unreachable
  }

  //! Returns the union of intersecting periods -- or null period
  /*! 
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::merge(const period<point_rep,duration_rep>& other) const 
  {
    if (this->intersects(other)) {      
      if (begin_ < other.begin_) {
        return period<point_rep,duration_rep>(begin_, last_ > other.last_ ? this->end() : other.end());
      }
      
      return period<point_rep,duration_rep>(other.begin_, last_ > other.last_ ? this->end() : other.end());
      
    }
    return period<point_rep,duration_rep>(begin_,begin_); // no intersect return null
  }

  //! Combine two periods with earliest start and latest end.
  /*! Combines two periods and any gap between them such that 
   *  start = min(p1.start, p2.start)
   *  end   = max(p1.end  , p2.end)
   *@code
   *        [---p1---)
   *                       [---p2---)
   * result:
   *        [-----------p3----------) 
   *@endcode
   */
  template<class point_rep, class duration_rep>
  inline BOOST_CXX14_CONSTEXPR
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::span(const period<point_rep,duration_rep>& other) const 
  {
    point_rep start((begin_ < other.begin_) ? begin() : other.begin());
    point_rep newend((last_  < other.last_)  ? other.end() : this->end());
    return period<point_rep,duration_rep>(start, newend);
  }


} } //namespace date_time



#endif

/* period.hpp
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
*/