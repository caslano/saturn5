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
iKjVogHT9zlDImOKl+66CdekjjeBoth7DtBuy48/m1D/cpId/DDnGfUGUA4rSq7+JlU2pG4gfY4s6fiHSuPgwWR/zCB1oJsexx8C4bvKhc0sSwXbjOmGXrpH/AFt85qY42ja3/K/bYxbuzeCHqfCGL6wL88eJ1V2Ya1lvUeFQE7ijBvptd4PF4N6cX772iIp7xdc+uA4xr8TQZ6brmzV/j+3KPJHoAFZNOxIxr/jHY8RYSlwAPaDgbks3iqVALlRznFQ/YvorJ2HYI/yNjQpqbLci9TV7iTP9OVtINU+f9QaKFSx7s/gRMBnkoLUNcpq1KEKaQ6Aqka0ABcXNWl1EWUUGn/vt02mNtWt6WP+yaqRrCyv8P66tvusnb7tUev2ZR9TxNnfXRSc6Y3MT+t0LUku8kOotRjeMEKNQoY1BbwLs4fPNcoZtOjY35imZWq1muzMJ1K32mVG1og7zSCSCntVbSVuvE0a6MxcseoBdMWW9Z644tjak670puJ9knFgHjMT53oKFlpFkXJTL5qLQiBtS91e8wZwcxbCv7Z4CAfuzMvE9zyuagqsZw==
*/