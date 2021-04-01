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
SoqVzDkKIdJ8QLDvEGe9L6+Zw/euAUWfTUDI4y9Y1qNtGezsosWr1RGUPHJR580/9ClOZqDS2qH+HGMuyP5FiJ8SRbTNAZe1o1qF53381O6mXsKCmtkyIbv2qedn5emJVu7vPa2wpuZ9LStEivrEe+ruJAcV3e4JsB8yo5I+2BFuO7xEb8B3t/VE2jL7MRKLO9sGE8sp3TTvPK0lD3x5tH0XC4Sge9eM8yO/Tz6TBBOpj+hfBYcdFH2SvM/gW75FhuiEP54aNqjc8BAMjkNVe0lH7eOv4a0SWSOveacztIlzhdFvevhEV1ESc/V8/sjZkicX9mqM2nqsK37ACNSI01V5v0khMbO5vFDI66idY1oh0/fUSLn53DBVud3ustoP7yyNw6gJOqTAh2PIJQZH3KqkTyd1cpfrsAY+cl98Mymf+6xADj/4GeWV+a6zMdHZDxN2bAD+FGAMTplqkvCLxdcmWYw4wuAdnoMSOOuStF6sMRat4zl+HYwDEp0hd505Pbi37+oS2Wn2v+1sniyuV2PPQ8ZfOHFE1la2lQK9edVAvsgen+nQEWJUhw==
*/