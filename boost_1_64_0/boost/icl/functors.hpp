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
eA+XjtzA6DCKtAuWnyFJEySyKspwrnUhZzCms6hpMW7OXAEuZok4ijp5xDEzj5pVs6woHAZVBlaHBmar7yTEN5s0Plsgk6F91Hm4vjHzSZkyS5ORgHidXhA7BQ0kIJWo/HQp7YotlLMzZRKM0P096nIxG88Y+JVIRAKeuNJaYJQkkLEVEglbns4TiYgfoTQFeSk8OVssUa9ZmIhuCWGSkKxd7UxMHRxUQjGOB/qOhHJV61L2NCskz6xoUfU+kmkp+qUEWXyBIFF9QOjHAzZPnEj6yqjLKlm2XCmVSmQKzXHD0dFZFhlh4zqnQFuQng1kavJFEh45FHLsBfrGWNplctU89B5Tx4GXXtFRgmsw5qHKqcbDvibTO88s0xxlOh8+hQpVG7PThWhWBZ9qbN1yECQ7h0bEQVTyye7RCY0sSqTmlGP5ZFomRysr08lhEvFkyfQO0icDnUlaGUmIS18yT8Smr8PU9iVJZNgCFOmW0+eETh4/BfuPDZHJdevSS9DNSxFk6UwL0yv2i7EuddPp5InxLx4j1X1QjDI5WoOtukgxypQ4RxnTlS2DPiSMPCl1AmCEJ8bls7IyORudp9RTDlt9K2bWk9KwtfPIhmJ7qaXq5mv62HTzBwlkEjbBQ+5YJKnaiJwSPDlfKKRbnVlecQZQ5eSwq8uxImEiddzZ9IEnpwBOwyQsg1FHc92gT1JmORzi4loxnY79IBoZ9XApJhcE7TycpQkkR5OnuXYRtlirThl9F6DlCehTT7dcQBUpAJ2RT3YATZ8gUrWxbrlSLMzA0ngi5p4ylkPF1XQVnXzNInFFU2hfmUlbiDWHT90smjLGtZzk/ekarxLOFkj42tPYZyxdtyk1ZWS7qGl6o8n5otlXUlNTRl97tUCqXJHbDl1FlY+THp7/yj/zXKTzqAMpUSansMnjFZUYzaHOI9c9cnVNkQj5At0y9F8IqfcNuBAlZpP3FUoZSisrV4oTebJsTRnVmpWsD9eBSm9wSKrzj7k7dFmiuqHZkiTSAvTO6xwD3esuygYqcTIL/nSN15Qzr+/McnIHwobhHiinKiYJkzV1UnDHw+1brGoUaqf/5JF+tERLV3K3pI+z5h7BzCOrofIUKQJyYvz17R6tSpabJpZkislVR5GCrHSyfE2irnV/unhpt572hmg/dGB3/themjJG54NSTO7CqEkIkcRw/6dTAvU0+4MN1c1LF8jlPFxh1c8jeJ5F1JOSzpyXbipyJHTypeQZnX6GYZZR4SxPgXOdudiKOkQsPa0+luTmwka/H84HXL8rlsusV7HuP9fRFNANo7mzkFxN/h+WpH1NiYvt4knl3R5ujhcVdB/fY4zXUI3f4JN80t9YhnwDFt2P+pGqQ8aRckgd0r9uhHFj1bhVDl2/OobGGK+uGrfNIfOSvkIXUoced8e4KTUfhhBShx6PVdWh1hGP8Vqq8RTVMqkyKcZrqsaHqJbTGMM0sm30+DzVcupT/dmkPj1uNpTUIf2Va8j20+OFqvrUh8j7SH16vAjjVD9zQ6p9yHbS449V6zXH8JXUp8cNR9DLsaDaZwTJJ+MWGK+tGrdVjTei2gHj1VXjPiPo5dej2oTUocfjMa7+OCuRLJ8eTyHj9HsHkWpcH0dSSurT40NU+Xr4L4fk0+OTVOuqhvF5qvHqGF+hGq+B8S2qcUOM78M4+UgM48fINtPj/64UEBkZpv7l+EeQPPQMsLR7BzgRceHqX/Q1xnKC6HkjQ4NY6q4FVZcKcsk4i9EtSfKRR8bJvJgJAydW0w9C9alQU+RXkxsXEdqDg2A/TJND55Ht9PegBnUJcRmjdX8PCI+iBk15j9CYUPRyMadJ3SjkoQ9MXao=
*/