/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
namespace boost { namespace polygon { namespace detail {

template <typename coordinate_type>
struct minkowski_offset {
  typedef point_data<coordinate_type> point;
  typedef polygon_set_data<coordinate_type> polygon_set;
  typedef polygon_with_holes_data<coordinate_type> polygon;
  typedef std::pair<point, point> edge;

  static void convolve_two_segments(std::vector<point>& figure, const edge& a, const edge& b) {
    figure.clear();
    figure.push_back(point(a.first));
    figure.push_back(point(a.first));
    figure.push_back(point(a.second));
    figure.push_back(point(a.second));
    convolve(figure[0], b.second);
    convolve(figure[1], b.first);
    convolve(figure[2], b.first);
    convolve(figure[3], b.second);
  }

  template <typename itrT1, typename itrT2>
  static void convolve_two_point_sequences(polygon_set& result, itrT1 ab, itrT1 ae, itrT2 bb, itrT2 be) {
    if(ab == ae || bb == be)
      return;
    point first_a = *ab;
    point prev_a = *ab;
    std::vector<point> vec;
    polygon poly;
    ++ab;
    for( ; ab != ae; ++ab) {
      point first_b = *bb;
      point prev_b = *bb;
      itrT2 tmpb = bb;
      ++tmpb;
      for( ; tmpb != be; ++tmpb) {
        convolve_two_segments(vec, std::make_pair(prev_b, *tmpb), std::make_pair(prev_a, *ab));
        set_points(poly, vec.begin(), vec.end());
        result.insert(poly);
        prev_b = *tmpb;
      }
      prev_a = *ab;
    }
  }

  template <typename itrT>
  static void convolve_point_sequence_with_polygons(polygon_set& result, itrT b, itrT e, const std::vector<polygon>& polygons) {
    for(std::size_t i = 0; i < polygons.size(); ++i) {
      convolve_two_point_sequences(result, b, e, begin_points(polygons[i]), end_points(polygons[i]));
      for(typename polygon_with_holes_traits<polygon>::iterator_holes_type itrh = begin_holes(polygons[i]);
          itrh != end_holes(polygons[i]); ++itrh) {
        convolve_two_point_sequences(result, b, e, begin_points(*itrh), end_points(*itrh));
      }
    }
  }

  static void convolve_two_polygon_sets(polygon_set& result, const polygon_set& a, const polygon_set& b) {
    result.clear();
    std::vector<polygon> a_polygons;
    std::vector<polygon> b_polygons;
    a.get(a_polygons);
    b.get(b_polygons);
    for(std::size_t ai = 0; ai < a_polygons.size(); ++ai) {
      convolve_point_sequence_with_polygons(result, begin_points(a_polygons[ai]),
                                            end_points(a_polygons[ai]), b_polygons);
      for(typename polygon_with_holes_traits<polygon>::iterator_holes_type itrh = begin_holes(a_polygons[ai]);
          itrh != end_holes(a_polygons[ai]); ++itrh) {
        convolve_point_sequence_with_polygons(result, begin_points(*itrh),
                                              end_points(*itrh), b_polygons);
      }
      for(std::size_t bi = 0; bi < b_polygons.size(); ++bi) {
        polygon tmp_poly = a_polygons[ai];
        result.insert(convolve(tmp_poly, *(begin_points(b_polygons[bi]))));
        tmp_poly = b_polygons[bi];
        result.insert(convolve(tmp_poly, *(begin_points(a_polygons[ai]))));
      }
    }
  }
};

}
  template<typename T>
  inline polygon_set_data<T>&
  polygon_set_data<T>::resize(coordinate_type resizing, bool corner_fill_arc, unsigned int num_circle_segments) {
    using namespace ::boost::polygon::operators;
    if(!corner_fill_arc) {
      if(resizing < 0)
        return shrink(-resizing);
      if(resizing > 0)
        return bloat(resizing);
      return *this;
    }
    if(resizing == 0) return *this;
    if(empty()) return *this;
    if(num_circle_segments < 3) num_circle_segments = 4;
    rectangle_data<coordinate_type> rect;
    extents(rect);
    if(resizing < 0) {
      ::boost::polygon::bloat(rect, 10);
      (*this) = rect - (*this); //invert
    }
    //make_arc(std::vector<point_data< T> >& return_points,
    //point_data< double> start, point_data< double>  end,
    //point_data< double> center,  double r, unsigned int num_circle_segments)
    std::vector<point_data<coordinate_type> > circle;
    point_data<double> center(0.0, 0.0), start(0.0, (double)resizing);
    make_arc(circle, start, start, center, std::abs((double)resizing),
             num_circle_segments);
    polygon_data<coordinate_type> poly;
    set_points(poly, circle.begin(), circle.end());
    polygon_set_data<coordinate_type> offset_set;
    offset_set += poly;
    polygon_set_data<coordinate_type> result;
    detail::minkowski_offset<coordinate_type>::convolve_two_polygon_sets
      (result, *this, offset_set);
    if(resizing < 0) {
      result = result & rect;//eliminate overhang
      result = result ^ rect;//invert
    }
    *this = result;
    return *this;
  }

}}

/* minkowski.hpp
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
*/