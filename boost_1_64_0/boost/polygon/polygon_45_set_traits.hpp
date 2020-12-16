/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_SET_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_45_SET_TRAITS_HPP
namespace boost { namespace polygon{

  //default definition of polygon 45 set traits works for any model of polygon 45, polygon 45 with holes or any vector or list thereof
  template <typename T>
  struct polygon_45_set_traits {
    typedef typename get_coordinate_type<T, typename geometry_concept<T>::type >::type coordinate_type;
    typedef typename get_iterator_type<T>::type iterator_type;
    typedef T operator_arg_type;

    static inline iterator_type begin(const T& polygon_set) {
      return get_iterator_type<T>::begin(polygon_set);
    }

    static inline iterator_type end(const T& polygon_set) {
      return get_iterator_type<T>::end(polygon_set);
    }

    static inline bool clean(const T& ) { return false; }

    static inline bool sorted(const T& ) { return false; }
  };

  template <typename T>
  struct is_45_polygonal_concept { typedef gtl_no type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_concept> { typedef gtl_yes type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_with_holes_concept> { typedef gtl_yes type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_polygon_45_set_type {
    typedef typename is_45_polygonal_concept<typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_polygon_45_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename is_45_polygonal_concept<typename geometry_concept<std::list<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_polygon_45_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename is_45_polygonal_concept<typename geometry_concept<std::vector<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_45_set_type {
    typedef typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_45_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<std::list<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_45_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<std::vector<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  bool fracture_holes_45_by_concept() { return false; }
  template <>
  inline bool fracture_holes_45_by_concept<polygon_45_concept>() { return true; }

  template <typename T, typename iT>
  void get_45_polygons_T(T& t, iT begin, iT end) {
    typedef typename polygon_45_set_traits<T>::coordinate_type Unit;
    typedef typename geometry_concept<typename T::value_type>::type CType;
    typename polygon_45_formation<Unit>::Polygon45Formation pf(fracture_holes_45_by_concept<CType>());
    //std::cout << "FORMING POLYGONS\n";
    pf.scan(t, begin, end);
  }

  template <typename T>
  struct polygon_45_set_mutable_traits {};
  template <typename T>
  struct polygon_45_set_mutable_traits<std::list<T> > {
    template <typename input_iterator_type>
    static inline void set(std::list<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      polygon_45_set_data<typename polygon_45_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(std::distance(input_begin, input_end));
      ps.insert(input_begin, input_end);
      ps.sort();
      ps.clean();
      get_45_polygons_T(polygon_set, ps.begin(), ps.end());
    }
  };
  template <typename T>
  struct polygon_45_set_mutable_traits<std::vector<T> > {
    template <typename input_iterator_type>
    static inline void set(std::vector<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      size_t num_ele = std::distance(input_begin, input_end);
      polygon_set.reserve(num_ele);
      polygon_45_set_data<typename polygon_45_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(num_ele);
      ps.insert(input_begin, input_end);
      ps.sort();
      ps.clean();
      get_45_polygons_T(polygon_set, ps.begin(), ps.end());
    }
  };

  template <typename T>
  struct polygon_45_set_mutable_traits<polygon_45_set_data<T> > {
    template <typename input_iterator_type>
    static inline void set(polygon_45_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.set(input_begin, input_end);
    }
  };
  template <typename T>
  struct polygon_45_set_traits<polygon_45_set_data<T> > {
    typedef typename polygon_45_set_data<T>::coordinate_type coordinate_type;
    typedef typename polygon_45_set_data<T>::iterator_type iterator_type;
    typedef typename polygon_45_set_data<T>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.end();
    }

    static inline bool clean(const polygon_45_set_data<T>& polygon_set) { polygon_set.clean(); return true; }

    static inline bool sorted(const polygon_45_set_data<T>& polygon_set) { polygon_set.sort(); return true; }

  };
}
}
#endif

/* polygon_45_set_traits.hpp
1XxFX0m/sCHG6YVIHYLDjd06mZ7p7/Hy90Ey/3mSGyjCav0+kPXbWX5/60QhNwQ38Wh/TQ65yFhDfQKCwqN4Jjfrz09qn0vbKu/j7y7P5nVGZZvSaeYZEtaft+qTSoiHgEN4wjWYZIoxdlnPjaDZVlj/oTowtH+aPNMzQHkxv8V7VKSdQszPkuWyl+Gs2m5CXvltW5ZjBVZWzgmNzMvRL4znwpX/h8UMCGBlZ+75L9vLoHlPSvrnT+VZOtnG0uVlVJ+TYyQepbJ4TtNUmSGUQpRoypkS/D7VxGI5ZAkyc27T1l/7fPHv5yOYIHXpJNvjO7I9plAXba4S2UAMD1T9kTwA2ues9+aX2EC5JzAL8/MPv6bqPNWH48w7geQSycIxbn/zzD0vOSjCcv2SY0LykFiuzx+V9WlnPk7ttco/JvnG1ONUkqz/iNrG7kPSHVPTnAdnjxvdksvqlBx3TOtsv0xvkNX+fLaAPAMn7VcUPZUcEi3U9svwQVOlDbtlug0zbjNy4kibWe4Dzlb7yGbNPqB0r7Zq00RZRtO5Yb322C/rIEjaxIlrtr20l5dhW40JDNdbHh/6FpQNUPar0aYcKq3N7cJupZedKzTEsHv9sf1LaaObsn9pn0/0lYPl4xwMh/eQOnADyCKHgPbonu7ZX3sbz3ye8P39HCvabfeWVTunqedYc667/lbnzAdWzzunyrF5QGAMp/zMPaNo+1m4jJ9dtP2MXNbfmZTVZ+Gy+g6krD4LZ/tZway/2ymrzwTafrbw9b3DKavvRsrqM6gZPTt62fBs4Y5+3RZ882EnrxGuDU/27R6SmPEzq7af7cz6s6P37KhTDvneKd9DdRRP/l1VYhIu5uCeL17C6ngFa+PP2ASvY1u8iV3xFvbG29gfU3Ew3sMR+AAn4iOcjmk4H5/iUnyOa/Alrkd2TGKpAHejPR7APJiE+fBHLIDn0QGvYmG8hY54H50wDZ3xFZZAJcbHFQuhGzqjO5bCMlgePfBNLI9e6Ik+WAnvGe5Ry/cX+V5D+xniWVaj8gmT9EyxWAaHYjWMw4Y4HMNxJI7AUTgBx+BHOA6X4HhcixNwE07EozgJT+GHeBOn4iOchkWo1HSsgvFYA2djM5yDHfEj7IZzMQznYSzOx1m4AOfhJ/g5JuBuXIz7cAkex6V4FpfhK1yOrCO7z9EVV6EnrsZGuAb9cS32xq8wCtfhSFyP43ADzsWNuBQ34S7cgt/hNjyF2zEVd+Ej3I052Q/3YlH8Fj3wO6yE+/At3I+N8AC2xu+xOx7EQDyM0fgDjsAjOBmTcBYexU/wGK7C47gGk3EdnsAdeBIP4o/4I57Cy/gT3sHTmIbnMD/b0Xn0xAv4Jl7CFngFI/Eq6vAajsbrOBVv4Cz8Bdfir7gVb+P3eAcPYSoaY6fl+xl0puisYqfrsB/mwrpYA+thE6yPnfBtVGPHlenIdzGdVex4oBxH+qEH9semOABbYxiG4CAchJE4EqPwQ9ThChyMa1CPW3EI5mR+Q7E0xmE5HIGVcSQ2xFHYAcdiZ3wf5Rkf+Y7Ftir11j7jM0HqPQmd8QOshH/Favgh+uFUjMS/YSzG4yicgeNxJi7CWbgc5+Bu/AjP4Vy8gn/H57hAlmshFsaPsTguw1hcjvG4AufiZ7gUV+EKXI2yfuW7F21lY/36y/L1RHf8C3bH3hiNfdAU+5gi0+kk09HGPvrJdtIZXbELvoFdsRF2w3ewu0yPY6l8J+JYIuedCvzb0/T+Ezlu1sBSWBPLYx18E+tiTayH9bE+tsK3sTc2wCBshDpsjNOwCc7FpvgxNscN2AK/xtaYjG0wBX3xBnaV41o3zJGT5UAHfBfLYw/0RH8=
*/