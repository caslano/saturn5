///////////////////////////////////////////////////////////////////////////////
/// \file debug.hpp
/// Utilities for debugging Proto expression trees
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006
#define BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006

#include <iostream>
#include <boost/preprocessor/stringize.hpp>
#include <boost/core/ref.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/fusion.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

namespace boost { namespace proto
{
    namespace tagns_ { namespace tag
    {
    #define BOOST_PROTO_DEFINE_TAG_INSERTION(Tag)                               \
        /** \brief INTERNAL ONLY */                                             \
        inline std::ostream &operator <<(std::ostream &sout, Tag const &)       \
        {                                                                       \
            return sout << BOOST_PP_STRINGIZE(Tag);                             \
        }                                                                       \
        /**/

        BOOST_PROTO_DEFINE_TAG_INSERTION(terminal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(unary_plus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(negate)
        BOOST_PROTO_DEFINE_TAG_INSERTION(dereference)
        BOOST_PROTO_DEFINE_TAG_INSERTION(complement)
        BOOST_PROTO_DEFINE_TAG_INSERTION(address_of)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_not)
        BOOST_PROTO_DEFINE_TAG_INSERTION(pre_inc)
        BOOST_PROTO_DEFINE_TAG_INSERTION(pre_dec)
        BOOST_PROTO_DEFINE_TAG_INSERTION(post_inc)
        BOOST_PROTO_DEFINE_TAG_INSERTION(post_dec)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_left)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_right)
        BOOST_PROTO_DEFINE_TAG_INSERTION(multiplies)
        BOOST_PROTO_DEFINE_TAG_INSERTION(divides)
        BOOST_PROTO_DEFINE_TAG_INSERTION(modulus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(plus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(minus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(less)
        BOOST_PROTO_DEFINE_TAG_INSERTION(greater)
        BOOST_PROTO_DEFINE_TAG_INSERTION(less_equal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(greater_equal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(equal_to)
        BOOST_PROTO_DEFINE_TAG_INSERTION(not_equal_to)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_or)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_and)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_and)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_or)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_xor)
        BOOST_PROTO_DEFINE_TAG_INSERTION(comma)
        BOOST_PROTO_DEFINE_TAG_INSERTION(mem_ptr)
        BOOST_PROTO_DEFINE_TAG_INSERTION(assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_left_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_right_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(multiplies_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(divides_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(modulus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(plus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(minus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_and_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_or_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_xor_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(subscript)
        BOOST_PROTO_DEFINE_TAG_INSERTION(member)
        BOOST_PROTO_DEFINE_TAG_INSERTION(if_else_)
        BOOST_PROTO_DEFINE_TAG_INSERTION(function)

    #undef BOOST_PROTO_DEFINE_TAG_INSERTION
    }}

    namespace hidden_detail_
    {
        struct ostream_wrapper
        {
            ostream_wrapper(std::ostream &sout)
              : sout_(sout)
            {}

            std::ostream &sout_;

        private:
            ostream_wrapper &operator =(ostream_wrapper const &);
        };

        struct named_any
        {
            template<typename T>
            named_any(T const &)
              : name_(BOOST_CORE_TYPEID(T).name())
            {}

            char const *name_;
        };

        inline std::ostream &operator <<(ostream_wrapper sout_wrap, named_any t)
        {
            return sout_wrap.sout_ << t.name_;
        }
    }

    namespace detail
    {
        // copyable functor to pass by value to fusion::foreach
        struct display_expr_impl;
        struct display_expr_impl_functor
        {
            display_expr_impl_functor(display_expr_impl const& impl): impl_(impl)
            {}

            template<typename Expr>
            void operator()(Expr const &expr) const
            {
                this->impl_(expr);
            }

        private:
            display_expr_impl const& impl_;
        };

        struct display_expr_impl
        {
            explicit display_expr_impl(std::ostream &sout, int depth = 0)
              : depth_(depth)
              , first_(true)
              , sout_(sout)
            {}

            template<typename Expr>
            void operator()(Expr const &expr) const
            {
                this->impl(expr, mpl::long_<arity_of<Expr>::value>());
            }

        private:
            display_expr_impl(display_expr_impl const &);
            display_expr_impl &operator =(display_expr_impl const &);

            template<typename Expr>
            void impl(Expr const &expr, mpl::long_<0>) const
            {
                using namespace hidden_detail_;
                typedef typename tag_of<Expr>::type tag;
                this->sout_.width(this->depth_);
                this->sout_ << (this->first_? "" : ", ");
                this->sout_ << tag() << "(" << proto::value(expr) << ")\n";
                this->first_ = false;
            }

            template<typename Expr, typename Arity>
            void impl(Expr const &expr, Arity) const
            {
                using namespace hidden_detail_;
                typedef typename tag_of<Expr>::type tag;
                this->sout_.width(this->depth_);
                this->sout_ << (this->first_? "" : ", ");
                this->sout_ << tag() << "(\n";
                display_expr_impl display(this->sout_, this->depth_ + 4);
                fusion::for_each(expr, display_expr_impl_functor(display));
                this->sout_.width(this->depth_);
                this->sout_ << "" << ")\n";
                this->first_ = false;
            }

            int depth_;
            mutable bool first_;
            std::ostream &sout_;
        };
    }

    namespace functional
    {
        /// \brief Pretty-print a Proto expression tree.
        ///
        /// A PolymorphicFunctionObject which accepts a Proto expression
        /// tree and pretty-prints it to an \c ostream for debugging
        /// purposes.
        struct display_expr
        {
            BOOST_PROTO_CALLABLE()

            typedef void result_type;

            /// \param sout  The \c ostream to which the expression tree
            ///              will be written.
            /// \param depth The starting indentation depth for this node.
            ///              Children nodes will be displayed at a starting
            ///              depth of <tt>depth+4</tt>.
            explicit display_expr(std::ostream &sout = std::cout, int depth = 0)
              : depth_(depth)
              , sout_(sout)
            {}

            /// \brief Pretty-print the current node in a Proto expression
            /// tree.
            template<typename Expr>
            void operator()(Expr const &expr) const
            {
                detail::display_expr_impl(this->sout_, this->depth_)(expr);
            }

        private:
            int depth_;
            reference_wrapper<std::ostream> sout_;
        };
    }

    /// \brief Pretty-print a Proto expression tree.
    ///
    /// \note Equivalent to <tt>functional::display_expr(0, sout)(expr)</tt>
    /// \param expr The Proto expression tree to pretty-print
    /// \param sout The \c ostream to which the output should be
    ///             written. If not specified, defaults to
    ///             <tt>std::cout</tt>.
    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
        functional::display_expr(sout, 0)(expr);
    }

    /// \overload
    ///
    template<typename Expr>
    void display_expr(Expr const &expr)
    {
        functional::display_expr()(expr);
    }

    /// \brief Assert at compile time that a particular expression
    ///        matches the specified grammar.
    ///
    /// \note Equivalent to <tt>BOOST_MPL_ASSERT((proto::matches\<Expr, Grammar\>))</tt>
    /// \param expr The Proto expression to check againts <tt>Grammar</tt>
    template<typename Grammar, typename Expr>
    void assert_matches(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, Grammar>));
    }

    /// \brief Assert at compile time that a particular expression
    ///        does not match the specified grammar.
    ///
    /// \note Equivalent to <tt>BOOST_MPL_ASSERT_NOT((proto::matches\<Expr, Grammar\>))</tt>
    /// \param expr The Proto expression to check againts <tt>Grammar</tt>
    template<typename Grammar, typename Expr>
    void assert_matches_not(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT_NOT((proto::matches<Expr, Grammar>));
    }

    /// \brief Assert at compile time that a particular expression
    ///        matches the specified grammar.
    ///
    /// \note Equivalent to <tt>proto::assert_matches\<Grammar\>(Expr)</tt>
    /// \param Expr The Proto expression to check againts <tt>Grammar</tt>
    /// \param Grammar The grammar used to validate Expr.
    #define BOOST_PROTO_ASSERT_MATCHES(Expr, Grammar)                                               \
        (true ? (void)0 : boost::proto::assert_matches<Grammar>(Expr))

    /// \brief Assert at compile time that a particular expression
    ///        does not match the specified grammar.
    ///
    /// \note Equivalent to <tt>proto::assert_matches_not\<Grammar\>(Expr)</tt>
    /// \param Expr The Proto expression to check againts <tt>Grammar</tt>
    /// \param Grammar The grammar used to validate Expr.
    #define BOOST_PROTO_ASSERT_MATCHES_NOT(Expr, Grammar)                                           \
        (true ? (void)0 : boost::proto::assert_matches_not<Grammar>(Expr))

}}

#endif

/* debug.hpp
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
*/