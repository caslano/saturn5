///////////////////////////////////////////////////////////////////////////////
// value_accumulator.hpp
//
//  Copyright 2005 Eric Niebler, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_ACCUMULATOR_HPP_EAN_03_23_2006
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_ACCUMULATOR_HPP_EAN_03_23_2006

#include <boost/mpl/always.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    //////////////////////////////////////////////////////////////////////////
    // value_accumulator_impl
    template<typename ValueType, typename Tag>
    struct value_accumulator_impl
      : accumulator_base
    {
        typedef ValueType result_type;

        template<typename Args>
        value_accumulator_impl(Args const &args)
          : val(args[parameter::keyword<Tag>::instance])
        {
        }

        result_type result(dont_care) const
        {
            return this->val;
        }

    private:
        ValueType val;
    };

} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // value_tag
    template<typename Tag>
    struct value_tag
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // value
    template<typename ValueType, typename Tag>
    struct value
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::value_accumulator_impl<ValueType, Tag> > impl;
    };
}

namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, value, (typename)(typename))
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, value_tag, (typename))
}

using extract::value;
using extract::value_tag;

// Map all value<V,T> features to value_tag<T> so
// that values can be extracted using value_tag<T>
// without specifying the value type.
template<typename ValueType, typename Tag>
struct feature_of<tag::value<ValueType, Tag> >
  : feature_of<tag::value_tag<Tag> >
{
};

}} // namespace boost::accumulators

#endif

/* value_accumulator.hpp
feGbewjcPX9QpoC705bjLJiOLu7wR6rIkc+OSOQScgxkR2kkRI6+cIz4BTpp5FzeqOTCeS85feTcRc6fkXMQOXeQ8+fkZDShH9O89Ji8WOjtvIvH/ElnMp3Ja+aqKexXMoXdt4GmsB9iCvua2Xzs3riCULPDazUdaWTw+fdAtGfntGreTveAl1mL9zmqW4g/LVfKPJofM8m1SjacnIPtkp1G2bOx4VzhIdfm4X2z9NhOWguUTTb+qUzReI8MxMd2+jiSgKH7KF7dS89BGQJ4raBzPPdxabEBmWn5A9FO6l/OoOTfrvR+AzP/I7HXu+KfDu2Cr5623s346utvToILL5wHuPDIZ+Gr32xmX9A9vvo60Y9dn5ze63O7ppfeKb21o7pN71aV3qmS3nDa4N8NJQgnx2u79rjTI92VEraSqx711aOZd3very61LjzdhirHeb+glYeLZxUBP3zlCbZqcrDCD1+WB1HMGYLlxthBqYDfPxjBgN/fCFeNyiDRp+qosDHGRTnrJMX5+Zl7fvYS/1mS3dtDLEDwi0YkAMEjauNzW4kFCH5Bz+7uyBvzD9Pl1eT589rTusX7Lm4RTeWbfByKdfslxvuuOKYz3vfwgQI00JYM37nh3ATe94Szu8X7fifz0PG+uz/v+uMQheW5i/luMwNu+7b36crg5XrRbB0XxIJKFfoi1XPd3j0KEviK3qjnRgDE132pg6zu19McxR8LBcRfrkdwjjfk2l3pBFT1mGZ3Es7xVFEJ9zTfPJo72BBGNn7GQjZ+Gn2ETY1foH4yEllISS4qoZIczvU15fzTl4zX/Nc+dj2PUPV8pKgCT0c9cyVvDMa0DPPY4y32OjKJvcOKJ5I8nz54ajJ/tX2lnquOS8GTfmut1PNghSet6vmGow6OJx0618aTfnegVabXig8XnrTCPzjFelS1otv3SZtOseQzy9+Tiv+g4if8vSn+S0+x8AN6Aj/APyAJPwAESGgrsO+E67xMdt100iHjB4g+c7DiD2JiMZ03n0nPhRt+bzlhb62ZoUSZP8pLvu2n0HEsfM603gBGY0wTdL3fMyzbSPyPWHLfvNWd9vhgNgfJVju3os9R0xb+zuJ8u5vgUJzzGuTgnPu3X8tH+XhhqAC7cvE7gf1Kr22/eI+W7ag+2YJF64muEN/cfiTKZz3G1xskVaDhOASUi0lLMYeyPf5u2Y6dQImeLhlqaxZI0Sa1kDz1K3NPfyrYIcH7HKD+7z+ZSxcwtlDpTkLaGWoS/zP3+LNj+jt0Zmka/dkQgisRCL2RKvrvYgiGkZEoEp+8hY3K3HJoJ3ppSA3hQvHX11yjWnC7MP6rZmL8MTbNLk5KMZCpZasWCkTtT0PL/pyNlvTXdSnnWWnVSarA72O00s2QNhi3vYChyk8Rz6OtyLdZKzGRzKfLpFF2NbnxiF77HnulD5BCcjOtCz9F1JKW6v5BYyMSlF3LLraF2aXVXijRf98kbXo2TmvUdNacWDb4Fj/NZF9uiab2A8weVVpjcv9tHMwFtgwTd4se2C/QnYvrPTByMy8/nTeMARzq+7ER2sR64OyM6hKdTozwTDOpeJUZEHeS19S0OIY7ybUxfTA6yXRzcr9Ef5So/i5R71NRxyZHnWz6kqLyOYIXigB8kKnALETRai9l9HdUt3og6htMnUDUV4TqN9dC26PVTpTT3nPXSrU/fe7nwQU/1D8ZP1fmWfNX9WAUrqVRCtfGhbuARg4GkDnGY09AdMzOHwd8/1ulaPS46IZj0qjZUHE9TC+vnxUVNOPkrzHUsLpUtNsVyBZjagediP3NnVyRG/gD1siUxaGsj53kkaUnynnTHs1oE9MYKuqIEFbK3tg=
*/