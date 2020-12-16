///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// This is based on is_std_hash_map.hpp which was
// modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_unordered_set_or_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

// Definitions of overloads for the use of find with unordered types.

#ifndef BOOST_PHOENIX_IS_STD_UNORDERED_SET_OR_MAP
#define BOOST_PHOENIX_IS_STD_UNORDERED_SET_OR_MAP

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
#include BOOST_PHOENIX_UNORDERED_SET_HEADER
#include BOOST_PHOENIX_UNORDERED_MAP_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_unordered_set
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_multiset
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_map
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_multimap
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP

    template<
        class Kty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_set< std::unordered_set<Kty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_multiset< std::unordered_multiset<Kty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Ty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_map< std::unordered_map<Kty,Ty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Ty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_multimap< std::unordered_multimap<Kty,Ty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

#endif
} // namespace boost

#endif

/* is_unordered_set_or_map.hpp
+ljj+7+UQPGyv3pGlk1HUjIn4LO0+3fL5bxzvkx7mfyOXykrDe39KR+o36fGM/mybaaPk+j+7gu1b6S8g93iFnx3XL5LTVzk0Hb9dHUfp+TuXOCK/15leYkv581pB1HF7m24Q3upT8n3mFyvwg2rC+R6AMu57r575LlvFGos3kn7jb6vcr7kJmbnylsJ5mfNrc72h5/7OM/9jEPWNXX5t/6df+cZv/6df1/yWf/OvwPa56s9rnN1/ae2ftrFd3LMwXIfq+F+OJnuy2W5ra8+w/R+bbrz2PbjMhiH65aZHO61ZbTcIVj9+1PsrhEOv9d83EGuCWxmjeuO6N37Q+2eEV9oE7OYaS2xm9ZFWWkSuFrXQxueh75X9pelLfVB5d6Gcl0cZzJ3AXPPSVKq9+/Vst5zYf+ura0PyD5HoDG/DvvkGUTSB0XI+2ydD2r5yUMByFCejRB+iW2opQ+7YrE9a8nX433Ud4XJtXi6PoarDPMc2XK9rOl6F9mO0r+jSetPtOv4ZNod7nxqtZBpv0q9xlamPUjaQADDcyHUxSOuaef5+Jc+vq2uG5+lXHwsJSRm/0fcMV8I0e/X8+c+Bv5cJzHHMvRiRDESk8udqnG+xtgWZN/bEKdA4nSROJ0Y7qaOS3RxMpLZ1q/G8/+rvq5KrpWS+OdxDAH31qE+a9/35GXPdx685dd+uxs8Mj32Dh5Y9mQt5fuK4ZNa5XXZsunF0EFbGpb/8S3HfK9Qvm9xePmmi+3jDt2cP+6JdQcfP86xMdf3g37p0jn25+U3Pzp6RujZyzeuZLouV75/1a/pC/F9+74ypH63AQuvHNWS5xvWVr4/8M5Tp39rOXrZq9HZJ17r+8oW2lpd5fvcFut/WjX5jhlrr7rh7oC+Db+oVesj1/jrvhSYPHdh9z13PPLkDX+0O05PWeT6/qF77ht5U726fwxP6v9w5mf9WWf5NVK+P7sp/M7uRzIvrjq377nV+9o8xnLkGr+zLGPdTxWdXz95y4hWEZ9HcQFwqJ/y/Svvxn33UHrLr/+8pXjkR+2fOud6dBHfr3ngzlNfHo2MXHV0an7a5vvPUseu6Wp9OqlR+pzrbvpHw3XODl1j6KsmusZT8vn0trsSHr5ibaPjtYN/fuA51kkNXPW8I2XK/nrff3xob6c/79heSJ8zM0D5/t4n7jj87hsLLywLOtCsW4NfJrBN7/p9sF/y2BOTz2Zc1XHH+uVLHmYn8PRlyvdLg3a8/PLCFteX7Zn/THnXmVdz3Znr908NHX/+4sCrT972zadHk2onvc26wpVP/fMh/8mYlDr7oys6b3ZuW9WE8TRUvn9268JbIzYdSPk05PdHf+rSti/HkV3f19mb1q7Dip8HtLjQIrD5M3M/Ik/X9F4883KDXStWFY3+8OfEtJkdy9mfc31/7cSkFp/HnY9o6GxVvrLfBepzc33l+59/vmLXgz23rBn0RkFOcL/P6MRPuub7I9OXxp29bMt9Kx5sWn78/m1HmI9Nle9jH9vwSYc2p37++tXtBfWXfsH0jnKNZ2GbruH7Q7Y/8euSZwtPrD/Hga37XfNx0rMPTvzkz8fG/vDw7TuveKQj27NRrvkVGXlf7Ffv/hY65YNlrabc3eqYaz+a7/ed9h+wtu6E30d38j/0VqdPuXGrn2t631128vU/f9p6fsnGNiFPbZpJHQe54g4Nd/x846x53eoumtdo+TeOk5wzrad8//62z18f7ki7Z9W/l859st1D/PacLGMlyrpQ/l1ILrVR3eca5l+r4JxsZ5fL766T312Gg+R31HVBY5yFLXEOdsa52AMdOBrn4TlMYIhuzvjwNhlfQ4yV8WXWr1VQF7MwDJ3YHxc=
*/