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

            BOOST_DELETED_FUNCTION(ostream_wrapper &operator =(ostream_wrapper const &))
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

            BOOST_DELETED_FUNCTION(display_expr_impl(display_expr_impl const &))
            BOOST_DELETED_FUNCTION(display_expr_impl &operator =(display_expr_impl const &))
        private:

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