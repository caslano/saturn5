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
8TsCP7eVhIpuYaqcv0+wUJ9fmPkuOP9aLdcCyVT0Ho0b5n3PsVBiIfMu1OCELlw2290WYVtdcFvjqjqdYUhf0ExxIVPosCMv1U7y/PAVkpqXSbvTPm91mj/TyfUMV1LPwd0b9EdYsK6UAdjAVACQEwkIZYt4vsgl5Fh0pXXViwtDb1921mZU1k9m8Fnda0NTL0z1suAyd6Pleqe5NeWguErKwUdir0vGkNeeSx0URO/IHYYJqK/0S+RpsogkTGYhG2tLeFiTMVDqbCuMb0/aB7dwy+o2OtxWq6qfFY21rDv1c+klb+u1eqdZRaWp0JklKlOkrB8EnhVvT6Vh1B3GG6p1iUY3jk4+7DqVc2v7dM79yB3jdvuXYuu7022S6/ovw9TtUpkwdfvkAsap/XUjYt1R4g6WN8UL/LGsCRD5rla4EkOWCduS5W/NnUTQG7Eph+W35FcE4wjP8XfbQCFEujI6vVvTKsbJG5A5dofWtgmlfeiF1oSB7xfTMvWrlm5ukeTjlyAXKdUMY7uUbhp0yintGr1m18IzEG34Y+ntzrdBMe5yvlNbu0PsXo2dy+JLjnQDB9vGSOfwMtvWG7hV0WHb2gn9YSXdYBB7B69xPcSD+NV7oqeV6PE6dClOTA/pFJmCgTuOcEB0VO/Y
*/