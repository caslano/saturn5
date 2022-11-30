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

#ifndef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
            literal(literal const &) = default;
#endif

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