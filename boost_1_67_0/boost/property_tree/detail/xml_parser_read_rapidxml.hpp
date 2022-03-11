// ----------------------------------------------------------------------------
// Copyright (C) 2007 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <boost/property_tree/detail/rapidxml.hpp>
#include <vector>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Ptree, class Ch>
    void read_xml_node(detail::rapidxml::xml_node<Ch> *node,
                       Ptree &pt, int flags)
    {
        using namespace detail::rapidxml;
        switch (node->type())
        {
            // Element nodes
            case node_element: 
            {
                // Create node
                Ptree &pt_node = pt.push_back(std::make_pair(node->name(),
                                                             Ptree()))->second;

                // Copy attributes
                if (node->first_attribute())
                {
                    Ptree &pt_attr_root = pt_node.push_back(
                        std::make_pair(xmlattr<typename Ptree::key_type>(), Ptree()))->second;
                    for (xml_attribute<Ch> *attr = node->first_attribute();
                         attr; attr = attr->next_attribute())
                    {
                        Ptree &pt_attr = pt_attr_root.push_back(
                            std::make_pair(attr->name(), Ptree()))->second;
                        pt_attr.data() = typename Ptree::key_type(attr->value(), attr->value_size());
                    }
                }

                // Copy children
                for (xml_node<Ch> *child = node->first_node();
                     child; child = child->next_sibling())
                    read_xml_node(child, pt_node, flags);
            }
            break;

            // Data nodes
            case node_data:
            case node_cdata:
            {
                if (flags & no_concat_text)
                    pt.push_back(std::make_pair(xmltext<typename Ptree::key_type>(),
                                                Ptree(node->value())));
                else
                    pt.data() += typename Ptree::key_type(node->value(), node->value_size());
            }
            break;

            // Comment nodes
            case node_comment:
            {
                if (!(flags & no_comments))
                    pt.push_back(std::make_pair(xmlcomment<typename Ptree::key_type>(),
                                    Ptree(typename Ptree::key_type(node->value(), node->value_size()))));
            }
            break;

            default:
                // Skip other node types
                break;
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<
                               typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {
        typedef typename Ptree::key_type::value_type Ch;
        using namespace detail::rapidxml;

        // Load data into vector
        stream.unsetf(std::ios::skipws);
        std::vector<Ch> v(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                          std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(
                xml_parser_error("read error", filename, 0));
        v.push_back(0); // zero-terminate

        try {
            // Parse using appropriate flags
            const int f_tws = parse_normalize_whitespace
                            | parse_trim_whitespace;
            const int f_c = parse_comment_nodes;
            // Some compilers don't like the bitwise or in the template arg.
            const int f_tws_c = parse_normalize_whitespace
                              | parse_trim_whitespace
                              | parse_comment_nodes;
            xml_document<Ch> doc;
            if (flags & no_comments) {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<0>(&v.front());
            } else {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws_c>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<f_c>(&v.front());
            }

            // Create ptree from nodes
            Ptree local;
            for (xml_node<Ch> *child = doc.first_node();
                 child; child = child->next_sibling())
                read_xml_node(child, local, flags);

            // Swap local and result ptrees
            pt.swap(local);
        } catch (parse_error &e) {
            long line = static_cast<long>(
                std::count(&v.front(), e.where<Ch>(), Ch('\n')) + 1);
            BOOST_PROPERTY_TREE_THROW(
                xml_parser_error(e.what(), filename, line));  
        }
    }

} } }

#endif

/* xml_parser_read_rapidxml.hpp
QG/a5cuaYI75J0M5HYEvtKkpi4ypOCVS2Cf2Ea2K4lFsELbw8VJCu+49ur2Fdd8E2czkg9NmFSpN5Ip35xyBXfeHCdt6nnpv6jGNXhbGjQuQZMdQjWPx+OmbSyqF283T5Wz3xwtDpplu334RCw5K0zyOWGOnjgyCfHaCuJe4sa0zbyJijlybpbnb8wP/kTinS+8Kuze+WHTvagb2svrgW9WbYaiR3e0ceIz7gvjteR/AYLaQxNOaOzNt1kHi8N65rMCqyZv3NyS+tbNbRd/rq42BaI2xrYqPjN3HUPR1NQk1Huv7kwpgEluNyhGsOZ3riihW661mHXMtOhV5psWMO6EDor8RM0+eyfsDH+rKTxE4KrxSl7qzewV8ev5vYhsiow/zNEeRxlGN5XDLbTo6BamncoTD7SNvQkQ893UO3DOm49OzAEdFcaTVMCXySpQXitNPaEmfilg+n6wZc79NvPxcxKJH6BjoDa/Go2JF/PB4UKgoEMMfnPBkWvDpEUeeuI/AzlTE54gr9GeM6p27p+4jZwL21ebfqC3JjPN9M6lWnulN9p75wdnPbRC4zkN/q8EVzKF+fp5HArlVTlJbGYsZEykN/Kk+SZDnzm+ay1AjP811b54M8qmcTk4d1A5sX4VFtGf8XcvQrzDCLeXO0tTEt27Ipu6HFW68CTB04Wovy+kNfnQlvH1pR2B9r7E6wETkGfB9Tu/B+ks0XTocI3q+TGEuR3lA6XfoonCGodYcfRT0R2GAxQBGGl82NXYffzfjlu7bCRpJtq3dMgFYm2Os13R7A7+G5IAcrls3X4UYUqJ5c6DC2J5ceBuJp7Oe/MPbLLKomfCYM3nTVHppdfCYfoZ25CkinoA8cOzGuIhE/34xyzn/uNiuD2uCo82u4xVMlC1xab5QzTuBg2rXyMH0pPIMb3Jw38DENkmgTc6He+ejiwjpCjusmvca5OjgeYD1+ot5R94Vnm+Gum/bT71t0/ER2hn+Qe4tuND6NFx+peYPy7lCZfpwFMLMAnGXP3g6QE2Cdrhu2ywNfn7ietjvl+iv5l4dcGIbRUed/W/hW4Vv6wLEB5ivRCOVlsodRbbJ2k7vVERtz0RAJAr+WmrJzjnXOQo2jaYGJff1pX4mj+/c9z7KCI83qQpd35sTRZJ4W3ZbdAJir5ODqKEiidFFJYMkhedurX0+Cb/iSKSwT14jruQuF85W7/RxhTSOB2thnzhI26niLiKMn1cG/5BodkqGTTPot3CqNXSMI6h2pu9Le4Alf5/uMBfgdccF9JlZ3sIOXi8p6KLui9GG+djh5j/aDE91gMdqsME0nz2E4zwojmIogU+H/k5BHTK+/jnowR9UuiE6U/Kj/l1Y7pZXQY4JuizRRE8pA6VsOWPVhyT/Jq293aX5W9py7IQ5+3QvSLEbImMFyX8AuVR3OZuxoUsQstNut+Zcn+RCuBSFSxcmWAtwbVIAi1ottOVXR7xd6tpo/GxWhZHLYHQZOraBibSkMBM2HNT+6yfy3hFPIXiRlqD6ZsNxWkkbJugobLpTdyo4FDPe2yTe7+fdXJdW3lwnrrYK9vewtG4o558W2dm7xba/GkPsqL5ANWm+eqdIjRbHkCjg0IjqFOCdJccy15s+vaZTo8qeppNQGU1db56EEkVFVVw99c7DSKe8/UvSPIRDtWyldoy17yMy+tpXHgieOYnzmdWhiKFUwUS36ocqp08MVqsQ2Oc2qcCJz5rsn0O1xq6tksfGflgZZqRDqWXEaas2uXLJiDe8bZslhsCnI6nTknGlM5mJRUJ0QnUiejhBTeyknaYfiOIMFFoqSthoUr/EsgwgA/95rLEUkNyfUSoefKAOOcQZNF8NOnLyIEmrfFGtWevfMgRyzkd9E75eRnQ9Npx17WEesEtgeKE3IbgLKQgJvV5uTzd2IR5N1Xz2ww/ke3GS2QkBeiI6bzWDquGk9cWNzb71zQfgRHTESKx70uU2XZ9TY4lI5bQik78whaJYu2mFwmmy2d0R2ai51NaLwXDeJ3Z/lARYL7ggOmpM1z1hyjoL/oloGoQecZV2iDNtlqbdDuxOUDsPOxQNQBf+oT2XM8HZ3hrYsgm4ogalHrBRQ13HeFaraQTa7fnDxEj3UJOToiDybP5DjnE+3zcT/NPPZYuMw+0H7bzt5YFt0fkcGoclopSjkyI79inw4UZxcR1vdfzs9pMNEQ3I0UFGgHUeT7u4xHf9byZRN0s5H6zvfrq5c423VbHUEKielSzM0zlBNuMesYi4iboSSO3yP3vSFl7lht7kvS2x2fX99EkPyMhg7GCqBvfWs+ZgxWmOExNwtUfnbaVUOOPB7pmT9qlVWuRNukEMljPkyh92zde5DQPHHqqt2H8L4SV68pzM+2eH1gheICOtK6yxxKQAkqEmEYbfnthG1Ya6Ztad2kxnOSj17epL+P04zRg6OsCEte7DZrgyzjLBDXRS4EMaW58YVsQB3+QYv8/McMJUt6tdoJqdaJZexumntSQu4qj8hwVr92tqsSQz0oPI3s+o72+krBvHpjiynJulaAa1VhaI9zbf+pnFvyMJDWJ05nvfyQoH65mKO76P65RVzlcmPlR8/vDyl5t5wzcvIPSufQVdduSuTCx3+Hrz9+eQ3xcT4SG9Px+etXvT/yhL5BqGTtyPKqQcwTbm6NFwPC2i3cNpOhqDp2CJbRukjg09bENpGM1qWNq6GjF2Flg8VHmJfGZ5cnWhGGLv6dS7h/IHtoNexoJhfH39FqSyrGe5O5AyJxGc8EDlRA/LEJrg9GgbYIiyhUFQUB/xbI5Kz0M51dowJCpLKKgAjUwzl4IuNr+IkP4AR96di22Bvg4YBOTSXGFnpmKRt5pgsbqzXLW+rvK0fxguj5Eyk6ds+l1SGR75Tj/CZpv9negBlfB21iDCUJkZw/axUeAH9IDbyahyUGlf0XbrytsoCdDcRpTO1dRxhvKWjzP5EGbY/IpvJKyFQbIFpjEm0kY6riHgU0UbkoNwRgXEfr1T9t5MWW0PyOlUqvgw/fKnoHXZfWS2Fh1S+UofJ88b6x7xS2j7LshjcbSQlpoXKB89qQnYTO/ZawAD90FCAIUFdRjLT3uqLxiYClKTrbUXUqhGZHIAa3HGiwJ17KQjHiKFjQ/vk9LImW1AVQp7LjHjj+TSQZsthvo38mafX8fgjPOMkTNh6vh8h5alKp0y5TihY/BqS+8HcXq1Sg23/CJrmZrlTF/RaMlrouR/fuBfPc2vyVgx1yylTGU4dS8OL45/WMho+nnx6nEQcfMs6YL4+KpVePpEH3yaprysr6ikBae13YhzKhobbcn96D5aXuOUjkIzbTUBHASVGXSTrV6WU3xy7pRNObvCCmrkuBsBP4R/bVtSknCxLuZGuzWmpk3zb7Gvd4Qcp/3DpyBNa3+nRWzwkmACkixx3GakF8/AwItwmyAsbg0N5MfLdOx+UOJC+zemHsDTw9as6GjTxYlAsqG0ONrYdVgOFL4RGrN7N7zfOfJeP2vCyJmD9N0qSnWrkVgfzWOtbKTRzONlWdZt1w/QeJIkzgGPSjdLGnwLkgSoEBorwMpqWiPz29GrIYKbB1wmDB85wTzvCCsbn5eq5bKhUWMjw6v1hzPuvSYktmI2Oka1VgkpG59I2D2fy/D4LekxSt9WxE2XaJvNmLX2N33o3ShViQcTeo4vauYkgUoPL+ZJbhb02vqVP4rPLW2yAb4ACQ023chFIxMH+Knrk02ddMmR+QNDPMzQrZRmRiq3jxOqk91RTzHRismFWCYt7h27rpX5n1KwAyP24QlhfPdaB/fbbouU7t/VFRccJoITWJJ6wsvMqL/Wi0cgQ1N5mHzRHLbxmZLu2lPqHoh+2YDUkGNnvcQ0w0Ip43URYoejrOQrO0p2KeAnlfR5+TMnOLYZpTtTrIB7aa4IlZkrml8DEdl65obne+Tnl+zIY3QAa1cgEsdt/vEeqLszqWF71vIhI9KsHbFtukTCWzfReMkp76so8Rf7go7sNAEQguBP9MBIzWG/JmX934nEBf1vujoln0hijS3wEFsEPAe6fuQPg7SepHQLRPFYrDF1uJkNORiv+UHI9OccHZoxvBZ1tTYLMrxddqdHCoySMp7SJHpJNGiFzndTwujfPIjoXvl7Ev+4Gt7c0PEIvk1DGKz1Y86QDT48bG5Lqw3ZFzP06UeNl4wXc0j8ijTYVwT1kW22e6XTpmyKokL9ARN6c0IAnR9NRqyvTpOVfhozEhih2tVF/HbCi3jPwXZBcli2VlBB8LQmYLtrm8mfZ3cDt1mfustJ95GsLqrnQFs2pgYP6GsxhWRL5eQ1WG7IUysmVPNMICC1o7FwCb5pHwlfneyW60FHDctCHeEpehG12ZJBBVvjmoByQvEGN23gtpYFrLjtJAI3qOZgYDZo+q/aGyfJbntu3jHfSQinM1A5dlIDlROEMAoTsufIE9E5Tg0nUfzJDuwYqjxLtl1u7Dv54k/dF0TJfCcunGv2f6riQBT1nxEG7b0IcbwXbCh8c0wTIE14jEMHjww7AaXlgS4mxSJoQL6TOC51oBL370meTVc3cQxnewQp7PitMjwWaN7mf7+fsl07pbA8PTI7NgqkVi5PLmbmswJIBxyIn8/uLvU6zFZluiBFs/SCCg4b0863805RYsonDEmMIZyxbgzS65HrA8w/yNUq9rhOC7uZv7CWyIbYhi3/kH47Utlzh569QX+gA2j6fzVPnYqbVHXRQo3yMNop+ARWCMkTEYB+wtCBjjLGHjke24zOdD8JoDNBsAL8D9bI5vmSmwUriClbGbbanhxXLZz7QOU3abVqxNj5+T2gn+ichfQH+BTpOCBD2Yr+CPfyfDt2giJf3q0nsKhgoz3QzkZeB5IK89StWv3Es5WpOH8gHERZa+yVGjoJiX28EP1lI/jsTS4yx+0uyZXI+2OczGPTPilsr3cBc6resucqeJJ52SI3DBrooKvc3DayweG5W0lXxqpj5cYSa8Pf9THA27GxZaXy8eHDTRA5wQ6OgYThQU+k7K6WNm9tuK5CY6H5JeiQr+jQ12oQ5SflUJxrQWuO7scLuEPoORLOI91Ajh//JjkvZVZO2ZUXH1eClRN7QLlHPqkPqwd/sNb8hNpUBp6gOCJRx6HHEqYNFphGTkHmmQKmLgmaGciGK48bZzxY0Nr35QWYEZZZ3YF3QLmnInj4sD5AX7nsGyfdlZ9UgwKzwUi9FoVPGNX3QOo/D5xnyhQWR61+T6upLWiKe1eX8juJL2LrYStF7ksEM7fr1tWlmTxAOM7YC8lBzolZ1wlv3J4d1QTsdNzBuBYZUHA7kSoAGDWZIqnZawYq/aaKk5wtXfThznahbk2oDrRfJGceO240yp+EvZqg8iPY1xjl0ASG9Jv5le3ECaleUS4FIb0472vQWpY+QewXVHv3xsFAZxDxf1LhIDj8QPuO1DgBuf5dZc5B4SdBlEBe/XJwvHE6CL5SxArYKQWNG6GHRARcagYU+/T9rtRdkjGx8aPR/miEXXyYxD1ihnezRaHcQIInErUKSZp77rdz209rv/eDuN5Ne0PtUhUzv/I/E3LLm0ZVtDnJ/J2h3Nerx3XidxGZ3MAEnHHeEyQqjqq/sWisWRruu+SA7F+mW59xDmLDxCp900qU3wG6YdhLbZPUOQbeeF5CuJ9Tn3Pix/t0gHgBOxtumOulY2fBL+WYOiAGJ6rPL1SYk2z4Yp4xqtVhlQure/B0tWDgjhbHfaUfrwQ7fu6LyTu5bNU0rYWaxZm8WXjjIYoj/7scrV12MZRm146FgmbvIwXiCDrQRIsOFxNpSTSHryvh6Druxa/ovriWNIo1uFCQMInb8jNCacxuVTzttyaVIZ9N+22/uvzMb+siTXvxhMmeTBL2w01X9wuTdjOlVrbhSCsiiuUvDzCVhR8/48IGMzro/N0QEZYCbM8WBoJWYasmWhJPB7L3rIhFux9sTwFLWKrITwg7vgcp8HWbZ/5A47oqbWdWD6sNURxPGVUFylbE2t2iMYsjyUt5pZLkza83aoG52o1p5ocNisf7vqI9HnFhuvc0qygiZlGldX+mT3i7p73f4hWLFQp0B/yaLApdQnGSP/9dJ0VB/01EJvrIZfNQn9x5LpFuj2z4o1nDSqR0sSi6LCVWvtejosmmJhs0bfx8OHBBY7miMR58/z2NqG+/+s5RD2NbhI3bIerYn+fzOqSOLL6LCwNkvMOFf0+i7B0itMsm4nNrm2z0Xo3Iiwew4HTzqHaokgNt/J8i+5+zzCxSAqt3tQqMTEw10Xr8HMZ9tXpcpOSobOlZbmnT6KyMEYrtaWSpkUhpKyK6LCtuuopl/PkqbPrvkVZDbZaxkQWLonpKof4CI1Yi5Wnj28NelRB7l65Bm5kyPQ5Qbloo0DuJopyL5MymuojFNqYqs2An5Xfk8MXpTYqef2E/4Q7DUGdxxIpN6bAp0kHIekyhDCJB1F6+izPg9HDP6Sw19/nWwEM2xvRcT1tkxBYjDEgVQMPyiduiqoAJPRHyD5uc2NRkzJSND5vC3Er2i7CaLd/gk7OiAdi5/X6o8gw5YvmOWB9RL99J9d8JhpFAHr1uaU4OhRpDu2DHr03WuOTxzJQL8Fvv5OfbJr5UjpTI3kGdB6VcmJxs65aOHuSSp9zMDicclSbUyrtTN01e+HqOWp1eYe/CeJGDk0xwb4Xg6WZpW9Lg+CG7XGfqX83LNqlh0Vnk+c07uRimvQtAmADBHUaM8KRLkNKTm4K/Pd28Ci6ywNh+NGRkB2xPFLNJwF5JqjNH5VN5yE4vLCRcLIpPsXbJgwtHHi3y80hIfj9ley72XF9s6GpUyp3IKdBL2o40cb+MZs/fOeg4Y/omPYzvA7PwHdRKw1eORd3rE6pj/vqox0iVmO6gKKb39sAZrNo1JCYGudi74/6mwf2gkmZf0Tl4b+YvjD9yu/c+0EF+30c8+wwVAN6f/Nj+2BKvMU7IfD9lV4R12yHK2h9CFKFRjdAdYesLOJlO5larxW0FF3HXSFszNgVrMCKyxAApe04CP3MdPq4lSr7z+BRUjpW3DDyIngIp/Nod7kJkcf4/qQteVeAsC36csOIG9sGnoLbAcV173y5Z2xmQ2OBITboiPjxzaq3DjmHjw1FrB+ZyY47spofExPhChIXI+sWc6Kygog4W26WExBivBm1OStj3YlJoHmCuKiZoOp0rOtBAu4+GX8k9DSzFXYIyk8O6T0Xjey5On8g+5BS0n/P+zF/p+yBviQesXFjTZlFRMUFwBj0wWmMLLP43TvCgHRtTV3w5G3nFSAfOV3wKVip2i+oF0d3shn2KHOQUdkbaomNu0EQEoJ0gWA7OMhHGqcSN490E8D48PryAoNruvWZcMPnj7l5HK/+0jFN1aeYZ4ALUlTk6/JRqGbLJ6ph90jH+GOHOrh7dl7qXdtS8r2rDBLeG2TA+dLSqtrIcaH15EHtvVfuufuSxfg4LhVbKT3Cl40BcIXvVyeuw+JUQlBkfRtYv2ufHrqGncZ2qVBx4PwwxV7klnWZ3Uje50M/PFbVKI3RiDco8ciwCWILiR0urYviRsteeAxEA90NkjrnAyZktTqkGhVuvRs5drRnfnIoA7AA9MF95/RPCpoz8XAlHQjhngTl87OvezaPcrSJ+p/TF2qbRxs/8ZDmBoWmDMU13rkbJ7GDq7g/P5z1ptD728rp5yuaAu2eGh3v7to65Y5VgMhLGNBRz1/zlWqwNkp8omrtc2ds8v7zvsVa2xxRZpDjOsOWZQXnyuv9zuo2KAJII0kmJ52my3OQCs/mjf8LHL/sosFIouxIcT9LD0d4YYFUWNOCiLhYv0lJ1eezPF5EdtAdkPZVWuh7RD80WldMbebN9qUrXX0o0iCG3r7sCT3KgNtRe86SEs8WyQrf9iEhi34TX8OISXjFVdlgK2mE+YP3o9OBPQb8xQ1p86O8J4CMTLeYDFSFgyBpmzKafvdYcjNhu5CE3JQwR+Xzgw05kk+J/oKktI4pp+lp8Tw/AZxa0Uut2P9hyA3Nwl/YY15EWC7N4uiMqpW63aOw0MGEI9S4q/rPMMB1/V35+aXxtrPSHTNFipnrPnEfu5+kg8mefkFH54NH/3hUl0JqNqcquIwH5C1SNftLwtAZLTBzAPamikBtnyEuG37ElnyB5Xrh0cz5oKyvZKO9H5fW6o7XNFkPRSN7sCGrehKrIG1UkimeN5ExRuuZiXSyI3nyZuJIfF4Yr2uj7PCntQTZ8zAvl8BWt5u1hAVUXHvDPtPGDDxD7j6Keh67+sKaPc9wtR3ilT0EDdox773iB/lGgwiTQ9b6TkA6w6HcpLreyaVTR5VmYTxQeZuFW6vWJZl/R5YeENX2Y48PTJTC4HjtSOTJOSEcFiQ0CXbdqRLu4HVRB7Ns6B21nQN+3R+QL1w+/G0WVqtyOvGd26JqCmc/xEsBVA0wW1JfLIPbmnVxaNyZkRcg/vt6o5T+5V9RzoEPznS7hWgf8/n1++XDWGoARMPeEsPGHG9t5ylbbLox7axy1JuCrd/eUd4SfHvAobcLTknc/GExfjG7/YPA+dxVrXPbnsTiRiRyBuVrWldLIAizWqp6yK6JMrFGwNv1xTe6b30rzceeKKIVJ0x7qmolTtkWUl2uUZzYyL1RVuljby4wdGbamdqhJwcfbP+9+tB35myHZmNpbwUMued7hdcettG4sArBMoJWBP53TE/O7eJP01I/7WuF4S0ZT0ehjCcmAfKaqtXvTF8RIr8IdlMFmc1s3Cz3b//30kIn95Svx74eilNjuPa+Sl2kwbVz/OKPGmcUsISwZ8AJrcMb7cvooaNvyHbHSQxY7ckBpqrXXkK7ZTi/+HZXTCv7GIA/EaNr70fAYlbYdB1J5aHyuz/Z3/cikBO/c5NIpu/6oW70eiCab96IjAXkPYXx95VgXk+KzaAnXmF9JXkeLAuIbXfOhw9ak8olnanqKOwUucWEBnqC07hDNUmSOuShU0FfUh4Wv1kg0zu2gEmL/Bf9qM7wCHE/Hg0zERukh6guaHcwmWG98btTzxtQaqe3R4TMFurxSHeMqRqzd5qy1BCOOHYrcr/4/9VsJ4Mbl6RdhP14P7y+3LZXqlGU9UyOZ+onqyH76CA/5tC8u6AMvFERKsvQ9MKnaZmWPaF82pUcGjqk=
*/