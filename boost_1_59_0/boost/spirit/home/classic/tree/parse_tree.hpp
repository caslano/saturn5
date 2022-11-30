/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2007 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_TREE_PARSE_TREE_HPP
#define BOOST_SPIRIT_TREE_PARSE_TREE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/tree/common.hpp>
#include <boost/spirit/home/classic/core/scanner/scanner.hpp>

#include <boost/spirit/home/classic/tree/parse_tree_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

//////////////////////////////////
// pt_match_policy is simply an id so the correct specialization of tree_policy can be found.
template <
    typename IteratorT,
    typename NodeFactoryT,
    typename T 
>
struct pt_match_policy :
    public common_tree_match_policy<
        pt_match_policy<IteratorT, NodeFactoryT, T>,
        IteratorT,
        NodeFactoryT,
        pt_tree_policy<
            pt_match_policy<IteratorT, NodeFactoryT, T>,
            NodeFactoryT,
            T
        >,
        T
    >
{
    typedef
        common_tree_match_policy<
            pt_match_policy<IteratorT, NodeFactoryT, T>,
            IteratorT,
            NodeFactoryT,
            pt_tree_policy<
                pt_match_policy<IteratorT, NodeFactoryT, T>,
                NodeFactoryT,
                T
            >,
            T
        >
    common_tree_match_policy_;

    pt_match_policy()
    {
    }

    template <typename PolicyT>
    pt_match_policy(PolicyT const & policies)
        : common_tree_match_policy_(policies)
    {
    }
};

//////////////////////////////////
template <typename MatchPolicyT, typename NodeFactoryT, typename T>
struct pt_tree_policy :
    public common_tree_tree_policy<MatchPolicyT, NodeFactoryT>
{
    typedef typename MatchPolicyT::match_t match_t;
    typedef typename MatchPolicyT::iterator_t iterator_t;

    template<typename MatchAT, typename MatchBT>
    static void concat(MatchAT& a, MatchBT const& b)
    {
        BOOST_SPIRIT_ASSERT(a && b);

        std::copy(b.trees.begin(), b.trees.end(),
            std::back_insert_iterator<typename match_t::container_t>(a.trees));
    }

    template <typename MatchT, typename Iterator1T, typename Iterator2T>
    static void group_match(MatchT& m, parser_id const& id,
            Iterator1T const& first, Iterator2T const& last)
    {
        if (!m)
            return;

        typedef typename NodeFactoryT::template factory<iterator_t> factory_t;
        typedef typename tree_match<iterator_t, NodeFactoryT, T>::container_t
            container_t;
        typedef typename container_t::iterator cont_iterator_t;

        match_t newmatch(m.length(),
                factory_t::create_node(first, last, false));

        std::swap(newmatch.trees.begin()->children, m.trees);
        // set this node and all it's unset children's rule_id
        newmatch.trees.begin()->value.id(id);
        for (cont_iterator_t i = newmatch.trees.begin()->children.begin();
                i != newmatch.trees.begin()->children.end();
                ++i)
        {
            if (i->value.id() == 0)
                i->value.id(id);
        }
        m = newmatch;
    }

    template <typename FunctorT, typename MatchT>
    static void apply_op_to_match(FunctorT const& op, MatchT& m)
    {
        op(m);
    }
};

namespace impl {

    template <typename IteratorT, typename NodeFactoryT, typename T>
    struct tree_policy_selector<pt_match_policy<IteratorT, NodeFactoryT, T> >
    {
        typedef pt_tree_policy<
            pt_match_policy<IteratorT, NodeFactoryT, T>, 
            NodeFactoryT, 
            T
        > type;
    };

} // namespace impl


//////////////////////////////////
struct gen_pt_node_parser_gen;

template <typename T>
struct gen_pt_node_parser
:   public unary<T, parser<gen_pt_node_parser<T> > >
{
    typedef gen_pt_node_parser<T> self_t;
    typedef gen_pt_node_parser_gen parser_generator_t;
    typedef unary_parser_category parser_category_t;

    gen_pt_node_parser(T const& a)
    : unary<T, parser<gen_pt_node_parser<T> > >(a) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename ScannerT::iteration_policy_t iteration_policy_t;
        typedef typename ScannerT::match_policy_t::iterator_t iterator_t;
        typedef typename ScannerT::match_policy_t::factory_t factory_t;
        typedef pt_match_policy<iterator_t, factory_t> match_policy_t;
        typedef typename ScannerT::action_policy_t action_policy_t;
        typedef scanner_policies<
            iteration_policy_t,
            match_policy_t,
            action_policy_t
        > policies_t;

        return this->subject().parse(scan.change_policies(policies_t(scan)));
    }
};

//////////////////////////////////
struct gen_pt_node_parser_gen
{
    template <typename T>
    struct result {

        typedef gen_pt_node_parser<T> type;
    };

    template <typename T>
    static gen_pt_node_parser<T>
    generate(parser<T> const& s)
    {
        return gen_pt_node_parser<T>(s.derived());
    }

    template <typename T>
    gen_pt_node_parser<T>
    operator[](parser<T> const& s) const
    {
        return gen_pt_node_parser<T>(s.derived());
    }
};

//////////////////////////////////
const gen_pt_node_parser_gen gen_pt_node_d = gen_pt_node_parser_gen();


///////////////////////////////////////////////////////////////////////////////
//
//  Parse functions for parse trees
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename NodeFactoryT, typename IteratorT, typename ParserT, 
    typename SkipT
>
inline tree_parse_info<IteratorT, NodeFactoryT>
pt_parse(
    IteratorT const&        first_,
    IteratorT const&        last,
    parser<ParserT> const&  p,
    SkipT const&            skip,
    NodeFactoryT const&   /*dummy_*/ = NodeFactoryT())
{
    typedef skip_parser_iteration_policy<SkipT> it_policy_t;
    typedef pt_match_policy<IteratorT, NodeFactoryT> pt_match_policy_t;
    typedef
        scanner_policies<it_policy_t, pt_match_policy_t>
        scan_policies_t;
    typedef scanner<IteratorT, scan_policies_t> scanner_t;

    it_policy_t iter_policy(skip);
    scan_policies_t policies(iter_policy);
    IteratorT first = first_;
    scanner_t scan(first, last, policies);
    tree_match<IteratorT, NodeFactoryT> hit = p.derived().parse(scan);
    return tree_parse_info<IteratorT, NodeFactoryT>(
        first, hit, hit && (first == last), hit.length(), hit.trees);
}

template <typename IteratorT, typename ParserT, typename SkipT>
inline tree_parse_info<IteratorT>
pt_parse(
    IteratorT const&        first,
    IteratorT const&        last,
    parser<ParserT> const&  p,
    SkipT const&            skip)
{
    typedef node_val_data_factory<nil_t> default_node_factory_t;
    return pt_parse(first, last, p, skip, default_node_factory_t());
}

//////////////////////////////////
template <typename IteratorT, typename ParserT>
inline tree_parse_info<IteratorT>
pt_parse(
    IteratorT const&        first_,
    IteratorT const&        last,
    parser<ParserT> const&  parser)
{
    typedef pt_match_policy<IteratorT> pt_match_policy_t;
    IteratorT first = first_;
    scanner<
        IteratorT,
        scanner_policies<iteration_policy, pt_match_policy_t>
    > scan(first, last);
    tree_match<IteratorT> hit = parser.derived().parse(scan);
    return tree_parse_info<IteratorT>(
        first, hit, hit && (first == last), hit.length(), hit.trees);
}

//////////////////////////////////
template <typename CharT, typename ParserT, typename SkipT>
inline tree_parse_info<CharT const*>
pt_parse(
    CharT const*            str,
    parser<ParserT> const&  p,
    SkipT const&            skip)
{
    CharT const* last = str;
    while (*last)
        last++;
    return pt_parse(str, last, p, skip);
}

//////////////////////////////////
template <typename CharT, typename ParserT>
inline tree_parse_info<CharT const*>
pt_parse(
    CharT const*            str,
    parser<ParserT> const&  parser)
{
    CharT const* last = str;
    while (*last)
    {
        last++;
    }
    return pt_parse(str, last, parser);
}

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* parse_tree.hpp
NKlV1Hiz8I0obNkan6xzoeR2g+waCLQ1ztn2JPsAYAcAtICyiQCeTFTIRMQcb7UrJURGjY20ZiijELu9i79U/GE9i2wGs0aPKyidphjqwYCRA7e2ui830kqdCDtlmF7Y+sNLrKnxaPkkeHwcKBmrcROd+lWO4cCsb8sa3ol+ZnUbDp/Ht7mHd6Kf2c4J4qrxNhsq4A6MmBTZRyTxfBzS1JYew9P2IQLPcDt+4KU32bEdK3D/Po/2oDwbczbiJLi0tS1LekVDOiJUV+18z6K4Q/1+tMNcXHR5pJvt5prsLjbbzTtfHGGzTc7fMVl/546MDNqp7mGFeU+opXsvjzDugOq1BoOHfX7GPoxV85hsHfgcwrzsN0NknQnzIhBprxOR5l5DlPj+el9bO2UXnSn7DN23X7RSXdSVGV7ffveSGnan0dnIWcyeQmgwIKuFxdUgWP8fUrIwGeAVUFM8PagpSkpTXr/yZE3pz02xOCwcBS+pNZ1s4GXvF7fIxvzvbRmEtog5yW0Z8N+2ZdULJ2zL53P+j23xoy3Xp7Rl2RUna8uV3JbBhjrIUAcSiXlij7Bo5ksnbubQ/1szJU/ouRdxb0+6t4FfauQskRbfObKqqpq5Xc+G642uNlvWPPb16KhejDP1jN9DrQqGkjbxtw/TWACub6vPHEVnmXjFwDK+I9Mvuj3RjrN0y+/Zb3ZAPxAtdvplLiNnI8z9tk1tuhPl+ev7nuXFTBAvn4V8thhUqrMaK6KwRemudy/coXQq/EjJEN/3NQztYr3T1MIG5YdSsWgG6GtLOJk5HCUUl1+IGWAb4WmqbIpoKcJhfTKOaXEyx3TA/8g0NVuMXdfkNTILZ5vodrUpIk/whxIO5fw8H/en8vL6lgWCVYgMbcTS9TkEIf0RCJPwYb8D4uE5LnDQT8n/OZi/yT8hkAI6ZdezQbB1YPhyO1aVp/uycYSgKv0UszJZFe3REwI07bYiv6yNIMesz/RhHBAHCgn1adGLh1XBa0VRHv1I7yZ2B7hEzMqE3wd9ll/pBxckBHE5OyhxBiE5Lj0zbCDoL3y0J/NSA0H9iFgyRFY9R5+qMAcwW44RNTpXK1b0ax1+MLU82vg5ZmfhY2uhydDSqND4OZJVzrVKV6qsZVBzqgE/h0ZO/5WIaahh9OcO18vpuEHqgJVgLY+4SW7+3kkO5fwyv1jDEK3mxrrJXH05kLTiHl1Y4bx7U0HNNOkqFbL3U6lo7PuwrXot1smRMHRVIr8dajuUseNhM3Iv32DFhBZiudxwjsRhJz+7lV48jT98ePSilspSaTKArpoty6aFlPc58u2zDfQkszjUU+RLR+h6rK4hqIZybKQfvSvyVW1W+j+NR+pYH3bHkYVISTtiABd9dJ7feF8bPZRNB/rckoz7sgufA+4NDeyR2tfGNkaz8rSSVunJ1kBMW0NtxWTC68zUhJoFzSac4R/xljtnFcPKK/Ox8I2TDx/RfK16seMx3MjqELKJveJmsfHY9jID22OrsRhBIqjBPUdGNg0oLHfe9jbtB2bwXNpFpdoHFvMlUDIockTmzLSrF8Lmq9WuZoTdk2LdI63pMlBgVqS1iwo8oRdr92+Tat+xruh+pkzx350Q+stu00w4xYdDUbmHvUJtprUznsDQg0pKRVoAxoZJrl4sFyaGf45cidT6rHCaMTMvho/wZrDUkjF0LHGCvMtk3hTTOrN2c6mfoNBiWcgK5vxfNGlJapOkH4aIka5ieGiT/xetgAJjtJ4ZxDDNkZV00hvEh8U0hp2DXMlzJuc77qNqQJKPKlaX9zXy2B8Qv6H6wmnSZRtUbR4UhjEVS073tUTHGAU7xxS+32fzWQ3nlexBoGXfnoL3RO1VQOziSGaSzy7arcr08mxq9gFApk8YOVtfxPKm6Sv3Vgh1UuHn6nXhDHoZu5KZ6lpFs1bRolUc1Cpa5e6MZGpI0QsGFNfSfa5wTjCIgKTpUBEqk+zycBrdwDmV3kg1ro71JEAV5g6EEaikV965ISUHH+WFNQvGI1Lz9vo4s/3wCPTEnJ4ZvBj7imcuBZSNwS56GKoTtiI1K2wXD/yMY4oH1c6CByDxzrpw/+pdzDKfgZNYR9hbzbcLhuYVe8TEQVTVQg6kQjTt+DyN7xEj0yf0TNgIVzi1ijZjMfDieh/HhKWe6iVCm4+csG7u9VumxKu/+YvdUxf7Qlf365kh5wGbLTyI/RbTWN2abRjV7+K9OSU3dnBGF4Qi4zKROxKBzjXfisK9SoY+JS92mXSN1SUeAi7WJezgB3Ns9yrZgUDolnS2ScY5UrhJSdMbo76t2Cs0daum7tBUdFdO3mHfCtTIpvYtmnpQU1ulwb0MQ+uugqEf1XpKinMuj5KFnzwlrWB3ve+5AZxHHSYmnmEY9MF0fWZe1PecP2wnQmPeC2yNPQmb1JDpDC/VbAICR5m4a6a72PVIMSU2XBTwklQ0njUHVcQuiA+APoTDDbPEJyh9b5YZH2GF7GHgQzw7WgXpvv16xS69fCsiRjbkH9XrOTbk+0fyG3RfY75vRzptqSt03750n0CWFt23Ajna32/NbymsODjXmV++K738oL6lsKS5Il0n6PCtSN9U6Gud20lXd+Srjelqa6HaQq8It8sJG2EjUKqXLKMdYNhIoC4mAF96ZcpSzOZ9fmQBpIcOwgvLsawUtzidqBmtvE2ONWx5eZGgv5Hxk3I1X7P46nKC1H5QutV8LbFbgvSPTdV3vciI6DRvRZvSHZGixflXERZNxT+gaiCkVPt6K5qV3t6KVrUHpQdDZ7DWRbOEF8qRpp5CR0gwFE6XBWWYP/ivUqkpB70VB9XFouRKJjl/je+cjQCERY7hkB8qWcNhKKrKb788IvFtXsuLEayVyg2hxgrXFdL7eed6H9RKbNT3jv34c2xxUDzRh86KBoMOohmTvtGLp1t+TuJE9HSiPld6lOzIvu+1EZMKavx+iRI6V6aKd018MXyaP9Qbnfuj2blyMFEd1b+/kbCKe37dzRZWxPYs04s0R2lsIxw5Qxw7SHTEZb+RXrKPYhOZQJmh11bSArSEMIUM0YhMPX6T0Elltbb+QFjuO2SL6wP+JauDPiDrQPZHaBN2vSadvmXzczaTFJTifqRmYTGUIi1E2dTbyw6tQP2vG9BfZ8cHWrFHHy/9jvAniMya1JPIrJ+AVx2I3LSfY0qKwRen0lk0QIOYvUfnC00fPNfps2B1fciyul7robSPLKIqk0qKr6nOOkPdb9FNSW3LRtteR9tyk9uWrY/PTmpbdmgO2jaZ2wbDdkkE/nlQByKwYn9hPROBQwmcON7kNrEYTSzOLthcWO9+pLZwO/A/NBG6BknUXxeT+rs8zBPzP9N/HYZ7K7rkaz/5cGeHlqJLC25O7dLGi07WpSEdu+RJ7tJIN6Ul98eiZsM3/1+o2Tj2t+JAQtGyd0YCIpsO0QsCy9CDG2yetWNu6+0RtVCVaWFSYHU3akLOHOw9xSEj524wS0wst3imNv7WaPEkk1ZMKj8/wKRAhpiN0jNv1HsZM6fTjjDzeuMh6CtMjbt5Pza1m028d6HBbt6zO7h5z3OYbt4vdJzAzXuedPO+/u/0BwwjMWlSipv3bLEvneFFzJyWtEKDhC7MNRhqaOffJv4K71OtAX27GHCFjT20x3cR2tCvw/w00KLYrHSK1PYtb/r9Tot0nhh3mW76Q++Pqs9Cgday6LV9tal54jXKTcigNkhsGc6ht+Je0gPsLz6vyqC+2MS/26UeNu2f8Be/YyfcRebZIjNulT7jU6fnzInx6enVlQDkVxdI35SEGBYPQDUEqQ7aDiMzBtgwqoozMiObvj61Dl5dLTxkcBIeAqRQ3D4YTS/YXXhUKfDOzlPPEXaqeOikbPUUcXggnfZzHGonMeclbmpmmWjJMQxtWp53dn86K6b118ffWLiFLWb8fm3qjfr4UMHukTRumTpMuB2RGSFb5dRJylixl+rS5wyjrg+P3JNnUy4LDyKcBX4u08fREirOg6tLQtN8jMoQqVwAn7Gz8+p9W6Gwo5XvkDs55dSHA00Jt0HFdRsByu2wjynO44TCOqLa+RyydJsUlz8sT1dWwNomVCjCcRbWirIO7orL6OCWQE2VBQsMWrddvXNv5VkeVVivnBoUhTASqqcZWNIFtDJP24Qd/HUkU24lF0U60Vwo9LWYUx9/K8Zmkt5qTinPggs67CD1fK7kJaT5DorCMnMVXdwFSO/1cDR5wSV2eHkCOp8ZPgUtR7A+piZpSfXfQUvqr1NoED9xr5GeCb6ivh/K2GeR1XyTIKs797bI6j0gq/c8bJLVGzqDrEbmJLKaH0O2nZKsbmSyGmlMVvNNSDBZjWooxy76iQxHPptSHhm+i2+uK9gcHpDq+NRvAzhPpk3rsjDz6+kYRCl9C03ZOXo6JS2GElNAbxVTKe9kzoHqCIQwJQgofge8Ndw7RcqHc6tLMBIrfoUd+VBGi9V7vkn03tXL6n0zeo8/3PvaTug9Mqfpw63e82PIz73/+FnBvUca955vQkN3oveohnLs594jn81duYWaHxm+Xz6st0MvOjxoineuX+1cJvxGOxy/+suIQPQLYwzWgB9rIJeeua+oBaZHswGlgTx67fW73FWI3ujeMKaHe0ORh317N/snEHpicgmK/foYInhGj3VXnk0Z6SdT/rxq45+H8KNcNlY5fay7ir2jzsyjjVptgWJZs/EQwko2QdkFSZkwUiJoQ/TJJuji6WPy9KL+QC6IXJp/E2Sk8xAw5R6tZI/m2/f57/bovT7/3f5SoqM+2be3ds+QQTQ4e7oO4L95+Ht2Lv39rG9/oID4Hmiq2EVJH5tVZMwaZixG8MsYWGf5xaOYLWE1EPEw9dbDn/cxRlcZaiceKQwxEWla8TDCU7XiIh6FPG38KGqsVjyG8o0kgCmOvGvo72rjhxVsLivVAkX0Xhs/xg892WZK1UtatPFFyeViXeXk/Ho0m7gjWMQRgrfek00eUBk7D52cJ0+CKXUBfQg2piAoqY82gOqK9SiTSD3253CLX280PqqqV78tEzcd4eAZSfISk4nn8ouHYAosRh5JjpoRNEnpnFuxiQ2fib9ABi6UoQ89ltbVNsmPGw4V24CaJY610vF4kTjzCCefgyo+jp1i5V4hc7vh/FkSmDhgvkjR0RuUxEyYmEeHX25BTUBX+wa1EsJXGrWJrayRh1DjnUz95lhXZl8A+WbazZd9tnEPTMZ2QbrVFVKqG5mu2RNzRG7aQ3jODrYwlL2infewcrXp3xrL/ybqQ2GFR80gojaWV1jhvK1PYYVrdi8wRYBR0WFxAyH7AXlApPalusCIVOyyq2d7K/IUblaZSWGqgJWRTp0af5dDK9RGumJE63iUa70VjcrVhtooag8bKJym9ta72Ev26dc47CX79Wuc55UI/RrXeSXNh33ZNkL16MSBP/19pbCVDEnOTSMaJnI+NgxvxR6FwHSPkRNK1irsdjHoRItjDCm6flns3ICYw0ESFDdVCeNdRJGlGTq1UHUqXQMmRYyOfVhQIxlKYODFuX1J+MIP48yDRDgk3tMLOBmhY9MZI0O82WTaJGSjb44PwfQVngIhmyeAzz1kGFM5E7CFT0ToEo6rZStSi8XY7obU5i3Uh4B3HabtH/zrgeHu8uascA95Q8hOqPgLmy3U3c5nupwoNLwrbeKv/yT97R5upAUR53ZTo+bN7W8jEF5C72Nn6ZlMtrB+rKUF28INvcOhb4t9IlVhkxxgl4Cv24XQrH2MZnF3xlJVDNvhSdVHvqPDYs91TC2h9wMC0ZJlYu+j1CkMA39t4rIJyfqDy0RPIpioHjuCDpw10Yp5GmmGLEIfDpJW/2Q9yO1YZ5BfRs5GDIw9EAgzOYa1qn5Nfa45yMs/0eAoMAEOtnKxxAozCDeIoc2PHDTbLMclCNu8AkNMOQvowRzdKf7wAwHZUKUPBKa+eOpC9nJFJ2mFK3YG1XV2zZU2Gzz1Z4u8eKZ6IgI24AUhJ/G2zG8GmZ/EnxTfnxlHPZ9IozWxHjS+Tf1VCGhItEpQi4HIXX6V6QsKCf56/klEFabG1Ebebqa0zNt6iWVnyjaMcYpXqaXaAthb1y9AxcxyK2nTOQli668uSGBmmUETs2s1LktC6yLn2qZBYvYYIvCYW2pkDjj51U67fV7sFNbXNbVNIMthsb/UHkl4Vv+vSuQll6B0lhyZhc6MVPSNF8pJ6CAkFBBY6ySu4/q/lx/w/1h+4P9j+UH/j+UH/z+WH/r/WH7YL5bPT57002Dfp/wIYaClSWIq18UVZ8zt+//SkFGpDfmvQG/M/wys4/6fgNX/i4OVc6Jhue64IgWbA8HCWquQ11visr55gbfEoxz0lmQr33tLcpVv4/V1VJCMa/iYmuPHt+VstsU06809yZRdnzplyQN4eqQiO16+BxQgMYaw60acD2gGJWIMdPh0j+OGjfWEEipAlB/H29lHrjCMDBRJGaASFxvXwpQXsoyE6Du5eWcY6gBuUX+06PjotKW5yWOTXDIX84qSuSiZKJB9MuBLhh7XyeDt+BHi0Ldhl6i8go+drHobzGniGkEpQVkO+zy0g3NwU/V2OuF6ni+RCr96E51uzQUGC1GPE0OBWHYWljSrV+hFjkJfi3pp2MEHAJA9v+j5HWhzpYveIIrypdGMpPLHMAqlOIP0qd9/TeeuGdvk/nOlXUd4VHUIhGNmSTeId5LJ8UbxEhTzG2GKXPip+5EarXxX4Tug/4+2G4TWhrMmR2+fFK1Y9ePzegUiGehqozZyuu7L1a6ZpN11vTbyRm1iW8RIUz3eQIjaBsxiguGfXrBTm7hHm7hPm7hfmyi0iY3zDbhQguvvRpadBMQHsDmiacvEWG8LSppf8201cwAILPfTDjVxzADHe4ydpxNyXTOJMM8dYs+ZwFt3ILNCALZD7D3SblQ/shHSqPJdum9rOCt616TJUZWaLW4dx0q38uSvcE0nRFoKhS/F/ASEaOYJ7e2dmaf2iENQwC/+ic96EinSaoxlq2FH9Re/IVI75xpTF0aqkrCe7VzaU8+e397wYG+P0m9+e9FD9Jszv70av13ntw8iUk7JECpcnY0PMYGFaF1+h158K+Sq3pkDVEdk+gCbPn5myls/oM4vClqIrAa2RpNdehphaTdfY2FppRwEfHwIrJ3tSSUHanNDBDhO3RkMAuj14gH0aEoTvXOHKp2CAJ2RnxvGWy9R88ogrWGNHKBiG5w9envASFz0XTrArBfud+bDqVZbUgPLpM4O1fPPbyXqF+fRciwXUDKE/A0+mIr8Lf02GflDQKTIFfagfkQdl4TpO0eYmH57K0HlGKXw2jy1szFzjlgykhDRLOknB6O315jl9AvHXv7GeboHPuImeIgAnuWAJG92nniA3UMSiWajZfTijybivF14vpXhC5w27tOIPIiKaHED6wVJ4o91l4ttnKRXsrEwP/aLud+amOMXYH5tih1hLI7o1kyO7+kAexKGiGaxTtTlJwxZROlOaL1Db6GGLJRk6o8J/SEOrsFUMJGz03CQKacFxLBvufX9E7o+M/P8om9bR0CV6je5NqWvpJ5zOmyoAba4TCUkn5AHW1ipfgSbxeVjutmItji/iVsG
*/