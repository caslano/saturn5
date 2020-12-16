// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP
#define BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP

#include <boost/convert/base.hpp>
#include <boost/convert/detail/config.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace boost { namespace cnv
{
    struct spirit;
}}

struct boost::cnv::spirit : public boost::cnv::cnvbase<boost::cnv::spirit>
{
    typedef boost::cnv::spirit             this_type;
    typedef boost::cnv::cnvbase<this_type> base_type;

    using base_type::operator();

    template<typename string_type, typename out_type>
    void
    str_to(cnv::range<string_type> range, optional<out_type>& result_out) const
    {
        typedef typename cnv::range<string_type>::iterator                  iterator;
        typedef typename boost::spirit::traits::create_parser<out_type>::type parser;

        iterator    beg = range.begin();
        iterator    end = range.end();
        out_type result;

        if (boost::spirit::qi::parse(beg, end, parser(), result))
            if (beg == end) // ensure the whole string has been parsed
                result_out = result;
    }
    template<typename in_type, typename char_type>
    cnv::range<char_type*>
    to_str(in_type value_in, char_type* beg) const
    {
        typedef typename boost::spirit::traits::create_generator<in_type>::type generator;

        char_type* end = beg;
        bool      good = boost::spirit::karma::generate(end, generator(), value_in);
        
        return cnv::range<char_type*>(beg, good ? end : beg);
    }
};

#endif // BOOST_CONVERT_SPIRIT_BASED_CONVERTER_HPP


/* spirit.hpp
ETwBGZ85BKesCm/CZw3HBez5B3JCD/a/wLnUIo+K/2rnz9/HwTDOpYB81SxwIBW73XQY7O6Bz72ObfWF/+9BX9LBbzj8D2DZH5zlaGyxButedQKOfhFuRp79iXnwVtb3WTC8+Wn8/p+8m/oGDhRArNqEc3kJjMKHzSLH2ox1XOgGNhagDy+gc8it/gbOK5l4Mlm9D6h+hrgxhDzFJPwcY1deg12Dn+fgMS87OYNA2jJOva7Y1g5iCc4xNwy/gU69WJ/1RJGbPQN+kFP1+5z+ncHpLZzhLHQiWNwnkzvDF72ELT1A7nUxck95HptLIBezCF3YRs55AfcCrfBn4MPMicQ75bAB6u7uDLY2Jp7DFzWpwV3oKfYRjl+7DVtYhw/KxrZ+wQ+z/5HV4GDn4AuMd+0z8nidmXMz8zcHG5/lXLkjaUwupBVvvi5zn5hzjPK3yKvXZz/oSD+4Y63y+FbObDc2PO8QZ0Ts3GMuvmwuOAjfDQ8Gs8O4u4Yn9+RNx4evw5MP23hrgY69TGx4Cbl0AZsGs443yF+GM0d9uEtHuP5L2E8x3BO8e4x8xzfIZ24i+2uBDieRt/4eH3uSWIp2996GP+T3sU3xt3zWIaAyPCEZHWgIRsFNyv8L//MOvBm8/DMFfrcDG44kbgPHJ7bhLKuChdXhZh+AUyJ/dhE8qUCuSbyHhhuOQB9XpiPrpsj2Zez2fvGZAt61TkamYfwOviX8BU4UYs+PoYOPY2MfIHP0otpZZNSIWHGwuH8H/+G51cDVzkfxCfitt5Dn+EP4qwJwCf2Ma4HtI5s5u5HjfegJ+vkqPqTmUn5vgn0uwC+Cl0Py4WOrwGpyH0vD8Ino0N7R4NUpdHQIuB3M34Xwy3jiZXz3TGyQpwt8phoMHQr/G4uvcOKPZ4ALB7ElsG1udWI4sKFtFHHgcPC0iPiJ8398J+/GqiNnjLMUX3yqHv5lGjLtiC2exBdxBuK/ETwUPYv1x9b7ET/8EyxsQ+yPTjxgpy/+Km8svvB+zpF71CrMOxw+9NluYoNE8NiOnuE/24eTu6zNeOTud18AL8GK0Hfg3gXoBHnCB0aiZ+J7Jn+Ce9VGHrX9lDhhdgQ60IhcIv7/ZXBpYxwYwT4j+4J9n2Br6FF6OfT2NLm+HeR46ONYSA4WfDsAL3EKPRoFLuBvmvzMWdyNPKrwd09s8BnO1c6Zd0a/yEWdbYjfCSDGgHcd/4s9jwWb8KMnj+FbH4Vf9iWegjvtWEZeN538VQo2QLwQjc4d4RwzsKfb1iLzh9Dvg5xPNDyBvPI5cP+9B9CdUv7dg/VFgCfEM9UmcJ74xtfY89ct0bmX8dft0c8OcPCLxPf4hlrI6zFkt5A7qwj8S7vqYNAZsBQfWI94/2fO+ALzNCf+PLmHv1fCb7izeOM28L0Cvp95u2UxPzxqH5i8DR+cAEbOGEjcepW5sPn94BZqBs/nOyCRz1ez4a747br3BhAj4D9SiUeIud+OgbM8Tg58Oz5qLziZh65h533x9/cS862uRw4/Cb6GTae34t77SeynhHs7fOHFPGwEbHzoOWL/J8AJ5Ci+wyLtCezrK/LJHxID1cTm8P0nmLdRXfjSJtr9iJzRm6n57CEGH46/v45PV+KKM+DlRnAAn9kKfIkBB691AEvQ/+7kRh+H4yZPA9/Fd5KvAAfhspPgFQ7ip+cP8e70LnQ6BDkvBE/m4QffskGqiaefIg+PzgVj/zWucZb/4L1ed2Iz/ND0t+Ebg4g/N4LxNnS5P3chy8m7E8e+RmwxB470IXzz9EfoVBv4BPL44Ucw7zL5KvITXfsRA2CHdVzkSJLgBlewlcXI5G2hc8SYYMozb8KjVxHfR3M=
*/