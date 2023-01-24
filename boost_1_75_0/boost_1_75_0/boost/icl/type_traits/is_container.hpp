/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
kvYkGGn3uN9g2jMR21/VUrNLa+1CKj4ehxG2xwtyhkn2QrQzR/JHaMo96V08DZ8q89GUeyY+hpPsR56Gb5RcJ5ZCFcSoE2w+4XUpbkmX6lKIfdJNimzNMuYRFHnPjZg9z7J3x+JCmuLhXAfw5HjGXih25l7cG4VEeSNjyBTfKdSXnhVB3MPLU+SJ8RYpRV6hVHd6ejx5b46Qy8Cwp4wD0pmGXUEPQot2mOGXcZzpAHSh8ax0+LnIqAfp4PMoJdZpZ3G9Wt6fJ1Z+piRT2tdpd+SZ76OyPbQrta3g02hHno25qsl64LnU+HbLQWbb98bYOyLUoXSIWZ+vzYeSqb5otdkax3bPFCpG2EDEFymt5m3HlDBcabVstdT24dBnYrxklIA3LSFRegHo4tYxLpA+F3tLDeXIV1ql7YJaObI0PMeUKCyOGIubyhCWLzQZI5TY4WONPsZ4zpYrVxGXJRiumD5n2lLIhdK6NW3v1d5H20na/ii0n7QmL+CldXShXeUtIpRAy2Ve3ucv12gxxLH3SEvyjDAOeNtl87Bcj7ZL5owr2/h2/bk8/l4Rnau1Ow0FM85SKt+yzZISyxSzOSZXerZRNrkdJPOMUayy5AdLzc8JHaVE78dibFXru63WA6+cxnSkhSjszbHGgbW98rQ8lsOuTPBoJeZJWNOezNihY62eaH3EOOCqMYzR5noLg/GWEbxeojbvKNfsFzOD
*/