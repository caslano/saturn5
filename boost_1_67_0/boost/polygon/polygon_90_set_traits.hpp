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