/*==============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

        template <typename... A>
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
            typename vector_chooser<sizeof...(A)>::template apply<
                typename proto::detail::uncvref<
                    typename proto::result_of::child_c<A, 1>::type
                >::type...
            >::type
          , detail::map_local_index_to_tuple<
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        typename proto::result_of::child_c<A, 0>::type
                    >::type
                >::type...
            >
        >
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION(A const&... a) BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
        {
            typedef
                typename vector_chooser<sizeof...(A)>::template apply<
                    typename proto::detail::uncvref<
                        typename proto::result_of::child_c<A, 1>::type
                    >::type...
                >::type
            locals_type;

            locals_type locals = {proto::child_c<1>(a)...};

            return
                BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
                    locals_type
                  , detail::map_local_index_to_tuple<
                        typename proto::detail::uncvref<
                            typename proto::result_of::value<
                                typename proto::result_of::child_c<A, 0>::type
                            >::type
                        >::type...
                    >
                >(locals);
        }


/* local_gen.hpp
T6Q10k+l26WfSU1SaO/aW1XFJuRP88zzQMDf8ItBcYcLROJeOmGldhZhr5hrl6pOWhLy0OFF9IUp8bmwcngoF6nfxce7KtFiXOkXqcXFEeZo2tF0xZUiwhRuF+4LvsyvnF3ID2LiV+D5Iy/YKMydohyVrzqOLCTEiYkRFvyXBNGlEe75WU6lVWWe8R7lcGuynJhfmIevnXl9/rK6Sn7wjFpMBx+ozPwn56X1OAO6urK7HMEF/OEycSxZNNfKj8yj2URKFjREc8e/UR0uE8fmqsWVfk+prxTa/+KkaWFP/uiE5yFRFBV/uIPKcD+6eeGHr6fxY+okfswWPzKbf/0r3CL4TYVusjqfL1yCRhUu4EfZKcewRlhECUYcPxxVyH8iOV191rba4MHvAReHS/hX1T38l7ni+FdUQRH1CCFvBkKIUlKd8xlNqtyqhS/VhemIZhfTlme+kHUddKec8R37AG/YqMqnhrcTv5CKU2S7jAGqdOISLSFVh8CPqo0sbGGhqKpl6ju+1GJVOUacBC4ksK/3V4ikc4eRZcArvfrHIeEWgaqacg9ytC7cQvQjKpHINuRauFz8+AJlwm9zUtvykCP8F92HP1wmKgXvfaNZcc/K5oZZBQ+qQ4T9/iXef2nroa/6R8QyWsz5McaiGqltRC0Jk+EwWfwVY5naKpQ/wrPotlU+HAUVbuWvEn2YSixuQlPLxAliIoRodl5fbaAimgW/lEnI8VOU2O2QD3RCjc4sDeWD6KTEe52PbuCLaJZk5mEDKI1IOfyIKlf8i7Dyx/DKH8Mrf0yvwlLij9U2/LErvOiUecuJdVx+pFy5CiA8NpE13R+1KQlxRPnHOnU/JI/d3vwx2lvsM/nV1soh86ELmKAdxVpEd+6ZHNevdsLLhMeXH3GgshNt/czcRPYW/jPrLVTO1Hcf0fcMo7oRja+y7jTWIp4x7eng97C6E63qhTJdNctW20f2aMIGv1qIaqE64SNUUWM48GMcXkzjjN/njXBVE1BuvKYRTEQveoiic1XLcB6GqHdRdWAvpgfR7evrcNSRKodjd9j+03bY/pgddoxzZMOt62qRMTSf6i4WqatFrROBRrjhtRK/uYywEPe3RFiIn7XFtIgZmKh4vDMLuYp1mYVaLoYntUw5s7rr5O5wu4W1OFglehg4dCu8ZwrGKySKNb7xq8nmxbgl4nQXUZzuYonYFy5E2sT2FNan8Vc1V4spD/cz5gkwsfWFZexbLmLc63Da6x5US1IxBw0J+FRRGYoi5RU4hAr1MVJD1ZQi7Wp9UfwShxmp5epVHnzsbic60wh5pFNxoSAmwRFW4qe4olVEOFBi5hG/IuX5HMVRZDaINqWW85laZFpp1hN53nr0E9gjhUgWxs5oZ6af7hz1cLsY+Sm6hkhhZNpUrTdiYRm5qOTnawZfvV49VSZhUq80z+CiujO5f064Cd09oYiq4JxvtgQ3gaJLMWtWW/E1tFCIlKoVIle0PIZ+ZbGpusaMN39hjlzthtxHrnlFbqkqsHoJLHb08B6xmwdZlOWxiGrUZXHEkjjKujfsJuuI+1rExSyC1XPZ8OVyrFN7uZX49b9HnAighCRqHO9W1JN12Asxj2C4iW+j1dAMQSUXyQiJVDMrccyQ8Dds/R3q6vh15uEi0WfGWogLG+UMMp9XqRxCrhcFqBKIHBArdGHlAVOz6zKjNgZPf5/nDblSD15Cppy84o1wHbEyidgZiNwVCBfHdF2HGlKzMCStr6sLuY4QqzbvIuzEz0WFTYwlxJlsNqidiE5PyPlBFcIkyq+72VOC8+Q804unFeUqPaC3QThBtopX8dsnIYgy71fvYggzr0+qI8gj5aJc1RY=
*/