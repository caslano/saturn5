/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/extract_value_type.hpp

 [begin_description]
 Extract true value type from complex types (eg. std::complex)
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_EXTRACT_VALUE_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_EXTRACT_VALUE_TYPE_HPP_INCLUDED

#include <boost/utility.hpp>
#include <boost/mpl/has_xxx.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< typename S , typename Enabler = void >
struct extract_value_type {};

// as long as value_types are defined we go down the value_type chain
// e.g. returning S::value_type::value_type::value_type

template< typename S >
struct extract_value_type<S , typename boost::disable_if< has_value_type<S> >::type >
{
    // no value_type defined, return S
    typedef S type;
};

template< typename S >
struct extract_value_type< S , typename boost::enable_if< has_value_type<S> >::type >
{
    // go down the value_type
    typedef typename extract_value_type< typename S::value_type >::type type;
};

} } } }

#endif

/* extract_value_type.hpp
g/hpLfFhbeRjsv9h8rbBGAAyf+Z9I4uz8v8HvP8ggJ9F5v+GHxnBEn2ync1/Qf+x2MeX1XB2/r649PxTOO0fgbPzL9qutLv28y8nden5x5P97dNaXCZ35To2PgG+Jqt/TOHK5CR9LKd0ZUSvyFWW3w+md2n9vYQvytpnR7hyFJtfCmf1NzODK4+Q+QtmRsSz9l34lCz/hy/J2p//cnL90Uwu7d9M4HR8Enw4Oz/FczhrHyoVr+F0fc9+J+nbzDzeKO7D2f1N4cv2DNRP/7t+Wz67K/f3v9+W+d1zuPJ9j/39r+d1ZQ94OOj9W2nkoPXhFnLlsv+sr/DgpIN+f1FXvvnP+tYPLzOo/XtJV6busceny7qyBRmfICNdmb9F1tdezpWY3D+zvCt7s/Yt+Lqk/dZfAaXn0fmTj//+t37Yikh//klrh8jf4M/iYmaweL6qK8e18Hwt5a98dVdego9riW/WdCVt4zotbtZ1ZVVyfSn8FLJ/Wbgejy/gY7ZwfZb2E9kA6Sc8sHi1oSvvCszizUaufCX299uPXZmO/H62iSvnkt/PN3PlKfL7xeauvE5+v9oC399/1hf4YOmB9iEzypUDxxBZeND7O8cyAx4mOD/8MYMtfd/dlaPH+Pf8gH0Hx+/vypkkXg5xZYGef5/fkUsPvL/mCKTfbbsXR7kykpSvzdGu+Kx/AH7SsH+Xv0bOMXD+coJL58/F8GmHkfTlVFc+6fnbxxzC07NcOXs4vq9Bfu3cA24uduXXnn/3r5251CC/wpXFWP8V/HS2ftCVrpzYi/rVIP9h0PH96105gfltrjzZ+nf5aJEBR/sBvs+WvX/K3IX0nezfVMBvIuPv6ntcWYKNvyhduVuQdtnKT/e6shzbHwG+Cxv/eZ8rb7D5A/e7sjqb/w6/qgW31F+rB93+9nlja/99yJUfEe9bXB5F/krSn/RxV06FT2bzJ3F8Ei+VK7MM//f8101nGMg/5RVXVmPtP/DDho1+/4coP/hv8fJJAJ+RHR++Rwvt85b136K3kb6w9kf4Dmx8/zuubEL6l1P4Dmx9rXdd+Z3Uf6P3XJmmRfrX3ndlZ/hktvaND13ZkIw/Mx+5shGbHwzfjXjwMb4fNj8GvgiJr+ErsvmJn6B+QerH4adwse+PE36G9P0/6UOBCmfv6PRJPnelw8a/w78Q+/o50ReuvCD29dXjL3H9Lfv9bxpXrmXjd79yZSHy/PyvXblHyPpG3yD9FPv7Id+6Mort7wk/jtSvs+9deZC0/2Y/oP7KxgfA52Prh/zoyjKs/QxO++cVL+Cs/lXBWft0o7j5iXsAZ+cXKZ4ox8+U+ELxCs7m/8vPqP8Qj+BHkecnv7iyOxv/DqfzG+Hs+is4u75GcfMr9wC+RBv/t8z/N38g/Wbrl8H/+Kd8P0T+IR06Pq5QvFbctDrynZD2+XZHrm4j/WgPfX1Fb0fGZ/df8QZ+pCB/tj3/MToyM3k/avh9gvKnzYd35G7i1ZgduZf5WB25jPV/j92R33AxkaV8Wjj8+mLTkZDVX+Ezk/w96HRkWtK+nnsd+XH0uzdsiPpN3e3ICJZ+jd+h83MD+Nrs+4WvweaPTdDh3xecfd+REp8onileKF7BpyEuE3bo+NMQvivrH4ZvReoP8UT8+Dl8anb+SryZuEP7DxP4Umz+HHz5lv37SSbtyHgt0n49GU+/GsX9yTv98xcnstT/zBQduYPUD2XKjizE+s/hLH9M4Wz/8BzO7n8NZ++f+Dg/tv6dz4+fwen7D6f5q+INnOavU3EP4PT7V+ITOB3fqnimeK54oXipeKV4rXijuEzN3cAnZOm/Eh/CPeKxcvxUic+V+FKJr5V4mUa5P3A=
*/