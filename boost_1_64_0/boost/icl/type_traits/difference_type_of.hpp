/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911
#define BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/type_traits/is_pointer.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(difference_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_difference_type 
      : mpl::bool_<detail::has_difference_type<Type>::value>
    {};

    //--------------------------------------------------------------------------
    template<class Type> // type_of(T-T)==T
    struct is_subtraction_closed
    {
        typedef is_subtraction_closed type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_numeric<Type>
                             , mpl::and_< has_rep_type<Type>
                                        , mpl::not_<has_difference_type<Type> > 
                                        >
                             >::value)
            );
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct has_difference
    {
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_subtraction_closed<Type>
                             , is_pointer<Type> 
                             , has_difference_type<Type> >::value) 
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_difference, bool has_diff_type> 
    struct get_difference_type;

    template <class Type>
    struct get_difference_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_difference_type<Type*, true, false>
    {
        typedef std::ptrdiff_t type;
    };

    template <class Type>
    struct get_difference_type<Type, true, false>
    {
        typedef Type type;
    };

    template <class Type>
    struct get_difference_type<Type, true, true>
    {
        typedef typename Type::difference_type type;
    };

    //--------------------------------------------------------------------------
    template<class Type> 
    struct difference_type_of
    { 
        typedef typename 
            get_difference_type< Type 
                               , has_difference<Type>::value
                               , has_difference_type<Type>::value
                               >::type type;
    };

}} // namespace boost icl

#endif



/* difference_type_of.hpp
rUJaE8/vdO+M5P5psTkJzGUdXb8zOXbzWJHrqst0q/OS1zhRy8fhci6vtS134Lxonl+V+rz4gDYeJd3b4eqS4rLb+a/n1HmYfbi1ySnwiXIeOvZSfNLY2obWVDyJB9r7+DVGioLPZXHZ/XJYFzlUccWNpRIAu4FoNfBIKNFW4BmDsg7EfGA26FUGolexfdqgvA++Ftsl2G4D1huUdQweBv4Sqqy38Bq267B9Fvgb9l8ENhmUd/AXAHNAbzAQlWK70aC8L94ojOhW4DagMdAEaAg0AG4HRpLyvuwoIrqfiATwmgO12TuEe0KV9/V+Bn4D9oYq78h9j/3d2F7F9hLwJvavYPsL8DuwP1R5R/QH7L+B7TVsvwMOYP8nbH8F/gAOhirvN17G/lvYEmBn71s52DtUk8G7mYjmE9FKg/IO06+AC/uzDMoczYOwb8revVkENCEigc0b9SCiXkTUnM0t9WTvSSwG7iKiKCLKJKKJBmVMuDcRjSOiPkSUQkTtwbew5+lhodhK/gCTwG9BRC3ZeHwnIroA/jYi2k5EM0KIZgI1wKsD27pAbcAIRAL1gJuBW4D6QB0iGg7dUDZ3ARZ52JzAAjAfAu8vwCNAVyJyYluXiJ4noq1EdBE6DxiQn7QfQvQNEMHmu2qyOa7FbI5tA5tDW8Lm8Bay+biVbL5oFRFNIaK1ocqc2ho239aWiNoQUTs2n2eW8oROERFNIKJigg9sPqEeEd1IyhxMOJvXyGfzDB3YHICXiJ5i4/VPsHmEpaHwB4gAagHhQE2gPRvfXh2ijPGvBFYBOyU/2XzBN+y32AvYc/wBA8mpZhjykiD5aVDexdtBRC8R0SQiOgVec6AZMB8QADfwKjAWKAKWAA+HEn0dQuTB/ufAF8CPwBYiupfAh3wYETnAawIsA/0Y8DiwHHgCeBJ4ClgBrARWAauBp4FngDXANwaiUdi+EEK0FXgJeBnYCGwCngM2A9uAV6QYAK8CJcAW4HngRWA7sAPYBbwGjAsl+sxA9AIR1cX+NYDCiF4B71FC+dAJBW8EEXmx7UJESw1Ec4HpRPQgEcUSUQIRLSOiPCIaTkQ+6LYBWgMvAzuA7cBLwGUD0evAtwb4BcwE5hHRA5CNJaI8qZ7A88DthPph+xywGSgBtgDrgPXABuBZYCPwKDDZQDQe24mSDRG9ZiD6CHgfOAZcAXYDHwAfArOBvUAL6LcEbgVWGIgaYXsb0FjyAWgIRLP3LQuwP8NANNWgzK0kEtFkIvIZiCyQHcZ2BLZvYPs1sJyI/sC2M3hHgDuALOA94H0gCvgO6AS8A/wAfA90BAYDPwE/Az8Cl4FfgCtAE2A1m1tuBghAc6DEQPQcsBnYAnwJfAwcBYql44FtHWwTga5AN6A7EAf0BHoAvYB44E7gHqAfkA7cDfQHMoChQF8gBkgCkoHeQAqQCqQBfYC7gAHAQGAQkAnEAl2ABKAtMARoB2QDHYDaQE0pnkAOYAUWACKQC5SwtUymAPWBacCDwHQgEngImAnMABoAs4AbDESTJP8M8AtIA1KBueDNA+YDNxmIbMAYIB+4h4jWhRDdaID/wL3A3UAmMAjIAgYD/YB0SR8YDowAhgEDgCHAUCAbyAD6Av2BeqFErcKU7x3+DvwGhAGdgA7AnUBnoCPQBYgH4oBEIApIAO4AYoBYwCi1UYMyN9kQ21uASOB2oC7QWCoTqA/cBjQAbgUaAeFS3WA/EtsIYDRgBkYBJuA+YDMR3Qh/a2A/BLgZqAPUBozA30KIHgUeB5YBtcDLA0KBp4noGSLqiv0ewF1AL6AnkAR0B7oBvYFkg/J7BJL6KCL6iIiOE9FJIrpERB8T0Sk2//oVEZ0=
*/