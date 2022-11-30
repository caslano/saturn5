    ///////////////////////////////////////////////////////////////////////////////
    /// \file or_n.hpp
    /// Definitions of or_N
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1>
    struct or_2
      : mpl::bool_<matches_<Expr, BasicExpr, typename G1::proto_grammar>::value>
    {
        typedef G1 which;
    };
    template<typename Expr, typename BasicExpr , typename G0 , typename G1>
    struct or_2<true, Expr, BasicExpr, G0 , G1>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2>
    struct or_3
      : or_2<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2>
    struct or_3<true, Expr, BasicExpr, G0 , G1 , G2>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3>
    struct or_4
      : or_3<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3>
    struct or_4<true, Expr, BasicExpr, G0 , G1 , G2 , G3>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
    struct or_5
      : or_4<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
    struct or_5<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
    struct or_6
      : or_5<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
    struct or_6<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
    struct or_7
      : or_6<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
    struct or_7<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
    struct or_8
      : or_7<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
    struct or_8<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
    struct or_9
      : or_8<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
    struct or_9<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
    struct or_10
      : or_9<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
    struct or_10<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9>
      : mpl::true_
    {
        typedef G0 which;
    };

/* or_n.hpp
GmYgdDSS2zGJzsnQObbNEtjy1FtfF+PKUEZATnOcM4XIVuUZAqbB6ULnj7LWUQZDqIu9dRW/Nar7W7F6P42866R6rpu1++XJG3mgM0WGUYkoNQZneY4U32l5+4lNeCmyNR2eKZxFap1ANCJEJ0lJ+PEJHdUsAxMOPFRsmZjkmq4dwJza9WLMyC+IhzmtXQXp97BXQRrS+ZzIMALb1OZ3aaeK9TEPknef6lQRYPbJ0EdESd17hEAdHFk5chnB8+MGwDO3w7VJ+Yect6m0B7D16BbK0fL2qJOdU2mXMRigBPpB5kmTfU6nzkjSBjWyNihSSBtRgXmvdkVkQbYVVlH8mnFaGr1WAIPfzNbHXJuwOtpP1HoKwa40+WNjt2CcItOajPzpahlFypTItLoppi8/dq9uZ9Ec7bShqL9BYikW0s3PQ70gXZDbJhAUuEmjeCy7S9bJ1dPjXqryEZqanNBgj3s4ECkSiFkzAWuk/YM2K6P6XMRTpH3gdo0bghx/uajGONE3mDD9MHc5LFi1IQGDL8wxE8dnO80xMJSN25eqlsBeuJ4cEsqSFdkpLAe7GlTScmvjZcm6UiUe64PiGj9R7vj45OlZrEq+a2hp51CEHO205C5IjsAHqk9OTe9lm6F39i69DG4R5a9z4S1WoWPZH7Hxa8S+5POXTrVQlmu2M2Qfykd5q9/Ff0N3EGPMgrKor7Z8uiUZrfVEnfynnZPsEZ/4t9Nd5gwXUxihwWqC8rGrOFZrL1gbhdKGLtDU5AjPZyWglt36HVWdiofFisWTmRAtFYepoCiMGN2BuN1V95xgQ7rb0f5fbLz/P4yTQ24/ImeKGh8s+ZrPxzaAonRogXqLfvzUnFJ84RBh6qrqzc39KLdqjnRtT7JcsbxJXGtADmnDgmkJ22km1XwGPzHWJMgywGVOdpwM2fc5jWYcbOP95qfI0BQjZECuK8mc6RuSTMIsUBWvU+7sCi6Zyb4piRPyDPEQlmdnzBE0+VN4upE5p22nTezC3upA7lQGKPE2tlAb+m8xfluEz5SAldIwNk7aVFQVyZet0Q5OHq2Gk7chbv1/uwIFcQ95Ea+91mO/n91EgEMqNiiB+HVsNGWBEt9YbXmJtVfFVrys74Uj9brkiRUmT+uHn1r2RhX56dziQJrkxx3fNEn5T3o0hxk7KgHYUaOE+ru43aJKOR4p5hzphHfr1zG+N/I1I38+sTkFnBORkO86tYMUtoKkX6/cyL4tQ1QcR+KSYMtFnUVVZspwGcvlZDBFHnoixabvKGZ3lDGQYolObQhLpn3yg19BnGXvIJJpxFTFlIa8xP+4refr8HwXqK1C2dOqoF1JuHM2fSK+QnnKb5X1rl0MwimFxRnBVQnDoLhs+86t3cyaRlyQh+2IQt2Gh/PqrUYqnCeHEFv3fCqCo0r9cqJBd4MGDchFfriYN4koEs7IYrrT90BQG+5Asq8memkmdGf17lATjh9vI0xs3NHQ6MhGFbOYcw6phDyWMulS4W0GbaiC80J00cibJCRhE93oKHuje9rAyEuAG+Aio1MIBO7TYhz2F3G20lH2DFjR8lUJ1yhXsmvUSGMTuKxajrZ3oWvUY/CW4Q3HSf/cqki5FL2G1yylCWc1R86tJF+ofbLHuxyYwCfXPt9pilAzFC0JQ5RVVjLOcjZ5BI+n/CNiHRibUObm0TnCsG1esvebAPa9oZ6GoXC9bIgjjoZkJ8JGxpsNCZP/fkoLw44Wr3Hf7O8p6UsPyRvb+Yu6XCxF32KadD8Hu8ZQ74TvFcKUL0UhvTCRqC+/WYH4Q61j6RMfwwDkiXza+partFm7Wgi05PI2hwYZ21kdBUAaO0b0jXto0U4JjUla0+2/jK/pkAJrWw+M99kH3IzV6VzYOmFPL9iU5HXSzVSP9nQhHTnyxn+ZcbUN+70zii9mD0nXGnDE2r1sWVUYYS45IM+2nzFFTyIabndNz9Y8sbPpayZeomfRYogLiwanJyvFDsicL4jOcrB5PBQNrxdQe0xcU5s3uVYx3zw6mFLIgal2gS6kplhSc7BbL5wnSL1pVL7OaW+HqFYGuVZB/FDigFVKObPy5SBIl+wFLNxTjDC81ijgb+x5x7Zt27Zt27Zt27Zt27Zt85+dc5I+adP0ollt066bHsuVsQxpHW8CrMYE8Hohpu1hQSpWSaGpBVRzeAyrMmnwAf7kfARYZbJgZVCvPQwZNOg5LSxKNRqxUgkIrkqzJ9Jd/5527hrxqo/7oZAO4HS+GK6ZuuqGmQPoeiELlM6k/f7m7b7N2uT17riOZFX6+R3+vLhWH/qEM/f2c/X+1OHSYiRsJRGwJUKP1Lr9HRLUXeNr6ZfXLOsfEkbkUckPYcVBkCG2yI3x670vO7y9+MgW9vt6gUhXkmF4FrUJOEFQgbrITYDq2Mt4K+pCOZnRrSf4CC9c0IkyN7qARGLC0LRdtV2lGasJXa7OTvqW+jvJ1MIrNSp+uoB7zokflFnUqLBc6tC8Xq7Eiq4bBEIH8iGlFxtXpawOhpp49z5JwSON+NF3MePbFmemCWc6iwueETzSIKx8M6hgWeQAZdExbPLxnNTPo9udgzlLnvNwpwxq1j3yMlfXbELo9XpaHilJVykthPtVkbJtcG9C+nOyz4BwsPA2kumHR8O5xQvtksIrwhmwdon0zmDXTTa/lEIrykbDpb7SGGud8zWWavUi5d/t9VNBEg8vihst9Kqyoakr8eB+x58CnEj/Ox3Rtsngj/SmuUO0kRjI42vUsMTmXQKCcNBucycsXo0m9UrRs8Llgs7fzQJLVXD6DcATkeL520FrjU3yF2cPH9xBEKoDvTDL9W0s247qcdv2kayMSHZvLPnP+GvSNymgmoLmQCVJXc4AWbsSijA/snM/ajDWaeEVWP9RLupEUQHGiYhLg2Uzm9BNQmahtt6pgtmV+nyPKCxDTucYkbfpWUdOEnVPinO0XMybtMJnCTSQssQjTltENQuaB4jGXGGrWt2Pxzcd3wcXKBhouMj3MAGHKJDXxf5v7JaF/7ItI98PLVQri9+UfKMnn1eR4GtUyUC4Efe/mmWkVO++cI3F6819tkKXmsPjjUssFeFTvfO0DGjpfDxCs3OoO91kHrOjzF/GdZsYOHOEODvRKM24qx81aYkHPAN0JHIn2YYozYLf5RC7H7bR0lbL214vj1Jb70jLi/6Bp4lwGWBiz78Suj0+v1U5PRepRwm4aFlILD+Tp4zZ/gAqH5a+3+5cuNhBd+Llwz941MhRlRdSacNHhJnnkkQ0EtbuYcHgFgfElvflXvOcgwsa1zZmbUS44mAxlMLBm4Zf6/TGM5f08y96A1PGVCRLVLmWicd0xwK5Ra7LL2e6GXXsm0+Vz3MqYk3WTwf7kxwP7NqbAH1LyY42zhFkDBLANH9nsc+vXC4WVK8ifHD7wSEy33QsXNmNJqouiPUSC0RXezvINL9IcQoXEpXUHYobcGjwIqvo3oiWWC4GtAi01/pCUtvgW29aO18t7vB90u5fPQUNz7fEzI3CxAQMdEcM0uIUCXa1gEmwSc8aChFfrjoED73+coIcjVm3YJq17Rb6ui7y8n5Dqf2OzPVunusqCDQRQ6W7hIieGX8IeNbOEReY1qlKpVRqWdwWS9zVgSPDgTiE9ab6Ct91V/kGx0xvkoxyi4ie/3PaUFrrmWF73iiX2kV+9pDZKsanA8LHvwNwjLvdYtyj5Ji6VO46Q4dL2X7il4r4CMzOpoDFk9SxZNShLcRR9YKwSR0eN6j9wq3QEqQVTcmDhPIXXSSsTrUcF/vAlBgPvFWB2LDeMYwVDuYXxBrgbzYUd+nsYTLkz+r91CklHwajR1f2N2TtauRzf8Fdm2QhbNsrRi+dPcIJBphEYEHkQpWb4jOUcLgbInF2VS7y4nk+nKz2mGPmXLxV0y72eBIXr/K8lDZABV51A5lFNR7OmK/p6WyWrUK23jvyY54ryHVyYOsa1T1jkr5tl0t3yCiLfd9xOWwu/WYgkU99rDUSXc1qYzKYRUSFl6YKvcLahG0ASNlBBN4FBfZVRNRMX978aT3edKUSS7ElDBTFGIWQ5tdwc78eOmw6nGCZ//DliFfOPpYQBpqtIweX89BtNJ8/HMFYSarXkEmGE9dgj2y5K9CKNPjVHMe+USYjz8ZDaRz0PKEIy6F8Gd1Nz6NI8iqySXTmAEW8anoPYLa6IfLcxfiHL8JplCnV9gXTwbX/gNqk+oMsl/XcU/yeHKz525q/dhhuI2f0XFkfeRx4+Cv+n4KecZwP10+beVKsBJ990kIeOia7BspkTNRC2RVvojUj6h7RngC7K85nJ5TYPoTFCAmfRj/si4/LKiyIFcuDy2rK11A1Y9UtYoB+ds+QwtaVqaZai+EBBjEYdXwyKYWv979s/RyzcQUszyqN4XFV2Lgye506FN9qE+1aLSdJLrJMUWIvJw1nN2zLSVP1hIojGMBSi5QABSz601AQxVLM1g+q9cNqRep5i6eqieos01XcOiA03hewsyjwVVo3vxh/3PtCJ3ojc6yW2F3IVhHjm5mQ1JXj/LRUo2sjui6UOYOCNr9zTH5rAAJ3l9RRnYfLdsb3z0TbHehJf4BkcvgNXsEKs180C93OV/PXJY8MFdgCGGDRUjJH5QRCnBke0tuWUr+tNGrUaLtcivZt7IRinH3zEHLdD5F+nRyr241zHkwMhnCcVCYycu/Erx/b2YGC23WKnYP6BSsK5OZqBdgD+HVKUQOh2euRmBXJa9mQj9GrAcMmSbLACdNQUPy59LIX5IXSDzuwz9GmJMpHLkn1TcMl9jPXn2A50aqSN528lcWWd4SPI9221m0kmLTtNnhdLVPxp3sTSIWCjxEM1by25WKigw3XQ9odx/3IQgNajZnPElsDS2Zpx2ubnBJnporswzUVVepsgIFrryjumLPO8MSr/7CNHmDNKPTW7Np5G0xiGaqy1cW9NeIP9+D13hHhYbsx6zIaKUMETa3Oheg6a7HtJn8TvfqMiaKh1445TRHWjD+LxdeIux/km3afdaq+GTPnexSJu6eVtP3i5Lq/nqwcaC1d71cV29u9yhpDUpyBMjaQbC+uXX9b4ZerRGlrZrZY7ggupnqPRpbSo2aTJB7nezNMGpC2fGKUs3K7RhkhYMu5QtixdtEzBSdHfq/ZqzyODhzZmPcC2PEowr9kb0A41l15Wac1ZIF8O4ujsZYL1smsD+oOYcA5c0hu3SPD5/8rFazFTwJozK00OybYAb2pOGA1pT/vvW3SRGf9oBb96sSuF/d9Dv1tAaM5l9gBqnSlGDNWiREl1DyItioSESrnfi0T9oUzqcd4A7EqWcnz33gw0w1WpadZpazLmv+KSOHzE31XFGDiE2ptM2ml/sCXNnRDrF5lOl+LrrVSJnp0oa+mTuDZuZMIRINfpZRzMQdXp/Mvy1bxBNDOhnQxaCl1ubOqnvbwPR5Eu5l1IeNcIQSfkT/dGErbY8B3s78WuHs4KZ3851qnngKn10rFbPwDrkge2215vMgrptJ1w+ECGLHa/FDGKX7fkYtcC6Q1Kr1a4j7V/CwVzqySyRqEbiRZOlHC+b4uQHVyU7efZ/AsMUwjGy6laWnuF84q7l+zDH0tGsp/IVfXoyK14EAyjRqJckRFMVMd+kHQOoG6Dxq9wNJecF80HnPIIRHWGfKYrqQdXJnTEskO5XCC1LpTc6tQAdPZ+XiOGxGiktrpON+amLbnMzuUrjedLcc7lKL8hQFD8KaeCb4MH2ljhOa4sNxep9Lz5f1W0Vzlb175ztQmi9WYoenf30yPCz0E4/De6ESzQOD1Uo1oIlWKhQcnJV9yP0iwg6FSkruO06w0ZkCuUywbzufTDpLR6Qtu2t6hd3vOFCJ+Ti2Lxyh2/591VqWbmlkVH4PL0RwhgZZz/1UFWZoEE1Zz8ov9zOfbWpxZRbqe7OR8A3GPQQTM35sNnzNFF7KzdxhR0fABRn4PsUWMwz4VXGCxA1E7JlzZht2X37jGZ3NpzA/SEs4C+Jl9ubrQ4fJ5oUVplHL5BijG+HYu0yangvABQ6N8T+XBK37qVKh2zI+4YEXhSMpS7r0eLs9+A19lvtYYuRtQ9Scg68sgAJFf6siS/f0R5tak78pBdUkp8oDs01DLjzA3foL4FEbT6iLmrvYwNh6LcMkk6YZJwDNqzoc92ZIWsg9IuNv3AViKDlRUgjKpWzh4UlE9IeQuPCeZZlZG6wYpR5lGNjPZzap5shEs1VMJqMS09+oDV87jU3IHqfeEXCqN4uZu/qNE+djNBaGqK9k8h9t8h6XQVlL3pX9L6l80tMGJZge4kjA4tkY7LNse6eZVlu9LWC/dAXXi+TGpVJBLwaMnMcMoHHsH0wG3kRtKZBSgWNc/9OJQ5SXnxVPGHcGUFA0Z8UW1WgKfx5aoc5Ma5XRGVXuZOPCKcWPDgiyqEN2H8RNMPEO1qrlQNGJU33CkgEhvk/0wtaIZO3oCDQK1U10R3NFBvQgvI7OnTEPfkQYm0MUz36AkLdPhwps6uy019scKoTt8GsV0idXwOQOSxuw1iRRmcC9Pr5mUCuAIgxER4nX722UuA/IxX0IGXFiTSjvqWR10W94VhtJAfBZH+65vul65GFSNUjXdeTn15C+LxAjTrjQgQn7kdY9ur2AKJJIcqNJkmS7Pa/LC5Z0+atHaTDFHxtb/UiishsHf2MY/RRHw3I39hBEkyZ1Vp76KpH6iXIK3GoWx0wwpfwOiHQm3XZ7GQvxA7lNj0fKz8yufqWjiCD8Rbtu9wbUnGRNj04Vlv4I0vO5VXTah8wXT/jHKia7Lr7nQjrkkeW9Rs8u3UA7C78DUs2QiLVukzlNEmkGf19CEZ9yUEX45QC7G+L4hGbRzVJw4KQ9oKL/P0cqPZ/x6Os17m5RJ/NwrxnDbaUBsJD4nauBa/JJ6r4dcULcRX6v6rFuYgJNxHo3esW7gNnry/A4anlS6nWjM3ZBxjpbz0m0XfH/XukwE0E/spRH2/OQkHzgLnUOj8oZyV9NXy3xhvTSLgJR6ZqiY1q2tN2O3tDpRLb627rrlxYTGRXNFDIXjVarlN4RyMWcYLrq9fh5RQy1a1WCzGQu2LkLvTB2gbznM3xqT9ivtcqoZzyq7I66MTzrizVgFpqJtcH4pZVDbnDunK4wC085fggO9eQk/Xpgn576ftWW0390w2UxbuSdMfxkPkwgTxnqj+DB9YR4yRhNDKSQ0CWsl7I5SqDdIrWOq3uW+OdZBbe+K/Wpgpo8T5/1E0o6+KgUFIZ+osJRXMrbWmPJEwAjkhto1aQpxs8fo1F9wKGvLo1ZuV1lo8hMfrRNqC+HFsoRwhJeXmad/qKeqr9cxscjGnKVswqcleSpl0bf4U9hN4yBcEHtUmCWUG9B6c/ngajrgJFVLws+3LZLq+pQOInkPE3nKOMeUJhJG8Io72R2VIO2zk95IxELjIZAynn5nXQw1zpPT+T8EOkC/5L9QSeuTVx0ZMWMQPbjRmoYkl4k4t6cA/2piJFsaqIs2WCdfp/V/3udJSeB/rABdj/UIAR8CDFHHpy5hq8IDUWaLTE1pZqiX/hd7SuXGtcdmPNLPkW1j4LX26qENt1ZOZyaJ0I/MbyynhNozgd4k/hto
*/