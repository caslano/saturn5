/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTIONS_HPP
#define BOOST_SPIRIT_ACTIONS_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  action class
    //
    //      The action class binds a parser with a user defined semantic
    //      action. Instances of action are never created manually. Instead,
    //      action objects are typically created indirectly through
    //      expression templates of the form:
    //
    //          p[f]
    //
    //      where p is a parser and f is a function or functor. The semantic
    //      action may be a function or a functor. When the parser is
    //      successful, the actor calls the scanner's action_policy policy
    //      (see scanner.hpp):
    //
    //          scan.do_action(actor, attribute, first, last);
    //
    //      passing in these information:
    //
    //          actor:        The action's function or functor
    //          attribute:    The match (returned by the parser) object's
    //                        attribute (see match.hpp)
    //          first:        Iterator pointing to the start of the matching
    //                        portion of the input
    //          last:         Iterator pointing to one past the end of the
    //                        matching portion of the input
    //
    //      It is the responsibility of the scanner's action_policy policy to
    //      dispatch the function or functor as it sees fit. The expected
    //      function or functor signature depends on the parser being
    //      wrapped. In general, if the attribute type of the parser being
    //      wrapped is a nil_t, the function or functor expect the signature:
    //
    //          void func(Iterator first, Iterator last); // functions
    //
    //          struct ftor // functors
    //          {
    //              void func(Iterator first, Iterator last) const;
    //          };
    //
    //      where Iterator is the type of the iterator that is being used and
    //      first and last are the iterators pointing to the matching portion
    //      of the input.
    //
    //      If the attribute type of the parser being wrapped is not a nil_t,
    //      the function or functor usually expect the signature:
    //
    //          void func(T val); // functions
    //
    //          struct ftor // functors
    //          {
    //              void func(T val) const;
    //          };
    //
    //      where T is the attribute type and val is the attribute value
    //      returned by the parser being wrapped.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT, typename ActionT>
    class action : public unary<ParserT, parser<action<ParserT, ActionT> > >
    {
    public:

        typedef action<ParserT, ActionT>        self_t;
        typedef action_parser_category          parser_category_t;
        typedef unary<ParserT, parser<self_t> > base_t;
        typedef ActionT                         predicate_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        action(ParserT const& p, ActionT const& a)
        : base_t(p)
        , actor(a) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            typedef typename parser_result<self_t, ScannerT>::type result_t;

            ignore_unused(scan.at_end()); // allow skipper to take effect
            iterator_t save = scan.first;
            result_t hit = this->subject().parse(scan);
            if (hit)
            {
                typename result_t::return_t val = hit.value();
                scan.do_action(actor, val, save, scan.first);
            }
            return hit;
        }

        ActionT const& predicate() const { return actor; }

    private:

        ActionT actor;
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* actions.hpp
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
*/