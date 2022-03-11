// Boost.Polygon library voronoi_diagram.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_DIAGRAM
#define BOOST_POLYGON_VORONOI_DIAGRAM

#include <vector>
#include <utility>

#include "detail/voronoi_ctypes.hpp"
#include "detail/voronoi_structures.hpp"

#include "voronoi_geometry_type.hpp"

namespace boost {
namespace polygon {

// Forward declarations.
template <typename T>
class voronoi_edge;

// Represents Voronoi cell.
// Data members:
//   1) index of the source within the initial input set
//   2) pointer to the incident edge
//   3) mutable color member
// Cell may contain point or segment site inside.
template <typename T>
class voronoi_cell {
 public:
  typedef T coordinate_type;
  typedef std::size_t color_type;
  typedef voronoi_edge<coordinate_type> voronoi_edge_type;
  typedef std::size_t source_index_type;
  typedef SourceCategory source_category_type;

  voronoi_cell(source_index_type source_index,
               source_category_type source_category) :
      source_index_(source_index),
      incident_edge_(NULL),
      color_(source_category) {}

  // Returns true if the cell contains point site, false else.
  bool contains_point() const {
    source_category_type source_category = this->source_category();
    return belongs(source_category, GEOMETRY_CATEGORY_POINT);
  }

  // Returns true if the cell contains segment site, false else.
  bool contains_segment() const {
    source_category_type source_category = this->source_category();
    return belongs(source_category, GEOMETRY_CATEGORY_SEGMENT);
  }

  source_index_type source_index() const {
    return source_index_;
  }

  source_category_type source_category() const {
    return static_cast<source_category_type>(color_ & SOURCE_CATEGORY_BITMASK);
  }

  // Degenerate cells don't have any incident edges.
  bool is_degenerate() const { return incident_edge_ == NULL; }

  voronoi_edge_type* incident_edge() { return incident_edge_; }
  const voronoi_edge_type* incident_edge() const { return incident_edge_; }
  void incident_edge(voronoi_edge_type* e) { incident_edge_ = e; }

  color_type color() const { return color_ >> BITS_SHIFT; }
  void color(color_type color) const {
    color_ &= BITS_MASK;
    color_ |= color << BITS_SHIFT;
  }

 private:
  // 5 color bits are reserved.
  enum Bits {
    BITS_SHIFT = 0x5,
    BITS_MASK = 0x1F
  };

  source_index_type source_index_;
  voronoi_edge_type* incident_edge_;
  mutable color_type color_;
};

// Represents Voronoi vertex.
// Data members:
//   1) vertex coordinates
//   2) pointer to the incident edge
//   3) mutable color member
template <typename T>
class voronoi_vertex {
 public:
  typedef T coordinate_type;
  typedef std::size_t color_type;
  typedef voronoi_edge<coordinate_type> voronoi_edge_type;

  voronoi_vertex(const coordinate_type& x, const coordinate_type& y) :
      x_(x),
      y_(y),
      incident_edge_(NULL),
      color_(0) {}

  const coordinate_type& x() const { return x_; }
  const coordinate_type& y() const { return y_; }

  bool is_degenerate() const { return incident_edge_ == NULL; }

  voronoi_edge_type* incident_edge() { return incident_edge_; }
  const voronoi_edge_type* incident_edge() const { return incident_edge_; }
  void incident_edge(voronoi_edge_type* e) { incident_edge_ = e; }

  color_type color() const { return color_ >> BITS_SHIFT; }
  void color(color_type color) const {
    color_ &= BITS_MASK;
    color_ |= color << BITS_SHIFT;
  }

 private:
  // 5 color bits are reserved.
  enum Bits {
    BITS_SHIFT = 0x5,
    BITS_MASK = 0x1F
  };

  coordinate_type x_;
  coordinate_type y_;
  voronoi_edge_type* incident_edge_;
  mutable color_type color_;
};

// Half-edge data structure. Represents Voronoi edge.
// Data members:
//   1) pointer to the corresponding cell
//   2) pointer to the vertex that is the starting
//      point of the half-edge
//   3) pointer to the twin edge
//   4) pointer to the CCW next edge
//   5) pointer to the CCW prev edge
//   6) mutable color member
template <typename T>
class voronoi_edge {
 public:
  typedef T coordinate_type;
  typedef voronoi_cell<coordinate_type> voronoi_cell_type;
  typedef voronoi_vertex<coordinate_type> voronoi_vertex_type;
  typedef voronoi_edge<coordinate_type> voronoi_edge_type;
  typedef std::size_t color_type;

  voronoi_edge(bool is_linear, bool is_primary) :
      cell_(NULL),
      vertex_(NULL),
      twin_(NULL),
      next_(NULL),
      prev_(NULL),
      color_(0) {
    if (is_linear)
      color_ |= BIT_IS_LINEAR;
    if (is_primary)
      color_ |= BIT_IS_PRIMARY;
  }

  voronoi_cell_type* cell() { return cell_; }
  const voronoi_cell_type* cell() const { return cell_; }
  void cell(voronoi_cell_type* c) { cell_ = c; }

  voronoi_vertex_type* vertex0() { return vertex_; }
  const voronoi_vertex_type* vertex0() const { return vertex_; }
  void vertex0(voronoi_vertex_type* v) { vertex_ = v; }

  voronoi_vertex_type* vertex1() { return twin_->vertex0(); }
  const voronoi_vertex_type* vertex1() const { return twin_->vertex0(); }

  voronoi_edge_type* twin() { return twin_; }
  const voronoi_edge_type* twin() const { return twin_; }
  void twin(voronoi_edge_type* e) { twin_ = e; }

  voronoi_edge_type* next() { return next_; }
  const voronoi_edge_type* next() const { return next_; }
  void next(voronoi_edge_type* e) { next_ = e; }

  voronoi_edge_type* prev() { return prev_; }
  const voronoi_edge_type* prev() const { return prev_; }
  void prev(voronoi_edge_type* e) { prev_ = e; }

  // Returns a pointer to the rotation next edge
  // over the starting point of the half-edge.
  voronoi_edge_type* rot_next() { return prev_->twin(); }
  const voronoi_edge_type* rot_next() const { return prev_->twin(); }

  // Returns a pointer to the rotation prev edge
  // over the starting point of the half-edge.
  voronoi_edge_type* rot_prev() { return twin_->next(); }
  const voronoi_edge_type* rot_prev() const { return twin_->next(); }

  // Returns true if the edge is finite (segment, parabolic arc).
  // Returns false if the edge is infinite (ray, line).
  bool is_finite() const { return vertex0() && vertex1(); }

  // Returns true if the edge is infinite (ray, line).
  // Returns false if the edge is finite (segment, parabolic arc).
  bool is_infinite() const { return !vertex0() || !vertex1(); }

  // Returns true if the edge is linear (segment, ray, line).
  // Returns false if the edge is curved (parabolic arc).
  bool is_linear() const {
    return (color_ & BIT_IS_LINEAR) ? true : false;
  }

  // Returns true if the edge is curved (parabolic arc).
  // Returns false if the edge is linear (segment, ray, line).
  bool is_curved() const {
    return (color_ & BIT_IS_LINEAR) ? false : true;
  }

  // Returns false if edge goes through the endpoint of the segment.
  // Returns true else.
  bool is_primary() const {
    return (color_ & BIT_IS_PRIMARY) ? true : false;
  }

  // Returns true if edge goes through the endpoint of the segment.
  // Returns false else.
  bool is_secondary() const {
    return (color_ & BIT_IS_PRIMARY) ? false : true;
  }

  color_type color() const { return color_ >> BITS_SHIFT; }
  void color(color_type color) const {
    color_ &= BITS_MASK;
    color_ |= color << BITS_SHIFT;
  }

 private:
  // 5 color bits are reserved.
  enum Bits {
    BIT_IS_LINEAR = 0x1,  // linear is opposite to curved
    BIT_IS_PRIMARY = 0x2,  // primary is opposite to secondary

    BITS_SHIFT = 0x5,
    BITS_MASK = 0x1F
  };

  voronoi_cell_type* cell_;
  voronoi_vertex_type* vertex_;
  voronoi_edge_type* twin_;
  voronoi_edge_type* next_;
  voronoi_edge_type* prev_;
  mutable color_type color_;
};

template <typename T>
struct voronoi_diagram_traits {
  typedef T coordinate_type;
  typedef voronoi_cell<coordinate_type> cell_type;
  typedef voronoi_vertex<coordinate_type> vertex_type;
  typedef voronoi_edge<coordinate_type> edge_type;
  typedef class {
   public:
    enum { ULPS = 128 };
    bool operator()(const vertex_type& v1, const vertex_type& v2) const {
      return (ulp_cmp(v1.x(), v2.x(), ULPS) ==
              detail::ulp_comparison<T>::EQUAL) &&
             (ulp_cmp(v1.y(), v2.y(), ULPS) ==
              detail::ulp_comparison<T>::EQUAL);
    }
   private:
    typename detail::ulp_comparison<T> ulp_cmp;
  } vertex_equality_predicate_type;
};

// Voronoi output data structure.
// CCW ordering is used on the faces perimeter and around the vertices.
template <typename T, typename TRAITS = voronoi_diagram_traits<T> >
class voronoi_diagram {
 public:
  typedef typename TRAITS::coordinate_type coordinate_type;
  typedef typename TRAITS::cell_type cell_type;
  typedef typename TRAITS::vertex_type vertex_type;
  typedef typename TRAITS::edge_type edge_type;

  typedef std::vector<cell_type> cell_container_type;
  typedef typename cell_container_type::const_iterator const_cell_iterator;

  typedef std::vector<vertex_type> vertex_container_type;
  typedef typename vertex_container_type::const_iterator const_vertex_iterator;

  typedef std::vector<edge_type> edge_container_type;
  typedef typename edge_container_type::const_iterator const_edge_iterator;

  voronoi_diagram() {}

  void clear() {
    cells_.clear();
    vertices_.clear();
    edges_.clear();
  }

  const cell_container_type& cells() const {
    return cells_;
  }

  const vertex_container_type& vertices() const {
    return vertices_;
  }

  const edge_container_type& edges() const {
    return edges_;
  }

  std::size_t num_cells() const {
    return cells_.size();
  }

  std::size_t num_edges() const {
    return edges_.size();
  }

  std::size_t num_vertices() const {
    return vertices_.size();
  }

  void _reserve(std::size_t num_sites) {
    cells_.reserve(num_sites);
    vertices_.reserve(num_sites << 1);
    edges_.reserve((num_sites << 2) + (num_sites << 1));
  }

  template <typename CT>
  void _process_single_site(const detail::site_event<CT>& site) {
    cells_.push_back(cell_type(site.initial_index(), site.source_category()));
  }

  // Insert a new half-edge into the output data structure.
  // Takes as input left and right sites that form a new bisector.
  // Returns a pair of pointers to a new half-edges.
  template <typename CT>
  std::pair<void*, void*> _insert_new_edge(
      const detail::site_event<CT>& site1,
      const detail::site_event<CT>& site2) {
    // Get sites' indexes.
    std::size_t site_index1 = site1.sorted_index();
    std::size_t site_index2 = site2.sorted_index();

    bool is_linear = is_linear_edge(site1, site2);
    bool is_primary = is_primary_edge(site1, site2);

    // Create a new half-edge that belongs to the first site.
    edges_.push_back(edge_type(is_linear, is_primary));
    edge_type& edge1 = edges_.back();

    // Create a new half-edge that belongs to the second site.
    edges_.push_back(edge_type(is_linear, is_primary));
    edge_type& edge2 = edges_.back();

    // Add the initial cell during the first edge insertion.
    if (cells_.empty()) {
      cells_.push_back(cell_type(
          site1.initial_index(), site1.source_category()));
    }

    // The second site represents a new site during site event
    // processing. Add a new cell to the cell records.
    cells_.push_back(cell_type(
        site2.initial_index(), site2.source_category()));

    // Set up pointers to cells.
    edge1.cell(&cells_[site_index1]);
    edge2.cell(&cells_[site_index2]);

    // Set up twin pointers.
    edge1.twin(&edge2);
    edge2.twin(&edge1);

    // Return a pointer to the new half-edge.
    return std::make_pair(&edge1, &edge2);
  }

  // Insert a new half-edge into the output data structure with the
  // start at the point where two previously added half-edges intersect.
  // Takes as input two sites that create a new bisector, circle event
  // that corresponds to the intersection point of the two old half-edges,
  // pointers to those half-edges. Half-edges' direction goes out of the
  // new Voronoi vertex point. Returns a pair of pointers to a new half-edges.
  template <typename CT1, typename CT2>
  std::pair<void*, void*> _insert_new_edge(
      const detail::site_event<CT1>& site1,
      const detail::site_event<CT1>& site3,
      const detail::circle_event<CT2>& circle,
      void* data12, void* data23) {
    edge_type* edge12 = static_cast<edge_type*>(data12);
    edge_type* edge23 = static_cast<edge_type*>(data23);

    // Add a new Voronoi vertex.
    vertices_.push_back(vertex_type(circle.x(), circle.y()));
    vertex_type& new_vertex = vertices_.back();

    // Update vertex pointers of the old edges.
    edge12->vertex0(&new_vertex);
    edge23->vertex0(&new_vertex);

    bool is_linear = is_linear_edge(site1, site3);
    bool is_primary = is_primary_edge(site1, site3);

    // Add a new half-edge.
    edges_.push_back(edge_type(is_linear, is_primary));
    edge_type& new_edge1 = edges_.back();
    new_edge1.cell(&cells_[site1.sorted_index()]);

    // Add a new half-edge.
    edges_.push_back(edge_type(is_linear, is_primary));
    edge_type& new_edge2 = edges_.back();
    new_edge2.cell(&cells_[site3.sorted_index()]);

    // Update twin pointers.
    new_edge1.twin(&new_edge2);
    new_edge2.twin(&new_edge1);

    // Update vertex pointer.
    new_edge2.vertex0(&new_vertex);

    // Update Voronoi prev/next pointers.
    edge12->prev(&new_edge1);
    new_edge1.next(edge12);
    edge12->twin()->next(edge23);
    edge23->prev(edge12->twin());
    edge23->twin()->next(&new_edge2);
    new_edge2.prev(edge23->twin());

    // Return a pointer to the new half-edge.
    return std::make_pair(&new_edge1, &new_edge2);
  }

  void _build() {
    // Remove degenerate edges.
    edge_iterator last_edge = edges_.begin();
    for (edge_iterator it = edges_.begin(); it != edges_.end(); it += 2) {
      const vertex_type* v1 = it->vertex0();
      const vertex_type* v2 = it->vertex1();
      if (v1 && v2 && vertex_equality_predicate_(*v1, *v2)) {
        remove_edge(&(*it));
      } else {
        if (it != last_edge) {
          edge_type* e1 = &(*last_edge = *it);
          edge_type* e2 = &(*(last_edge + 1) = *(it + 1));
          e1->twin(e2);
          e2->twin(e1);
          if (e1->prev()) {
            e1->prev()->next(e1);
            e2->next()->prev(e2);
          }
          if (e2->prev()) {
            e1->next()->prev(e1);
            e2->prev()->next(e2);
          }
        }
        last_edge += 2;
      }
    }
    edges_.erase(last_edge, edges_.end());

    // Set up incident edge pointers for cells and vertices.
    for (edge_iterator it = edges_.begin(); it != edges_.end(); ++it) {
      it->cell()->incident_edge(&(*it));
      if (it->vertex0()) {
        it->vertex0()->incident_edge(&(*it));
      }
    }

    // Remove degenerate vertices.
    vertex_iterator last_vertex = vertices_.begin();
    for (vertex_iterator it = vertices_.begin(); it != vertices_.end(); ++it) {
      if (it->incident_edge()) {
        if (it != last_vertex) {
          *last_vertex = *it;
          vertex_type* v = &(*last_vertex);
          edge_type* e = v->incident_edge();
          do {
            e->vertex0(v);
            e = e->rot_next();
          } while (e != v->incident_edge());
        }
        ++last_vertex;
      }
    }
    vertices_.erase(last_vertex, vertices_.end());

    // Set up next/prev pointers for infinite edges.
    if (vertices_.empty()) {
      if (!edges_.empty()) {
        // Update prev/next pointers for the line edges.
        edge_iterator edge_it = edges_.begin();
        edge_type* edge1 = &(*edge_it);
        edge1->next(edge1);
        edge1->prev(edge1);
        ++edge_it;
        edge1 = &(*edge_it);
        ++edge_it;

        while (edge_it != edges_.end()) {
          edge_type* edge2 = &(*edge_it);
          ++edge_it;

          edge1->next(edge2);
          edge1->prev(edge2);
          edge2->next(edge1);
          edge2->prev(edge1);

          edge1 = &(*edge_it);
          ++edge_it;
        }

        edge1->next(edge1);
        edge1->prev(edge1);
      }
    } else {
      // Update prev/next pointers for the ray edges.
      for (cell_iterator cell_it = cells_.begin();
         cell_it != cells_.end(); ++cell_it) {
        if (cell_it->is_degenerate())
          continue;
        // Move to the previous edge while
        // it is possible in the CW direction.
        edge_type* left_edge = cell_it->incident_edge();
        while (left_edge->prev() != NULL) {
          left_edge = left_edge->prev();
          // Terminate if this is not a boundary cell.
          if (left_edge == cell_it->incident_edge())
            break;
        }

        if (left_edge->prev() != NULL)
          continue;

        edge_type* right_edge = cell_it->incident_edge();
        while (right_edge->next() != NULL)
          right_edge = right_edge->next();
        left_edge->prev(right_edge);
        right_edge->next(left_edge);
      }
    }
  }

 private:
  typedef typename cell_container_type::iterator cell_iterator;
  typedef typename vertex_container_type::iterator vertex_iterator;
  typedef typename edge_container_type::iterator edge_iterator;
  typedef typename TRAITS::vertex_equality_predicate_type
    vertex_equality_predicate_type;

  template <typename SEvent>
  bool is_primary_edge(const SEvent& site1, const SEvent& site2) const {
    bool flag1 = site1.is_segment();
    bool flag2 = site2.is_segment();
    if (flag1 && !flag2) {
      return (site1.point0() != site2.point0()) &&
             (site1.point1() != site2.point0());
    }
    if (!flag1 && flag2) {
      return (site2.point0() != site1.point0()) &&
             (site2.point1() != site1.point0());
    }
    return true;
  }

  template <typename SEvent>
  bool is_linear_edge(const SEvent& site1, const SEvent& site2) const {
    if (!is_primary_edge(site1, site2)) {
      return true;
    }
    return !(site1.is_segment() ^ site2.is_segment());
  }

  // Remove degenerate edge.
  void remove_edge(edge_type* edge) {
    // Update the endpoints of the incident edges to the second vertex.
    vertex_type* vertex = edge->vertex0();
    edge_type* updated_edge = edge->twin()->rot_next();
    while (updated_edge != edge->twin()) {
      updated_edge->vertex0(vertex);
      updated_edge = updated_edge->rot_next();
    }

    edge_type* edge1 = edge;
    edge_type* edge2 = edge->twin();

    edge_type* edge1_rot_prev = edge1->rot_prev();
    edge_type* edge1_rot_next = edge1->rot_next();

    edge_type* edge2_rot_prev = edge2->rot_prev();
    edge_type* edge2_rot_next = edge2->rot_next();

    // Update prev/next pointers for the incident edges.
    edge1_rot_next->twin()->next(edge2_rot_prev);
    edge2_rot_prev->prev(edge1_rot_next->twin());
    edge1_rot_prev->prev(edge2_rot_next->twin());
    edge2_rot_next->twin()->next(edge1_rot_prev);
  }

  cell_container_type cells_;
  vertex_container_type vertices_;
  edge_container_type edges_;
  vertex_equality_predicate_type vertex_equality_predicate_;

  // Disallow copy constructor and operator=
  voronoi_diagram(const voronoi_diagram&);
  void operator=(const voronoi_diagram&);
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI_DIAGRAM

/* voronoi_diagram.hpp
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
*/