/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CONSTRUCT_MAR_24_2007_0629PM)
#define BOOST_SPIRIT_CONSTRUCT_MAR_24_2007_0629PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  We provide overloads for the assign_to_attribute_from_iterators
    //  customization point for all built in types
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<char, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const&, char& attr)
        {
            attr = *first;
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<signed char, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const&, signed char& attr)
        {
            attr = *first;
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<unsigned char, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const&, unsigned char& attr)
        {
            attr = *first;
        }
    };

    // wchar_t is intrinsic
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<wchar_t, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const&, wchar_t& attr)
        {
            attr = *first;
        }
    };

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    // wchar_t is intrinsic, have separate overload for unsigned short
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<unsigned short, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const&, unsigned short& attr)
        {
            attr = *first;
        }
    };
#endif

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<bool, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, bool& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, bool_type(), attr);
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<short, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, short& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, short_type(), attr);
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<int, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, int& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, int_type(), attr);
        }
    };
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<unsigned int, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, unsigned int& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, uint_type(), attr);
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<long, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, long& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, long_type(), attr);
        }
    };
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<unsigned long, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, unsigned long& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, ulong_type(), attr);
        }
    };

#ifdef BOOST_HAS_LONG_LONG
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<boost::long_long_type, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, boost::long_long_type& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, long_long_type(), attr);
        }
    };
    template <typename Iterator>
    struct assign_to_attribute_from_iterators<boost::ulong_long_type, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, boost::ulong_long_type& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, ulong_long_type(), attr);
        }
    };
#endif

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<float, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, float& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, float_type(), attr);
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<double, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, double& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, double_type(), attr);
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<long double, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last, long double& attr)
        {
            Iterator first_ = first;
            qi::parse(first_, last, long_double_type(), attr);
        }
    };

}}}

#endif

/* construct.hpp
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
*/