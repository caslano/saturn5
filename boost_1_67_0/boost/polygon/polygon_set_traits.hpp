/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_SET_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_SET_TRAITS_HPP
namespace boost { namespace polygon{

  struct polygon_set_concept {};

  //default definition of polygon set traits works for any model of polygon , polygon with holes or any vector or list thereof
  template <typename T>
  struct polygon_set_traits {
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
  struct is_polygonal_concept { typedef gtl_no type; };
  template <>
  struct is_polygonal_concept<polygon_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygonal_concept<polygon_with_holes_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygonal_concept<polygon_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_polygon_set_type {
    typedef typename is_polygonal_concept<typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_polygon_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename is_polygonal_concept<typename geometry_concept<std::list<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_polygon_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename is_polygonal_concept<typename geometry_concept<std::vector<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_set_type {
    typedef typename gtl_same_type<polygon_set_concept, typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_set_concept, typename geometry_concept<std::list<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_set_concept, typename geometry_concept<std::vector<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct polygon_set_mutable_traits {};
  template <typename T>
  struct polygon_set_mutable_traits<std::list<T> > {
    template <typename input_iterator_type>
    static inline void set(std::list<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      polygon_set_data<typename polygon_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(std::distance(input_begin, input_end));
      ps.insert(input_begin, input_end);
      ps.get(polygon_set);
    }
  };
  template <typename T>
  struct polygon_set_mutable_traits<std::vector<T> > {
    template <typename input_iterator_type>
    static inline void set(std::vector<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      size_t num_ele = std::distance(input_begin, input_end);
      polygon_set.reserve(num_ele);
      polygon_set_data<typename polygon_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(num_ele);
      ps.insert(input_begin, input_end);
      ps.get(polygon_set);
    }
  };

  template <typename T>
  struct polygon_set_mutable_traits<polygon_set_data<T> > {
    template <typename input_iterator_type>
    static inline void set(polygon_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.set(input_begin, input_end);
    }
  };
  template <typename T>
  struct polygon_set_traits<polygon_set_data<T> > {
    typedef typename polygon_set_data<T>::coordinate_type coordinate_type;
    typedef typename polygon_set_data<T>::iterator_type iterator_type;
    typedef typename polygon_set_data<T>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const polygon_set_data<T>& polygon_set) {
      return polygon_set.end();
    }

    static inline bool clean(const polygon_set_data<T>& polygon_set) { polygon_set.clean(); return true; }

    static inline bool sorted(const polygon_set_data<T>& polygon_set) { polygon_set.sort(); return true; }

  };
}
}
#endif

/* polygon_set_traits.hpp
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
*/