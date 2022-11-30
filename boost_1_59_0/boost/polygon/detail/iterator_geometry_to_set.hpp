/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_GEOMETRY_TO_SET_HPP
#define BOOST_POLYGON_ITERATOR_GEOMETRY_TO_SET_HPP
namespace boost { namespace polygon{
template <typename concept_type, typename geometry_type>
class iterator_geometry_to_set {};

template <typename rectangle_type>
class iterator_geometry_to_set<rectangle_concept, rectangle_type> {
public:
  typedef typename rectangle_traits<rectangle_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  rectangle_data<coordinate_type> rectangle_;
  mutable value_type vertex_;
  unsigned int corner_;
  orientation_2d orient_;
  bool is_hole_;
public:
  iterator_geometry_to_set() : rectangle_(), vertex_(), corner_(4), orient_(), is_hole_() {}
  iterator_geometry_to_set(const rectangle_type& rectangle, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    rectangle_(), vertex_(), corner_(0), orient_(orient), is_hole_(is_hole) {
    assign(rectangle_, rectangle);
    if(dir == HIGH) corner_ = 4;
  }
  inline iterator_geometry_to_set& operator++() {
    ++corner_;
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return corner_ == that.corner_;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(corner_ == 0) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), LOW);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 1) {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = -1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 2) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), HIGH);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
    } else {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    }
    return vertex_;
  }
};

template <typename polygon_type>
class iterator_geometry_to_set<polygon_90_concept, polygon_type> {
public:
  typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
  typedef typename polygon_traits<polygon_type>::iterator_type coord_iterator_type;
private:
  value_type vertex_;
  typename polygon_traits<polygon_type>::iterator_type itrb, itre;
  bool last_vertex_;
  bool is_hole_;
  int multiplier_;
  point_data<coordinate_type> first_pt, second_pt, pts[3];
  bool use_wrap;
  orientation_2d orient_;
  int polygon_index;
public:
  iterator_geometry_to_set() : vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {}
  iterator_geometry_to_set(const polygon_type& polygon, direction_1d dir, orientation_2d orient = HORIZONTAL, bool is_hole = false, bool winding_override = false, direction_1d w = CLOCKWISE) :
    vertex_(), itrb(), itre(), last_vertex_(),
    is_hole_(is_hole), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(),
    orient_(orient), polygon_index(0) {
    itrb = begin_points(polygon);
    itre = end_points(polygon);
    use_wrap = false;
    if(itrb == itre || dir == HIGH || ::boost::polygon::size(polygon) < 4) {
      polygon_index = -1;
    } else {
      direction_1d wdir = w;
      if(!winding_override)
        wdir = winding(polygon);
      multiplier_ = wdir == LOW ? -1 : 1;
      if(is_hole_) multiplier_ *= -1;
      first_pt = pts[0] = *itrb;
      ++itrb;
      second_pt = pts[1] = *itrb;
      ++itrb;
      pts[2] = *itrb;
      evaluate_();
    }
  }
  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(),
    second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {
    vertex_ = that.vertex_;
    itrb = that.itrb;
    itre = that.itre;
    last_vertex_ = that.last_vertex_;
    is_hole_ = that.is_hole_;
    multiplier_ = that.multiplier_;
    first_pt = that.first_pt;
    second_pt = that.second_pt;
    pts[0] = that.pts[0];
    pts[1] = that.pts[1];
    pts[2] = that.pts[2];
    use_wrap = that.use_wrap;
    orient_ = that.orient_;
    polygon_index = that.polygon_index;
  }
  inline iterator_geometry_to_set& operator++() {
    ++polygon_index;
    if(itrb == itre) {
      if(first_pt == pts[1]) polygon_index = -1;
      else {
        pts[0] = pts[1];
        pts[1] = pts[2];
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      }
    } else {
      ++itrb;
      pts[0] = pts[1];
      pts[1] = pts[2];
      if(itrb == itre) {
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      } else {
        pts[2] = *itrb;
      }
    }
    evaluate_();
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return polygon_index == that.polygon_index;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    return vertex_;
  }

  inline void evaluate_() {
    vertex_.first = pts[1].get(orient_.get_perpendicular());
    vertex_.second.first =pts[1].get(orient_);
    if(pts[1] == pts[2]) {
      vertex_.second.second = 0;
    } else if(pts[0].get(HORIZONTAL) != pts[1].get(HORIZONTAL)) {
      vertex_.second.second = -1;
    } else if(pts[0].get(VERTICAL) != pts[1].get(VERTICAL)) {
      vertex_.second.second = 1;
    } else {
      vertex_.second.second = 0;
    }
    vertex_.second.second *= multiplier_;
  }
};

template <typename polygon_with_holes_type>
class iterator_geometry_to_set<polygon_90_with_holes_concept, polygon_with_holes_type> {
public:
  typedef typename polygon_90_traits<polygon_with_holes_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type> itrb, itre;
  iterator_geometry_to_set<polygon_90_concept, typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type> itrhib, itrhie;
  typename polygon_with_holes_traits<polygon_with_holes_type>::iterator_holes_type itrhb, itrhe;
  orientation_2d orient_;
  bool is_hole_;
  bool started_holes;
public:
  iterator_geometry_to_set() : itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {}
  iterator_geometry_to_set(const polygon_with_holes_type& polygon, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(orient), is_hole_(is_hole), started_holes() {
    itre = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, HIGH, orient, is_hole_);
    itrhe = end_holes(polygon);
    if(dir == HIGH) {
      itrb = itre;
      itrhb = itrhe;
      started_holes = true;
    } else {
      itrb = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, LOW, orient, is_hole_);
      itrhb = begin_holes(polygon);
      started_holes = false;
    }
  }
  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {
    itrb = that.itrb;
    itre = that.itre;
    if(that.itrhib != that.itrhie) {
      itrhib = that.itrhib;
      itrhie = that.itrhie;
    }
    itrhb = that.itrhb;
    itrhe = that.itrhe;
    orient_ = that.orient_;
    is_hole_ = that.is_hole_;
    started_holes = that.started_holes;
  }
  inline iterator_geometry_to_set& operator++() {
    //this code can be folded with flow control factoring
    if(itrb == itre) {
      if(itrhib == itrhie) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        } else {
          //in this case we have no holes so we just need the iterhib == itrhie, which
          //is always true if they were default initialized in the initial case or
          //both point to end of the previous hole processed
          //no need to explicitly reset them, and it causes an stl debug assertion to use
          //the default constructed iterator this way
          //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
          //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
        }
      } else {
        ++itrhib;
        if(itrhib == itrhie) {
          if(itrhb != itrhe) {
            itrhib = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
            itrhie = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
            ++itrhb;
          } else {
            //this is the same case as above
            //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
            //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
          }
        }
      }
    } else {
      ++itrb;
      if(itrb == itre) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        }
      }
    }
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return itrb == that.itrb && itrhb == that.itrhb && itrhib == that.itrhib;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(itrb != itre) return *itrb;
    return *itrhib;
  }
};


}
}
#endif

/* iterator_geometry_to_set.hpp
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
*/