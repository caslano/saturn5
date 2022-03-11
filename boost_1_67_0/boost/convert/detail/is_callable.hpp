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
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
*/