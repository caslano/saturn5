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
VblvlT/K5APhR1Yc+X4hoJLkALMKvQa33ubReBjjgMnnIo+DIJPjuVArh72YC2WBeVhpgkH7lYCxi6geGLJcO5LVB+GtMMCCee/+PJUpZFcsPcfxHTHTW64TnF1eW8KkurrMl4wyF0FSunmqx3ZprF5HuSF4YIQZ3V62foPH0CvjLPJT2xHaTCw2HFNiabs9iOlIRJFYdhAFNurAFjevYivIX2DK0WXB+kuZHl/ksre5QRGiHl6URtufM8riloUfpakjqiCkMlW9rVlNWFIjTjlaxyvNssiKs5KgbOqoJq2+CvI2xjf4+J8WfuJbnqiGNIyJytL99DeMcTEKrCxwYvG4fbKh7nvcXlnevY/bB+Mx/J+OCsLmgLetDbEYDKkT+06WY3AKSNUc437C0vVk3RVuakURBtSo6oqZHNcjbxxi60OZmG8HBYyP8njFvDQWDjpsvfU3lqYtHFnRRVEmfTk10NC5B2WHvsnHprIMvMiOcy7bPq7tMGTDqPTT2Cn7spWl1NkQY027i8qWIs7LskxTvy/K1/mWlnNZmpbwPbsoAt8W0B9UevNSvqcrxsLYM1QuFZFj+UVkgRQO/cymcywdT0R2lGdRFEkJ1YelH3WBRDhRsugjoLL7/DII3NB1laRc33T0IzVrOq0jLC1bZJ6dpGlagoTKHEuIz9/HqWwugtzPQjAHiMqZu7Mio1h2jFgmp7jtM/hI9stMyfTWpudwTK8SEzqfX/umsa4voswLZUdcW6Kj9176zaRlzxuyfmjFTmRzUSPye6y/Y6isY4kisL3YLXMuzEeQvVXY48aYuPOMGWvRS+WA5Av5XEBPGhiqCLwecnieml+YX63HolXYk5uQezHb7gf7LXpFhyFR1H7MMyUu7s9xvIwP/hGyb2f14zhoMl7u9/X8+wWa11L4SRr7ciATbuVfwHrCQZSff8E9VLbn7AWencPpl7FiorTGQ8XFNMe/yOP6ZImXu34sxrqdaYj82qsnHGmgOfnX5fp/Yc2/18v7feBNVM/+MC8TN0xjkRcTT3JCz0nqitnr63bM0pWNMkhtz7UilnDd9eaX1mSS8lwd1NasHF86AtvKJarHiUQSysL6uUv1TEq5yuhSXg+Mcj1QvxeBuu5O955l4TIr8rzEisWT5zqy1CtVjiZnYGDGUQQ1rzJdr2S6ChH5oWx1YU7z9TxU2+/3K8uLME+BLqyjy1QX+CsdOfJadiGsmRkoHnSjFTm1Q8xfpQFUz0O/hrz1bbXry/wskxM6vmU5vkhV2mvdqnKxRL06qxKbkprZux9zTFcukryMy9Jb9z2DB+j2QPU9InPcPLEiVzy32pYw4mhSbiZKv3Qsuw7eOMGGsqEFffZq6H5kb13768jZq9EWXO8vgY5J2dc/rfqnBnGjDvdmt4AOjesNNZnI4frO/7TUodG6YPCMgjo7PUsw0An8Pz9A/TaReZkcViDAGGDVGeyLBIPtEADU2WxZFlf2dP+JuTMx/pTSG6r4c0S/lME0Vvq/o+tSiiisSzBiW4VdIOkvYtbUeR7c+7CHifeWnAX+yQbAzFTrYkAwALC55o4QLtsfwfjxiHOHL3njlXHU3gliBzZSDDphX7e7iWI9phvPuCkObzfsvulmgoN6Tao39dA3rnjyN4xz0j+3vWuLxkBBf0/xivq992x9/FDH7AAN9M77wk1aeewcML7HO4i7toj6wpu2cujWHObxF+1cvS2HvIM3a+XhOWOMB/cFvn/nuqmbZf669+90v7/xvjou2NIy7JdPy1cQ1a6zcZ/IGR7kRO/vBa4OUx5/k/XgBgMDRSSNR48wnDm/af2Eo8CT+UUS7AWogQo551o5UIN9TnejyYE=
*/