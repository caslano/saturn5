/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_SET_VIEW_HPP
#define BOOST_POLYGON_POLYGON_90_SET_VIEW_HPP
namespace boost { namespace polygon{
  struct operator_provides_storage {};
  struct operator_requires_copy {};

  template <typename value_type, typename arg_type>
  inline void insert_into_view_arg(value_type& dest, const arg_type& arg, orientation_2d orient);

  template <typename ltype, typename rtype, typename op_type>
  class polygon_90_set_view;

  template <typename ltype, typename rtype, typename op_type>
  struct polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> > {
    typedef typename polygon_90_set_view<ltype, rtype, op_type>::coordinate_type coordinate_type;
    typedef typename polygon_90_set_view<ltype, rtype, op_type>::iterator_type iterator_type;
    typedef typename polygon_90_set_view<ltype, rtype, op_type>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set);
    static inline iterator_type end(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set);

    static inline orientation_2d orient(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set);

    static inline bool clean(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set);

    static inline bool sorted(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set);
  };

    template <typename value_type, typename ltype, typename rtype, typename op_type>
    struct compute_90_set_value {
      static
      void value(value_type& output_, const ltype& lvalue_, const rtype& rvalue_, orientation_2d orient_) {
        value_type linput_(orient_);
        value_type rinput_(orient_);
        orientation_2d orient_l = polygon_90_set_traits<ltype>::orient(lvalue_);
        orientation_2d orient_r = polygon_90_set_traits<rtype>::orient(rvalue_);
        //std::cout << "compute_90_set_value-0 orientations (left, right, out):\t" << orient_l.to_int()
        //        << "," << orient_r.to_int() << "," << orient_.to_int() << std::endl;
        insert_into_view_arg(linput_, lvalue_, orient_l);
        insert_into_view_arg(rinput_, rvalue_, orient_r);
        output_.applyBooleanBinaryOp(linput_.begin(), linput_.end(),
                                     rinput_.begin(), rinput_.end(), boolean_op::BinaryCount<op_type>());
      }
    };

    template <typename value_type, typename lcoord, typename rcoord, typename op_type>
    struct compute_90_set_value<value_type, polygon_90_set_data<lcoord>, polygon_90_set_data<rcoord>, op_type> {
      static
      void value(value_type& output_, const polygon_90_set_data<lcoord>& lvalue_,
                 const polygon_90_set_data<rcoord>& rvalue_, orientation_2d orient_) {
        orientation_2d orient_l = lvalue_.orient();
        orientation_2d orient_r = rvalue_.orient();
        value_type linput_(orient_);
        value_type rinput_(orient_);
        //std::cout << "compute_90_set_value-1 orientations (left, right, out):\t" << orient_l.to_int()
        //          << "," << orient_r.to_int() << "," << orient_.to_int() << std::endl;
        if((orient_ == orient_l) && (orient_== orient_r)){ // assume that most of the time this condition is met
          lvalue_.sort();
          rvalue_.sort();
          output_.applyBooleanBinaryOp(lvalue_.begin(), lvalue_.end(),
                                       rvalue_.begin(), rvalue_.end(), boolean_op::BinaryCount<op_type>());
        }else if((orient_ != orient_l) && (orient_!= orient_r)){ // both the orientations are not equal to input
          // easier way is to ignore the input orientation and use the input data's orientation, but not done so
          insert_into_view_arg(linput_, lvalue_, orient_l);
          insert_into_view_arg(rinput_, rvalue_, orient_r);
          output_.applyBooleanBinaryOp(linput_.begin(), linput_.end(),
                                       rinput_.begin(), rinput_.end(), boolean_op::BinaryCount<op_type>());
        }else if(orient_ != orient_l){ // left hand side orientation is different
          insert_into_view_arg(linput_, lvalue_, orient_l);
          rvalue_.sort();
          output_.applyBooleanBinaryOp(linput_.begin(), linput_.end(),
                                       rvalue_.begin(), rvalue_.end(), boolean_op::BinaryCount<op_type>());
        } else if(orient_ != orient_r){ // right hand side orientation is different
          insert_into_view_arg(rinput_, rvalue_, orient_r);
          lvalue_.sort();
          output_.applyBooleanBinaryOp(lvalue_.begin(), lvalue_.end(),
                                       rinput_.begin(), rinput_.end(), boolean_op::BinaryCount<op_type>());
        }
      }
    };

    template <typename value_type, typename lcoord, typename rtype, typename op_type>
    struct compute_90_set_value<value_type, polygon_90_set_data<lcoord>, rtype, op_type> {
      static
      void value(value_type& output_, const polygon_90_set_data<lcoord>& lvalue_,
                 const rtype& rvalue_, orientation_2d orient_) {
         value_type rinput_(orient_);
         lvalue_.sort();
         orientation_2d orient_r = polygon_90_set_traits<rtype>::orient(rvalue_);
         //std::cout << "compute_90_set_value-2 orientations (right, out):\t" << orient_r.to_int()
         //          << "," << orient_.to_int() << std::endl;
         insert_into_view_arg(rinput_, rvalue_, orient_r);
         output_.applyBooleanBinaryOp(lvalue_.begin(), lvalue_.end(),
                                      rinput_.begin(), rinput_.end(), boolean_op::BinaryCount<op_type>());
      }
    };

    template <typename value_type, typename ltype, typename rcoord, typename op_type>
    struct compute_90_set_value<value_type, ltype, polygon_90_set_data<rcoord>, op_type> {
      static
      void value(value_type& output_, const ltype& lvalue_,
                 const polygon_90_set_data<rcoord>& rvalue_, orientation_2d orient_) {
        value_type linput_(orient_);
        orientation_2d orient_l = polygon_90_set_traits<ltype>::orient(lvalue_);
        insert_into_view_arg(linput_, lvalue_, orient_l);
        rvalue_.sort();
        //std::cout << "compute_90_set_value-3 orientations (left, out):\t" << orient_l.to_int()
        //          << "," << orient_.to_int() << std::endl;

        output_.applyBooleanBinaryOp(linput_.begin(), linput_.end(),
                                     rvalue_.begin(), rvalue_.end(), boolean_op::BinaryCount<op_type>());
      }
    };

  template <typename ltype, typename rtype, typename op_type>
  class polygon_90_set_view {
  public:
    typedef typename polygon_90_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_90_set_data<coordinate_type> value_type;
    typedef typename value_type::iterator_type iterator_type;
    typedef polygon_90_set_view operator_arg_type;
  private:
    const ltype& lvalue_;
    const rtype& rvalue_;
    orientation_2d orient_;
    op_type op_;
    mutable value_type output_;
    mutable bool evaluated_;
    polygon_90_set_view& operator=(const polygon_90_set_view&);
  public:
    polygon_90_set_view(const ltype& lvalue,
                     const rtype& rvalue,
                     orientation_2d orient,
                     op_type op) :
      lvalue_(lvalue), rvalue_(rvalue), orient_(orient), op_(op), output_(orient), evaluated_(false) {}

    // get iterator to begin vertex data
  private:
    const value_type& value() const {
      if(!evaluated_) {
        evaluated_ = true;
        compute_90_set_value<value_type, ltype, rtype, op_type>::value(output_, lvalue_, rvalue_, orient_);
      }
      return output_;
    }
  public:
    iterator_type begin() const { return value().begin(); }
    iterator_type end() const { return value().end(); }

    orientation_2d orient() const { return orient_; }
    bool dirty() const { return false; } //result of a boolean is clean
    bool sorted() const { return true; } //result of a boolean is sorted

//     template <typename input_iterator_type>
//     void set(input_iterator_type input_begin, input_iterator_type input_end,
//              orientation_2d orient) const {
//       orient_ = orient;
//       output_.clear();
//       output_.insert(output_.end(), input_begin, input_end);
//       polygon_sort(output_.begin(), output_.end());
//     }
    void sort() const {} //is always sorted
  };

  template <typename ltype, typename rtype, typename op_type>
  struct geometry_concept<polygon_90_set_view<ltype, rtype, op_type> > {
    typedef polygon_90_set_concept type;
  };

  template <typename ltype, typename rtype, typename op_type>
  typename polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
  begin(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.begin();
  }
  template <typename ltype, typename rtype, typename op_type>
  typename polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
  end(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.end();
  }
//   template <typename ltype, typename rtype, typename op_type>
//   template <typename input_iterator_type>
//   void polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
//   set(polygon_90_set_view<ltype, rtype, op_type>& polygon_set,
//       input_iterator_type input_begin, input_iterator_type input_end,
//       orientation_2d orient) {
//     polygon_set.set(input_begin, input_end, orient);
//   }
  template <typename ltype, typename rtype, typename op_type>
  orientation_2d polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
  orient(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.orient(); }
  template <typename ltype, typename rtype, typename op_type>
  bool polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
  clean(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set) {
    return !polygon_set.dirty(); }
  template <typename ltype, typename rtype, typename op_type>
  bool polygon_90_set_traits<polygon_90_set_view<ltype, rtype, op_type> >::
  sorted(const polygon_90_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.sorted(); }

  template <typename value_type, typename arg_type>
  inline void insert_into_view_arg(value_type& dest, const arg_type& arg, orientation_2d orient) {
    typedef typename polygon_90_set_traits<arg_type>::iterator_type literator;
    literator itr1, itr2;
    itr1 = polygon_90_set_traits<arg_type>::begin(arg);
    itr2 = polygon_90_set_traits<arg_type>::end(arg);
    dest.insert(itr1, itr2, orient);
    dest.sort();
  }

  template <typename T>
  template <typename ltype, typename rtype, typename op_type>
  inline polygon_90_set_data<T>& polygon_90_set_data<T>::operator=(const polygon_90_set_view<ltype, rtype, op_type>& that) {
    set(that.begin(), that.end(), that.orient());
    dirty_ = false;
    unsorted_ = false;
    return *this;
  }

  template <typename T>
  template <typename ltype, typename rtype, typename op_type>
  inline polygon_90_set_data<T>::polygon_90_set_data(const polygon_90_set_view<ltype, rtype, op_type>& that) :
    orient_(that.orient()), data_(that.begin(), that.end()), dirty_(false), unsorted_(false) {}

  template <typename geometry_type_1, typename geometry_type_2>
  struct self_assign_operator_lvalue {
    typedef geometry_type_1& type;
  };

  template <typename type_1, typename type_2>
  struct by_value_binary_operator {
    typedef type_1 type;
  };

    template <typename geometry_type_1, typename geometry_type_2, typename op_type>
    geometry_type_1& self_assignment_boolean_op(geometry_type_1& lvalue_, const geometry_type_2& rvalue_) {
      typedef geometry_type_1 ltype;
      typedef geometry_type_2 rtype;
      typedef typename polygon_90_set_traits<ltype>::coordinate_type coordinate_type;
      typedef polygon_90_set_data<coordinate_type> value_type;
      orientation_2d orient_ = polygon_90_set_traits<ltype>::orient(lvalue_);
      //BM: rvalue_ data set may have its own orientation for scanline
      orientation_2d orient_r = polygon_90_set_traits<rtype>::orient(rvalue_);
      //std::cout << "self-assignment boolean-op (left, right, out):\t" << orient_.to_int()
      //          << "," << orient_r.to_int() << "," << orient_.to_int() << std::endl;
      value_type linput_(orient_);
      // BM: the rinput_ set's (that stores the rvalue_ dataset  polygons) scanline orientation is *forced*
      // to be same as linput
      value_type rinput_(orient_);
      //BM: The output dataset's scanline orient is set as equal to first input dataset's (lvalue_) orientation
      value_type output_(orient_);
      insert_into_view_arg(linput_, lvalue_, orient_);
      // BM: The last argument orient_r is the user initialized scanline orientation for rvalue_ data set.
      // But since rinput (see above) is initialized to scanline orientation consistent with the lvalue_
      // data set, this insertion operation will change the incoming rvalue_ dataset's scanline orientation
      insert_into_view_arg(rinput_, rvalue_, orient_r);
      // BM: boolean operation and output uses lvalue_ dataset's scanline orientation.
      output_.applyBooleanBinaryOp(linput_.begin(), linput_.end(),
                                   rinput_.begin(), rinput_.end(), boolean_op::BinaryCount<op_type>());
      polygon_90_set_mutable_traits<geometry_type_1>::set(lvalue_, output_.begin(), output_.end(), orient_);
      return lvalue_;
    }

  namespace operators {
  struct y_ps90_b : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_b,
    typename is_polygon_90_set_type<geometry_type_1>::type,
    typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryOr> >::type
  operator|(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryOr>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryOr());
  }

  struct y_ps90_p : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if<
    typename gtl_and_3< y_ps90_p,
      typename gtl_if<typename is_polygon_90_set_type<geometry_type_1>::type>::type,
      typename gtl_if<typename is_polygon_90_set_type<geometry_type_2>::type>::type>::type,
    polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryOr> >::type
  operator+(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryOr>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryOr());
  }

  struct y_ps90_s : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_s,
    typename is_polygon_90_set_type<geometry_type_1>::type,
    typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd> >::type
  operator*(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryAnd());
  }

  struct y_ps90_a : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_a,
    typename is_polygon_90_set_type<geometry_type_1>::type,
    typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd> >::type
  operator&(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryAnd());
  }

  struct y_ps90_x : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_x,
    typename is_polygon_90_set_type<geometry_type_1>::type,
    typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryXor> >::type
  operator^(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryXor>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryXor());
  }

  struct y_ps90_m : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_m,
    typename gtl_if<typename is_polygon_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_polygon_90_set_type<geometry_type_2>::type>::type>::type,
                       polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryNot> >::type
  operator-(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_90_set_view<geometry_type_1, geometry_type_2, boolean_op::BinaryNot>
      (lvalue, rvalue,
       polygon_90_set_traits<geometry_type_1>::orient(lvalue),
       boolean_op::BinaryNot());
  }

  struct y_ps90_pe : gtl_yes {};

  template <typename coordinate_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and< y_ps90_pe, typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_data<coordinate_type_1> >::type &
  operator+=(polygon_90_set_data<coordinate_type_1>& lvalue, const geometry_type_2& rvalue) {
    lvalue.insert(polygon_90_set_traits<geometry_type_2>::begin(rvalue), polygon_90_set_traits<geometry_type_2>::end(rvalue),
                  polygon_90_set_traits<geometry_type_2>::orient(rvalue));
    return lvalue;
  }

  struct y_ps90_be : gtl_yes {};
  //
  template <typename coordinate_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and< y_ps90_be, typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       polygon_90_set_data<coordinate_type_1> >::type &
  operator|=(polygon_90_set_data<coordinate_type_1>& lvalue, const geometry_type_2& rvalue) {
    return lvalue += rvalue;
  }

  struct y_ps90_pe2 : gtl_yes {};

  //normal self assignment boolean operations
  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_pe2, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryOr>(lvalue, rvalue);
  }

  struct y_ps90_be2 : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps90_be2, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator|=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryOr>(lvalue, rvalue);
  }

  struct y_ps90_se : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps90_se, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator*=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd>(lvalue, rvalue);
  }

  struct y_ps90_ae : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps90_ae, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator&=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryAnd>(lvalue, rvalue);
  }

  struct y_ps90_xe : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps90_xe, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator^=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryXor>(lvalue, rvalue);
  }

  struct y_ps90_me : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps90_me, typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
                                         typename is_polygon_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, boolean_op::BinaryNot>(lvalue, rvalue);
  }

  struct y_ps90_rpe : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps90_rpe,
    typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
    typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, rvalue);
  }

  struct y_ps90_rme : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps90_rme,
    typename is_mutable_polygon_90_set_type<geometry_type_1>::type,
    typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, -rvalue);
  }

  struct y_ps90_rp : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps90_rp,
    typename gtl_if<typename is_mutable_polygon_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type>::type,
  geometry_type_1>::type
  operator+(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval += rvalue;
    return retval;
  }

  struct y_ps90_rm : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps90_rm,
    typename gtl_if<typename is_mutable_polygon_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type>::type,
  geometry_type_1>::type
  operator-(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval -= rvalue;
    return retval;
  }
  }
}
}
#endif

/* polygon_90_set_view.hpp
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
*/