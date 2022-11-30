/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_SET_VIEW_HPP
#define BOOST_POLYGON_POLYGON_45_SET_VIEW_HPP
namespace boost { namespace polygon{

  template <typename ltype, typename rtype, int op_type>
  class polygon_45_set_view;

  template <typename ltype, typename rtype, int op_type>
  struct polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> > {
    typedef typename polygon_45_set_view<ltype, rtype, op_type>::coordinate_type coordinate_type;
    typedef typename polygon_45_set_view<ltype, rtype, op_type>::iterator_type iterator_type;
    typedef typename polygon_45_set_view<ltype, rtype, op_type>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set);
    static inline iterator_type end(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set);

    template <typename input_iterator_type>
    static inline void set(polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set,
                           input_iterator_type input_begin, input_iterator_type input_end);

    static inline bool clean(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set);

  };

  template <typename value_type, typename ltype, typename rtype, int op_type>
  struct compute_45_set_value {
    static
    void value(value_type& output_, const ltype& lvalue_, const rtype& rvalue_) {
      output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                  polygon_45_set_traits<ltype>::end(lvalue_));
      value_type rinput_;
      rinput_.set(polygon_45_set_traits<rtype>::begin(rvalue_),
                  polygon_45_set_traits<rtype>::end(rvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op_type == 0)
        output_ |= rinput_;
      else if(op_type == 1)
        output_ &= rinput_;
      else if(op_type == 2)
        output_ ^= rinput_;
      else
        output_ -= rinput_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }
  };

  template <typename value_type, typename ltype, typename rcoord, int op_type>
  struct compute_45_set_value<value_type, ltype, polygon_45_set_data<rcoord>, op_type> {
    static
    void value(value_type& output_, const ltype& lvalue_, const polygon_45_set_data<rcoord>& rvalue_) {
      output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                  polygon_45_set_traits<ltype>::end(lvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op_type == 0)
        output_ |= rvalue_;
      else if(op_type == 1)
        output_ &= rvalue_;
      else if(op_type == 2)
        output_ ^= rvalue_;
      else
        output_ -= rvalue_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }
  };

  template <typename ltype, typename rtype, int op_type>
  class polygon_45_set_view {
  public:
    typedef typename polygon_45_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_45_set_data<coordinate_type> value_type;
    typedef typename value_type::iterator_type iterator_type;
    typedef polygon_45_set_view operator_arg_type;
  private:
    const ltype& lvalue_;
    const rtype& rvalue_;
    mutable value_type output_;
    mutable bool evaluated_;

    polygon_45_set_view& operator=(const polygon_45_set_view&);
  public:
    polygon_45_set_view(const ltype& lvalue,
                        const rtype& rvalue ) :
      lvalue_(lvalue), rvalue_(rvalue), output_(), evaluated_(false) {}

    // get iterator to begin vertex data
  public:
    const value_type& value() const {
      if(!evaluated_) {
        evaluated_ = true;
        compute_45_set_value<value_type, ltype, rtype, op_type>::value(output_, lvalue_, rvalue_);
      }
      return output_;
    }
  public:
    iterator_type begin() const { return value().begin(); }
    iterator_type end() const { return value().end(); }

    bool dirty() const { return value().dirty(); } //result of a boolean is clean
    bool sorted() const { return value().sorted(); } //result of a boolean is sorted

    //     template <typename input_iterator_type>
    //     void set(input_iterator_type input_begin, input_iterator_type input_end,
    //              orientation_2d orient) const {
    //       orient_ = orient;
    //       output_.clear();
    //       output_.insert(output_.end(), input_begin, input_end);
    //       polygon_sort(output_.begin(), output_.end());
    //     }
  };

  template <typename ltype, typename rtype, int op_type>
  typename polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  begin(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.begin();
  }
  template <typename ltype, typename rtype, int op_type>
  typename polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  end(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.end();
  }
  template <typename ltype, typename rtype, int op_type>
  bool polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  clean(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.value().clean(); }

  template <typename geometry_type_1, typename geometry_type_2, int op_type>
  geometry_type_1& self_assignment_boolean_op_45(geometry_type_1& lvalue_, const geometry_type_2& rvalue_) {
    typedef geometry_type_1 ltype;
    typedef geometry_type_2 rtype;
    typedef typename polygon_45_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_45_set_data<coordinate_type> value_type;
    value_type output_;
    value_type rinput_;
    output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                polygon_45_set_traits<ltype>::end(lvalue_));
    rinput_.set(polygon_45_set_traits<rtype>::begin(rvalue_),
                polygon_45_set_traits<rtype>::end(rvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
    if(op_type == 0)
      output_ |= rinput_;
    else if(op_type == 1)
      output_ &= rinput_;
    else if(op_type == 2)
      output_ ^= rinput_;
    else
      output_ -= rinput_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    polygon_45_set_mutable_traits<geometry_type_1>::set(lvalue_, output_.begin(), output_.end());
    return lvalue_;
  }

  template <typename concept_type>
  struct fracture_holes_option_by_type {
    static const bool value = true;
  };
  template <>
  struct fracture_holes_option_by_type<polygon_45_with_holes_concept> {
    static const bool value = false;
  };
  template <>
  struct fracture_holes_option_by_type<polygon_with_holes_concept> {
    static const bool value = false;
  };

  template <typename ltype, typename rtype, int op_type>
  struct geometry_concept<polygon_45_set_view<ltype, rtype, op_type> > { typedef polygon_45_set_concept type; };

  namespace operators {
  struct y_ps45_b : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_b,
    typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
    typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
    typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator|(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }

  struct y_ps45_p : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_p,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type>::type,
  polygon_45_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator+(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }

  struct y_ps45_s : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_s, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator*(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }

  struct y_ps45_a : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_a, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator&(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }

  struct y_ps45_x : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_x, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 2> >::type
  operator^(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 2>
      (lvalue, rvalue);
  }

  struct y_ps45_m : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_m,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type>::type,
  polygon_45_set_view<geometry_type_1, geometry_type_2, 3> >::type
  operator-(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 3>
      (lvalue, rvalue);
  }

  struct y_ps45_pe : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4<y_ps45_pe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type, gtl_yes,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }

  struct y_ps45_be : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_be, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator|=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }

  struct y_ps45_se : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps45_se,
    typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
    typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator*=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }

  struct y_ps45_ae : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_ae, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator&=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }

  struct y_ps45_xe : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if<
    typename gtl_and_3<y_ps45_xe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                      typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    geometry_type_1>::type &
  operator^=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 2>(lvalue, rvalue);
  }

  struct y_ps45_me : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_me, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 3>(lvalue, rvalue);
  }

  struct y_ps45_rpe : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3< y_ps45_rpe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, rvalue);
  }

  struct y_ps45_rme : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rme, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, -rvalue);
  }

  struct y_ps45_rp : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rp, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator+(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval += rvalue;
    return retval;
  }

  struct y_ps45_rm : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rm, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator-(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval -= rvalue;
    return retval;
  }
  }
}
}
#endif

/* polygon_45_set_view.hpp
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
*/