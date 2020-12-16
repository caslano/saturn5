///////////////////////////////////////////////////////////////////////////////
/// \file empty.hpp
/// Proto callables for boost::empty()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012

#include <boost/range/empty.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::empty()
    struct empty
    {
        BOOST_PROTO_CALLABLE()

        typedef bool result_type;

        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }
    };

}}}

#endif

/* empty.hpp
xVYym2uwLmq6xch3Nh//X/4+N2YTtLP7MIswqmLxzgZ+GMhsltFgf74uDKbfH/WekVS3WWO0XIoWLEawWMHiBIsXLEGwRMGSBEsWbL1gKYJtESxVsDTB0gXbL1iGYJmCZQmWLViOYLmC5QmWL1iBYIWCFQlWLFiJYKWClQlWLliFYJWCGY16vxkLZvo+wy9zZXq/xjoLtm6c9kwbwewFcxTM5b2G/qlMnx1Y58HWddGe6SmY13sN80/Z/5lxPmzdPM18BfMTzP99hrkSoOz/zJVAtu4TzYJonT7jeo0OZuvmGAUO5BbyPsPzQ+mZ+vybFRTG1s02CprOLVywCMEi32eY7zOU/Z/5HsXWzTSaPo0MMzWa1ukztXdwDFs33ah6PW6xgsW91548jlemf37BfxLYuqn4J7dEwZIESxZsvWApgm0RLFWwNMHSBdsvWIZgmYJlCZYtWI5guYLlCZYvWIFghYIVvc/wq1iZ/jkZP0EoYeumGI2ZyK1UsDLBygWrEKxSMKPR7zdjwUwFMxfMQjAbwewFcxTMRTA3wTwE8xTMSzBvwXwE8xXMTzB/wQIECxQs6H2GX8HK1PdNZiFs3SSjqhbcQgULEyxcsAjBIgWbIVjUe21092g6u/791rtKDFs3Ef+dPzOW1unfU/H9j60br32Wiqd19N2X1iWwdZ3073+CJQmWLNh6wVIE2yJYqmBpgqULtl+wDMEyBcsSLFuwHMFyBcsTLF+wAsEKBSsSrFiwEsFKBSsTrFywCsEqBTMKe78ZC2YqmLlgFoLZCGYvmKNgLoK5CeYhmKdgXoJ5C+YjmK9gfoL5CxYgWKBgQYIFCxYiWKhgYYKFCxYhWKRgMwSLEixasBjBYgWLEyxesATBEgVLEixZsPWCpQi2RbBUwdIESxdsv2AZgmUKliVYtmA5guUKlidYvmAFghUKViRYsWAlgpUKViZYuWAVglUKZjTm/WYsmKlg5oJZCGYjmL1gjoK5COYmmIdgnoJ5CeYtmI9gvoL5CeYvWIBggYIFCRYsWIhgoYKFCRYuWIRgkYLNECxKsGjBYgSLFSxOsHjBEgRLFCxJsGTB1guWItgWwVIFSxMsXbD9gmUIlilYlmDZguUIlitYnmD5ghUIVihYkWDFgpUIVipYmWDlglUIVimY0dj3m7FgpoKZC2YhmI1g9oI5CuYimJtgHoJ5CuYlmLdgPoL5CuYnmL9gAYIFChYkWLBgIYKFChYmWLhgEYJFCjZDsCjBogWLESxWsDjB4gVLECxRsCTBkgVbL1iKYFsESxUsTbB0wfYLliFYpmBZgmULliNYrmB5guULViBYoWBFghULViJYqWBlgpULViFYpWBG495vxoKZCmYumIVgNoLZC+YomItgboJ5COYpmJdg3oL5COYrmJ9g/oIFCBYoWJBgwYKFCBYqWJhg4YJFCBYp2AzBogSLFixGsFjB4gSLFyxBsETBkgRLFmy9YCmCbREsVbA0wdIF2y9YhmCZgmUJli1YjmC5guUJli9YgWCFghUJVixYiWClgpUJVi5YhWCVghmFv9+MBTMVzFwwC8FsBLMXzFEwF8HcBPMQzFMwL8G8BfMRzFcwP8H8BQsQLFCwIMGCBQsRLFSwMMHCBYsQLFKwGYJFCRYtWIxgsYLFCRYvWIJgiYIlCZYs2HrBUgTbIliqYGmCpQu2X7AMwTIFyxIsW7AcwXIFyxMsX7ACwQoFKxKsWLASwUoFKxOsXLAKwSoFMxr/fjMWzFQwc8EsBLMRzF4wR8FcBHMTzEMwT8G8BPMWzEcwX8H8BPMXLECwQMGCBAsWLESwUMHCBAsXLEKwSMFmCBYlWLRgMYLFChYnWLxgCYI=
*/