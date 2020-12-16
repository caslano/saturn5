//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP

#include <boost/gil/color_convert.hpp>

namespace boost{ namespace gil {

/// This one is missing in gil ( color_convert.hpp ).
template <>
struct default_color_converter_impl<gray_t,rgba_t>
{
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const
    {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t  >::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t >::type>(get_color(src,gray_color_t()));

        using channel_t = typename channel_type<P2>::type;
        get_color(dst,alpha_t()) = channel_traits< channel_t >::max_value();
    }
};

}} // namespace boost::gil

#endif

/* gray_to_rgba.hpp
exK1Nr3JY5XqOGaro/pk4WY37YFz326H2mfjfZt/WH5210Aa7R1jVSz1fWVuClZFoSRJ7WCpluGnrxQJzYlAgAhxBA/2A58ys9ihv/NiiDxg4nOLJzuzVb99IAWOYjgsmcrsXiKpvSMX1nbri76s+TXzSiIqS/Kag3NpmKL//0uWgnHGME4LEx/DxFuYhBgmwcK4YhiXhakXw9SzMIkxTKJWL4nyejuyEmHPrvZVYbfAj6K1NFRJhp4vZ/vUDLTxiMDZ3P/ARKTcdz+yyTeaw/lO3GP2uEj6oJEvdBZSNK1HiP5RSI6LsFOggWW9ALxQG4eBW3lJvHVzPh8uHLt3Mu7t8GRcSIOrNhDEgTCz2PtFnnh4qPqa/cg40hL0CvUg/YU/3HAh1MYk2n8Dopr7wMqcbviuFv9XldeQoaqCFqfG2AzVGW8pQ5X3yTBv5gt9l0+Dj//KC/3mg2BR6D1P1rk1GHEb2IC9Az9CInpcheuTta649nF5QryGtkvgG+NOa+9s2IPbS/OxMJ+ZMJVD5mm5S14hcvB5ay6Qt6id70ViUIVIyeK1BU4LT5umaD4in6lG6hu7vwLhyTrvKsTLl9z96Zb82Wn569VwI/eiDOScXzrcidC+eOh4EXnVLR5wlBrXicQ6GlTt1zb5wd+T3IuoMMG4MOztl/YbiUgWxE7Va2xuLtKL/BflEf6mfFXv++lwxf4VWFvHedqNfVVZ5DrLc5rQUOVoAGJfsLDX14zyJyvKYsvTI8IBauXCesR/m+V1Acs2Yni1/qp0Iq4ThBZ2h3nncg37u9MuLLEXWSl8C6ymS+w5FnZXrbDxFvafDKsEeibxPw1T/HLgxQ5tXugz2ASf2jlmXyKkgVnkd63AU8nfKT8i4YOnUqdBC395LNAjViAQuEyMCqQvwvLYvo/e3MBuJIqkDYXgmGwfmnFWlNaIsutU4FMtoCZXZPk1keQ+XWK8w2q2zPLL1JvWV0MRiRX82qEmdeFf6PZuWngYkgwfG4eVEIUZaID8xeNf7fquNHlozj5qh8PgKkQTIsV9V2i4+xjuvPz72x//KlTeacMuEw8D5c4JlYmIcHZ1w74owdUw88LDUgDJHCEoIJTv9kiwoBUsx1G7/W+z8O3I5imfd8qg893zm4FXQd+B8GUj9MMXmiLYfrCM515dkJC5Zsb06dP7FxckZOWBW17veBgn32or6hM2NO5UCV07+ZhJM7cVhMg0R7Bs6vLvjOugqVlYNN2rR7XvXhi/EULil+atJSPTUzyq/UAw5NsjMZ2fPM/mOwpLcxPgaFxYmh8fWu9bH7bW9PS84tzfQhuCB92+9d8l+NYfdPoarmeM3yzP30PrgwfjEcEJzwRfw53ANwe+Ct9z8I3mB79zBB5FlD1Yh7NW435rS/CLfkitHpgQCJGEDyL4HN7iImdEFDr/aag2Skd88RgjJGuTam4iez8HFCQlrsjTt4231JW/r6kfeRWfnjw00l5km74eu7VapnMlD6918Iv3BPyKbiU8Mgnt5a9iUaM13eHBojwzL2T4He/Vr98bOsLvZP6ZyD/T+ecG/hnDyHzNxPNcnAvnz2+jVFpiFof1CLOMB+cyeT8q1gumfS36eV5fbtF3NA0mynnMJ59jsEgBVan/23wyMTPyBj/+yMv8TI48x8/EyDJ+bog8ws+YyP38TI+E+Blv7pd0tIJhKi9CFoGrvaEfkWj4hqhIOnRhUesfikbDD7DZbsWjfrP2R3hlp/uTGP4CiI54+Mwf3XFDCPUksgG4SPUWlnndnuO4j4vflJdTMZvXYztfkx282woZ3aZTf1yPXSIHGa0NWUkZXryGyqA8jAaeeXG8BK7KQ+DGCCw=
*/