// ----------------------------------------------------------------------------
// Copyright (C) 2002-2007 Marcin Kalicinski
// Copyright (C) 2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED

#include <string>
#include <boost/property_tree/detail/ptree_utils.hpp>

namespace boost { namespace property_tree { namespace xml_parser
{

    // Naively convert narrow string to another character type
    template<class Str>
    Str widen(const char *text)
    {
        typedef typename Str::value_type Ch;
        Str result;
        while (*text)
        {
            result += Ch(*text);
            ++text;
        }
        return result;
    }

    //! Xml writer settings. The default settings lead to no pretty printing.
    template<class Str>
    class xml_writer_settings
    {
        typedef typename Str::value_type Ch;
    public:
        xml_writer_settings(Ch inchar = Ch(' '),
                typename Str::size_type incount = 0,
                const Str &enc = widen<Str>("utf-8"))
            : indent_char(inchar)
            , indent_count(incount)
            , encoding(enc)
        {
        }

        Ch indent_char;
        typename Str::size_type indent_count;
        Str encoding;
    };

    template <class Str>
    xml_writer_settings<Str> xml_writer_make_settings(typename Str::value_type indent_char = (typename Str::value_type)(' '),
        typename Str::size_type indent_count = 0,
        const Str &encoding = widen<Str>("utf-8"))
    {
        return xml_writer_settings<Str>(indent_char, indent_count, encoding);
    }

} } }

#endif

/* xml_parser_writer_settings.hpp
qtO+LH0nKvr75arvs0mEHy1G+/LVd9+926yhcYXqW+nOziY5p33F6jvOnMIEI4n+o+8Xqe+IO0PPg5KhfyXqA/7tyqr9jPZVVP1y1JzhXpXaw8tfzbSRygNG32aDGVzOMnW7uqQb4A9BDGxvBUM3eQG5Vk19rlHBXN/vzczN9vR3/KTvM4EQXf39WooPZobL+vLasl7BTA8/WXuv08Lv1ek/frbQJ/T9uhJft/V6sm8zXLfQZa8v+w8R8P25mcTQvAG+j2rnDSUvDJACmjI3Irn359K5Wfb9xuK77hXz/SbVd7Eu9gpIpK7nTavvPfAw43QzOSfc2djUZZ+Uh9nZuWCGQJr2zWX95yqlwL7fgpXh7bqlHD8o82AG2jVHGc37VlKuoVVmNZ1bi2/qZJDR3199h9KZ6YkC+vttZN/nPr5y/NvKMYoDrwug+X478z0uIDSqnrc33+VAMlp3MLCkZPUfk2NWYJZo3APVt0og8dnQGJc00pmarB5U30lWFe2J6rsU1BvSt0maP95MgMYqMTG0DilaGGH+/bCWxcTHZ01vio2llIF+kfoGfoSNqQEbunes4DD1oRL43L+TlFef1+EojVOU5AH/fmfqQzH7ZN0ud7VH4/vwvpUAV5oZS/ra5qmd9UUhV4A/QcLLrjd7WMOo7NMlbC4RSwSkzsDBE/BnAC4OzFEVrFliRfNbN8X351fldFxuWSsNvqYsurIHZSVRRLsB224RLJ9L0xbmA769WdKsPsOHBm5pnWzF+202b4+QxKG2QKra9S7TJ5VGMlBJ470SnpSuvL0Yzq+trJ4zWKI+H2I0ygKunruh4/2gis0kUhXep3j/YmxRcxoHILJx+CzwTCC04SX62QOs1qDq+0/xnXhnblnis6z/ryRP6iYhlL2ZgLXyysDZAV9EWD1g0N+u+P+V8UjjSkLDudyr6P1zt/GkFgicS1ytjtPs98sRjlDksHWgTm0aV5HwKpQkqVR0YEaXZPLiCqceA23G5TqAq3GBZZSEd8PCPuNm9f6+AfBmcWVBrGxVECXO+/onSiPXPBCEeN+K8e7drTSDTWN9O+JtYlWyoBcXfl2+Jlg/zKKXUnQF/qmbKngdabSTuNH43W8Pxn7uOLpZ1u0uDXxD72LAXdbeFs2zEN+kAGPRozZ2Wf+lRdGdK6n2NG9LCZ89ARs58e2+P7Zb+7neIFlnSCGEE/XB2AKeFpCaEq2icbqHocm7u+qDewFGFanKL+J3dzZZKrZmxPFiVaf7mH4hJQO7v20JFsYE/Qk8NmegFhgK4dzflvGR+ueBI8eW+onG4qagN6caSu18FMqV2D7hpqebo9OjmWKupHY+AbAkr4ywaoyeWpPDut5+NptH2LnMMUFFn0A/79InupbEd3MP6uTF7gy1/2WynK1yiPYu+pepAcP/lbvNUT5Pajofm4cp1uFaN74atAI/Qfne3cSgqbn6JmqjEQdb17wd8KaONDiCxvkGDVufvQdwvj5qKI3pB6y5Ys/vj7AxIlVn0f4U4HyNqsvr5+vwAFvJu9k6/rvAqRYe0k8/we98XaNG/Sc5pyXHrv/PGX9vJjWMaY7/EvBSKRwo0kNE+/fNeTarKZNe+jtwxOLTw+ZKjeclLjbzSswornsEXSiPkXXmOvMmoHW8mPHxo6bn3UmJL3ldE7S4zaQ5UT/eUMJdzwtmZ/t+MOvNJKWorGYn6RwEHvOIYIiOJTPAOnZA9sUU4I31DhR4Px4FDtOVyfispO3ge00+UNDM3TbgpScXCFHnFL+PmnN1e7AEHpdZUNV66x6A5UUv8aDTQuJz8R7wEbqM6ntv4FjDTt9X8J0ZQXoM7ovvaXl81i1QqxQqBSA=
*/