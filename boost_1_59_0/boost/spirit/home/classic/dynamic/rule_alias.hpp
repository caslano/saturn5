/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_RULE_ALIAS_HPP)
#define BOOST_SPIRIT_RULE_ALIAS_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  rule_alias class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT>
    class rule_alias :
        public parser<rule_alias<ParserT> >
    {
    public:
    
        typedef rule_alias<ParserT> self_t;
    
        template <typename ScannerT>
        struct result 
        { 
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };
    
        rule_alias()
        : ptr(0) {}
        
        rule_alias(ParserT const& p)
        : ptr(&p) {}
        
        rule_alias&
        operator=(ParserT const& p)
        {
            ptr = &p;
            return *this;
        }
    
        template <typename ScannerT>
        typename parser_result<ParserT, ScannerT>::type
        parse(ScannerT const& scan) const
        { 
            if (ptr)
                return ptr->parse(scan);
            else
                return scan.no_match();
        }
        
        ParserT const&
        get() const
        {
            BOOST_ASSERT(ptr != 0);
            return *ptr;
        }
    
    private:
    
        ParserT const* ptr; // hold it by pointer
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* rule_alias.hpp
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
*/