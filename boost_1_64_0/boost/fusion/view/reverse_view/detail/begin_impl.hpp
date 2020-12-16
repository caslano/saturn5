/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07202005_0849)
#define FUSION_BEGIN_IMPL_07202005_0849

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::last_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
j0I7nePUbcoPbTKzF0PL3aB2zjJBrrTfTI9WfmTOZdSfi03gAWmrZ3+pTWP7mwlmM8v3864uND/ReNzJV12bU1s8JojRSvvzwqDilN8yE31WZ0DrMqlhN1pHaGattFxTrTEUt9IErUHalB+6LaX5qWLOVSbIoZGW3P3RNMphNc5rkFb78fejaYzWhFqnTf4pNHfXmmAAs8y7f15BZaawttcXz6N5vQ7HltmTIqs7Ul+vN0EkM7ofQ7OhVVPMiFZiR/m01E60jRppw75MrEXjsBHnPDNj5cLHhYHXBO9A2o9zZ6en/DZjW5jxtjjQxLssM6ONu5XdQfntMEG2CGmRg2E29cteE/yYRlpYwnefad0eMcFypb4saF+LdJD5HTVBHDP6fgFaUMUcx0wwnVnrxLUTaR0dN0EvrTR9YiN5Lj+Fa0wjrUXOOgOFwRm8roC0zMU1STRGaLnCpL0tUsVPZfpD89uXFDGdckDjOcjvF2AOF0xQjxl9vwDNi8bzo+8XoDkvmqASM/p+AZoPrTLLPTG27TLq6ysmmMtyP7EnW0myayaYBNLW+HP2o/ly3QS/h0sr9ukwrQfbXROsjZS2s/3cMjQOz0ywOY20Emejx1MOr03QA6TVuN2L7gPgjQm+Z0bfS0Czo01lbXlyOG0rivuIfcbs2q1SZ6hfvuAewnI/+XHgPprXX01wKK20v1tFzaf60plDxoi+X4DmQavGLEOfUn2FQXozRJLxNbYhzIBWSGlLVs2GsJ09D+8X5s5ghiSQFrNv3nOKy2iGkcyG7Rp1UZgP7QKzE6eyFRXm15mhE6vvtN7novr0ZsgA0jblv1VKmCeF1Vq8v7owbwort/tzDWoLWltm5mElNMLsBjMYmHXIP/8vYYlotZitet2jE5WZwqZ7XlUVZjWa4SGzH0a1+JnqM5mhNLNftdcnUu5oNo20r2NenqC+tpihIEgrUOTmd1Qm2ikti+u0YSC1M4sZtmtY3Oq+64UFs5khr1JmNrTDNYt8ohyym+lZXna06K6tC1O/oL0Mk/YvNI4R5shtht4gTWvb1FpYAC2BWdEPmYZRnBVzYDZsx28VyPKYIQ8z+p4cmgstlpn8ri3mrhIXRMvCjL4rjWb4LvU4O1ohZvK7d9gWtGrM9voTr1LuaBrFcqDJ9zxjW9DmKpYT7fvaZbvTvM5rhqcaaVW2WsbSGBUwg5bZ6l86/CHMWdAMGcOkvdthKEg5FDJDPEiT36PG+tCGMpt98/pgGofCZnAyy55xRjTlh5afWavFvSZQfxYxQ85wab0fxIyitpSQbcmVsi1oA8OlJReaQ2PkKGuGVSDt67xdPuqXcrjXMTuhzTtSmA3tObOSk2qmoXldPvU4J9q5MGnF6xW8STlUMcMijbT3kQ8t1M44M5wHaYMTtj2n+qqaoQqzpKGW05Q7WlFmbW/XcNJ8QSvN6lvUed1CmoPVae6ihc5dL1oWZnzO+1XioAbOeWZ8zttVzIUWKy10baI5FItGo89h0Ww1zdBMsdxo+bOmrSjMg9ad2YcEKEdxtcxQTiPN/6ztJ6qvthnmgzRrZOQWauePZhimZWV2mpSe6qtrpvscK9r8dWuprx31cE4wO/Dj2L40tvVx/Wmk5bNZ79I4NDDDGJB2vdHLThTnMEMBxfKgOUqNHy7MjWaSxp5tY5loemYD4hZSfv4URn+LiBZEK8Hs1tWGD6g/40Pjit4YZ6Pc0YzScNzXbKe1ghYljT3nwxxSlFkgoc1HyiHU2OcWmANaJDN+fgmgBZiV9lTRCIMEnNfMWltj5lJ+aNHMvht+bz+NQwqTf1OIOaBVZPbgWYtM1JYUcZPWv5TnpUahduDlquK0jtA=
*/