/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_07202005_0857)
#define FUSION_PRIOR_IMPL_07202005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct prior_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename next_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* prior_impl.hpp
gHLqmhd/jfl34rQJsTSNX9EO2lgjWDawzN5OkJxkDt6igIGTTKlUKNd3Xgtzvcziugn8qPlPfENXwfyzxz8VCaLCc/LSD4SbylEfqF5dRAes/IfZIE8XXC9n7eCDifsj3D9isOcacuPdwWZi5/RThHYbmWrIaLeeh685CrBlGR2SckaPAHPrYp+QGtFii5sIL+HLYrdC4f3PQJy1EUDY9LpQbCn4yTFdhynODpBzSWS66I246fcJNohtpCgShoBgIwZ9+qslgr9yRCS7Z05WenVFeGCCtxlZsWBXkTGtIoXm7Jcqy2VvxSgilw4/FVmk9mwNaAqeRLgYRp/U9rfFY6rSAcUVXrpCPXE7ByLoRIksgOJi5LymuAsygWJBhDhRB2GjHsAv10SKIYIBstiHsCWFmO8Q90LYO1B0kLAAC6MTRQsEXqZIIOaDhHTUAk7wi8DyEpOwXAGElyj+pSlF4KAEFWKS+I5QCkUD8fNoEEGjOIoonhXfF+4gULyQcxXCRdSGHkFM5iKkQjkgwUECO4yEEDt2nWhvURfk/ibzTDqYotsNF9LhzbRrGxUX4nV8ISjyWI6qmfSfkSG2Jp61XgA2UN65ElNSpYVYEUoRQgXGBkNYJlHcE6OJ1BA2MVZbsADTRAr195a+bS4wUkwHpSNFlZeiNbKBovaUVed3YqE9LWyQDYFx7Rkok0EYqunyRGa90UTuZPYc6VI9
*/