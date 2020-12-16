///////////////////////////////////////////////////////////////////////////////
/// \file at.hpp
/// Proto callables Fusion at
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    struct at
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename N>
        struct result<This(Seq, N)>
          : fusion::result_of::at<
                typename boost::remove_reference<Seq>::type
              , typename boost::remove_const<typename boost::remove_reference<N>::type>::type
            >
        {};

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq, N>::type
        operator ()(Seq &seq, N const & BOOST_PROTO_DISABLE_IF_IS_CONST(Seq)) const
        {
            return fusion::at<N>(seq);
        }

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq const, N>::type
        operator ()(Seq const &seq, N const &) const
        {
            return fusion::at<N>(seq);
        }
    };
}}}

#endif

/* at.hpp
w33D8+W9zM9SZgHjM3xPw7y6VEcwnp8+NUd3pTqCuTA70e6v/hRPGI/ZBNMPaD5Ew1ozC7XZPltZKqwes78qbnVTlgXjs2rWrvu7qA/C+OzY27gjzXcbVEZLZj3fbBikzB9Wn9fR2q870xlgHzBz2bXwD+p1MBNmuX1Of0lngHXge5n4HcW6CGbKa6y7xwFlJTBefyX7tn1B9VBqOFM77+zWTJkXbCTrS1f67rhEPQvG9+mw9eUEZckwXrdxNv45NKtgfL4HnjkXQPP2geEz57qXHVdmCuO9bv0XQ5yobmE+zNxbP1pGsYbxe+9+uBnlUjSsK7OWLfKOKMuA8XqItghfTfkC4/XwgdfEk3QPsBr8/r74gOJZop3htmOCFZ3voeHZ81/2OUV1BOP10HXMsLV0RzA+i5eV9X1JdQTj+XLl5t5f6ewwXrdTklpVod4D68R7+Zf7k+nsMDNmJq0C6I5yH2qf9Z9do1ll/sgwz6Yn7aAac4RZMjt588s/6HyaVd+zhc7gD+N31PGN12maVTB7Zg1CkgqUhcO8mA09We+wsiSYMbM/xlZS7ibDeC8Yv+CJubJ0WA3eC75q+RnlEsyC2WlTz1XKcmCmvJfv/HkgzT+YFbMlKzx3U0/Wzj5u5oeUS6UwG2ZTe20cQDVWZpgvw5dvmk95ptnqfu2CqE/AeDxfJww4r8wHxs9wwmN7X8pBmDPvBccP2FBtauvcL96lvUTA+Bku/mtTL2Ux2j5d+12Ko9kIa8nrvax1E2WZMJ6DMasG16TchTVn1trkTANlFdr72iVv/5nq9rHh9+n00+6m1JdgfF3veyapFDPYENZbKwY8v0RngPF7X+Fy6SuaDzBffoattyiehbBqzJb/coJqugjmzfOlZcv6NMeeGObSk7tf+FNtwpoy65P9XTbVH6wmn5vmZ2YqC4LVY2ZTURlNdwsb+h9zwdlhb3469A/qL9pejpi/rEW1otlfNWvTTM3TrNpN/y7KCmC8prdaLhtLMdPWzV3t8inVGMycWZndHOrzZTATZkk/Tz5B+aK977zv8tHKKmEWzO6v/3kU9cinhvlp9vCFN90DjN/f9aVrq1OsYa7M3A7/XFdZFMyZ13T8PuoFSTCe8zX3hznTPcB8mI3MMZ1L54O5M0u59Nlv1CfKDT+fXXqcNp5yHubM72HAwD3KQjR7vOfIQZpVMEtmq5KHFFCtwHis32wvnqosEcbv1utEjgX1chj/Ht66Yrwb5QvMidfD6cTndHaYDbPFHVyu0P09034fzM50nDJ7GL+jB93X08zxhTnyvD48cifFBVaTv+9+2wk0x2C8NutdHVZGcdFsUOqHvyvbD/NkNvj0km3UJ2A8Zn0H7nqprARmyWdcl8EdKK9h1nyfvfe+prny3PCZ/wx2aUVx0az2T1kfUi5p9vC+xUrqrbAuzNacCxlKcdEsLeKrltQ/YTwunZMLjlJ/gbVntmlrxWqamy8M790ks6gG9U9YI2Z+5r1zKedhdsw+G9CO4hkEc2FW9/BBF2UzYM48r9/G0t0mwnj9VRmW4aMsA+bJ8+zTBeHUz2CtmO357ZsxdIYKw+9O43fMpbnpD3Pm+Xml5yqKNaw+s3tT86oqi4U1YXZuqzn18lSYG7Pwp4HUy3Nh9swW2n3yPZ1Be1+z7H1UK0YvDXOw1ZlR1+h8MCtmAV82sqJcgvF7WOSTQbUSAHNi1t9hxw2aY7CGzDrFTnqkLB7Gc6K42e9nlaXBPJjt7116Wlk+zJGZy6ri2jRzYPwexv7p40s19pdhfp74MOmeMjdYB2YNpr/4TlkojL8vqnFhGPVdGM+X69cGPKf709Y1vOhEeZ0N4/ew7vduS6k=
*/