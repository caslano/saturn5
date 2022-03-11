// Boost.Polygon library detail/voronoi_structures.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES
#define BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES

#include <list>
#include <queue>
#include <vector>

#include "boost/polygon/voronoi_geometry_type.hpp"

namespace boost {
namespace polygon {
namespace detail {
// Cartesian 2D point data structure.
template <typename T>
class point_2d {
 public:
  typedef T coordinate_type;

  point_2d() {}

  point_2d(coordinate_type x, coordinate_type y) :
      x_(x),
      y_(y) {}

  bool operator==(const point_2d& that) const {
    return (this->x_ == that.x()) && (this->y_ == that.y());
  }

  bool operator!=(const point_2d& that) const {
    return (this->x_ != that.x()) || (this->y_ != that.y());
  }

  coordinate_type x() const {
    return x_;
  }

  coordinate_type y() const {
    return y_;
  }

  point_2d& x(coordinate_type x) {
    x_ = x;
    return *this;
  }

  point_2d& y(coordinate_type y) {
    y_ = y;
    return *this;
  }

 private:
  coordinate_type x_;
  coordinate_type y_;
};

// Site event type.
// Occurs when the sweepline sweeps over one of the initial sites:
//   1) point site
//   2) start-point of the segment site
//   3) endpoint of the segment site
// Implicit segment direction is defined: the start-point of
// the segment compares less than its endpoint.
// Each input segment is divided onto two site events:
//   1) One going from the start-point to the endpoint
//      (is_inverse() = false)
//   2) Another going from the endpoint to the start-point
//      (is_inverse() = true)
// In beach line data structure segment sites of the first
// type precede sites of the second type for the same segment.
// Members:
//   point0_ - point site or segment's start-point
//   point1_ - segment's endpoint if site is a segment
//   sorted_index_ - the last bit encodes information if the site is inverse;
//     the other bits encode site event index among the sorted site events
//   initial_index_ - site index among the initial input set
// Note: for all sites is_inverse_ flag is equal to false by default.
template <typename T>
class site_event {
 public:
  typedef T coordinate_type;
  typedef point_2d<T> point_type;

  site_event() :
      point0_(0, 0),
      point1_(0, 0),
      sorted_index_(0),
      flags_(0) {}

  site_event(coordinate_type x, coordinate_type y) :
      point0_(x, y),
      point1_(x, y),
      sorted_index_(0),
      flags_(0) {}

  explicit site_event(const point_type& point) :
      point0_(point),
      point1_(point),
      sorted_index_(0),
      flags_(0) {}

  site_event(coordinate_type x1, coordinate_type y1,
             coordinate_type x2, coordinate_type y2):
      point0_(x1, y1),
      point1_(x2, y2),
      sorted_index_(0),
      flags_(0) {}

  site_event(const point_type& point1, const point_type& point2) :
      point0_(point1),
      point1_(point2),
      sorted_index_(0),
      flags_(0) {}

  bool operator==(const site_event& that) const {
    return (this->point0_ == that.point0_) &&
           (this->point1_ == that.point1_);
  }

  bool operator!=(const site_event& that) const {
    return (this->point0_ != that.point0_) ||
           (this->point1_ != that.point1_);
  }

  coordinate_type x() const {
    return point0_.x();
  }

  coordinate_type y() const {
    return point0_.y();
  }

  coordinate_type x0() const {
    return point0_.x();
  }

  coordinate_type y0() const {
    return point0_.y();
  }

  coordinate_type x1() const {
    return point1_.x();
  }

  coordinate_type y1() const {
    return point1_.y();
  }

  const point_type& point0() const {
    return point0_;
  }

  const point_type& point1() const {
    return point1_;
  }

  std::size_t sorted_index() const {
    return sorted_index_;
  }

  site_event& sorted_index(std::size_t index) {
    sorted_index_ = index;
    return *this;
  }

  std::size_t initial_index() const {
    return initial_index_;
  }

  site_event& initial_index(std::size_t index) {
    initial_index_ = index;
    return *this;
  }

  bool is_inverse() const {
    return (flags_ & IS_INVERSE) ? true : false;
  }

  site_event& inverse() {
    std::swap(point0_, point1_);
    flags_ ^= IS_INVERSE;
    return *this;
  }

  SourceCategory source_category() const {
    return static_cast<SourceCategory>(flags_ & SOURCE_CATEGORY_BITMASK);
  }

  site_event& source_category(SourceCategory source_category) {
    flags_ |= source_category;
    return *this;
  }

  bool is_point() const {
    return (point0_.x() == point1_.x()) && (point0_.y() == point1_.y());
  }

  bool is_segment() const {
    return (point0_.x() != point1_.x()) || (point0_.y() != point1_.y());
  }

 private:
  enum Bits {
    IS_INVERSE = 0x20  // 32
  };

  point_type point0_;
  point_type point1_;
  std::size_t sorted_index_;
  std::size_t initial_index_;
  std::size_t flags_;
};

// Circle event type.
// Occurs when the sweepline sweeps over the rightmost point of the Voronoi
// circle (with the center at the intersection point of the bisectors).
// Circle event is made of the two consecutive nodes in the beach line data
// structure. In case another node was inserted during algorithm execution
// between the given two nodes circle event becomes inactive.
// Variables:
//   center_x_ - center x-coordinate;
//   center_y_ - center y-coordinate;
//   lower_x_ - leftmost x-coordinate;
//   is_active_ - states whether circle event is still active.
// NOTE: lower_y coordinate is always equal to center_y.
template <typename T>
class circle_event {
 public:
  typedef T coordinate_type;

  circle_event() : is_active_(true) {}

  circle_event(coordinate_type c_x,
               coordinate_type c_y,
               coordinate_type lower_x) :
      center_x_(c_x),
      center_y_(c_y),
      lower_x_(lower_x),
      is_active_(true) {}

  coordinate_type x() const {
    return center_x_;
  }

  circle_event& x(coordinate_type center_x) {
    center_x_ = center_x;
    return *this;
  }

  coordinate_type y() const {
    return center_y_;
  }

  circle_event& y(coordinate_type center_y) {
    center_y_ = center_y;
    return *this;
  }

  coordinate_type lower_x() const {
    return lower_x_;
  }

  circle_event& lower_x(coordinate_type lower_x) {
    lower_x_ = lower_x;
    return *this;
  }

  coordinate_type lower_y() const {
    return center_y_;
  }

  bool is_active() const {
    return is_active_;
  }

  circle_event& deactivate() {
    is_active_ = false;
    return *this;
  }

 private:
  coordinate_type center_x_;
  coordinate_type center_y_;
  coordinate_type lower_x_;
  bool is_active_;
};

// Event queue data structure, holds circle events.
// During algorithm run, some of the circle events disappear (become
// inactive). Priority queue data structure doesn't support
// iterators (there is no direct ability to modify its elements).
// Instead list is used to store all the circle events and priority queue
// of the iterators to the list elements is used to keep the correct circle
// events ordering.
template <typename T, typename Predicate>
class ordered_queue {
 public:
  ordered_queue() {}

  bool empty() const {
    return c_.empty();
  }

  const T &top() const {
    return *c_.top();
  }

  void pop() {
    list_iterator_type it = c_.top();
    c_.pop();
    c_list_.erase(it);
  }

  T &push(const T &e) {
    c_list_.push_front(e);
    c_.push(c_list_.begin());
    return c_list_.front();
  }

  void clear() {
    while (!c_.empty())
        c_.pop();
    c_list_.clear();
  }

 private:
  typedef typename std::list<T>::iterator list_iterator_type;

  struct comparison {
    bool operator() (const list_iterator_type &it1,
                     const list_iterator_type &it2) const {
      return cmp_(*it1, *it2);
    }
    Predicate cmp_;
  };

  std::priority_queue< list_iterator_type,
                       std::vector<list_iterator_type>,
                       comparison > c_;
  std::list<T> c_list_;

  // Disallow copy constructor and operator=
  ordered_queue(const ordered_queue&);
  void operator=(const ordered_queue&);
};

// Represents a bisector node made by two arcs that correspond to the left
// and right sites. Arc is defined as a curve with points equidistant from
// the site and from the sweepline. If the site is a point then arc is
// a parabola, otherwise it's a line segment. A segment site event will
// produce different bisectors based on its direction.
// In general case two sites will create two opposite bisectors. That's
// why the order of the sites is important to define the unique bisector.
// The one site is considered to be newer than the other one if it was
// processed by the algorithm later (has greater index).
template <typename Site>
class beach_line_node_key {
 public:
  typedef Site site_type;

  // Constructs degenerate bisector, used to search an arc that is above
  // the given site. The input to the constructor is the new site point.
  explicit beach_line_node_key(const site_type &new_site) :
      left_site_(new_site),
      right_site_(new_site) {}

  // Constructs a new bisector. The input to the constructor is the two
  // sites that create the bisector. The order of sites is important.
  beach_line_node_key(const site_type &left_site,
                      const site_type &right_site) :
      left_site_(left_site),
      right_site_(right_site) {}

  const site_type &left_site() const {
    return left_site_;
  }

  site_type &left_site() {
    return left_site_;
  }

  beach_line_node_key& left_site(const site_type &site) {
    left_site_ = site;
    return *this;
  }

  const site_type &right_site() const {
    return right_site_;
  }

  site_type &right_site() {
    return right_site_;
  }

  beach_line_node_key& right_site(const site_type &site) {
    right_site_ = site;
    return *this;
  }

 private:
  site_type left_site_;
  site_type right_site_;
};

// Represents edge data structure from the Voronoi output, that is
// associated as a value with beach line bisector in the beach
// line. Contains pointer to the circle event in the circle event
// queue if the edge corresponds to the right bisector of the circle event.
template <typename Edge, typename Circle>
class beach_line_node_data {
 public:
  explicit beach_line_node_data(Edge* new_edge) :
      circle_event_(NULL),
      edge_(new_edge) {}

  Circle* circle_event() const {
    return circle_event_;
  }

  beach_line_node_data& circle_event(Circle* circle_event) {
    circle_event_ = circle_event;
    return *this;
  }

  Edge* edge() const {
    return edge_;
  }

  beach_line_node_data& edge(Edge* new_edge) {
    edge_ = new_edge;
    return *this;
  }

 private:
  Circle* circle_event_;
  Edge* edge_;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES

/* voronoi_structures.hpp
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
*/