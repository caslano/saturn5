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