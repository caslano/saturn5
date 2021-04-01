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
A/7/1OKrDo8cQQ1ojcZu2uGr6bUAdqtfpw/PopUrXTIEVFmQTbjxzy5HIF7GOyCyvn9ZAfIMXx87CX0ulyXQAzUOoUtjyr8aE7/DxPvc3XB6uGR60xr9THjlo2Io9dJ0NpxME5p/xlnsvj40VVrlsA/FfqDZ7fTYsfH3dXN4IgScLNAF/RXZNt3HhVFLEk77xdhsciXOqJ5KXrNYg5v0QCbKD3LdCAhcbH7bkwYt7XHpOf0QR5KtkUz5c3Hdif1E8Afun/1Uvp2KU4Enx8+UbLUWR3N/VXjhGZlC89nNBJXI45CzCLDop9jP9GUMMfgJViFM+wznpdG8shkLb3Ik3Gb96dTd07vs96h1U5629jtWJVMGyl6JU2TrTfjoT9YIX8i5AojeOLxS6XpxgAxjPUOSdCZxgHBmw65cR2A182jq1CZDSAyExosCUBU/fOVa5NsMdkT/9xq18gTgXUoT6YmT+em3GWA9B7WbFjme3qxvNsgDR+o9G6Zle9VnGLZj4dupLyh1J8h8hvHCubl9YY4TttwCIH8VwMrtYHfjSJHBdnq6Tk6dd2DXjA==
*/