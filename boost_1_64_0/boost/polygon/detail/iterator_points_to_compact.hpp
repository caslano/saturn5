/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
#define BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
namespace boost { namespace polygon{
template <typename iT, typename point_type>
class iterator_points_to_compact {
private:
  iT iter_, iterEnd_;
  orientation_2d orient_;
  mutable typename point_traits<point_type>::coordinate_type coord_;
public:
  typedef typename point_traits<point_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef coordinate_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const coordinate_type* pointer; //immutable
  typedef const coordinate_type& reference; //immutable

  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}
  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}
  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}
  //use bitwise copy and assign provided by the compiler
  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }
  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }
  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }
  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }
};
}
}
#endif


/* iterator_points_to_compact.hpp
+YHa2wE+8+cBs3mcwAT6bgEVikRi1Qi/yYqfyekqdGA6YPajC1LD36BybihPL9K/97SpmnzfbYM5LeLGB1HHHOs2xXcvUNVt1jr6r5tvjySxhNEKB9WdoMbnZ4DUL6XmBOyJs13+EDylPywaTi+PpVYOfk0GM0xHYhNsYMRHm6ZvLBunSZ4mZwv3R/nRn0Qz9wlzQcImNYkyqq32ZGyckRFrpaE/VfuDDs/s7H67PNB990d2ch/lVicsofbYI/WV2WHbm9nzPLhOUGnZoAljEZLw8tN5i7MM1umy5vlsJNXZZZYE8ChkJ4ZqImCeAzmEJJ63N5479C2ulGYCNFhPA+ySGjKi6ilj8KisSuXdp4xjU0G6SPiriGujUVkKRJeQsRIRPqHYg2TO2qCW3tqxyvxBruNx8y95ucck0n31cxahpmgM618b2I9mrQZ0/HdELyhfWRpKj0+2V8AVwnVkvSg3aoSXae8Iu+eDR6fm8rzCzk9FiIu913+Lyf6a5najXFBQ7IYRS6FOfCtHV8w4x1naMpHoeyyO92ZlAogH0s4L3cZDNMZXNRRizA==
*/