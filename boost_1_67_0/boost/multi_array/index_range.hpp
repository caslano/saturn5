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