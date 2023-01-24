/*!
@file
Adapts `boost::fusion::tuple` for use with Hana.

In the current version of Boost.Fusion, `boost::fusion::tuple` is basically
an alias to `boost::fusion::vector`, so both data types share the same
implementation in Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/ext/boost/fusion/vector.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion tuples.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion tuple is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/tuple.cpp
    template <typename ...T>
    struct tuple { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        // In the current version of Boost.Fusion, `boost::fusion::tuple` is
        // basically an alias to `boost::fusion::vector`, hence the alias.
        using tuple_tag = vector_tag;
    }}}
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

/* tuple.hpp
R61ShAbUaVBqQ7q01F3BLkiI+CkKZNH92IeQYchhRVzE+YojFwvtw80jKPwKXebYOsrLy4HByImVnR8t66Vvx+MbymrmvHgjrz+/kZP0Rla0QyNHYMRvb0umDZwUbeCT70TZzOvakmnj2rBx6P5mPvYz9DR6boni8Pon9JnrydiuQkeutMDpdLmpHl3MZ6V0hZusx3lrG6wgazCgtKp3HEe6QO8rftvKCD27WtL8bnIDZsJ74ehEoweKmTz6xEb92AveQznJK/SuLe9bp170ST1iqZ+PLUPStWYvdcTy7OulUbdS7OAgTSBpw2H9lOAIhfGC47d4VIPT+lpkBVuNQBY28EoAL4qKUPc2hfRAPjgg7KMvcYm7KtSbDUoLyktbjQWQeULT1IbDommpZnytoDG76Dpvx8YvIEsrEph7x9Utnrs+QzO1cgWldfMLxaEwV7fgSskcKeG1HOUd9Z6YlL8TLxcqbiT/3c007mx+9kqPSznhIjvwlaEkvCheOFVKai2xcBqcNFMugw6FDwOcdaLirttTRom7lKpsVb0rFEHhcW2mb2cdBH1PNcBf8iwys+jeUumMmgpsmSUZ+a+FXRDlS2Zq9Ta/b5UlLQBHBul7SqfSVn+MKtUHpEzFi8BqttzDWeXbeG7g0DhqOewklv1MLyBDUTFHWzE66eLw2euG/x2nB/4nGmiKBu4fh8dUa/2nSNblF9ZDSa7I
*/