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
yhz+3E2eJYUU9BJNDz+CWWvCSdyqhh7fBC4v7qTuui5O9K3z8pn93UeNdqxnhb92z3ntaEVSQJuUFQ6Q0T5ZuvQNxhjrRRu23ZXx2U1nX/sAxzNT1lUR5lhA52AGt3c7lk967YXsWhR1F2aZALCZLbosWRum2NGY7B7leGbTLAgarERxjqoM9aGfDec5zkpsFWWbvgii9n7/N3yfYK3ArpMkoGlNUO4O69qA5Wdj1pWQ/NJaGaEugijbJyc4rkYUkD1xE6/pLveWtIlxFr/xeWHbZkGTizNHW9B0i7SawnWjcxzP6bABP5VtpMbZmU+dX9pTPbqFqErEI+Z1LLTpFMvo6H5rDsF9ID/Kcc03edXWSZL268qRZja0z3u0W5En4GVN1VwE7fkxs6H96LdTnt97IbMihykLTsITtspfAdZ7KxnNRPhlp2Qg+Afo5x97JTBvTf0V08d/cV1yPimKpI5w7O8hBmcDRgID/6jQrMGr+m8yyDyosg77vVssyTkRpwXFA8xS5cEt0fztjXwce/dQiSxbZNoimj5/uOXvfDts3oE7wBtf09oBldE5NW02CciJc+4R7dCsX6/NkI1arCNKpbVhbZiG3elluLjQ6bgNswcqjqMWWZOFbYj+j/f3KMk4JeaesOk++Kq+DRvSeIZDJhMwqVKFXiDAxGiiKyxohnB6+uK5mK+JJi4SaGaNcEoc1uGcuc/x+hsIXHAGMkpjrevgfv5RXImzNJ4be/kOowb2PSg5WoHz3yV/oUcjEpRhMUnTitEYKm8jK1N5dDLwkkhWnaIzPaDzxgGdGBaWqily8chJOtMDOtLbR13cNuSqItZAaGIffcCjk4i4C7Iwh4XrAdb/RvbKi/YuNzYJG6vyHE/PlllTyrQTnk3UzM+XBvMDZaELqyqz+oKuZWzIZt+8lPfnVJjGWRwFkdg+OPT1+O8Bv59nM2rbJO9UjDV5XtLN9Hla8/XSA/w18Cded65tpazoZT7lPziQsf8FWC5jVzHs/ZQIrFLQelmbkYt6WTIbQfom3xhH8928X7MyCIO6BgdbY4t739qsrjbw6S2StGylt+zkEWv705zGPcnOlcMMDRps0dk8OFcbjF+RhTLNfBremnO+zGu87lyIiS2yPCKtZc1cMM4aOluA9WwSdZE1ObvOtJ5UoJf5d0x3/L13Jid5XkPiqwT5zPZSklXO3Hw9k9PDlXzW5jlWUWdj75m8vOaELfXYEbunvtEPPLtZWucpDlm6+V0e7x/sWbuZzekLeM+HJwU/KnEutspORvGgOrcQ3omHI+A21ol12GJ3xdw2OxNLLLagacTK1p69w+us/d/rayWipK6DoK4utq8PNW2/uh+Dl0ON7CQuiv7ru0NH/fHf7BIcd4RxiXB7H2KhMb/52ekT+Gv3Ucp1PtJpik6TO3P/uD5/q+gTKkaFzm4MpvPxqZ7Lx63q0jrosKe1q4t/Zj2VtwnrKYONjLIYi6UITcoxT1RNh4Prbb5rtjrFOLA8fx/luObqrqxjOGQod2NN2OpVn+awWJIygkE0LypLVweu0F6gkBrtImga4+dJ/Q7vbya7tI1ljUh261Y0tVeYtXwN/122tirDrsFEPwDQ9GLodi+c9n7Xutu6A7P2EDD8+WGc7skkqMMWYvKMzXtqeNgjOFwr2ihJ4zRN1VGTd2dnCPfWeXuuG/x7Hn6ZyTKrs0TMacCzBv+Bjz9L6iLJ4s7inxvgt75gfCzmZFCENRQVoZz1FbSdL8FhITZXbdCCDrRo5U3bDzZWrq6MK3osFsg6eiiJrosd4rjCDA2Og6TNpNqrx6cDScya/Y5vb02CjmSK7iLjTYXNGe71v5FxWLeteCA=
*/