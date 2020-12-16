/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
p+LUOlUob79zplwpysT1U9t3hbyJR4Lymmsf15mM9rvA0guEHwZJkvm52N2iGzBSrSldesepoWUrth4H3tto/zJ3w7J0mXy129jU075uvz+zODxhJ37k50HA4nhGvz8gbX9Wn+vPwffx9KPM9aKgcJisVuI90p9ncTgidP3MiSMWxRaNgRs9qD/8pIdMlvSnTELbspjsTp+6m1Si2qe7rvunMdlAZKVneYGj8v6s3vpGFcP6gAbi3uY69b3mXMiUL6TZYWgnoaw2OaFZp9p6jlaTns7v6xpljZ0s8dMsIaFnbNFqm9JTHyCMQobf8w828lvGZZyoqh7uDqRuUmo8u3z+epHJuyKyM5ojlwWPQO0BYU5i67kMk5V37JM0z5KMy5JT4hFdstjgWdBxzL2f+22PkzJ3Ai8QchaAtuqt1iPdAnW79jrSjCMVHn25HZqCCnnfWnof1Gsoef72kdtRv7y53JOlmAynqfq9yI8SPn8r4MxxKvbz6Ocpht9UIsJxKuZF72DzyCwKy9gXKvd+ShYGPuXJz489uDrAF5ATplwq/MjNMje3hU+7GsR9GP2Q8PDY0UoMPr1KU86OhV3K5xe8WFSTNieSYqvH5uUfG7v0OzZio6YhjpsrDqLuxPrsi8Xtkn7SaO5eXcx1ZK7O5ytZXInwAye1fNup2vsfRjcxo3g7msXtiSRJwiwrrKuMW0d3d/hnN+PLRemVse1lhVCLM4ptjwiO+Xpt8I7GutgJnMLx5dwCEfydfBzV8fymEU9hhdRJnEjIifVVxKPL03knn+t4aVzENDdWLalnBZX0BmrXkL+Nlodv/MKj72lR1e+eEUB+vpF+npWpH0R1feydPsb1prxdRrkTU3vsLY5xvSFb+oEVOSSs6nDvtI/rOYAp71DZy9Qq/CAVajqjN9Gq6sewrQbsBSiebCC5n4G3ieQZnxpnVmmpdNrYVTbuH8xIDs7escY59A4213fz3KJvTSDyx6Yp9ZL1DUwsxnfhv/R20+5AzkJOsbu0T1J5OQU/B3eFnwOJKX7rQBN3ug0O7kzBfgAY7kzBN4GBSTUwy/7KGWDqlAEyRnjzntRoFhjuScG37D5gOKT0tX68nX/LHBqwizKRc8WtYw9TvkbUakDex5A73c06zvX49nZ+fkgzVy+Nwmu+F6jbrMPbjOBTyk7kXfSdymVzLXvy3hDz//FE3Y7EVtvyRlvef0riEtm7LX8MTrstXzcNrNWWfwbG2hJnjRXG2/KGswhnbalkgLXbcnmfxtCWmA+cfxv7hpau5QRRlGFLQrca7vkTn92lcePMv+YWozrW97PeZrbZOFWVf2q7t9Q2PmmUy8e+fO945QsaZ2X084SqDZk07jBNSbx99/EzKnwsgQZu2KetTnNeDQNPZznetDW62MDrxgb+5H0cVw1u4JebuGp4wnHPmuN14wOfO8DxWgGwxj5otufRsKCvZZw6oiI35gy3abR9ELulG4XxtbY+bLvearY9b/c31u3ud81WJ8y4i3eibne0OfqtxNp35T6qwie3N+yhpk0O7+tfmgWGdoZv630aQxsDu/t+YGhf2BcCQ9sCO3RAY2hXYH8BhjaFbdbi2P4P9mmw2zIwuSw2bbrOjzF9aAXsgoFVy9Gx3MUxBj9JuPv91sYYn+du4V+7/5pbkb3gJTrT3N+JyvJ4sUyDuVN2xuH3QXhUPu4of5P38R12Soix48pUjTErScjSe5XAzbua8DekMNQGMPLBpTFECZuaNaOu1rdXRhsVBTgVELixPYe6PmfIb42210hftu6qz7sMjG0vGumXBme85hv7FQg57tSHx5sYA1h7xqLwc6+I8qt/77Juz1jn5618LVY=
*/