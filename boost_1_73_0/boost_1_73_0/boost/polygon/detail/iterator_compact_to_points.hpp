/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
#define BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
namespace boost { namespace polygon{
template <typename iterator_type, typename point_type>
class iterator_compact_to_points {
private:
  iterator_type iter_;
  iterator_type iter_end_;
  point_type pt_;
  typename point_traits<point_type>::coordinate_type firstX_;
  orientation_2d orient_;
public:
  typedef std::forward_iterator_tag iterator_category;
  typedef point_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const point_type* pointer; //immutable
  typedef const point_type& reference; //immutable

  inline iterator_compact_to_points() : iter_(), iter_end_(), pt_(), firstX_(), orient_() {}
  inline iterator_compact_to_points(iterator_type iter, iterator_type iter_end) :
    iter_(iter), iter_end_(iter_end), pt_(), firstX_(), orient_(HORIZONTAL) {
    if(iter_ != iter_end_) {
      firstX_ = *iter_;
      x(pt_, firstX_);
      ++iter_;
      if(iter_ != iter_end_) {
        y(pt_, *iter_);
      }
    }
  }
  //use bitwise copy and assign provided by the compiler
  inline iterator_compact_to_points& operator++() {
    iterator_type prev_iter = iter_;
    ++iter_;
    if(iter_ == iter_end_) {
      if(x(pt_) != firstX_) {
        iter_ = prev_iter;
        x(pt_, firstX_);
      }
    } else {
      set(pt_, orient_, *iter_);
      orient_.turn_90();
    }
    return *this;
  }
  inline const iterator_compact_to_points operator++(int) {
    iterator_compact_to_points tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ == that.iter_;
    }
    return (iter_ == that.iter_) && (x(pt_) == x(that.pt_));
  }
  inline bool operator!=(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ != that.iter_;
    }
    return (iter_ != that.iter_) || (x(pt_) != x(that.pt_));
  }
  inline reference operator*() const { return pt_; }
};
}
}
#endif

/* iterator_compact_to_points.hpp
WBmd9yKavYhaDTgqrrNM3SP9KBWP9dScXU4nszF0AS//D0Q9/H/88Pj3PVF2BXbCwMPKY2HbuO5jkc9xzTploU/o7h5g9zBcn2EjnOC+j21+dvq9JnjDYvyfuve8mPPKV1BLAwQKAAAACAAtZ0pSJTMtUiYDAADzBgAAIQAJAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvdW5pdDE2MDEuY1VUBQABtkgkYK1UbU/bMBD+nl9xyr60KDSQrdCObVpX2KjYWtQGTRWZIsdxiLfEjmynBI39953TMgRjqjThKrVzueflzk78necbDuzA1hG3V4wD5xZxruR3Rs3T2XF8C+sfoiKct4n4cA+5jbuwHXILnRYSb1Te2HUcbxOKrDf751tkFNslRhBmkWNZ3Sh+lRvojLuwPxwOYBeCvWDPg2MiOCtgYZhImLry4E3aRt7npGl6mr3zgBkgRW9DFeZcg5aZuSaKAa4LTpnQLAWiIWWaKp7gDRdgcgYZLxiMZ+fLyfSTB9c5p7kluZE16FzWRQo5WTFQjDK+WnNURBmQGcKRPOXaIGFtuBQ91GZgmCq15bDypNASyIrwgiQoRAzkxlT6te/TWhXo3k8l1T69K7+Xm/JPJUs0UZIbkJUBI6HWzAOb6UEpU57ZGRuC
*/