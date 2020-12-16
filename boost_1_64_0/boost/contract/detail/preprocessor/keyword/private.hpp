
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMAprivate ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTYprivate

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `private` (this can be
//               checked with `..._IS_PRIVATE` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PRIVATE(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* private.hpp
PdXrSTEZBVMGi2tw5vb7kP4dDWbP9uOTMF48xqijLGHxwW/R3eG2+nrwDq9SESa6xrgFoaQ99eIB1/fRT59uTVfLHwu8uad9rGn04ANr3Ud+xxmTPmblbnJSDtSiv17qxEvzE31wcEV4nd09Fu0IPD4vnMXaiOe2vTRDHE99FE5F4Ile2vsl9WhxW3xYb6oPrubx3gvO3W6xBm2Dd75E6R06a5mWB88tB6r5ufuNquEzYtuYjziyk68Quwwf0rxzYfnLYiXPb9Xjw4bS6svty1Wm3Xy24Ey5Q+sOSkXDtXXtFSHno/Da5/ZVT/AbKfRUvlIDfXmb5HzSADU6Hn3RgzvWwGQa6cZm2juZnJHPQ+nVmWK4b6+e9Fiav4Dcb2UPxP3aqqeB6rbpS7zOGpxA98UFex96LcP0/WrzM7lrwlJ52+0Puj+lmhiEMys5P3HfvU+JOf5MKXZt8fWn7dQk/PunkX6TfflMOLPPPXXA5yz8jb9pb530TQ/47M0GcO2h2r0t7gOMuRJyhAPBcyt76epswXmQ0mre5zPSYTma6bmoiyb83OVO8u0BPGoIU31+QzR8wfN9XpZzdWgO9z5Pe6ZLKccTgmfUrN0Q9+DDi4rR63V54+A5j1vWu7i+RzfrTNdlwZP3Jvp/vLauPXyK4Aff77sEHpcOzoaH3Vd96FN8sjbpPLi9AHzaV+9tuV6vHFilTz/Qv83DbwU/DsFqsRhFB/yE44rwkPqvJ06EPUMFZ2nj8WI1Kca5wO0w5PpjjbhiDv6YDbvX8x1v6e/Bk0q9YdqP9hP+tj5fwWoxDcZS8zhduMQ91Oe5POLJi4TW008z8ZB9qaE8bZUn8dUreP1kVFLv/WtrvWknjd2UbnuaFo2mD4mTOrx917D6bYyfXGuPfwt1Vj8lYOtwOLkNh9DsH0y3Zk2cacymHuHlm/H2+WjFPXKjn2v3FtvEoc4p8nh7xOCLufLOmh0MnqWkiwdU4UH0T1oM4a0uhJP2d5ePDMk3uvY9sJIKZ6iPlNajirU5JUYJ7v3j/6xvBb5UfP8dz3Ppn2f8RU9E7H9ZHezheqZlFd3Ax3w/jj7nmXv5XNYyxnlS37OB7+DXFJ+IRX8aUR1ehJcF4GOb1jREQohW1ePkn+umi9DGPIs95jX87UVjH1YDD6r3ZvDjV/XzPt5fJx4Z4FjqXM4a9McR1dTddNduwi+9Yf2fl6t6lNX4vZ+2wvVEe6R8675W8FQP9c5CMY/i374z5r/VYLQeXCY4W8WaX5KbeiSlBsNLe1SRsmoer6bJRyPoxSS0FS/jP32YvzOX3v3w73T5SJ/k52Fb6CvEHOFj9XOa+uxHeshfHcMTa+UFD17/zOMe8pdXo+g1GEtjFqId/zvBc06C24vo3B/1H3HDwgxqltb7W98qLjXe2Uk3zrHnnk2tjLaHlsYeQ3L+Qw1e/YxWHIsLprkGPEndl5e9FZwBxF/Z9Qmq0DrqLP4ULGiqpw2nFm6jyXZao+bmT58u5G1/td4XThgTvphPG5XNznOI+7EbPNRwYzrCn+H9VlWsO+757K71UhNRtEaFdu6znF7jtWt/o1d4m6aI1ufPScfbP/TOFO9WwEmn6ADr771N+mFwjJbO5M9rNG40bNixI1gf+kb9/ziJX3LNG+qzzm6aryKupuH7DxdHXDhqhn6GOAwLejr2OY5Z++3rrXOUfrua7WpME+1jNj/7+JnJPe7ZOa0+2FB+Q46klw/ljP9Dnj46lqb7kX+dTSsY89iy8lgcvqEBC02F07TxE3Tf8EE0Cb56B3++1QAv5w7Ox9FsNMWSj8J0iTn25hfov8Zf+/kVHjdEd2ymnye4n7W+OQCGP2lct/A=
*/