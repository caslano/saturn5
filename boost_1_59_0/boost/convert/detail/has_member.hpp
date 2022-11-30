// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_HAS_MEMBER_HPP
#define BOOST_CONVERT_HAS_MEMBER_HPP

#include <boost/type_traits/detail/yes_no_type.hpp>

// This macro allows to check if a type has a member named "__member_name__"...
// ... regardless of the signature. If takes advantage of the following behavior related to
// function resolution. Say, both, foo and base, declare a method with the same name "func":
//
//      struct   foo { int  func (int, int) { return 0; } };
//      struct  base { void func () {} };
//      struct mixin : public foo, public base {};
//
// Now, if we inherit from both -- foo and base -- classes, then the following calls will fail
//      mixin_ptr(0)->func();
//      mixin_ptr(0)->func(5, 5);
// with the error message (gcc): request for member func is ambiguous
// regardless if we provide any arguments or not even though one might expect that
// arg-based signature resolution might kick in. The only way to deploy those methods is:
//
//      mixin_ptr(0)->foo::func();
//      mixin_ptr(0)->base::func(5, 5);
//
// C2. The actual signature of __member_name__ is not taken into account. If
//     __T__::__member_name__(any-signature) exists, then the introduced base::__member_name__
//     will cause mixin->__member_name__() call to fail to compile (due to ambiguity).
// C3. &U::__member_name__ (a.k.a. &mixin::__member_name__)
//     has the type of func_type only if __T__::__member_name__ does not exist.
//     If __T__::member_name does exist, then mixin::__member_name__ is ambiguous
//     and "yes_type test (...)" kicks in instead.
// C4. Need to find some unique/ugly name so that it does not clash if this macro is
//     used inside some other template class;

#define BOOST_DECLARE_HAS_MEMBER(__trait_name__, __member_name__)                           \
                                                                                            \
    template <typename __boost_has_member_T__> /*C4*/                                       \
    class __trait_name__                                                                    \
    {                                                                                       \
        using check_type = typename boost::remove_const<__boost_has_member_T__>::type;      \
        using   yes_type = ::boost::type_traits::yes_type;                                  \
        using    no_type = ::boost::type_traits:: no_type;                                  \
                                                                                            \
        struct  base { void __member_name__(/*C2*/) {}};                                    \
        struct mixin : public base, public check_type {};                                   \
                                                                                            \
        template <void (base::*)()> struct aux {};                                          \
                                                                                            \
        template <typename U> static no_type  test(aux<&U::__member_name__>*); /*C3*/       \
        template <typename U> static yes_type test(...);                                    \
                                                                                            \
        public:                                                                             \
                                                                                            \
        BOOST_STATIC_CONSTANT(bool, value = (sizeof(yes_type) == sizeof(test<mixin>(0))));  \
    }

#endif // BOOST_CONVERT_HAS_MEMBER_HPP

/* has_member.hpp
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
*/