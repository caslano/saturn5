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
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
*/