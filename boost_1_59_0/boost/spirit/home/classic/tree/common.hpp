/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    Copyright (c) 2001-2007 Hartmut Kaiser
    Revised 2007, Copyright (c) Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_TREE_COMMON_HPP
#define BOOST_SPIRIT_TREE_COMMON_HPP

#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
#include <vector>
#else
#include <list>
#endif

#if defined(BOOST_SPIRIT_USE_BOOST_ALLOCATOR_FOR_TREES)
#include <boost/pool/pool_alloc.hpp>
#endif

#include <algorithm>

#include <boost/ref.hpp>
#include <boost/call_traits.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core.hpp>
#include <boost/assert.hpp>

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
#include <iostream>
#include <boost/spirit/home/classic/debug/debug_node.hpp>
#endif

#include <boost/spirit/home/classic/tree/common_fwd.hpp>

#include <iterator> // for std::iterator_traits, std::distance

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

template <typename T>
void swap(tree_node<T>& a, tree_node<T>& b);

template <typename T, typename V>
void swap(node_iter_data<T, V>& a, node_iter_data<T, V>& b);

namespace impl {
    template <typename T>
    inline void cp_swap(T& t1, T& t2);
}

template <typename T>
struct tree_node
{
    typedef T parse_node_t;
    
#if !defined(BOOST_SPIRIT_USE_BOOST_ALLOCATOR_FOR_TREES)
    typedef std::allocator<tree_node<T> > allocator_type;
#elif !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
    typedef boost::pool_allocator<tree_node<T> > allocator_type;
#else
    typedef boost::fast_pool_allocator<tree_node<T> > allocator_type;
#endif

#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
    typedef std::vector<tree_node<T>, allocator_type> children_t;
#else
    typedef std::list<tree_node<T>, allocator_type> children_t;
#endif  // BOOST_SPIRIT_USE_LIST_FOR_TREES

    typedef typename children_t::iterator tree_iterator;
    typedef typename children_t::const_iterator const_tree_iterator;

    T value;
    children_t children;

    tree_node()
        : value()
        , children()
    {}

    explicit tree_node(T const& v)
        : value(v)
        , children()
    {}

    tree_node(T const& v, children_t const& c)
        : value(v)
        , children(c)
    {}

    void swap(tree_node<T>& x)
    {
        impl::cp_swap(value, x.value);
        impl::cp_swap(children, x.children);
    }
};

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
template <typename T>
inline std::ostream&
operator<<(std::ostream& o, tree_node<T> const& n)
{
    static int depth = 0;
    o << "\n";
    for (int i = 0; i <= depth; ++i)
    {
        o << "\t";
    }
    o << "(depth = " << depth++ << " value = " << n.value;
    int c = 0;
    for (typename tree_node<T>::children_t::const_iterator it = n.children.begin();
         it != n.children.end(); ++it)
    {
        o << " children[" << c++ << "] = " << *it;
    }
    o << ")";
    --depth;
    return o;
}
#endif

//////////////////////////////////
template <typename IteratorT, typename ValueT>
struct node_iter_data
{
    typedef IteratorT iterator_t;
    typedef IteratorT /*const*/ const_iterator_t;

    node_iter_data()
        : first(), last(), is_root_(false), parser_id_(), value_()
        {}

    node_iter_data(IteratorT const& _first, IteratorT const& _last)
        : first(_first), last(_last), is_root_(false), parser_id_(), value_()
        {}

    void swap(node_iter_data& x)
    {
        impl::cp_swap(first, x.first);
        impl::cp_swap(last, x.last);
        impl::cp_swap(parser_id_, x.parser_id_);
        impl::cp_swap(is_root_, x.is_root_);
        impl::cp_swap(value_, x.value_);
    }

    IteratorT begin()
    {
        return first;
    }

    IteratorT const& begin() const
    {
        return first;
    }

    IteratorT end()
    {
        return last;
    }

    IteratorT const& end() const
    {
        return last;
    }

    bool is_root() const
    {
        return is_root_;
    }

    void is_root(bool b)
    {
        is_root_ = b;
    }

    parser_id id() const
    {
        return parser_id_;
    }

    void id(parser_id r)
    {
        parser_id_ = r;
    }

    ValueT const& value() const
    {
        return value_;
    }

    void value(ValueT const& v)
    {
        value_ = v;
    }
private:
    IteratorT first, last;
    bool is_root_;
    parser_id parser_id_;
    ValueT value_;

public:
};

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
// value is default nil_t, so provide an operator<< for nil_t
inline std::ostream&
operator<<(std::ostream& o, nil_t const&)
{
    return o;
}

template <typename IteratorT, typename ValueT>
inline std::ostream&
operator<<(std::ostream& o, node_iter_data<IteratorT, ValueT> const& n)
{
    o << "(id = " << n.id() << " text = \"";
    typedef typename node_iter_data<IteratorT, ValueT>::const_iterator_t
        iterator_t;
    for (iterator_t it = n.begin(); it != n.end(); ++it)
        impl::token_printer(o, *it);
    o << "\" is_root = " << n.is_root()
        << /*" value = " << n.value() << */")";
    return o;
}
#endif

//////////////////////////////////
template <typename IteratorT = char const*, typename ValueT = nil_t>
struct node_val_data
{
    typedef
        typename std::iterator_traits<IteratorT>::value_type
        value_type;

#if !defined(BOOST_SPIRIT_USE_BOOST_ALLOCATOR_FOR_TREES)
    typedef std::allocator<value_type> allocator_type;
#elif !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
    typedef boost::pool_allocator<value_type> allocator_type;
#else
    typedef boost::fast_pool_allocator<value_type> allocator_type;
#endif

#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
    typedef std::vector<value_type, allocator_type> container_t;
#else
    typedef std::list<value_type, allocator_type> container_t;
#endif

    typedef typename container_t::iterator iterator_t;
    typedef typename container_t::const_iterator const_iterator_t;

    node_val_data()
        : text(), is_root_(false), parser_id_(), value_()
        {}

#if defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
    node_val_data(IteratorT const& _first, IteratorT const& _last)
        : text(), is_root_(false), parser_id_(), value_()
        {
            std::copy(_first, _last, std::inserter(text, text.end()));
        }

    // This constructor is for building text out of iterators
    template <typename IteratorT2>
    node_val_data(IteratorT2 const& _first, IteratorT2 const& _last)
        : text(), is_root_(false), parser_id_(), value_()
        {
            std::copy(_first, _last, std::inserter(text, text.end()));
        }
#else
    node_val_data(IteratorT const& _first, IteratorT const& _last)
        : text(_first, _last), is_root_(false), parser_id_(), value_()
        {}

    // This constructor is for building text out of iterators
    template <typename IteratorT2>
    node_val_data(IteratorT2 const& _first, IteratorT2 const& _last)
        : text(_first, _last), is_root_(false), parser_id_(), value_()
        {}
#endif

    void swap(node_val_data& x)
    {
        impl::cp_swap(text, x.text);
        impl::cp_swap(is_root_, x.is_root_);
        impl::cp_swap(parser_id_, x.parser_id_);
        impl::cp_swap(value_, x.value_);
    }

    typename container_t::iterator begin()
    {
        return text.begin();
    }

    typename container_t::const_iterator begin() const
    {
        return text.begin();
    }

    typename container_t::iterator end()
    {
        return text.end();
    }

    typename container_t::const_iterator end() const
    {
        return text.end();
    }

    bool is_root() const
    {
        return is_root_;
    }

    void is_root(bool b)
    {
        is_root_ = b;
    }

    parser_id id() const
    {
        return parser_id_;
    }

    void id(parser_id r)
    {
        parser_id_ = r;
    }

    ValueT const& value() const
    {
        return value_;
    }

    void value(ValueT const& v)
    {
        value_ = v;
    }

private:
    container_t text;
    bool is_root_;
    parser_id parser_id_;
    ValueT value_;
};

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
template <typename IteratorT, typename ValueT>
inline std::ostream&
operator<<(std::ostream& o, node_val_data<IteratorT, ValueT> const& n)
{
    o << "(id = " << n.id() << " text = \"";
    typedef typename node_val_data<IteratorT, ValueT>::const_iterator_t
        iterator_t;
    for (iterator_t it = n.begin(); it != n.end(); ++it)
        impl::token_printer(o, *it);
    o << "\" is_root = " << n.is_root()
        << " value = " << n.value() << ")";
    return o;
}
#endif

template <typename T>
inline void
swap(tree_node<T>& a, tree_node<T>& b)
{
    a.swap(b);
}

template <typename T, typename V>
inline void
swap(node_iter_data<T, V>& a, node_iter_data<T, V>& b)
{
    a.swap(b);
}

//////////////////////////////////
template <typename ValueT>
class node_iter_data_factory
{
public:
    // This inner class is so that node_iter_data_factory can simulate
    // a template template parameter
    template <typename IteratorT>
    class factory
    {
    public:
        typedef IteratorT iterator_t;
        typedef node_iter_data<iterator_t, ValueT> node_t;

        static node_t create_node(iterator_t const& first, iterator_t const& last,
                bool /*is_leaf_node*/)
        {
            return node_t(first, last);
        }

        static node_t empty_node()
        {
            return node_t();
        }

        // precondition: ContainerT contains a tree_node<node_t>.  And all
        // iterators in the container point to the same sequence.
        template <typename ContainerT>
        static node_t group_nodes(ContainerT const& nodes)
        {
            return node_t(nodes.begin()->value.begin(),
                    nodes.back().value.end());
        }
    };
};

//////////////////////////////////
template <typename ValueT>
class node_val_data_factory 
{
public:
    // This inner class is so that node_val_data_factory can simulate
    // a template template parameter
    template <typename IteratorT>
    class factory
    {
    public:
        typedef IteratorT iterator_t;
        typedef node_val_data<iterator_t, ValueT> node_t;

        static node_t create_node(iterator_t const& first, iterator_t const& last,
                bool is_leaf_node)
        {
            if (is_leaf_node)
                return node_t(first, last);
            else
                return node_t();
        }

        static node_t empty_node()
        {
            return node_t();
        }

        template <typename ContainerT>
        static node_t group_nodes(ContainerT const& nodes)
        {
            typename node_t::container_t c;
            typename ContainerT::const_iterator i_end = nodes.end();
            // copy all the nodes text into a new one
            for (typename ContainerT::const_iterator i = nodes.begin();
                 i != i_end; ++i)
            {
                // See docs: reduced_node_d cannot be used with a
                // rule inside the [].
                BOOST_ASSERT(i->children.size() == 0);
                c.insert(c.end(), i->value.begin(), i->value.end());
            }
            return node_t(c.begin(), c.end());
        }
    };
};

//////////////////////////////////
template <typename ValueT>
class node_all_val_data_factory
{
public:
    // This inner class is so that node_all_val_data_factory can simulate
    // a template template parameter
    template <typename IteratorT>
    class factory
    {
    public:
        typedef IteratorT iterator_t;
        typedef node_val_data<iterator_t, ValueT> node_t;

        static node_t create_node(iterator_t const& first, iterator_t const& last,
                bool /*is_leaf_node*/)
        {
            return node_t(first, last);
        }

        static node_t empty_node()
        {
            return node_t();
        }

        template <typename ContainerT>
        static node_t group_nodes(ContainerT const& nodes)
        {
            typename node_t::container_t c;
            typename ContainerT::const_iterator i_end = nodes.end();
            // copy all the nodes text into a new one
            for (typename ContainerT::const_iterator i = nodes.begin();
                    i != i_end; ++i)
            {
                BOOST_ASSERT(i->children.size() == 0);
                c.insert(c.end(), i->value.begin(), i->value.end());
            }
            return node_t(c.begin(), c.end());
        }
    };
};

namespace impl {

    ///////////////////////////////////////////////////////////////////////////
    // can't call unqualified swap from within classname::swap
    // as Koenig lookup rules will find only the classname::swap
    // member function not the global declaration, so use cp_swap
    // as a forwarding function (JM):
    template <typename T>
    inline void cp_swap(T& t1, T& t2)
    {
        using std::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;
        using boost::swap;
        swap(t1, t2);
    }
}

//////////////////////////////////
template <typename IteratorT, typename NodeFactoryT, typename T>
class tree_match : public match<T>
{
public:

    typedef typename NodeFactoryT::template factory<IteratorT> node_factory_t;
    typedef typename node_factory_t::node_t parse_node_t;
    typedef tree_node<parse_node_t> node_t;
    typedef typename node_t::children_t container_t;
    typedef typename container_t::iterator tree_iterator;
    typedef typename container_t::const_iterator const_tree_iterator;

    typedef T attr_t;
    typedef typename boost::call_traits<T>::param_type      param_type;
    typedef typename boost::call_traits<T>::reference       reference;
    typedef typename boost::call_traits<T>::const_reference const_reference;

    tree_match()
    : match<T>(), trees()
    {}

    explicit
    tree_match(std::size_t length_)
    : match<T>(length_), trees()
    {}

    tree_match(std::size_t length_, parse_node_t const& n)
    : match<T>(length_), trees()
    { 
        trees.push_back(node_t(n)); 
    }

    tree_match(std::size_t length_, param_type val, parse_node_t const& n)
    : match<T>(length_, val), trees()
    {
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
        trees.reserve(10); // this is more or less an arbitrary number...
#endif
        trees.push_back(node_t(n));
    }

    // attention, these constructors will change the second parameter!
    tree_match(std::size_t length_, container_t& c)
    : match<T>(length_), trees()
    { 
        impl::cp_swap(trees, c);
    }

    tree_match(std::size_t length_, param_type val, container_t& c)
    : match<T>(length_, val), trees()
    {
        impl::cp_swap(trees, c);
    }

    template <typename T2>
    tree_match(match<T2> const& other)
    : match<T>(other), trees()
    {}

    template <typename T2, typename T3, typename T4>
    tree_match(tree_match<T2, T3, T4> const& other)
    : match<T>(other), trees()
    { impl::cp_swap(trees, other.trees); }

    template <typename T2>
    tree_match&
    operator=(match<T2> const& other)
    {
        match<T>::operator=(other);
        return *this;
    }

    template <typename T2, typename T3, typename T4>
    tree_match&
    operator=(tree_match<T2, T3, T4> const& other)
    {
        match<T>::operator=(other);
        impl::cp_swap(trees, other.trees);
        return *this;
    }

    tree_match(tree_match const& x)
    : match<T>(x), trees()
    {
        // use auto_ptr like ownership for the trees data member
        impl::cp_swap(trees, x.trees);
    }

    tree_match& operator=(tree_match const& x)
    {
        tree_match tmp(x);
        this->swap(tmp);
        return *this;
    }

    void swap(tree_match& x)
    {
        match<T>::swap(x);
        impl::cp_swap(trees, x.trees);
    }

    mutable container_t trees;
};

#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)
template <typename IteratorT, typename NodeFactoryT, typename T>
inline std::ostream&
operator<<(std::ostream& o, tree_match<IteratorT, NodeFactoryT, T> const& m)
{
    typedef
        typename tree_match<IteratorT, NodeFactoryT, T>::container_t::iterator
        iterator;

    o << "(length = " << (int)m.length();
    int c = 0;
    for (iterator i = m.trees.begin(); i != m.trees.end(); ++i)
    {
        o << " trees[" << c++ << "] = " << *i;
    }
    o << "\n)";
    return o;
}
#endif

//////////////////////////////////
struct tree_policy
{
    template <typename FunctorT, typename MatchT>
    static void apply_op_to_match(FunctorT const& /*op*/, MatchT& /*m*/)
    {}

    template <typename MatchT, typename Iterator1T, typename Iterator2T>
    static void group_match(MatchT& /*m*/, parser_id const& /*id*/,
            Iterator1T const& /*first*/, Iterator2T const& /*last*/)
    {}

    template <typename MatchT>
    static void concat(MatchT& /*a*/, MatchT const& /*b*/)
    {}
};

//////////////////////////////////
template <
    typename MatchPolicyT,
    typename IteratorT,
    typename NodeFactoryT,
    typename TreePolicyT, 
    typename T
>
struct common_tree_match_policy : public match_policy
{
    common_tree_match_policy()
    {
    }

    template <typename PolicyT>
    common_tree_match_policy(PolicyT const & policies)
        : match_policy((match_policy const &)policies)
    {
    }

    template <typename U>
    struct result { typedef tree_match<IteratorT, NodeFactoryT, U> type; };

    typedef tree_match<IteratorT, NodeFactoryT, T> match_t;
    typedef IteratorT iterator_t;
    typedef TreePolicyT tree_policy_t;
    typedef NodeFactoryT factory_t;

    static const match_t no_match() { return match_t(); }
    static const match_t empty_match()
    { return match_t(0, tree_policy_t::empty_node()); }

    template <typename AttrT, typename Iterator1T, typename Iterator2T>
    static tree_match<IteratorT, NodeFactoryT, AttrT> create_match(
        std::size_t length,
        AttrT const& val,
        Iterator1T const& first,
        Iterator2T const& last)
    {
#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)

        BOOST_SPIRIT_DEBUG_OUT << "\n>>> create_node(begin) <<<\n" 
            "creating node text: \"";
        for (Iterator1T it = first; it != last; ++it)
            impl::token_printer(BOOST_SPIRIT_DEBUG_OUT, *it);
        BOOST_SPIRIT_DEBUG_OUT << "\"\n";
        BOOST_SPIRIT_DEBUG_OUT << ">>> create_node(end) <<<\n\n"; 
#endif
        return tree_match<IteratorT, NodeFactoryT, AttrT>(length, val,
            tree_policy_t::create_node(length, first, last, true));
    }

    template <typename Match1T, typename Match2T>
    static void concat_match(Match1T& a, Match2T const& b)
    {
#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_NODES)

        BOOST_SPIRIT_DEBUG_OUT << "\n>>> concat_match(begin) <<<\n";
        BOOST_SPIRIT_DEBUG_OUT << "tree a:\n" << a << "\n";
        BOOST_SPIRIT_DEBUG_OUT << "tree b:\n" << b << "\n";
        BOOST_SPIRIT_DEBUG_OUT << ">>> concat_match(end) <<<\n\n";
#endif
        BOOST_SPIRIT_ASSERT(a && b);
        if (a.length() == 0)
        {
            a = b;
            return;
        }
        else if (b.length() == 0
#ifdef BOOST_SPIRIT_NO_TREE_NODE_COLLAPSING
            && !b.trees.begin()->value.id().to_long()
#endif
            )
        {
            return;
        }
        a.concat(b);
        tree_policy_t::concat(a, b);
    }

    template <typename MatchT, typename IteratorT2>
    void
    group_match(
        MatchT&             m,
        parser_id const&    id,
        IteratorT2 const&   first,
        IteratorT2 const&   last) const
    {
        if (!m) return;
        
#if defined(BOOST_SPIRIT_DEBUG) && \
    (BOOST_SPIRIT_DEBUG_FLAGS & BOOST_SPIRIT_DEBUG_FLAGS_TREES)

        BOOST_SPIRIT_DEBUG_OUT << "\n>>> group_match(begin) <<<\n"
            "new node(" << id << ") \"";
        for (IteratorT2 it = first; it != last; ++it)
            impl::token_printer(BOOST_SPIRIT_DEBUG_OUT, *it);
        BOOST_SPIRIT_DEBUG_OUT << "\"\n";
        BOOST_SPIRIT_DEBUG_OUT << "new child tree (before grouping):\n" << m << "\n";

        tree_policy_t::group_match(m, id, first, last);

        BOOST_SPIRIT_DEBUG_OUT << "new child tree (after grouping):\n" << m << "\n";
        BOOST_SPIRIT_DEBUG_OUT << ">>> group_match(end) <<<\n\n";
#else
        tree_policy_t::group_match(m, id, first, last);
#endif
    }
};

//////////////////////////////////
template <typename MatchPolicyT, typename NodeFactoryT>
struct common_tree_tree_policy
{
    typedef typename MatchPolicyT::iterator_t iterator_t;
    typedef typename MatchPolicyT::match_t match_t;
    typedef typename NodeFactoryT::template factory<iterator_t> factory_t;
    typedef typename factory_t::node_t node_t;

    template <typename Iterator1T, typename Iterator2T>
        static node_t
        create_node(std::size_t /*length*/, Iterator1T const& first,
            Iterator2T const& last, bool leaf_node)
    {
        return factory_t::create_node(first, last, leaf_node);
    }

    static node_t
        empty_node()
    {
        return factory_t::empty_node();
    }

    template <typename FunctorT>
        static void apply_op_to_match(FunctorT const& op, match_t& m)
    {
        op(m);
    }
};

//////////////////////////////////
// directives to modify how the parse tree is generated

struct no_tree_gen_node_parser_gen;

template <typename T>
struct no_tree_gen_node_parser
:   public unary<T, parser<no_tree_gen_node_parser<T> > >
{
    typedef no_tree_gen_node_parser<T> self_t;
    typedef no_tree_gen_node_parser_gen parser_generator_t;
    typedef unary_parser_category parser_category_t;

    no_tree_gen_node_parser(T const& a)
    : unary<T, parser<no_tree_gen_node_parser<T> > >(a) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const
    {
        typedef typename ScannerT::iteration_policy_t iteration_policy_t;
        typedef match_policy match_policy_t;
        typedef typename ScannerT::action_policy_t action_policy_t;
        typedef scanner_policies<
            iteration_policy_t,
            match_policy_t,
            action_policy_t
        > policies_t;

        return this->subject().parse(scanner.change_policies(policies_t(scanner)));
    }
};

struct no_tree_gen_node_parser_gen
{
    template <typename T>
    struct result {

        typedef no_tree_gen_node_parser<T> type;
    };

    template <typename T>
    static no_tree_gen_node_parser<T>
    generate(parser<T> const& s)
    {
        return no_tree_gen_node_parser<T>(s.derived());
    }

    template <typename T>
    no_tree_gen_node_parser<T>
    operator[](parser<T> const& s) const
    {
        return no_tree_gen_node_parser<T>(s.derived());
    }
};

const no_tree_gen_node_parser_gen no_node_d = no_tree_gen_node_parser_gen();

//////////////////////////////////

struct leaf_node_parser_gen;

template<typename T>
struct leaf_node_parser
:   public unary<T, parser<leaf_node_parser<T> > >
{
    typedef leaf_node_parser<T> self_t;
    typedef leaf_node_parser_gen parser_generator_t;
    typedef unary_parser_category parser_category_t;

    leaf_node_parser(T const& a)
    : unary<T, parser<leaf_node_parser<T> > >(a) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const
    {
        typedef scanner_policies< typename ScannerT::iteration_policy_t,
            match_policy, typename ScannerT::action_policy_t > policies_t;

        typedef typename ScannerT::iterator_t iterator_t;
        typedef typename parser_result<self_t, ScannerT>::type result_t;
        typedef typename result_t::node_factory_t factory_t;

        iterator_t from = scanner.first;
        result_t hit = impl::contiguous_parser_parse<result_t>(this->subject(),
            scanner.change_policies(policies_t(scanner,match_policy(),scanner)),
            scanner);

        if (hit)
            return result_t(hit.length(), 
                factory_t::create_node(from, scanner.first, true));
        else
            return result_t(hit.length());
    }
};

struct leaf_node_parser_gen
{
    template <typename T>
    struct result {

        typedef leaf_node_parser<T> type;
    };

    template <typename T>
    static leaf_node_parser<T>
    generate(parser<T> const& s)
    {
        return leaf_node_parser<T>(s.derived());
    }

    template <typename T>
    leaf_node_parser<T>
    operator[](parser<T> const& s) const
    {
        return leaf_node_parser<T>(s.derived());
    }
};

const leaf_node_parser_gen leaf_node_d = leaf_node_parser_gen();
const leaf_node_parser_gen token_node_d = leaf_node_parser_gen();

//////////////////////////////////
namespace impl {

    template <typename MatchPolicyT>
    struct tree_policy_selector
    {
        typedef tree_policy type;
    };

} // namespace impl

//////////////////////////////////
template <typename NodeParserT>
struct node_parser_gen;

template <typename T, typename NodeParserT>
struct node_parser
:   public unary<T, parser<node_parser<T, NodeParserT> > >
{
    typedef node_parser<T, NodeParserT> self_t;
    typedef node_parser_gen<NodeParserT> parser_generator_t;
    typedef unary_parser_category parser_category_t;

    node_parser(T const& a)
    : unary<T, parser<node_parser<T, NodeParserT> > >(a) {}

    template <typename ScannerT>
    struct result
    {
        typedef typename parser_result<T, ScannerT>::type type;
    };

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const
    {
        typename parser_result<self_t, ScannerT>::type hit = this->subject().parse(scanner);
        if (hit)
        {
            impl::tree_policy_selector<typename ScannerT::match_policy_t>::type::apply_op_to_match(NodeParserT(), hit);
        }
        return hit;
    }
};

template <typename NodeParserT>
struct node_parser_gen
{
    template <typename T>
    struct result {

        typedef node_parser<T, NodeParserT> type;
    };

    template <typename T>
    static node_parser<T, NodeParserT>
    generate(parser<T> const& s)
    {
        return node_parser<T, NodeParserT>(s.derived());
    }

    template <typename T>
    node_parser<T, NodeParserT>
    operator[](parser<T> const& s) const
    {
        return node_parser<T, NodeParserT>(s.derived());
    }
};
//////////////////////////////////
struct reduced_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        if (m.trees.size() == 1)
        {
            m.trees.begin()->children.clear();
        }
        else if (m.trees.size() > 1)
        {
            typedef typename MatchT::node_factory_t node_factory_t;
            m = MatchT(m.length(), node_factory_t::group_nodes(m.trees));
        }
    }
};

const node_parser_gen<reduced_node_op> reduced_node_d =
    node_parser_gen<reduced_node_op>();


struct discard_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        m.trees.clear();
    }
};

const node_parser_gen<discard_node_op> discard_node_d =
    node_parser_gen<discard_node_op>();

struct infix_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        typedef typename MatchT::container_t container_t;
        typedef typename MatchT::container_t::iterator iter_t;
        typedef typename MatchT::container_t::value_type value_t;

        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // copying the tree nodes is expensive, since it may copy a whole
        // tree.  swapping them is cheap, so swap the nodes we want into
        // a new container of children.
        container_t new_children;
        std::size_t length = 0;
        std::size_t tree_size = m.trees.size();

        // the infix_node_d[] make no sense for nodes with no subnodes
        BOOST_SPIRIT_ASSERT(tree_size >= 1);

        bool keep = true;
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
        new_children.reserve((tree_size+1)/2);
#endif
        iter_t i_end = m.trees.end();
        for (iter_t i = m.trees.begin(); i != i_end; ++i)
        {
            if (keep) {
                // adjust the length
                length += std::distance((*i).value.begin(), (*i).value.end());

                // move the child node
                new_children.push_back(value_t());
                swap(new_children.back(), *i);
                keep = false;
            }
            else {
                // ignore this child node
                keep = true;
            }
        }

        m = MatchT(length, new_children);
    }
};

const node_parser_gen<infix_node_op> infix_node_d =
    node_parser_gen<infix_node_op>();

struct discard_first_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        typedef typename MatchT::container_t container_t;
        typedef typename MatchT::container_t::iterator iter_t;
        typedef typename MatchT::container_t::value_type value_t;

        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // copying the tree nodes is expensive, since it may copy a whole
        // tree.  swapping them is cheap, so swap the nodes we want into
        // a new container of children, instead of saying
        // m.trees.erase(m.trees.begin()) because, on a container_t that will 
        // cause all the nodes afterwards to be copied into the previous 
        // position.
        container_t new_children;
        std::size_t length = 0;
        std::size_t tree_size = m.trees.size();

        // the discard_first_node_d[] make no sense for nodes with no subnodes
        BOOST_SPIRIT_ASSERT(tree_size >= 1);

        if (tree_size > 1) {
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
            new_children.reserve(tree_size - 1);
#endif
            iter_t i = m.trees.begin(), i_end = m.trees.end();
            for (++i; i != i_end; ++i)
            {
                // adjust the length
                length += std::distance((*i).value.begin(), (*i).value.end());

                // move the child node
                new_children.push_back(value_t());
                swap(new_children.back(), *i);
            }
        }
        else {
        // if there was a tree and now there isn't any, insert an empty node
            iter_t i = m.trees.begin(); 

        // This isn't entirely correct, since the empty node will reference
        // the end of the discarded node, but I currently don't see any way to 
        // get at the begin of the node following this subnode.
        // This should be safe anyway because the it shouldn't get dereferenced
        // under any circumstances.
            typedef typename value_t::parse_node_t::iterator_t iterator_type;
            iterator_type it = (*i).value.end();
            
            new_children.push_back(
                value_t(typename value_t::parse_node_t(it, it)));
        }
        
        m = MatchT(length, new_children);
    }
};

const node_parser_gen<discard_first_node_op> discard_first_node_d =
    node_parser_gen<discard_first_node_op>();

struct discard_last_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        typedef typename MatchT::container_t container_t;
        typedef typename MatchT::container_t::iterator iter_t;
        typedef typename MatchT::container_t::value_type value_t;

        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // copying the tree nodes is expensive, since it may copy a whole
        // tree.  swapping them is cheap, so swap the nodes we want into
        // a new container of children, instead of saying
        // m.trees.erase(m.trees.begin()) because, on a container_t that will 
        // cause all the nodes afterwards to be copied into the previous 
        // position.
        container_t new_children;
        std::size_t length = 0;
        std::size_t tree_size = m.trees.size();

        // the discard_last_node_d[] make no sense for nodes with no subnodes
        BOOST_SPIRIT_ASSERT(tree_size >= 1);

        if (tree_size > 1) {
            m.trees.pop_back();
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
            new_children.reserve(tree_size - 1);
#endif            
            iter_t i_end = m.trees.end();
            for (iter_t i = m.trees.begin(); i != i_end; ++i)
            {
                // adjust the length
                length += std::distance((*i).value.begin(), (*i).value.end());

                // move the child node
                new_children.push_back(value_t());
                swap(new_children.back(), *i);
            }
        }
        else {
        // if there was a tree and now there isn't any, insert an empty node
            iter_t i = m.trees.begin(); 

            typedef typename value_t::parse_node_t::iterator_t iterator_type;
            iterator_type it = (*i).value.begin();
            
            new_children.push_back(
                value_t(typename value_t::parse_node_t(it, it)));
        }
        
        m = MatchT(length, new_children);
    }
};

const node_parser_gen<discard_last_node_op> discard_last_node_d =
    node_parser_gen<discard_last_node_op>();

struct inner_node_op
{
    template <typename MatchT>
    void operator()(MatchT& m) const
    {
        typedef typename MatchT::container_t container_t;
        typedef typename MatchT::container_t::iterator iter_t;
        typedef typename MatchT::container_t::value_type value_t;

        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // copying the tree nodes is expensive, since it may copy a whole
        // tree.  swapping them is cheap, so swap the nodes we want into
        // a new container of children, instead of saying
        // m.trees.erase(m.trees.begin()) because, on a container_t that will 
        // cause all the nodes afterwards to be copied into the previous 
        // position.
        container_t new_children;
        std::size_t length = 0;
        std::size_t tree_size = m.trees.size();
        
        // the inner_node_d[] make no sense for nodes with less then 2 subnodes
        BOOST_SPIRIT_ASSERT(tree_size >= 2);

        if (tree_size > 2) {
            m.trees.pop_back(); // erase the last element
#if !defined(BOOST_SPIRIT_USE_LIST_FOR_TREES)
            new_children.reserve(tree_size - 1);
#endif
            iter_t i = m.trees.begin(); // skip over the first element
            iter_t i_end = m.trees.end();
            for (++i; i != i_end; ++i)
            {
                // adjust the length
                length += std::distance((*i).value.begin(), (*i).value.end());
                
                // move the child node
                new_children.push_back(value_t());
                swap(new_children.back(), *i);
            }
        }
        else {
        // if there was a tree and now there isn't any, insert an empty node
            iter_t i = m.trees.begin(); // skip over the first element

            typedef typename value_t::parse_node_t::iterator_t iterator_type;
            iterator_type it = (*++i).value.begin();
            
            new_children.push_back(
                value_t(typename value_t::parse_node_t(it, it)));
        }
        
        m = MatchT(length, new_children);
    }
};

const node_parser_gen<inner_node_op> inner_node_d =
    node_parser_gen<inner_node_op>();


//////////////////////////////////
// action_directive_parser and action_directive_parser_gen
// are meant to be used as a template to create directives that
// generate action classes.  For example access_match and
// access_node.  The ActionParserT template parameter must be
// a class that has an innter class called action that is templated
// on the parser type and the action type.
template <typename ActionParserT>
struct action_directive_parser_gen;

template <typename T, typename ActionParserT>
struct action_directive_parser
:   public unary<T, parser<action_directive_parser<T, ActionParserT> > >
{
    typedef action_directive_parser<T, ActionParserT> self_t;
    typedef action_directive_parser_gen<ActionParserT> parser_generator_t;
    typedef unary_parser_category parser_category_t;

    action_directive_parser(T const& a)
        : unary<T, parser<action_directive_parser<T, ActionParserT> > >(a) {}

    template <typename ScannerT>
    struct result
    {
        typedef typename parser_result<T, ScannerT>::type type;
    };

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const
    {
        return this->subject().parse(scanner);
    }

    template <typename ActionT>
    typename ActionParserT::template action<action_directive_parser<T, ActionParserT>, ActionT>
    operator[](ActionT const& actor) const
    {
        typedef typename
            ActionParserT::template action<action_directive_parser, ActionT>
            action_t;
        return action_t(*this, actor);
    }
};

//////////////////////////////////
template <typename ActionParserT>
struct action_directive_parser_gen
{
    template <typename T>
    struct result {

        typedef action_directive_parser<T, ActionParserT> type;
    };

    template <typename T>
    static action_directive_parser<T, ActionParserT>
    generate(parser<T> const& s)
    {
        return action_directive_parser<T, ActionParserT>(s.derived());
    }

    template <typename T>
    action_directive_parser<T, ActionParserT>
    operator[](parser<T> const& s) const
    {
        return action_directive_parser<T, ActionParserT>(s.derived());
    }
};

//////////////////////////////////
// Calls the attached action passing it the match from the parser
// and the first and last iterators.
// The inner template class is used to simulate template-template parameters
// (declared in common_fwd.hpp).
template <typename ParserT, typename ActionT>
struct access_match_action::action
:   public unary<ParserT, parser<access_match_action::action<ParserT, ActionT> > >
{
    typedef action_parser_category parser_category;
    typedef action<ParserT, ActionT> self_t;
    
    template <typename ScannerT>
    struct result
    {
        typedef typename parser_result<ParserT, ScannerT>::type type;
    };

    action( ParserT const& subject,
            ActionT const& actor_);

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const;

    ActionT const &predicate() const;

    private:
    ActionT actor;
};

//////////////////////////////////
template <typename ParserT, typename ActionT>
access_match_action::action<ParserT, ActionT>::action(
    ParserT const& subject,
    ActionT const& actor_)
: unary<ParserT, parser<access_match_action::action<ParserT, ActionT> > >(subject)
, actor(actor_)
{}

//////////////////////////////////
template <typename ParserT, typename ActionT>
template <typename ScannerT>
typename parser_result<access_match_action::action<ParserT, ActionT>, ScannerT>::type
access_match_action::action<ParserT, ActionT>::
parse(ScannerT const& scan) const
{
    typedef typename ScannerT::iterator_t iterator_t;
    typedef typename parser_result<self_t, ScannerT>::type result_t;
    if (!scan.at_end())
    {
        iterator_t save = scan.first;
        result_t hit = this->subject().parse(scan);
        actor(hit, save, scan.first);
        return hit;
    }
    return scan.no_match();
}

//////////////////////////////////
template <typename ParserT, typename ActionT>
ActionT const &access_match_action::action<ParserT, ActionT>::predicate() const
{
    return actor;
}

//////////////////////////////////
const action_directive_parser_gen<access_match_action> access_match_d
    = action_directive_parser_gen<access_match_action>();



//////////////////////////////////
// Calls the attached action passing it the node from the parser
// and the first and last iterators
// The inner template class is used to simulate template-template parameters
// (declared in common_fwd.hpp).
template <typename ParserT, typename ActionT>
struct access_node_action::action
:   public unary<ParserT, parser<access_node_action::action<ParserT, ActionT> > >
{
    typedef action_parser_category parser_category;
    typedef action<ParserT, ActionT> self_t;
    
    template <typename ScannerT>
    struct result
    {
        typedef typename parser_result<ParserT, ScannerT>::type type;
    };

    action( ParserT const& subject,
            ActionT const& actor_);

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scanner) const;

    ActionT const &predicate() const;

    private:
    ActionT actor;
};

//////////////////////////////////
template <typename ParserT, typename ActionT>
access_node_action::action<ParserT, ActionT>::action(
    ParserT const& subject,
    ActionT const& actor_)
: unary<ParserT, parser<access_node_action::action<ParserT, ActionT> > >(subject)
, actor(actor_)
{}

//////////////////////////////////
template <typename ParserT, typename ActionT>
template <typename ScannerT>
typename parser_result<access_node_action::action<ParserT, ActionT>, ScannerT>::type
access_node_action::action<ParserT, ActionT>::
parse(ScannerT const& scan) const
{
    typedef typename ScannerT::iterator_t iterator_t;
    typedef typename parser_result<self_t, ScannerT>::type result_t;
    if (!scan.at_end())
    {
        iterator_t save = scan.first;
        result_t hit = this->subject().parse(scan);
        if (hit && hit.trees.size() > 0)
            actor(*hit.trees.begin(), save, scan.first);
        return hit;
    }
    return scan.no_match();
}

//////////////////////////////////
template <typename ParserT, typename ActionT>
ActionT const &access_node_action::action<ParserT, ActionT>::predicate() const
{
    return actor;
}

//////////////////////////////////
const action_directive_parser_gen<access_node_action> access_node_d
    = action_directive_parser_gen<access_node_action>();



//////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  tree_parse_info
//
//      Results returned by the tree parse functions:
//
//      stop:   points to the final parse position (i.e parsing
//              processed the input up to this point).
//
//      match:  true if parsing is successful. This may be full:
//              the parser consumed all the input, or partial:
//              the parser consumed only a portion of the input.
//
//      full:   true when we have a full match (i.e the parser
//              consumed all the input.
//
//      length: The number of characters consumed by the parser.
//              This is valid only if we have a successful match
//              (either partial or full). A negative value means
//              that the match is unsuccessful.
//
//     trees:   Contains the root node(s) of the tree.
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename IteratorT,
    typename NodeFactoryT,
    typename T
>
struct tree_parse_info 
{
    IteratorT   stop;
    bool        match;
    bool        full;
    std::size_t length;
    typename tree_match<IteratorT, NodeFactoryT, T>::container_t trees;

    tree_parse_info()
        : stop()
        , match(false)
        , full(false)
        , length(0)
        , trees()
    {}

    template <typename IteratorT2>
    tree_parse_info(tree_parse_info<IteratorT2> const& pi)
        : stop(pi.stop)
        , match(pi.match)
        , full(pi.full)
        , length(pi.length)
        , trees()
    {
        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // use auto_ptr like ownership for the trees data member
        swap(trees, pi.trees);
    }

    tree_parse_info(
        IteratorT   stop_,
        bool        match_,
        bool        full_,
        std::size_t length_,
        typename tree_match<IteratorT, NodeFactoryT, T>::container_t trees_)
    :   stop(stop_)
        , match(match_)
        , full(full_)
        , length(length_)
        , trees()
    {
        using std::swap;
        using boost::swap;
        using BOOST_SPIRIT_CLASSIC_NS::swap;

        // use auto_ptr like ownership for the trees data member
        swap(trees, trees_);
    }
};

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* common.hpp
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
*/