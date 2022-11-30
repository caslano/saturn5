/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_SYMBOLS_HPP
#define BOOST_SPIRIT_SYMBOLS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <string>

#include <boost/ref.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/directives.hpp>

#include <boost/spirit/home/classic/symbols/symbols_fwd.hpp>


///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  symbols class
//
//      This class implements a symbol table. The symbol table holds a
//      dictionary of symbols where each symbol is a sequence of CharTs.
//      The template class can work efficiently with 8, 16 and 32 bit
//      characters. Mutable data of type T is associated with each
//      symbol.
//
//      The class is a parser. The parse member function returns
//      additional information in the symbol_match class (see below).
//      The additional data is a pointer to some data associated with
//      the matching symbol.
//
//      The actual set implementation is supplied by the SetT template
//      parameter. By default, this uses the tst class (see tst.ipp).
//
//      Symbols are added into the symbol table statically using the
//      construct:
//
//          sym = a, b, c, d ...;
//
//      where sym is a symbol table and a..d are strings. Example:
//
//          sym = "pineapple", "orange", "banana", "apple";
//
//      Alternatively, symbols may be added dynamically through the
//      member functor 'add' (see symbol_inserter below). The member
//      functor 'add' may be attached to a parser as a semantic action
//      taking in a begin/end pair:
//
//          p[sym.add]
//
//      where p is a parser (and sym is a symbol table). On success,
//      the matching portion of the input is added to the symbol table.
//
//      'add' may also be used to directly initialize data. Examples:
//
//          sym.add("hello", 1)("crazy", 2)("world", 3);
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename CharT, typename SetT>
class symbols
:   private SetT
,   public parser<symbols<T, CharT, SetT> >
{
public:

    typedef parser<symbols<T, CharT, SetT> > parser_base_t;
    typedef symbols<T, CharT, SetT> self_t;
    typedef self_t const& embed_t;
    typedef T symbol_data_t;
    typedef boost::reference_wrapper<T> symbol_ref_t;

    symbols();
    symbols(symbols const& other);
    ~symbols();

    symbols&
    operator=(symbols const& other);

    symbol_inserter<T, SetT> const&
    operator=(CharT const* str);

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, symbol_ref_t>::type type;
    };

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse_main(ScannerT const& scan) const
    {
        typedef typename ScannerT::iterator_t iterator_t;
        iterator_t first = scan.first;
        typename SetT::search_info result = SetT::find(scan);

        if (result.data)
            return scan.
                create_match(
                    result.length,
                    symbol_ref_t(*result.data),
                    first,
                    scan.first);
        else
            return scan.no_match();
    }

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename parser_result<self_t, ScannerT>::type result_t;
        return impl::implicit_lexeme_parse<result_t>
            (*this, scan, scan);
    }

    template < typename ScannerT >
    T* find(ScannerT const& scan) const
    { return SetT::find(scan).data; }

    symbol_inserter<T, SetT> const add;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Symbol table utilities
//
//  add
//
//      adds a symbol 'sym' (string) to a symbol table 'table' plus an
//      optional data 'data' associated with the symbol. Returns a pointer to
//      the data associated with the symbol or NULL if add failed (e.g. when
//      the symbol is already added before).
//
//  find
//
//      finds a symbol 'sym' (string) from a symbol table 'table'. Returns a
//      pointer to the data associated with the symbol or NULL if not found
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename CharT, typename SetT>
T*  add(symbols<T, CharT, SetT>& table, CharT const* sym, T const& data = T());

template <typename T, typename CharT, typename SetT>
T*  find(symbols<T, CharT, SetT> const& table, CharT const* sym);

///////////////////////////////////////////////////////////////////////////////
//
//  symbol_inserter class
//
//      The symbols class holds an instance of this class named 'add'.
//      This can be called directly just like a member function,
//      passing in a first/last iterator and optional data:
//
//          sym.add(first, last, data);
//
//      Or, passing in a C string and optional data:
//
//          sym.add(c_string, data);
//
//      where sym is a symbol table. The 'data' argument is optional.
//      This may also be used as a semantic action since it conforms
//      to the action interface (see action.hpp):
//
//          p[sym.add]
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename SetT>
class symbol_inserter
{
public:

    symbol_inserter(SetT& set_)
    : set(set_) {}

    typedef symbol_inserter const & result_type;

    template <typename IteratorT>
    symbol_inserter const&
    operator()(IteratorT first, IteratorT const& last, T const& data = T()) const
    {
        set.add(first, last, data);
        return *this;
    }

    template <typename CharT>
    symbol_inserter const&
    operator()(CharT const* str, T const& data = T()) const
    {
        CharT const* last = str;
        while (*last)
            last++;
        set.add(str, last, data);
        return *this;
    }

    template <typename CharT>
    symbol_inserter const&
    operator,(CharT const* str) const
    {
        CharT const* last = str;
        while (*last)
            last++;
        set.add(str, last, T());
        return *this;
    }

private:

    SetT& set;
};

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#include <boost/spirit/home/classic/symbols/impl/symbols.ipp>
#endif

/* symbols.hpp
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
*/