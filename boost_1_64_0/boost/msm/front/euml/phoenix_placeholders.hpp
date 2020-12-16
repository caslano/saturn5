// Copyright 2011 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H
#define BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>
// provide some meaningful placeholders (instead of arg1...arg4)
namespace boost { namespace msm { namespace front { namespace euml
{
    boost::phoenix::expression::argument<1>::type const _event = {};
    boost::phoenix::expression::argument<2>::type const _fsm = {};
    boost::phoenix::expression::argument<3>::type const _source = {};
    boost::phoenix::expression::argument<4>::type const _target = {};
    // this is for state actions
    boost::phoenix::expression::argument<3>::type const _state = {};
}}}}

#endif //BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

/* phoenix_placeholders.hpp
QumQByyelXhaD/dO1XwKnLnzTuzlrpOAgdV9Az0pY9rP2EporNHUJotTrU06RRqnYZE7fFZ11W1hteoPx8g/THF2LOLQScRU7LHTw3hrPtma6yXR672u592O08yPO9hLL2xd5EElOf6MwG9P9X0AT+PNVp60OAeGfsmyxHQfnnnqiJ+VHTqD1sPSUfbP+bS3OmBqDuYd6+pUa/9WEWClSl1RELZA62vjF6fGWHbTVqvVjDjDRb6lgYtvZpTfYpXfd1X+E3FWZDgothwMXBbQl/pokAn8j1W8HzrNoBNlMS51HTbUGQuUNpbKKrvlxSk4ixfjrBXwtmChrB22nVb5H5ip95NmlIQ4iSViuM0mM1GAU7R3zfQzeJQUadD01eEGlwgVWyOo5s6iyvdsiGly34VqBrJA7LBtfW89OdPnTpAULvbm3FkezMvksaSisjiXDgRnw6vqU8zU9ky8VscP2s0yH/U8Maza85yK9z2nGXXaaZYVlJc4hyzK9tvaqChbM7bYaO35ES3/ZrvVLoKc56/256lq/t6m4su7UztroxOU/MFn54/rDr914mz4rGpszPQ13Q/dZtbKxOIhD4eiEP1qDP92pp/tgsDHzG+3GB+yIkbeFNS3S0ervWyunv9ZFVLXFYNIKElVTL2sOnurPC3so2meMqVDXm+esWBVZvFsC3vS9PKpxXISr02dBp3F59q4zFtYNXEPqdYu9UBwqirDp1SeoOXkYaeZNnGWXBZXFutAoZbkAnPHqN31/zXX1o4kLvLUxdpUrrbK8AsFft+W2vdo97gTdbDkOsoyKdZqOQppBCj34i19L/PCMGv7Ec+Xx1q3xl2k5c3uT61OFESQFdTkXSbB15UlVnkQLs8cimV924/ZGz3aeBPaicwtTCV/WjB0FzcnjYr2RIOGFZLS2/+TMj20L+NozCp9x/OGjmLSm80Dtq47i6R7d0XFpGioYfPyfLAyvgXXAA/mDs7R44Q9rmIrwMqYuJxjR6lv9zUUbLmHu/yO6fE75i1Oqdcxr9Leb+FPDxBAdVbhoVS5+PhqLlhYf4DKjy9jTXeOyzRPWjgM1Aj3i9Inl8OUWRYr7AkLy5U6L3EsCivzP16HZZZXyJ9ZdVW4RQsXlAdNwFizEq5h14dfiUuUxD3RwnmluIJVCSUk3JGd2qcEHifcYbt9cAtjoFtYztTvh+x64PJcVJd9gGWa71SxbG7kuJ0ts2lRtuEtpGdr4ryN8WzAgSeAq+bqa00cy1qZc7N4VDGdqniumDwhtj6FR7Cg2HKffrPJ429NNkq0ZKSxeLzRIxmUldd0UM/SmFf79XtNHgwfmwXtO8HHy+U4PUZ6x7qOcG91Ou8Oxxe6Qrzuke7u+8s1gZ21u/IsLHV7nTcSvRTPi9iORL/z9QodzVfRSX/4k6aeEccOlTjwv/oCwzhd2EGubuFGIcLVd1exSQwHaBIlBsH5bzAsKrTBFIdZ+O0Lgy5qnlX13tL3/aAVxVGB/e/Ucfw6yv9kkoDZbOPUc5556jj+X1w7dZQXcIYfuqtY0Gkv+dyWfi8r/KgFeVS5n5JchvaRpfm43MvCmdBHprvl97f0s4DX9LK8SGJKR2wGlEJfpIBp2q7OE1v6/RTHgSTL/FCmoR7S7aTU+8XeS3q9cNENsiz2rLTYIduuF7XPEy/pd/+m6+de1lbK9Eo6QNcUiM77/iW9fXBNCaADqt7r2NnMEEE0nlXxnzf44ySKIq/VUvn9Gv4nV+NG5T+WF1Ga5GFY6pZvbAt5T7VnXVGxJyDoKfwOxMlMELHKtvFFzkDr4ju1tHH7Y8fnTpn2loCSXP29HEt3xbjV9Ao0Q2+I3cDduEjpK31w1eg=
*/