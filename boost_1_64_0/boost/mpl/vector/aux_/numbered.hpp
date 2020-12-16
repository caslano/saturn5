
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

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

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define AUX778076_VECTOR_TAIL(vector, i_, T) \
    BOOST_PP_CAT(vector,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        > \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(vector,i_)
    : v_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_VECTOR_TAIL(vector,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(vector,i_) type;
};
#endif

#   undef AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   if i_ > 0

template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(vector,i_)
{
    typedef aux::vector_tag<i_> tag;
    typedef BOOST_PP_CAT(vector,i_) type;

#   define AUX778076_VECTOR_ITEM(unused, i_, unused2) \
    typedef BOOST_PP_CAT(T,i_) BOOST_PP_CAT(item,i_); \
    /**/

    BOOST_PP_REPEAT(i_, AUX778076_VECTOR_ITEM, unused)
#   undef AUX778076_VECTOR_ITEM
    typedef void_ BOOST_PP_CAT(item,i_);
    typedef BOOST_PP_CAT(T,BOOST_PP_DEC(i_)) back;

    // Borland forces us to use 'type' here (instead of the class name)
    typedef v_iter<type,0> begin;
    typedef v_iter<type,i_> end;
};

template<>
struct push_front_impl< aux::vector_tag<BOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef BOOST_PP_CAT(vector,i_)<
              T
              BOOST_PP_COMMA_IF(BOOST_PP_DEC(i_))
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef BOOST_PP_CAT(vector,BOOST_PP_DEC(i_))<
              BOOST_PP_ENUM_SHIFTED_PARAMS(i_, typename Vector::item)
            > type;
    };
};


template<>
struct push_back_impl< aux::vector_tag<BOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef BOOST_PP_CAT(vector,i_)<
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
              BOOST_PP_COMMA_IF(BOOST_PP_DEC(i_))
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef BOOST_PP_CAT(vector,BOOST_PP_DEC(i_))<
              BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

#   endif // i_ > 0

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template< typename V >
struct v_at<V,i_>
{
    typedef typename V::BOOST_PP_CAT(item,i_) type;
};

#   else

namespace aux {
template<> struct v_at_impl<i_>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::BOOST_PP_CAT(item,i_) type;
    };
};
}

template<>
struct at_impl< aux::vector_tag<i_> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

#if i_ > 0
template<>
struct front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};
#endif

template<>
struct size_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : long_<i_>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<i_> >
    : size_impl< aux::vector_tag<i_> >
{
};

template<>
struct clear_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
RfLMy1yLCuntx+r/ce35udeuW/8/rpOBlnayfv9HO1mb8mzmpOvy156fmJs0mfrf18UsSZUbz+vVsbsvbeuF60bWPfe9zHWsnV79cJnrWD8xPevjtd7rAv28LnymrCHkuY9reJ5cgzz3cQ3PEt2PDrxA/gKnhgVMDpgeMyd5kdg1xraP7+PTFvXqbHnGxd8jG/IM1kMf95BF2uuvGfv8nsXSO36LLnNdmrowRnteZh9tkpGR75HVPr4/Pyo93/fxnPNy1CNvfX5/aXubL3Md7e2d7wGXXocCSO2ZhwvaPDU8KIhBnqjZ3/qLv5cO9/imF32H7Z7YI0sjep8/beI9AZPCYuYsTohLlfvL8xmTS6/BP0KPvd7v4u/xj5gT50t+L63o1eXWF/5+UlhAjyWb6h9wt7pVUo8PcIu+72vPC660WbvO9zLXiQBzHfe7zLMZ49Se9XS565IukOXLXMOYyzNZN322DS/ggnFvz+u9X8iksAjaNFm7j/Wqi74/vyDmJCxOjZk7P27eElmn9LGP67hkvnYv976uWZDMZb160bev6xYmxXNh71j0dZ0oWa7r9a0vuo6xWtyjhy/+fknffWy+5LpL+9h+yTV99lHy+xdf13cf3S+57r/72GNLL5CLEJnoML+JQQH/JWa98r368tf+ty293HWIW4+/2dd12LCesevrGuyXdk17X9dcZLsyRa4vvSY1fZE8q2e+X+29z4xemU7viZUu+l4vfzPvlvvK50l5B9X5T9s96v/hT3I2VLL6f8e9nP1yL2dDeaq/B5xVnzl3qOvrfudd8hm829movjfGqvu7OenVfZ+QtsinHFGi7pfJO+Sf16nnXM3vb1LPzb+BM7M4Q/RkirrPsZs5W8aWM0acBujUmR/qPsX3qc+kM7zrei1n6aSo568zcMaHrbqfj5W63qVN/T05Sf0/kHFyGcnZs4Hq792Z6u9xNeoz2ln9vegkZ3tYq+fsG6M+rbI4+2oc725/0aSeew9nJh/nDKQ2zohwU/f1Gs5Zhs/pVX/vUe2rvpUzvpfq1Lh3qM/SUerTqtCgxvETzoIsV3+PHKD+b/sF8/iL+kyos1Dff6TuX9RioeZjAO1p4UyTeUoO/ALU30OPq/41PMgZdnsHqH5O5GxYT84IdNep6wrVZ9wbvJN/NmdtNCB/5Zwh8JO6r36C+ntZMe+SL6GfZervFVmcjXlWPVd/E+ORp743t/KO8r8405x2e6Vx9ky9+l0B4955SKfmpxE5uJ+zF7Txp/+R1pyBwP2cd+jUvHiY1Lh0qeu79/JO+4FqfOJSebe8JWcUtNPe79R1aW/plbx/q1PX3cEZ4GGcnfeeXrVngRqfUsa/czJnd3oy/ytor7/63DeBsw5jLNVzT6i/p9Rw9lsbZ9v48O7/wXrV7kHq/vtH8LyjyPtv6n7dnClV9SpnJDqq76WsSD23lDOT0tTvj9Sr751mcobNHM5ysFfjY9XCmUix6rqsWjUPjds4Y2GyTrXnUeTuD/VZXcH/kzhD4w31+5pv1KdVl7pPWn9LJU/XmNU8B6FHvNR1JVGc0biJ9h/mLNPHOAvOU93HBnk28zu7LJ26f7P6DA/m7PmhOtXuiZwJuU/9PjdC3a/yqwFq3DjT78hczijdzBnM2plGn6v7hPqq60um6ZRcf4+ejuPsylfQC46s58V6JR8TWD9J6n4lhzmLF31eijx1HudMIz/kpVivnnOX+lyXqp6f5KKev+w+9GAsZ1A9zpnB16n7dXioz7Ryzn5v4ozgW7EfoZyt8Dly4cPZUFdZqHHz4+znf3HG9Nus61GccYz9KWvkbLjr0Gur0Dfv8Y7/x5Hbm41Kvobo1XqKUO0=
*/