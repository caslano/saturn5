/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SUBRULE_HPP)
#define BOOST_SPIRIT_SUBRULE_HPP

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/non_terminal/parser_context.hpp>

#include <boost/spirit/home/classic/core/non_terminal/subrule_fwd.hpp>
#include <boost/spirit/home/classic/core/non_terminal/impl/subrule.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  subrules_scanner class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScannerT, typename ListT>
    struct subrules_scanner : public ScannerT
    {
        typedef ScannerT                            scanner_t;
        typedef ListT                               list_t;
        typedef subrules_scanner<ScannerT, ListT>   self_t;

        subrules_scanner(ScannerT const& scan, ListT const& list_)
        : ScannerT(scan), list(list_) {}

        template <typename PoliciesT>
        struct rebind_policies
        {
            typedef typename rebind_scanner_policies<ScannerT, PoliciesT>::type
                rebind_scanner;
            typedef subrules_scanner<rebind_scanner, ListT> type;
        };

        template <typename PoliciesT>
        subrules_scanner<
            typename rebind_scanner_policies<ScannerT, PoliciesT>::type,
            ListT>
        change_policies(PoliciesT const& policies) const
        {
            typedef subrules_scanner<
                BOOST_DEDUCED_TYPENAME
                    rebind_scanner_policies<ScannerT, PoliciesT>::type,
                ListT>
            subrules_scanner_t;

            return subrules_scanner_t(
                    ScannerT::change_policies(policies),
                    list);
        }

        template <typename IteratorT>
        struct rebind_iterator
        {
            typedef typename rebind_scanner_iterator<ScannerT, IteratorT>::type
                rebind_scanner;
            typedef subrules_scanner<rebind_scanner, ListT> type;
        };

        template <typename IteratorT>
        subrules_scanner<
            typename rebind_scanner_iterator<ScannerT, IteratorT>::type,
            ListT>
        change_iterator(IteratorT const& first, IteratorT const &last) const
        {
            typedef subrules_scanner<
                BOOST_DEDUCED_TYPENAME
                    rebind_scanner_iterator<ScannerT, IteratorT>::type,
                ListT>
            subrules_scanner_t;

            return subrules_scanner_t(
                    ScannerT::change_iterator(first, last),
                    list);
        }

        ListT const& list;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  subrule_scanner type computer class
    //
    //      This computer ensures that the scanner will not be recursively
    //      instantiated if it's not needed.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScannerT, typename ListT>
    struct subrules_scanner_finder
    {
          typedef subrules_scanner<ScannerT, ListT> type;
    };

    template <typename ScannerT, typename ListT>
    struct subrules_scanner_finder<subrules_scanner<ScannerT, ListT>, ListT>
    {
          typedef subrules_scanner<ScannerT, ListT> type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  subrule_list class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename FirstT, typename RestT>
    struct subrule_list : public parser<subrule_list<FirstT, RestT> >
    {
        typedef subrule_list<FirstT, RestT> self_t;
        typedef FirstT                      first_t;
        typedef RestT                       rest_t;

        subrule_list(FirstT const& first_, RestT const& rest_)
        : first(first_), rest(rest_) {}

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<FirstT, ScannerT>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename subrules_scanner_finder<ScannerT, self_t>::type
            subrules_scanner_t;
            subrules_scanner_t g_arg(scan, *this);
            return first.start.parse(g_arg);
        }

        template <int ID, typename DefT, typename ContextT>
        subrule_list<
            FirstT,
            subrule_list<
                subrule_parser<ID, DefT, ContextT>,
                RestT> >
        operator,(subrule_parser<ID, DefT, ContextT> const& rhs_)
        {
            return subrule_list<
                FirstT,
                subrule_list<
                    subrule_parser<ID, DefT, ContextT>,
                    RestT> >(
                        first,
                        subrule_list<
                            subrule_parser<ID, DefT, ContextT>,
                            RestT>(rhs_, rest));
        }

        FirstT first;
        RestT rest;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  subrule_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <int ID, typename DefT, typename ContextT>
    struct subrule_parser
    : public parser<subrule_parser<ID, DefT, ContextT> >
    {
        typedef subrule_parser<ID, DefT, ContextT> self_t;
        typedef subrule<ID, ContextT> subrule_t;
        typedef DefT def_t;

        BOOST_STATIC_CONSTANT(int, id = ID);

        template <typename ScannerT>
        struct result
        {
            typedef typename
                impl::get_subrule_parser_result<
                    DefT, ScannerT, typename subrule_t::attr_t>::type type;
        };

        subrule_parser(subrule_t const& start_, DefT const& rhs_)
        : rhs(rhs_), start(start_) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            // This will only be called when parsing single subrules.
            typedef subrule_list<self_t, nil_t> list_t;
            typedef subrules_scanner<ScannerT, list_t> scanner_t;

            list_t    list(*this, nil_t());
            scanner_t g_arg(scan, list);
            return start.parse(g_arg);
        }

        template <int ID2, typename DefT2, typename ContextT2>
        inline subrule_list<
            self_t,
            subrule_list<
                subrule_parser<ID2, DefT2, ContextT2>,
                nil_t> >
        operator,(subrule_parser<ID2, DefT2, ContextT2> const& rhs) const
        {
            return subrule_list<
                self_t,
                subrule_list<
                    subrule_parser<ID2, DefT2, ContextT2>,
                    nil_t> >(
                        *this,
                        subrule_list<
                            subrule_parser<ID2, DefT2, ContextT2>, nil_t>(
                                rhs, nil_t()));
        }

        typename DefT::embed_t rhs;
        subrule_t const& start;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  subrule class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <int ID, typename ContextT>
    struct subrule
        : public parser<subrule<ID, ContextT> >
        , public ContextT::base_t
        , public context_aux<ContextT, subrule<ID, ContextT> >
    {
        typedef subrule<ID, ContextT> self_t;
        typedef subrule<ID, ContextT> const&  embed_t;

        typedef typename ContextT::context_linker_t context_t;
        typedef typename context_t::attr_t attr_t;

        BOOST_STATIC_CONSTANT(int, id = ID);

        template <typename ScannerT>
        struct result
        {
            typedef typename
                impl::get_subrule_result<ID, ScannerT, attr_t>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse_main(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t result_;
            impl::parse_subrule<result_t, ScannerT, ID>::
                do_(result_, scan);
            return result_;
        }

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef parser_scanner_linker<ScannerT> scanner_t;
            BOOST_SPIRIT_CONTEXT_PARSE(
                scan, *this, scanner_t, context_t, result_t);
        }

        template <typename DefT>
        subrule_parser<ID, DefT, ContextT>
        operator=(parser<DefT> const& rhs) const
        {
            return subrule_parser<ID, DefT, ContextT>(*this, rhs.derived());
        }

    private:

        //  assignment of subrules is not allowed. Use subrules
        //  with identical IDs if you want to have aliases.

        subrule& operator=(subrule const&);

        template <int ID2, typename ContextT2>
        subrule& operator=(subrule<ID2, ContextT2> const&);
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* subrule.hpp
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
*/