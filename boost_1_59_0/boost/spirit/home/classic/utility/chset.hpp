/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_CHSET_HPP
#define BOOST_SPIRIT_CHSET_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/shared_ptr.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/utility/impl/chset/basic_chset.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

namespace utility { namespace impl {

    // This is here because some compilers choke on out-of-line member
    // template functions.  And we don't want to put the whole algorithm
    // in the chset constructor in the class definition.
    template <typename CharT, typename CharT2>
    void construct_chset(boost::shared_ptr<basic_chset<CharT> >& ptr,
            CharT2 const* definition);

}} // namespace utility::impl

///////////////////////////////////////////////////////////////////////////////
//
//  chset class
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT = char>
class chset: public char_parser<chset<CharT> > {

public:
                    chset();
                    chset(chset const& arg_);
    explicit        chset(CharT arg_);
    explicit        chset(anychar_parser arg_);
    explicit        chset(nothing_parser arg_);
    explicit        chset(chlit<CharT> const& arg_);
    explicit        chset(range<CharT> const& arg_);
    explicit        chset(negated_char_parser<chlit<CharT> > const& arg_);
    explicit        chset(negated_char_parser<range<CharT> > const& arg_);

                    template <typename CharT2>
    explicit        chset(CharT2 const* definition)
                    : ptr(new basic_chset<CharT>())
                    {
                        utility::impl::construct_chset(ptr, definition);
                    }
                    ~chset();

    chset&          operator=(chset const& rhs);
    chset&          operator=(CharT rhs);
    chset&          operator=(anychar_parser rhs);
    chset&          operator=(nothing_parser rhs);
    chset&          operator=(chlit<CharT> const& rhs);
    chset&          operator=(range<CharT> const& rhs);
    chset&          operator=(negated_char_parser<chlit<CharT> > const& rhs);
    chset&          operator=(negated_char_parser<range<CharT> > const& rhs);

    void            set(range<CharT> const& arg_);
    void            set(negated_char_parser<chlit<CharT> > const& arg_);
    void            set(negated_char_parser<range<CharT> > const& arg_);

    void            clear(range<CharT> const& arg_);
    void            clear(negated_char_parser<range<CharT> > const& arg_);
    bool            test(CharT ch) const;
    chset&          inverse();
    void            swap(chset& x);

    chset&          operator|=(chset const& x);
    chset&          operator&=(chset const& x);
    chset&          operator-=(chset const& x);
    chset&          operator^=(chset const& x);

private:

    boost::shared_ptr<basic_chset<CharT> > ptr;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Generator functions
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
inline chset<CharT>
chset_p(chlit<CharT> const& arg_)
{ return chset<CharT>(arg_); }

//////////////////////////////////
template <typename CharT>
inline chset<CharT>
chset_p(range<CharT> const& arg_)
{ return chset<CharT>(arg_); }

template <typename CharT>
inline chset<CharT>
chset_p(negated_char_parser<chlit<CharT> > const& arg_)
{ return chset<CharT>(arg_); }

template <typename CharT>
inline chset<CharT>
chset_p(negated_char_parser<range<CharT> > const& arg_)
{ return chset<CharT>(arg_); }

//////////////////////////////////
inline chset<char>
chset_p(char const* init)
{ return chset<char>(init); }

//////////////////////////////////
inline chset<wchar_t>
chset_p(wchar_t const* init)
{ return chset<wchar_t>(init); }

//////////////////////////////////
inline chset<char>
chset_p(char ch)
{ return chset<char>(ch); }

//////////////////////////////////
inline chset<wchar_t>
chset_p(wchar_t ch)
{ return chset<wchar_t>(ch); }

//////////////////////////////////
inline chset<int>
chset_p(int ch)
{ return chset<int>(ch); }

//////////////////////////////////
inline chset<unsigned int>
chset_p(unsigned int ch)
{ return chset<unsigned int>(ch); }

//////////////////////////////////
inline chset<short>
chset_p(short ch)
{ return chset<short>(ch); }

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
//////////////////////////////////
inline chset<unsigned short>
chset_p(unsigned short ch)
{ return chset<unsigned short>(ch); }
#endif
//////////////////////////////////
inline chset<long>
chset_p(long ch)
{ return chset<long>(ch); }

//////////////////////////////////
inline chset<unsigned long>
chset_p(unsigned long ch)
{ return chset<unsigned long>(ch); }

#ifdef BOOST_HAS_LONG_LONG
//////////////////////////////////
inline chset< ::boost::long_long_type>
chset_p( ::boost::long_long_type ch)
{ return chset< ::boost::long_long_type>(ch); }

//////////////////////////////////
inline chset< ::boost::ulong_long_type>
chset_p( ::boost::ulong_long_type ch)
{ return chset< ::boost::ulong_long_type>(ch); }
#endif

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/utility/impl/chset.ipp>
#include <boost/spirit/home/classic/utility/chset_operators.hpp>

/* chset.hpp
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
*/