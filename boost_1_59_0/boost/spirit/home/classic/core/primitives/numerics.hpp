/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_NUMERICS_HPP
#define BOOST_SPIRIT_NUMERICS_HPP

#include <boost/config.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/directives.hpp>

#include <boost/spirit/home/classic/core/primitives/numerics_fwd.hpp>
#include <boost/spirit/home/classic/core/primitives/impl/numerics.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  uint_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, 
        int Radix, 
        unsigned MinDigits,
        int MaxDigits
    >
    struct uint_parser : parser<uint_parser<T, Radix, MinDigits, MaxDigits> >
    {
        typedef uint_parser<T, Radix, MinDigits, MaxDigits> self_t;
    
        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, T>::type type;
        };
        
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef impl::uint_parser_impl<T, Radix, MinDigits, MaxDigits> impl_t;
            typedef typename parser_result<impl_t, ScannerT>::type result_t;
            return impl::contiguous_parser_parse<result_t>(impl_t(), scan, scan);
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  int_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T,
        int Radix,
        unsigned MinDigits,
        int MaxDigits
    >
    struct int_parser : parser<int_parser<T, Radix, MinDigits, MaxDigits> >
    {
        typedef int_parser<T, Radix, MinDigits, MaxDigits> self_t;
    
        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, T>::type type;
        };
        
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef impl::int_parser_impl<T, Radix, MinDigits, MaxDigits> impl_t;
            typedef typename parser_result<impl_t, ScannerT>::type result_t;
            return impl::contiguous_parser_parse<result_t>(impl_t(), scan, scan);
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  uint_parser/int_parser instantiations
    //
    ///////////////////////////////////////////////////////////////////////////
    int_parser<int> const
        int_p   = int_parser<int>();
    
    uint_parser<unsigned> const
        uint_p  = uint_parser<unsigned>();
    
    uint_parser<unsigned, 2> const
        bin_p   = uint_parser<unsigned, 2>();
    
    uint_parser<unsigned, 8> const
        oct_p   = uint_parser<unsigned, 8>();
    
    uint_parser<unsigned, 16> const
        hex_p   = uint_parser<unsigned, 16>();
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  sign_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    namespace impl
    {
        //  Utility to extract the prefix sign ('-' | '+')
        template <typename ScannerT>
        bool extract_sign(ScannerT const& scan, std::size_t& count);
    }
    
    struct sign_parser : public parser<sign_parser>
    {
        typedef sign_parser self_t;

        template <typename ScannerT>
        struct result 
        {
            typedef typename match_result<ScannerT, bool>::type type;
        };

        sign_parser() {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            if (!scan.at_end())
            {
                std::size_t length;
                typename ScannerT::iterator_t save(scan.first);
                bool neg = impl::extract_sign(scan, length);
                if (length)
                    return scan.create_match(1, neg, save, scan.first);
            }
            return scan.no_match();
        }
    };
    
    sign_parser const sign_p = sign_parser();
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  default real number policies
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct ureal_parser_policies
    {
        // trailing dot policy suggested suggested by Gustavo Guerra
        BOOST_STATIC_CONSTANT(bool, allow_leading_dot = true);
        BOOST_STATIC_CONSTANT(bool, allow_trailing_dot = true);
        BOOST_STATIC_CONSTANT(bool, expect_dot = false);
    
        typedef uint_parser<T, 10, 1, -1>   uint_parser_t;
        typedef int_parser<T, 10, 1, -1>    int_parser_t;
    
        template <typename ScannerT>
        static typename match_result<ScannerT, nil_t>::type
        parse_sign(ScannerT& scan)
        { 
            return scan.no_match(); 
        }
    
        template <typename ScannerT>
        static typename parser_result<uint_parser_t, ScannerT>::type
        parse_n(ScannerT& scan)
        { 
            return uint_parser_t().parse(scan); 
        }
    
        template <typename ScannerT>
        static typename parser_result<chlit<>, ScannerT>::type
        parse_dot(ScannerT& scan)
        { 
            return ch_p('.').parse(scan); 
        }
    
        template <typename ScannerT>
        static typename parser_result<uint_parser_t, ScannerT>::type
        parse_frac_n(ScannerT& scan)
        { 
            return uint_parser_t().parse(scan); 
        }
    
        template <typename ScannerT>
        static typename parser_result<chlit<>, ScannerT>::type
        parse_exp(ScannerT& scan)
        { 
            return as_lower_d['e'].parse(scan); 
        }
    
        template <typename ScannerT>
        static typename parser_result<int_parser_t, ScannerT>::type
        parse_exp_n(ScannerT& scan)
        { 
            return int_parser_t().parse(scan); 
        }
    };
    
    template <typename T>
    struct real_parser_policies : public ureal_parser_policies<T>
    {
        template <typename ScannerT>
        static typename parser_result<sign_parser, ScannerT>::type
        parse_sign(ScannerT& scan)
        { 
            return sign_p.parse(scan); 
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  real_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T,
        typename RealPoliciesT
    >
    struct real_parser
    :   public parser<real_parser<T, RealPoliciesT> >
    {
        typedef real_parser<T, RealPoliciesT> self_t;
    
        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, T>::type type;
        };
    
        real_parser() {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::real_parser_impl<result_t, T, RealPoliciesT>::parse(scan);
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  real_parser instantiations
    //
    ///////////////////////////////////////////////////////////////////////////
    real_parser<double, ureal_parser_policies<double> > const
        ureal_p     = real_parser<double, ureal_parser_policies<double> >();
    
    real_parser<double, real_parser_policies<double> > const
        real_p      = real_parser<double, real_parser_policies<double> >();
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  strict reals (do not allow plain integers (no decimal point))
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct strict_ureal_parser_policies : public ureal_parser_policies<T>
    {
        BOOST_STATIC_CONSTANT(bool, expect_dot = true);
    };
    
    template <typename T>
    struct strict_real_parser_policies : public real_parser_policies<T>
    {
        BOOST_STATIC_CONSTANT(bool, expect_dot = true);
    };
    
    real_parser<double, strict_ureal_parser_policies<double> > const
        strict_ureal_p
            = real_parser<double, strict_ureal_parser_policies<double> >();
    
    real_parser<double, strict_real_parser_policies<double> > const
        strict_real_p
            = real_parser<double, strict_real_parser_policies<double> >();
    
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* numerics.hpp
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
*/