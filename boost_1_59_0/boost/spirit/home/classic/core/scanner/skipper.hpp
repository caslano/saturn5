/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SKIPPER_HPP)
#define BOOST_SPIRIT_SKIPPER_HPP

///////////////////////////////////////////////////////////////////////////////
#include <cctype>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/scanner/scanner.hpp>
#include <boost/spirit/home/classic/core/primitives/impl/primitives.ipp>

#include <boost/spirit/home/classic/core/scanner/skipper_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  skipper_iteration_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BaseT>
    struct skipper_iteration_policy : public BaseT
    {
        typedef BaseT base_t;
    
        skipper_iteration_policy()
        : BaseT() {}
    
        template <typename PolicyT>
        skipper_iteration_policy(PolicyT const& other)
        : BaseT(other) {}
    
        template <typename ScannerT>
        void
        advance(ScannerT const& scan) const
        {
            BaseT::advance(scan);
            scan.skip(scan);
        }
    
        template <typename ScannerT>
        bool
        at_end(ScannerT const& scan) const
        {
            scan.skip(scan);
            return BaseT::at_end(scan);
        }
    
        template <typename ScannerT>
        void
        skip(ScannerT const& scan) const
        {
            while (!BaseT::at_end(scan) && impl::isspace_(BaseT::get(scan)))
                BaseT::advance(scan);
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  no_skipper_iteration_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BaseT>
    struct no_skipper_iteration_policy : public BaseT
    {
        typedef BaseT base_t;

        no_skipper_iteration_policy()
        : BaseT() {}

        template <typename PolicyT>
        no_skipper_iteration_policy(PolicyT const& other)
        : BaseT(other) {}

        template <typename ScannerT>
        void
        skip(ScannerT const& /*scan*/) const {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  skip_parser_iteration_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    namespace impl
    {
        template <typename ST, typename ScannerT, typename BaseT>
        void
        skipper_skip(
            ST const& s,
            ScannerT const& scan,
            skipper_iteration_policy<BaseT> const&);

        template <typename ST, typename ScannerT, typename BaseT>
        void
        skipper_skip(
            ST const& s,
            ScannerT const& scan,
            no_skipper_iteration_policy<BaseT> const&);

        template <typename ST, typename ScannerT>
        void
        skipper_skip(
            ST const& s,
            ScannerT const& scan,
            iteration_policy const&);
    }

    template <typename ParserT, typename BaseT>
    class skip_parser_iteration_policy : public skipper_iteration_policy<BaseT>
    {
    public:
    
        typedef skipper_iteration_policy<BaseT> base_t;
    
        skip_parser_iteration_policy(
            ParserT const& skip_parser,
            base_t const& base = base_t())
        : base_t(base), subject(skip_parser) {}
    
        template <typename PolicyT>
        skip_parser_iteration_policy(PolicyT const& other)
        : base_t(other), subject(other.skipper()) {}
    
        template <typename ScannerT>
        void
        skip(ScannerT const& scan) const
        {
            impl::skipper_skip(subject, scan, scan);
        }
    
        ParserT const&
        skipper() const
        { 
            return subject; 
        }
    
    private:
    
        ParserT const& subject;
    };
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  Free parse functions using the skippers
    //
    ///////////////////////////////////////////////////////////////////////////////
    template <typename IteratorT, typename ParserT, typename SkipT>
    parse_info<IteratorT>
    parse(
        IteratorT const&        first,
        IteratorT const&        last,
        parser<ParserT> const&  p,
        parser<SkipT> const&    skip);
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  Parse function for null terminated strings using the skippers
    //
    ///////////////////////////////////////////////////////////////////////////////
    template <typename CharT, typename ParserT, typename SkipT>
    parse_info<CharT const*>
    parse(
        CharT const*            str,
        parser<ParserT> const&  p,
        parser<SkipT> const&    skip);
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  phrase_scanner_t and wide_phrase_scanner_t
    //
    //      The most common scanners. Use these typedefs when you need
    //      a scanner that skips white spaces.
    //
    ///////////////////////////////////////////////////////////////////////////////
    typedef skipper_iteration_policy<>                  iter_policy_t;
    typedef scanner_policies<iter_policy_t>             scanner_policies_t;
    typedef scanner<char const*, scanner_policies_t>    phrase_scanner_t;
    typedef scanner<wchar_t const*, scanner_policies_t> wide_phrase_scanner_t;
    
    ///////////////////////////////////////////////////////////////////////////////

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#include <boost/spirit/home/classic/core/scanner/impl/skipper.ipp>
#endif


/* skipper.hpp
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
*/