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