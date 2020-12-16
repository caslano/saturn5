// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CALLABLE_HPP
#define BOOST_CONVERT_IS_CALLABLE_HPP

#include <boost/convert/detail/has_member.hpp>

namespace boost { namespace cnv { namespace detail
{
    typedef ::boost::type_traits::yes_type yes_type;
    typedef ::boost::type_traits:: no_type  no_type;

    struct not_found {};
    struct void_return_substitute {};

    // The overloaded comma operator only kicks in for U != void essentially short-circuiting
    // itself ineffective. Otherwise, when U=void, the standard op,() kicks in and returns
    // 'void_return_substitute'.
    template<typename U> U const& operator, (U const&, void_return_substitute);
    template<typename U> U&       operator, (U&,       void_return_substitute);

    template <typename src, typename dst> struct match_const { typedef dst type; };
    template <typename src, typename dst> struct match_const<src const, dst> { typedef dst const type; };

    template<typename T, typename return_type>
    struct redirect
    {
        static no_type  test (...);
        static yes_type test (return_type);
    };

    template<typename T>
    struct redirect<T, void>
    {
        static yes_type test (...);
        static no_type  test (not_found);
    };
}}}

// No-args case needs to be implemented differently and has not been implemented yet.
//        template <typename R>
//        struct check<true, R ()>

// C1. Need to find some unique/ugly names so that they do not clash if this macro is
//     used inside some other template class;
// C2. Body of the function is not actually used anywhere.
//     However, Intel C++ compiler treats it as an error. So, we provide the body.

#define BOOST_DECLARE_IS_CALLABLE(__trait_name__, __member_name__)                          \
                                                                                            \
template <typename __boost_is_callable_T__, typename __boost_is_callable_signature__>       \
class __trait_name__                                                                        \
{                                                                                           \
    typedef __boost_is_callable_T__        class_type; /*C1*/                               \
    typedef __boost_is_callable_signature__ signature; /*C1*/                               \
    typedef boost::cnv::detail::not_found   not_found;                                      \
                                                                                            \
    BOOST_DECLARE_HAS_MEMBER(has_member, __member_name__);                                  \
                                                                                            \
    struct mixin : public class_type                                                        \
    {                                                                                       \
        using class_type::__member_name__;                                                  \
        not_found __member_name__(...) const { return not_found(); /*C2*/}                  \
    };                                                                                      \
                                                                                            \
    typedef typename boost::cnv::detail::match_const<class_type, mixin>::type* mixin_ptr;   \
                                                                                            \
    template <bool has, typename F> struct check { static bool const value = false; };      \
                                                                                            \
    template <typename Arg1, typename R>                                                    \
    struct check<true, R (Arg1)>                                                            \
    {                                                                                       \
        typedef typename boost::decay<Arg1>::type* a1;                                      \
                                                                                            \
        static bool const value = sizeof(boost::type_traits::yes_type)                      \
                               == sizeof(boost::cnv::detail::redirect<class_type, R>::test( \
                                  (mixin_ptr(0)->__member_name__(*a1(0)),                   \
                                   boost::cnv::detail::void_return_substitute())));         \
    };                                                                                      \
    template <typename Arg1, typename Arg2, typename R>                                     \
    struct check<true, R (Arg1, Arg2)>                                                      \
    {                                                                                       \
        typedef typename boost::decay<Arg1>::type* a1;                                      \
        typedef typename boost::decay<Arg2>::type* a2;                                      \
                                                                                            \
        static bool const value = sizeof(boost::type_traits::yes_type)                      \
                               == sizeof(boost::cnv::detail::redirect<class_type, R>::test( \
                                  (mixin_ptr(0)->__member_name__(*a1(0), *a2(0)),           \
                                   boost::cnv::detail::void_return_substitute())));         \
    };                                                                                      \
                                                                                            \
    public:                                                                                 \
                                                                                            \
    /* Check the existence of __member_name__ first, then the signature. */                 \
    static bool const value = check<has_member<class_type>::value, signature>::value;       \
}

#endif // BOOST_CONVERT_IS_CALLABLE_HPP

/* is_callable.hpp
IpjOZH59jEs32md6touEst7uSk0Ne5GiqwhXOtqVoayouMBBxkxvd/VG4ylTG1hzTVuTuiKjHIetlI8o4pAlefrX8j0ueSxFT1tq7crdpB3nxGxZtjLoDIruy3ct9um7KnrmppeAellPKkt1jKhjcpVaFrsSHSU/cJtXvfADZdJ7BOzL9pYZe5Dmq6bNB9eEN8LgiCWBfZvnHKr7rheTkMcyeEgg7cT8msyNNpK8annaGJX6Omr7mMctrSPYZ733OuqY1+GzTX0fY6HW4fGSXO60jEN9Wr5U39AzBtkWe287DjhPxS5rvcqpqDZ0ICLQ3NeCe9Sb+4pq/bys8yJL+up7q26tN2Stt2nsq02J2sjTpqmP8yyxnpl1HLd5LcFe9d5rucurjfda7javRW6iy6ylp01hiadSl1l96xzKYRtraC0wKF6UWrRCOu+2tEnLF22klYh6rzHkmYz1hXrWZwhS99EdlL4AQX4oOmbowf1qOdvFi2Q5Re5Cl0lni34Vjyp0WX3NA0p/bj/07uCuV91oV1GBV3l+SR7rKXbrMoyz6qzwOZIP76btgS3kyHZSSr902KzcV8bJHrXU+hyS5zKXHmGZz7q3XvQrHlHgdqQX5BXmuvLw9TpHDVfH1MTs4P9tpvVkeNaTqg3Oei0x0Q3XG8nY1CvrldcTpZbLc5YFs/PS0ChvrrLHJ2b38Zw9vRQ9RAiFo4w9xnjV54sGunwSheyKnKVk2V0eTfbsL4m61JSozkJPiTP1+ChO7C/fUVKc2VnXiZRaaixAVKuGAuqdwlmrzpjjUvOY6YWjsKh0m7UsDbwMtpSV5OeUiv5e5SxKLu/n2QNYkC7p6ACxB4xBTTEia3O5Qk2caUSFljkKgBQxh7Ucm1Pkp+wJrr+AshokzG4X/lDj/yuUMtYklb2mlcWKsrJxWiUa844JTvrUk9c1PfCkaNIJ9IqlmLc+50OVyb9UDzT3EWdmig3NY94oTzFazVMY/d4U+AebkfrqZ/6Wih0MZeDQ2wb2jSgoyrBZyrmt8lmOKprL31HKCXBKlXJ9zvVqudievv5NKm7Ia9THebeWKisOIDQ/xxh/s1ZOWSh1prEyzGPpde8rWOH0WbdVqSv2uYaPpDUUjzRivE9UDs05mjnIZ2Iss8z1c/6n5xwVjYIqQ/Dlvts99diQ1qYsPLogvdhV7I1n/oGynuLLzFwpISKFhKnBmIw2cCIfbdix3OZLn+OgQmWzMYEDPtZeMdCXje30zJnIZOotC7BAjs0aH6mr0cIiI37ZpfXnKida3JKFxXoceoEHmhXMOEq7xPJgFX2CNBypEqSWNZHK7tTKsqWytlqZ088o66SVVRHtyiYfN2lVxGONLwIDfcVI3YLkeEZ0NXC3e5Cam4iLdESkDBD2b/iOXkFy3iKZftH5OcVG3zBTX3NeM8JrTlJ4I42+dlNfXqBI5xllrivkyZHorPOu3lp9Yl/7QKUFfrKt0szArmhjDHTB4Gx9g1T75WorQywrh+AP75eb5TbWFkebAR3bdnGExfZOgA0zuo4N8fLcwmClde+tJcsrtRBPbMpNJnrJMyon35mryywpSMduJZVo5XepHpmybpmjpnrskntYNRFh7KVfkFzH8UrrHWBajzhbh2ukNO4grV5faRl1tLjINdLbhu/2iT9Dg3zYKMuR/X06bTIKjCpPX9cN+soxf5alDaYNPTF4VI7nzMUVqj6CIcfhXvUG9uep6xLvA+ljxDQFPsdkVdKZPhKk57ypMOa75Mn9KPefvNoiNejxm251Ptivoe+lapnLnU4WyVmktx2plAPSEpcbrZZlsxZRruv2o0GSrxL6Iq1zgtoHq4HlS+c20bQ=
*/