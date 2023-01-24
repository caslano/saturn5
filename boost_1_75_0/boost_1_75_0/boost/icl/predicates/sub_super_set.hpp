/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

    /// Functor class template contained_in implements the subset relation.
    template<class Type> 
    struct sub_super_set : public relation<Type,Type>
    {
        /// Apply the subset relation.
        /** <tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> 
            is contained in <tt>super</tt> */
        bool operator()(const Type& sub, const Type& super)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::sub_super_set>::apply()  
    { return "C="; }

    /// Functor class template <b>contains</b> implements the superset relation. 
    template<class Type> 
    struct super_sub_set : public relation<Type,Type>
    {
        /// Apply the superset relation.
        /** <tt>contains(super, sub)</tt> is true if <tt>super</tt> containes 
            <tt>sub</tt> */
        bool operator()(const Type& super, const Type& sub)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::super_sub_set>::apply()  
    { return "D="; }

}} // namespace icl boost

#endif


/* sub_super_set.hpp
Il4fO6ZAxjffEfUT8Ktpv312+lxvxyUriMGOBsdZ76YpsDfKP4NuaoUd4ZX3GIGnfQLq//gdRJ+Kqk2FfoiOh9z74kQCfWYSyvYUYrt01x1wdTTu90llS7QnhN87R6AdPtxE/NYOBOiA20r7dnhrS28EphnFHSwG3w3hZn+kF+1FdVM8+tCsJl5m2ocOlMOGHP31WN+BfUv7CvGt1z9h6GF0MpknOhLvOm0HozNcKu0vRxL4tgDWh4fjXdfNiCUH9eKaBPv9z38z6Xw/8Z5osBs8O09BHVX8HSsnq3ibbhuDur7xM4oz2Ok7fRX45iNXaGicsZ88FXPSs//h5tsaSQfsCxANDppC7fWnJ2IfVdR/Xq8/vErf/Ah55VOg4w7XryCupUYA/vhYtNOds8KBANVlA1PR/z75JBTq0/ez0bwFY9FWH7vm+6N0MgVv/zi8841SMo5MJVJVnP0/fAp8xHEetpYZuaQ+EIni7L9rAmyVtlNFfHNPL+bvGi/fdYFcANvHYY21wd/H2MRQN6UPVsC2G8BaWtRLOhZbL1fVHNIeVVMR7yxfs6QvEiXPdpAqXAF7EbSj6HcOT0JNtWdJdX09xa09BTbk3GuBm7vYXe+qaWxoctfXgrYFMUHHpltBI+iG2kWeFuA3TMMc9YaL4V21LbWLWjBHgVaRBdqUMtBa6hqbPTWLPS2ctn8k4iCzc0Fb3FLbDFwdYkWO
*/