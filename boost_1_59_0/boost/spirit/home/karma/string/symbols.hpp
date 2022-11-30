//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_SYMBOLS_NOV_23_2009_1251PM)
#define BOOST_SPIRIT_KARMA_SYMBOLS_NOV_23_2009_1251PM

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/reference.hpp>
#include <boost/spirit/home/karma/generate.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/string_generate.hpp>
#include <boost/config.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/traits.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/if.hpp>
#include <map>
#include <set>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4355) // 'this' : used in base member initializer list warning
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    template <typename T, typename Attribute, typename Enable>
    struct symbols_lookup
    {
        typedef
            mpl::eval_if<fusion::traits::is_sequence<T>
              , traits::detail::value_at_c<T, 0>
              , detail::add_const_ref<T> > sequence_type;
        typedef typename
            mpl::eval_if<traits::is_container<T>
              , traits::container_value<T>
              , sequence_type>::type type;

        // fusion sequence
        template <typename T_>
        static type call(T_ const& t, mpl::false_, mpl::true_)
        {
            return fusion::at_c<0>(t);
        }

        // container
        template <typename T_, typename IsSequence>
        static type call(T_ const& t, mpl::true_, IsSequence)
        {
            return t[0];
        }

        // not a container and not a fusion sequence
        template <typename T_>
        static type call(T_ const& t, mpl::false_, mpl::false_)
        {
            return t;
        }

        static type call(T const& t)
        {
            typedef typename traits::is_container<T>::type is_container;
            typedef typename fusion::traits::is_sequence<T>::type is_sequence;

            return call(t, is_container(), is_sequence());
        }
    };

    template <typename Attribute>
    struct symbols_lookup<Attribute, Attribute>
    {
        typedef Attribute const& type;

        static type call(Attribute const& t)
        {
            return t;
        }
    };

    template <typename Attribute, typename T, typename Enable>
    struct symbols_value
    {
        typedef
            mpl::eval_if<fusion::traits::is_sequence<T>
              , traits::detail::value_at_c<T, 1>
              , mpl::identity<unused_type> > sequence_type;
        typedef typename
            mpl::eval_if<traits::is_container<T>
              , traits::container_value<T>
              , sequence_type>::type type;

        // fusion sequence
        template <typename T_>
        static type call(T_ const& t, mpl::false_, mpl::true_)
        {
            return fusion::at_c<1>(t);
        }

        // container
        template <typename T_, typename IsSequence>
        static type call(T_ const& t, mpl::true_, IsSequence)
        {
            return t[1];
        }

        // not a container nor a fusion sequence
        template <typename T_>
        static type call(T_ const&, mpl::false_, mpl::false_)
        {
            return unused;
        }

        static type call(T const& t)
        {
            typedef typename traits::is_container<T>::type is_container;
            typedef typename fusion::traits::is_sequence<T>::type is_sequence;

            return call(t, is_container(), is_sequence());
        }
    };

    template <typename Attribute>
    struct symbols_value<Attribute, Attribute>
    {
        typedef unused_type type;

        static type call(Attribute const&)
        {
            return unused;
        }
    };
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Attribute>
    struct symbols_lookup
      : mpl::if_<
            traits::not_is_unused<T>
          , std::map<Attribute, T>
          , std::set<Attribute>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename CharEncoding, typename Tag>
        struct generate_encoded
        {
            typedef typename
                proto::terminal<tag::char_code<Tag, CharEncoding> >::type
            encoding_type;

            template <typename OutputIterator, typename Expr, typename Attribute>
            static bool call(OutputIterator& sink, Expr const& expr
              , Attribute const& attr)
            {
                encoding_type const encoding = encoding_type();
                return karma::generate(sink, encoding[expr], attr);
            }
        };

        template <>
        struct generate_encoded<unused_type, unused_type>
        {
            template <typename OutputIterator, typename Expr, typename Attribute>
            static bool call(OutputIterator& sink, Expr const& expr
              , Attribute const& attr)
            {
                return karma::generate(sink, expr, attr);
            }
        };
    }

    template <
        typename Attribute = char, typename T = unused_type
      , typename Lookup = typename symbols_lookup<T, Attribute>::type
      , typename CharEncoding = unused_type, typename Tag = unused_type>
    struct symbols
      : proto::extends<
            typename proto::terminal<
                reference<symbols<Attribute, T, Lookup, CharEncoding, Tag> >
            >::type
          , symbols<Attribute, T, Lookup, CharEncoding, Tag> >
      , primitive_generator<
            symbols<Attribute, T, Lookup, CharEncoding, Tag> >
    {
        typedef T value_type;       // the value associated with each entry

        typedef reference<symbols> reference_;
        typedef typename proto::terminal<reference_>::type terminal;
        typedef proto::extends<terminal, symbols> base_type;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef Attribute type;
        };

        symbols(std::string const& name = "symbols")
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(new Lookup())
          , name_(name)
        {}

        symbols(symbols const& syms)
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(syms.lookup)
          , name_(syms.name_)
        {}

        template <typename CharEncoding_, typename Tag_>
        symbols(symbols<Attribute, T, Lookup, CharEncoding_, Tag_> const& syms)
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(syms.lookup)
          , name_(syms.name_)
        {}

        template <typename Symbols, typename Data>
        symbols(Symbols const& syms, Data const& data
              , std::string const& name = "symbols")
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(new Lookup())
          , name_(name)
        {
            typename range_const_iterator<Symbols>::type si = boost::begin(syms);
            typename range_const_iterator<Data>::type di = boost::begin(data);
            while (si != boost::end(syms))
                add(*si++, *di++);
        }

        symbols&
        operator=(symbols const& rhs)
        {
            *lookup = *rhs.lookup;
            name_ = rhs.name_;
            return *this;
        }

        template <typename CharEncoding_, typename Tag_>
        symbols&
        operator=(symbols<Attribute, T, Lookup, CharEncoding_, Tag_> const& rhs)
        {
            *lookup = *rhs.lookup;
            name_ = rhs.name_;
            return *this;
        }

        void clear()
        {
            lookup->clear();
        }

        struct adder;
        struct remover;

        template <typename Attr, typename T_>
        adder const&
        operator=(std::pair<Attr, T_> const& p)
        {
            lookup->clear();
            return add(p.first, p.second);
        }

        template <typename Attr, typename T_>
        friend adder const&
        operator+= (symbols& sym, std::pair<Attr, T_> const& p)
        {
            return sym.add(p.first, p.second);
        }

        template <typename Attr>
        friend remover const&
        operator-= (symbols& sym, Attr const& attr)
        {
            return sym.remove(attr);
        }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        // non-const version needed to suppress proto's += kicking in
        template <typename Attr, typename T_>
        friend adder const&
        operator+= (symbols& sym, std::pair<Attr, T_>& p)
        {
            return sym.add(p.first, p.second);
        }

        // non-const version needed to suppress proto's -= kicking in
        template <typename Attr>
        friend remover const&
        operator-= (symbols& sym, Attr& attr)
        {
            return sym.remove(attr);
        }
#else
        // for rvalue references
        template <typename Attr, typename T_>
        friend adder const&
        operator+= (symbols& sym, std::pair<Attr, T_>&& p)
        {
            return sym.add(p.first, p.second);
        }

        // for rvalue references
        template <typename Attr>
        friend remover const&
        operator-= (symbols& sym, Attr&& attr)
        {
            return sym.remove(attr);
        }
#endif
        template <typename F>
        void for_each(F f) const
        {
            std::for_each(lookup->begin(), lookup->end(), f);
        }

        template <typename Attr>
        value_type* find(Attr const& attr)
        {
            typename Lookup::iterator it = lookup->find(attr);
            return (it != lookup->end()) ? &(*it).second : 0;
        }

        template <typename Attr>
        value_type& at(Attr const& attr)
        {
            return (*lookup)[attr];
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attr>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attr const& attr) const
        {
            typename Lookup::iterator it = lookup->find(
                traits::symbols_lookup<Attr, Attribute>::call(attr));
            if (it == lookup->end())
                return false;

            return karma::detail::generate_encoded<CharEncoding, Tag>::call(
                        sink, (*it).second
                      , traits::symbols_value<Attribute, Attr>::call(attr)) &&
                   karma::delimit_out(sink, d);
        }

        template <typename Context>
        info what(Context&) const
        {
            return info(name_);
        }

        void name(std::string const &str)
        {
            name_ = str;
        }
        std::string const &name() const
        {
            return name_;
        }

        ///////////////////////////////////////////////////////////////////////
        struct adder
        {
            template <typename, typename = unused_type>
            struct result { typedef adder const& type; };

            adder(symbols& sym)
              : sym(sym)
            {
            }

            template <typename Attr>
            adder const&
            operator()(Attr const& attr, T const& val = T()) const
            {
                sym.lookup->insert(typename Lookup::value_type(attr, val));
                return *this;
            }

            template <typename Attr>
            adder const&
            operator, (Attr const& attr) const
            {
                sym.lookup->insert(typename Lookup::value_type(attr, T()));
                return *this;
            }

            symbols& sym;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(adder& operator= (adder const&))
        };

        struct remover
        {
            template <typename>
            struct result { typedef remover const& type; };

            remover(symbols& sym)
              : sym(sym)
            {
            }

            template <typename Attr>
            remover const&
            operator()(Attr const& attr) const
            {
                sym.lookup->erase(attr);
                return *this;
            }

            template <typename Attr>
            remover const&
            operator, (Attr const& attr) const
            {
                sym.lookup->erase(attr);
                return *this;
            }

            symbols& sym;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(remover& operator= (remover const&))
        };

        adder add;
        remover remove;
        shared_ptr<Lookup> lookup;
        std::string name_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // specialization for unused stored type
    template <
        typename Attribute, typename Lookup
      , typename CharEncoding, typename Tag>
    struct symbols<Attribute, unused_type, Lookup, CharEncoding, Tag>
      : proto::extends<
            typename proto::terminal<
                spirit::karma::reference<
                    symbols<Attribute, unused_type, Lookup, CharEncoding, Tag> >
            >::type
          , symbols<Attribute, unused_type, Lookup, CharEncoding, Tag>
        >
      , spirit::karma::generator<
            symbols<Attribute, unused_type, Lookup, CharEncoding, Tag> >
    {
        typedef unused_type value_type;  // the value associated with each entry

        typedef spirit::karma::reference<symbols> reference_;
        typedef typename proto::terminal<reference_>::type terminal;
        typedef proto::extends<terminal, symbols> base_type;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef Attribute type;
        };

        symbols(std::string const& name = "symbols")
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(new Lookup())
          , name_(name)
        {}

        symbols(symbols const& syms)
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(syms.lookup)
          , name_(syms.name_)
        {}

        template <typename CharEncoding_, typename Tag_>
        symbols(symbols<Attribute, unused_type, Lookup, CharEncoding_, Tag_> const& syms)
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(syms.lookup)
          , name_(syms.name_)
        {}

        template <typename Symbols, typename Data>
        symbols(Symbols const& syms, Data const& data
              , std::string const& name = "symbols")
          : base_type(terminal::make(reference_(*this)))
          , add(*this)
          , remove(*this)
          , lookup(new Lookup())
          , name_(name)
        {
            typename range_const_iterator<Symbols>::type si = boost::begin(syms);
            typename range_const_iterator<Data>::type di = boost::begin(data);
            while (si != boost::end(syms))
                add(*si++, *di++);
        }

        symbols&
        operator=(symbols const& rhs)
        {
            *lookup = *rhs.lookup;
            name_ = rhs.name_;
            return *this;
        }

        template <typename CharEncoding_, typename Tag_>
        symbols&
        operator=(symbols<Attribute, unused_type, Lookup, CharEncoding_, Tag_> const& rhs)
        {
            *lookup = *rhs.lookup;
            name_ = rhs.name_;
            return *this;
        }

        void clear()
        {
            lookup->clear();
        }

        struct adder;
        struct remover;

        template <typename Attr>
        adder const&
        operator=(Attr const& attr)
        {
            lookup->clear();
            return add(attr);
        }

        template <typename Attr>
        friend adder const&
        operator+= (symbols& sym, Attr const& attr)
        {
            return sym.add(attr);
        }

        template <typename Attr>
        friend remover const&
        operator-= (symbols& sym, Attr const& attr)
        {
            return sym.remove(attr);
        }

        // non-const version needed to suppress proto's += kicking in
        template <typename Attr>
        friend adder const&
        operator+= (symbols& sym, Attr& attr)
        {
            return sym.add(attr);
        }

        // non-const version needed to suppress proto's -= kicking in
        template <typename Attr>
        friend remover const&
        operator-= (symbols& sym, Attr& attr)
        {
            return sym.remove(attr);
        }

        template <typename F>
        void for_each(F f) const
        {
            std::for_each(lookup->begin(), lookup->end(), f);
        }

        template <typename Attr>
        value_type const* find(Attr const& attr)
        {
            typename Lookup::iterator it = lookup->find(attr);
            return (it != lookup->end()) ? &unused : 0;
        }

        template <typename Attr>
        value_type at(Attr const& attr)
        {
            typename Lookup::iterator it = lookup->find(attr);
            if (it == lookup->end())
                add(attr);
            return unused;
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attr>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attr const& attr) const
        {
            typename Lookup::iterator it = lookup->find(
                traits::symbols_lookup<Attr, Attribute>::call(attr));
            if (it == lookup->end())
                return false;

            return karma::detail::generate_encoded<CharEncoding, Tag>::
                      call(sink
                        , traits::symbols_lookup<Attr, Attribute>::call(attr)
                        , unused) &&
                   karma::delimit_out(sink, d);
        }

        template <typename Context>
        info what(Context&) const
        {
            return info(name_);
        }

        void name(std::string const &str)
        {
            name_ = str;
        }
        std::string const &name() const
        {
            return name_;
        }

        ///////////////////////////////////////////////////////////////////////
        struct adder
        {
            template <typename, typename = unused_type>
            struct result { typedef adder const& type; };

            adder(symbols& sym)
              : sym(sym)
            {
            }

            template <typename Attr>
            adder const&
            operator()(Attr const& attr) const
            {
                sym.lookup->insert(attr);
                return *this;
            }

            template <typename Attr>
            adder const&
            operator, (Attr const& attr) const
            {
                sym.lookup->insert(attr);
                return *this;
            }

            symbols& sym;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(adder& operator= (adder const&))
        };

        struct remover
        {
            template <typename>
            struct result { typedef remover const& type; };

            remover(symbols& sym)
              : sym(sym)
            {
            }

            template <typename Attr>
            remover const&
            operator()(Attr const& attr) const
            {
                sym.lookup->erase(attr);
                return *this;
            }

            template <typename Attr>
            remover const&
            operator, (Attr const& attr) const
            {
                sym.lookup->erase(attr);
                return *this;
            }

            symbols& sym;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(remover& operator= (remover const&))
        };

        adder add;
        remover remove;
        shared_ptr<Lookup> lookup;
        std::string name_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename T, typename Lookup
      , typename CharEnconding, typename Tag, typename Modifiers>
    struct make_primitive<
        reference<symbols<Attribute, T, Lookup, CharEnconding, Tag> >
      , Modifiers>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef reference<
            symbols<Attribute, T, Lookup, CharEnconding, Tag>
        > reference_;

        typedef typename mpl::if_c<
            lower || upper
          , symbols<
                Attribute, T, Lookup
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type>
          , reference_>::type
        result_type;

        result_type operator()(reference_ ref, unused_type) const
        {
            return result_type(ref.ref.get());
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename T, typename Lookup
      , typename CharEncoding, typename Tag
      , typename Attr, typename Context, typename Iterator>
    struct handles_container<karma::symbols<Attribute, T, Lookup, CharEncoding, Tag>
            , Attr, Context, Iterator>
      : traits::is_container<Attr> {};
}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif


/* symbols.hpp
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
*/