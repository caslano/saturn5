/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   function_traits.hpp
 * \author Andrey Semashev
 * \date   30.08.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_

#include <boost/mpl/has_xxx.hpp>
#include <boost/log/detail/config.hpp>

#if defined(BOOST_NO_SFINAE) || defined(BOOST_MPL_CFG_NO_HAS_XXX)
#   if !defined(BOOST_LOG_NO_FUNCTION_TRAITS)
#      define BOOST_LOG_NO_FUNCTION_TRAITS
#   endif
#else

#include <boost/mpl/int.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/is_nonmember_callable_builtin.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

    //  A number of traits to deal with functors
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_argument_type, argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_first_argument_type, first_argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_second_argument_type, second_argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_arg1_type, arg1_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_arg2_type, arg2_type, false)

    namespace has_arity_no_adl {

        typedef char yes_type;
        struct no_type
        {
            char dummy[2];
        };

        template< typename FunT, int ArityV = FunT::arity >
        struct checker
        {
        };

        template< typename FunT >
        yes_type has_arity_impl(FunT const&, checker< FunT >*);
        template< typename FunT >
        no_type has_arity_impl(FunT const&, ...);

    } // namespace has_arity_no_adl

    //! The metafunction detects if the type has an arity static constant member
    template< typename FunT >
    struct has_arity
    {
        static FunT const& get_FunT();

        enum value_t { value = (sizeof(has_arity_no_adl::has_arity_impl(get_FunT(), 0)) == sizeof(has_arity_no_adl::yes_type)) };
        typedef mpl::bool_< value > type;
    };

    //! The metafunction results in an unqualified type with removed reference
    template< typename T >
    struct root_type :
        public remove_cv<
            typename remove_reference<
                T
            >::type
        >
    {
    };

    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_argument_type< FunT >::value,
        bool = has_first_argument_type< FunT >::value,
        bool = has_arg1_type< FunT >::value
    >
    struct first_argument_type_of_impl
    {
    };
    template< typename FunT >
    struct first_argument_type_of_impl< FunT, true, false, false, false >
    {
        typedef typename root_type<
            typename mpl::front<
                typename function_types::parameter_types< FunT >::type
            >::type
        >::type type;
    };
    template< typename FunT, bool HasFirstArgumentV, bool HasArg1V >
    struct first_argument_type_of_impl< FunT, false, true, HasFirstArgumentV, HasArg1V >
    {
        typedef typename root_type<
            typename FunT::argument_type
        >::type type;
    };
    template< typename FunT, bool HasArg1V >
    struct first_argument_type_of_impl< FunT, false, false, true, HasArg1V >
    {
        typedef typename root_type<
            typename FunT::first_argument_type
        >::type type;
    };
    template< typename FunT >
    struct first_argument_type_of_impl< FunT, false, false, false, true >
    {
        typedef typename root_type<
            typename FunT::arg1_type
        >::type type;
    };

    //! The metafunction returns the first argument type of a function
    template< typename FunT >
    struct first_argument_type_of :
        public first_argument_type_of_impl< FunT >
    {
    };


    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_second_argument_type< FunT >::value,
        bool = has_arg2_type< FunT >::value
    >
    struct second_argument_type_of_impl
    {
    };
    template< typename FunT >
    struct second_argument_type_of_impl< FunT, true, false, false >
    {
        typedef typename root_type<
            typename mpl::front<
                typename mpl::pop_front<
                    typename function_types::parameter_types< FunT >::type
                >::type
            >::type
        >::type type;
    };
    template< typename FunT, bool HasArg2V >
    struct second_argument_type_of_impl< FunT, false, true, HasArg2V >
    {
        typedef typename root_type<
            typename FunT::second_argument_type
        >::type type;
    };
    template< typename FunT >
    struct second_argument_type_of_impl< FunT, false, false, true >
    {
        typedef typename root_type<
            typename FunT::arg2_type
        >::type type;
    };

    //! The metafunction returns the second argument type of a function
    template< typename FunT >
    struct second_argument_type_of :
        public second_argument_type_of_impl< FunT >
    {
    };


    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_arity< FunT >::value,
        bool = has_argument_type< FunT >::value,
        bool = has_second_argument_type< FunT >::value
    >
    struct arity_of_impl
    {
    };
    template< typename FunT >
    struct arity_of_impl< FunT, true, false, false, false > :
        public function_types::function_arity< FunT >
    {
    };
    template< typename FunT, bool HasArgumentTypeV, bool HasSecondArgumentTypeV >
    struct arity_of_impl< FunT, false, true, HasArgumentTypeV, HasSecondArgumentTypeV > :
        public mpl::int_< FunT::arity >
    {
    };
    template< typename FunT, bool HasArgumentTypeV >
    struct arity_of_impl< FunT, false, false, HasArgumentTypeV, true > :
        public mpl::int_< 2 >
    {
    };
    template< typename FunT >
    struct arity_of_impl< FunT, false, false, true, false > :
        public mpl::int_< 1 >
    {
    };

    //! The metafunction returns the arity of a function
    template< typename FunT >
    struct arity_of :
        public arity_of_impl< FunT >
    {
    };

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // defined(BOOST_NO_SFINAE) || defined(BOOST_MPL_CFG_NO_HAS_XXX)

#endif // BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_

/* function_traits.hpp
/6brh17/P5//eYvnFpzWv3/m8Vr/Px67xp7NjB/JNR3lRk1D3eVZ/99fxp9HjvUcu5bXPz0jM6//wHTv2HOazG8qnG8982asyE9yDeNvEuPIoeh1S5b1sKbq2Ywziaz7SR/047c6m98y0jMH5WVkZPr329YfwG/VQc5+S85o7LfTBvr3W0rG8fOb9wz84zfO7jyefvzGzXfJuPmFX19+14U7HkmbOvaVJfue6V57/Ma7/13j1/8L49TJLv0GwOkOe6v2tu7B2oRciimHyvArJ+MFFfhz/kra2Kg61G7UYVTHVeydiSpEVa9qXj+kw16tjvu0bl4VecL2aj2e+7SeiHPxt66KPCFn43+fPVmPdT/WHYTtICqqOtD/ErgCV+AKXIErcAWull0/9Pn/8/nP7O/S49X2n4Bd4zyxAw7t69eoiO9K1zasHmkpi3/y5prnb+6Lk323/K4Nw765xvcV3fPPcR+m9Kb310uSdkVr3JE1R1xzzDU1b4vdsa4u/O1MuzkMvRk4PBO1HNlZcCJhXRd99H3NjLnshMuz75ZtHzr8j17Vf2X7OuSnbvRvKzz/sSt+/Oex6R/3LJlcdfslgfb1f0L7er6R/uF0h7OESJfL3TAexsME2Ad2sJxN1A+eBIfAJDgGngwnw45wmsrxPo6pzfzvPNfkv62tfCLaySe6jbw00DYOXIErcP2LvbOBz6oqA/j7whhfA7axL8YYA8aniIBDUQYSXyICjm8c2D7YgMHYxj5yCNlEUlTChVZYmstQkdBmUCFaLbXys2ZhkmLOpKKiIrSkMuv/Pu9z7+593/OOd4L09Z7f79l/95zznHvOuefee957nvvcSIiESIiESPg3/f63vP+f+e//HHQt3x8ndA37eX0H4Dnkp1n8LrnA9v3BzlcVl/k+ZK7vnR/KkvfvxT9Dkv4Wf0Xyf4eadPI8Kj58pvB72ion2f7Nr3H2b/5+g/2+NQqNfkDceT2Jbl+QyfBdSf+ip179U6k/1JpCHlisK86Tt+2T1D9Ji+Q9SFlezx4k3s7fmnmg+gd4XfI28N4Gc2405sCFaGxAxCcqqReOJo+jrb8Wnf1S1xXyHex1RR6Hz4ERkr8rJXXypKv/ordUpwv1v5yUucgDiNO3h7OMxVLGaEoYaNfjNomLtp6BiN+siRR+CwoJHOt5iMlXRWyIZyC+45uox9d6n5/jRBzHKcAPX5N+O2Ic0gnJQt7pS4+OkvEj/oAZQCsY2GU1Ff7x8/u+6s/H/OxIdb32WPNoXaxnQrWSPtLy2yA+l34SB8P4Pr/VRupg9HOXrX75f6jPw15ETpK3KaA9+K13tKWoynpmFQ9bJG++qW1ajtehW1W5wjz2yRvYD1VSYev5V6yMnVpPISUP8cyJe7oj+2Yn8zne3b3RHTr2ju7ZsUt0h5j0qOiOHQdGR8V07mj5d3iAXgroX9u3zkuy3yc8u/h7AGFUxvVErwNpM3rzHl9C+M/TpJ+1f3QsaRztDuj7Ui2kiQp2Usak8c8Qd9/jXjqscYRegG9pcTnmSdJzKUbSL8JfSA+ekSQYjoGpjIoxwJOuZQyX9LfQudJTxkX5c7Toq55MeyzcI+lJJh8llB3ok7piLLF6XnMuDfWl9zL5J0LXfI7M12PYRdIPeNP4m4UUIBuQer32PYa8hLyBHKOlnbyU5e3imQbnI2uRarY38yURPfZ6np3+HLN8Mm8b2uqTuXqo5Vf5wtEejVtmx429xIqb0xo33opLb40bZ8X1bI3LsuJODbHjxlpxx1rjxlhxr7bG2XXZNyTYZ/RdrXEXWnGbhwT7jF5jx42X7fn29kXG643bh7SMSfc3TnSMuX1IMzYCfaCq//s=
*/