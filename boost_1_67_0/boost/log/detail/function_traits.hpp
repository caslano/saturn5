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
AdE1FBwLWylYI8uY5T6PLrx37xKa4itAOTtLqR+tfDOeyUo1pXIP9rQzTTuIc/FgyNCk1m1S0eaNCg4DlF+8pygr6yoOQFIw0APg8PAwez/jDNXJs8C2i1QS3Hz30PHCQL5gtbGX5E5PFHD+5HDR0Fzk7bE7Z4SxKW8xT5a3QvPsI3UTzlv3SimnA8fQnw7oyhJ+vH7riHsn6C34EyY/iPN/y7xvPh/c9CG9IX8deStTDOiGJ+inR+Xc6HZ++084SQAxZS8vvMYzG0IAr3TgYdqvo6PdnjDJK4YrEOAN4I0b++NMrDz+3uV8VdMntewU0Pw6icB2GzW+rmlrW+vzjomjgYESid49x+td6Dh9eSfM/evWRIZycYM1V4m5SlYgmBaVDdWNcO2Uk+Cl+ggmqUv6iNZtrmw+841Zw5okxF0EWm8tsMST6LlC/lsPWHUD0EpEfZIA5J/YCSQqt17WTTpiv1SI9cJgdy+CO4VVNacJpbeTMiUAbwtt/uGykqXVJaRMJSQJQtABz82Ijm92j/HBb92zQRfVebKgEwz7XBRe9GSKx2d4rrpQB7x81NZWcanbW3vFQSSdqptQNDSszD0DTqvhGvB6uP5FqIAAweuq8so/VahqzRSksLut22kZH24Cyj9wbkaDRtHsu81/CiQ++8McQaRSfIlqUGT1x7ys1va6HjUvrXLntxAB5A892LvILZh605X+qPb0UDG7LUzdSsUbtGdECTUZO38G+lEiIjCgm+JwW8Jc92yrtkyDryzv7+shmIUb31G/q5D230MY7toIYIScg91ux6LPmLvF5Xbv30Sm5ITpYc+m9JyiRH8iCQ3F0xkuj9dTG6gFTlnKAAgs99P2UwIe3q6JS+gLeOoAuuYlvaZ4M4Oz1skz71+e2QyFUMvBRlZzKwsgDSh/3wAxgEC7J8Wo+4yPVr0mBwaGj3XwEQ8vxcbABU8dm4dHAa+w44KhonPPq7Pn4dKiBEsTj5oVRBScCwxyYB0y7BFZ2XJNefVmehdKThDzL7uCSPeLCPd/HyeCxtE2AQt87gy408YjZBHvoBxlyywR0F1BeaT2GPY0tb9+8qazEebMj+vZ+3XPo7gXXcflOvcNZwcNhtDwrOs5A8uQC7TeSEMlmvC2zpr4vUjXpXsA2Z0NQcTG5/KnLaPChgOlumV0Q0XqMatKqmmqOaJFPl391isLADtwnfqrVuX+RHUe5c8wkWpS5FOTEVFnUUjtTnEvp8yYiUlN8VzzSLFnIPzjVX7NU6a45WOdr6uvRMDH7xJpV43xPtQJDAS5Pg1jGjiPQjLlnp3u7Hd33aH+g7xb8kS8vbD+n28HC7NclHSTQ0ohW5Bq17yjPN8FLxnMElSRXJWjCXYPyspEPbhoQjYFPrxFHmRdF/SVmcIBl0Fufq76rKwaUAjkIjQOczAQrcxTF7hbxwTzPsdbs97fkP5r+wWjuy7wd+QebWmtkUzvT0Zr2ZwF5XzMMb9iWQDoPbqhJXrPmZpNCQZOjgJI94AI4AoCQQJlgiFCeskARX+LJkwGAgeHY2xquveLB1DvpPWE9tLolVUf26jjWfeZu3XrAbHYUz8lY633n29+7XxpOs/JbgtvQxe5XEolkXIYaGlGupLqqd2TMMIEA3xg0r/M7oU5/9OOdF/H1stQkMRZ9X6uWIy7dQzMRVywE7BwoJIgrpO8nxXwfE4+XfXU+UVwTkJ9mWnjkVm5Y496dmnM776uKQZodv53EU6v3kZC5EeWie0NAw0NgAF4pOHBz0YzLCtF8F1NYWE7+Pl5QYtO1RCaU5cGW54AFgeVY3w7mZKKur5IgwZi6JvCAAj5VeUq3jqhv6TrYlnxMJnSWFCbsG4mVLeVrkrT9mueN1ykfUwqwj3jsZt9o6Lr8rS2tsOPXkhgs5abUNeh3hAaYjm/5op0GgWmkKLG6ARkNDKdboKY5JApGv1+gOIVbePOktXVsPQyIM96kOiiic07V6yXTbm8avVa0VtXaa4nkdpud1fp+0R9Xbibs3uYVII7VPe7HjPcm+HLtlnCo4opQch13p/9qBFqYwrAoDkr/L8Sglxd7kG5tuqHrXk5/nwAfe3szK+3pD34nffIzg3fKzTS1Gq/UlX9vbDmpfeAzdYCPz43gR7iPRTNVQ/eq6mBDfMeDbsHA0AYmdiSwk5ObAwyO9vSDjl8qkWmDnz0twbs1oL3efJlskElIdCAwaB1YONN98HqHdSOm4eyPEW9EvgBXAhM06+2Gx2s5lw3qRi2iSHjyBmsdb8xg5qO/dUt3Xj6W7k5xwU0XtzbLa9duI/a08dzMX2wlfE34SsWuwKKCGxP0PG/bMqMHv5NP1kigmL8YWWxPm/qpBKRTDkDIvRb55x8dDEuMX+/wcm90nO2TmjS6ps8dG9a3fxlVp1XreW+LEi5f80cX0lYlTuy5tP28LNt2yGwzXqnBycsRICw7gNiCY82Ymb5ufXVjoqdHatDQxE1iR8r8Uuou6ltSAqB3BC1c5Ne2IrLCdqyXT+ddkdqBaFLys/NiYBtpBM9JXxlUPnThOXV/OZuEXceCcCwHCC9H5idAKm4c2gsQgVRBC2HBLl/udfomj6HH+EA+2k60LUUqIkHpj0sdbKOHTzriS6Rz5aUiarPpUS2cjOE5pNEAqtDT6/4brETIWnOfP4LQvTzOo6/E0N/vhZCwuvR9NjfadTcyYOzYsNJbAYJI44m5E3fM/W3l9l9ewssz5fvoLVZ+Ohlggtt4oMn4rTMwNo+nkr8jGmG46E95yEnTUei9z7Rp+uIXQoXRNSAl/VoEJBocJoVXmd//vuMNrUzbUY7EnI9Avn94ozSWWL1vFkf6wtF2v0HeM4ToaJVr0OmafBiBbHxsLyIiXg7sDQLccG+vsB5ymh0Muey5ELVXVPo1iiZTg5Qpf5PgOmstYl7DauZfXmwtpzRAqR7LaOLlqRZFZP1zLKDWi7c/jBNQZ+BWt1FiaOCsbxDJfprsHNVhqRMunbPstGcwui6MFhBRiwxV8Efj93Cs9kp8dXWOGZk5TPElG21SctJvZkyb1NtKsBSws4NCYQ7fVFEhPTTxbe4IYf/+SaVTY9PLSAkcRPATCpEu1qzlWDI2TXVp+ZU13sWLWxP/Hsd1fXd506HjrJID3+Aox3jWnC59vKLPsZndONiU8SNvYnWLyfOp5f/lR7iaUCjN2mHHB0m7iv9ZGJzan8Tp09J6nXtL570oYcU8rW2/hV1e0s+bNjLWGs49LTa78dSwKqvOZy5L7ecCl1B+ZiBu5/vDt/P2j9oVflJABKgVeldB6x53agxdNj3TKFtu3hYBnBzKEbIEmyhzxRTOrKkJpTAgUY70ZBwEpEmDwHT28rNkukN34pmA80qf4cmZATJYCFsxNLSDMnEgGwclI9/aiEhofKnijyesNRJLLELYskBzVarTpfI8BZb8gnZeCGVSLoZjfJaqgvKF0UIQLJJf/sgK/o8YshyKSdFfSZpuNy5Kpq3YdWGu8uOwhtZVr2AvPh8UHrg9DMIgHjYX2eANlWQ+Tpcy+kH24srG30CN3MekJReQWrq306uYIZAs+q4gu7BFJhg6GucDShtGONDFdbZ9ImOau9AQzT+dUh/wP4IgxyHTvoNEqKdpHf8ocObsuIa19oxzxI+gDaoqPDgXG5Mku9kJ4ngM4XTHuu+LgM/fDuFy/Z96VYCS/NaHgrrI+/Xqo6H58mxS2ggMSX4s/ZCn+E1WkF/muf1camStdrL2+CVYIFoax8TvdMCQwMvopkBEB0fykVgnpGk8JTlxTIJmTHWsgkv8/keQlX+MYTo9vbo9PYUz5uR0MI4ayaWFiDaS2faWbXh21N982xmw4+EeTBjQ+5STfpvQ0AVekaaksWcTMYQBeubE181ibBtb78lKNKadGn0qQ19x8F7mnFkeX3t5T3/DXXB+Sl3vUBk4W8H0zq9sF3MdG5cjraNJ7QJoZIK+RKZ+p9+jk/qz5i7YUXw0vbn36tfGRo5CRhoBX2lMjIG0SGDjJyZTl/nRsu1TjjtBej4IduVRvrNQPlAUfbJSBv1uqDFxAvOMCN32Fa4Nf0Q8p40aL5PnzKL70MYHTIaAnWLjg4Fl+u92ImBATT1j1k3dXjNIGMhsHg+EEaJ0CEYAYjaPEZhYLas3I4KeGSZjEEajmzus/q2b3erdn3L8SiOD0CwZLlcPr0fh66ZmWZJ5pwJw1f6dH6uA/YO8TWa1JUeF2G/UjxBYV2sqrNc0/Y8i3RcWkTBPcyYPhInypa9kSY2uL6+aE0+5k1NOGfl3bCIQp6/8nGC1SAar9SN5xAHysxk8a8PuEzMomSOU1wDiwso+iJ+X1rlNQPJu4xb+f9YQgyAJh4yl/351SYOPaeQxkucfd5OEabVndBbI1D6ID7s5BSM3hSXfyxGyxiMclcBjqq1XWTnhIRAg7NZpMl3z0Ut6bTZtNkvG29dIcFBP7g/eE2qGoRsNfSGw+BbrCzD7DFcAoETbVA8bsgP9gLAQ99U4i69JQXrpMGrfEtsMilwIXEEdMnrAk/7vEP2RPLGSik8C/hluFObg2TaVuMXmcznrsV1IOCRJGzl9fkqLUNFKe0WO+Q92VAHe06kGb6X9ZGDl1LApF9drF9aFZZzYqmV1DoV02ov+t83+m1o0CqVhgGyZ+242SB/WJIY61NzwYzMcAkReW/m7ofv+57EXvG1rr4GK+YKRdOwzSZaCLdSz9y5+BtHrAA24DpUeaR29WrWVzfAhU2MOnhWCg6kbf5rnj8/veT1i1vWXWTEap/7G104iXaCTS+jJ5o7Vc3YWA7MHJGKSOWg63hNuz+gZSNhS3MXUHW6mzke7/24H48z52bPwehrXRjOHaeFPOg4CaxDzcLk3r9ZwiXEu2pUihI3/vaUMJDRKnFJM6AbxWub27WHqpt26QKZ2eCX2eLUH6KwsqMxFdn/13E8BcJranlAOP6Wjn9cUT8w+u6K61k73h+kpMN5/WgkPqt/udFx/6L3MNGerwiPWxb9rC4D66kSkF4ZorSYgsRqt4bU4NN4H2BIIB93ARgV7SSFa0kROEu+n8xI09QZ/++NfnIAXzRKKd+AR9ptodoh5LuzZVIgcAvvciluCNiTNJXgwk/0wsu7F3XgZoyOkUDwZfTnfdrOPwnMA2JXQm+vcxkb7FQYsn1jYimAEnoxjzDfIOSWOvhVezxkJmOzMufKYw/4sQCyFpCpFnziRLazJNmK7f/TZoZPj4zWPMaS1nbj1AhFBCgzj+tdXcUCVEHqah+fKeFf45ca64qrh1/rMdtcsYkg6euiXtiqEMNIsMpcdBXRFlDx3ELiXAA6UTZ5KZt6u99xkOCsbtjYF8vY5n6xyE37bJiBMS2+YC8SRfAgmVdR2Xp3BigFn/yKKXVn9nkqKlrfJccKrIuhVjHOhE6+DMkM9zNLtS2hTnrmqlWELV1T971SOw9Y/ceKeHvtMohhOCkGAfhUgihDo/NMt0fy5bMWNWSbg3v1pgL4GV2Vh6fztqApj1wLkmfxV81J6x22+nub2gRAD+sZ7BvH9N+kKeAtgZI/MvN+zYUFZHuHoe+/NxC5PME8EIoQT/iiNfO9HTtsnYWOOFF8hkQRohKBUc6a82aZBDWNwSpZ9ja9T1DLq3t7Z4w2s1NTMK5B2inM/AJtVyj7HgbO4JAnHuzMlOlXCDcvPvQ2XxC3n4rxpBbpJTwYFL6aNxykvsJi+WGTAh6zPH07LuQla17G/J9el9D49Q3yAfi5btpz56E59wN5IYuJiLUoHh2XIouYTeMiZ6Z9zyvqtE8LiPWOOVKv/MJ5238YHDUb/A5JQB6oClrYBtP7CCOsEuqsABvr/NL/PyGfvQPf9y3Jov/2Dvl3hwmhqUqlOWkKAOY2NDA2pmJmNNnzSBBC/U1vg5DtXy3qktOgQPG1oJH2wwOF9gZ/EgLaRpFoSbUY2KUn/InSdYlnjmMFdGeO6T7OqZnHyVYsAgt9wiT/ghkjZrAPdjd7ZqK8+khtm+5zZKfm3KrmNwl8FCPniOOAz9s1g10MLfrux+Z5rhH3zMZRp3E3PLhKV63S+neRjsIW/W257yF/Ww3GedFH/e5HYeh6g/eyvE2Fpt3zwjrI6iM77hI85x358nY6u+A4KRsSrsiDFGftrQdsWmpquJ7muOv18EIarJDsmiokqDdjBipFT1r0Vw6sLpiUYprvMzINdmv2Asdg/wiGZkGjMYEqfS1MW34jkt8r7pjPwHrtfl0rd9ujDNRoThUj+vmnNUGPL5itR5K0ohQ3N5W3FBRZbOXZxLI91jLo0K/d4th17nLa1GdGQW4rCtV3izRQL8R6/IyV+MsJ7hfi0g+WyQHwOuAReGdU4stwkya5sIOqwdKQiqZli3kO/2kFNt2lWStLUykMAmEVKCpuaci3Z+uwxKZh/I3K/VVedhuLBz7WOLbpVfxE2WL7MKVKJUYW58Sjo5UEih/UCDZ3R66TGd/AZw4GLvLp7ilzpOK3TPm6TaNJliJqilie7yDzCPYxOL2oQg51Gfp3gSkif9AAx5FuIkziVy5A8rRoSUVSNyKoKV8H0ecaTuPas/7bTN/CvKO7dxS9/Fzsrx547XnRPbLSzm46CFXUsbzgSDEi28miYBU6JO56cy05+u6lje6oj0ASAOaXv5B5af87kP7d+PpPlqgKJrYhg8mQ1lXo1jH8yS66CyvdR3BzaGaUKqoWq+lWD+aSXZ1YIs9B30ghrn6lgdEJBguvT/gCDKDrtNskbjIVNvxt/1adwc0eIiWmVf2xbwODtcqbJM0jaoqdTjTA5gJQvfeUFsz7St7bZyZYiSBwRiISTqoc8/VCQLe5I4UPPmnwMK+g+2myDrUQPIaHjZ5fdolknBUFj4/Yn43NZkUjiMmE5nJMu04XJfVWKMDtQjvt3oD35vJfkbUAOztyit9+bXVsGKonYtUwOlQq51yLJCv/srV3+UJ911EYyMOQ4LEd4O8Bb5fx5rdRn4gkxoutSx1Pn2qmx0cGXDtrmpvAzVLqifr10kdStH5S5UHUFuS2zkzjkiW+BLD2UJ3QHOikc+V8Y70mAWG9xf+DKkWVOyXxFeXNJ5kmAO1sC7Bfg1dtz7zjPPZurbnzuWHTS8ogNHiEzWg4azGpK4ZVs9zzxDqH0Qzz0dMDctnZo4vgY2cLpy19nKTq0I9RGLoyGn+eez7ixZzmxKP3qdo6wDg2MQVbS8yLu8bNoovMnfCMP7BlC+HM//LMPppFcottxgiyVgJ0hVUQx0S3bzAAGCfQfkJsA/P7G/gtfkT0inv2kiK0/YHqGASwRtTajD3XGU5IE7LPSSmY6ktomuh4ff7Bm/BykpgMmLPxPw+Y8PewA/CreqtulflP4aEKUFDQJDfxv3tJAarMi5kVnPDxVVUaY9nscu6/ZUW5NHADvRTkBLwFuOgcjv6oN16RoY8Vm8qeS0vDV1hRbV6WF6vbm3lKeN41ziPvUMpVTpIdI1R11MxfrZplZgD480Wl0+HdJRaM4X9GmZ7tr+ij6ywnAqmM21sYjyjThpJuwodxhK87kOVaZtC/Uo5o1E8cG0Q3o0b3AAjIC4G3untTvekjIsRM/AX9urCvqhUQ8J5DmlpJMwCA37R5HN7AOmtbCLSXIna/GqS4D7XLEGj5cK2hzI/9IcA4DHUSyy8opobk1nyfvm/uwy4JdkWKCRGdn99/yenI+4hZZ67gR2oUhNsdZedgGSjwgJLdrSaGr2BTnPHD0+Ef75m3HLK3hRm7QbQKCN+cI6cEe9Np1j/acoeaiUF9KJXMCSDNVdW10fWsIdZJhuepYM/blQaB0yx4fls7BzXtrv4HQVqC3odH8iPQlAMAm7cHHE0Kyk1zH1HVZ92EIfJus28PDIi+Wb/87RZn/JSXzgAeDPoOWSYCHu9cQKnJg+cX5cAAMqO28aHfOABlQaQOs/2nkt9wD1gv0qLOMAobZyTL+7QLWFzAa6bt83G0YV9BwyEnIueLm/u0u4i4qvW+TvpAqhSdh4K064BDchFc0CSfPYsp4gH0KyiE8NZNPbExvLmq13jnM3cfd8xfBd/UTxe/QcGY2432ZbWcnc7fBsT/MTBm9fAXjuZF4mhssHL0Q6KbW0qv51GtQC3S3mHblJED4vuKeqeM6uM8UINx95gOssMeDI+SRtYpXesekafNG/pCiKLJGR1NfrtQ13e27fNk4LJrFOn1/KixoE4cQx+e69DFqKn2vAEbzn/bVqNjixV4BoFOLxfcjM9TzULQw+PYcwv3FV9DZJdmg27E6hObJ4NGqadC/6sWLvl8l5iHoRs/VkQo1iwUT3msjOLcLUpM+E8BvshgVCmqzZ5ysdoioLR7a/VlaiqqWBOCmLRZbCJKTERvy0SASo0sZkTDmn4NABBZ3W34uNGCYYl42Ee329+OuW2qZ3cCWHh69w8AEGQ4CAi0n8vaztqfmIq5vV2vJladkqQ0DPa0FMeYCvlaSu+xcOc0JSsicyt346ALyGHw8i0os88cmwdOSqQ75OM7uCW4G1GvGRsgyxO9eeXKe2suI8EBOt8GraK12F33eblNb6zFtRAXlZX1SYAKi5ymLTM7xeEbYiseRAndweQosGuiki6QkLh95t7j7zGQsZkA0/pI79W3T8cWm2pz2u3QszCatD6tTCBtghy7GJgds3PnoSkPAys9rVmwgV25Y2NPeGhlFIUJS7yRSIBJyYgNYrHeaNzjKlXCvNnDmJh7IOJENTUuSpRpTe6fbgwrzUjG9130dg6jw13IXEpTzSO+wEnBNTT3zqWwQkb8cAWe8/LwE7rl0M8de12YnrcCDNZuqMgNd4Wa9enB8u6CuA2rM41dYBB+vuA2ORF3pzT434qJPPbu/V2PJq6pCM/gRPBy32+gpcJ7Qv1keF6wLL07GQMm8d9+7olkivFNtQWBEQhcu8VR/WYoI/CKeYFLB5QvzncQIJmfhscBM6f4s9F76eWJWPINFOzmvTUew9Mjb12ZYWHtpPx0OV4OWucu/06vmoiJjIiQ8XWVyGrKvxLsZ3StRTLN0GhKCDGqL9d1WCgssYr2bccWp8KhVmXnXXFOL9GPDuNhuji2JsqRRRAkVCfZxhb/Q1XSteFG9zjK7nG2qpv/nSqXpCBPE//kVdoiR84JiKWBdeo/MdDNmDqE6TGicnE=
*/