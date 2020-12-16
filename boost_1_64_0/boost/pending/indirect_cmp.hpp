//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_INDIRECT_CMP_HPP
#define BOOST_INDIRECT_CMP_HPP

#include <functional>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

//: indirect_cmp
//
// could also do this with compose_f_gx_hx, and the member binder...
//
//! category: functors
//! component: type
//! tparam: ReadablePropertyMap - a model of ReadablePropertyMap
//! definition: functor.h
template < class ReadablePropertyMap, class Compare > class indirect_cmp
{
public:
    typedef
        typename boost::property_traits< ReadablePropertyMap >::value_type T;
    typedef typename boost::property_traits< ReadablePropertyMap >::key_type K;
    typedef K first_argument_type;
    typedef K second_argument_type;
    typedef bool result_type;
    inline indirect_cmp(
        const ReadablePropertyMap& df, const Compare& c = Compare())
    : d(df), cmp(c)
    {
    }

    template < class A, class B >
    inline bool operator()(const A& u, const B& v) const
    {
        const T& du = get(d, u);
        const T& dv = get(d, v);
        return cmp(du, dv);
    }

protected:
    ReadablePropertyMap d;
    Compare cmp;
};

template < typename Compare, typename ReadablePropertyMap >
indirect_cmp< ReadablePropertyMap, Compare > make_indirect_cmp(
    const Compare& cmp, ReadablePropertyMap pmap)
{
    indirect_cmp< ReadablePropertyMap, Compare > p(pmap, cmp);
    return p;
}

template < class ReadablePropertyMap > class indirect_pmap
{
public:
    typedef
        typename boost::property_traits< ReadablePropertyMap >::value_type T;
    typedef typename boost::property_traits< ReadablePropertyMap >::key_type K;
    typedef K argument_type;
    typedef T result_type;
    inline indirect_pmap(const ReadablePropertyMap& df) : d(df) {}

    inline T operator()(const K& u) const { return get(d, u); }

protected:
    ReadablePropertyMap d;
};

template < typename ReadablePropertyMap >
indirect_pmap< ReadablePropertyMap > make_indirect_pmap(
    ReadablePropertyMap pmap)
{
    indirect_pmap< ReadablePropertyMap > f(pmap);
    return f;
}

} // namespace boost

#endif // GGCL_INDIRECT_CMP_HPP

/* indirect_cmp.hpp
IKelXHUe8Yn0m/K7n4ttqL+bcC5HWnX3zQeyILUW7QJZgPp7ksshK1H3BXpAlt7VLrcPZBUt6vwPsgZ1ZnSVyJap8z/IHPXdJQyy9tdt2fUST92hulHapmxjpJTxhS2LhSx5tbr/B1mL6t9xkFWrM+Rkkan+mCJ6UWmniw7O2mlnQhaTqO7/SX7qLChH2qvuTNwjfbTLLmO+lKvSFkm8d+36LYQs/5A6/xO9qDsEj0HWXfnEcqmL2tuvEF39Up3/SRlp6v4fZFXqXL5K6tyozv+k31Rf/kR0pdbjz4qs1ZbVSBmq3F1ik0rPr0h/qLPmVyFz1Dpsn7RXnQsclPqpPclvpIwfqPM/aZtqR7PEC1Hnf9Lnqoz3RadK9pGMwZPq738lP/Xd6ixkGWrf/Zm09x077Zdi9+qOnHcA2rZJnf8FoH7d1P0/yMod28deEYA6Kx/ROwA6UPYSCJmj9m+DA2Tvov7+V8pV9zxCJT/liyOkzm3q/p/UZaIt+5bEU+XGSDz1twXxkNWxjL7ODdgJy4YJe+wwbycI6h5ekFVU4Dh4d2N3lww/EbvjTXDePU5HOk9JF+PtNH2MAP8dPi8zoyDDpPP2MDLz/0U5fMyklODUMbH2O4RfvZtuv/P1/OpdokrX1euSdypdgPdX75JVuh4+l7xT6Xp3+updikrXv/Ml75iursq8C/KVd2w5ngGXpGvZ/NW74PlFEnS838j3x7dc8v6BBx7InDXHKrfsp+Z9wezgxFhVp/KtX72brtpSse0v71J0ulU/++qdK10l31U+2/GuqKM+Rebd5lHmXfj2jndZbGdH/3s5ssGHTx/TEaduOF/2Qrp2k67OwePldLzpkBfI3XbI8V7k+Ac6TF7eTle8wLr828wr5ytbavX7Ki9vx7wJHmHelTvmHeJ89e56864H3xV0ueTdN+08yy59F2nerRlq3uX3uOTdDaaeOCHAG/l3BGjz4eGz75zzdZv3cfiGuuok6RpwVtSJ6ebNnzebYyz/knSdnI43weER5t1QH/MOcb56d73Js7Pk2YK1eGhHnNHD52Xl3jvbcT/ux/24H/fjftyP+3E//4OHe6iOPZUTIAKE+O+lT8deizsH7KE69lId/+DV9ZdG5HrRRJO1dsea2/k2wsEIL3kuXTdjHd2xnoYQpSC85Ll03Yo1K1LhvSfCqr8Sj+tUrFs71q+OL8If/JV4XHtiLSprUrQX4U++Fm+0437cj/txP+7H/bgf9+N+3I/7cT/ux/38Hz35uJ+TjdDT4bYff7PdV0L+7svfHvx9j5+344+Qj29EF2/n8kt+X4N/nG7gJb9P40PnFZf8dtyP+3E/7sf9uB/3437cj/txP+7H/bgf9/Nff77E09fvutPp+A7f3NtxjuLO/jWQZ32OW9cIt2WYMGeMCfcs8OwIN5WaM4Mlp83viY+Y/6/AaQPNb/9Ex4lAGB/g1fF7/WiTfvsATxPean6ff8ikW/Cx0/E7scKEB1814do2E//EWRNuG+90nC/kvGze98G/Z3O15N/Jy6R/0OS34jqT/64/eqKeKOeEp6n/HCOfNtP8Xn7Ow9Sf8Q/dx/LSTbiC8ce/6Jj4E4x++gQy/zmeptxKpyMszDO/Dw8y73c87Zj0E8zvrFnmffRqIz/FcOFbRp9Htptw0WK2Y7iJf3G2idd9mQlX1Jhw26tM/7YJB/VlOyo8jR4r2V9vmnynMf89bSb+EuY7t4z5PmfCBc0m9Gc+ft8z4elVRn72PPXG9s5939PxRbhlEu2G8RYNML/jU0x45FOmZ30PJ3qY+qeZcPUF01/xt5vfPWeZ8MQCE38U/nbMS/K/jfHjTZjxkmPaTT3n0I4PTzM=
*/