/*=============================================================================
    Copyright (c) 1998-2002 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SCANNER_HPP)
#define BOOST_SPIRIT_SCANNER_HPP

#include <iterator>
#include <boost/config.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/match.hpp>
#include <boost/spirit/home/classic/core/non_terminal/parser_id.hpp>

#include <boost/spirit/home/classic/core/scanner/scanner_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  iteration_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct iteration_policy
    {
        template <typename ScannerT>
        void
        advance(ScannerT const& scan) const
        {
            ++scan.first;
        }

        template <typename ScannerT>
        bool at_end(ScannerT const& scan) const
        {
            return scan.first == scan.last;
        }

        template <typename T>
        T filter(T ch) const
        {
            return ch;
        }

        template <typename ScannerT>
        typename ScannerT::ref_t
        get(ScannerT const& scan) const
        {
            return *scan.first;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  match_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct match_policy
    {
        template <typename T>
        struct result { typedef match<T> type; };

        const match<nil_t>
        no_match() const
        {
            return match<nil_t>();
        }

        const match<nil_t>
        empty_match() const
        {
            return match<nil_t>(0, nil_t());
        }

        template <typename AttrT, typename IteratorT>
        match<AttrT>
        create_match(
            std::size_t         length,
            AttrT const&        val,
            IteratorT const&    /*first*/,
            IteratorT const&    /*last*/) const
        {
            return match<AttrT>(length, val);
        }

        template <typename MatchT, typename IteratorT>
        void group_match(
            MatchT&             /*m*/,
            parser_id const&    /*id*/,
            IteratorT const&    /*first*/,
            IteratorT const&    /*last*/) const {}

        template <typename Match1T, typename Match2T>
        void concat_match(Match1T& l, Match2T const& r) const
        {
            l.concat(r);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  match_result class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename MatchPolicyT, typename T>
    struct match_result
    {
        typedef typename MatchPolicyT::template result<T>::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  action_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename AttrT>
    struct attributed_action_policy
    {
        template <typename ActorT, typename IteratorT>
        static void
        call(
            ActorT const& actor,
            AttrT& val,
            IteratorT const&,
            IteratorT const&)
        {
            actor(val);
        }
    };

    //////////////////////////////////
    template <>
    struct attributed_action_policy<nil_t>
    {
        template <typename ActorT, typename IteratorT>
        static void
        call(
            ActorT const& actor,
            nil_t,
            IteratorT const& first,
            IteratorT const& last)
        {
            actor(first, last);
        }
    };

    //////////////////////////////////
    struct action_policy
    {
        template <typename ActorT, typename AttrT, typename IteratorT>
        void
        do_action(
            ActorT const&       actor,
            AttrT&              val,
            IteratorT const&    first,
            IteratorT const&    last) const
        {
            attributed_action_policy<AttrT>::call(actor, val, first, last);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner_policies class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IterationPolicyT,
        typename MatchPolicyT,
        typename ActionPolicyT>
    struct scanner_policies :
        public IterationPolicyT,
        public MatchPolicyT,
        public ActionPolicyT
    {
        typedef IterationPolicyT    iteration_policy_t;
        typedef MatchPolicyT        match_policy_t;
        typedef ActionPolicyT       action_policy_t;

        scanner_policies(
            IterationPolicyT const& i_policy = IterationPolicyT(),
            MatchPolicyT const&     m_policy = MatchPolicyT(),
            ActionPolicyT const&    a_policy = ActionPolicyT())
        : IterationPolicyT(i_policy)
        , MatchPolicyT(m_policy)
        , ActionPolicyT(a_policy) {}

        template <typename ScannerPoliciesT>
        scanner_policies(ScannerPoliciesT const& policies)
        : IterationPolicyT(policies)
        , MatchPolicyT(policies)
        , ActionPolicyT(policies) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner_policies_base class: the base class of all scanners
    //
    ///////////////////////////////////////////////////////////////////////////
    struct scanner_base {};

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IteratorT,
        typename PoliciesT>
    class scanner : public PoliciesT, public scanner_base
    {
    public:

        typedef IteratorT iterator_t;
        typedef PoliciesT policies_t;

        typedef typename std::
            iterator_traits<IteratorT>::value_type value_t;
        typedef typename std::
            iterator_traits<IteratorT>::reference ref_t;
        typedef typename boost::
            call_traits<IteratorT>::param_type iter_param_t;

        scanner(
            IteratorT&          first_,
            iter_param_t        last_,
            PoliciesT const&    policies = PoliciesT())
        : PoliciesT(policies), first(first_), last(last_)
        {
            at_end();
        }

        scanner(scanner const& other)
        : PoliciesT(other), first(other.first), last(other.last) {}

        scanner(scanner const& other, IteratorT& first_)
        : PoliciesT(other), first(first_), last(other.last) {}

        template <typename PoliciesT1>
        scanner(scanner<IteratorT, PoliciesT1> const& other)
        : PoliciesT(other), first(other.first), last(other.last) {}

        bool
        at_end() const
        {
            typedef typename PoliciesT::iteration_policy_t iteration_policy_type;
            return iteration_policy_type::at_end(*this);
        }

        value_t
        operator*() const
        {
            typedef typename PoliciesT::iteration_policy_t iteration_policy_type;
            return iteration_policy_type::filter(iteration_policy_type::get(*this));
        }

        scanner const&
        operator++() const
        {
            typedef typename PoliciesT::iteration_policy_t iteration_policy_type;
            iteration_policy_type::advance(*this);
            return *this;
        }

        template <typename PoliciesT2>
        struct rebind_policies
        {
            typedef scanner<IteratorT, PoliciesT2> type;
        };

        template <typename PoliciesT2>
        scanner<IteratorT, PoliciesT2>
        change_policies(PoliciesT2 const& policies) const
        {
            return scanner<IteratorT, PoliciesT2>(first, last, policies);
        }

        template <typename IteratorT2>
        struct rebind_iterator
        {
            typedef scanner<IteratorT2, PoliciesT> type;
        };

        template <typename IteratorT2>
        scanner<IteratorT2, PoliciesT>
        change_iterator(IteratorT2 const& first_, IteratorT2 const &last_) const
        {
            return scanner<IteratorT2, PoliciesT>(first_, last_, *this);
        }

        IteratorT& first;
        IteratorT const last;

    private:

        scanner&
        operator=(scanner const& other);
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  rebind_scanner_policies class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScannerT, typename PoliciesT>
    struct rebind_scanner_policies
    {
        typedef typename ScannerT::template
            rebind_policies<PoliciesT>::type type;
    };

    //////////////////////////////////
    template <typename ScannerT, typename IteratorT>
    struct rebind_scanner_iterator
    {
        typedef typename ScannerT::template
            rebind_iterator<IteratorT>::type type;
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* scanner.hpp
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
*/