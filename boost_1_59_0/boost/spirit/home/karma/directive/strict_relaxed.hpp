//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_STRICT_RELAXED_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_STRICT_RELAXED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/modify.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::strict>  // enables strict[]
      : mpl::true_ {};

    template <>
    struct use_directive<karma::domain, tag::relaxed> // enables relaxed[]
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct is_modifier_directive<karma::domain, tag::strict>
      : mpl::true_ {};

    template <>
    struct is_modifier_directive<karma::domain, tag::relaxed>
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    // Don't add tag::strict or tag::relaxed if there is already one of those 
    // in the modifier list
    template <typename Current>
    struct compound_modifier<Current, tag::strict
          , typename enable_if<has_modifier<Current, tag::relaxed> >::type>
      : Current
    {
        compound_modifier()
          : Current() {}

        compound_modifier(Current const& current, tag::strict const&)
          : Current(current) {}
    };

    template <typename Current>
    struct compound_modifier<Current, tag::relaxed
          , typename enable_if<has_modifier<Current, tag::strict> >::type>
      : Current
    {
        compound_modifier()
          : Current() {}

        compound_modifier(Current const& current, tag::relaxed const&)
          : Current(current) {}
    };

    namespace karma
    {
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
        using boost::spirit::strict;
        using boost::spirit::relaxed;
#endif
        using boost::spirit::strict_type;
        using boost::spirit::relaxed_type;
    }
}}

#endif

/* strict_relaxed.hpp
lXO6AUEsDKdUQLAQvoz4ojjigWYthiWp9nxvv88p75TFup97XVy7qBGZYpYYTucJSksPQWaRlU7TbSVCu7fmST21naLgZs9WCtXEPK8UF+T6pnskhxdyLfT4UrS5Fq3/cPhhGw1jdJBcIepL1VVZVvmMRWHLR+GeqvsgWHE2hOM6ql4BB3G6xS9XncKCsBdcrUvYWt0LrjNLyp7hl7NLyp7ll/YlZc/xS9uSsgWQoHC5Hu1zqs0src7J80fZADM1QJrmcVW2naSGmNtqw6Y018HgOtwxMATXwRqKQSm7l8uazmXBfZ0Hh6nrJsk0bJYnxPaA5Nd78fUjzlqc0PYWm5uRxnsQxIu0QaOxvRavOrqUVl3EMI1SlhP9pG1GxdqXDo4rzsyonKW4Fr7AXUttGuWxvVZ5sSbVc0lf1XYvNwP91DbLPmNrDCeoHyEU3DckX8T/iQiQO2ZO0wXeA0fFeBqzs/13tRlTBOei0gT8vTxsTYiUxorlMGhzh9H+SUCozR0Jy463ideJPlG6aXOHA6PMHaUFWrV5ZrEQsdlmWHSPYnE7zkyzLF4YF/Lf7ygx+6eF3O25nkiViQw/7SClf4VZmpBqJPSblWJ0URepcFRKHZ3905bZ17D3+la0CEkWroZ8NuIdkOi0MSk4eRiTKp6igqPn7PptEGlvkGB5xsg8hlzue8kwLwfQ6wpDpaY5uoUvdwwsvkLtSUtzoPOT4n7qQNNnpv3KQKWn88hfIVtYcNKRNbwkRS0Z7jxffJk6YRSl7Espe5s0SlcyXKGY9gX16uiF1GDfFF4T1I9EbcR6P22oc+1ahsgCUfBLdM4U+bhB/zh3lBhCX2cqWaOmEUtCSPEWHwz834/SDJiCucO4/0tWy4hRmCV2wAjEeUjMuRi948WoEZiQ26I2+3pwa3wWOHSq1b7kkynMBci9z35kQgUloa4MzeuVQIeBprdUSMUjc0OYNVgZ5yGciD+sE4pPkzBH1IbnL2rsUSk6OTq6AYuCm5+J/t4+o5guKaTpF7jB+klGdYLhP7T5XWPny6NWcbKMUH1/GbKLTylUncU+TKJKNOoEO+0Jer77FSKWJ1gpYsapSXiPMMifajqDTMTHrPuixEe1cThlO/VpWcS57GRL2We0813Ri5KMKXLcZZ9jUu7q9CyZm4vCzh2HzLzdI7YIqCJgYwhWJgSrEuA+e0IRQyXSDWxq1qoTUENwlt8QnFWktzrC2+OLmEx1R1j3r+NilNnurXgXe+Y7BSDTRduP1KIREBkSxZ5XuARCXRwowVxbO/G7Hxlwml6f6ylcIT8pBfVKQYNSIJSCRvanHXLB4EmMa40XKMtPLafHxeklQ6e/8I1IPSH3erVJvJ15DlZ93OtzGWqqs8D+GTSPVZmRLH6RTmR4ejoIHmth/J3Qp+5fhBNT6SqisOY16YrdZ6ICxKax53S9v/UiQMWKUQWxagiJXW6dEgRVeUPuxoyz0AWI1SfQj1SvfYCv0neqDesHquAXcaCaUTkj42+Z04ThNv24f+MPOOhPrTiCMb5jugHGrLU5SXDFshKOZGtDY5NZ7ZzWA6jEsRYe5lcNOGb0RMeFhbih2ekKbW4JUjJyRLzwfESGUCcZ7DkWotRHlrdpovhXaKfPoB/+1uo+5aJNnQaPGqW1/vize+zw46m6j0LOiHYEarWJj6nuIzgRFVsXgSvkmxSPldMS0abFeMqGk0/QTx5a0ET6n7+3RVu0D6dY+YWlmfKk/j13S/QqqM9IsHozDuSkbuR+R04r8Wa5oaUoRMx1tETVWu79rFUT2wYwdXyV2EgvxAR/cVuLts1AyLGsym/1GXL5Mmi3kS3/Q3nXOVqkIk2FoUkqW1z2FM1B7i875R6FcQQ9wnqoVQoZOF91wihKLvY00pri3s1/up+dmc2zPVlPka8VvU/jUsg3uTnMHHXPJWy5qeaXXYZInG3oFKo9pDXFapGOQoMqp0alfQebI9ofIN1F96MXIiK+W4M0qU/8MnL+6UsgVhG3nn+TQ0QUFv1eK64d+63cKMow6DY5mrw3WYnrsvjjLWOKwvFnj6SMKdL1tx9H/ZmR+sXhsFQhBhsqmyCbJB75nBqCWt7DybtB3msX7O1un6idGqsQd10EAVJv513s7G1wDWcVvznXrGFdpJ+Wc7IMTfhoCpoAtYBsc8b+G8Hf+YyKu2ma/7Ycf25QmPw35/jvvhEspb83gt3px1bWYpCCuEMKDKgZxG7qs7rn1LdoYra1Sgy+Zo9S0OSY4Pf3dVYFcEy8i8VxFBMYr2ZbaB2hghtz/NeEylGCwxIwK0nh7bPo4ywl61mHu8l/tWVGkTLDH76cKAKfPWzFH0s4Hn/MVOKbVOILWUXrkwOXle7x97dtzXo22N7dnxdsH+S/a/R3aHG22NFd3rIQRQt0eRZuSMhJLqSxlbqghSOgRsBCLEOwSTv1C403rp5Uw6lr5bv2I8i+Q2LCF4QCZ05hQCvT/Hc424ph3roCBz5qTdphZ/OC9FDWQo9Y/5zBMNVZXZxQgcr2hMozQeqJl5+DQdmpFZWA7zh1X2QHtR932d/Iq+tVQbOTn7ZbbfJ+elH8GgyCO1EtsL5BUZMt6vm0i0qxXXGoxVZ6e8YaGjXg0/a0WuUZu/JMEkWaqk1tM5Vci5Kbok62K0+lzlCmmpWpicqYZCV3iDImvdOT+XGXhVDUiempluMu64nkVPHFbw2Gul7r/9DPTkx23YhKaoj4x30GQ5TSOrFIan9YTiTRJn9iTBH+2k8sQv9OJMV6kVLG+GNVMVVPSvAfF4Of9PAonhRR84sWXbkGeoI9GTe9lAE9uRmnFh1lWVZnXnueekwZO4rYvnzbloBVGZupupK8anFytekgNVAZO47VchVXIjWpSlhsW5rEQxxh5wg7IibhyHWLm94rq+otPavoPZFflLHDg6M75g60WwIDcTThsrBCmXkNtEQre1G/jMrYkaGxuLKcpB7Q5mRqc0aJe5j4UffQWCZFNrNY/yy4JuQIwly1rex74ORLVYU6FYXAVBKvXJW2j0/BgpUXcXnC1ZrmavT1emMm0SzFtc724nilWITj1XacAVfD5OXCZ+JzgjUXM/3mbPp03CVC5l9QCRJ81CZiTQO1db3a4/vZxZUTAJhvBB9qMKCKtKaQubfi2quiSUdD5gWKq0atpry0lX1aXBcsbjAGMn054sI5YJCajEpnjf8qT8h8J7YnbqTJddTDZia1TdA0ERNpOEIqFE082lMWcYC4ANVVA7uzAaG46qtdR2BVvtp10GaA/JLKz6Lyf4vyaY8Zatsy+Yivmxf3fz7RAvVV31h6fsI/ubJ82n5w8AqdgJhaHuJa6oyuekdA0Bp27aWxCZuoyuDjR2ya+2DgNa7qLqpqmF7VtbSdmtz1PkMo8c6J2JnvdUDnOVqN8tNqLs7v0KgcGJXApNSFrHemuerT5FkrroS7GuhznO3FvRImpLuV4ps6vZozaRyaUJQrkQ79wSIifolVdkRwPpFbc1OgYxxVcMqP+mWjrcpT8SHwdEmeAdfPzjo2SbiqM8obdT9R3mCocjWqbpHmakhz1zurigeq9OZqzKeWm1yCm95W6wnb0lzC5KqPhPMlKcQ3ctyNBJKuBgLBGW0XfTmh2UaV8yqBg0BE7VSgft78Ka20GnGoTY7wIDQ+UKPWeGMB5BcdseOq5lo8E8W65zq0466DIfNt1a69oDCPFewgSEkw4Gigknj74EN1BpBcrhpeEXXHFpYSaNe6d4gJ45FmA8et1ONu57gKAgMie5fCDe1x1xHFdbBuxMIX+9nr4isIq50oWKu6atMI3A/g+n5atUecPk8sUY7i2iis6IHi+lAXWo04Jnz2fBBksNyURFjSfsK1ViLLjUCWFc/QvLk/9OhdnHAh1vIK9xPgs+tZQOkGI/pRYXTVElzayuaBn3fVmYPFdUm2F68Cr09DEKjU3EeCxUcMtpcuQoRunxjZ208QCJ2Ib6oCg3es8sT3J+tPHMNl+e704QRvvydcSceqInfoKTrpxCrGyS57JDKB3k/MKDqRVRTpTTmnoA6d4P0XfWooInq9OMUgQdM/iLh2GopEKKd5LlFNI9iEZBjiX9231slmWPGK+CKjjXIIRUgt60upfYgqGuHsEq7pYv0oRaAX6I+240crTW8E/2Ey7a5qj3PW0GZZ4zPCiYuyFOoaul9KUP5/myF6pEU0KUEKbWiC2bPVBr4m0jf4jJnIM7HiVfZpB7HKz+vbRVvL/hmbxY3nm7UuKaOWVZrFPU2XfuuktGNisaddCUPnESKtLwJQcw0QuRU2qTm09PVb3FkphGp7/VyFnXiE+yQ1/GJ6tvOVaM/++5z9nEYr8V3/he3yXZAe5XS80DRD/dTptiwwgRhxtcNfEQVLLIrbQsjXRaujPa0K9+1c4quHLBl/o53p63Pi8aExaq7/H1fOXt+lc9pjou4hy9f7xdhs5v1MribAQAJXExELxVbD3p0Z6s5lHGefzAWNRJ8qBa1KgV6XMliZYVaz/Tl+Z05gqoRB3RPuS0zifplFSErU/Q7rRq2NbQ015K/0URkcHnwiuyg3Vz2M1WQD3fgSKxZNbgzd2ydB6a1kmQGvRJdjl/AO6ToqGZVggxWTMtasjLUoY63qGH9Ovtc/JMffPU9alw+7WCgxCEXD6raCE/R+RF0EK/uFL+d7U9rF2G/d+Vt3qJe7WtULoYBg5bGx1rSx5gjiJ8Y3zRQJ5Ek73EzeoHGnfvVvQC/c/MQoa7cgsrbsuP9Kr1qSQov9iRtaNKKYvB7pTCyimRfVebVtcRH1NdkKqms3vVj4xSNq2yHJiyKJ4V3k12qWP8drK1WM7JB5MO94jR5x8CLkWLoTXwYNicxAmDIuC4pr/Y4c/9U5/j45gbvkx7pra2mrCF8uU9TFcyhF/8YhiTPDffUU18o4xo2c6th/aj8F6j0mzu4d4+9T9zoigV3jnzUfqwxfJlPVfhWJqgon6EiWU8pia4/z5+f66UFOPSZgPvFV+IoTx2Ij45/rEYkIxx3bf+J1vBH6D1MbviKU/uyQ2MAVJ2pP1NI8bIJhbx0ltl0rFaJPfEXARSUA62cVMcon8Pz6KdrARgNBSHSvjyccb0P8QGU9yPJCGUXBNlBHK3kG7vnxJzOQVcROtK/z23JyAgMpqA94d7zK8eXtJzKKGMMBCItImMbsxLFwnxO1dflFPCr+eOoUNTi/KGbXs6mwgi8HNrKVddnEEv5bvw6euoZy+ywV34Cmqrobx6RNhp1Q0iTsw3bljL6EYJU5V+u/cbXuGemWEG6c4GxNekFaE7lc00gEeaBRHMfdjmox/h7WWvIlVlifpsIfvBuMtTZ3ZMhdL84txUHvSL0CmJITb1EUsd0gutTDzNRvDUEqBWUUnPr+nkLUlH3mfG2eGfe8+h+F5B5XzkSIW9REb8EQ7CTBMB0R2GIJlE3vfSxy25ZI73q+EeOgKPHHu5lnLcQxUUUOmngDNxH82ejla1jqKN3PwPX60BeperPCbkcQvozCu3ic+FxDeQunABUs6tMSykc461AKOhQ+IVGkU4O3xvE72N0Q27r3qFnjWJiclZlDMzGKhRhxwkSdUK/AMGPQ9aTa555QCMWI7Sr0ddEeX5wvTts8isvjExtx6NGLWsi1LFKwNjdTPQTB+sYmBswEfOOS0AjxVGdJOGTcnMMlSXa8lEuqREk5neUURsuplOWgn2Loz5ZzL5czCuVwdZhL2XtR5YMW5SQZaZDDIzb4Igq5PHg8hOI3FCmuyIlcRl2O6bkamxtLhz44hsvk1QkN4HhptFdBV7maNfwroO+8FPQmw5DxSSq4pMgb4gXikbIVD9v7UFbxHYFVLKGzzj6nSStLJ66U1wMSUWSWP47TMEO0TxRlS8U2bs6rWVFhGdqhloMRyYiYzC6rLLmxTCua4dyJ6OJ8tZw1fs0VKsjpTpXGbJlg/ucxjf71Ex06tcZwbESfRNkjUUO1qx5v00RjFvSoHj7TFHU8x/7SHVxcyc1U9y/1uifKusHPJ1dgwRwQPTrYtmbfSO2f6hb3iVaYNpxlbjxecog8i/Zh1PLzxD+fOMdWCj8XP7RG6s3FbQQvE4j50nRW3lPw09mhtyQ7j5qSozclUzYl2o6TUNcfO9zJmClgormMtOgTwtrTiKSD1p6Y0gFmEtuvmIuKfbMrtmIKnnHxLkfcOzQK6xVXAxEgtMMTEuGTv4hQobhRLRBpxQ1pBfWL9mFcleL1SkGFEljr78HnvmUPYDN1LxfuBSBH9+pcD1sS0vo/Jm3sLhcPlkmTB7hVSKm8eSwd8eMzTcvlS+TXHkZYGYwQsRCVrBAvLQHE6rIVYqtsq/YEH6oxjA9++2Nwj7lMsy3FhTKloLKtoFJtSzsdfOigIVhcYbCxIPi4q+arwPoTBaXHXRUnCl484SqNoHoJssyGHawLvAiE3/9R4lpkRZ4SWz4s0AZWaP1H4vTUGXJvEPMV9JFiNyquI6Y9EPybByvEy+NORGCFEjgauUK4odq1gREmPCQYCw5SLqerwvYizqeNBTWmQKWjuMb24n0UVAPETH4YHTPq8srFVE1BhUS9y8XvS5thRYLAJS9XddOEecRkWnRi5LgYQ3ZdXKziDOS/c0a+C97OLVctbgo/KDfC3FwaCAgnB7cSaymFep07Yusj56QNsjlLcADAvFOgVvLXDfJOp1kprocgKTIQR6tdR3kgtIeIqytuL/lN9Mramit0kyzDKhoBk9/dRbBBSy3LAuLVfVDtzdIRyAgOqpn+T2l7OBpsj5OuY4gjYfrxL982a2n03X20rXbQcTVh0bc0pIY8X7zPpM01h8aNJIw658VWTc2yUhqKDwr65FET5Kcp/MnMn0y++NC4bjRgt4oxsdGI9MUTXieqJN4jrqVvp/YZ4NbEaCvDURql1O/MuGtD1pEwZjLBcjd81WZZIQKvJwI6B3v1Xlph4j/lUkAf6UHTP2hgXAfXoAB//JpC+kNjfETYFsvLNuoBRm3f0gpSaUvfC6OnXyDQTk1z1WLM5Y6eTx8+KoON1QNicxl28yOMBV1HeAJKHozs5rjfyhv8oxQlmsd06kgHG6d0oZsjLPm9aOM+W9k+I1/ebfwfGW6Ie5xuK+yNWNXJrc7d4Oqs4OqsxNVNtsKuHiWwI4FdndwuE9iRwI4ExHX68zKOj3XusZXW8RjH+YcFK3+k8OLbwA8E4EwiYBV3nZc+cm5htZMom3uqL9P2THX+p0XT8vIYLBnMz7osFj/fiqKPV9NHlcDWSrFmf5+Qaz1irYglhgci39bjLitxboQvFFfFcUiEwKd9fY5CkoQ+Dkl7xdfnjomvv9Ep866E8cezuhKQsi2SftwRnq43M/uSZnIXxSqiG4he/S/k6cP/pfSD3P9m2NaKEN3Pw+5Vp11YXfPjisslZV+IUitS5xBQzLiTtwbCHfszjuuKl8tZ8XL4f2CJJDjSbFsOy4I/aLOTxDxC+3naFt7m24mMXBykWkFmLqQJgd6E+4hSQP+PKgW1SkGd2i0XhjU8qmt5sDL2zDTEbrGU4pVKwYvC+Ewz04IFS6pdpdjDqUQmhgqWKwXLItsK5xA9FvABY0B1NabBJKRIc9d7cimDvr2E
*/