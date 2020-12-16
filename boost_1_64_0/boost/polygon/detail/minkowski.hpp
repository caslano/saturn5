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
C7ojsNEC++Lz5Rs5uftYXrOyBNs98ENtlHeex1fsCrhdIXcRfZYh2nZ6C/Ja7kIbnlJ8I8JVWBByR/dFJ/ZJsLwgUm8DctQp1lPsD7kWuAuKcdhG8v8bgd8HfJ4nGArHqKO/fcq/eQvifmLejfjtfvzmC5vNRdderAd+VzzuKiguDmJJREQvpesqOHx9avR7FV9H+h21dxP0bqV+cP48bfux3xp4nYGH/ebGtgp1830Rv3lC2D9ht4+Ob28ljRxPsavJH1E/prXAj0uFH6P4pgR+20z/Y/58EHj00xoFXv414psNm/WNzMMfw3n4HXl8dsBWB73GaH+nhyeVBYPob567sEXjzzwOG7ndKezHydge6YP/+OPHfUERzrJBd+wLrTiZlmz9+yCmr8iH4QXYJfM8hVFfpXQdB7L12HajMUJc7KuNXN+/2IfrianRtP8PYLvzOfd/MPtjINudH293LJetYB7OH/Fvhylqyfkrnq+e+TKYrzfz1STkK3TP8wfdgrCFfPsx3zh27FDmG8J89Qn56P/DC4IYQLy6609xXc9cXZmrC3OlBbbCVez+01z3djAiZV++f5mA7TFw2RNyuSuK3JGDBgPBi134z6yHIbwHr4WJsyYyPtO5jSbLIlfLyG80Ng7IiPst8hYgVyRP8PCAub5G+mNX/hjx7uz7wfx+oeqE/ijz/Z0xvJy5ejBXN+aqbwFXEP+LG6gW8U1gvrSORqRMYr6J2B6nc5bgEyzhlvTJ3MdHoy2+u6N3Lgm/rmHut/i89hpzOxdthtvva7ozDPEavb9gA53beoD7KWw08O5bxOc2PhfWon70DqsY7JHrUuzcNp1tz+nM5zZeQ9cL8gnoBYLCdqzA8/sWBz3mzayrKHoJiF7n2I9j1Nq6FWpt3b1xa+tKQ83XGXqbsFEJsCwT268J26M5xusP2WczMfBwIcEnvyN+iazve7KPiZkXwKiP38Zv6l4m4uN6+DcbfjqJ7pcifonWX4P6fI/jiud4ne9b+JYldoGG38X18Cn2ff+4/OKnacyG4n0fdHtxDpHXw5aPW7l+Uh4z+dsbkTKG+Udjexb1beHNvm8MwNa5t7ausxP/Ni/oL41MptguM+/6U7bLx8fTQmzP0ZhkuyKHD9vRqQU+yOoNrjJf9P6R7dvAxwcfipHbTyN2v8zzmC5GpOSwHdnYXuiD/5RF7BDzwZZ8w8y0Z81Oze3ZlMgevmddD3+shC29aE5VJu9f0LeYDjdJfRD+zEjj8z5fBwdyP/LNfkQ60PLrnbT/35GLvj6Si16Y+sCEm365eOSIvI0Pt322+nLrufk/9dw8uqaJYw4ci6htI9c0fdMmmov+LSRhGyFZj2MD8EMCvU2s9ytk5N6lbdx751ivcwK9daz3EWRHyI+Zz2bwXJvn4Db8TxvIHqx3JNerwFbL9Y7lvzth83K98bx2cgIk4ftApkM6IHeGnAw5HHI/yH0g94ecDTkFMgw5FbISchqv1TsQcgmkE/JbyGqD55iQHubvgu0E5s9g/j7MvwtkGmQ/yJ6Q/SF35Rz/QZCDIEdBDoYcCzkEcjLkUF6zNxxyJqQd0gWZBVkEuQekO3p9YP/xXJDniOmG9N+M6dF6CwwUnm9NYfu3wzaH653O9i+D7MJrS7tDnsP+Ww65B+T5kOMhV0BO5LVwkyAvYfsvZbvyaWO+wczXAVse81XweKiE7AR5FGRXyCWQxLsUMgPyWEgb5AmQu0GeDDkQ8hRIc81FDfNkJFhz4WMeP2QPyEWQ6ZBhyN6QZZDRtbk8x+K5V4Vam3s7t3MnZBfIu9nO+yB3gXyAj6NVkIMgH4YcAlkXs5PnVZBdE9j5GLf/OGR7yCc=
*/