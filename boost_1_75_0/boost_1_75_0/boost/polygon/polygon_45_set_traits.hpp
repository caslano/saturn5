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
g6fAKM1gmnvFQbvsJBhyTa7ClBu/MK91myaYqENiIvP9TVpa9vWnw/2b1GR48vO30GmVVa5X+TiYrCGCNe4Vgw4RvZdvoU+4s9F4Z7qmg00HjN0p+lya2J0uiAwREbLsRTnD/MiywYYoJSppwpRvxuCZf6id/ldKVojnFyz6i+ovkYTm9BU/1i4CO9A2w+xtyZVkRFGvOmFGmOZlIjKR5akd5bkJahpP+p+ofr6o/9WCeBX4TvCBGK9TlOUnTDkpDiTKun0m7hcTlBmU2CMBoDE7IJL4PkG97RyVlQlqF+2DXOLDcf0IBAcAM4C5Y1gjnjkGBcD3Nx4gMH/0PrbiPhZkilvBdxIaEyhSZRZDpGFwmRMzSFjuY9cYU/aVqcBO+3KFiiCSnwnH32DYXrnS51Seyci/YPSh1gfi66pjaqChs++3Ov/Z7VdG4iiJRiUp1XiJgYLXVjJRGY4wSCr2eqyZfzXA8QePtv4v1iXC+rmm74r9K/bgu3egDemqmcXRo6bJJqljevbccEL1tYpmO1z7ST1+pXJ1vUIvQeyl+0dcO8fVcLzNBA1BRcrZl9p95TMEurp+bZPIaW9//CaPIhRB9Fh+gcDFRTPCEOH6gSi4+JKM6L3oXf1S/xc8dztkt5pUbyfkcqaWLv6yGbT0Z3J2n6bywA9uvNw0gxh7/YIyhAAMLsGLXcHOSJDCMlHV8XENJHie0yjfAW+q
*/