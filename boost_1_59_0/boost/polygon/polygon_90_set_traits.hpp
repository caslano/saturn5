/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_SET_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_90_SET_TRAITS_HPP
namespace boost { namespace polygon{

  struct polygon_90_set_concept {};

  template <typename T, typename T2>
  struct traits_by_concept {};
  template <typename T>
  struct traits_by_concept<T, coordinate_concept> { typedef coordinate_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, interval_concept> { typedef interval_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, point_concept> { typedef point_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, rectangle_concept> { typedef rectangle_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, segment_concept> { typedef segment_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_90_concept> { typedef polygon_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_90_with_holes_concept> { typedef polygon_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_45_concept> { typedef polygon_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_45_with_holes_concept> { typedef polygon_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_concept> { typedef polygon_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_with_holes_concept> { typedef polygon_traits<T> type; };

  struct polygon_45_set_concept;
  struct polygon_set_concept;
  template <typename T>
  struct polygon_90_set_traits;
  template <typename T>
  struct polygon_45_set_traits;
  template <typename T>
  struct polygon_set_traits;
  template <typename T>
  struct traits_by_concept<T, polygon_90_set_concept> { typedef polygon_90_set_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_45_set_concept> { typedef polygon_45_set_traits<T> type; };
  template <typename T>
  struct traits_by_concept<T, polygon_set_concept> { typedef polygon_set_traits<T> type; };

  template <typename T, typename T2>
  struct get_coordinate_type {
    typedef typename traits_by_concept<T, T2>::type traits_type;
    typedef typename traits_type::coordinate_type type;
  };
  //want to prevent recursive template definition syntax errors, so duplicate get_coordinate_type
  template <typename T, typename T2>
  struct get_coordinate_type_2 {
    typedef typename traits_by_concept<T, T2>::type traits_type;
    typedef typename traits_type::coordinate_type type;
  };
  template <typename T>
  struct get_coordinate_type<T, undefined_concept> {
    typedef typename get_coordinate_type_2<typename std::iterator_traits
                                           <typename T::iterator>::value_type,
                                           typename geometry_concept<typename std::iterator_traits
                                                                     <typename T::iterator>::value_type>::type>::type type; };

  template <typename T, typename T2>
  struct get_iterator_type_2 {
    typedef const T* type;
    static type begin(const T& t) { return &t; }
    static type end(const T& t) { const T* tp = &t; ++tp; return tp; }
  };
  template <typename T>
  struct get_iterator_type {
    typedef get_iterator_type_2<T, typename geometry_concept<T>::type> indirect_type;
    typedef typename indirect_type::type type;
    static type begin(const T& t) { return indirect_type::begin(t); }
    static type end(const T& t) { return indirect_type::end(t); }
  };
  template <typename T>
  struct get_iterator_type_2<T, undefined_concept> {
    typedef typename T::const_iterator type;
    static type begin(const T& t) { return t.begin(); }
    static type end(const T& t) { return t.end(); }
  };

//   //helpers for allowing polygon 45 and containers of polygon 45 to behave interchangably in polygon_45_set_traits
//   template <typename T, typename T2>
//   struct get_coordinate_type_45 {};
//   template <typename T, typename T2>
//   struct get_coordinate_type_2_45 {};
//   template <typename T>
//   struct get_coordinate_type_45<T, void> {
//     typedef typename get_coordinate_type_2_45< typename T::value_type, typename geometry_concept<typename T::value_type>::type >::type type; };
//   template <typename T>
//   struct get_coordinate_type_45<T, polygon_45_concept> { typedef typename polygon_traits<T>::coordinate_type type; };
//   template <typename T>
//   struct get_coordinate_type_45<T, polygon_45_with_holes_concept> { typedef typename polygon_traits<T>::coordinate_type type; };
//   template <typename T>
//   struct get_coordinate_type_2_45<T, polygon_45_concept> { typedef typename polygon_traits<T>::coordinate_type type; };
//   template <typename T>
//   struct get_coordinate_type_2_45<T, polygon_45_with_holes_concept> { typedef typename polygon_traits<T>::coordinate_type type; };
//   template <typename T, typename T2>
//   struct get_iterator_type_45 {};
//   template <typename T>
//   struct get_iterator_type_45<T, void> {
//     typedef typename T::const_iterator type;
//     static type begin(const T& t) { return t.begin(); }
//     static type end(const T& t) { return t.end(); }
//   };
//   template <typename T>
//   struct get_iterator_type_45<T, polygon_45_concept> {
//     typedef const T* type;
//     static type begin(const T& t) { return &t; }
//     static type end(const T& t) { const T* tp = &t; ++tp; return tp; }
//   };
//   template <typename T>
//   struct get_iterator_type_45<T, polygon_45_with_holes_concept> {
//     typedef const T* type;
//     static type begin(const T& t) { return &t; }
//     static type end(const T& t) { const T* tp = &t; ++tp; return tp; }
//   };
//   template <typename T>
//   struct get_iterator_type_45<T, polygon_90_set_concept> {
//     typedef const T* type;
//     static type begin(const T& t) { return &t; }
//     static type end(const T& t) { const T* tp = &t; ++tp; return tp; }
//   };

  template <typename T>
  struct polygon_90_set_traits {
    typedef typename get_coordinate_type<T, typename geometry_concept<T>::type >::type coordinate_type;
    typedef get_iterator_type<T> indirection_type;
    typedef typename get_iterator_type<T>::type iterator_type;
    typedef T operator_arg_type;

    static inline iterator_type begin(const T& polygon_set) {
      return indirection_type::begin(polygon_set);
    }

    static inline iterator_type end(const T& polygon_set) {
      return indirection_type::end(polygon_set);
    }

    static inline orientation_2d orient(const T&) { return HORIZONTAL; }

    static inline bool clean(const T&) { return false; }

    static inline bool sorted(const T&) { return false; }
  };

  template <typename T>
  struct is_manhattan_polygonal_concept { typedef gtl_no type; };
  template <>
  struct is_manhattan_polygonal_concept<rectangle_concept> { typedef gtl_yes type; };
  template <>
  struct is_manhattan_polygonal_concept<polygon_90_concept> { typedef gtl_yes type; };
  template <>
  struct is_manhattan_polygonal_concept<polygon_90_with_holes_concept> { typedef gtl_yes type; };
  template <>
  struct is_manhattan_polygonal_concept<polygon_90_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_polygon_90_set_type {
    typedef typename is_manhattan_polygonal_concept<typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_polygon_90_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename is_manhattan_polygonal_concept<typename geometry_concept<std::list<T> >::type>::type,
      typename is_manhattan_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_polygon_90_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename is_manhattan_polygonal_concept<typename geometry_concept<std::vector<T> >::type>::type,
      typename is_manhattan_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_90_set_type {
    typedef typename gtl_same_type<polygon_90_set_concept, typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_90_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_90_set_concept, typename geometry_concept<std::list<T> >::type>::type,
      typename is_manhattan_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_90_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_90_set_concept, typename geometry_concept<std::vector<T> >::type>::type,
      typename is_manhattan_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

//   //specialization for rectangle, polygon_90 and polygon_90_with_holes types
//   template <typename T>
//   struct polygon_90_set_traits
//     typedef typename geometry_concept<T>::type concept_type;
//     typedef typename get_coordinate_type<T, concept_type>::type coordinate_type;
//     typedef iterator_geometry_to_set<concept_type, T> iterator_type;
//     typedef T operator_arg_type;

//     static inline iterator_type begin(const T& polygon_set) {
//       return iterator_geometry_to_set<concept_type, T>(polygon_set, LOW, HORIZONTAL);
//     }

//     static inline iterator_type end(const T& polygon_set) {
//       return iterator_geometry_to_set<concept_type, T>(polygon_set, HIGH, HORIZONTAL);
//     }

//     static inline orientation_2d orient(const T& polygon_set) { return HORIZONTAL; }

//     static inline bool clean(const T& polygon_set) { return false; }

//     static inline bool sorted(const T& polygon_set) { return false; }

//   };

//   //specialization for containers of recangle, polygon_90, polygon_90_with_holes
//   template <typename T>
//   struct polygon_90_set_traits<T, typename is_manhattan_polygonal_concept<typename std::iterator_traits<typename T::iterator>::value_type>::type> {
//     typedef typename std::iterator_traits<typename T::iterator>::value_type geometry_type;
//     typedef typename geometry_concept<geometry_type>::type concept_type;
//     typedef typename get_coordinate_type<geometry_type, concept_type>::type coordinate_type;
//     typedef iterator_geometry_range_to_set<concept_type, typename T::const_iterator> iterator_type;
//     typedef T operator_arg_type;

//     static inline iterator_type begin(const T& polygon_set) {
//       return iterator_type(polygon_set.begin(), HORIZONTAL);
//     }

//     static inline iterator_type end(const T& polygon_set) {
//       return iterator_type(polygon_set.end(), HORIZONTAL);
//     }

//     static inline orientation_2d orient(const T& polygon_set) { return HORIZONTAL; }

//     static inline bool clean(const T& polygon_set) { return false; }

//     static inline bool sorted(const T& polygon_set) { return false; }

//   };

  //get dispatch functions
  template <typename output_container_type, typename pst>
  void get_90_dispatch(output_container_type& output, const pst& ps,
                       orientation_2d orient, rectangle_concept ) {
    form_rectangles(output, ps.begin(), ps.end(), orient, rectangle_concept());
  }

  template <typename output_container_type, typename pst>
  void get_90_dispatch(output_container_type& output, const pst& ps,
                       orientation_2d orient, polygon_90_concept tag) {
    get_polygons(output, ps.begin(), ps.end(), orient, true, tag);
  }

  template <typename output_container_type, typename pst>
  void get_90_dispatch(output_container_type& output, const pst& ps,
                       orientation_2d orient, polygon_90_with_holes_concept tag) {
    get_polygons(output, ps.begin(), ps.end(), orient, false, tag);
  }

  //by default works with containers of rectangle, polygon or polygon with holes
  //must be specialized to work with anything else
  template <typename T>
  struct polygon_90_set_mutable_traits {};
  template <typename T>
  struct polygon_90_set_mutable_traits<std::list<T> > {
    typedef typename geometry_concept<T>::type concept_type;
    template <typename input_iterator_type>
    static inline void set(std::list<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end, orientation_2d orient) {
      polygon_set.clear();
      polygon_90_set_data<typename polygon_90_set_traits<std::list<T> >::coordinate_type> ps(orient);
      ps.reserve(std::distance(input_begin, input_end));
      ps.insert(input_begin, input_end, orient);
      ps.clean();
      get_90_dispatch(polygon_set, ps, orient, concept_type());
    }
  };
  template <typename T>
  struct polygon_90_set_mutable_traits<std::vector<T> > {
    typedef typename geometry_concept<T>::type concept_type;
    template <typename input_iterator_type>
    static inline void set(std::vector<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end, orientation_2d orient) {
      polygon_set.clear();
      size_t num_ele = std::distance(input_begin, input_end);
      polygon_set.reserve(num_ele);
      polygon_90_set_data<typename polygon_90_set_traits<std::list<T> >::coordinate_type> ps(orient);
      ps.reserve(num_ele);
      ps.insert(input_begin, input_end, orient);
      ps.clean();
      get_90_dispatch(polygon_set, ps, orient, concept_type());
    }
  };

  template <typename T>
  struct polygon_90_set_mutable_traits<polygon_90_set_data<T> > {

    template <typename input_iterator_type>
    static inline void set(polygon_90_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end,
                           orientation_2d orient) {
      polygon_set.clear();
      polygon_set.reserve(std::distance(input_begin, input_end));
      polygon_set.insert(input_begin, input_end, orient);
    }

  };

  template <typename T>
  struct polygon_90_set_traits<polygon_90_set_data<T> > {
    typedef typename polygon_90_set_data<T>::coordinate_type coordinate_type;
    typedef typename polygon_90_set_data<T>::iterator_type iterator_type;
    typedef typename polygon_90_set_data<T>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_90_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const polygon_90_set_data<T>& polygon_set) {
      return polygon_set.end();
    }

    static inline orientation_2d orient(const polygon_90_set_data<T>& polygon_set) { return polygon_set.orient(); }

    static inline bool clean(const polygon_90_set_data<T>& polygon_set) { polygon_set.clean(); return true; }

    static inline bool sorted(const polygon_90_set_data<T>& polygon_set) { polygon_set.sort(); return true; }

  };

  template <typename T>
  struct is_polygon_90_set_concept { };
  template <>
  struct is_polygon_90_set_concept<polygon_90_set_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygon_90_set_concept<rectangle_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygon_90_set_concept<polygon_90_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygon_90_set_concept<polygon_90_with_holes_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_mutable_polygon_90_set_concept { typedef gtl_no type; };
  template <>
  struct is_mutable_polygon_90_set_concept<polygon_90_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct geometry_concept<polygon_90_set_data<T> > { typedef polygon_90_set_concept type; };

  //template <typename T>
  //typename enable_if<typename is_polygon_90_set_type<T>::type, void>::type
  //print_is_polygon_90_set_concept(const T& t) { std::cout << "is polygon 90 set concept\n"; }
  //template <typename T>
  //typename enable_if<typename is_mutable_polygon_90_set_type<T>::type, void>::type
  //print_is_mutable_polygon_90_set_concept(const T& t) { std::cout << "is mutable polygon 90 set concept\n"; }
}
}
#endif

/* polygon_90_set_traits.hpp
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
*/