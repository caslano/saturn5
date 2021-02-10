/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102
#define BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102

namespace boost{namespace icl
{
    // naming convention
    // predicate: n-ary predicate
    // property:  unary predicate
    // relation:  binary predicate

    // Unary predicates

    template <class Type>
    class property
    {
    public:
        typedef Type argument_type;
        typedef bool result_type;
    };

    template <class Type>
    class member_property : public property<Type>
    {
    public:
        member_property( bool(Type::* pred)()const ): property<Type>(), m_pred(pred){}
        bool operator()(const Type& x)const { return (x.*m_pred)(); }
    private:
        bool(Type::* m_pred)()const;
    } ;

    // Binary predicates: relations

    template <class LeftT, class RightT>
    class relation
    {
    public:
        typedef LeftT first_argument_type;
        typedef RightT second_argument_type;
        typedef bool result_type;
    };


}} // namespace icl boost

#endif


/* predicate.hpp
CMqUU0wws/DsyGmKHYqPHeU2WanxDCiKBC42WnIwsF4EuChSbCjlwCthRgWItAXLx/7g2bKKkfEeppXa92hFE1EwZQSUPsC6iLmzA6aqUYPCUkdjeu77so5ZUZt+/L9waFlikY0VCAaVB3EXo/UU3zxb+PG9S4nvmzM9RUPCrtwn21EE7Lj/bju2M3Y8RGvujFIUD+NM4TykBAa7qhkbMOFMfUwm5D5AyGMqIad812iHOfTg2fEUs8MqEkb5aHu0v/t77VBgVBiKphJShDKVphjyeZAGRqcI/H66KRIQWoO+oA+DwkF7QnoPFEuOHSqRWTPKFDPOVKwDVJRJg6HnklaTavFcqBIGA4q/MwOeDVWKDXIwo6zHDjqp/EqFlOHUWwWNUms0rAPEC/gCsXCcyXwKOFKnhMMmuB32c3TW9HtKZNBgh5zXMvIstUJWgR6aZykhUSjD51Izz5MrpMeOF66OPI9yoTU/jecZjCJGxAZTs5I74XIcuRw6r9/kRbSHYywv+patlkDfyqPChVfUDQOU2CMKdC898qhocQgaqCrbmRTL16m5sQ50z3yd1MYHUbpas47Ucgh4ElUbdHPUxJsDMsL5hpYvPkiMDhvdszFUNRhd4VdLsuJYB5ponqQ48LYNCq8aMBeVqNo4
*/