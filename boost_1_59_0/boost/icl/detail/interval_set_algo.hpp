/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_SET_ALGO_HPP_JOFA_081005
#define BOOST_ICL_INTERVAL_SET_ALGO_HPP_JOFA_081005

#include <boost/next_prior.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/relation_state.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/is_total.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/interval_combining_style.hpp>
#include <boost/icl/detail/element_comparer.hpp>
#include <boost/icl/detail/interval_subset_comparer.hpp>
#include <boost/icl/detail/associated_value.hpp>

namespace boost{namespace icl
{

namespace Interval_Set
{

//------------------------------------------------------------------------------
// Lexicographical comparison on ranges of two interval container 
//------------------------------------------------------------------------------

template<class LeftT, class RightT>
bool is_element_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
bool is_element_less(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::less;
}

template<class LeftT, class RightT>
bool is_element_greater(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::greater;
}

//------------------------------------------------------------------------------
// Subset/superset compare on ranges of two interval container 
//------------------------------------------------------------------------------

template<class IntervalContainerT>
bool is_joinable(const IntervalContainerT& container, 
                 typename IntervalContainerT::const_iterator first, 
                 typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!icl::touches(key_value<IntervalContainerT>(it_++),
                         key_value<IntervalContainerT>(next_++)))
            return false;

    return true;
}


template<class LeftT, class RightT>
bool is_inclusion_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                             is_total<RightT> >,
                   bool>::type
within(const LeftT&, const RightT&)
{
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                             mpl::not_<is_total<RightT> > >,
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}


template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_map, is_interval_map, LeftT, RightT>, 
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_set, LeftT, RightT>, 
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}



template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                             is_total<LeftT> >,
                   bool>::type
contains(const LeftT&, const RightT&)
{
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                             mpl::not_<is_total<LeftT> > >,
                   bool>::type
contains(const LeftT& super, const RightT& sub)
{
    int result =
        subset_compare
        (
            super, sub, 
            super.begin(), super.end(), 
            sub.begin(), sub.end()
        );
    return result == inclusion::superset || result == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_set, LeftT, RightT>, 
                   bool>::type
contains(const LeftT& super, const RightT& sub)
{
    int result =
        subset_compare
        (
            super, sub, 
            super.begin(), super.end(), 
            sub.begin(), sub.end()
        );
    return result == inclusion::superset || result == inclusion::equal;
}

template<class IntervalContainerT>
bool is_dense(const IntervalContainerT& container, 
              typename IntervalContainerT::const_iterator first, 
              typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!icl::touches(key_value<IntervalContainerT>(it_++), 
                         key_value<IntervalContainerT>(next_++)))
            return false;

    return true;
}

} // namespace Interval_Set

namespace segmental
{

template<class Type>
inline bool joinable(const Type& _Type, typename Type::iterator& some, typename Type::iterator& next)
{
    // assert: next != end && some++ == next
    return touches(key_value<Type>(some), key_value<Type>(next)) 
        && co_equal(some, next, &_Type, &_Type); 
}

template<class Type>
inline void join_nodes(Type& object, typename Type::iterator& left_, 
                                     typename Type::iterator& right_)
{
    typedef typename Type::interval_type interval_type;
    interval_type right_interval = key_value<Type>(right_);
    object.erase(right_);
    const_cast<interval_type&>(key_value<Type>(left_)) 
        = hull(key_value<Type>(left_), right_interval);
}

template<class Type>
inline typename Type::iterator 
    join_on_left(Type& object, typename Type::iterator& left_, 
                               typename Type::iterator& right_)
{
    //CL typedef typename Type::interval_type interval_type;
    // both left and right are in the set and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    return left_;
}

template<class Type>
inline typename Type::iterator 
    join_on_right(Type& object, typename Type::iterator& left_, 
                                typename Type::iterator& right_)
{
    //CL typedef typename Type::interval_type interval_type;
    // both left and right are in the map and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    right_ = left_;
    return right_;
}

template<class Type>
typename Type::iterator join_left(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.begin())
        return it_;

    // there is a predecessor
    iterator pred_ = it_;
    if(joinable(object, --pred_, it_)) 
        return join_on_right(object, pred_, it_); 

    return it_;
}

template<class Type>
typename Type::iterator join_right(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.end())
        return it_;

    // there is a successor
    iterator succ_ = it_;

    if(++succ_ != object.end() && joinable(object, it_, succ_)) 
        return join_on_left(object, it_, succ_);

    return it_;
}

template<class Type>
typename Type::iterator join_neighbours(Type& object, typename Type::iterator& it_)
{
           join_left (object, it_); 
    return join_right(object, it_);
}

template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    std::pair<iterator,iterator> overlap = object.equal_range(addend);
    iterator first_ = overlap.first,
             end_   = overlap.second,
             last_  = end_; --last_;

    iterator second_= first_; ++second_;

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}

template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend,
                                   typename Type::iterator last_)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    iterator first_ = object.lower_bound(addend);
    //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));
    iterator second_= boost::next(first_), end_ = boost::next(last_);

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}

} // namespace segmental

namespace Interval_Set
{
using namespace segmental;

template<class Type, int combining_style>
struct on_style;

template<class Type>
struct on_style<Type, interval_combine::joining>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type& object, iterator inserted_)
    { return join_neighbours(object, inserted_); }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        iterator joined_ = join_under(object, addend, last_);
        return join_neighbours(object, joined_);
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        iterator joined_ = join_under(object, addend);
        return join_neighbours(object, joined_);
    }
};

template<class Type>
struct on_style<Type, interval_combine::separating>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type&, iterator inserted_)
    { return inserted_; }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        return join_under(object, addend, last_);
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        return join_under(object, addend);
    }
};

template<class Type>
struct on_style<Type, interval_combine::splitting>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type&, iterator inserted_)
    { return inserted_; }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        iterator first_ = object.lower_bound(addend);
        //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));

        iterator it_ = first_;
        interval_type rest_interval = addend;

        add_front(object, rest_interval, it_);
        add_main (object, rest_interval, it_, last_);
        add_rear (object, rest_interval, it_);
        return it_;
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        std::pair<iterator,iterator> overlap = object.equal_range(addend);
        iterator first_ = overlap.first,
                 end_   = overlap.second,
                 last_  = end_; --last_;

        iterator it_ = first_;
        interval_type rest_interval = addend;

        add_front(object, rest_interval, it_);
        add_main (object, rest_interval, it_, last_);
        add_rear (object, rest_interval, it_);

        return it_;
    }
};


template<class Type>
void add_front(Type& object, const typename Type::interval_type& inter_val, 
                                   typename Type::iterator&      first_)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    // If the collision sequence has a left residual 'left_resid' it will
    // be split, to provide a standardized start of algorithms:
    // The addend interval 'inter_val' covers the beginning of the collision sequence.

    // only for the first there can be a left_resid: a part of *first_ left of inter_val
    interval_type left_resid = right_subtract(key_value<Type>(first_), inter_val);

    if(!icl::is_empty(left_resid))
    {   //            [------------ . . .
        // [left_resid---first_ --- . . .
        iterator prior_ = cyclic_prior(object, first_);
        const_cast<interval_type&>(key_value<Type>(first_)) 
            = left_subtract(key_value<Type>(first_), left_resid);
        //NOTE: Only splitting
        object._insert(prior_, icl::make_value<Type>(left_resid, co_value<Type>(first_)));
    }

    //POST:
    // [----- inter_val ---- . . .
    // ...[-- first_ --...
}


template<class Type>
void add_segment(Type& object, const typename Type::interval_type& inter_val, 
                                     typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    interval_type lead_gap = right_subtract(inter_val, *it_);
    if(!icl::is_empty(lead_gap))
        //           [lead_gap--- . . .
        // [prior_)           [-- it_ ...
        object._insert(prior(it_), lead_gap);

    // . . . --------- . . . addend interval
    //      [-- it_ --)      has a common part with the first overval
    ++it_;
}


template<class Type>
void add_main(Type& object, typename Type::interval_type& rest_interval, 
                            typename Type::iterator&      it_,
                      const typename Type::iterator&      last_)
{
    typedef typename Type::interval_type interval_type;
    interval_type cur_interval;
    while(it_ != last_)
    {
        cur_interval = *it_ ;
        add_segment(object, rest_interval, it_);
        // shrink interval
        rest_interval = left_subtract(rest_interval, cur_interval);
    }
}


template<class Type>
void add_rear(Type& object, const typename Type::interval_type& inter_val, 
                                  typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    iterator prior_ = cyclic_prior(object, it_);
    interval_type cur_itv = *it_;

    interval_type lead_gap = right_subtract(inter_val, cur_itv);
    if(!icl::is_empty(lead_gap))
        //          [lead_gap--- . . .
        // [prior_)          [-- it_ ...
        object._insert(prior_, lead_gap);
    
    interval_type end_gap = left_subtract(inter_val, cur_itv);
    if(!icl::is_empty(end_gap))
        // [---------------end_gap)
        //      [-- it_ --)
        it_ = object._insert(it_, end_gap);
    else
    {
        // only for the last there can be a right_resid: a part of *it_ right of addend
        interval_type right_resid = left_subtract(cur_itv, inter_val);

        if(!icl::is_empty(right_resid))
        {
            // [--------------)
            //      [-- it_ --right_resid)
            const_cast<interval_type&>(*it_) = right_subtract(*it_, right_resid);
            it_ = object._insert(it_, right_resid);
        }
    }
}


//==============================================================================
//= Addition
//==============================================================================
template<class Type>
typename Type::iterator 
    add(Type& object, const typename Type::value_type& addend)
{
    //CL typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return object.end();

    std::pair<iterator,bool> insertion = object._insert(addend);

    if(insertion.second)
        return on_style_::handle_inserted(object, insertion.first);
    else
        return on_style_::add_over(object, addend, insertion.first);
}


template<class Type>
typename Type::iterator 
    add(Type& object, typename Type::iterator    prior_, 
                const typename Type::value_type& addend)
{
    //CL typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return prior_;

    iterator insertion = object._insert(prior_, addend);

    if(*insertion == addend)
        return on_style_::handle_inserted(object, insertion);
    else
        return on_style_::add_over(object, addend);
}


//==============================================================================
//= Subtraction
//==============================================================================
template<class Type>
void subtract(Type& object, const typename Type::value_type& minuend)
{
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    //CL typedef typename Type::value_type    value_type;

    if(icl::is_empty(minuend)) return;

    std::pair<iterator, iterator> exterior = object.equal_range(minuend);
    if(exterior.first == exterior.second) return;

    iterator first_ = exterior.first;
    iterator end_   = exterior.second;
    iterator last_  = end_; --last_;

    interval_type leftResid = right_subtract(*first_, minuend);
    interval_type rightResid; 
    if(first_ != end_  )
        rightResid = left_subtract(*last_ , minuend);

    object.erase(first_, end_);

    if(!icl::is_empty(leftResid))
        object._insert(leftResid);

    if(!icl::is_empty(rightResid))
        object._insert(rightResid);
}


} // namespace Interval_Set

}} // namespace icl boost

#endif 


/* interval_set_algo.hpp
z3Dueg5KRbQrAhXQLw+2R63QeT5oPkc24lDKD7PxvQ3+c9oGB8OaqOHoARjWRDasDEcf3seG6CscuTw2rIdxWBlqXtI55OPGwWFdMmRYHRbZIBel9zMiLQ7eaZB+CAqUwuOlT7rdsEcDZHoAx3gBPDOD+Y/Itf21qdJh5diXkjOmREcA6KFCRc8xCsu/iWG/Dlk8b/s4mgb9ILapztjUgdT3xFQpkmYr65fLuLWfwRNI5w+jo4alSMEUHZiA2jpUT9zyRFYg3tZIFxRAEEIa2cw6RGq2FMUz3kRY1NRlMeb4uaSI3DBVPJ/6PhHPi+PJE371GzBRQE2SPMjygdCFeOLvV+3iLUVWZeph8UdaLVBDVWZFtFx6GHg17AG0Du0tf4U9uBp6kMy+XGp5t61DHEl5PDXoCJyEGCHdTV9H/2/kNousR480uQofyMJD+VDXQ1DtkU8WBtoAmULtd/YZSUo2UEXn4lDrjNUhoKCwH3Oyd6vRdisn3g3LjEFo7dXkPVw//cGaXABFuezs1LsbimT4DfCilTjPAlkwJTU6ExaVmmwz2zDV1FMmDPCQQ0zFgw3n2Sm3GTUyIgb1cOQho7zRCBWShxBf8P4gIyriAHsrJ0OCpZhAXspp7SpXATZ1EGBrp/pqU2HgGETCYvoq2TYEdvuTaxqKkKSAJCMuwW3yw0iRBfc0aHDL6KVjXybfDPgNzVzLKfLiUYgLAEWK3YYjuNwh6kZY7efRukxwo16eK15hm4g7sDgayrIxakFM0qhdiJG54AIjg31l7E7YAvcbdU2oLojGR0YC1X8mxWGRRjAFwq6HOpidImOL/c4S9IZmT1MdFnpUMW1Vz5B0DNE/XBRX9WvbP6jqN+syhUQho6VYLa+YlTfMVQcqK975KwAatzLWjmLBzeUrUFUnF4+knvgMjwU4vHrn/agcTIrR2EGSiz4rMwGRmerbE+rbbPVNUt/y1TdRfStS3+5T30rUt1L17c4CbB1GlGBE1Qj6cAfekcA2UXyP6stjjMKJvM3ELV7E0mXK8YsSVO2vMtNbMYN2UEmKV6KEdIvgVLi8DTMFEymZqSTnbZiNodkYysFQDobsGLIryaRksSIzWRhVvHK0el2TmpcrQnWrT8ary0ThANrUgOeC//WposBsojlsDto8+gPmehHCZpqohtm0oi7qVJxVIESSlqpz56JPo6EA3dCJitAb32feRzh68jtcsxGPt7Lm2rgRJbxLFH5I5qABpco1EO1V3q9cic9tHSgL8H7lcvZySn1xsZdO9iIVYKRuG4KaOKNpBzqXwZim7RjCNE3PQ6jFhAU99V62haWsnNeeDXVjHMDqNmyoMN+qMIBb6KXLQ4MAl305wF2hAZxclzYU2EhLNIkq/dg31bjSFgSymX9TFDoBefkND+iECUwWBs8FFdcDw1wpdvXthSHjKp/DTL1nFKUp9gd2Tz2GKXu2D0/8ayhgmD1R9Ai8dNA7MZBhy9AnrdNCftRPPyeK4vEq7RXl5HQZxC0j0fo+PCESTW8gk7+UtkKKstIVbfvNTIMFRaK46L/Hb3PYzYxXuwAaE78AKohfAMH3f3rfM9V/RrhCve8Zeem+ZyPseMGNA1EuuPG7qCG4ES94zFodExtHYR1HhdUN46UWvVbR51ETs+aomofUx81Djhqs7xPIMdvfI0zXzEOOVs1DQnUt8njVyORqNdC8MEE3+FIRadCeqnheonaEk8FO3MYR+/CTbxOdAsDdRFVYSHPRq3/Kji2EZMBjGIsiCeh+s3L5cQZhQKRvw3hmRwwDapzG4DPhADxOLVjyqf0tcckQFVmgqqxiTBnrg7C1WwU1fLbjsUg3XiIrY4+j2L3jvNXRbe2W5zAnnCktzLkxFgfsUmU6THTl1pkAVU1/gXbjJ+tBvMlwmpvOYrOO2vYLE4EiWMp8AKmusbs4RhEygIt+CeBUIozbJ0AhLUwqIpSda9l7HI8H0/Y9lx2P1WHsGxDbsKyzEv2UBJmAjOsOZewhlVMZU3kGwFuLpk+xG4Lgr/CNROAd1RmkUKoUy6+ehhH+v+LuryaX6A2GjipDZScU4KbX/pYdurnpDzBPsCjHrOlRLP2lqkdx3uuhc6D8fTvuQiEkmgfhyuPXohjcdRB0e+h0eMCHTFyLr2HzPTQNE1ky9brKHSxl61MoaJJfZaAv/FHTSmdi0MXm7Y+Qcotqb3C7nQ98iU+9MB79IWyHeLxwIEs4qXNAHgmcImTALyj4h55yWhNWv2Rm3nKuqh9ABU+Bqx/Q7YCpS3XTJ/5DPQRL8tAFECxF/xac3iusJMUcmRss0csjyZL07NiigCIvMdaN8Lrc9NnpeMdljlqli4owgbwT7jNpfkpIRHVbcslfSY/dmCmMQG9EblqbwQRpoORGJ9fARdOAo/OiSWs3XTydfYJS82rNFUIic/CB7Pg0hTlqllozoQPo5GFFWaRnvtkOSTZy6ERvkXFDKhnVkKDo+V2hqJnfGwJuP6zePTBvC4kRJZFJVJLu6BhAR43MSTV9HU8E5ypQTq1Zt+mzcih2odnuxlvDE8IUaROn+qI06xOjVzQaFMAW5D36CGQqxFxJUk0WZGMy+cEdWZlQX/3ZexLiAnfBboTng3LgFJOTQrka2bGDBM7iVWpjuuw8ZG3zn5QdO2VnSHbukZ3P8f45SbAZekkMCaQtC6XaPTq5die/OQOifRcza9J8Fzds4vm9EX6vrwFWhtTJ48rn9/rD2+G1KikcM5bawrJjC//oyUTAQ1mBNz/OBiwgOVsV2fGk7HhGdmyXHa/KjnbZ8XzX65AGSpNopmCTqEGYJVFOmFxSIoyGNz6wNRFvedq5rsfVgLHrJ2pA31WbiIaF2n1dghqT0PVDjLl4rThFchwyEschYu9H1yPb+eBSLXdv2fYuB/qDg8i97+DJR9F8aMb2rhxMsKpV1zVdK2PS8DJa+eAIVkar0mVkBbQOLaC1CwUCfBcXCdf5LlYKmb6LDwijfRfX84EPMN55hOs6bGJNsHQdVAOZXXsg0JiUf5OY5tukny2OXLgQEvpgtLt+A1/yrSz+Rha/6sgmjG/E+JW8/xF83s/7H8Lng7x/LT5F3l+Fzw28/158Luf9d2FVq7boyAgUZJFWPa/jd0V6iubr0SOYc0dQ3NMYYfiicfJCKH8wCt0pdk00qTMTu49//Bb0wxVbxQfZ9XFsOf/4Ubyu9m/DeFrI+9GPOUzaXfDzSNQM/YbNa3Wvoz2HQ0tQR4BDaAWaCbZe5soPxhY/Wjh1hGXHAd4/M4HZk+CajEhkOA4Qx4EWx/PMtqYhAcW3nsSwL5IJg2dHUcqgeFwWD/DBz5hwVyuqCXddpR9e7bCahAp+n73fFXQcd9GXf6p543aEape1OJ5hOpuLJXqXcIdEk4WWEj6QZmATZW9xhFKYq6r2vcx62Ue8n2kOOQ8RPVlqlMIcLKSuHIhqtPc3OI5remhQDfSi6zAO0RBYEmaxW2Dh6h7HEY7fB2zjAWHU09n7j8TivX0ac8BcdW3BhaxTR8PFrCOJI30X7xPjSoLRm5mxxTxHa50BYHDfNmZGsrUuE6DThKb2XDRvB7uIkh3PCUk4pt1Rg1zbim3hFPFJKQT/W2VtDvww2zA4Po9LdvqUsei6mdS2SwfS6j9jFspG4qCjZZSx6Lu5FFuCZpQwwswi5s4SORh0fTFMi4f+CS3Xdx3CKzkKsPoHtpuZeP9rCCoqe14ilOMq938M8FYCcT9laWDZP810OrdOx046Fq2WcnVCot0eaBO/yXYcOBLrqtZrsKIbhJVo0iKUQzdhqm8hVdcdrIxWFE6SnVt7HO0+mBgLA9sboJ5Gx1bj0mbH7pwGxxstjleZCdgJEK8l5FhCDiKgRwldCpKyMIvwNVOdSSF5NXHuWS1zURMKD3AaDHUd06vz3RPBhMLonohdSEK4ezpq4V+390d7IQbyi19Zj+K3sYGjm0bVAB+xLrW3Qzqq6/0QhzAgtpMOckFMsCo46rXJ8SkfJa1q7x027SSS2iIapVWv6oKvHWOXpq2KszUQ2pSIX4Qs4gg9fYfL66Z7noM+hHOkvjy5bDOWXmcwOLc2jFwSPRQMYM7s5mIAygRYEjCBQjo57MvLEY1MNNJ5gDgPNOtz7PBRqn1Gxwei6pLALlzd06IXEmEsZ0XTeiJqMDua3BNJEFIhmAnDy1g4cXu2+Gq2GOqJmNFXwI6gY4+nKpN+xq4SzYr4KqnFuKBzN+2FuJ4IVypAgUaR93qqcuAL3RPTBKaf1wmwN4V0dfOhe6TsgOzYrDg3W0OricEVDBxnsN/ymE5XWFoI4F93LZTswqKD+Ik+jcXUbtaVim9HeUUMQd+w9EdQIB9m2CgMad2ieJXP6YQRivgc3fgQRKx6TldKanc2Tvaf5APHYmgUiQTZLuvYgyKcf6mHnfgg+kpoixDllg+zLXs6si0n4DftRLblHvjdD78m+K2Db4wC5/cmuujfnsELwlVRczF7Pf0L9R75XGNi4wju9UJLw8jixpENiY3hxpHFflgO5cx8qLtxIn6Mmm55R0iyN3Lw5dtGzu5vE66Npvr6VglmX58j/uUr0l7iy80RLuSmi/qSxhT7An9bAyf2rGBFndadmmgZe73l486eA3oxLkTGjvHRHxqwV8KVSKvTV7cwi4GlpcQZkzk8EykxtkWQjKIfXfrEyVxbJKAAOSOkeejLwNDbXR5Dr4c+KDJSljn59tWipaFuYaI1lOfgvPyzIWubNHcW+s6NGd4hYfoWbBoVEEMiYmKzYVawUI9tqRsFdGHjqAYLCWuDw1nbcp2WyoxZuRbIbGg1OLmldNrXONlmFKJvFQzNegfQpfNxAK4jxcaSjabejmb9rPlSbGVNytNVK8t7B3R6sh/eU/A9RXvXzdeTiKoTKJ2dqYo2oxeWoPPMUuQrkPcMOo8vZRaHqPsJhHYLbjTBYr0LiJ/a49Ad6Fagh382bIgYWpfS7x5nd6tiGiTz0G+RG3D2SwdmlJMIQtBzm1BzVCW+u7GlOEpe4UqbwyyOi48P6yIJN+tyUEcCR6gMNj4YokLIwVRKNo0gEfowFN5syCmMJhg6cCjq8iFyNUQ+x4bNQKqNhYGe2qt7P8JKRFOeaK4xoIm9WjMkLICE3qocNz1ZoRLODo4ZXR8yFuym9vvHYiECQy0bC+LoMLRcGg1Ds4vGHmOaRcD+HWfGitUhqCDNqOnwqzptCIYNuVYP1KBWpdXz8eM45h3W0JJ48RESw1rRWyTdgibWHR3SgYwSWzf/TFiK9ddMRScnk2CRpDQmLfSHxL6GhQNoNwDb6qaPQK+jzI4AThDE0ju+09pnVsW0B2rjzau1rBJuhP8OYSb8X40eADTLkPQD1ft7WSQuiMFiZ6A9xVHDon6jyrKVRSp1OgNeu+l1bCGVajZW00+bcgCuT5fFTptmsED3aUf3KTF2yhk79aPu02X0tIOemrhBW7vzRROsXRQhB2b4zllDrHaPrcydNdRqtwmAsD3S9XMU8LZU3gPf6L8fg7Zooge3VBlp+ICmz8TcO17XqZorQPdepLpf+jIZRS1RYoadpmUxDfFO5geBu3RF2so05UkzXXwMZS/FM1DuqxHm5y2rcg3WGjuKkuYAtXlzuvFQ60Y0qellli68ythQ3MhFAX68zMgFRuEO3oQBW4s4friWPubt+r1qKFEw2ppFtyy2y+LxPDFj0PxBRp6YPmj+IB1lxJ5B45+oxY8CUgJsteke+NNEuXDuVJMLHXJZh+0jpry0BBkssR/YT5Utf5MM2oM45fa46C/uVo2LommIjLiJA08lknunmDAbdJ6UdaBiwClxjNtLW3eoEp6nbM3Cs3Jtu8fjVlARfXgT8Ep8v+pXOVh0ZYJWeQG5zBjFYI1n7sMaOy+rsVMci7ld1PQbzRxFs/CgXDt8kGAlGxTi6AzOTlpdP1JRVtcvwUMNtVUcivOMPcCsLRxaXV8HX4T01fVzFUUchXYq0Cfj+gdVqUAgWA4BmBzX7KFmrWMa9XliO76fomnrmCGFQ8FVIXrlEQAYAJIGBJJj7QAkJxFIJp5HIJnjdnu/3xhKwfm/h5PzKZeMoUzUjKGszksXku1oDuX8UHMo51VImvh9Vh+YBZA3B+EpIt4pl52Sy44DJPxzixqLVjKQyhwEqUy3O25B5ZIVD2YKhAGURz/UWsYP5cuMpaTHZ3T06iHGUnBwys7g8uukec/FDaUIO2Eusa7OQSMpl2pECHqbGfWIfx9uuqMdTXe8pIKY1piPGgZNdxxijRkfb0xg1SWbHQSyXhRh69/5bNxoR2WLo4MZa/H+fV0wcYuYIZbJsngqryxDsAH01QJqycDU6fSarSr0ZF1mBcXjHWLwBZYLYKPaQ2iVI8lL29YwQyjHVUMob61hgHUKAWv/YQAs6WyJ+y2fEfpOzc9qxgBQsuA0tHEbHia1mO6E/3hHEGzAdNFJEqdI93C6ZrsRfqYUMoK52w5l1Yd9zJD02o+WwS5VlJUGSPZVaNBqqSarGLiJLh1zhVGCo30aw7nBSmPQeL1clGXZjd5wbLGaBBLLK8AKa5fsXQkPN63+tepbNFdSGyInau0Yd3k7RkIbDO9A/Z9KzUa1lJp90UTCQmhUsq6KWQpFi8fCnY1OXU9YLyzuCXNiqitu3VnIJ+/Ej88uHagFZ9erOeXERoeuodgYLDYzSw0uKtynaR1dpxRzEiQyFjpsH9f8h/WkOi5B40nILc1VxAcDJ5uLjfViSlXP8igPYxzdSCIlqM8mhb6FBuxmJnkkQBrzvIPNmc1O3mCdyXPFRN8S46B16SVG7lIjvlqtNeIlaEQ0haXDJL5C6aKB37wWlWbm4CgoY/cw6bqK8rIV0oGSiMe7lx0Yol2MG4KPsnG9Ak/dhJTgQjM0Co1nkESpJcvE5ja29i/KTbT63+NWM4z1A3gnWLO3ojzCZPR2ViyyeLyiia4EnpnMoRxahrR9I46O5uQXCPqFHvrCu3h2KyTqGxNviYifB41/MjKt6ceeQeFf28VSuYDZ3ERfstHlahHLotd66AOQkVCHb25BqTBhGS2H9LZIqZwk3Axby7zP2FFji9Hwbe4k8ajCstF3fwSLdCIG5cktJjTpqWca2aVoiSyiMMuddDtLhEGs8Uzcw6D1aN4yziuPI30tBiYsmYxmGB2cUc7z5V4ljgRi9iiQoHZy5PdXRWcpiTCCpkaugV/YyPG7Tth7pCmLF1mMgln7kt4weSFwJFCwcGPgqLjH15cpmHx9yeIf4LOxeaGqGwIsPO9/H2VruMEEifbouZLoJ+zTW6ov2qGNUQzWk4XWo9EE+wJf7t1CHzbu6p79enEy86RkBibBl3eVaCThaAJacMtz9kOzZWf/kc8DR4URrPakuxcqibeK3yCDJJRgPjEF6y+A+oXcwEnhOkg2gd91pOcRtVeJ0E+7ksj6G+X5XW099eoHA8QqifauSjQsworWQdHQ664pSlyLxCBl6hRDxQrNPKjb47UqeQUIOQA3M+t0OnaNsDcGO5DH22zqT3VYdOplQtOr6GSkRZ4zE22wJsGQkA4xgXyEQuTeoBiztgG9bmNy3yjGFP40AYns2b9AyFKNXjOomobpg+a5mAUypGAGR39J
*/