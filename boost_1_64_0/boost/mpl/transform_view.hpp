
#ifndef BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/transform_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(F)
    >
struct transform_view
{
 private:
    typedef typename lambda<F>::type f_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;
 
 public:
    struct tag;
    typedef transform_view type;
    typedef aux::transform_iter< first_,last_,f_ > begin;
    typedef aux::transform_iter< last_,last_,f_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, transform_view)

}}

#endif // BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

/* transform_view.hpp
bFlpdv0ZKE1V6rJU6qqamCUrzZo2MaLSHEulOVVjB8pKBy44Lstaaa6l0twqd56sNC+qpQMtlQ6smpgvK823dYuoNM9SaV7V2KGy0qELXBGV5lsqza9yD5eVDq8/NqKlQy2VDq2aWCgrLRx3is1a6XBLpcOrxo6RlY75sdjmMnKJEaBcVeNcoBEucUqa2k6vep5bpP7nmbwJTrXLZvcAcKaiwD2naTW4THaTRJ+Dr3TkcBWFYXjLU/87Ur3ofQnzK2oJuEhnplQCgm6xEHx7BkMg7ptwpQK//KO5AmgL7voVilUOU5KvjHBFnAkTDOMuMk0p0LzM5sUBXCqtGt9jTXea+sXHePJiQZnJoIAn+WbQ/7mAuPbPibX1rFKrJBwTG+MujDIpeXeq2b83c/86S9C/Lb0sqvevg6k+XBBsAw+qUFJLX7RO2f96/JcRp4h9Pdfoqud6fs1V3zpJ72CUkf/nZyo0IgQSO1n/KWBtL4oubkFsceN0cXeq4mbp4gQL6m9HhcJpbAY40qHCT7PxfbG1aOqkkC56jir609NVJ40FR5ulJkUWZLiYFCU08bJQbhZ/Cc7Jplggv1CVIPyvaZHK2E/6We7fO5u/n79ErEBx+BFQmfkXo2OY6BHNQtrm7vuDIOasPTXLBQpaWF+ShUxx0qfGgQ+cJ4Bwlxqrp4DzVEC4mykvOYE9ArBA8e1flUv51D+sqKYU90oOKX90Rt8JzWnOMf+kie3ekvj2E6YlgFewZAntURCjsKjQaJk9CoLnsSbgYS/aXhY4/elMbRg71n42d0Dn8xPX57XJ8ipVea23b5EdJ166z9t/jmxKzHjOhP2rs6z3o0NFO6uKtkq58SZlt2kHW1bu6p+8veix9pD8rO+IJW9TQdFjFQTGpoKS9ZVCo91OSOKlJX8HLcJbyQZcHZiz6pKtwc1pVSVbKSK4Ja2qfAdlDRppVUWbwmXbix7qgDLXdaU/KOshKrN8U0H5OpT5SBKVSUK1HW4qh2zGyzLLtwa30DXCrRQR3ESkdQdlDdaRj6BNVEv6C3SD9DyhxUjBjsHvBwvFYArSRdNB/n6Ud5sjnyCELHErFbvNno8C7VRg3dPgozY5AqL246l2SkkF3dRxiUvmwTtkEjuqAcFNqUvSdAGAyK4gchBEvssUTMf5p1qybsLd7k3bizZCDkFusDci58bYNMHAxqRADoEFfW9uSn5Fe1XuiEoH6fq/iKacZ4FkK92spI8obCvl5osH55F4SfeSvxt9t/vE93EOMRA1Ahico6vuG+TrpOocjITdHOiiFLw46eVZO188RjKni2BLX3qTrYnvI+Zfi29v7jOTVlysP+lUbvqEq8qAIcMe/D6/olB5XQTsyWnU7PkDpT8jh/6WX5ER820EMOli+iyjbCrKyJ+xI81afYYrNKHjrhk7CqtKaqJh+Cx/xpa0iMKdaUklNXQVmdw/1ugu8hP61nz7Hj6lYiVdub1orbxRLsSoMGy4WlCAGSU1haQmvLzM2DZQ8nkYoRolWU3umr5YcCnah9MLEzJ3aqjRt/gUmkQwlGwkNBkSIHnWxuCW6VXlG2WHUZLJHfZHgM+fQhNcu6qKNgQDG0Sukg3BzdOrSjZQ9oLyDew9bgjhZEHRBnVY2I+UyAjenWXGMZ84WCAm6iS0EolTwkmUnK/nXlv2/+u5Lf7p+yk/lETeF+rOjpuHKN80aWyZ9QdbXPloqVtLL8u1fHQvPlJJb7Kat8nrztXixJneWeL8e1wMe3jTCap2QWNulef5C3XGGcj42VjF/F0smFJD2HiFWVC4yIQ4tOI4sQkC+3C6AmgMA8QGpFnUeoi3XuGX0AOmtfX9/P3fwB7q9V4=
*/