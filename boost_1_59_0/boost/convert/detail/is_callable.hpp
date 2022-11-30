// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CALLABLE_HPP
#define BOOST_CONVERT_IS_CALLABLE_HPP

#include <boost/convert/detail/has_member.hpp>

namespace boost { namespace cnv { namespace detail
{
    using yes_type = ::boost::type_traits::yes_type;
    using  no_type = ::boost::type_traits:: no_type;

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