/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_EXCEPTIONS_HPP
#define BOOST_SPIRIT_EXCEPTIONS_HPP

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <exception>

#include <boost/spirit/home/classic/error_handling/exceptions_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_error_base class
    //
    //      This is the base class of parser_error (see below). This may be
    //      used to catch any type of parser error.
    //
    //      This exception shouldn't propagate outside the parser. However to
    //      avoid quirks of many platforms/implementations which fall outside
    //      the C++ standard, we derive parser_error_base from std::exception
    //      to allow a single catch handler to catch all exceptions.
    //
    ///////////////////////////////////////////////////////////////////////////
    class BOOST_SYMBOL_VISIBLE parser_error_base : public std::exception
    {
    protected:

        parser_error_base() {}
        virtual ~parser_error_base() BOOST_NOEXCEPT_OR_NOTHROW {}

    public:

        parser_error_base(parser_error_base const& rhs)
            : std::exception(rhs) {}
        parser_error_base& operator=(parser_error_base const&)
        {
            return *this;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_error class
    //
    //      Generic parser exception class. This is the base class for all
    //      parser exceptions. The exception holds the iterator position
    //      where the error was encountered in its member variable "where".
    //      The parser_error also holds information regarding the error
    //      (error descriptor) in its member variable "descriptor".
    //
    //      The throw_ function creates and throws a parser_error given
    //      an iterator and an error descriptor.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ErrorDescrT, typename IteratorT>
    struct parser_error : public parser_error_base
    {
        typedef ErrorDescrT error_descr_t;
        typedef IteratorT iterator_t;

        parser_error(IteratorT where_, ErrorDescrT descriptor_)
        : where(where_), descriptor(descriptor_) {}

        parser_error(parser_error const& rhs)
        : parser_error_base(rhs)
        , where(rhs.where), descriptor(rhs.descriptor) {}

        parser_error&
        operator=(parser_error const& rhs)
        {
            where = rhs.where;
            descriptor = rhs.descriptor;
            return *this;
        }

        virtual
        ~parser_error() BOOST_NOEXCEPT_OR_NOTHROW {}

        virtual const char*
        what() const BOOST_NOEXCEPT_OR_NOTHROW
        {
            return "BOOST_SPIRIT_CLASSIC_NS::parser_error";
        }

        IteratorT where;
        ErrorDescrT descriptor;
    };

    //////////////////////////////////
    template <typename ErrorDescrT, typename IteratorT>
    inline void
    throw_(IteratorT where, ErrorDescrT descriptor)
    {
         boost::throw_exception(
            parser_error<ErrorDescrT, IteratorT>(where, descriptor));
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  assertive_parser class
    //
    //      An assertive_parser class is a parser that throws an exception
    //      in response to a parsing failure. The assertive_parser throws a
    //      parser_error exception rather than returning an unsuccessful
    //      match to signal that the parser failed to match the input.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ErrorDescrT, typename ParserT>
    struct assertive_parser
    :   public unary<ParserT, parser<assertive_parser<ErrorDescrT, ParserT> > >
    {
        typedef assertive_parser<ErrorDescrT, ParserT>  self_t;
        typedef unary<ParserT, parser<self_t> >         base_t;
        typedef unary_parser_category                   parser_category_t;

        assertive_parser(ParserT const& parser, ErrorDescrT descriptor_)
        : base_t(parser), descriptor(descriptor_) {}

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<ParserT, ScannerT>::type result_t;

            result_t hit = this->subject().parse(scan);
            if (!hit)
            {
                throw_(scan.first, descriptor);
            }
            return hit;
        }

        ErrorDescrT descriptor;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  assertion class
    //
    //      assertive_parsers are never instantiated directly. The assertion
    //      class is used to indirectly create an assertive_parser object.
    //      Before declaring the grammar, we declare some assertion objects.
    //      Examples:
    //
    //          enum Errors
    //          {
    //              program_expected, begin_expected, end_expected
    //          };
    //
    //          assertion<Errors>   expect_program(program_expected);
    //          assertion<Errors>   expect_begin(begin_expected);
    //          assertion<Errors>   expect_end(end_expected);
    //
    //      Now, we can use these assertions as wrappers around parsers:
    //
    //          expect_end(str_p("end"))
    //
    //      Take note that although the example uses enums to hold the
    //      information regarding the error (error desccriptor), we are free
    //      to use other types such as integers and strings. Enums are
    //      convenient for error handlers to easily catch since C++ treats
    //      enums as unique types.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ErrorDescrT>
    struct assertion
    {
        assertion(ErrorDescrT descriptor_)
        : descriptor(descriptor_) {}

        template <typename ParserT>
        assertive_parser<ErrorDescrT, ParserT>
        operator()(ParserT const& parser) const
        {
            return assertive_parser<ErrorDescrT, ParserT>(parser, descriptor);
        }

        ErrorDescrT descriptor;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  error_status<T>
    //
    //      Where T is an attribute type compatible with the match attribute
    //      of the fallback_parser's subject (defaults to nil_t). The class
    //      error_status reports the result of an error handler (see
    //      fallback_parser). result can be one of:
    //
    //          fail:       quit and fail (return a no_match)
    //          retry:      attempt error recovery, possibly moving the scanner
    //          accept:     force success returning a matching length, moving
    //                      the scanner appropriately and returning an attribute
    //                      value
    //          rethrow:    rethrows the error.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct error_status
    {
        enum result_t { fail, retry, accept, rethrow };

        error_status(
            result_t result_ = fail,
            std::ptrdiff_t length_ = -1,
            T const& value_ = T())
        : result(result_), length(length_), value(value_) {}

        result_t        result;
        std::ptrdiff_t  length;
        T               value;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  fallback_parser class
    //
    //      Handles exceptions of type parser_error<ErrorDescrT, IteratorT>
    //      thrown somewhere inside its embedded ParserT object. The class
    //      sets up a try block before delegating parsing to its subject.
    //      When an exception is caught, the catch block then calls the
    //      HandlerT object. HandlerT may be a function or a functor (with
    //      an operator() member function) compatible with the interface:
    //
    //          error_status<T>
    //          handler(ScannerT const& scan, ErrorT error);
    //
    //      Where scan points to the scanner state prior to parsing and error
    //      is the error that arose (see parser_error). The handler must
    //      return an error_status<T> object (see above).
    //
    ///////////////////////////////////////////////////////////////////////////
    namespace impl
    {
        template <typename RT, typename ParserT, typename ScannerT>
        RT fallback_parser_parse(ParserT const& p, ScannerT const& scan);
    }

    template <typename ErrorDescrT, typename ParserT, typename HandlerT>
    struct fallback_parser
    :   public unary<ParserT,
        parser<fallback_parser<ErrorDescrT, ParserT, HandlerT> > >
    {
        typedef fallback_parser<ErrorDescrT, ParserT, HandlerT>
            self_t;
        typedef ErrorDescrT
            error_descr_t;
        typedef unary<ParserT, parser<self_t> >
            base_t;
        typedef unary_parser_category
            parser_category_t;

        fallback_parser(ParserT const& parser, HandlerT const& handler_)
        : base_t(parser), handler(handler_) {}

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::fallback_parser_parse<result_t>(*this, scan);
        }

        HandlerT handler;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  guard class
    //
    //      fallback_parser objects are not instantiated directly. The guard
    //      class is used to indirectly create a fallback_parser object.
    //      guards are typically predeclared just like assertions (see the
    //      assertion class above; the example extends the previous example
    //      introduced in the assertion class above):
    //
    //          guard<Errors>   my_guard;
    //
    //      Errors, in this example is the error descriptor type we want to
    //      detect; This is essentially the ErrorDescrT template parameter
    //      of the fallback_parser class.
    //
    //      my_guard may now be used in a grammar declaration as:
    //
    //          my_guard(p)[h]
    //
    //      where p is a parser, h is a function or functor compatible with
    //      fallback_parser's HandlerT (see above).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ErrorDescrT, typename ParserT>
    struct guard_gen : public unary<ParserT, nil_t>
    {
        typedef guard<ErrorDescrT>      parser_generator_t;
        typedef unary_parser_category   parser_category_t;

        guard_gen(ParserT const& p)
        : unary<ParserT, nil_t>(p) {}

        template <typename HandlerT>
        fallback_parser<ErrorDescrT, ParserT, HandlerT>
        operator[](HandlerT const& handler) const
        {
            return fallback_parser<ErrorDescrT, ParserT, HandlerT>
                (this->subject(), handler);
        }
    };

    template <typename ErrorDescrT>
    struct guard
    {
        template <typename ParserT>
        struct result
        {
            typedef guard_gen<ErrorDescrT, ParserT> type;
        };

        template <typename ParserT>
        static guard_gen<ErrorDescrT, ParserT>
        generate(ParserT const& parser)
        {
            return guard_gen<ErrorDescrT, ParserT>(parser);
        }

        template <typename ParserT>
        guard_gen<ErrorDescrT, ParserT>
        operator()(ParserT const& parser) const
        {
            return guard_gen<ErrorDescrT, ParserT>(parser);
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#include <boost/spirit/home/classic/error_handling/impl/exceptions.ipp>
#endif


/* exceptions.hpp
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
*/