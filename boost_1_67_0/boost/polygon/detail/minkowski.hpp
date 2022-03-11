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