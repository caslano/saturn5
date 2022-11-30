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
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
*/