/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_BASIC_CHSET_HPP
#define BOOST_SPIRIT_BASIC_CHSET_HPP

///////////////////////////////////////////////////////////////////////////////
#include <bitset>
#include <climits>
#include <boost/spirit/home/classic/utility/impl/chset/range_run.hpp>
#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  basic_chset: basic character set implementation using range_run
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    class basic_chset
    {
    public:
                            basic_chset();
                            basic_chset(basic_chset const& arg_);

        bool                test(CharT v) const;
        void                set(CharT from, CharT to);
        void                set(CharT c);
        void                clear(CharT from, CharT to);
        void                clear(CharT c);
        void                clear();

        void                inverse();
        void                swap(basic_chset& x);

        basic_chset&        operator|=(basic_chset const& x);
        basic_chset&        operator&=(basic_chset const& x);
        basic_chset&        operator-=(basic_chset const& x);
        basic_chset&        operator^=(basic_chset const& x);

        private: utility::impl::range_run<CharT> rr;
    };

    #if (CHAR_BIT == 8)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  basic_chset: specializations for 8 bit chars using std::bitset
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    class basic_chset_8bit {

    public:
                            basic_chset_8bit();
                            basic_chset_8bit(basic_chset_8bit const& arg_);

        bool                test(CharT v) const;
        void                set(CharT from, CharT to);
        void                set(CharT c);
        void                clear(CharT from, CharT to);
        void                clear(CharT c);
        void                clear();

        void                inverse();
        void                swap(basic_chset_8bit& x);

        basic_chset_8bit&   operator|=(basic_chset_8bit const& x);
        basic_chset_8bit&   operator&=(basic_chset_8bit const& x);
        basic_chset_8bit&   operator-=(basic_chset_8bit const& x);
        basic_chset_8bit&   operator^=(basic_chset_8bit const& x);

        private: std::bitset<256> bset;
    };

    /////////////////////////////////
    template <>
    class basic_chset<char>
    : public basic_chset_8bit<char> {};

    /////////////////////////////////
    template <>
    class basic_chset<signed char>
    : public basic_chset_8bit<signed char> {};

    /////////////////////////////////
    template <>
    class basic_chset<unsigned char>
    : public basic_chset_8bit<unsigned char> {};

#endif

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/utility/impl/chset/basic_chset.ipp>

/* basic_chset.hpp
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
*/