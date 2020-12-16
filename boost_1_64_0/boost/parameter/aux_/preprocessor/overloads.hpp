// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file generates overloads in this format:
//
//     template <typename A0, typename A1>
//     typename ::boost::mpl::apply_wrap1<
//         ::boost::parameter::aux::make_arg_list<
//             PS0,A0
//           , ::boost::parameter::aux::make_arg_list<
//                 PS1,A1
//               , ::boost::mpl::identity<
//                     ::boost::parameter::aux::empty_arg_list
//                 >
//             >
//         >
//      , unnamed_list
//     >::type
//         operator()(A0 const& a0, A1 const& a1) const
//     {
//         typedef typename ::boost::mpl::apply_wrap1<
//             ::boost::parameter::aux::make_arg_list<
//                 PS0,A0
//               , ::boost::parameter::aux::make_arg_list<
//                     PS1,A1
//                   , ::boost::mpl::identity<
//                         ::boost::parameter::aux::empty_arg_list
//                     >
//                 >
//             >
//         >::type arg_tuple;
//
//         return arg_tuple(
//             a0
//           , a1
//           , ::boost::parameter::aux::void_()
//             ...
//         );
//     }
//

#if !defined(BOOST_PP_IS_ITERATING)
# error Boost.Parameters - do not include this file!
#endif

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_open_list(z, n, text) \
    ::boost::parameter::aux::item< \
        BOOST_PP_CAT(PS, n), BOOST_PP_CAT(A, n)

#define BOOST_PARAMETER_close_list(z, n, text) > 

#define BOOST_PARAMETER_arg_list(n) \
    ::boost::parameter::aux::make_arg_list< \
        BOOST_PP_ENUM(N, BOOST_PARAMETER_open_list, _) \
      , ::boost::parameter::void_ \
        BOOST_PP_REPEAT(N, BOOST_PARAMETER_close_list, _) \
      , deduced_list \
      , ::boost::parameter::aux::tag_keyword_arg \
    >

#define BOOST_PARAMETER_arg_pack_init(z, n, limit) \
    BOOST_PP_CAT(a, BOOST_PP_SUB(limit, n))

template <BOOST_PP_ENUM_PARAMS(N, typename A)>
typename ::boost::mpl::first<
    typename BOOST_PARAMETER_arg_list(N)::type
>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, & a)) const
{
    typedef typename BOOST_PARAMETER_arg_list(N)::type result;
    typedef typename ::boost::mpl::first<result>::type result_type;
    typedef typename ::boost::mpl::second<result>::type error;
    error();

    return result_type(
        BOOST_PP_ENUM(N, BOOST_PARAMETER_arg_pack_init, BOOST_PP_DEC(N))
        BOOST_PP_ENUM_TRAILING_PARAMS(
            BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, N)
          , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT
        )
    );
}

#undef BOOST_PARAMETER_arg_list
#undef BOOST_PARAMETER_close_list
#undef BOOST_PARAMETER_open_list
#undef N


/* overloads.hpp
513IvVR033KSVt9QVZO45kaJPt9fLHE/nF3GXdRvcRd6ulp/D3R1XtPlwti3LY3y/Vjk4x1Lvzs78a/XXx8ncXZmR+cVXyjHpfa3Ka+MCh8P07EJj3WBHK8lv+Oc1826MPYMeyI6XrA8Ni/8VQnfxD1cN2slLlf13jlU1uAxvjGtq4L2fPRb5bxf4v39cuLgJ2lJfN6tsc/zMdGX3eGb1md8m/x53iI9z3kik+cNWAOZs/VOj/HNTf3i+qqVlvF93e+HEZf6UBSX9+c8XmTXWrM8YRsew4atcq7ns2Lf06BLv6cpMr6neUT0lQeetYb5w/5dtJw+Jf6zAx5PMf6xb2pmyfm+6glZ93tKJL5H4n9meNh/sb+Tdb/3i96rPN3848VuzXnhc5MJPW++nnet6H8oMNiqCYh/W/2Sl9fIyzVSPs3Z4bz01XJYwOO5udZSr5GyFpU9XvVNOX6Pp9ha4YnOX18vfgEr3u7jPQFrFHbfZZVwvqcN273f6up7l7+z9YL/fuvxwOes2PkX1c1bHL/22nDJ/wH/x6xf+1zKxihXvnqoXz7v1hV19lhIkdhjetZ11o8D4sfRLJUPWd/2hG35hzzJ+/ylK3je0jn27xLbzMh+L7n6Da7Ms9S/MzDR6pd1lXV/VhNyxLPzmiVtrJU8bhK5mWpTrWuGTbvAV0fIOoF2fX9K0jgs8Kr1kk/8ONLyosVvk/zlFES+61yxbGlV9LuJU5wvrk7LEEzsu4Gdore3pfmOqwNFpPegUSbTmE10HXkriurT/iNsUcv4fuF7Uh6bvJdbo7ziZ+u9Eb1j0Gu2i3m3V6+Yt9BKqKOPyDkf8ORZW6hH1HX13yu6/+Jbx8p593unSjso1HazJyLjz0Vmp6fKWuAdxvmRjavfIebDIKNtJ5q3LZ6O1j88K7y1/gHWLv9wT7gPu2iVx9pP/iN92B76RE23zqc30xUUO87MqrQe967yfdmr7Zxz4CTsZsJ+FiiJpUfbxAn6nqesZ6hnj3sHWMXa3v12eku8IcKe8xBGeRwhPQclzY9nXerp6buNNvIL/yxPfPtYsWiR0W+Fhifvt4pUb9QWedalnuuyVlmxer+aeh9rb4cl3Ss8Q5m94tKepa4/gc4Piu2mUdfttQK4/taFDShxDhBnssTZIfYt9cfGlIu17t8j6Srt8FfL633A38vTJWuztovoeSdhr0Gi73C4fUn8Xh203tttgiZm1/ufS/vKkzZyHBm9JvJrWF6rl8Voft8t+X3RM5pZzm2ue9gwdh76xoT25ZGy72q2Ly3Tf3mKtX1lS5xlWQ9Y63wTKc+PU56yTiTy2R31e8K7d4e/lQvJNyIaNrdj9Ju3fxDmCcoas/iN7xj73m2dfjMYDZuD22jL+OzvBYtV5z5b53PBavm6xucPh1Xivz2m13f3y1k+lq0U3dHwvaob2XBas0P+DrE1KFX/wSBzl8Nx1l3Ccnn9/L5BWTlENWxIKS1uWGIZ/XuN2GdvoMa6KFAcZ/9OXq3DtI9Ce31jS9cojPadd4r8rsB4a07Aqe8s0mtPk8T7ROBuz2DvAP/LVqy9UyfQU2S092US9yvoXBYw2/pC8f9mYIa1kLQm9j3PSb/6VdJqt3OnME3PrGHiH7jQ+rTvZV9na6b/nZ6wHVuxcyV23ExeQ9nrKoOh4PysDnyhpGu4ZhM2HhdZX3RdjZSR+s/FbVI5+ewp5PfbZaS6DwT1+611U8N1ILgQ5QFf5LvUhYS1BGP1YN21sXrQV8P34/ZE5DmFryPx/Fn6XZWcK6HOlYXoP/PD8QcFazhXln6D+zR6skP2ubLWYSeR07DBhH0hT+Q4T6BjKCso4WYbWUicZyVOb+I=
*/