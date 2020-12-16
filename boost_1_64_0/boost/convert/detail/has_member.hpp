// Copyright (c) 2009-2016 Vladimir Batov.
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
        typedef typename boost::remove_const<__boost_has_member_T__>::type check_type;      \
        typedef ::boost::type_traits::yes_type                yes_type;                     \
        typedef ::boost::type_traits:: no_type                 no_type;                     \
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
BjgiwsE3+pITFH0Rbpw9pU9CpCPZHpHiSI4Li41V2oltJ0cPsrNuZRx10/RgdX0cap+kfmHaOvwt9fY+Rl0lS10440aExyZE9PWMbexBladJVmr5/R308nJyeVRSQpwjNT4uLJ4pIlWZ3bjekWRPCYuOd4QlJkYmxPEvjyxqyH0iFBkkJKcg+CSEp+llI2kf9rCUGEdKn9T4vg5FSNRjBop8Y8OSUTXOQYxtlCeiT/QWNcg0yVaxNmGgv7CzOGwnyVUoYNQdUVDUJ6MoviTPVZSTHunKzMl3Kcbfv8PNWgACzPWYTbU/ssgFI1xFqW5XUWKRy+3KL9bkbJTHFxRrVZ7zM+qi853pxTmlLvYExhvlcc6ROXkleYxlKqd9qTM3J8N2Noo9ldf2lMCeHKnJ9iRHWAT6F50y0IGRJNvjI+zqdm5QyU7OvqHvIyVROYtwREeL6IQk0bRPdG9Nt33XYzoosWdfvtvEJvTX9uG7Pjq+X1hsdOTN2qAGqSAIcg+X9v2g2Lev5uqufVaJPW+yebAzJiHckRAeI4wx3p7iSApLERoXD8TFglzop65X/jdti85hafGR/aMjNSwod9P2kckRiY6UsN7qnivetK0iHBUAkfMg9o9/YP/EpOz/Zj2VPqos/mMzIZenfcklOsGnWBSZ3KQdfgJ5hOGM7I5+CbGp2KF6vuY+N94qcmev9FD3mspeTT3/zlZ9tlLtV/jTJjYz5+vv4XzEKvBtNQ4iVpF/L+T3fhrvCFQ5ptuR6czLyR1lE2UDGcMfXkFpoTOjnc3DdyupZRhvlh5HDKJtDb1tKG+2yitnO1jiKONt7oL04c6MjCKYa0GRM8vlGFmoMBQf5Wwt3BfPKsMYs1u383ug+73cMHKfnfr97588MLvP6g//kTv9yYeShLzaxObkD48WnKpNvhOuaGvjLkpvk+1ywkjTchmOE0Zq/DAC7JU//EFSSJgfrY4/eGH+8Of7B9v73Yr/b8X/t+L/W/H/rfj/Vvx/K/6/Ff/fiv9vxf+34v9b8f+t+P9W/H8r/v+7sfv/I/4n3gy28WcEmwtLjm/nwBMInx8d39uR7xoBH6WeP6Ooj8CzpyQ48py58CR0k9iTOjDWR9/MIpdL7DtYazPG6K9UeeZ9jPKc0HSHpT/cqWLw49T1QEDEj5yXwmmVPq1bD+F/BYWufLc79752rdu1bps5JL1oVGFxwRCnO7/dEKcjIzTHkVnYOl3w6eDyxFOImZ8MfgTTIlJnPM/epnrWL3ql5RSIdXvWN4M6xlTrikh7iAZS32eoD0+NwmfHee15jjQuq7F5yl8QfdBVFCkn18UTZq18nlaO3PW287Wy9OKiXHnsBUq5Kkx5vUs8c+YUu/LExJb1vmKttxl9l1nrWLQ856vGXk26sZxyGJojPZf42OEqKioo0s93pdQnq6hghNIo36aPuUrdhyJa5tLX+YZnLVmuYkdB2jBXerE+32ptvkKXa7g6HTJEX3ZSXoy+RNs4YfYlyvZTtoKyH6WygJpqu1yprHpNtZ1LKquntWsolbXUyrpJZa21slCprC1lBygr9DPKemrthkrtYrWyflJZvraWLlJZqdYuUSobqZVlSWWPan3PS2UfaO2aibIy2lFOlstd7GVHkyQ7MvTjh5oefVd66Tp8mHJ7v0RHpFqs69vRmiZ9U2plHThmqs8JzSjj2ksAADGeee3Tfa79uGcueslrOGlaA5VlW0MWLDCPVVjWMNO0hubaXL945uptj7cn4RsH2SNTook5nBnDZDs8TTuHG0Bw5bdvZ/QHw2/QH2OV93Se/gmJ9vjk5FhHVp5IARhn8rtXnTK7PkfcjeYQQCThzB81NYzLLyw=
*/