/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
qb3xVnuel3GDRLyGv5MMT71Nn3Ioz+E8GcWLeLVkeRU/vcxzxBv44cs8I6d7TvGKt3vueBWPfYfnjufxO7KC+4vC0C9lXsKnXW7/8wzu/077nxfwarmWV3HPKzwLPMJfvMt98cq77UfJ8wae9B5j42Xcb4V54BlcIRN4FX8lo3h2ZUtYLTvje8E932efq+dxg9TV63jfKs9C3M/77XnZpp76gP4kE7fHihzKa7jnBz2PPMKCRLyEP5Wlzg1l6ysp9SoevNozop690rxJQb2OL/iQdwXP4NPXeLfwLH5V6ryBUz/iHcKreJcU4rXAAz9q/nkGz5FFvICXS5mX8Ra5itdxyFX65yk8VlbwHF4gt/MSflqqvIp3SYU38MCrrQvP4LlyMy/gSrmWVzBcY5/E8/BZ3yc/px+exYuvNf88us73X9nG87j7F8wJz+Gc6z1fOf3gCes9m7yAK6WDV/BbMo3X8YEvevZ58UuuW/Xs8wjXyRJex703eP/wCMuyhlcxe6NnnOdxh6zi0U3eVzKa53C1DOVVfFgm8dRG7yjp5nm8Qtp4GW+TAV7HIV/2vZOn8Fg5iOdwnrTyIn5cRvIq3iMjePiKnyuk6Qzj+WpLWHiLMcT+NT/nyK74uniR7OAl/Khs4hW8VdbzOj7j694tPMJTZDPP46WykZdxg2zlNXxItvPUJn8W+Ia9NNnafdPPtN/S3hhyNc++bOZVbLrVevEIy7KFV/FXsomnvm1/yRpexaWbrQ0P32kJ75H1vIrPvsN98Qb2f9/9um4ZL73TnPAafmGLeePhBy1huozkRTzwh9aL53CRDOMlfFCaeOpHniE5iGfq9qG0ulYZH5JhPHVXS7hScvG1cN5P7Ddex1O3er54Ad/2U88Cr+PKu/U5xbnb7Lt79cnz2/1sLDu0Cfd5J//CffEivud+c8vreEfDdbWPHnCvvzR36jm8T3bE8/lgS7hBtvIGbt/h+YrH/6uWsODX5p/X8C07PV88PORnJ9nCU7/17MtSXsVf7XK+fkoPe65lOa/iPbKKh0dawnNlGo9wjEziObxAunkJr5cOXsOHpI2nfu/nAbmQZ/F8WcaLeLUs4VW8V8bxEFpDs4zgGTxXRvMCvk9G8greKQO8Ebcf0hpWxPeO98lWHu3WGhbJQfHY8ItylXoNP7F7ayjxBq5/WmsYap4Le7aGtXu3hiaefbqvywhewd2e0RrKPMLFciEv4X3SzVNDW8M5MsALePAzW8O6Nm3wQVkWt9m3NbxMlvAsjkm1hr3O1Aarw1rDcu1rz24Nlz1Hn7yKs5/bGjp4CaceoH9ew7HP0yfP46dkDa9h98GtYRSPnt8aemQSL+FA1BpSrtXAXzW3hsCz6dZwRktruN14ynjTIa2hznMvbA0fkLXxGPCIF7WGWlzHe+VQ50aHtoYTXtIaIl7DjxzRGjbF4znK2Ea2hp28iAuPbg0NHo6xJse2hlW8fFyr/2anNdwc9zla369qDRVeybb6M4I1ih1fc4J+eAlvH98a2trUT2wNM05qDcPjecMfSkbdP9wS3nOytebZU1rDm2UYL2M4XXgd35xzj7yCrzzDuXE/eIesV2/gyya3hmk8iw/LRp6ZYq5kZPz84qUympdxg0zjNbxb2ngD92trDeN4hKdIB8/jpTKJl/F3Z7aGbfovnNUaeqe2hgnxGuHkc6wjL2BZsryCba9uDTleO9een2ZP8Cy+TubwEi49rzXkeR2HvKY1FHgKx8sanscjpts/vICXyBJewpfm7RWex552+5xX8YwZ9icv4pEzrSPP4/ukcJaxYUMW8aijNbxcpvIsPq3T2GLHr0meh1nWURpxn/gJyahX8QdyKG8=
*/