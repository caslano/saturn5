// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#if defined(BOOST_BZIP2_BINARY)
# if defined(BOOST_MSVC) || \
     defined(__BORLANDC__) || \
     (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) || \
     (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/

// Specify the name of the .lib file.
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_BZIP2_BINARY))
# endif
#else 
# if !defined(BOOST_IOSTREAMS_SOURCE) && \
     !defined(BOOST_ALL_NO_LIB) && \
     !defined(BOOST_IOSTREAMS_NO_LIB) \
     /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
#  define BOOST_LIB_NAME boost_bzip2

// If we're importing code from a dll, then tell auto_link.hpp about it.
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif

// And include the header that does the work.
#  include <boost/config/auto_link.hpp>
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED

/* bzip2.hpp
cakZSY3Su6Vm8Hcx7J6Ukpqb0TjVPwfXVnW4q8S1P/dP4VrY6YqpbT5ukiuv5bQteprCtRltavS0oA0pou+cMwKMK4Loq2W+zsyz+Ob7zJ6dMe2pkZO0NfO43jlB79iDPVDkVxniOeAa2BQ9rr7Do8fW9RI6diDsjne6smWmH9xU7K0tbaSGa5+nkXcSZvwhYeznG6Vsq35rODbdNPk37i7Jv5h1R2ukMmEdTb50LMx8iO1dVDY8W8JoTJqlmPe+ORK3haGjKfmPY8byXnsyxsTFm5/aJt8ift5nXjrLWyeatU22MrE3QZnYHb8my/StP5L7bHKGoK8ZZg1URG/zff1Q3Lx6bPqVfeuwHmruXcHWQ/n1eZdFn1vqXMsa178njzJ1vZNXz/da9Hx3vJ6bvuAUfahZIfIczoTd0XPnbqPnvGrQzmB8vW3e3TcR+WmhRu4IF9MpFGLUan3XQNh16w8ib52X9Na3W0TmCWcNd3gYY+kj2sLRRLbM2fjkyyPykoCR+2r/QmSu5yzsdPrATWz9RHs4ZHg0/VrDDiIzilFUGmGlOOmUm6EYy14ahGfvd7p/ZojbFmcm4WTKNUqke40w3f6de+5BtyM8fZEt/v6dvZ/zMwkjVcMkCmJv542DWRO6VdyepvVLch7ESDuh996o9066IL1fpCdnv2c2vObu2L7cJWJvZe3LXS9unb6RvpNlHtXWbzK6Zea65LrqkF5vba6rTvj6U2lHOvL7FeUyG74Ge7pzovdEy2fxQDz5978276qvuFfenYUyqKvpm1vLI2F552Bk3BPtW7WEO8T9J6GF6NQL9N8/hJZySjjWNsy0D5+I+42h9sRlAnG5DV8v8retrBKWvR3ztEFp8mx9iVFHN66SxoPkWmYonfBn83TrMdH1QyeJW2rNOwaes/zC0iJvmH+S+w5GP1qrHkb9pXjfXywoLpll1ny9J35+GKqZgyo14VWK33F8C59idPUvcq2n+K/G/6n3ufYR/v6fkc8W97ZG/ndyvyWhmDXBBfPmRPPsMNhU7vGF9OYGkhZ3OC217OrzcI3wpA80VOzTQyZd0CF/n+FSiUOOidM68dPLjO12ir2lWZeyUfXO7aNO60s6DIi0s6nZGakVV6RPoHMatnRRnUR91MkS3gCnGenYjqfqdpA+6jLko33UHhqHfcRhFnHISFk+K/249K7pXVPDrOpKzwTJVBi2/DtJnrs/I5KsyBhZw8rJjYSVmpS0fCIPwCKuJm5oTR1dq6FyU1QuaXlueh8E0tN899H8aiL3meVM0vv0pw5rwvX9OBbivwgzGzNH12wXwrl6rVj72lm++s22ftjsW+/pg1DmZTxXy7oI0TvibPoZ1b5+Rsy8/UCHH3HFpGOKMAPc+aX7PXVWXN+ZONnf4eDPWj/Z6iBkg69NMLImP2RC1oy7LOXB9FuPFr8n8nxhT72wpAwxM9cyS2SyzZ4257n7/mTX9CeT7WOjcbHrceueXzre0fzimXxtyp5jIze6lkiNVB5J/myM5A+Z404A2tuUlvAFkctPSgm1cdaFm9nXOtjzzLzzeF/chydF0/NpsZ8fyg61sOUr4fnfnzHXOa/ogqJ5Ne8C+myXPcHMXMwrYt/hnO6MsOa/hmn/LoU4viTu05Oic+QPiP2UcFfenYwMh219RsKMfzfSVufhfyNuk5Pa4bcnbxquDN9m6qvXxa2Zrf9owvS9AzFrAD54wHU/JnxOqHVM3dJW02G9uC8JH0/NeQtrjnuFPtF+c8h5UdzODrOOMbQm9KA8+8vEdYmk3QOhmrKxqLygrNzUi0f9UN5R8cxvOJn6LqBa4jkkyVpu1N9lcr/bwp2cS/X9E6M/uXY=
*/