// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_INDEX_RANGE_HPP
#define BOOST_MULTI_ARRAY_INDEX_RANGE_HPP

#include <boost/config.hpp>
#include <utility>
#include <boost/limits.hpp>

// For representing intervals, also with stride.
// A degenerate range is a range with one element.

// Thanks to Doug Gregor for the really cool idea of using the
// comparison operators to express various interval types!

// Internally, we represent the interval as half-open.

namespace boost {
namespace detail {
namespace multi_array {

  template <typename Index,typename SizeType>
  class index_range {
  public:
    typedef Index index;
    typedef SizeType size_type;

  private:
    static index from_start()
      { return (std::numeric_limits<index>::min)(); }

    static index to_end()
      { return (std::numeric_limits<index>::max)(); }

  public:

    index_range()
    {
      start_ = from_start();
      finish_ = to_end();
      stride_ = 1;
      degenerate_ = false;
    }

    explicit index_range(index pos)
    {
      start_ = pos;
      finish_ = pos+1;
      stride_ = 1;
      degenerate_ = true;
    }

    explicit index_range(index start, index finish, index stride=1)
      : start_(start), finish_(finish), stride_(stride),
        degenerate_(false)
    { }


    // These are for chaining assignments to an index_range
    index_range& start(index s) {
      start_ = s;
      degenerate_ = false;
      return *this;
    }

    index_range& finish(index f) {
      finish_ = f;
      degenerate_ = false;
      return *this;
    }

    index_range& stride(index s) { stride_ = s; return *this; }

    index start() const
    { 
      return start_; 
    }

    index get_start(index low_index_range = index_range::from_start()) const
    { 
      if (start_ == from_start())
        return low_index_range;
      return start_; 
    }

    index finish() const
    {
      return finish_;
    }

    index get_finish(index high_index_range = index_range::to_end()) const
    {
      if (finish_ == to_end())
        return high_index_range;
      return finish_;
    }

    index stride() const { return stride_; }

    size_type size(index idx) const
    {
      return (start_ == from_start() || finish_ == to_end())
        ? idx : ((finish_ - start_) / stride_);
    }

    void set_index_range(index start, index finish, index stride=1)
    {
      start_ = start;
      finish_ = finish;
      stride_ = stride;
    }

    static index_range all() 
    { return index_range(from_start(), to_end(), 1); }

    bool is_degenerate() const { return degenerate_; }

    index_range operator-(index shift) const
    { 
      return index_range(start_ - shift, finish_ - shift, stride_); 
    }

    index_range operator+(index shift) const
    { 
      return index_range(start_ + shift, finish_ + shift, stride_); 
    }

    index operator[](unsigned i) const
    {
      return start_ + i * stride_;
    }

    index operator()(unsigned i) const
    {
      return start_ + i * stride_;
    }

    // add conversion to std::slice?

  public:
    index start_, finish_, stride_;
    bool degenerate_;
  };

  // Express open and closed interval end-points using the comparison
  // operators.

  // left closed
  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<=(Index s, const index_range<Index,SizeType>& r)
  {
    return index_range<Index,SizeType>(s, r.finish(), r.stride());
  }

  // left open
  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<(Index s, const index_range<Index,SizeType>& r)
  {
    return index_range<Index,SizeType>(s + 1, r.finish(), r.stride());
  }

  // right open
  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<(const index_range<Index,SizeType>& r, Index f)
  {
    return index_range<Index,SizeType>(r.start(), f, r.stride());
  }

  // right closed
  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<=(const index_range<Index,SizeType>& r, Index f)
  {
    return index_range<Index,SizeType>(r.start(), f + 1, r.stride());
  }

} // namespace multi_array
} // namespace detail  
} // namespace boost

#endif

/* index_range.hpp
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
*/