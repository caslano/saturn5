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