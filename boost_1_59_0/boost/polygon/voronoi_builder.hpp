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
  struct event_comparison_type {
    bool operator()(const event_type& lhs, const event_type& rhs) const {
      return predicate(rhs.first, lhs.first);
    }
    event_comparison_predicate predicate;
  };
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