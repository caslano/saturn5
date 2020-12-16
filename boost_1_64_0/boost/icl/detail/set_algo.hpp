/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SET_ALGO_HPP_JOFA_990225
#define BOOST_ICL_SET_ALGO_HPP_JOFA_990225

#include <boost/type_traits/remove_const.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/concept/container.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>


namespace boost{namespace icl
{

namespace Set
{

template<class ObjectT, class ConstObjectT, class IteratorT>
bool common_range(IteratorT& lwb, IteratorT& upb, ObjectT& x1, const ConstObjectT& x2)
{
    // lwb and upb are iterators of x1 marking the lower and upper bound of
    // the common range of x1 and x2.
    typedef typename ConstObjectT::const_iterator ConstObject_iterator;
    // ObjectT may be const or non const. 
    typedef typename remove_const<ObjectT>::type  PureObjectT;

    lwb = x1.end();
    upb = x1.end();

    if(icl::is_empty(x1) || icl::is_empty(x2)) 
        return false;

    IteratorT x1_fst_ = x1.begin();
    IteratorT x1_lst_ = x1.end(); x1_lst_--;

    ConstObject_iterator x2_fst_ = x2.begin();
    ConstObject_iterator x2_lst_ = x2.end(); x2_lst_--;

    typename ObjectT::key_compare key_less;
    if(key_less(icl::key_value< PureObjectT>(x1_lst_), 
                icl::key_value<ConstObjectT>(x2_fst_))) // {x1}   {x2}
        return false;
    if(key_less(icl::key_value<ConstObjectT>(x2_lst_), 
                icl::key_value< PureObjectT>(x1_fst_))) // {x2}   {x1} 
        return false;

    // We do have a common range
    lwb = x1.lower_bound(icl::key_value<ConstObjectT>(x2_fst_));
    upb = x1.upper_bound(icl::key_value<ConstObjectT>(x2_lst_));

    return true;
}


/** Function template <tt>contained_in</tt> implements the subset relation. 
<tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> is contained in <tt>super</tt> */
template<class SetType>
inline bool within(const SetType& sub, const SetType& super)
{
    if(&super == &sub)                   return true;
    if(icl::is_empty(sub))               return true;
    if(icl::is_empty(super))             return false;

    typename SetType::const_iterator common_lwb_, common_upb_;
    if(!common_range(common_lwb_, common_upb_, sub, super))
        return false;

    typename SetType::const_iterator sub_ = common_lwb_, super_;
    while(sub_ != common_upb_)
    {
        super_ = super.find(*sub_++);
        if(super_ == super.end()) 
            return false;
    }
    return true;
}

template<class SetType>
bool intersects(const SetType& left, const SetType& right)
{
    typename SetType::const_iterator common_lwb_right_, common_upb_right_;
    if(!common_range(common_lwb_right_, common_upb_right_, right, left))
        return false;

    typename SetType::const_iterator right_ = common_lwb_right_, found_;
    while(right_ != common_upb_right_)
    {
        found_ = left.find(*right_++);
        if(found_ != left.end()) 
            return true; // found a common element
    }
    // found no common element
    return false;    
}


#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4996) //'std::equal': Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif                        // I do guarantee here that I am using the parameters correctly :)

/** Function template <tt>lexicographical_equal</tt> implements 
    lexicographical equality. */
template<class SetType>
inline bool lexicographical_equal(const SetType& left, const SetType& right)
{
    if(&left == &right)
        return true;
    else return left.iterative_size() == right.iterative_size()
             && std::equal(left.begin(), left.end(), right.begin()); 
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


} // namespace Set

}} // namespace icl boost

#endif


/* set_algo.hpp
wSVg09XbBbXMiZhpoY5h3MMkaT2dDd0aOgqPmFg2Rd20qybxvUuB/XXarwufnl09IUFZZ3k6bGsWucj+KLuWzR15tL5L/VTtl+PRr4CMG/67gJF4VJ7bdVT+2j6mFLEZgnx/UWZeKqxuf2LFFamGHVh3WtnrxIFjl8kHdrwQ1brSWnqopq1aRn1HwOe0gzsYtZri7r4+rr8/Z128D6l6Z+RenfrNOjvfdW1pOiGm1X5oOFs0xBDdWT8P7gmCp9SDG4pUigt06mquTvsUd1awla4NLShhEScTbdzFfOAT1qJJLzd2N/9XfJaOSbd37KRtf9mRcy+P7FWUrhB9rvHmqYz0+iNdV8zxwCTbMAK2+H2oLXwfAjmm07I0EhfUXFdZkxFuy+6l4yT8l80pRjJJE8HBPn6ii9+bsXLiqYi5Syq6f2hkrMX1XOvOk0wXD6ALtYfndklsHLzoaHzWg3/nFyazILS6UJ9Ga1CmumnFXhzt5TfyCSElBVbJKmN+N4aGJyu3PvOnPtb26ITlOeozk6saX4YK1Na+kdGdbHh0rOUZbf5ux8/06cVWpDH0YzI76/OvNOp28PYOBmQeHhZiJg0d91V6YZvh3ozwym3Ozw658Z6FzJom5sgZAxn2t2cPKMkpV5cmmNgcKUnaznL5XJkBqwhZ9PUMhtdjeh6cr7auVeMtYUm4vpsU/X0MWLcyIaM0XyryDCYnzuj1d19l5jKwDm3T83vqsX/fUI3IW+0d337HfdufPPrL/bXhT+YVo6Tk3l6urC95mqMnKMV/UrzxuFSXvhLc0wunaOdauRVJ39Vgq2jR8jz1pIOyxDntxHbCtmDx7OZtfnGrJGrekt7HhjnZWXY5XHzHKh87/c5UrXi0sin7254FG1jVuG/dXa3ikusAP+NpEKVJvlJlkaLpitOvs7/8lCdGVZYVeOsSVV1H1AeaeBraML11oz4UjkXvpUu01Q4p+EmgYp11UQzS3WzAxeOhXU5wp07ROnorhobH+2WG223KbCetbocDt1u4D0onk7BwxnS3Zd/+NgFfPmn1rln7sjKJUPBznrr3xzrMz3/dYY25bMqv+rk9z/Dc2SbHnWecQ+mcbbijT6DfuJyGdJqCMe19+mvpL54ss7vV8PdqhtwbSWZnQsNMtJZ3PUjgGNDf4T97qKv2PvlVqV0r1lgwvlN7Lz/hfTB+29RJ8offeOJrP9KvoqVGKXTLvt+HMAKAB/rJQkX153P3/oGX/CcozBXCT8lUPUwJTfHSODd0bznsebGDus6OvuvwdYlivqGaZ/PD1D1oHBIZbsQ4plXA7OjBK+feWk3wH+rZaZIGnqcNMoUuvnpaXc4Qbn1lU2/HxksuxoIAGBw18E0dPv2J3iT96UZq5lYKnOfi93ZkWrCjNl2TIe/X+TYS4T156EAk/PwEjs/BINTRUd/WxWnK3rCXR4HX1S5rWt/GUVh1xGQDBHk6llKxHD+R32FoM9VFnRs9vKnsxUyeOMXsrfH0Z5fXZm46snm8cWdv4cqA3YOSEmWzFhL84oM0eapNXEzvaGYjmT4v3QmQ5dEk30x2bDxWc/XMd7wX1znvEZERrq9+WtfTYb7mr/FWIPAFagUG3q10cKdzeKfM5s2rE4+wQSYKNrJEvmu1pBVcmelMG8MOtaXCTZtbLpj0ssuVzSx8zWaxR10u7v/CF5QV9fpeXz2BUVk5xsadfuLlKKNVB7us3LqJkGHlcIeEpbsGXd1DVdn2fFw9rlG+P/KmAIAeAz2hOwcWees6Fge5b/hrvN0wyh3Gy45wcBCMj6wLfBYRWBA4ODi49743vnaW58GB4PiRkcQruz7ZHu9YJX5Rfs3bzXs0X+s=
*/