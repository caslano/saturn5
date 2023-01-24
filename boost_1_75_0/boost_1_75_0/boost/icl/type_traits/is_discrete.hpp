/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410

#include <string>
#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4913) // user defined binary operator ',' exists but no overload could convert all operands, default built-in binary operator ',' used
#endif                        

#include <boost/detail/is_incrementable.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_discrete
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, 
            value = 
                (mpl::and_
                 < 
                     boost::detail::is_incrementable<Type>
                   , mpl::or_
                     < 
                         mpl::and_
                         <
                             mpl::not_<has_rep_type<Type> >
                           , is_non_floating_point<Type>
                         >
                       , mpl::and_
                         <
                             has_rep_type<Type>
                           , is_discrete<typename rep_type_of<Type>::type>
                         >
                     >
                 >::value
                )
            );
    };

}} // namespace boost icl

#endif



/* is_discrete.hpp
9EMVp2B1IGpwpFo/YXEFGABXyl2PWnzKfoSNN4M7KF8NBg9hgln7gUFqKsRwAxOjI/2Oeyc/+RbT2BRyx0YVwt8vtIRvyaDra92epathtJLZg46KXElay2FFGCRUlIcJIiVhq+3QWaALYabQGBFv9jL/OitZ48p6aCDx5HemrcX7i2XV9HcHCMGzLRc6+cuIWVKybiwg++Xe9wlwUOBbFXucgOnKtTW4TsIcYz5QMZNfbmcoiDME/Zekyj2cnUtaXglR/fPc3TcWWXlfieaPWyTUCUwJc5fyp+6tXDOG1849zQeyZeZ9Ivo1DDz4Car4PPf0j7WK2Pp5jiUfWKbnFztmY7Dy6Y/1fn5TwdDoOIhsvey+Dn/w1O9Tj9SwwCdi+Oc5n3xytZ5f4xhKf4UtI8ytRU3d/1ZmXgWxoARePGebD5TIzBPd+Wb+azlLCqQOS9l7fcM2EkmXSoj+GpmPvoex+TC8m6YdX0rmPnkQCjryDY9y+Y5mjLr/6yEZRYrP+5aC+Ofo65k213eG9m/Y4vBlQQkh6AfcLb3qhGeSwOaT25D5AZp62FKqTnijmujxyK98rC1rSCYtbDgmPGewKL3bC+AerJofndHNBxhbDuCOU2McWw1giwtWexr43fVAdS/YEun0tzgBAClAtWeRkXn6l40qS5Bq52lgDsOlmPU5ZWvm+Nr8Th2GaqTU+c4Ce1NH8ajuNf7lXDVG
*/