/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_icl_container
    { 
        typedef is_icl_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<  is_element_container<Type>
                     , is_interval_container<Type> >::value));
    };

}} // namespace boost icl

#endif



/* is_icl_container.hpp
qX/IILATX8zPxFDcmGP74YzTmtwcfSzCg4H8LvCY6nIB/h6t8hnmVvcc5ZIvbU3uEvIyuWusDA/RXP1K9tn0yA78vSHyVzOf/Pz2O/m3COHAjcuDj3kc9uoY1oIwVWsNLnqyAwtSeFvzHuB14FHlXo94+EqWyzJWHFrG++VeWgZg6tmDgib3Bsg5pMg4jvgz7s9y+XeeeU7gSfE3Iqg8p8BD6R7R4Lcz/E0a/E7Auznv8jv8smXO/j8y+m/8bOA7lwdrp5d4+/9vV/Y0Ge+X91dr6QVB9zDs5b5GgxuAUx2+Hu+vUOCdgB9DnR3W6OOAl9BGr50B/roZ4AzCD3iUYSGe1+LJoFnrIAkZ+1AH6p5+HrCHPsBr043vUNqUeVoUuSUuD72T3OtAH1DxGv0+xEk/hf4k03v4/8+9ZPI40jeyFtvjcAR1RQO2G8/gC6cM22bZB7RPcypx+jqVvIQBHYZ9D4nTl65CI7Kxy7YppfDQjAsf6Xo8BYF4MMmtxIH25KWivQnI5LLZlx1rOE6PYdGt6T6Cpy7BduXqtcbcbbbKd9dsJebv9buSHk6p3qV8osrvUj53YVp8V9IrTzR4q5N/A4lN0dgTMvRZT8Zpp0uSV6ll71I+al3mXSq3BQ28K+npxRadlCO6Eh+Ht0E+CREYtW1THPdwkKJQIhn4HabhipF8huf2Og7brXBrULdCQbS8QBfs9PEHaHzhuPrNH94Y61Lh2FWmOTFBBOYkW1svu4Q6HLkVlIrDGk2Nj5oZKZTA8Kky5aM4iYwAqvd/rt92tDfsHNCz0tA1BrPSOCRSt3pbWiZ2c7n1FJhABIZ6tEvtWmMNp9eU4HjXm8UJ3MuNxJFkO9WVfOOBdTDJNNz75W04n7e3l6j2LqmSIEvk5bGs2y1erLorXZtF1rjK/Sb2it/I1scn5FtWHed0DKNWtXfMAvKDbwLN6CTLa/ImAEpuZEctEUpxwvMOlpB5OLtBGCww1AIKQajp9E4FNzsydEcBZ92+OsBwnBzon6owoWHsGDmLmtOS4mNV11zRyj40n1FwrygI+KzfWU5ZPD5ytq4VYcpqdeepQYYfPurMrQp4Uvw+CC9f5PHcjjn2R+Dfv68Gb/vI8uAtOBO4XIO3A34O88MVGrwb8FGcobyfBt8BeN0IBO+vwQuAH9w23V+fXLq0CRacYQ547HWYL4N2IdN0v9+ZB7fhuYLxgjsC2EKWtwLhJqTttx6Zr649QKOef2xF2A8YzQFfwrBFCIcAo/OPL8b7PIQlCIcBOxX05AURrgfsWz77IedRhoutj1oQbgb/h/IC47PWnEfJzxKEnwBG82C1/s77lKXlOK1DvHyvIDhg6hy6/QPLg3cnHJ4GnquO+5+5VPO5ETRN57o/oJ0LPn7xut8JmoFoc1lrgF0OfZQ2XfnB5vn9tSxX/bVf5tSt5OVG8JD8Bp6tpAfguSv1fug416d6dp7rU5V3AjD9/PahNy6zeV+olY36oJTtgpSN42cuUmcr3Dq7uA5LPb74v9BhyWfyGPSD8SsR7phDferteOGYtn79qNdvt39IPWOP8NGLy79z3X31bx243zKMy7fyLY5fYKHqO/oo9x1e4934oeb0OoEn3nvPQH+bRt/30f/PNeH/0y+/hrxS9HT/Bp8CN/MZfMub8VCMk5Na9K544Z27YTB+Wup8x47IypRWrLbkuu22BoT3PTOOl9I702ynbNlHUQDzzhCSfG9tnaFFqIdDZjw8RRy4jOMuh56utyOGHyfK+P5Uaivw0aE4nTPtj9JWLe0DYKpRROmoFJwWT+eYLzG0DSdS4fmVvQ7OHCYXTA+Yko+RBDyukg2pu4xM9URmLBMbHko=
*/