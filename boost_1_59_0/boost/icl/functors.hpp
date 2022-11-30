/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_FUNCTORS_HPP_JOFA_080315
#define BOOST_ICL_FUNCTORS_HPP_JOFA_080315

#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/unit_element.hpp>
#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/has_set_semantics.hpp>

namespace boost{namespace icl
{
    // ------------------------------------------------------------------------
    template <typename Type> struct identity_based_inplace_combine 
    {
        typedef Type& first_argument_type;
        typedef const Type& second_argument_type;
        typedef void result_type;
        inline static Type identity_element() { return boost::icl::identity_element<Type>::value(); }
    };

    // ------------------------------------------------------------------------
    template <typename Type> struct unit_element_based_inplace_combine 
    {
        typedef Type& first_argument_type;
        typedef const Type& second_argument_type;
        typedef void result_type;
        inline static Type identity_element() { return boost::icl::unit_element<Type>::value(); }
    };

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_identity 
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_identity<Type> type;
        void operator()(Type&, const Type&)const{}
    };

    template<>
    inline std::string unary_template_to_string<inplace_identity>::apply() 
    { return "i="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_erasure 
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_erasure<Type> type;
        typedef identity_based_inplace_combine<Type> base_type;

        void operator()(Type& object, const Type& operand)const
        { 
            if(object == operand)
                //identity_element(); //JODO Old gcc-3.4.4 does not compile this
                object = base_type::identity_element(); //<-- but this.
        }
    };

    template<>
    inline std::string unary_template_to_string<inplace_erasure>::apply() 
    { return "0="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_plus 
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_plus<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object += operand; }

        static void version(Type&){}
    };

    template<>
    inline std::string unary_template_to_string<inplace_plus>::apply() { return "+="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_minus 
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_minus<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object -= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_minus>::apply() { return "-="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_bit_add
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_bit_add<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object |= operand; }

        static void version(Type&){}
    };

    template<>
    inline std::string unary_template_to_string<inplace_bit_add>::apply() { return "b|="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_bit_subtract
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_bit_subtract<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object &= ~operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_bit_subtract>::apply() { return "b-="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_bit_and
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_bit_and<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object &= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_bit_and>::apply() { return "b&="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_bit_xor
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_bit_xor<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object ^= operand; }
    };

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_et
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_et<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object &= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_et>::apply() { return "&="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_caret
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_caret<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object ^= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_caret>::apply() { return "^="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_insert
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_insert<Type> type;

        void operator()(Type& object, const Type& operand)const
        { insert(object,operand); }
    };

    template<>
    inline std::string unary_template_to_string<inplace_insert>::apply() { return "ins="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_erase
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_erase<Type> type;

        void operator()(Type& object, const Type& operand)const
        { erase(object,operand); }
    };

    template<>
    inline std::string unary_template_to_string<inplace_erase>::apply() { return "ers="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_star
        : public identity_based_inplace_combine<Type> //JODO unit_element_
    {
        typedef inplace_star<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object *= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_star>::apply() { return "*="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_slash
        : public identity_based_inplace_combine<Type> //JODO unit_element_
    {
        typedef inplace_slash<Type> type;

        void operator()(Type& object, const Type& operand)const
        { object /= operand; }
    };

    template<>
    inline std::string unary_template_to_string<inplace_slash>::apply() { return "/="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_max
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_max<Type> type;

        void operator()(Type& object, const Type& operand)const
        {
            if(object < operand)
                object = operand;
        }
    };

    template<>
    inline std::string unary_template_to_string<inplace_max>::apply() { return "max="; }

    // ------------------------------------------------------------------------
    template <typename Type> struct inplace_min
        : public identity_based_inplace_combine<Type>
    {
        typedef inplace_min<Type> type;

        void operator()(Type& object, const Type& operand)const
        {
            if(object > operand)
                object = operand;
        }
    };

    template<>
    inline std::string unary_template_to_string<inplace_min>::apply() { return "min="; }

    //--------------------------------------------------------------------------
    // Inter_section functor
    //--------------------------------------------------------------------------
    template<class Type> struct inter_section
        : public identity_based_inplace_combine<Type>
    {
        typedef typename boost::mpl::
            if_<has_set_semantics<Type>,
                icl::inplace_et<Type>, 
                icl::inplace_plus<Type> 
               >::type
            type;

        void operator()(Type& object, const Type& operand)const
        { 
            type()(object, operand);
        }
    };

    //--------------------------------------------------------------------------
    // Inverse functor
    //--------------------------------------------------------------------------
    template<class Functor> struct inverse;

    template<class Type> 
    struct inverse<icl::inplace_plus<Type> >
    { typedef icl::inplace_minus<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_minus<Type> >
    { typedef icl::inplace_plus<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_bit_add<Type> >
    { typedef icl::inplace_bit_subtract<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_bit_subtract<Type> >
    { typedef icl::inplace_bit_add<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_et<Type> >
    { typedef icl::inplace_caret<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_caret<Type> >
    { typedef icl::inplace_et<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_bit_and<Type> >
    { typedef icl::inplace_bit_xor<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_bit_xor<Type> >
    { typedef icl::inplace_bit_and<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_star<Type> >
    { typedef icl::inplace_slash<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_slash<Type> >
    { typedef icl::inplace_star<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_max<Type> >
    { typedef icl::inplace_min<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_min<Type> >
    { typedef icl::inplace_max<Type> type; };

    template<class Type> 
    struct inverse<icl::inplace_identity<Type> >
    { typedef icl::inplace_erasure<Type> type; };

    // If a Functor 
    template<class Functor> 
    struct inverse
    {
        typedef typename 
            remove_reference<typename Functor::first_argument_type>::type argument_type;
        typedef icl::inplace_erasure<argument_type> type; 
    };


    //--------------------------------------------------------------------------
    // Inverse inter_section functor
    //--------------------------------------------------------------------------
    template<class Type> 
    struct inverse<icl::inter_section<Type> >
        : public identity_based_inplace_combine<Type>
    {
        typedef typename boost::mpl::
            if_<has_set_semantics<Type>,
                icl::inplace_caret<Type>, 
                icl::inplace_minus<Type> 
               >::type
            type;

        void operator()(Type& object, const Type& operand)const
        { 
            type()(object, operand);
        }
    };


    //--------------------------------------------------------------------------
    // Positive or negative functor trait
    //--------------------------------------------------------------------------

    // A binary operation - is negative (or inverting) with respect to the
    // neutral element iff it yields the inverse element if it is applied to the 
    // identity element:
    // 0 - x = -x
    // For a functor that wraps the inplace of op-assign version this is 
    // equivalent to
    //
    // T x = ..., y;
    // y = Functor::identity_element();
    // Functor()(y, x); // y == inverse_of(x) 

    template<class Functor> struct is_negative;

    template<class Functor> 
    struct is_negative
    {
        typedef is_negative<Functor> type;
        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template<class Type> 
    struct is_negative<icl::inplace_minus<Type> >
    {
        typedef is_negative type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Type> 
    struct is_negative<icl::inplace_bit_subtract<Type> >
    {
        typedef is_negative type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    //--------------------------------------------------------------------------
    // Pro- or in-version functor
    //--------------------------------------------------------------------------
    template<class Combiner> struct conversion;

    template<class Combiner> 
    struct conversion
    { 
        typedef conversion<Combiner> type;
        typedef typename
            remove_const<
                typename remove_reference<typename Combiner::first_argument_type
                >::type
            >::type
            argument_type;
        // The proversion of an op-assign functor o= lets the value unchanged
        // (0 o= x) == x;
        // Example += :  (0 += x) == x
        static argument_type proversion(const argument_type& value)
        { 
            return value; 
        } 

        // The inversion of an op-assign functor o= inverts the value x
        // to it's inverse element -x
        // (0 o= x) == -x;
        // Example -= :  (0 -= x) == -x
        static argument_type inversion(const argument_type& value)
        {
            argument_type inverse = Combiner::identity_element();
            Combiner()(inverse, value);
            return inverse;
        }
    };

    template<class Combiner> struct version : public conversion<Combiner>
    {
        typedef    version<Combiner> type;
        typedef conversion<Combiner> base_type;
        typedef typename base_type::argument_type argument_type;

        argument_type operator()(const argument_type& value)
        { return base_type::proversion(value); } 
    };

    template<>struct version<icl::inplace_minus<short      > >{short       operator()(short       val){return -val;}};
    template<>struct version<icl::inplace_minus<int        > >{int         operator()(int         val){return -val;}};
    template<>struct version<icl::inplace_minus<long       > >{long        operator()(long        val){return -val;}};
    template<>struct version<icl::inplace_minus<long long  > >{long long   operator()(long long   val){return -val;}};
    template<>struct version<icl::inplace_minus<float      > >{float       operator()(float       val){return -val;}};
    template<>struct version<icl::inplace_minus<double     > >{double      operator()(double      val){return -val;}};
    template<>struct version<icl::inplace_minus<long double> >{long double operator()(long double val){return -val;}};

    template<class Type> 
    struct version<icl::inplace_minus<Type> > : public conversion<icl::inplace_minus<Type> >
    { 
        typedef    version<icl::inplace_minus<Type> > type;
        typedef conversion<icl::inplace_minus<Type> > base_type;
        typedef typename base_type::argument_type argument_type;

        Type operator()(const Type& value)
        {
            return base_type::inversion(value);
        } 
    };

}} // namespace icl boost

#endif



/* functors.hpp
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
*/