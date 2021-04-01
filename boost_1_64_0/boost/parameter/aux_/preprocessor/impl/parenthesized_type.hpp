// Copyright David Abrahams 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // A metafunction that transforms void(*)(T) -> T
    template <typename UnaryFunctionPointer>
    struct unaryfunptr_arg_type;

    template <typename Arg>
    struct unaryfunptr_arg_type<void(*)(Arg)>
    {
        typedef Arg type;
    };

    template <>
    struct unaryfunptr_arg_type<void(*)(void)>
    {
        typedef void type;
    };
}}} // namespace boost::parameter::aux

// A macro that takes a parenthesized C++ type name (T) and transforms it
// into an un-parenthesized type expression equivalent to T.
#define BOOST_PARAMETER_PARENTHESIZED_TYPE(x)                                \
    ::boost::parameter::aux::unaryfunptr_arg_type< void(*)x >::type

#endif  // include guard


/* parenthesized_type.hpp
vUgcPerJ/gwYdcC92fNmvUKawIWtu/ZYWq8Mws9wyhHOCRHIFBiN1/13fVUSuf8xxsr12CsSG9fXVHDfXFpDjKQreoUG0K3FFqB61dpgaNn4EIHe5n+2RwTNlN1t2vSKRhoQ/qPZ0uA/pom411dKinlGyAoX+23qzOJ3bFLIDj4HknhVJUqQkad64P694oGEbWyondUTRFxCDuWlaZ/HzbR5YjLuJVWyRjfOWr03MFZv+Mop6xIY2kfKJ4nYvRBox05KWm36JTZPEDQtUWILlBqHULKJwdGdPVDbgoJCa2/DuorKTkTLWNA7ASFinlGaMd+Y1D8wts7yQytCjwHCQ7suf4IqiXzQLFfTbV1sxtC6dCgD4K3rm5qWiHI7ByMQW7Gtf9MhPeGdoN4SY+kX5/VWuAwfRPJildbbEUaKsgQJUNnOqY27FjxNfvb3/EF7GTSIDl3PSoI02YIO/nfpkciWfoC1fYUOxHV3JH8SNeP4VPdBMYnSsJUHQeYKF4P40GoYNX8Q3G7/yhQqnlAMeTGHIHZT4cMFlHy1iKmsMMi99DCj1HFwClGmMw==
*/