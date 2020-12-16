/*=============================================================================
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE
#define BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_complete.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence>
    struct is_native_fusion_sequence
      : mpl::and_<
          is_complete<Sequence>
        , is_convertible<Sequence, detail::from_sequence_convertible_type>
      >
    {};
}}}

#endif

/* is_native_fusion_sequence.hpp
h6+Cm0NYhca96akIx0iKpbCsPaHizg5OngPzYXMncL3FvsBx7pxXsiJfNV4hwBtnJ+uji4XX2t3Zae8QFhBjH9WLE6+oikop8prZ5fHBEJUFFIHjUCKcJDlJWWQOhA24OzsDsjcB3LTnbS12J7s8nKANac8E5cZmb2xlA0k8CelUIKvyW8i1M7DDQuWnLFNmURJ+cWLFZA9tZSMJPHhHg1yWv06osAGdwZrYtV2xIqyxnsxW6/drTuabhl/2a8pnEdYT531IQVpCAdsrb/Km+TPUx5H7yL1x5OycH80PXt/5oLeymRiVaXBcg/5qGwGE7k6/hXDKSlGGK4q1OSav95OvXZ9aCYzxb3X7NFWFMsfWZHQFrYwNGOJTtthCAhe0BMOX+erqZWQ4bz4vN3wG8SnCpfUUQgktgZUNQYHvCPNJLZNliUNKxP3llwE+S7yt44tFiuBFRa9Bm55rwBVGN7Yhr3z3Y9p4GKLY6MkykwWeH+94ZyN3KyTplNOWLGZgSnwtP28zfts67VXZQm2I5GpIUfTi83M4M0Lu+lY+EJtYyZqsMxqNgDuwLrfyiThDEzOaD0mb4ZOv9xX/PNZtipZ6zpZpSq73wT8hJmGL4ZQomy1zQwLj4/rRsHTx21mPhcsa6aTGssAlDfwbPT/5201ZN2OKUQYnSX6xxrY6T8FyVBg72P+cX9zDck9Fclyx7ItRRGSB5Z6O5WxWmlNHDs+7/n1mK3crxUKToJFYmijkFIW48EiW0egFG24KZmczkAV7mFZ2T4aQlChx1OAa8EbYK7B8porySAQWr/JgD4PqUlTijnJFTu+dXk38Ql7eygYiE3U2CUZirfi9JlIXzMdWPpHslObcuzof68H2eJCfnWzsI8DnCWOU51Y7FYncgoE4Si3mBSmWUOSQmeTi+I3g0wX7CJJdJaj3hhSQbf2gWtndyFQwzjKydo2d+qd+CslL4X0JnJP9Xh7sWFr528KbmEzO5PLsdPHGTdxesFdDsk64rMPgFVRbO5H9EupTJ7VP1FgSa9rCyZvM91rZSEQ0uUoLMh/8TKsGYatq+uhRjOFSFqNLIHILBmIvf6fVzWCo6Iv35PDgHMUtIeA7juR1Sd5poat8xvIwT1v5Gz4ax4owRPDuPfWZrRyjtcHUK08NqR+KNWlwTX1X9+fRqXBvo9NbLe528NZqmuUa1cUxfSGSNUoo5YwlopXd1PtXO9da/wPLtCqGgFkInDEMqrcjTIhkhKB1NA6P83P82H715kXTB2wzH7syIs3OMqPI/qaMHQpl7NxFZYB9WVvGnuSa86AsOTiZzy6aj9xjsG9o5V8QjWFSGLpKww5GmVUe7shQHRVxIiufih+sLddZ1Pvc93fAf6zFRsI8tctwFrOD5e3tgzePB/FziL2B+Dix0jLrGd3E8+mjc0JuEYQLJEdlMwuKbALxPDzK5iXECv8uHotFKmWSgu/A5eXW0CNd3LxntbhblsZUWMhk+IKDczPk6f9u1z4XImdGkMXSCZMP4bKGbNlXXfsMwnkiUmRBR0hLtom9PimgyYN61HEPu4VLJZLVQ32jIHwGfBvCSWIl50pxA+SU1+GJH/thvLXYQCTXgmru60G6Or3RN8ISCDmoEVchQnqVuASu5XF69Jer3EMZw5Ee73Wfx7yBxRwVd6ReylYD5yGk322wk4O1F2MMzV6boghN+/bOzhCVbop5tMVEEnTwNoths1uay1S7gJPDDWbdl5UIz3sjOY+eJzJcM8zqxK9L9tXxcIf8pnNcxPiN/My2jEKWSc1tXH2Xzw9WDz3wKtLM/90WF4hSilvFzKq+NZvH5s5gI2+wvMmmJJ3kKH8Dy78cy2ujZTY=
*/