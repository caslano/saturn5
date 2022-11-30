/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    Copyright (c) 2003 Gustavo Guerra
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DEBUG_NODE_HPP)
#define BOOST_SPIRIT_DEBUG_NODE_HPP

#if !defined(BOOST_SPIRIT_DEBUG_MAIN_HPP)
#error "You must include boost/spirit/debug.hpp, not boost/spirit/debug/debug_node.hpp"
#endif

#if defined(BOOST_SPIRIT_DEBUG)

#include <string>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp> // for iscntrl_

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  Debug helper classes for rules, which ensure maximum non-intrusiveness of
//  the Spirit debug support
//
///////////////////////////////////////////////////////////////////////////////

namespace impl {

    struct token_printer_aux_for_chars
    {
        template<typename CharT>
        static void print(std::ostream& o, CharT c)
        {
            if (c == static_cast<CharT>('\a'))
                o << "\\a";

            else if (c == static_cast<CharT>('\b'))
                o << "\\b";

            else if (c == static_cast<CharT>('\f'))
                o << "\\f";

            else if (c == static_cast<CharT>('\n'))
                o << "\\n";

            else if (c == static_cast<CharT>('\r'))
                o << "\\r";

            else if (c == static_cast<CharT>('\t'))
                o << "\\t";

            else if (c == static_cast<CharT>('\v'))
                o << "\\v";

            else if (iscntrl_(c))
                o << "\\" << static_cast<int>(c);

            else
                o << static_cast<char>(c);
        }
    };

    // for token types where the comparison with char constants wouldn't work
    struct token_printer_aux_for_other_types
    {
        template<typename CharT>
        static void print(std::ostream& o, CharT c)
        {
            o << c;
        }
    };

    template <typename CharT>
    struct token_printer_aux
    :   mpl::if_<
            mpl::and_<
                is_convertible<CharT, char>,
                is_convertible<char, CharT> >,
            token_printer_aux_for_chars,
            token_printer_aux_for_other_types
        >::type
    {
    };

    template<typename CharT>
    inline void token_printer(std::ostream& o, CharT c)
    {
    #if !defined(BOOST_SPIRIT_DEBUG_TOKEN_PRINTER)

        token_printer_aux<CharT>::print(o, c);

    #else

        BOOST_SPIRIT_DEBUG_TOKEN_PRINTER(o, c);

    #endif
    }

///////////////////////////////////////////////////////////////////////////////
//
//  Dump infos about the parsing state of a rule
//
///////////////////////////////////////////////////////////////////////////////

#if BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES
    template <typename IteratorT>
    inline void
    print_node_info(bool hit, int level, bool close, std::string const& name,
        IteratorT first, IteratorT last)
    {
        if (!name.empty())
        {
            for (int i = 0; i < level; ++i)
                BOOST_SPIRIT_DEBUG_OUT << "  ";
            if (close)
            {
                if (hit)
                    BOOST_SPIRIT_DEBUG_OUT << "/";
                else
                    BOOST_SPIRIT_DEBUG_OUT << "#";
            }
            BOOST_SPIRIT_DEBUG_OUT << name << ":\t\"";
            IteratorT iter = first;
            IteratorT ilast = last;
            for (int j = 0; j < BOOST_SPIRIT_DEBUG_PRINT_SOME; ++j)
            {
                if (iter == ilast)
                    break;

                token_printer(BOOST_SPIRIT_DEBUG_OUT, *iter);
                ++iter;
            }
            BOOST_SPIRIT_DEBUG_OUT << "\"\n";
        }
    }
#endif  // BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES

#if BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES
    template <typename ResultT>
    inline ResultT &
    print_closure_info(ResultT &hit, int level, std::string const& name)
    {
        if (!name.empty())
        {
            for (int i = 0; i < level-1; ++i)
                BOOST_SPIRIT_DEBUG_OUT << "  ";

        // for now, print out the return value only
            BOOST_SPIRIT_DEBUG_OUT << "^" << name << ":\t";
            if (hit.has_valid_attribute())
                BOOST_SPIRIT_DEBUG_OUT << hit.value();
            else
                BOOST_SPIRIT_DEBUG_OUT << "undefined attribute";
            BOOST_SPIRIT_DEBUG_OUT << "\n";
        }
        return hit;
    }
#endif // BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES

}

///////////////////////////////////////////////////////////////////////////////
//
//  Implementation note: The parser_context_linker, parser_scanner_linker and
//  closure_context_linker classes are wrapped by a PP constant to allow
//  redefinition of this classes outside of Spirit
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED)
#define BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_context_linker is a debug wrapper for the ContextT template
    //  parameter of the rule<>, subrule<> and the grammar<> classes
    //
    ///////////////////////////////////////////////////////////////////////////
    template<typename ContextT>
    struct parser_context_linker : public ContextT
    {
        typedef ContextT base_t;

        template <typename ParserT>
        parser_context_linker(ParserT const& p)
        : ContextT(p) {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const& p, ScannerT &scan)
        {
            this->base_t::pre_parse(p, scan);

#if BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES
            if (trace_parser(p.derived())) {
                impl::print_node_info(
                    false,
                    scan.get_level(),
                    false,
                    parser_name(p.derived()),
                    scan.first,
                    scan.last);
            }
            scan.get_level()++;
#endif  // BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES
        }

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT& post_parse(ResultT& hit, ParserT const& p, ScannerT &scan)
        {
#if BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES
            --scan.get_level();
            if (trace_parser(p.derived())) {
                impl::print_node_info(
                    hit,
                    scan.get_level(),
                    true,
                    parser_name(p.derived()),
                    scan.first,
                    scan.last);
            }
#endif  // BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES

            return this->base_t::post_parse(hit, p, scan);
        }
    };

#endif // !defined(BOOST_SPIRIT_PARSER_CONTEXT_LINKER_DEFINED)

#if !defined(BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED)
#define BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED

///////////////////////////////////////////////////////////////////////////////
//  This class is to avoid linker problems and to ensure a real singleton
//  'level' variable
    struct debug_support
    {
        int& get_level()
        {
            static int level = 0;
            return level;
        }
    };

    template<typename ScannerT>
    struct parser_scanner_linker : public ScannerT
    {
        parser_scanner_linker(ScannerT const &scan_) : ScannerT(scan_)
        {}

        int &get_level()
        { return debug.get_level(); }

        private: debug_support debug;
    };

#endif // !defined(BOOST_SPIRIT_PARSER_SCANNER_LINKER_DEFINED)

#if !defined(BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED)
#define BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED

    ///////////////////////////////////////////////////////////////////////////
    //
    //  closure_context_linker is a debug wrapper for the closure template
    //  parameter of the rule<>, subrule<> and grammar classes
    //
    ///////////////////////////////////////////////////////////////////////////

    template<typename ContextT>
    struct closure_context_linker : public parser_context_linker<ContextT>
    {
        typedef parser_context_linker<ContextT> base_t;

        template <typename ParserT>
        closure_context_linker(ParserT const& p)
        : parser_context_linker<ContextT>(p) {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const& p, ScannerT &scan)
        { this->base_t::pre_parse(p, scan); }

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT&
        post_parse(ResultT& hit, ParserT const& p, ScannerT &scan)
        {
#if BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES
            if (hit && trace_parser(p.derived())) {
            // for now, print out the return value only
                return impl::print_closure_info(
                    this->base_t::post_parse(hit, p, scan),
                    scan.get_level(),
                    parser_name(p.derived())
                );
            }
#endif // BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES

            return this->base_t::post_parse(hit, p, scan);
        }
    };

#endif // !defined(BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED)

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // defined(BOOST_SPIRIT_DEBUG)

#endif // !defined(BOOST_SPIRIT_DEBUG_NODE_HPP)


/* debug_node.hpp
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
*/