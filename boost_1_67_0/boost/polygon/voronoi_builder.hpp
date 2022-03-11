// Boost.Polygon library voronoi_builder.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_BUILDER
#define BOOST_POLYGON_VORONOI_BUILDER

#include <algorithm>
#include <map>
#include <queue>
#include <utility>
#include <vector>

#include "detail/voronoi_ctypes.hpp"
#include "detail/voronoi_predicates.hpp"
#include "detail/voronoi_structures.hpp"

#include "voronoi_geometry_type.hpp"

namespace boost {
namespace polygon {
// GENERAL INFO:
// The sweepline algorithm implementation to compute Voronoi diagram of
// points and non-intersecting segments (excluding endpoints).
// Complexity - O(N*logN), memory usage - O(N), where N is the total number
// of input geometries.
//
// CONTRACT:
// 1) Input geometries should have integral (e.g. int32, int64) coordinate type.
// 2) Input geometries should not intersect except their endpoints.
//
// IMPLEMENTATION DETAILS:
// Each input point creates one input site. Each input segment creates three
// input sites: two for its endpoints and one for the segment itself (this is
// made to simplify output construction). All the site objects are constructed
// and sorted at the algorithm initialization step. Priority queue is used to
// dynamically hold circle events. At each step of the algorithm execution the
// leftmost event is retrieved by comparing the current site event and the
// topmost element from the circle event queue. STL map (red-black tree)
// container was chosen to hold state of the beach line. The keys of the map
// correspond to the neighboring sites that form a bisector and values map to
// the corresponding Voronoi edges in the output data structure.
template <typename T,
          typename CTT = detail::voronoi_ctype_traits<T>,
          typename VP = detail::voronoi_predicates<CTT> >
class voronoi_builder {
 public:
  typedef typename CTT::int_type int_type;
  typedef typename CTT::fpt_type fpt_type;

  voronoi_builder() : index_(0) {}

  // Each point creates a single site event.
  std::size_t insert_point(const int_type& x, const int_type& y) {
    site_events_.push_back(site_event_type(x, y));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SINGLE_POINT);
    return index_++;
  }

  // Each segment creates three site events that correspond to:
  //   1) the start point of the segment;
  //   2) the end point of the segment;
  //   3) the segment itself defined by its start point.
  std::size_t insert_segment(
      const int_type& x1, const int_type& y1,
      const int_type& x2, const int_type& y2) {
    // Set up start point site.
    point_type p1(x1, y1);
    site_events_.push_back(site_event_type(p1));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SEGMENT_START_POINT);

    // Set up end point site.
    point_type p2(x2, y2);
    site_events_.push_back(site_event_type(p2));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SEGMENT_END_POINT);

    // Set up segment site.
    if (point_comparison_(p1, p2)) {
      site_events_.push_back(site_event_type(p1, p2));
      site_events_.back().source_category(SOURCE_CATEGORY_INITIAL_SEGMENT);
    } else {
      site_events_.push_back(site_event_type(p2, p1));
      site_events_.back().source_category(SOURCE_CATEGORY_REVERSE_SEGMENT);
    }
    site_events_.back().initial_index(index_);
    return index_++;
  }

  // Run sweepline algorithm and fill output data structure.
  template <typename OUTPUT>
  void construct(OUTPUT* output) {
    // Init structures.
    output->_reserve(site_events_.size());
    init_sites_queue();
    init_beach_line(output);

    // The algorithm stops when there are no events to process.
    event_comparison_predicate event_comparison;
    while (!circle_events_.empty() ||
           !(site_event_iterator_ == site_events_.end())) {
      if (circle_events_.empty()) {
        process_site_event(output);
      } else if (site_event_iterator_ == site_events_.end()) {
        process_circle_event(output);
      } else {
        if (event_comparison(*site_event_iterator_,
                             circle_events_.top().first)) {
          process_site_event(output);
        } else {
          process_circle_event(output);
        }
      }
      while (!circle_events_.empty() &&
             !circle_events_.top().first.is_active()) {
        circle_events_.pop();
      }
    }
    beach_line_.clear();

    // Finish construction.
    output->_build();
  }

  void clear() {
    index_ = 0;
    site_events_.clear();
  }

 private:
  typedef detail::point_2d<int_type> point_type;
  typedef detail::site_event<int_type> site_event_type;
  typedef typename std::vector<site_event_type>::const_iterator
    site_event_iterator_type;
  typedef detail::circle_event<fpt_type> circle_event_type;
  typedef typename VP::template point_comparison_predicate<point_type>
    point_comparison_predicate;
  typedef typename VP::
    template event_comparison_predicate<site_event_type, circle_event_type>
    event_comparison_predicate;
  typedef typename VP::
    template circle_formation_predicate<site_event_type, circle_event_type>
    circle_formation_predicate_type;
  typedef void edge_type;
  typedef detail::beach_line_node_key<site_event_type> key_type;
  typedef detail::beach_line_node_data<edge_type, circle_event_type>
    value_type;
  typedef typename VP::template node_comparison_predicate<key_type>
    node_comparer_type;
  typedef std::map< key_type, value_type, node_comparer_type > beach_line_type;
  typedef typename beach_line_type::iterator beach_line_iterator;
  typedef std::pair<circle_event_type, beach_line_iterator> event_type;
  typedef struct {
    bool operator()(const event_type& lhs, const event_type& rhs) const {
      return predicate(rhs.first, lhs.first);
    }
    event_comparison_predicate predicate;
  } event_comparison_type;
  typedef detail::ordered_queue<event_type, event_comparison_type>
    circle_event_queue_type;
  typedef std::pair<point_type, beach_line_iterator> end_point_type;

  void init_sites_queue() {
    // Sort site events.
    std::sort(site_events_.begin(), site_events_.end(),
        event_comparison_predicate());

    // Remove duplicates.
    site_events_.erase(std::unique(
        site_events_.begin(), site_events_.end()), site_events_.end());

    // Index sites.
    for (std::size_t cur = 0; cur < site_events_.size(); ++cur) {
      site_events_[cur].sorted_index(cur);
    }

    // Init site iterator.
    site_event_iterator_ = site_events_.begin();
  }

  template <typename OUTPUT>
  void init_beach_line(OUTPUT* output) {
    if (site_events_.empty())
      return;
    if (site_events_.size() == 1) {
      // Handle single site event case.
      output->_process_single_site(site_events_[0]);
      ++site_event_iterator_;
    } else {
      int skip = 0;

      while (site_event_iterator_ != site_events_.end() &&
             VP::is_vertical(site_event_iterator_->point0(),
                             site_events_.begin()->point0()) &&
             VP::is_vertical(*site_event_iterator_)) {
        ++site_event_iterator_;
        ++skip;
      }

      if (skip == 1) {
        // Init beach line with the first two sites.
        init_beach_line_default(output);
      } else {
        // Init beach line with collinear vertical sites.
        init_beach_line_collinear_sites(output);
      }
    }
  }

  // Init beach line with the two first sites.
  // The first site is always a point.
  template <typename OUTPUT>
  void init_beach_line_default(OUTPUT* output) {
    // Get the first and the second site event.
    site_event_iterator_type it_first = site_events_.begin();
    site_event_iterator_type it_second = site_events_.begin();
    ++it_second;
    insert_new_arc(
        *it_first, *it_first, *it_second, beach_line_.end(), output);
    // The second site was already processed. Move the iterator.
    ++site_event_iterator_;
  }

  // Init beach line with collinear sites.
  template <typename OUTPUT>
  void init_beach_line_collinear_sites(OUTPUT* output) {
    site_event_iterator_type it_first = site_events_.begin();
    site_event_iterator_type it_second = site_events_.begin();
    ++it_second;
    while (it_second != site_event_iterator_) {
      // Create a new beach line node.
      key_type new_node(*it_first, *it_second);

      // Update the output.
      edge_type* edge = output->_insert_new_edge(*it_first, *it_second).first;

      // Insert a new bisector into the beach line.
      beach_line_.insert(beach_line_.end(),
          std::pair<key_type, value_type>(new_node, value_type(edge)));

      // Update iterators.
      ++it_first;
      ++it_second;
    }
  }

  void deactivate_circle_event(value_type* value) {
    if (value->circle_event()) {
      value->circle_event()->deactivate();
      value->circle_event(NULL);
    }
  }

  template <typename OUTPUT>
  void process_site_event(OUTPUT* output) {
    // Get next site event to process.
    site_event_type site_event = *site_event_iterator_;

    // Move site iterator.
    site_event_iterator_type last = site_event_iterator_ + 1;

    // If a new site is an end point of some segment,
    // remove temporary nodes from the beach line data structure.
    if (!site_event.is_segment()) {
      while (!end_points_.empty() &&
             end_points_.top().first == site_event.point0()) {
        beach_line_iterator b_it = end_points_.top().second;
        end_points_.pop();
        beach_line_.erase(b_it);
      }
    } else {
      while (last != site_events_.end() &&
             last->is_segment() && last->point0() == site_event.point0())
        ++last;
    }

    // Find the node in the binary search tree with left arc
    // lying above the new site point.
    key_type new_key(*site_event_iterator_);
    beach_line_iterator right_it = beach_line_.lower_bound(new_key);

    for (; site_event_iterator_ != last; ++site_event_iterator_) {
      site_event = *site_event_iterator_;
      beach_line_iterator left_it = right_it;

      // Do further processing depending on the above node position.
      // For any two neighboring nodes the second site of the first node
      // is the same as the first site of the second node.
      if (right_it == beach_line_.end()) {
        // The above arc corresponds to the second arc of the last node.
        // Move the iterator to the last node.
        --left_it;

        // Get the second site of the last node
        const site_event_type& site_arc = left_it->first.right_site();

        // Insert new nodes into the beach line. Update the output.
        right_it = insert_new_arc(
            site_arc, site_arc, site_event, right_it, output);

        // Add a candidate circle to the circle event queue.
        // There could be only one new circle event formed by
        // a new bisector and the one on the left.
        activate_circle_event(left_it->first.left_site(),
                              left_it->first.right_site(),
                              site_event, right_it);
      } else if (right_it == beach_line_.begin()) {
        // The above arc corresponds to the first site of the first node.
        const site_event_type& site_arc = right_it->first.left_site();

        // Insert new nodes into the beach line. Update the output.
        left_it = insert_new_arc(
            site_arc, site_arc, site_event, right_it, output);

        // If the site event is a segment, update its direction.
        if (site_event.is_segment()) {
          site_event.inverse();
        }

        // Add a candidate circle to the circle event queue.
        // There could be only one new circle event formed by
        // a new bisector and the one on the right.
        activate_circle_event(site_event, right_it->first.left_site(),
            right_it->first.right_site(), right_it);
        right_it = left_it;
      } else {
        // The above arc corresponds neither to the first,
        // nor to the last site in the beach line.
        const site_event_type& site_arc2 = right_it->first.left_site();
        const site_event_type& site3 = right_it->first.right_site();

        // Remove the candidate circle from the event queue.
        deactivate_circle_event(&right_it->second);
        --left_it;
        const site_event_type& site_arc1 = left_it->first.right_site();
        const site_event_type& site1 = left_it->first.left_site();

        // Insert new nodes into the beach line. Update the output.
        beach_line_iterator new_node_it =
            insert_new_arc(site_arc1, site_arc2, site_event, right_it, output);

        // Add candidate circles to the circle event queue.
        // There could be up to two circle events formed by
        // a new bisector and the one on the left or right.
        activate_circle_event(site1, site_arc1, site_event, new_node_it);

        // If the site event is a segment, update its direction.
        if (site_event.is_segment()) {
          site_event.inverse();
        }
        activate_circle_event(site_event, site_arc2, site3, right_it);
        right_it = new_node_it;
      }
    }
  }

  // In general case circle event is made of the three consecutive sites
  // that form two bisectors in the beach line data structure.
  // Let circle event sites be A, B, C, two bisectors that define
  // circle event are (A, B), (B, C). During circle event processing
  // we remove (A, B), (B, C) and insert (A, C). As beach line comparison
  // works correctly only if one of the nodes is a new one we remove
  // (B, C) bisector and change (A, B) bisector to the (A, C). That's
  // why we use const_cast there and take all the responsibility that
  // map data structure keeps correct ordering.
  template <typename OUTPUT>
  void process_circle_event(OUTPUT* output) {
    // Get the topmost circle event.
    const event_type& e = circle_events_.top();
    const circle_event_type& circle_event = e.first;
    beach_line_iterator it_first = e.second;
    beach_line_iterator it_last = it_first;

    // Get the C site.
    site_event_type site3 = it_first->first.right_site();

    // Get the half-edge corresponding to the second bisector - (B, C).
    edge_type* bisector2 = it_first->second.edge();

    // Get the half-edge corresponding to the first bisector - (A, B).
    --it_first;
    edge_type* bisector1 = it_first->second.edge();

    // Get the A site.
    site_event_type site1 = it_first->first.left_site();

    if (!site1.is_segment() && site3.is_segment() &&
        site3.point1() == site1.point0()) {
      site3.inverse();
    }

    // Change the (A, B) bisector node to the (A, C) bisector node.
    const_cast<key_type&>(it_first->first).right_site(site3);

    // Insert the new bisector into the beach line.
    it_first->second.edge(output->_insert_new_edge(
        site1, site3, circle_event, bisector1, bisector2).first);

    // Remove the (B, C) bisector node from the beach line.
    beach_line_.erase(it_last);
    it_last = it_first;

    // Pop the topmost circle event from the event queue.
    circle_events_.pop();

    // Check new triplets formed by the neighboring arcs
    // to the left for potential circle events.
    if (it_first != beach_line_.begin()) {
      deactivate_circle_event(&it_first->second);
      --it_first;
      const site_event_type& site_l1 = it_first->first.left_site();
      activate_circle_event(site_l1, site1, site3, it_last);
    }

    // Check the new triplet formed by the neighboring arcs
    // to the right for potential circle events.
    ++it_last;
    if (it_last != beach_line_.end()) {
      deactivate_circle_event(&it_last->second);
      const site_event_type& site_r1 = it_last->first.right_site();
      activate_circle_event(site1, site3, site_r1, it_last);
    }
  }

  // Insert new nodes into the beach line. Update the output.
  template <typename OUTPUT>
  beach_line_iterator insert_new_arc(
      const site_event_type& site_arc1, const site_event_type &site_arc2,
      const site_event_type& site_event, beach_line_iterator position,
      OUTPUT* output) {
    // Create two new bisectors with opposite directions.
    key_type new_left_node(site_arc1, site_event);
    key_type new_right_node(site_event, site_arc2);

    // Set correct orientation for the first site of the second node.
    if (site_event.is_segment()) {
      new_right_node.left_site().inverse();
    }

    // Update the output.
    std::pair<edge_type*, edge_type*> edges =
        output->_insert_new_edge(site_arc2, site_event);
    position = beach_line_.insert(position,
        typename beach_line_type::value_type(
            new_right_node, value_type(edges.second)));

    if (site_event.is_segment()) {
      // Update the beach line with temporary bisector, that will
      // disappear after processing site event corresponding to the
      // second endpoint of the segment site.
      key_type new_node(site_event, site_event);
      new_node.right_site().inverse();
      position = beach_line_.insert(position,
          typename beach_line_type::value_type(new_node, value_type(NULL)));

      // Update the data structure that holds temporary bisectors.
      end_points_.push(std::make_pair(site_event.point1(), position));
    }

    position = beach_line_.insert(position,
        typename beach_line_type::value_type(
            new_left_node, value_type(edges.first)));

    return position;
  }

  // Add a new circle event to the event queue.
  // bisector_node corresponds to the (site2, site3) bisector.
  void activate_circle_event(const site_event_type& site1,
                             const site_event_type& site2,
                             const site_event_type& site3,
                             beach_line_iterator bisector_node) {
    circle_event_type c_event;
    // Check if the three input sites create a circle event.
    if (circle_formation_predicate_(site1, site2, site3, c_event)) {
      // Add the new circle event to the circle events queue.
      // Update bisector's circle event iterator to point to the
      // new circle event in the circle event queue.
      event_type& e = circle_events_.push(
          std::pair<circle_event_type, beach_line_iterator>(
              c_event, bisector_node));
      bisector_node->second.circle_event(&e.first);
    }
  }

 private:
  point_comparison_predicate point_comparison_;
  struct end_point_comparison {
    bool operator() (const end_point_type& end1,
                     const end_point_type& end2) const {
      return point_comparison(end2.first, end1.first);
    }
    point_comparison_predicate point_comparison;
  };

  std::vector<site_event_type> site_events_;
  site_event_iterator_type site_event_iterator_;
  std::priority_queue< end_point_type, std::vector<end_point_type>,
                       end_point_comparison > end_points_;
  circle_event_queue_type circle_events_;
  beach_line_type beach_line_;
  circle_formation_predicate_type circle_formation_predicate_;
  std::size_t index_;

  // Disallow copy constructor and operator=
  voronoi_builder(const voronoi_builder&);
  void operator=(const voronoi_builder&);
};

typedef voronoi_builder<detail::int32> default_voronoi_builder;
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI_BUILDER

/* voronoi_builder.hpp
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
*/