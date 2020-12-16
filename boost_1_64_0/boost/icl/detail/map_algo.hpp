/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_MAPALGO_HPP_JOFA_080225
#define BOOST_ICL_MAPALGO_HPP_JOFA_080225

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/set_algo.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        

namespace boost{namespace icl
{
namespace Map 
{

template <class ObjectT, class CoObjectT>
bool intersects(const ObjectT& left, const CoObjectT& right)
{
    typedef typename CoObjectT::const_iterator co_iterator;
    co_iterator right_common_lower_, right_common_upper_;
    if(!Set::common_range(right_common_lower_, right_common_upper_, right, left))
        return false;

    co_iterator right_ = right_common_lower_;
    while(right_ != right_common_upper_)
        if(!(left.find(key_value<CoObjectT>(right_++))==left.end()))
            return true;

    return false;
}


template<class MapT>
typename MapT::const_iterator next_proton(typename MapT::const_iterator& iter_, const MapT& object)
{
    while(   iter_ != object.end() 
          && (*iter_).second == identity_element<typename MapT::codomain_type>::value())
        ++iter_;

    return iter_;
}

/** Function template <tt>lexicographical_equal</tt> implements 
lexicographical equality except for identity_elementic content values. */
template<class MapT>
bool lexicographical_distinct_equal(const MapT& left, const MapT& right)
{
    if(&left == &right)        
        return true;

    typename MapT::const_iterator left_  = left.begin();
    typename MapT::const_iterator right_ = right.begin();

    left_  = next_proton(left_,  left);
    right_ = next_proton(right_, right);

    while(left_ != left.end() && right_ != right.end())
    {
        if(!(left_->first == right_->first && left_->second == right_->second))
            return false;

        ++left_;
        ++right_;
        left_  = next_proton(left_,  left);
        right_ = next_proton(right_, right);
    }

    return left_ == left.end() && right_ == right.end();
}

} // namespace Map
}} // namespace boost icl

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif


/* map_algo.hpp
jK2o++5q7EhcJsz7n8ePvP4II4yu4F5+DQ14ieHqhR/QYGUf0u2khxuue7G9LfYgLHkbe3SBC5mSmiHp1ESwqkFIQLsR8O3bscnwc9CskoCFPdsODkqNOK1kP/h3JuH3Z0JBenUxqk49jSTePsRy+ol3z6zMmEqdPPzGb/zGb/zGb/zGb/zGb/zGb/zGb/zGb/zGb/zGb/zGb/zG/zeEhc2Jf55e9h6+vm5CYsJiwqIO5rY+wV5+nub2tsQ/cUt3fzc/Ydt/rI2n7fdNAAAAA4BUDOD+aiD0yADhPg8Q1OiAsH0DEDpUgbByIxAadIBgagMEAScgrBUCwgOi3IGY38kABFiAqj4Q5IltYQnOcgLhMfFhlwICoywQKIltCrmAsHk3EISJ/dgR82YSQJjmAMJ5biB8EATCU+7v+1grDoRV/H+WqYsCIcQCCJpm3+oUEdvAL+IXbOTr7uX2nZFUlQF0iC0MDDTZVJXZrN0cPX2c/ZzcF8vTsD8/AAAN1msIt4hPzwYqQs56KgKBnYqgy0JFSCampRxUBC8WYspFRXhIfEaJT+laYh2izIubWJ/4sPFQEUSJ7wAAXjzE93XEtsR3WEf1d3X8u7pZWrvb+zn9oJuKgaKQrrXPH4vsfXwBALgFfL18nANkqRfy/jbE7A+ouktHWLZk7skA4Mpt+j/JMIA/FTTarCGQLJRTAYCa45rvdDAkvlPQf9+H6Q8yKgAw/5PsW78rbNcQSBfKVwCAFbF8af0g4nv4WqI/kQAslR8gypkliP73gzyZKHe2AsKFH+SZRHmp1J/tTrYgD1oY246Ywg849xN90pLoCHx6QAAMACGEAACKiPUapKi+6tP5gz7E8m99LNEnBQNYKm9e4J36g/w5Uf5Q6nt/UbP781xI2v0l77eOa/6C4yRR1rOE43G77+dy8oe5LCL6g/DW73W/tiDDlrTjqqYn7OH5NpfP7b7Xnczp+34nD9P9hU3piXVGpai+m3M2ogw2fZOtAAA+omwpJwIAiDr90WbfONEDgPSibLGOPXEeF8qZAEDF6fv5MHT6k72+k7kRZWq7vpdFOv3J377a7Zb9N12pACCNWL44prTDGgLZEp7Nv2CHogX9jizp8xpRZqDyZxm2YAeCxx9t/usx8r8Vf4pVlgbqOwDAVYz4iBMfCQBTGctN4pa6qtqGito6WuqKmvBneAl7+jnZ+yzmPZSsfZ19/5T38/qW9/qad4fFvpTVFPUVlQ1V9dUNDNWVLQ1NdOBrn8TQ6G6/kLd1svax9Av0BAAAcHC2d7MzDPay/9rPdnVVTRV1lW/9Gukbq36r+6cSAFt/nwB7ALCx9iUmAJ4+dn9ibevpYG3r5+nzZ911iZS0VImcDAAAAqzd/O2FPYhR285ysf03udfXeP5N5kxc1pxtnf3cgpUVARb61Pi+V4A/Bn5rP3sN+2AAAIBvPS22sdTVVzdWNFTVUN31a2uOr4eYsO0/tk7ZOtnbun7XSElIbJPEn1JxiYVU+s+ppKjMn1KpzWIAoLFQT2OhnsZCPY2FehoL9XSFxGTE/5SKi0v+OZXa9KdUQvrP71LiYvBnpGAA9AuxAAMAUdViz0YlEbsPJif4HkexvetlT2lH3wNfzPwV+bwdOznzm8zIwVUFQxd8uETV8aqu4evbr15iSjxHUyqa/Cmsnu29cm4cTCLqL/sQYTUl88YTqPFFkC2B9oMrV0u772xg7vpgNVq0BOldM5voXe9duvKIT2wp73ULvGu9JXekt9+d71Qtz86/eiHJ5fjB2+gHLP1Z+Dd0wq+QU0evICu7MKUobqyrUlr5rP55Ne9yGWVOI3SlkmZFreuV+r3idMlXd5Jef2w=
*/