/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0830)
#define FUSION_REPLACE_08182005_0830

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct replace
        {
            typedef transform_view<Sequence, detail::replacer<T> > type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace<Sequence const, T>::type
        >::type
    replace(Sequence const& seq, T const& old_value, T const& new_value)
    {
        typedef typename result_of::replace<Sequence const, T>::type result;
        detail::replacer<T> f(old_value, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace.hpp
FSLSX41EpAs4kVrBLJWa5kCnKO7onAA1CdTs2C2QXG2dctH/4kCG9J189p8w+vamsoVuA6bCjS0wsCcTgszFLd/8S8vzU0YFMsUrAdBFSHmQtV4gyTHA9qCyAjZzLy9W2Ff7TJxpV/hMGwW44g6eLcRM+1b+5mwYf8ZVZW0VQzAavg7jVjpnR2Mg0gLt8hvjMkfhdcba6wLZa/MvG8Mu1k6/SnYqxalAkKVmjc/R2anAcRreT+84PcKsc5wWIRW0fs95XKzkM5Vfk5VfEx6nCR7JV+wgfrzyNPmVPo6HfnQ4SReTHtfFXFLlZDY9gv/ZqZqk0k1rjqdDrpK/MUHO5wQsVw5zs07gQK3KLRVUbhuR+kyl7xj43MXaYdJrhKJ9tkwL2sTIRDVl1TmXuk2Pg60kWIXZo79Nh3LVqBQCS36BZi+vcXMrPaqxMU0c4NHGr2rE0MZ0pjmWIc7RJPdHeanTYwKj1z9GGFz3lJLHRaMf27NDVXKkgy3/74aVpU9lNdBECrS8rMdGXxUbcfITH3FsYNaTlhABCUz/IM+hYs9T2iJFLhQtEvDRj2b5oxasa0YqDrubeqz9ozz/U4Hiw6ujj/3bPdPHWYhErGhIH79kNqCPDeWECFxfQegBR5A0JeHrQfkQ44klVTD9X13GsTRESzP3ftiQZqZ6ohm70qmFlmbqQhg3yXM00dFOt0x/aOfzpp5pRx4vaOen
*/