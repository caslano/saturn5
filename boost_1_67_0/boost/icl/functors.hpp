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