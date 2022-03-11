///////////////////////////////////////////////////////////////////////////////
/// \file literal.hpp
/// The literal\<\> terminal wrapper, and the proto::lit() function for
/// creating literal\<\> wrappers.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_LITERAL_HPP_EAN_01_03_2007
#define BOOST_PROTO_LITERAL_HPP_EAN_01_03_2007

#include <boost/config.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/extends.hpp>

namespace boost { namespace proto
{
    namespace utility
    {
        /// \brief A simple wrapper for a terminal, provided for
        /// ease of use.
        ///
        /// A simple wrapper for a terminal, provided for
        /// ease of use. In all cases, <tt>literal\<X\> l(x);</tt>
        /// is equivalent to <tt>terminal\<X\>::type l = {x};</tt>.
        ///
        /// The \c Domain template parameter defaults to
        /// \c proto::default_domain.
        template<
            typename T
          , typename Domain // = default_domain
        >
        struct literal
          : extends<basic_expr<tag::terminal, term<T>, 0>, literal<T, Domain>, Domain>
        {
        private:
            typedef basic_expr<tag::terminal, term<T>, 0> terminal_type;
            typedef extends<terminal_type, literal<T, Domain>, Domain> base_type;
            typedef literal<T, Domain> literal_t;

        public:
            typedef typename detail::term_traits<T>::value_type       value_type;
            typedef typename detail::term_traits<T>::reference        reference;
            typedef typename detail::term_traits<T>::const_reference  const_reference;

            literal()
              : base_type(terminal_type::make(T()))
            {}

            template<typename U>
            literal(U &u)
              : base_type(terminal_type::make(u))
            {}

            template<typename U>
            literal(U const &u)
              : base_type(terminal_type::make(u))
            {}

            template<typename U>
            literal(literal<U, Domain> const &u)
              : base_type(terminal_type::make(u.get()))
            {}

            BOOST_PROTO_EXTENDS_USING_ASSIGN(literal_t)

            reference get()
            {
                return proto::value(*this);
            }

            const_reference get() const
            {
                return proto::value(*this);
            }
        };
    }

    /// \brief A helper function for creating a \c literal\<\> wrapper.
    /// \param t The object to wrap.
    /// \return literal\<T &\>(t)
    /// \attention The returned value holds the argument by reference.
    /// \throw nothrow
    template<typename T>
    inline literal<T &> const lit(T &t)
    {
        return literal<T &>(t);
    }

    /// \overload
    ///
    template<typename T>
    inline literal<T const &> const lit(T const &t)
    {
        #ifdef BOOST_MSVC
        #pragma warning(push)
        #pragma warning(disable: 4180) // warning C4180: qualifier applied to function type has no meaning; ignored
        #endif

        return literal<T const &>(t);

        #ifdef BOOST_MSVC
        #pragma warning(pop)
        #endif
    }

}}

#endif

/* literal.hpp
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
*/